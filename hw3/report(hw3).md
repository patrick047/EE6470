# EE6470 Homework 3
### Gaussian Blur Filter
student:趙庭慶 number:109061616
## Implemation
### 3X3 Gaussian Blur Filter(systemC) with TLM 2.0
I modified the hw2 and lab03 source code to make the new 3X3 Gaussian Blur Filter(TLM2.0).
There are four parts of this source code
(1) GaussianBlurFilter.cpp(do convoluction), GaussianBlurFilter.h
(2) Testbench.cpp, Testbench.h
(3) main.cpp
(4) Initiator.cpp, Initiator.h
and using cmake to working this homework.
cmake: cmake --> Cmakelist.txt --> Makefile
make: Makefile
make run: run
#### structure
I modified the structure from the sobel filter(lab03).
![](https://raw.githubusercontent.com/patrick047/EE6470/main/hw3/hw3_2.jpg)

## Results 
### Original
![](https://raw.githubusercontent.com/patrick047/EE6470/main/hw1/Gaussian_Blur/lena.bmp)
### After hw3
![](https://raw.githubusercontent.com/patrick047/EE6470/main/hw3/GaussianBlurSC/build/lena_filted.bmp)
The simulation time is 2601473.
![](https://raw.githubusercontent.com/patrick047/EE6470/main/hw3/hw3_1.PNG)

## Source Code Introduction
#### GaussianBlurFilter mask
```
const double filter[MASK_X][MASK_Y] =
    {
        1,2,1,
        2,4,2,
        1,2,1,
};

double factor = 16.0;
double bias = 0.0;

```
#### socket connect to main.cpp
```
Testbench tb("tb");
  GaussianBlurFilter GaussianBlur_filter("GaussianBlur_filter");
  tb.initiator.i_skt(GaussianBlur_filter.t_skt);
```
#### blocking_transpot connect to do_GaussianBlur
```
void GaussianBlurFilter::blocking_transport(tlm::tlm_generic_payload &payload, sc_core::sc_time &delay)
{
  sc_dt::uint64 addr = payload.get_address();
  addr = addr - base_offset;
  unsigned char *mask_ptr = payload.get_byte_enable_ptr();
  unsigned char *data_ptr = payload.get_data_ptr();
  word buffer;

  switch (payload.get_command())
  {
  case tlm::TLM_READ_COMMAND:
    switch (addr)
    {
    case GaussianBlur_FILTER_RESULT_ADDR:
      buffer.uc[0] = o_result_r.read();
      buffer.uc[1] = o_result_g.read();
      buffer.uc[2] = o_result_b.read();

      break;
    default:
      std::cerr << "Error! SobelFilter::blocking_transport: address 0x"
                << std::setfill('0') << std::setw(8) << std::hex << addr
                << std::dec << " is not valid" << std::endl;
      break;
    }
    data_ptr[0] = buffer.uc[0];
    data_ptr[1] = buffer.uc[1];
    data_ptr[2] = buffer.uc[2];
    data_ptr[3] = buffer.uc[3];

    break;

  case tlm::TLM_WRITE_COMMAND:
    switch (addr)
    {
    case GaussianBlur_FILTER_R_ADDR:
      if (flag == 0)
      {
         buffer.uc[0]=data_ptr[0] ;
         buffer.uc[1]=data_ptr[1] ;
         buffer.uc[2]=data_ptr[2] ;
         buffer.uc[3]=data_ptr[3] ;
        i_width.write(buffer.uint);
        flag = 1;
      }
      else //(flag = 1)
      {
         
        if (mask_ptr[0] == 0xff)
        {
          i_r.write(data_ptr[0]);
        }
        if (mask_ptr[1] == 0xff)
        {
          i_g.write(data_ptr[1]);
        }
        if (mask_ptr[2] == 0xff)
        {
          i_b.write(data_ptr[2]);
        }
      }
      break;
    default:
      std::cerr << "Error! SobelFilter::blocking_transport: address 0x"
                << std::setfill('0') << std::setw(8) << std::hex << addr
                << std::dec << " is not valid" << std::endl;
      break;
    }
    break;

  case tlm::TLM_IGNORE_COMMAND:
    payload.set_response_status(tlm::TLM_GENERIC_ERROR_RESPONSE);
    return;
  default:
    payload.set_response_status(tlm::TLM_GENERIC_ERROR_RESPONSE);
    return;
  }
  payload.set_response_status(tlm::TLM_OK_RESPONSE); // Always OK
}
```
