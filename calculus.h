#ifndef CALCULUS_H
#define CALCULUS_H

double dabs(double a)
{
    return (a > 0) ? a : -a;
}

double h(double (*f)(double), double (*g)(double), double arg)
{
    return (f(arg) - g(arg));
}

double root_tangent(double (*f)(double), double (*g)(double), double (*f_deriv)(double), double (*g_deriv)(double), double a, double b, double eps1, int* cnt)
{
    // firstly we will check what sign of derivitive of function is
    if (isinf(h(f, g, a)) ||  isinf(h(f_deriv, g_deriv, a)))   // in case we have some undefined points on the ends of the section
        a += dabs(a) / 1000;
    if (isinf(h(f, g, b)) || isinf(h(f_deriv, g_deriv, b)))
        b -= dabs(b) / 1000;


    double deriv = h(f_deriv, g_deriv, a);
    double chord = (h(f, g, a) + h(f, g, b)) / 2;
    double middle = h(f, g, (a + b) / 2);
    int convex = 0;
    int sign = 1;
    double x_iter = a;

    if (chord - middle <= 0)  // checking convexity
    {
        convex = 1;
    }
    else
    {
        convex = -1;
    }


    if (deriv == 0)
    {
        printf("Choose another interval");
        return -1;
    }

    if (deriv * convex < 0) // in cases grow and convex down or fall and convex up
    {
        sign = -1;
        x_iter = b;
    }
    else
    {
        sign = 1;
        x_iter = a;
    }

    double delta = 0;
    *cnt += 1;               // the first point of calculations also goes in count
    
    while ((h(f, g, x_iter) * h(f, g, x_iter + eps1 * sign)) > 0)   // calculating x_iter
    {
        delta = h(f, g, x_iter) / h(f_deriv, g_deriv, x_iter);
        x_iter = x_iter - delta;
        *cnt += 1;
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
    double coefficient = 0.15;           // coeffitient for counting simpson sum
    unsigned long long n = 100;
    double I_n = simpson_sum(f, a, b, n);
    n *= 2;
    double I_2n = simpson_sum(f, a, b, n);

    //int cnt = 1;
    while (dabs(I_n - I_2n) * coefficient >= eps2)
    {
        I_n = I_2n;
        n *= 2;
        I_2n = simpson_sum(f, a, b, n);
        //cnt++;
        //printf("Counted sum %d with number of steps %d\n", cnt, n);
    }

    return I_n;
}

#endif // CALCULUS_H
