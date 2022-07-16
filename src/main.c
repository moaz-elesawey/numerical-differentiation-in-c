#include <stdio.h>
#include <stdlib.h>
#include "function.h"

dtype * linspace(double, double, int);
dtype * derivative(dtype (*)(dtype), dtype *, int, double, int);
dtype * apply_func(dtype (*)(dtype), dtype *, int);

double fact(double);
double nCr(double, double);

void print_mat_1d(dtype *, int);
void write_data(dtype *, dtype *, dtype *, int);

int main(int argc, char **argv) {

    double start = -2*M_PI, end = 2*M_PI, size = 1000;
    double h = 1e-6;

    int order = 1;

    printf("input the xstart, xend, and diff order seperated by space \n");
    scanf("%lf", &start);
    scanf("%lf", &end);
    scanf("%d", &order);

    dtype * x_data = linspace(start, end, size);
    dtype * y_data = apply_func(&f, x_data, size);
    dtype * dfdx = derivative(&f, x_data, size, h, order);

    write_data(x_data, y_data, dfdx, size);

    free(x_data);
    free(y_data);
    free(dfdx);

    return EXIT_SUCCESS;
}

dtype * linspace(double start, double end, int size) {
    /* create an array of shape (size) */

    double inc = (end - start) / (double) size;

    dtype * array = (dtype *) calloc(size, sizeof(dtype));
    array[0] = start;

    for(int i=1; i<size; i++) {
        array[i] = array[i-1] + inc;
    }

    return array;
}

dtype * derivative(dtype (*f)(dtype x), dtype * x_data, int size, double h, int n) {
    /*find the derivative of func expressed in arr*/
    /*h should be very small value like 1e-6*/
    /*n is the order of derivative*/

    dtype * dfndx = (dtype *) calloc(size, sizeof(dtype));

    for(int i=0; i<size; i++) {
        dfndx[i] = 0.0;
        for(int k=0; k<=n; k++) {
            dfndx[i] +=  pow(-1, k) * nCr(n, k) * ( f(x_data[i] + h*(n-k)) / pow(h, n) );
        }
    }

    return dfndx;
}


double fact(double n) {
    double ans = n;

    if(n < 1) { return 1.0; }

    for(double i=n-1; i>1; i--)
        ans *= i;

    return ans;
}

double nCr(double n, double k) {
    /* find the combination of (n of k) */
    return fact(n) / ( fact(k) * fact(n-k) );
}

dtype * apply_func(dtype (*f)(dtype), dtype * x_data, int size) {
    
    dtype * y_data = (dtype *) calloc(size, sizeof(dtype));

    for(int i=0; i<size; i++) {
        y_data[i] = f(x_data[i]);
    }

    return y_data;
}

void print_mat_1d(dtype * array, int size){
    if(size < 5) {
        for(int i=0; i<size; i++){
            printf("%6.3f ", array[i]);
        }
        printf("\n"); return ;
    }
    else {
        for(int i=0; i<5; i++){
            printf("%6.3f ", array[i]);
        }
        printf("... ");
        for(int i=size-5; i<size; i++){
            printf("%6.3f ", array[i]);
        }
        printf("\n"); return ;
    }
}

void write_data(dtype * x_data, dtype * y_data, dtype * dfdx, int size) {
    FILE *fptr;

    fptr = fopen("out/data.dat", "w");

    fprintf(fptr, "#%7s %9s %10s\n", "x", "f(x)", "f'(x)");
    for(int i=0; i<size; i++) {
        fprintf(fptr, "%-10.5f %-10.5f %-10.5f\n", x_data[i], y_data[i], dfdx[i]);
    }
    printf("done writing data...\n");

    fclose(fptr);
}


