# EE6470 Homework 1 
### Gaussian Blur Filter
student:趙庭慶 number:109061616
## Implemation
### Part 1: 3X3 Gaussian Blur Filter(c/c++)
I modified the sobel filter source code as the new 3X3 Gaussian Blur Filter from the [website](https://lodev.org/cgtutor/filtering.html#Gaussian_Blur_) that TA provied.
I used the following code as the filter parameters.
```
double filter[filterHeight][filterWidth] =
{
  1, 2, 1,
  2, 4, 2,
  1, 2, 1,
};

double factor = 1.0 / 16.0;
double bias = 0.0;

```

Then, the code down below is doing the convolution part.
```
void GaussianBlur_filter(){
  for(unsigned int y = 0; y < height; y++){
    for(unsigned int x = 0; x < width; x++){
      double red = 0.0, green = 0.0, blue = 0.0;
      //set the color values in the arrays
      for(int filterY = 0; filterY < MASK_Y; filterY++){
        for(int filterX = 0; filterX < MASK_X; filterX++){
          int imageX = (x - MASK_X / 2 + filterX + width) % width;
          int imageY = (y - MASK_Y / 2 + filterY + height) % height;
      red += *(image_s + byte_per_pixel * (width * imageY + imageX) +2) * filter[filterY][filterX];
      green += *(image_s + byte_per_pixel * (width * imageY + imageX) +1) * filter[filterY][filterX];
      blue += *(image_s + byte_per_pixel * (width * imageY + imageX) +0) * filter[filterY][filterX];
        }
      }
      
      // Write result through pointer
    *(image_t + byte_per_pixel * (width * y + x) + 2) = min(max(int(factor * red + bias), 0), 255);
    *(image_t + byte_per_pixel * (width * y + x) + 1) = min(max(int(factor * green + bias), 0), 255);
    *(image_t + byte_per_pixel * (width * y + x) + 0) = min(max(int(factor * blue + bias), 0), 255);
    }
  }
}
```
#### NOTE: 
Acessing the image_s's data to the function doing convoluction and write out the result to the iamge_t. 
rgb_raw_data_offset = 54; (avoid the picture shift)

### Part 2: 3X3 Gaussian Blur Filter(systemC)
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

## Results (pictures)
### Original
![](https://raw.githubusercontent.com/patrick047/EE6470/main/hw1/Gaussian_Blur/lena.bmp)
### Part 1
![](https://raw.githubusercontent.com/patrick047/EE6470/main/hw1/Gaussian_Blur/lena_filtered.bmp)
### Part 2
![](https://raw.githubusercontent.com/patrick047/EE6470/main/hw1/GaussianBlurSC/build/lena_filted.bmp)

## Discussions
For this homework, I modified source code of the lab02 sobel_fifo and the sobel_sw from TA provided.
In the systemC type, I debug my code more than hundreds times because I did the convoluction twice that I did not notice its mistake.
After that, I fixed it. 
I didn't use the systemC data type in this homework because I am not really familiar with it.
Thus, I have to work hard on it after submit this homework report. 