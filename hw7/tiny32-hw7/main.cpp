#include <string.h>

#include "stdio.h"

// Filter ACC
static char* const GAUSSIANBLURFILTER_START_ADDR[2] = {reinterpret_cast<char* const>(0x73000000),
                                                       reinterpret_cast<char* const>(0x74000000)};
static char* const GAUSSIANBLURFILTER_READ_ADDR[2] = {reinterpret_cast<char* const>(0x73000004),
                                                      reinterpret_cast<char* const>(0x74000004)};

// DMA
static volatile uint32_t* const DMA_SRC_ADDR = (uint32_t* const)0x70000000;
static volatile uint32_t* const DMA_DST_ADDR = (uint32_t* const)0x70000004;
static volatile uint32_t* const DMA_LEN_ADDR = (uint32_t* const)0x70000008;
static volatile uint32_t* const DMA_OP_ADDR = (uint32_t* const)0x7000000C;
static volatile uint32_t* const DMA_STAT_ADDR = (uint32_t* const)0x70000010;
static const uint32_t DMA_OP_MEMCPY = 1;
static const uint32_t DMA_OP_NOP = 0;

bool _is_using_dma = false;
uint32_t lock;

// read array
unsigned int ReadfromByteArray(unsigned char* array, unsigned int offset) {
	unsigned int output = (array[offset] << 0) | (array[offset + 1] << 8) | (array[offset + 2] << 16) | (array[offset + 3] << 24);
	return output;
}

// sem_x
int sem_init(uint32_t* __sem, uint32_t count) __THROW {
	*__sem = count;
	return 0;
}
int sem_wait(uint32_t* __sem) __THROW {
	uint32_t value, success;  // RV32A
	__asm__ __volatile__(
	    "\
L%=:\n\t\
     lr.w %[value],(%[__sem])            # load reserved\n\t\
     beqz %[value],L%=                   # if zero, try again\n\t\
     addi %[value],%[value],-1           # value --\n\t\
     sc.w %[success],%[value],(%[__sem]) # store conditionally\n\t\
     bnez %[success], L%=                # if the store failed, try again\n\t\
"
	    : [value] "=r"(value), [success] "=r"(success)
	    : [__sem] "r"(__sem)
	    : "memory");
	return 0;
}

int sem_post(uint32_t* __sem) __THROW {
	uint32_t value, success;  // RV32A
	__asm__ __volatile__(
	    "\
L%=:\n\t\
     lr.w %[value],(%[__sem])            # load reserved\n\t\
     addi %[value],%[value], 1           # value ++\n\t\
     sc.w %[success],%[value],(%[__sem]) # store conditionally\n\t\
     bnez %[success], L%=                # if the store failed, try again\n\t\
"
	    : [value] "=r"(value), [success] "=r"(success)
	    : [__sem] "r"(__sem)
	    : "memory");
	return 0;
}

void write_data_to_ACC(char* ADDR, unsigned char* buffer, int len, int hart_id) {
	if (_is_using_dma) {
		// Using DMA
		sem_wait(&lock);
		*DMA_SRC_ADDR = (uint32_t)(buffer);
		*DMA_DST_ADDR = (uint32_t)(ADDR);
		*DMA_LEN_ADDR = len;
		*DMA_OP_ADDR = DMA_OP_MEMCPY;
		sem_post(&lock);
	} else {
		// Directly Send
		memcpy(ADDR, buffer, sizeof(unsigned char) * len);
	}
}
void read_data_from_ACC(char* ADDR, unsigned char* buffer, int len, int hart_id) {
	if (_is_using_dma) {
		// Using DMA
		sem_wait(&lock);
		*DMA_SRC_ADDR = (uint32_t)(ADDR);
		*DMA_DST_ADDR = (uint32_t)(buffer);
		*DMA_LEN_ADDR = len;
		*DMA_OP_ADDR = DMA_OP_MEMCPY;
		sem_post(&lock);
	} else {
		// Directly Read
		memcpy(buffer, ADDR, sizeof(unsigned char) * len);
	}
}

int main(unsigned hart_id) {
	if (hart_id == 0)
		sem_init(&lock, 1);


#include "lena_std_short.h"  //included here to avoid compiler issue of not initializing global arrays
	unsigned char* source_array = lena_std_short_bmp;

	bool pass = true;
	unsigned int input_rgb_raw_data_offset = ReadfromByteArray(source_array, 10);
	unsigned int width = ReadfromByteArray(source_array, 18);
	unsigned int length = ReadfromByteArray(source_array, 22);
	unsigned int bytes_per_pixel = ReadfromByteArray(source_array, 28) / 8;
	unsigned char* source_bitmap = &source_array[input_rgb_raw_data_offset];
	printf("======================================\n");
	printf("Core %d\n", (hart_id == 0 ? 0 : 1));
	printf("\t  Reading from array\n");
	printf("======================================\n");
	printf(" input_rgb_raw_data_offset\t= %d\n", input_rgb_raw_data_offset);
	printf(" width\t\t\t\t= %d\n", width);
	printf(" length\t\t\t\t= %d\n", length);
	printf(" bytes_per_pixel\t\t= %d\n", bytes_per_pixel);
	printf("======================================\n");

	unsigned char buffer[4] = {0};
	int start = (hart_id == 0 ? 0 : width / 2);
	int end = (hart_id == 0 ? width / 2 : width);
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < length; j++) {
			for (int v = -1; v <= 1; v++) {
				for (int u = -1; u <= 1; u++) {
					if ((v + i) >= 0 && (v + i) < width && (u + j) >= 0 && (u + j) < length) {
						buffer[0] = *(source_bitmap + bytes_per_pixel * ((j + u) * width + (i + v)) + 2);
						buffer[1] = *(source_bitmap + bytes_per_pixel * ((j + u) * width + (i + v)) + 1);
						buffer[2] = *(source_bitmap + bytes_per_pixel * ((j + u) * width + (i + v)) + 0);
						buffer[3] = 0;
					} else {
						buffer[0] = 0;
						buffer[1] = 0;
						buffer[2] = 0;
						buffer[3] = 0;
					}
					write_data_to_ACC(GAUSSIANBLURFILTER_START_ADDR[hart_id], buffer, 4, hart_id);
				}
			}
			read_data_from_ACC(GAUSSIANBLURFILTER_READ_ADDR[hart_id], buffer, 4, hart_id);
      /*
			unsigned char R = output_bmp[bytes_per_pixel * (i * width + j) + 2];
			unsigned char G = output_bmp[bytes_per_pixel * (i * width + j) + 1];
			unsigned char B = output_bmp[bytes_per_pixel * (i * width + j) + 0];
			if (hart_id == 0)
				continue;
			if (R != buffer[0]) {
				printf("[ERROR] R: i:%d, j:%d, result:%d, correct:%d\n", i, j, buffer[0], R);
				pass = false;
			} else {
				// printf("[CORRECT] R: i:%d, j:%d, result:%d, correct:%d\n", i, j, buffer[0], R);
			}

			if (G != buffer[1]) {
				printf("[ERROR] G: i:%d, j:%d, result:%d, correct:%d\n", i, j, buffer[1], G);
				pass = false;
			} else {
				// printf("[CORRECT] G: i:%d, j:%d, result:%d, correct:%d\n", i, j, buffer[1], G);
			}

			if (B != buffer[2]) {
				printf("[ERROR] B: i:%d, j:%d, result:%d, correct:%d\n", i, j, buffer[2], B);
				pass = false;
			} else {
				// printf("[CORRECT] B: i:%d, j:%d, result:%d, correct:%d\n", i, j, buffer[2], B);
      */
			}
		}
		printf("Current: %d\n", i);
	}
}