#include <cmath>
#ifndef NATIVE_SYSTEMC
#include "stratus_hls.h"
#endif

#include "GaussianBlurFilter.h"

GaussianBlurFilter::GaussianBlurFilter(sc_module_name n) : sc_module(n)
{
#ifndef NATIVE_SYSTEMC
	HLS_FLATTEN_ARRAY(val);
#endif
	SC_THREAD(do_filter);
	sensitive << i_clk.pos();
	dont_initialize();
	reset_signal_is(i_rst, false);

#ifndef NATIVE_SYSTEMC
	i_r.clk_rst(i_clk, i_rst);
	i_g.clk_rst(i_clk, i_rst);
	i_b.clk_rst(i_clk, i_rst);
    o_r.clk_rst(i_clk, i_rst);
    o_g.clk_rst(i_clk, i_rst);
    o_b.clk_rst(i_clk, i_rst);
#endif
}

GaussianBlurFilter::~GaussianBlurFilter() {}

// sobel mask
const int filter[MASK_X][MASK_Y] =
	{
    {1,2,1},
    {2,4,2},
    {1,2,1}
};

const int factor = 16.0;


void GaussianBlurFilter::do_filter()
{
	sc_uint<8> source_r, source_g, source_b, i, j;
	//sc_uint<24> source_rgb, result_rgb;
	sc_uint<32> R, G, B; // color of R, G, B
	{
#ifndef NATIVE_SYSTEMC
		HLS_DEFINE_PROTOCOL("main_reset");
		i_r.reset();
		i_g.reset();
		i_b.reset();
		o_r.reset();
		o_g.reset();
		o_b.reset();
#endif
		wait();
	}
	while (true)
	{
		R = G = B = 0;
		for (unsigned int v = 0; v < MASK_Y; ++v)
		{
			for (unsigned int u = 0; u < MASK_X; ++u)
			{

				//sc_dt::sc_uint<24> rgb;

#ifndef NATIVE_SYSTEMC
				{
					HLS_DEFINE_PROTOCOL("input");
					source_r = i_r.get();
                    source_g = i_g.get();
                    source_b = i_b.get();
					wait();
				}
#else
				    source_r = i_r.read();
                    source_g = i_g.read();
                    source_b = i_b.read();
#endif
				//source_r = rgb.range(7, 0);
				//source_g = rgb.range(15, 8);
				//source_b = rgb.range(23, 16);
				{
					HLS_CONSTRAIN_LATENCY(0, 1, "lat01");
					R += (sc_uint<32>)source_r * filter[u][v];
					G += (sc_uint<32>)source_g * filter[u][v];
					B += (sc_uint<32>)source_b * filter[u][v];
				}
			}
		}
		//result_rgb.range(7, 0) = (sc_uint<8>)(R / factor);
		//result_rgb.range(15, 8) = (sc_uint<8>)(G / factor);
		//result_rgb.range(23, 16) = (sc_uint<8>)(B / factor);
#ifndef NATIVE_SYSTEMC
		{
			HLS_DEFINE_PROTOCOL("output");
			o_r.put((sc_uint<8>)(R/factor));
            o_g.put((sc_uint<8>)(G/factor));
            o_b.put((sc_uint<8>)(B/factor));
			wait();
		}
#else
		o_r.write((sc_uint<8>)(R/factor));
        o_g.write((sc_uint<8>)(G/factor));
        o_b.write((sc_uint<8>)(B/factor));
#endif
	}
}
