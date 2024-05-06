#ifndef TESTING_H
#define TESTING_H

#include "calculus.h"

enum Function {
	FUNC_INVALID = -1,
	FUNC_1,
	FUNC_2,
	FUNC_3
};

struct Function_Descriptor {
	char *name;
	enum Function func;
};

struct Function_Descriptor functions [] = {
	{"f1", FUNC_1},
	{"f2", FUNC_2},
	{"f3", FUNC_3}
};

int cmp(const void* pv1, const void* pv2)
{
	const struct Function_Descriptor* pop1 = pv1;
	const struct Function_Descriptor* pop2 = pv2;
	
	return strcmp(pop1->name, pop2->name);
} 

int test_root(int argc, char* argv[], int i)
{
	size_t s = sizeof(functions) / sizeof(*functions);
        	qsort(functions, s, sizeof(*functions), cmp);
        	
	double (*f)(double) = NULL;
	double (*f_deriv)(double) = NULL;
	double (*g)(double) = NULL;
	double (*g_deriv)(double) = NULL;
	
	double a = 0;
	double b = 0;
	double eps = 0;
	
	int count_iterations = 0;
	if (i + 5 >= argc)
	{
		printf("You haven't written all arguments, please use -help and try one more time\n");
		return 0;
	}
	
	struct Function_Descriptor* foo1 = bsearch(
		&(struct Function_Descriptor){argv[i + 1], FUNC_INVALID},
		functions, s, sizeof(*functions), cmp);
		
	switch (foo1 ? foo1->func : FUNC_INVALID)
	{
		case FUNC_1:
			f = f1;
			f_deriv = f1_deriv;
			break;
			
		case FUNC_2:
			f = f2;
			f_deriv = f2_deriv;
			break;
			
		case FUNC_3:
			f = f3;
			f_deriv = f3_deriv;
			break;
		
		default:
		case FUNC_INVALID:
			printf("You have written name of function incorrectly, please use -help and try one more time\n");
			return 0;
		
		
	}
	
	struct Function_Descriptor* foo2 = bsearch(
		&(struct Function_Descriptor){argv[i + 2], FUNC_INVALID},
		functions, s, sizeof(*functions), cmp);
	
	switch (foo2 ? foo2->func : FUNC_INVALID)
	{
		case FUNC_1:
			g = f1;
			g_deriv = f1_deriv;
			break;
			
		case FUNC_2:
			g = f2;
			g_deriv = f2_deriv;
			break;
			
		case FUNC_3:
			g = f3;
			g_deriv = f3_deriv;
			break;
		
		default:
		case FUNC_INVALID:
			printf("You have written name of function incorrectly, please use -help and try one more time\n");
			return 0;
		
		
	}
	
	if (f == g)
	{
		printf("You have written two same functions, if you struggle, read help and try one more time\n");
		return 0;
	}
	
	char *correct_a;
	char *correct_b;
	a = strtod(argv[i + 3], &correct_a);
	b = strtod(argv[i + 4], &correct_b);
	
	if (*correct_a != 0 || * correct_b != 0)
	{
		printf("Borders should be numbers, please try again one more time\n");
		return 0;
	}
	
	char *correct_eps;
	eps = strtod(argv[i + 5], &correct_eps);
	if (*correct_eps != 0)
	{
		printf("Eps should be number, please try again one more time\n");
		return 0;
	}
	
	double x_intersection = root_tangent(f, g, f_deriv, g_deriv, a, b, eps, &count_iterations);
	printf("Your functions %s, %s intersect at point %lf, which was counted by %d steps\n\n", argv[i + 1], argv[i + 2], x_intersection, count_iterations);
	
	return 1;
}

int test_integral(int argc, char* argv[], int i)
{
	size_t s = sizeof(functions) / sizeof(*functions);
        	qsort(functions, s, sizeof(*functions), cmp);
        	
	double (*f)(double) = NULL;
	
	double a = 0;
	double b = 0;
	double eps = 0;
	
	if (i + 4 >= argc)
	{
		printf("You haven't written all arguments, please use -help and try one more time\n");
		return 0;
	}
	
	struct Function_Descriptor* foo1 = bsearch(
		&(struct Function_Descriptor){argv[i + 1], FUNC_INVALID},
		functions, s, sizeof(*functions), cmp);
		
	switch (foo1 ? foo1->func : FUNC_INVALID)
	{
		case FUNC_1:
			f = f1;
			break;
			
		case FUNC_2:
			f = f2;
			break;
			
		case FUNC_3:
			f = f3;
			break;
		
		default:
		case FUNC_INVALID:
			printf("You have written name of function incorrectly, please use -help and try one more time\n");
			return 0;
		
		
	}
	
	char *correct_a;
	char *correct_b;
	a = strtod(argv[i + 2], &correct_a);
	b = strtod(argv[i + 3], &correct_b);
	
	if (*correct_a != 0 || * correct_b != 0)
	{
		printf("Borders should be numbers, please try again one more time\n");
		return 0;
	}
	
	char *correct_eps;
	eps = strtod(argv[i + 4], &correct_eps);
	if (*correct_eps != 0)
	{
		printf("Eps should be number, please try again one more time\n");
		return 0;
	}
	
	double area = integral(f, a, b, eps);
	printf("Your functions %s area on [%lf, %lf] is %lf\n\n", argv[i + 1], a, b, area);
	
	return 1;
}


#endif // TESTING_H

