#include <systemc>
#include <iostream>
#include <string>
using namespace std;

// Wall Clock Time Measurement
#include <sys/time.h>

#include "GaussianBlurFilter.h"
#include "Testbench.h"

// TIMEVAL STRUCT IS Defined ctime
// use start_time and end_time variables to capture
// start of simulation and end of simulation
struct timeval start_time, end_time;

// int main(int argc, char *argv[])
int sc_main(int argc, char **argv) {
  
  Testbench tb("tb");
  GaussianBlurFilter GaussianBlur_filter("GaussianBlur_filter");
  sc_clock clk("clk", CLOCK_PERIOD, SC_NS);
  sc_signal<bool> rst("rst");
  sc_fifo<unsigned char> r;
  sc_fifo<unsigned char> g;
  sc_fifo<unsigned char> b;
  sc_fifo<int> result_r;
  sc_fifo<int> result_g;
  sc_fifo<int> result_b;
  tb.i_clk(clk);
  tb.o_rst(rst);
  GaussianBlur_filter.i_clk(clk);
  GaussianBlur_filter.i_rst(rst);
  tb.o_r(r);
  tb.o_g(g);
  tb.o_b(b);
  tb.i_result_r(result_r);
  tb.i_result_g(result_g);
  tb.i_result_b(result_b);
  GaussianBlur_filter.i_r(r);
  GaussianBlur_filter.i_g(g);
  GaussianBlur_filter.i_b(b);
  GaussianBlur_filter.o_result_r(result_r);
  GaussianBlur_filter.o_result_g(result_g);
  GaussianBlur_filter.o_result_b(result_b);

  tb.read_bmp(argv[1]);
  sc_start();
  std::cout << "Simulated time == " << sc_core::sc_time_stamp() << std::endl;
  tb.write_bmp(argv[2]);

  return 0;
}
