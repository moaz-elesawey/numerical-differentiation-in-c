#ifndef _FUNCTION_H_
#define _FUNCTION_H_

#include <math.h>

// you can change the type of dtype to be float or long double
typedef double dtype;

/* Here you can define your function and it's parameters,
 * but with some constrains which are:
 *  - the function name should be (f).
 *  - the function only take one parameter which as f(x)
 *  - the function parameter and return value of type (dtype)*/

dtype f(dtype x) {
    dtype y = 0.0;

    /*add your function body here*/
    y = sin(x);

    return y;
}

/*****************************************/
/******** Some Function Examples *********/
/*****************************************/

/* dtype f(dtype x) { return sin(x) ; } */
/* dtype f(dtype x) { return cos(x) ; } */
/* dtype f(dtype x) { return pow(x, 2) * sin(2*x) * exp(-pow(x, 4)) ; } */
/* dtype f(dtype x) { return sin(x)/x ; } */
/* dtype f(dtype x) { return 1.0/(1.0 + exp(-x)) ; } */
/* dtype f(dtype x) { return pow(sin(x), 2) ; } */
/* dtype f(dtype x) { return exp(-pow(x, 2)) ; } */

#endif /*_FUNCTION_H_*/
