
#ifndef GaussianBlur_FILTER_H_
#define GaussianBlur_FILTER_H_
#include <systemc>
using namespace sc_core;

#include "filter_def.h"

class GaussianBlurFilter : public sc_module {
public:
  sc_in_clk i_clk;
  sc_in<bool> i_rst;
  sc_fifo_in<unsigned char> i_r;
  sc_fifo_in<unsigned char> i_g;
  sc_fifo_in<unsigned char> i_b;
  sc_fifo_out<int> o_result_r;
  sc_fifo_out<int> o_result_g;
  sc_fifo_out<int> o_result_b;

  sc_fifo_in<unsigned int> i_height; //new
  sc_fifo_in<unsigned int> i_width;  //new

  

  SC_HAS_PROCESS(GaussianBlurFilter);
  GaussianBlurFilter(sc_module_name n);
  ~GaussianBlurFilter() = default;

private:
  void do_GaussianBlurFilter();
  double red = 0.0, green = 0.0, blue = 0.0;
  int width = 0;
  int height = 0;
};
#endif