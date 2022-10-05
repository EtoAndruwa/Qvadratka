#include <stdio.h>
#include <math.h>

#define EPS 0.000001

void PRINT_WELCOME(); // Печатает welcome
void PRINT_EQUATION(double a, double b, double c); //Печатает уравнение с коэффициентами A,B и C
void INPUT_ABC(double* a, double* b, double* c); //Ввод A, B и С
void PRINT_ABC(double a, double b, double c); //Печатает A, B и С
void CALC_DISCR(double a, double b, double c, double* discr); //Считает дискриминант
int CALC_NUM_OF_ROOTS(double Discr); //Возвращает кол-во корней по дискриминанту
void CALC_ROOTS_0_OR_POS(double a, double b, double discr, double* x1, double* x2); //Cчитает корин при D>=0
void CALC_ROOTS_NEG(double a, double b, double discr, double* x_x1, double* y_x1, double* x_x2, double* y_x2);  //Cчитает корни при D<0
void LOGIC_CALC_ROOTS(double a, double b, double discr, double* x1, double* x2, double* x_x1, double* y_x1, double* x_x2, double* y_x2);  //Вызывает функцию calc_roots в зависимости от D
void PRINT_ROOTS_0_OR_POS(double* x1, double* x2); //Печатает корни при D>=0
void PRINT_ROOTS_NEG(double* x_x1, double* y_x1, double* x_x2, double* y_x2); //Печатает корни при D<0



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

        PRINT_WELCOME();
        printf("Enter a, b and c: ");

        INPUT_ABC(&A, &B, &C);
        PRINT_ABC(A, B, C);
        PRINT_EQUATION(A, B, C);

        CALC_DISCR(A, B, C, &Discr);
        LOGIC_CALC_ROOTS(A, B, Discr, &x1, &x2, &x_x1, &y_x1, &x_x2, &y_x2);

        Num_of_roots = CALC_NUM_OF_ROOTS(Discr);
        printf("Number of roots: %d\n", Num_of_roots);



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

void INPUT_ABC(double* a, double* b, double* c) //Ввод A, B и С
    {
        scanf("%lf", a);
        scanf("%lf", b);
        scanf("%lf", c);
    }

void PRINT_ABC(double a, double b, double c) //Печатает A, B и С
    {
        printf("A:%.2lf\n", a);
        printf("B:%.2lf\n", b);
        printf("C:%.2lf\n\n", c);
    }

void CALC_DISCR(double a, double b, double c, double* discr) //Считает дискриминант
    {
        *discr = (b * b) - (4 * a * c);
        printf("DISCR: %.2lf\n", *discr);
    }

int CALC_NUM_OF_ROOTS(double Discr) //Возвращает кол-во корней по дискриминанту    !!!!!!СРАВНИВАЮ ДАБЛ И INT
    {
        if(fabs(Discr - 0.0) < EPS)
            {
                //printf("EPS :%.11lf\n", EPS);
                //printf("If :%.11lf\n", fabs(Discr - 0));
                return 1;
            }
        else
            {
                //printf("EPS :%.11lf\n", EPS);
                //printf("Else if: %.11lf\n", fabs(Discr - 0));
                return 2;
            }
    }

void CALC_ROOTS_0_OR_POS(double a, double b, double discr, double* x1, double* x2)  //Cчитает корин при D>=0
    {
        *x1 = ((-b) - sqrt(discr)) / (2 * a);
        *x2 = ((-b) + sqrt(discr)) / (2 * a);
    }

void CALC_ROOTS_NEG(double a, double b, double discr, double* x_x1, double* y_x1, double* x_x2, double* y_x2)  //Cчитает корни при D<0
    {
        *x_x1 = (-b) / (2 * a);
        *y_x1 = - (sqrt(fabs(discr))) / (2 * a);

        *x_x2 = (-b) / (2 * a);
        *y_x2 = (sqrt(fabs(discr))) / (2 * a);
    }

void LOGIC_CALC_ROOTS(double a, double b, double discr, double* x1, double* x2, double* x_x1, double* y_x1, double* x_x2, double* y_x2)  //Вызывает функцию calc_roots в зависимости от D
    {
        if(discr >= 0)
            {
                CALC_ROOTS_0_OR_POS(a, b, discr, x1, x2);
                PRINT_ROOTS_0_OR_POS(x1, x2);
            }
        else
            {
                CALC_ROOTS_NEG(a, b, discr, x_x1, y_x1, x_x2, y_x2);
                PRINT_ROOTS_NEG(x_x1, y_x1, x_x2, y_x2);
            }
    }

void PRINT_ROOTS_NEG(double* x_x1, double* y_x1, double* x_x2, double* y_x2) //Печатает корни при D<0
    {
        printf("x1 = %.2lf+(%.2lf)i\n", *x_x1, *y_x1);
        printf("x2 = %.2lf+(%.2lf)i\n", *x_x2, *y_x2);
    }

void PRINT_ROOTS_0_OR_POS(double* x1, double* x2) //Печатает корни при D>=0
    {
        printf("x1 = %.2lf\n", *x1);
        printf("x2 = %.2lf\n", *x2);
    }

void SOLVE_LINEAR(double c, double b, double* x1)   //linear    eq
    {
      *x1 = -(c)-(b);
    }

void PRINT_LINEAR(double x1)   //prints linear root
    {
        printf("%lf", x1);
    }

/*double SOLVE_ABC_ZERO()
    {

    }
    */

/*int CASE_ABC(double a, double b, double c)
    {
        switch (a)
            {
                case a
            }
    }*/











