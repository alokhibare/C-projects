#include <stdio.h>
void menu()
{
    printf("\n-------------------------------------------");
    printf("\n-----WELCOME TO SIMPLE CALCULATOR-----");
    printf("Select 1 Option-\n1. Addition\n2. Subtraction\n3. Multyplication\n4. Division\n5. Modulous\n6. Power\n7. EXIT\n");
    printf("\nSo Tell me What's in your Mind: ");
}
int main()
{
    double a, b;
    int choice, answer;

    while (1)
    {
        menu();
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            answer = a + b;
            break;

        case 2:
            answer = a - b;
            break;

        case 3:
            answer = a * b;
            break;

        case 4:
            if (b != 0)
            {
                answer = a / b;
            }
            else
            {
                printf("You have Entered something Wrong.\nSo please check and try again Later.");
            }
            break;

        case 5:
            if (b != 0)
            {
                answer = (int)a % (int)b;
            }
            else
            {
                printf("You have Entered something Wrong.\nSo please check and try again Later.");
            }
            break;

        case 6:
            for (int i = 1, answer = 1; i <= b; i++) {
                answer = answer * a;
            }
            break;

        case 7:
            break;

        default:
            printf("INVALID OPTION!!");
            break;
        }
    }

    printf("\n\nBye Bye, Thanks for coming.\nDeveloped by ALOK.");

    return 0;
}
