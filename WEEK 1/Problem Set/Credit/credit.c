#include <cs50.h>
#include <stdio.h>

int check_card(long);
void check_flag(long);
int count_numbers(long);
int first_number(long);
int second_number(long);


int main(void)
{
    long card_num = get_long("Insert your card number: ");

    check_card(card_num);
    if (check_card(card_num) == 1) // number 1 represents true
    {
        check_flag(card_num);
    }
    else
    {
        printf("INVALID\n");
    }
}

int check_card(long card)
{
    // declaration of variables
    int sum = 0, sum2 = 0;
    int curr_digit = 0;
    int curr_sum = 0;

    while (card > 0)
    {
        curr_digit = card % 10; // first sum
        sum2 += curr_digit;

        card /= 10; // second sum
        curr_digit = card % 10;
        curr_sum = curr_digit * 2;
        if (curr_sum > 9)
        {
            sum += (curr_sum % 10) + (curr_sum / 10); // sum +=  last digit + first digit of the current digit
        }
        else
        {
            sum += curr_sum;
        }

        card /= 10; // next number for next loop
    }
    int sumt = sum + sum2;

    if (sumt % 10 == 0) // check if the last number of the total sum iguals to zero and return bool true of false
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int count_numbers(long card)
{
    int count = 0;
    while (card > 0)
    {
        card = card / 10;
        count++;
    }

    return count;
}

int second_number(long card)
{
    while (card >= 100)
    {
        card = card / 10;
    }
    card %= 10;

    return card;

}

int first_number(long card)
{
    while (card >= 10)
    {
        card = card / 10;
    }

    return card;
}

void check_flag(long card)
{
    if (count_numbers(card) == 16)
    {
        if (first_number(card) == 4)
        {
            printf("VISA\n");
        }
        else if (first_number(card) == 5)
        {
            if (second_number(card) >= 1 && second_number(card) <= 5)
            {
                printf("MASTERCARD\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }
    }
    else if (count_numbers(card) == 15)
    {
        if (first_number(card) == 3)
        {
            if (second_number(card) == 4 || second_number(card) == 7)
            {
                printf("AMEX\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }
    }
    else if (count_numbers(card) == 13)
    {
        if (first_number(card) == 4)
        {
            printf("VISA\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
}