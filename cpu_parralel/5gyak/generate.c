#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 10 


double array_product(double arr[], int left, int right) {
    if (left == right) {
        return arr[left];
    }
    int mid = (left + right) / 2;
    double left_prod = array_product(arr, left, mid);
    double right_prod = array_product(arr, mid+1, right);
    return left_prod * right_prod; 
}

int main() {
    double arr[N];
    srand(time(NULL)); 
    for (int i = 0; i < N; i++) {
        arr[i] = (double)rand() / RAND_MAX * 10.0; 
    }
    double product = array_product(arr, 0, N-1); 
    printf("The product of he array elements: %.2f\n", product);
    return 0;
}