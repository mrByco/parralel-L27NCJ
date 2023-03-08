#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

void printNumber();
void sleep(int arg);
int getRNDNum(int min, int max);
float getRNDFloat(int min, int max);

int main(int argc, char *argv[]){
    if (argc != 3) {
        printf("Error, wrong number of arguments!\n");
        return 1;
    }
    
    srand(time(NULL));

    int min;
    int max;
    if (sscanf (argv[1], "%i", &min) != 1) 
    {
        fprintf(stderr, "error - not an integer");
    }
    if (sscanf (argv[2], "%i", &max) != 1) 
    {
        fprintf(stderr, "error - not an integer");
    }


    printf("float: %f\n", getRNDFloat(min, max));
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

//TODO 2023.03.08.

// n numbers,
// write to file

// Elküldeni a repo linkjét, Gégnynek és Pillernek

// sleep 3. as feladat
// measure time: 
// 7. es feladat
// 9. idő mérése, és grafikon készítése
//      n = 1000
//      m = 2000 stb