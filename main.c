#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <search.h>

#include "help.h"
#include "functions.h"
#include "testing.h"
#include "calculus.h"


int main(int argc, char* argv[])
{
	for (int i = 0; i < argc; ++i)
    {
        if (strcmp(argv[i], "-help") == 0)
        {
            help();
            return 0;
        }
        
        if (strcmp(argv[i], "-tr") == 0)
        {
        	if (test_root(argc, argv, i) == 0)
        		return 0;
        }
        
        if (strcmp(argv[i], "-ti") == 0)
        {
        	if (test_integral(argc, argv, i) == 0)
        		return 0;
        }
    }

    double a = -2;
    double b = 2;
    double eps = 0.001;
    int cnt_roots = 0;

    double rt1 = root_tangent(f1, f2, f1_deriv, f2_deriv, a, b, eps / 10, &cnt_roots); // calculating first intersection
    
    // changing values for the next function
    a = -2;
    b = -1.5;
    double rt2 = root_tangent(f1, f3, f1_deriv, f3_deriv, a, b, eps / 10, &cnt_roots); // calculating second intersection
    
    // changing values for the next function again
    a = -1;
    b = 0;
    double rt3 = root_tangent(f2, f3, f2_deriv, f3_deriv, a, b, eps / 10, &cnt_roots); // calculating third intersection

    for (int i = 0; i < argc; ++i)
    {
        if (strcmp(argv[i], "-r") == 0)
        {
            printf("Curves 0.35x^2 - 0.95x + 2.7 and 3x + 1 intersect at point %lf\n", rt1);
            printf("Curves 0.35x^2 - 0.95x + 2.7 and 1 / (x + 2) intersect at point %lf\n", rt2);
            printf("Curves 1 / (x + 2) and 3x + 1 intersect at point %lf\n", rt3);
        }
        
        if (strcmp(argv[i], "-i") == 0)
        {
        	printf("The number of iterations needed to calculate all intersections is %d\n", cnt_roots);
        }
    }

    double integr1 = dabs(integral(f1, rt1, rt2, eps / 10));  // finging integrals on segments
    double integr2 = dabs(integral(f2, rt1, rt3, eps / 10));
    double integr3 = dabs(integral(f3, rt2, rt3, eps / 10));

    double res = integr1 - integr2 - integr3;  // calculating final result

    printf("\nThe result (area between intersections) is %.10lf\n", res);
    return 0;
}

