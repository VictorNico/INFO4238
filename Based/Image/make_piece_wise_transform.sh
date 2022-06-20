gcc -c image.c -std=c99 -O3 -march=native
gcc -c ../File/file.c -std=c99 -O3 -march=native
gcc -c ../Matrix/matrix.c -std=c99 -O3 -march=native
gcc -c ../../Libs/Plot/pbPlots.c -std=c99 -O3 -march=native
gcc -c ../../Libs/Plot/supportLib.c -std=c99 -O3 -march=native
gcc -c test.c -std=c99 -O3 -march=native
gcc test.o image.o file.o pbPlots.o supportLib.o matrix.o -lm -o test
strip test
./test

