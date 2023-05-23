#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int pi, pf;
    do
    {
        pi = get_int("Initial population: ");
    }
    while (pi < 9);

    do
    {
        pf = get_int("Final population: ");
    }
    while (pf < pi);

    if (pf == pi)
    {
        const int i = 0;
    }

    int i = 0;
    
    while (pi < pf)
    {
        pi = pi + (pi / 3) - (pi / 4);
        i++;
    }

    printf("Years: %i\n", i);
}
