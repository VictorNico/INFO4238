gcc -c type.c -std=c99 -O3 -march=native
gcc -c test.c -std=c99 -O3 -march=native
gcc test.o type.o -lm -o test
strip test
./test

