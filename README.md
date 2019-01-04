# streamtool
This is a test project

#################################

Release Notes:
1. init structure
2. init Makefile base
3. support compile .o .so (c/cpp) and linkage
4. support compile .a and linkage
5. 

#################################

Readme:
1. Under Apache-V2 lisence
2. C code call CPP code use lib/c2xlayer/ patten
3. Dynamic libxxx.so, should use "make install" after "make", unistall use "make unistall"
4. Dynamic libxxx.so makefile refer to ./lib/cmath/Makefile
5. Static libxxx.a makefile refer to ./lib/of/Makefile
6. 

#################################

Directorys:
1. 3rdparty:      third-party IPs except controller inside core
2. arch:          controller IP inside core
3. configs:       simulator configurations
4. Documentation: all simulator related documents
5. dts:           device tree 
6. include:       common definitions and user interface APIs
7. kernel:        THE MAIN IMPLEMENTATIONS
8. lib:           general dynamic.so and static.a lib functions
9. scripts:       project scripts
10. test:         test data and test case
11. tools:        all useful tools
12. ui:           simulator ui interface

