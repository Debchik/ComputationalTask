#ifndef HELP_H
#define HELP_H

void help()
{
	printf("Usage: Integrate [options] \n Options: \n");
            printf("\t-r \t\t\t\t\t Print points of intersection of functions\n");
            printf("\t-i \t\t\t\t\t Print number of steps completed to find all intersections of functions\n");
            printf("\t-help \t\t\t\t\t Print this message and exit\n");
            printf("\t-tr function_1 function_2 a b eps \t Flag for testing roots of intersections of functions. \n\t\tList of availiable funcitons is in the end of the message. a, b - ends of the section where to find roots, eps - error rate\n");
            printf("\t-ti function_1 a b eps \t Flag for testing finding integrals of function. \n\t\tList of availiable funcitons is in the end of the message. a, b - ends of the section where to find roots, eps - error rate\n");
            printf("\n\n\nAvailiable functions:\n");
            printf("f1 = 0.35x^2 - 0.95x + 2.7\n");
            printf("f2 = 3x + 1\n");
            printf("f3 = 1 / (x + 2)\n");
}
#endif // HELP_H
