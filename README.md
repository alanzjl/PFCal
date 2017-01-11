# PFCal

A power flow calculator based on Newton-Raphson method. Work with PQ, PV and Vt buses.

## Introduction

PFCal is a power flow calculator that supports PQ bus (with P and Q known), PV bus (with P and amplitude U known) and Vt bus (with amplitude and phase angle of generator known). The main goal is to simplify the calculation with guaranteed accuracy. 

Based on Visual Studio MFC, and [Eigen](https://github.com/PX4/eigen).

## Attention
Calculation with Vt buses and PQ buses has been fully tested, but because of our lack of samples, calculation with PV buses has only been tested few times. Also, we found out that sometimes projects with Pv buses will go trapped. 
The Accuracy: within 1e-5.

**Please pay attention to the unit of your input. **

to be continued ......


## Author
Jialiang Zhao, Jiahui Shi

Dec 2016