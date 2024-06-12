# NET-FREQUENCIES 
This program that calculates string net-frequencies.

# Requirements
- C++ compiler
- Installation of libdivsufsort, see: https://github.com/y-256/libdivsufsort

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
Default: Program outputs one string postions and nf, for each string with nf > 0
```
The program writes running times to **stdcerr** and the output to **stdout**. If you like to store the output in a file (**out_file**) use:
```
./nf.x FILE [OPTION] > out_file
```

# Rerun Experiments
### Install Peakergzf/string-net-frequency:
Follow the installation instructions of https://github.com/Peakergzf/string-net-frequency/
(We used commit [545b8e5](https://github.com/Peakergzf/string-net-frequency/commit/545b8e59305c174ca5ba05cca9c3591715a5f2e7))

Replace the files, with ours (see /src-Peakergzf): 
- main.cpp (We wrote this, to be able to call Algorithm 2 and Algorithm 3 of the publication)
- experiments.hpp (Only visibility of methods were changed to 'public' )
- suffix_arrays.cpp (We added lines for outputting the nf-values)

After replacing the files, rerun **cmake --build .** 

### Download test data:
```
make get_data
```
### Run experiments:
Eventually edit the file **PATHS** to set the correct paths to the **time** and the **main.bin** of ... 

To run the comparison of the output use:
```
make run_compare_dna_nf
```
To run the time and space measurement use:
```
make run
```

