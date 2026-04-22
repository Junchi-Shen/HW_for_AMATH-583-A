Compilation instructions for librefBLAS.so:

1. Compile the source files into position-independent object code (-fPIC):
g++ -std=c++17 -c -fPIC ref_daxpy.cpp -o ref_daxpy.o
g++ -std=c++17 -c -fPIC ref_dgemv.cpp -o ref_dgemv.o
g++ -std=c++17 -c -fPIC ref_dgemm.cpp -o ref_dgemm.o

2. Create the shared object library:
g++ -shared -o librefBLAS.so ref_daxpy.o ref_dgemv.o ref_dgemm.o
