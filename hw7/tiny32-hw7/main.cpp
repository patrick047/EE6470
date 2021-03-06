
#include <string.h>
#include "stdio.h"

#include "lena_std_short.h" //included here to avoid compiler issue of not initializing global arrays
unsigned char* source_array= lena_std_short_bmp;

//Filter ACC
static char* const FILTER_START_ADDR[2] = {reinterpret_cast<char* const>(0x73000000),
											reinterpret_cast<char* const>(0x74000000)};
static char* const FILTER_READ_ADDR[2]   = {reinterpret_cast<char* const>(0x73000004),
											reinterpret_cast<char* const>(0x74000004)};

// DMA 
static volatile uint32_t * const DMA_SRC_ADDR  = (uint32_t * const)0x70000000;
static volatile uint32_t * const DMA_DST_ADDR  = (uint32_t * const)0x70000004;
static volatile uint32_t * const DMA_LEN_ADDR  = (uint32_t * const)0x70000008;
static volatile uint32_t * const DMA_OP_ADDR   = (uint32_t * const)0x7000000C;
static volatile uint32_t * const DMA_STAT_ADDR = (uint32_t * const)0x70000010;
static const uint32_t DMA_OP_MEMCPY = 1;
static const uint32_t DMA_OP_NOP = 0;

//TODO fixed DMA access
bool _is_using_dma = false;
//Total number of cores
//static const int PROCESSORS = 2;
#define PROCESSORS 2
//the barrier synchronization objects
uint32_t barrier_counter=0; 
uint32_t barrier_lock; 
uint32_t barrier_sem; 
//the mutex object to control global summation
uint32_t lock;  
//print synchronication semaphore (print in core order)
uint32_t print_sem[PROCESSORS]; 


// semaphore
int sem_init (uint32_t *__sem, uint32_t count) __THROW{
  *__sem=count;
  return 0;
}
int sem_wait (uint32_t *__sem) __THROW{
  uint32_t value, success; //RV32A
  __asm__ __volatile__("\
L%=:\n\t\
     lr.w %[value],(%[__sem])            # load reserved\n\t\
     beqz %[value],L%=                   # if zero, try again\n\t\
     addi %[value],%[value],-1           # value --\n\t\
     sc.w %[success],%[value],(%[__sem]) # store conditionally\n\t\
     bnez %[success], L%=                # if the store failed, try again\n\t\
"
    : [value] "=r"(value), [success]"=r"(success)
    : [__sem] "r"(__sem)
    : "memory");
  return 0;
}

int sem_post (uint32_t *__sem) __THROW{
  uint32_t value, success; //RV32A
  __asm__ __volatile__("\
L%=:\n\t\
     lr.w %[value],(%[__sem])            # load reserved\n\t\
     addi %[value],%[value], 1           # value ++\n\t\
     sc.w %[success],%[value],(%[__sem]) # store conditionally\n\t\
     bnez %[success], L%=                # if the store failed, try again\n\t\
"
    : [value] "=r"(value), [success]"=r"(success)
    : [__sem] "r"(__sem)
    : "memory");
  return 0;
}

// barrier
int barrier(uint32_t *__sem, uint32_t *__lock, uint32_t *counter, uint32_t thread_count) {
	sem_wait(__lock);
	if (*counter == thread_count - 1) { //all finished
		*counter = 0;
		sem_post(__lock);
		for (int j = 0; j < thread_count - 1; ++j) sem_post(__sem);
	} else {
		(*counter)++;
		sem_post(__lock);
		sem_wait(__sem);
	}
	return 0;
}

// DMA
void write_data_to_ACC(char* ADDR, unsigned char* buffer, int len, int hart_id){
    if(_is_using_dma){  
        // Using DMA 
	    sem_wait(&lock);
        *(DMA_SRC_ADDR) = (uint32_t)(buffer);
        *(DMA_DST_ADDR) = (uint32_t)(ADDR);
        *(DMA_LEN_ADDR) = len;
        *(DMA_OP_ADDR)  = DMA_OP_MEMCPY;
	    sem_post(&lock);

    }else{
        // Directly Send
        memcpy(ADDR, buffer, sizeof(unsigned char)*len);
    }
}
void read_data_from_ACC(char* ADDR, unsigned char* buffer, int len, int hart_id){
    if(_is_using_dma){
        // Using DMA 
	    sem_wait(&lock);
        *(DMA_SRC_ADDR) = (uint32_t)(ADDR);
        *(DMA_DST_ADDR) = (uint32_t)(buffer);
        *(DMA_LEN_ADDR) = len;
        *(DMA_OP_ADDR)  = DMA_OP_MEMCPY;
	    sem_post(&lock);
    }else{
        // Directly Read
        memcpy(buffer, ADDR, sizeof(unsigned char)*len);
    }
}

// read array
unsigned int ReadfromByteArray(unsigned char* array, unsigned int offset) {
	unsigned int output = (array[offset] << 0) | (array[offset + 1] << 8) | (array[offset + 2] << 16) | (array[offset + 3] << 24);
	return output;
}

// main
int main(unsigned hart_id) {

	if (hart_id == 0) {
		// create a barrier object with a count of PROCESSORS
		sem_init(&barrier_lock, 1);
		sem_init(&barrier_sem, 0); //lock all cores initially
		for(int i=0; i< 2; ++i){
			sem_init(&print_sem[i], 0); //lock printing initially
		}
		// Create mutex lock
		sem_init(&lock, 1);
	}

  unsigned int input_rgb_raw_data_offset = ReadfromByteArray(source_array, 10);
	unsigned int width = ReadfromByteArray(source_array, 18);
	unsigned int length = ReadfromByteArray(source_array, 22);
	unsigned int bytes_per_pixel = ReadfromByteArray(source_array, 28) / 8;
	unsigned char* source_bitmap = &source_array[input_rgb_raw_data_offset];

  unsigned char  buffer[4] = {0};
	int start = (hart_id == 0 ? 0 : width/2);
	int end = (hart_id == 0 ? width/2 : width);
	
    for(int i = start; i < end; i++) {
      for(int j = 0; j < length; j++) {
        for(int y = -1; y <= 1; y ++) {
          for(int x = -1; x <= 1; x++) {
            if(0 <= i + y && i + y < length && 0 <= j + x && j + x < width){
                buffer[0] = *(source_bitmap + bytes_per_pixel * ((i + y) * width + (j + x)) + 2);
                buffer[1] = *(source_bitmap + bytes_per_pixel * ((i + y) * width + (j + x)) + 1);
                buffer[2] = *(source_bitmap + bytes_per_pixel * ((i + y) * width + (j + x)) + 0);
                buffer[3] = 0;
            }
            else{
                buffer[0] = 0;
                buffer[1] = 0;
                buffer[2] = 0;
                buffer[3] = 0;
            }
            write_data_to_ACC(FILTER_START_ADDR[hart_id], buffer, 4, hart_id);
			      if(hart_id == 0) continue;
            // printf("core%d: send %d %d %d\n", hart_id, *buffer, *(buffer+1), *(buffer+2));
          }
        }
        read_data_from_ACC(FILTER_READ_ADDR[hart_id], buffer, 4, hart_id);
			  if(hart_id == 0) continue;
        // printf("core%d: get %d %d %d\n", hart_id, *buffer, *(buffer+1), *(buffer+2));
      }
    }

	barrier(&barrier_sem, &barrier_lock, &barrier_counter, PROCESSORS);

	if (hart_id == 0) sem_post(&print_sem[1]);  // Allow Core 1 to print
  return 0;
}
