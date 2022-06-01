gcc -c file.c -std=c99 -O3 -march=native
gcc -c test.c -std=c99 -O3 -march=native
gcc test.o file.o -lm -o test
strip test
./test

