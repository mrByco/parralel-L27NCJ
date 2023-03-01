#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

void printNumber();
void sleep(int arg);
int getRNDNum(int min, int max);
float getRNDFloat(int min, int max);

int main(int args, char *argv[]){

    
    srand(time(NULL));
    printf("float: %f\n", getRNDFloat(2.f, 5.f));
    return 0;
}

void printNumber(int num){
    printf("N = %d\n", num);
}

int getRNDNum(int min, int max){
    return (rand() % (max - min)) + min;
}

float getRNDFloat(int min, int max){
    return ((float)rand() / (RAND_MAX) * ((float)max - (float)min) + (float)min);
}