# EE6470 Homework 5
### Cross-compile Gaussian Blur to RISC-V VP platform
student:趙庭慶 number:109061616
## Implemation
### Platform
#### PATH: riscv-vp/vp/src/platform
#### step 1:
I build a new folder(basic-hw6) in platform folder and modified (1)GaussianBlurFilter.h (2)main.cpp (3)CMakeLists here.
#### step 2:
Go to the PATH: riscv-vp/vp/build and do (1)cmake .. (2)make install, now the platform have been build.
### Structure

### Result:
#### Original
![](https://github.com/patrick047/EE6470/blob/main/hw5/hw5_data/lena_std_short.bmp)
#### After
![](https://github.com/patrick047/EE6470/blob/main/hw5/hw5_data/out.bmp)

## Conclusion
在這次的作業，對 Gaussian Blur Filter 做兩種不同方式 input 形式的模擬。
1. splitted 為 RBG data 利用 3 個 8-bit 的 p2p channel 進行傳送， 
2. non splitted mode 為 RBG data 利用 1 個 24-bit 的 p2p channel 進行傳送。
根據模擬結果得知， splitted mode 在 Area 和 Run time 都比 non splitted mode 來的差，而 DPA 相對於 BASIC 對 Run time 的表現沒有影響，但是 Area 的表現有比較好。



