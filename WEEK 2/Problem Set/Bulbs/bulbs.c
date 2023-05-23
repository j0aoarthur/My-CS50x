#include <cs50.h>
#include <stdio.h>
#include <string.h>

const int BITS_IN_BYTE = 8;

void print_bulb(int bit);

int main(void)
{
    string message = get_string("Message: ");

    for (int i = 0; i < strlen(message); i++)
    {
        int num = message[i];

        int bits[BITS_IN_BYTE];
        for (int n = BITS_IN_BYTE; n > 0; n--)
        {
            bits[n - 1] = num % 2;
            num /= 2;
        }

        for (int j = 0; j < BITS_IN_BYTE; j++)
        {
            print_bulb(bits[j]);
        }
        printf("\n");
    }
}
void print_bulb(int bit)
{
    if (bit == 0)
    {
        // Dark emoji
        printf("\U000026AB");
    }
    else if (bit == 1)
    {
        // Light emoji
        printf("\U0001F7E1");
    }
}