#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

void printNumber();
int getRNDNum(int min, int max);

int main(int argc, char *argv[]){

    srand(time(NULL));
    while (TRUE)
    {
        int numA = getRNDNum(1, 10);
        int numB = getRNDNum(1, 10);

        printf("Calculate: %d x %d = ", numA, numB);
        int userResult;
        int startTime = clock();
        scanf("%d", &userResult);
        int endTime = clock();

        if (userResult == numA * numB){
            printf("Good job!\n");
        }
        else {
            printf("Next time bro!\n");
        }
        int time;
        printf("U're time is: %dms\n\n", endTime - startTime);
    }
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