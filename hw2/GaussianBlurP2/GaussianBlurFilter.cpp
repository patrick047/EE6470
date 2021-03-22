#include <algorithm>
#include <cstdio>
#include <cassert>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <systemc>
#include "GaussianBlurFilter.h"
#include "filter_def.h"
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
{
    {
        wait();
    }
    width = i_width.read();
    height = i_height.read();
    int array_r[3][width];
    int array_g[3][width];
    int array_b[3][width];
    int m,n;
    int flag = 0;
    for ( m = 0; m < 3; ++m)
    {
        for ( n = 0; n < width ; ++n)
        {
            array_r[m][n] = 0;
            array_g[m][n] = 0;
            array_b[m][n] = 0;
        }
    }

    while (true)
    {
        if (flag == 0)
        {
            for ( m = 0; m < MASK_X; ++m)
            {
                for ( n = 0; n < width; ++n)
                {
                    array_r[m][n] = i_r.read();
                    array_g[m][n] = i_g.read();
                    array_b[m][n] = i_b.read();
                }
            }
            flag = 1;
        }
        else
        {
            for ( m = 0; m < MASK_N; ++m)  //shift
            {
            array_r[0][n] = array_r[1][n];
            array_g[0][n] = array_g[1][n];
            array_b[0][n] = array_b[1][n];
            array_r[1][n] = array_r[2][n];
            array_g[1][n] = array_g[2][n];
            array_b[1][n] = array_b[2][n];
            array_r[2][n] = array_g[2][n] = array_b[2][n] = 0;
            }
            for (int k = 0; k < width; ++k)
            {
                array_r[2][k] = i_r.read();
                array_g[2][k] = i_g.read();
                array_b[2][k] = i_b.read();
            }
        }

        wait();

        for (int s = 0; s < width; ++s)
        {
            red = 0.0;
            green = 0.0;
            blue = 0.0;
            wait();
            for (unsigned int v = 0; v < MASK_Y; ++v)
            {
                for (unsigned int u = 0; u < MASK_X; ++u)
                {
                    red += array_r[u][v + s] * filter[u][v];
                    green += array_g[u][v + s] * filter[u][v];
                    blue += array_b[u][v + s] * filter[u][v];
                   
                    wait();
                }
            }
            std::cout << std::setw(12) << red / 16 << std::setw(12) << green / 16 << std::setw(12) << blue / 16 << std::endl;
            o_result_r.write(red / factor);
            o_result_g.write(green / factor);
            o_result_b.write(blue / factor);
        }
    }
}