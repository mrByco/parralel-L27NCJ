#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <windows.h>

void printNumber();
int getRNDNum(int min, int max);
int isPrime();
int countPrimesInRange(int a, int b);

int main(int argc, char *argv[]){

    srand(time(NULL));
    int duration = 0;
    int getPrimesUntil = 10;
    FILE* fOut = fopen("results.txt", "w+");

    while (duration < 30000){
        int startT = clock();
        int primesFound = countPrimesInRange(1, getPrimesUntil);
        duration = clock() - startT;
        getPrimesUntil = floor(getPrimesUntil * 1.5);
        printf("%dms: range(1, %d); Primes found: %d\n", duration, getPrimesUntil, primesFound);
        fprintf(fOut, "%d, %d, %d\n", duration, getPrimesUntil, primesFound);
    }
    fclose(fOut);

    return 0;
}

int countPrimesInRange(int start, int end){
    int primes = 0;
    for (int i = start; i < end; i++){
        if (isPrime(i)){
            primes++;
        }
    }
    return primes;
}

int isPrime(int n){
    for (int i = 2; i < n; i++){
        float div = (float)n/(float)i;
        if (floor(div) == div)
        {
            return FALSE;
        }
    }
    return TRUE;
}