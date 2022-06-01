gcc -c pbPlots.c -std=c99 -O3 -march=native
gcc -c supportLib.c -std=c99 -O3 -march=native
gcc -c main.c -std=c99 -O3 -march=native
gcc -c ipcv_utils.c -std=c99 -O3 -march=native
gcc main.o ipcv_utils.o pbPlots.o supportLib.o -lm -o main
strip main
./main

