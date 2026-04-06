#include <stdio.h>
int getLCM(int, int);
int getGCD(int, int);
int getPF(int);
int main()
{
    int n, a, b, result;
    int choice_continue;

    do
    {
        printf("Select one below: \n1. GCD \n2. LCM \n3. Prime Factorization \nChoose: ");
        scanf("%d", &n);

        switch (n)
        {
        case 1:
            printf("Enter 2 Numbers: ");
            scanf("%d%d", &a, &b);
            result = getGCD(a, b);
            printf("GCD of %d and %d is %d\n", a, b, result);
            break;
        case 2:
            printf("Enter 2 Numbers: ");
            scanf("%d%d", &a, &b);
            result = getLCM(a, b);
            printf("LCM of %d and %d is %d\n", a, b, result);
            break;
        case 3:
            printf("Enter a Number: ");
            scanf("%d", &a);
            result = getPF(a);
            break;
        }

        printf("\n Do U wanna continue Niggah(1/0)?--");
        scanf("%d", &choice_continue);

    } while (choice_continue);
    return 0;
}

int getGCD(int u, int v)
{
    int i, max;
    if (u > v)
        max = u;
    else
        max = v;
    for (i = max; i >= 1; i--)
    {
        if (u % i == 0 && v % i == 0)
        {
            return i;
        }
    }
}
int getLCM(int u, int v)
{
    int i;
    for (i = 1; i <= u * v; i++)
    {
        if (i % u == 0 && i % v == 0)
        {
            return i;
        }
    }
}
int getPF(int u)
{
    int i;
    for (i = 2; u > 1; i++)
    {
        while (u % i == 0)
        {
            printf("%d ", i);
            u = u / i;
        }
    }
}
