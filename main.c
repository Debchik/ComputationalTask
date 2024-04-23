#include <stdio.h>
#include <stdlib.h>

double dabs(double a)
{
    return (a > 0) ? a : -a;
}

double h(double (*f)(double), double (*g)(double), double arg)
{
    return (f(arg) - g(arg));
}

double root_chord(double (*f)(double), double (*g)(double), double a, double b, double eps1)
{
    double deriv = h(f, g, b) - h(f, g, a);
    double chord = (h(f, g, a) + h(f, g, b)) / 2;
    double middle = h(f, g, (a + b) / 2);
    int convex_down = chord >= middle;
    int sign = 1;
    double mov_to_value = a;
    double x_iter = a;

    if ((deriv >= 0 && convex_down) || (deriv <= 0 && !convex_down)) // in case we have growing function
    {
        sign = 1;
        mov_to_value = b;
        x_iter = a;
    }
    else
    {
        sign = -1;
        mov_to_value = a;
        x_iter = b;
    }

    while ((h(f, g, x_iter) / h(f, g, x_iter + eps1 * sign)) > 0)
    {
        double delta = (h(f, g, x_iter) * (mov_to_value - x_iter)) / (h(f, g, mov_to_value) - h(f, g, x_iter));
        x_iter = x_iter - delta;
    }

    return x_iter;
}

double root_tangent(double (*f)(double), double (*g)(double), double (*f_deriv)(double), double (*g_deriv)(double), double a, double b, double eps1)
{
    // firstly we will check what sign of derivitive of function is

    double deriv = h(f_deriv, g_deriv, a);
    double chord = (h(f, g, a) + h(f, g, b)) / 2;
    double middle = h(f, g, (a + b) / 2);
    int convex_down = 0;
    int sign = 1;
    double x_iter = a;

    if (chord > middle)
    {
        convex_down = 1;
    }
    else if (chord < middle)
    {
        convex_down = 0;
    }
    else                  // checking on linear function
    {
        convex_down = -1;
    }

    if (deriv == 0)
    {
        printf("Choose another interval");
        return -1;
    }

    if ((deriv > 0 && convex_down == 1) || (deriv < 0 && (convex_down == 0))) // in case we have growing function
    {
        sign = -1;
        x_iter = b;
    }
    else if (convex_down != -1)
    {
        sign = 1;
        x_iter = a;
    }
    else if (deriv < 0)
    {
        sign = -1;
        x_iter = b;
    }
    else
    {
        sign = 1;
        x_iter = a;
    }

    while ((h(f, g, x_iter) / h(f, g, x_iter + eps1 * sign)) > 0)   // calculating x_n
    {
        double delta = h(f, g, x_iter) / h(f_deriv, g_deriv, x_iter);
        x_iter = x_iter - delta;
    }

    return x_iter;
}

double simpson_sum(double (*f)(double), double a, double b, int n)
{
    double delta = (double)(b - a) / n;
    double sum_1 = 0.0;
    double cur_x = a;

    for (int i = 0; i < (n / 2) - 1; ++i)
    {
        cur_x = a + 2 * i * delta;
        sum_1 += f(cur_x);
    }
    sum_1 *= 2;

    double sum_2 = 0.0;
    for (int i = 0; i < (n / 2); ++i)
    {
        cur_x = a + (2 * i - 1) * delta;
        sum_2 += f(cur_x);
    }
    sum_2 *= 4;

    double simpson_sum = f(a) + f(b);
    simpson_sum += sum_1 + sum_2;
    simpson_sum *= delta;
    simpson_sum /= (double)(3);

    return simpson_sum;
}

double integral(double (*f)(double), double a, double b, double eps2)
{
    int n = 100;
    double I_n = simpson_sum(f, a, b, n);
    n *= 2;
    double I_2n = simpson_sum(f, a, b, n);

    while (dabs(I_n - I_2n) >= eps2)
    {
        I_n = I_2n;
        n *= 2;
        I_2n = simpson_sum(f, a, b, n);
    }

    return I_n;
}

double func1(double x)
{
    return -2 * x + 5;
}

double func1_deriv(double x)
{
    return -2;
}

double func2(double x)
{
    return 0.5 * x;
}

double func2_deriv(double x)
{
    return 0.5;
}

double func3(double x)
{
    return  -x * x + 4 * x;
}

double func3_deriv(double x)
{
    return 2 * x + 4;
}

int main(void)
{
    double a = 0;
    double b = 3;
    double eps = 0.001;

    double rt1 = root_tangent(func1, func2, func1_deriv, func2_deriv, a, b, eps / 6);
    double rt2 = root_tangent(func1, func3, func1_deriv, func3_deriv, a, b, eps / 6);
    double rt3 = root_tangent(func2, func3, func2_deriv, func3_deriv, a, b, eps / 6);

    printf("%lf, %lf, %lf \n", rt1, rt2, rt3);

    double integr1 = dabs(integral(func1, rt1, rt2, eps / 6));
    double integr2 = dabs(integral(func2, rt1, rt3, eps / 6));
    double integr3 = dabs(integral(func3, rt2, rt3, eps / 6));

    double res = integr1 + integr3 - integr2;

    printf("%lf, %lf, %lf \n %lf", integr1, integr2, integr3, res);
    return 0;
}
