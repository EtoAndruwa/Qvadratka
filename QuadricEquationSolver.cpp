#include <stdio.h>
#include <math.h>

#define EPS 1e-7
#define INF "INF"
#define NO_ROOTS "NO_ROOTS"

/*struct MY_TEST_STRUCT
    {
        double a;
        double b;
        double c;
        double x1;
        double x2;
        double x_x1;
        double y_x1;
        double x_x2;
        double y_x1;
    };*/

void PRINT_WELCOME(); // Печатает welcome
void PRINT_EQUATION(double a, double b, double c); //Печатает уравнение с коэффициентами A,B и C
int INPUT_ABC(double* a, double* b, double* c); //Ввод A, B и С
void PRINT_ABC(double a, double b, double c); //Печатает A, B и С
void CALC_DISCR(double a, double b, double c, double* discr); //Считает дискриминант
void CALC_NUM_OF_ROOTS(double Discr, int* num_of_roots); //Возвращает кол-во корней по дискриминанту
void CALC_ROOTS_0_OR_POS(double a, double b, double discr, double* x1, double* x2); //Cчитает корин при D>=0
void CALC_ROOTS_NEG(double a, double b, double discr, double* x_x1, double* y_x1, double* x_x2, double* y_x2);  //Cчитает корни при D<0
int CASE_LOGIC(double a, double b, double c);  //Возвращает номер кейса
void PRINT_ROOTS_0_OR_POS(double* x1, double* x2); //Печатает корни при D>=0
void PRINT_ROOTS_NEG(double* x_x1, double* y_x1, double* x_x2, double* y_x2); //Печатает корни при D<0
void EQUATION_SOLVER_LOGIC(int case_num, double a, double b, double c, double* discr, double* x1, double* x2, double* x_x1, double* y_x1, double* x_x2, double* y_x2, int* Num_of_roots); //Отвечает за логику, по кейсам вызывает другие функции для решения уравнения
void PRINT_LINEAR(double x1); //Выводит один корень линейного уравнения
void SOLVE_LINEAR(double c, double b, double* x1); //Решает линейное уравнение
void DISCR_LOGIC(double a, double b, double c, double* discr, double* x1, double* x2, double* x_x1, double* y_x1, double* x_x2, double* y_x2); //Вызывает функции решения уравнения взависимости от значение дискриминанта квадр. уравнения

int main ()
    {
        int Num_of_roots = 0;
        double A = 0;
        double B = 0;
        double C = 0;
        double Discr = 0;
        double x1 = 0.0;
        double x2 = 0.0;
        double x_x1 = 0.0;
        double y_x1 = 0.0;
        double x_x2 = 0.0;
        double y_x2 = 0.0;
        int Eq_case = 0;

        PRINT_WELCOME();
        printf("Enter a, b and c: ");

        INPUT_ABC(&A, &B, &C);

        PRINT_ABC(A, B, C);
        PRINT_EQUATION(A, B, C);

        //MY_TEST_FUNCTION();

        Eq_case = CASE_LOGIC(A, B, C);
        //printf("Case number: %d\n", Eq_case);
        EQUATION_SOLVER_LOGIC(Eq_case, A, B, C, &Discr, &x1, &x2, &x_x1, &y_x1, &x_x2, &y_x2, &Num_of_roots);

        return 0;
    }



void PRINT_WELCOME() // Печатает welcome
    {
        printf("##########################\n");
        printf("######Done by Andrey######\n");
        printf("##########################\n\n");
    }

void PRINT_EQUATION(double a, double b, double c) //Печатает уравнение с коэффициентами A,B и C
    {
        printf("Your equation is: (%.2lf)*x^2+(%.2lf)*x+(%.2lf)=0\n\n", a, b, c);
    }

int INPUT_ABC(double* a, double* b, double* c) //Ввод A, B и С
    {
        if(scanf("%lf", a) != 1)
            {
                printf("ERROR: invalid value for A. Sorry, enter number, please!\n");
                return 0;
            }
        if(scanf("%lf", b) != 1)
            {
                printf("ERROR: invalid value for B. Sorry, enter number, please!\n");
                return 0;
            }
        if(scanf("%lf", c) != 1)
            {
                printf("ERROR: invalid value for C. Sorry, enter number, please!\n");
                return 0;
            }
    }

void PRINT_ABC(double a, double b, double c) //Печатает A, B и С
    {
        printf("A:%.2lf\n", a);
        printf("B:%.2lf\n", b);
        printf("C:%.2lf\n\n", c);
    }

void CALC_DISCR(double a, double b, double c, double* discr) //Считает дискриминант
    {
        if(fabs(c) <= EPS)
            {
                *discr = (b * b);
            }
        else
            {
                *discr = (b * b) - (4 * a * c);
            }
        //printf("DISCR: %.3lf\n", *discr);
    }

void DISCR_LOGIC(double a, double b, double c, double* discr, double* x1, double* x2, double* x_x1, double* y_x1, double* x_x2, double* y_x2)
    {
        if((fabs(*discr) <= EPS) && (fabs(b) <= EPS) && (fabs(c) <= EPS) && (fabs(a) > EPS))
            {
                *x1 = 0;
                printf("Root: %.3lf", *x1);
            }
        if(((fabs(*discr) <= EPS) && (fabs(b) > EPS) && (fabs(c) > EPS) && (fabs(a) > EPS)) || ((*discr) > EPS))
            {
                CALC_ROOTS_0_OR_POS(a, b, *discr, x1, x2);
                PRINT_ROOTS_0_OR_POS(x1, x2);
            }
        if((*discr) < -EPS)
            {
                CALC_ROOTS_NEG(a, b, *discr, x_x1, y_x1, x_x2, y_x2);
                PRINT_ROOTS_NEG(x_x1, y_x1, x_x2, y_x2);
            }
    }

void CALC_NUM_OF_ROOTS(double Discr, int* num_of_roots) //Вычисляет кол-во корней по дискриминанту
    {
        if(fabs(Discr - 0.0) <= EPS)
            {
                *num_of_roots = 1;
            }
        else
            {
                *num_of_roots = 2;
            }
    }

void CALC_ROOTS_0_OR_POS(double a, double b, double discr, double* x1, double* x2)  //Cчитает корин при D>=0
    {
        *x1 = (-(b) - sqrt(discr)) / (2.0 * a);
        *x2 = (-(b) + sqrt(discr)) / (2.0 * a);
    }

void CALC_ROOTS_NEG(double a, double b, double discr, double* x_x1, double* y_x1, double* x_x2, double* y_x2)  //Cчитает корни при D<0
    {
        *x_x1 = (-b) / (2 * a);
        *y_x1 = - (sqrt(fabs(discr))) / (2 * a);

        *x_x2 = (-b) / (2 * a);
        *y_x2 = (sqrt(fabs(discr))) / (2 * a);
    }

int CASE_LOGIC(double a, double b, double c)  //Возвращает номер кейса
    {
        if((a < EPS) && (b < EPS) && (c < EPS))
            {
                return 1;
            }
        if((fabs(a - 0.0) <= EPS) && (fabs(b - 0.0) <= EPS) && (fabs(c - 0.0) <= EPS))
            {
                return 2;
            }
        if((fabs(a - 0.0) <= EPS) && (fabs(b - 0.0) > EPS) && (fabs(c - 0.0) > EPS))
            {
                return 3;
            }
        if((fabs(a - 0.0) <= EPS) && (fabs(b - 0.0) <= EPS) && (fabs(c - 0.0) > EPS))
            {
                return 4;
            }
        if(((fabs(a - 0.0) > EPS) && (fabs(b - 0.0) > EPS) && (fabs(c - 0.0) > EPS)) || ((fabs(a - 0.0) > EPS) && (fabs(b - 0.0) <= EPS) && (fabs(c - 0.0) <= EPS)))
            {
                return 5;
            }
        if((fabs(a - 0.0) > EPS) && (fabs(b - 0.0) > EPS) && (fabs(c - 0.0) <= EPS))
            {
                return 6;
            }
    }

void PRINT_ROOTS_NEG(double* x_x1, double* y_x1, double* x_x2, double* y_x2) //Печатает корни при D<0
    {
        printf("x1 = %.2lf+(%.2lf)i\n", *x_x1, *y_x1);
        printf("x2 = %.2lf+(%.2lf)i\n", *x_x2, *y_x2);
    }

void PRINT_ROOTS_0_OR_POS(double* x1, double* x2) //Печатает корни при D>=0
    {
        printf("x1 = %.3lf\n", *x1);
        printf("x2 = %.3lf\n", *x2);
    }

void SOLVE_LINEAR(double c, double b, double* x1)   //linear eq
    {
        *x1 = -(c) / (b);
    }

void PRINT_LINEAR(double x1)   //prints linear root
    {
        printf("x1 = %lf", x1);
    }

void EQUATION_SOLVER_LOGIC(int case_num, double a, double b, double c, double* discr, double* x1, double* x2, double* x_x1, double* y_x1, double* x_x2, double* y_x2, int* Num_of_roots)//Отвечает за логику, вызывает другие функции для решения уравнения
    {
        switch (case_num)
            {
                case 1:
                    printf("ERROR: -1\n");
                    break;
                case 2:
                    printf("Number of roots: %s\n", INF);
                    break;
                case 3:
                    //printf("LINEAR\n");
                    SOLVE_LINEAR(c, b, x1);
                    PRINT_LINEAR(*x1);
                    break;
                case 4:
                    printf("%s\n", NO_ROOTS);
                    break;
                case 5:
                    //printf("DISCR\n");
                    CALC_DISCR(a, b, c, discr);
                    CALC_NUM_OF_ROOTS(*discr, Num_of_roots);
                    printf("Number of roots: %d\n", *Num_of_roots);
                    DISCR_LOGIC(a, b, c, discr, x1, x2, x_x1, y_x1, x_x2, y_x2);
                    break;
                case 6:
                    //printf("AX^2+Bx\n");
                    CALC_DISCR(a, b, c, discr);
                    CALC_NUM_OF_ROOTS(*discr, Num_of_roots);
                    printf("Number of roots: %d\n", *Num_of_roots);
                    CALC_ROOTS_0_OR_POS(a, b, *discr, x1, x2);
                    PRINT_ROOTS_0_OR_POS(x1, x2);
                    break;

                default:
                    printf("ERROR: no case matched");
                    break;
            }
    }











