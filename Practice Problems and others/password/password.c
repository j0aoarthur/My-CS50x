// Check that a password has at least one lowercase letter, uppercase letter, number and symbol
// Practice iterating through a string
// Practice using the ctype library

#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

bool valid(string password);

int main(void)
{
    string password = get_string("Enter your password: ");
    if (valid(password))
    {
        printf("Your password is valid!\n");
    }
    else
    {
        printf("Your password needs at least one uppercase letter, lowercase letter, number and symbol\n");
    }
}

// TODO: Complete the Boolean function below
bool valid(string password)
{
    int up = 0, lo = 0, nu = 0, sy = 0;

    for (int i = 0, n = strlen(password); i < n; i++)
    {
        if (islower(password[i]))
        {
            lo++;
        }
        else if (isupper(password[i]))
        {
            up++;
        }
        else if (isdigit(password[i]))
        {
            nu++;
        }
        else if (ispunct(password[i]))
        {
            sy++;
        }
    }

    if (lo > 0 && up > 0 && nu > 0 && sy > 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}
