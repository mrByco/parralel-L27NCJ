#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

void printNumber();
void sleep(int arg);
int getRNDNum(int min, int max);
float getRNDFloat(float min, float max);

int main(int args, char *argv[]){
    srand(time(NULL));
    for (int i = 0; i < 500; i++){
        printf("float: %f\n", getRNDFloat(2.f, 5.f));
        sleep(1);
    }
    return 0;
}

void printNumber(int num){
    printf("N = %d\n", num);
}

int getRNDNum(int min, int max){
    return (rand() % (max - min)) + min;
}

float getRNDFloat(float min, float max){
    return ((float)rand() / (RAND_MAX) * (max - min) + min);
}