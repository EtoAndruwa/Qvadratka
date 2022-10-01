#include <stdio.h>
#include <math.h>

void PRINT_WELCOME(); // �������� welcome
void PRINT_EQUATION(int a, int b, int c); //�������� ��������� � �������������� A,B � C
void INPUT_ABC(int* a, int* b, int* c); //���� A, B � �
void PRINT_ABC(int a, int b, int c); //�������� A, B � �
void CALC_DISCR(int a, int b, int c, int* discr); //������� ������������
int CALC_NUM_OF_ROOTS(int Discr); //���������� ���-�� ������ �� �������������
void CALC_ROOTS_0_OR_POS(int a, int b, int discr, double* x1, double* x2); //C������ ����� ��� D>=0
void CALC_ROOTS_NEG(int a, int b, int discr, double* x_x1, double* y_x1, double* x_x2, double* y_x2);  //C������ ����� ��� D<0
void LOGIC_CALC_ROOTS(int a, int b, int discr, double* x1, double* x2, double* x_x1, double* y_x1, double* x_x2, double* y_x2);  //�������� ������� calc_roots � ����������� �� D
void PRINT_ROOTS_0_OR_POS(double* x1, double* x2); //�������� ����� ��� D>=0
void PRINT_ROOTS_NEG(double* x_x1, double* y_x1, double* x_x2, double* y_x2); //�������� ����� ��� D<0


#define EPS 0.000001


int main ()
    {
        int Num_of_roots = 0;
        int A = 0;
        int B = 0;
        int C = 0;
        int Discr = 0;
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



void PRINT_WELCOME() // �������� welcome
    {
        printf("##########################\n");
        printf("######Done by Andrey######\n");
        printf("##########################\n\n");
    }

void PRINT_EQUATION(int a, int b, int c) //�������� ��������� � �������������� A,B � C
    {
        printf("Your equation is: (%d)*x^2+(%d)*x+(%d)=0\n\n", a, b, c);
    }

void INPUT_ABC(int* a, int* b, int* c) //���� A, B � �
    {
        scanf("%d", a);
        scanf("%d", b);
        scanf("%d", c);
    }

void PRINT_ABC(int a, int b, int c) //�������� A, B � �
    {
        printf("A:%d\n", a);
        printf("B:%d\n", b);
        printf("C:%d\n\n", c);
    }

void CALC_DISCR(int a, int b, int c, int* discr) //������� ������������
    {
        *discr = (b * b) - (4 * a * c);
        printf("DISCR: %d\n", *discr);
    }

int CALC_NUM_OF_ROOTS(int Discr) //���������� ���-�� ������ �� �������������
    {
        if(Discr == 0)
            {
                return 1;
            }
        else if(Discr > 0)
            {
                return 2;
            }
        else
            {
                return 2;
            }
    }

void CALC_ROOTS_0_OR_POS(int a, int b, int discr, double* x1, double* x2)  //C������ ����� ��� D>=0
    {
        *x1 = (float(-b) - sqrt(discr)) / (2 * a);
        *x2 = (float(-b) + sqrt(discr)) / (2 * a);
    }

void CALC_ROOTS_NEG(int a, int b, int discr, double* x_x1, double* y_x1, double* x_x2, double* y_x2)  //C������ ����� ��� D<0
    {
        *x_x1 = float(-b) / (2 * a);
        *y_x1 = - (sqrt(fabs(discr))) / (2 * a);

        *x_x2 = float(-b) / (2 * a);
        *y_x2 = (sqrt(fabs(discr))) / (2 * a);
    }

void LOGIC_CALC_ROOTS(int a, int b, int discr, double* x1, double* x2, double* x_x1, double* y_x1, double* x_x2, double* y_x2)  //�������� ������� calc_roots � ����������� �� D
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

void PRINT_ROOTS_NEG(double* x_x1, double* y_x1, double* x_x2, double* y_x2) //�������� ����� ��� D<0
    {
        printf("x1 = %f+(%f)i\n", *x_x1, *y_x1);
        printf("x2 = %f+(%f)i\n", *x_x1, *y_x1);
    }

void PRINT_ROOTS_0_OR_POS(double* x1, double* x2) //�������� ����� ��� D>=0
    {
        printf("x1 = %f\n", *x1);
        printf("x2 = %f\n", *x2);
    }



