#ifndef __UTILS_H
#define __UTILS_H

#include <stdio.h>

#define get_var_name(x) print_var_name(#x)
void print_var_name(const char* x_name);

#define 	pi		3.1415
double abstract(double number);
int round_up_round_down(double num);
int fast_log2(int num);
float radiant2degree(float radiant);
float degree2radiant(float degree);
double square(double x);
double square_root(double n);
#endif /*__UTILS_H*/
