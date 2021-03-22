# EE6470 Homework 2
### Gaussian Blur Filter
student:趙庭慶 number:109061616
## Implemation
### Part 1: 3X3 Gaussian Blur Filter(systemC) with FIFO
(NOTE: Same with the HW1 Part2)
I modified the Lab02 sobel_fifo source code to the new 3X3 Gaussian Blur Filter(systemC type).
There are three parts of this source code
(1) GaussianBlurFilter.cpp(do convoluction), GaussianBlurFilter.h
(2) Testbench.cpp, Testbench.h
(3) main.cpp
and using cmake to working this homework.
cmake: cmake --> Cmakelist.txt --> Makefile
make: Makefile
make run: run
#### structure
I modified the structure from the sobel filter(fifo).
![](https://github.com/patrick047/EE6470/blob/main/hw1/sobel_sw/001.jpg)
##### The output of the Testbench:
rst, o_r.write, o_g.write, o_b.write. (write into GaussianBlurFilter)
##### The input of the Testbench:
clk, i_resulr_r.read, i_resulr_g.read, i_resulr_b.read. (read from GaussianBlurFilter)
##### The output of the GaussianBlurFilter:
o_result_r.write, o_result_g.write, o_result_b.write. (write into Testbench)
##### The intput of the GaussianBlurFilter:
sc_main, rst, i_r.read, i_g.read, i_b.read. (read from Testbench)

### Part 2: 3X3 Gaussian Blur Filter(systemC) with FIFO and matrix
In GaussianBlurFilter.cpp, I used array to read the data from r,g,b, then read the image three row at first. 
After that, shift to read.
![](https://raw.githubusercontent.com/patrick047/EE6470/main/hw2/GaussianBlurP2/hw2_3.bmp)
Then, using 3X3 Gaussian Blur to deal with the data that stored in the array and write the result into o_result_r, o_result_g, o_result_b. 
I added i_weight, i_height, o_weight, o_height to send the size of images.(Different from part1)
```
sc_fifo<unsigned int> width, height; //new

tb.o_height(height); //new
tb.o_width(width); //new

GaussianBlur_filter.i_height(height); //new
GaussianBlur_filter.i_width(width); //new

```

## Results 
### Original
![](https://raw.githubusercontent.com/patrick047/EE6470/main/hw1/Gaussian_Blur/lena.bmp)
### Part 1
![](https://raw.githubusercontent.com/patrick047/EE6470/main/hw2/GaussianBlurSC/build/lena_filted.bmp)
The simulation time is 2621446.
![](https://raw.githubusercontent.com/patrick047/EE6470/main/hw2/GaussianBlurSC/hw2_1.png)
### Part 2
![](https://raw.githubusercontent.com/patrick047/EE6470/main/hw2/GaussianBlurP2/build/lena_filted.bmp)
The simulation time is 2606894.
![](https://raw.githubusercontent.com/patrick047/EE6470/main/hw2/GaussianBlurP2/hw2_2.png)

## Discussions
For this homework, I modified source code of the lab02 sobel_fifo from TA provided.
In the systemC type, I debug my code more than hundreds times because I did the convoluction twice that I did not notice its mistake.
After that, I fixed it. 
I didn't use the systemC data type in this homework because I am not really familiar with it.
Thus, I have to work hard on it after submit this homework report. 
In my observation, the result(simulation time) of part1 is more than part2.
Because of part2 take r,g,b into matrix, it is very effective that make the simulation time decrease.
I used two threads to avoid my code not working, ensure the channel(fifo) will not stuck.
