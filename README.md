# scientific-cpp
Slides and examples for a scientific c++ workshop using c++11 and c++14 features.

## Outline
- Basic introduction to types, functions and classes
- Leveraging the standard template library (stl)
- Using numerical algebra libraries
- Compiler flags and optimization

## Schedule

### Hour 1
- Compilers and tools
- Type system crash course
- Value, reference, pointer and const semantics
- Functions

### Hour 2
- Standard algorithms (stl)
- The future ranges

### Hour 3
- Linear algebra (dense and sparse matrices)
- Go fast time!  Compiler optimizations

## Preparation

You will need to install some variant of linux in a virtual machine (VM).  These instructions are written assuming you are using Fedora Workstation Edition.  If you are familiar with other variants please use that and find the equivalent packages on your system.

*Only if you are don't have a Linux system handy*
Firstly, download the live operating system image (.iso) from https://getfedora.org/en/workstation/ (approximately 1.3GiB) and install in OS in the virtual machine.  Make sure you set yourself as the administrator for the virtual OS.

Once you are logged into Fedora on the VM, then open up a terminal from the top left hand side (Activities->Terminal) and type:
```
<machine_name>$ sudo dnf install -y clang gcc-c++ cmake git
```
Or in a Ubuntu OS
```
<machine_name>$ sudo apt-get install clang git cmake
```
and provide your user password when prompted to install git, cmake and the clang compiler.  Once we have this working we need to pull down the slides and examples codes.  In the terminal type
```
<machine_name>$ cd
```
to get back to the user home directory and pull down the sources from github
```
<machine_name>$ git clone --depth=1 https://github.com/dbeurle/scientific-cpp.git
```
Now go to the ```slides/``` folder and open the slides.htm file in your favourite web browser.  The code examples are under ```examples/``` folder.

Let's download Eigen3 by
```
wget http://bitbucket.org/eigen/eigen/get/3.3.4.zip
```
Unzip and open the folder.  Create a new folder inside the eigen3 directory called ```build``` and go into this newly created folder.  Then in the terminal type
```
<machine_name>$ cmake .. 
<machine_name>$ sudo make install
```
To install the header only library.
