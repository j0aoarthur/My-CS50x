#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

bool only_digits(string arg);

int main(int argc, string argv[])
{

    while (argc != 2 || only_digits(argv[1]) || atoi(argv[1]) < 0)
    {
        printf("Usage ./caeser key\n");
        return 1;
    }

    int key = atoi(argv[1]);
    string plaintext = get_string("Plaintext:  ");

    for (int i = 0, n = strlen(plaintext); i < n; i++)
    {
        int curr_char = plaintext[i];
        if (isalpha(plaintext[i]))
        {
            if (islower(plaintext[i]))
            {
                int num = ((curr_char - 97) + key) % 26;
                num += 97;
                plaintext[i] = num;
            }
            else if (isupper(plaintext[i]))
            {
                int num = ((curr_char - 65) + key) % 26;
                num += 65;
                plaintext[i] = num;
            }
        }
    }

    printf("ciphertext: %s\n", plaintext);
}

bool only_digits(string arg)
{
    for (int i = 0, n = strlen(arg); i < n; i++)
    {
        if (isdigit(arg[i]))
        {}
        else
        {
            return true;
        }
    }
    return false;
}