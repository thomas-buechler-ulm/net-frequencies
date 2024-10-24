# NET-FREQUENCIES 

This program that calculates string net-frequencies.

The software is part of the article *Faster Computation of Chinese Frequent Strings and Their Net Frequencies* by Enno Ohlebusch, Thomas Büchler and Jannik Olbrich. (Published in Springer, String Processing and Information Retrieval: https://doi.org/10.1007/978-3-031-72200-4_19)


# Requirements
- C++ compiler
- Installation of libdivsufsort, see: https://github.com/y-256/libdivsufsort
  
Note that you also need to install the 64-bit version of libdivsufsort. For this, pass `-DBUILD_DIVSUFSORT64=ON` to cmake when installing libdivsufsort.


# Installation
Clone this repository.
```
git clone https://github.com/thomas-buechler-ulm/net-frequencies.git
cd net-frequencies
```
Eventually edit the file **PATHS** to set the correct paths to the **lib** and **include** directories that contain libdivsufsort and the **compiler**.

Installation:
```
make nf.x
```

# Test Installation
```
make tiny
```
This command runs our algorithm for the example string "mississippi".


# Manual
```
./nf.x FILE [OPTION]
FILE = input file
OPTION
	-a	Program outputs all string-positions with nf > 0
Default: Program outputs one string positions and nf, for each string with nf > 0
```
The program writes running times to **stderr** and the output to **stdout**. If you like to store the output in a file (**out_file**) use:
```
./nf.x FILE [OPTION] > out_file
```

# Rerun Experiments
### Install Peakergzf/string-net-frequency:
Follow the installation instructions of https://github.com/Peakergzf/string-net-frequency/
(We used commit [545b8e5](https://github.com/Peakergzf/string-net-frequency/commit/545b8e59305c174ca5ba05cca9c3591715a5f2e7))

Replace the following three files, with the ones stored in this repository: net-frequencies/src-Peakergzf): 
- main.cpp (We wrote this, to be able to call Algorithm 2 and Algorithm 3 of the publication)
- experiments.hpp (Only visibility of methods were changed to 'public' )
- suffix_arrays.cpp (We added lines for outputting the nf-values)

After replacing the files, rerun **cmake --build .** 

Edit the file **net-frequencies/PATHS** to set the correct path to the **main.bin** of Peakergzf/string-net-frequency (from Guo et al. https://arxiv.org/html/2404.12701v1)


### Download test data:
```
make get_data
```
### Run experiments:
Eventually edit the file **PATHS** to set the correct paths to the **time** command.

To run the comparison of the output use:
```
make run_compare_dna_nf
```
The outputs will be stored in directory ./out
The **diff** command should output nothing, as the outputs of both programs are equal. 


To run the time and space measurement use:
```
make run
```
The output of the net-frequencies will be redirected the dev/null. Time and space measurements will be written in directory ./out.
