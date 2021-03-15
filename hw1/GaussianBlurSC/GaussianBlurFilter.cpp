#include <algorithm>
#include <cstdio>
#include <cassert>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <systemc>
#include "GaussianBlurFilter.h"

GaussianBlurFilter::GaussianBlurFilter(sc_module_name n) : sc_module(n)
{
    SC_THREAD(do_GaussianBlurFilter);
    sensitive << i_clk.pos();
    dont_initialize();
    reset_signal_is(i_rst, false);
}
// GaussianBlurFilter mask
const double filter[MASK_X][MASK_Y] =
    {
        1,
        2,
        1,
        2,
        4,
        2,
        1,
        2,
        1,
};

double factor = 16.0;
double bias = 0.0;


void GaussianBlurFilter::do_GaussianBlurFilter()
{std::cout<<"gg";
    {
        wait();
    }
    //double red = 0.0, green = 0.0, blue = 0.0;
    while (true)
    { std::cout<<"gg";
        red = 0.0;
        green = 0.0;
        blue = 0.0;
        wait();
        for (unsigned int v = 0; v < MASK_Y; ++v)
        {
            for (unsigned int u = 0; u < MASK_X; ++u)
            {
                red += i_r.read() * filter[u][v];
                green += i_g.read() * filter[u][v];
                blue += i_b.read() * filter[u][v];
                //val[i] += grey * mask[i][u][v];
                wait();
            }
        }
        std::cout <<std::setw(12)<< red/16 <<std::setw(12)<<green/16 <<std::setw(12)<< blue/16 << std::endl;
    o_result_r.write(red / factor);
    o_result_g.write(green / factor);
    o_result_b.write(blue / factor);
    }
    
}

