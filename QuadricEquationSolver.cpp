#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define EPS 1e-7
#define INF (1 / 0.0)
#define NO_ROOTS 0



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

void print_welcome(); // Печатает welcome
void print_equation(double a, double b, double c); //Печатает уравнение с коэффициентами A,B и C
int input_abc(double* a, double* b, double* c); //Ввод A, B и С
void print_abc(double a, double b, double c); //Печатает A, B и С
void calc_discr(double a, double b, double c, double* discr); //Считает дискриминант
void calc_num_of_roots(double Discr, int* num_of_roots); //Возвращает кол-во корней по дискриминанту
void calc_roots_0_or_pos(double a, double b, double discr, double* x1, double* x2); //Cчитает корин при D>=0
void calc_roots_neg(double a, double b, double discr, double* x_x1, double* y_x1, double* x_x2, double* y_x2);  //Cчитает корни при D<0
int case_logic(double a, double b, double c);  //Возвращает номер кейса
void print_roots_0_or_pos(double* x1, double* x2); //Печатает корни при D>=0
void print_roots_neg(double* x_x1, double* y_x1, double* x_x2, double* y_x2); //Печатает корни при D<0
void equation_solver_logic(int case_num, double a, double b, double c, double* discr, double* x1, double* x2, double* x_x1, double* y_x1, double* x_x2, double* y_x2, int* Num_of_roots); //Отвечает за логику, по кейсам вызывает другие функции для решения уравнения
void print_linear(double x1); //Выводит один корень линейного уравнения
void solve_linear(double c, double b, double* x1); //Решает линейное уравнение
void discr_logic(double a, double b, double c, double* discr, double* x1, double* x2, double* x_x1, double* y_x1, double* x_x2, double* y_x2); //Вызывает функции решения уравнения взависимости от значение дискриминанта квадр. уравнения
int print_logic(double a, double b, double c, int print_logic_flag); //Логика печати уравнения


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
        int print_logic_flag = 0;

        print_welcome();
        printf("Enter a, b and c: ");

        print_logic_flag = input_abc(&A, &B, &C);
        print_logic(A, B, C, print_logic_flag);

        //MY_TEST_FUNCTION();

        Eq_case = case_logic(A, B, C);
        //printf("Case number: %d\n", Eq_case);
        equation_solver_logic(Eq_case, A, B, C, &Discr, &x1, &x2, &x_x1, &y_x1, &x_x2, &y_x2, &Num_of_roots);

        return 0;
    }

void print_welcome() // Печатает welcome
    {
        printf("##########################\n");
        printf("######Done by Andrey######\n");
        printf("##########################\n\n");
    }

void print_equation(double a, double b, double c) //Печатает уравнение с коэффициентами A,B и C
    {
        printf("Your equation is: (%.2lf)*x^2+(%.2lf)*x+(%.2lf)=0\n\n", a, b, c);
    }

int input_abc(double* a, double* b, double* c) //Ввод A, B и С
    {
        if(scanf("%lf", a) != 1)
            {
                printf("ERROR: invalid value for A. Sorry, enter number, please!\n");
                exit(1);
            }
        if(scanf("%lf", b) != 1)
            {
                printf("ERROR: invalid value for B. Sorry, enter number, please!\n");
                exit(1);
            }
        if(scanf("%lf", c) != 1)
            {
                printf("ERROR: invalid value for C. Sorry, enter number, please!\n");
                exit(1);
            }
        else
            {
                return 0;
            }
    }

void print_abc(double a, double b, double c) //Печатает A, B и С
    {
        printf("A:%.2lf\n", a);
        printf("B:%.2lf\n", b);
        printf("C:%.2lf\n\n", c);
    }

void calc_discr(double a, double b, double c, double* discr) //Считает дискриминант
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

void discr_logic(double a, double b, double c, double* discr, double* x1, double* x2, double* x_x1, double* y_x1, double* x_x2, double* y_x2)
    {
        if((fabs(*discr) <= EPS) && (fabs(b) <= EPS) && (fabs(c) <= EPS) && (fabs(a) > EPS))
            {
                *x1 = 0;
                printf("Root: %.3lf", *x1);
            }
        if(((fabs(*discr) <= EPS) && (fabs(b) > EPS) && (fabs(c) > EPS) && (fabs(a) > EPS)) || ((*discr) > EPS))
            {
                calc_roots_0_or_pos(a, b, *discr, x1, x2);
                print_roots_0_or_pos(x1, x2);
            }
        if((*discr) < -EPS)
            {
                calc_roots_neg(a, b, *discr, x_x1, y_x1, x_x2, y_x2);
                print_roots_neg(x_x1, y_x1, x_x2, y_x2);
            }
    }

void calc_num_of_roots(double Discr, int* num_of_roots) //Вычисляет кол-во корней по дискриминанту
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

void calc_roots_0_or_pos(double a, double b, double discr, double* x1, double* x2)  //Cчитает корин при D>=0
    {
        *x1 = (-(b) - sqrt(discr)) / (2.0 * a);
        *x2 = (-(b) + sqrt(discr)) / (2.0 * a);
    }

void calc_roots_neg(double a, double b, double discr, double* x_x1, double* y_x1, double* x_x2, double* y_x2)  //Cчитает корни при D<0
    {
        *x_x1 = (-b) / (2 * a);
        *y_x1 = - (sqrt(fabs(discr))) / (2 * a);

        *x_x2 = (-b) / (2 * a);
        *y_x2 = (sqrt(fabs(discr))) / (2 * a);
    }

int case_logic(double a, double b, double c)  //Возвращает номер кейса
    {
        if((fabs(a - 0.0) < EPS) && (fabs(b - 0.0) < EPS) && (fabs(c - 0.0) < EPS))
            {
                return 1;
            }
        if((fabs(a - 0.0) >= EPS) && (fabs(b - 0.0) >= EPS) && (fabs(c - 0.0) >= EPS))
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

void print_roots_neg(double* x_x1, double* y_x1, double* x_x2, double* y_x2) //Печатает корни при D<0
    {
        printf("x1 = %.2lf+(%.2lf)i\n", *x_x1, *y_x1);
        printf("x2 = %.2lf+(%.2lf)i\n", *x_x2, *y_x2);
    }

void print_roots_0_or_pos(double* x1, double* x2) //Печатает корни при D>=0
    {
        printf("x1 = %.3lf\n", *x1);
        printf("x2 = %.3lf\n", *x2);
    }

void solve_linear(double c, double b, double* x1)   //linear eq
    {
        *x1 = -(c) / (b);
    }

void print_linear(double x1)   //prints linear root
    {
        printf("x1 = %lf", x1);
    }

void equation_solver_logic(int case_num, double a, double b, double c, double* discr, double* x1, double* x2, double* x_x1, double* y_x1, double* x_x2, double* y_x2, int* Num_of_roots)//Отвечает за логику, вызывает другие функции для решения уравнения
    {
        switch (case_num)
            {
                case 1:
                    printf("ERROR: -1\n");
                    break;
                case 2:
                    printf("Number of roots: %lf\n", INF);
                    break;
                case 3:
                    //printf("LINEAR\n");
                    solve_linear(c, b, x1);
                    print_linear(*x1);
                    break;
                case 4:
                    printf("Number of roots: %d\n", NO_ROOTS);
                    break;
                case 5:
                    //printf("DISCR\n");
                    calc_discr(a, b, c, discr);
                    calc_num_of_roots(*discr, Num_of_roots);
                    printf("Number of roots: %d\n", *Num_of_roots);
                    discr_logic(a, b, c, discr, x1, x2, x_x1, y_x1, x_x2, y_x2);
                    break;
                case 6:
                    //printf("AX^2+Bx\n");
                    calc_discr(a, b, c, discr);
                    calc_num_of_roots(*discr, Num_of_roots);
                    printf("Number of roots: %d\n", *Num_of_roots);
                    calc_roots_0_or_pos(a, b, *discr, x1, x2);
                    print_roots_0_or_pos(x1, x2);
                    break;

                default:
                    printf("ERROR: no case matched");
                    break;
            }
    }

int print_logic(double a, double b, double c, int print_logic_flag)// Отвечает за логику печати уравнения
    {
        if(print_logic_flag == 0)
            {
                print_abc(a, b, c);
                print_equation(a, b, c);
            }
        else
            {
                return 1;
            }
    }

//void my_test_function(double a, double b, double c)
//    {
//        for(int i = 0; i < n; i++)
//            {
//                if()
//                    {
//                        printf("Test #\d - passed", i);
//                    }
//                else
//                    {
//                        printf("Test #\d - failed. Details:\n A = %lf\n B = %lf\n C = %lf\n", i, A, B, C);
//                    }
//
//            }
//    }












