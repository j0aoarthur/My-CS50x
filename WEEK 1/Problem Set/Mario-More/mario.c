#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height = 0;
    do
    {
        height = get_int("Height? ");
    }
    while (height < 1 || height > 8 );

    int space = 1;

    while (height > 0)
    {
        for (int i = height - 1; i > 0; i--)
        {
            printf(" ");
        }

        for (int j = 0; j < space; j++)
        {
            printf("#");
        }
        printf("  ");
        for (int k = 0; k < space; k++)
        {
            printf("#");
        }

        printf("\n");
        height--;
        space++;
    }
}
