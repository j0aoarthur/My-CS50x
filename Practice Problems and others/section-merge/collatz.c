#include <stdio.h>
#include <cs50.h>

int collatz(int n);

int main(void)
{

    int num = get_int("Número: ");


    int result = collatz(num);

    printf("O resultado é igual a %i\n", result);
}
int collatz(int n)
{
    if (n == 1)
    {
        return 0;
    }
    else if ((n % 2) == 0)
    {
        return 1 + collatz(n/2);
    }
    else
    {
        return 1 + collatz((3 * n) + 1);
    }
}
