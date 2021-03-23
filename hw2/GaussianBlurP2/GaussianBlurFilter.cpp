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
    int r[3][width], g[3][width], b[3][width];
    int m, n;
    int flag = 0;
    for (m = 0; m < 3; ++m) //setup array(m列n行)
    {
        for (n = 0; n < width; ++n)
        {
            r[m][n] = 0;
            g[m][n] = 0;
            b[m][n] = 0;
        }
    }

    while (true)
    {
        if (flag == 0)
        {
            for (m = 0; m < MASK_X; ++m)
            {
                for (n = 0; n < width; ++n)
                {
                    r[m][n] = i_r.read();
                    g[m][n] = i_g.read();
                    b[m][n] = i_b.read();
                }
            }
            flag = 1;
        }
        if (flag != 0)
        {

            for (int n = 0; n < width; ++n)
            {

                r[0][n] = r[1][n];
                g[0][n] = g[1][n];
                b[0][n] = b[1][n];
                r[1][n] = r[2][n];
                g[1][n] = g[2][n];
                b[1][n] = b[2][n];
                r[2][n] = g[2][n] = b[2][n] = 0;
            }

            for (int n = 0; n < width; ++n)
            {
                r[2][n] = i_r.read();
                g[2][n] = i_g.read();
                b[2][n] = i_b.read();
            }
        }

        wait();

        for (int d = 0; d < width; ++d)
        {
            double red = 0.0, green = 0.0, blue = 0.0;
            wait();
            for (unsigned int v = 0; v < MASK_Y; ++v)
            {
                for (unsigned int u = 0; u < MASK_X; ++u)
                {

                    red += r[u][v + d] * filter[u][v];
                    green += g[u][v + d] * filter[u][v];
                    blue += b[u][v + d] * filter[u][v];

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
