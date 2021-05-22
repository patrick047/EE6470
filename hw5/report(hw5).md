# EE6470 Homework 5
### High level synthesis of Gaussian Blur
student:趙庭慶 number:109061616
## Implemation
### non-splited
### Result:
#### Original
![](https://github.com/patrick047/EE6470/blob/main/hw5/hw5_data/lena_std_short.bmp)
#### After
![](https://github.com/patrick047/EE6470/blob/main/hw5/hw5_data/out.bmp)
#### Simulated time
#### BASIC
![](https://github.com/patrick047/EE6470/blob/main/hw5/hw5_data/hw5_simbasic1.PNG)
#### DPA
![](https://github.com/patrick047/EE6470/blob/main/hw5/hw5_data/hw5_simdpa1.PNG)
#### Area
#### BASIC
![](https://github.com/patrick047/EE6470/blob/main/hw5/hw5_data/hw5_areabasic1.PNG)
#### DPA
![](https://github.com/patrick047/EE6470/blob/main/hw5/hw5_data/hw5_areadpa1.PNG)
#### RTL Summary
#### BASIC
![](https://github.com/patrick047/EE6470/blob/main/hw5/RTL-SUMMARY/nonspiltted_BASIC.PNG)
#### DPA
![](https://github.com/patrick047/EE6470/blob/main/hw5/RTL-SUMMARY/nonspiltted_DPA.PNG)
-------------------------------------------------------------------------------
### splited
### Result:
#### Original
![](https://github.com/patrick047/EE6470/blob/main/hw5/hw5_data/lena_std_short.bmp)
#### After
![](https://github.com/patrick047/EE6470/blob/main/hw5/hw5_data/out.bmp)
#### Simulated time
#### BASIC
![](https://github.com/patrick047/EE6470/blob/main/hw5/hw5_data/hw5_simbasic2.PNG)
#### DPA
![](https://github.com/patrick047/EE6470/blob/main/hw5/hw5_data/hw5_simdpa2.PNG)
#### Area
#### BASIC
![](https://github.com/patrick047/EE6470/blob/main/hw5/hw5_data/hw5_areabasic2.PNG)
#### DPA
![](https://github.com/patrick047/EE6470/blob/main/hw5/hw5_data/hw5_areadpa2.PNG)
#### RTL Summary
#### BASIC
![](https://github.com/patrick047/EE6470/blob/main/hw5/RTL-SUMMARY/spiltted_BASIC.PNG)
#### DPA
![](https://github.com/patrick047/EE6470/blob/main/hw5/RTL-SUMMARY/spiltted_DPA.PNG)
## Conclusion
在這次的作業，對 Gaussian Blur Filter 做兩種不同方式 input 形式的模擬。
1. splitted 為 RBG data 利用 3 個 8-bit 的 p2p channel 進行傳送， 
2. non splitted mode 為 RBG data 利用 1 個 24-bit 的 p2p channel 進行傳送。
根據模擬結果得知， splitted mode 在 Area 和 Run time 都比 non splitted mode 來的差，而 DPA 相對於 BASIC 對 Run time 的表現沒有影響，但是 Area 的表現有比較好。
### Problem
在跑 sim_V 的時候，發生了部分datatype 無法進行 HLS ，利用 double 建立的就無法進行 HLS，up 因此改成用uint。


