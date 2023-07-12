#include <stdio.h>
#include <cs50.h>

int fact(int factorial);

int main(void)
{
    int factorial = get_int("Número: ");

    int resultado = fact(factorial);

    printf("O resultado é igual a %i\n", resultado);
}

int fact(int factorial)
{
    if (factorial < 2)
    {
        return 1;
    }

    return (factorial * fact(factorial - 1));
}