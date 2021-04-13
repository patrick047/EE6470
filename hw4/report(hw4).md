# EE6470 Homework 4
### Gaussian Blur Filter
student:趙庭慶 number:109061616
## Implemation
### 3X3 Gaussian Blur Filter(systemC) with TLM 2.0 bus
I modified the hw3 and lab04 source code to make the new 3X3 Gaussian Blur Filter(TLM2.0 bus).
There are seven parts of this source code
(1) GaussianBlurFilter.cpp(do convoluction), GaussianBlurFilter.h
(2) Testbench.cpp, Testbench.h
(3) main.cpp
(4) Initiator.cpp, Initiator.h
(5) MemoryMap.h
(6) Simplebus.h
(7) tlm_log.cpp, tlm_log.h
and using cmake to working this homework.
cmake: cmake --> Cmakelist.txt --> Makefile
make: Makefile
make run: run
#### structure
I modified the structure from the lab04.
![](https://raw.githubusercontent.com/patrick047/EE6470/main/hw4/hw4_2.jpg)

## Results 
### Original
![](https://raw.githubusercontent.com/patrick047/EE6470/main/hw1/Gaussian_Blur/lena.bmp)
### After hw4
![](https://raw.githubusercontent.com/patrick047/EE6470/main/hw4/build/lena_filted.bmp)
The simulation time is 2601473.
![](https://raw.githubusercontent.com/patrick047/EE6470/main/hw4/hw4_1.PNG)

## Source Code Introduction(new from before)
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
#### Testbench connect to SimpleBus and Filter
```
Testbench tb("tb");
  SimpleBus<1, 1> bus("bus"); //lab04
  bus.set_clock_period(sc_time(CLOCK_PERIOD, SC_NS));  //lab04
  GaussianBlurFilter GaussianBlur_filter("GaussianBlur_filter");
  tb.initiator.i_skt(bus.t_skt[0]);
  bus.setDecode(0, GaussianBlur_MM_BASE, GaussianBlur_MM_BASE + GaussianBlur_MM_SIZE - 1);  //lab04
  bus.i_skt[0](GaussianBlur_filter.t_skt);  //lab04
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
#### SimpleBus, manage i_skt, t_skt and MemoryMap
```
SC_HAS_PROCESS(SimpleBus);
  SimpleBus(sc_core::sc_module_name name, double clock_period_in_ps = 1000,
            bool trace = false, bool masked = true)
      : sc_core::sc_module(name), MemoryMap(name, NR_OF_INITIATOR_SOCKETS),
        clock_period(clock_period_in_ps, sc_core::SC_PS), m_trace(trace),
        m_is_address_masked(masked) {
    for (unsigned int i = 0; i < NR_OF_TARGET_SOCKETS; ++i) {
      t_skt[i].register_b_transport(this, &SimpleBus::initiatorBTransport, i);
      t_skt[i].register_transport_dbg(this, &SimpleBus::transportDebug, i);
      t_skt[i].register_get_direct_mem_ptr(this, &SimpleBus::getDMIPointer, i);
    }
    for (unsigned int i = 0; i < NR_OF_INITIATOR_SOCKETS; ++i) {
      i_skt[i].register_invalidate_direct_mem_ptr(
          this, &SimpleBus::invalidateDMIPointers, i);
    }
  }
```
