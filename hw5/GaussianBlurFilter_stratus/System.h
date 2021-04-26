#ifndef SYSTEM_H_
#define SYSTEM_H_
#include <systemc>
#include <string>
#include "filter_def.h"
using namespace sc_core;

#include "Testbench.h"
#ifndef NATIVE_SYSTEMC
#include "GaussianBlurFilter_wrap.h"
#else
#include "GaussianBlurFilter.h"
#endif

class System: public sc_module
{
public:
	SC_HAS_PROCESS( System );
	System( sc_module_name n, std::string input_bmp, std::string output_bmp );
	~System();
private:
  Testbench tb;
#ifndef NATIVE_SYSTEMC
	GaussianBlurFilter_wrapper GaussianBlurFilter;
#else
	GaussianBlurFilter GaussianBlurFilter;
#endif
	sc_clock clk;
	sc_signal<bool> rst;
#ifndef NATIVE_SYSTEMC
	cynw_p2p< sc_dt::sc_uint<24> > rgb;
	cynw_p2p< sc_dt::sc_uint<32> > result;
#else
	sc_fifo< sc_dt::sc_uint<24> > rgb;
	sc_fifo< sc_dt::sc_uint<32> > result;
#endif

	std::string _output_bmp;
};
#endif
