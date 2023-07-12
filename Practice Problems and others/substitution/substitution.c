#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

bool has_digits(string arg);
bool repeated_numbers(string arg);

int main(int argc, string argv[])
{
    // get key
    // check key repeated numbers
    // get plaintext
    // for i strlen plaintext
    // islower or upper, subtract 97, % 26 = num
    // new letter =  toupper or tolowoer (key[num]
    // print new word

    while (argc != 2)
    {
        printf("Usage: ./substitution key \n");
        return 1;
    }
    while (strlen(argv[1]) != 26 || has_digits(argv[1]))
    {
        printf("Key must contain 26 different characters. \n");
        return 1;
    }
    while (repeated_numbers(argv[1]))
    {
        printf("Repeated characters. \n");
    }

    string key = argv[1];

    string plaintext = get_string("Plaintext:  ");

    for (int i = 0, n = strlen(plaintext); i < n; i++)
    {
        if (islower(plaintext[i]))
        {
            int num = plaintext[i];
            num = (num - 97) % 26;
            plaintext[i] = tolower(key[num]);
        }
        else if (isupper(plaintext[i]))
        {
            int num = plaintext[i];
            num = (num - 65) % 26;
            plaintext[i] = toupper(key[num]);
        }

    }

    printf("ciphertext: %s\n", plaintext);
}

bool has_digits(string arg)
{
    for (int i = 0, n = strlen(arg); i < n; i++)
    {
        if (isdigit(arg[i]) || ispunct(arg[i]))
        {
            return true;
        }
    }
    return false;
}

bool repeated_numbers(string arg)
{
    bool seen[26] = {false}; // Initialize all elements to false
    int i = 0;
    while (arg[i] != '\0')
    {
        if (seen[(int)arg[i]])
        {
            return true; // Repeated letter found
        }
        seen[(int)arg[i]] = true; // Mark the character as seen
        i++;
    }
    return false;
}