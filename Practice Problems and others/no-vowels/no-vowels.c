// Write a function to replace vowels with numbers
// Get practice with strings
// Get practice with command line
// Get practice with switch

#include <cs50.h>
#include <stdio.h>
#include <string.h>

string replace(string arg);

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Error command line\n");
        return 1;
    }
    else
    {
        string new_string = replace(argv[1]);
        printf("%s \n", new_string);
    }
}

string replace(string arg)
{
    for (int i = 0, n = strlen(arg); i < n; i++)
    {
        if (arg[i] == 'a' || arg[i] == 'A')
        {
            arg[i] = '6';
        }
        else if (arg[i] == 'e' || arg[i] == 'E')
        {
            arg[i] = '3';
        }
        else if (arg[i] == 'i' || arg[i] == 'I')
        {
            arg[i] = '1';
        }
        else if (arg[i] == 'o' || arg[i] == 'O')
        {
            arg[i] = '0';
        }
    }
    return arg;
}
