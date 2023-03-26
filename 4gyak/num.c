#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int n, i, even_count = 0, odd_count = 0, zero_count = 0, pos_count = 0, neg_count = 0, abs_count = 0, interval_count = 0;
    float* arr;
    int interval_min, interval_max;
    
    srand(time(0)); 
    
    printf("Please give how many elements you want to be the array length: ");
    scanf("%d", &n);
    interval_min=0;
    interval_max=5;
    
    arr = (float*) malloc(n * sizeof(float)); 
    float lower_bound = -4.0;
    float upper_bound = 5.0;
    float range = upper_bound - lower_bound;
    
    for (i = 0; i < n; i++) {
        float random_num = (float) rand() / RAND_MAX;
        float scaled_num = (random_num * range) + lower_bound;
        arr[i] = scaled_num; 
    }
    
  
    for (i = 0; i < n; i++) {

        if ((int)arr[i] % 2 == 0) {
            even_count++;
        } else {
            odd_count++;
        }
        
        
        if (arr[i] == 0) {
            zero_count++;
        }
        
        
        if (arr[i] > 0) {
            pos_count++;
        } else if (arr[i] < 0) {
            neg_count++;
        }
        
        
        if (arr[i] < -1 || arr[i] > 1) {
            abs_count++;
        }
        
        if (arr[i] >= interval_min && arr[i] <= interval_max) {
            interval_count++;
        }
    }

    printf("The elements of the array are the followings:");
    for(int k=0; k<n;k++){
        printf("%.2lf\n" ,arr[k]);
    }
    
    printf("Even numbers: %d\n", even_count);
    printf("Odd numbers: %d\n", odd_count);
    printf("null numbers: %d\n", zero_count);
    printf("Positive numbers: %d\n", pos_count);
    printf("Negative numbers: %d\n", neg_count);
    printf("Lower than one absolute value numbers %d\n", abs_count);
    printf("Numbers in the intervall %d\n", interval_count);
    
    free(arr); 
    return 0;
    }