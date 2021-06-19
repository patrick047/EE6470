# EE6470 Homework 7
### Data Partitioning of the Gaussian Blur Processing
student:趙庭慶 number:109061616
## Implemation
### Platform
#### PATH: riscv-vp/vp/src/platform
#### step 1:
I build a new folder(tiny32-hw7) in platform folder and modified (1)GaussianBlurFilter.h (2)main.cpp (3)CMakeLists here.
#### step 2:
Go to the PATH: riscv-vp/vp/build and do (1)cmake .. (2)make install, now the platform have been build.
### Structure

### Result:
#### single core(hw6)
![](https://github.com/patrick047/EE6470/blob/main/hw6/hw6.PNG)
#### multiple core(hw7)
![](https://github.com/patrick047/EE6470/blob/main/hw7/hw7_1.PNG)
![](https://github.com/patrick047/EE6470/blob/main/hw7/hw7_2.PNG)
## Conclusion
在這次的作業，我們將systemc 模塊移植到riscv-vp上，對 Gaussian Blur Filter 在riscv上模擬。RISCV提供了一個完整的平台，包含了MEMORY,I/O,CPU，能夠輕鬆的在SOFTWARE跟HARDWARE上做SIMULATION。



