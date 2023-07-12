#include <cs50.h>
#include <stdio.h>

#define NUM_CITIES 10

typedef struct
{
    string city;
    int temp;
}
avg_temp;

avg_temp temps[NUM_CITIES];

void merge(avg_temp array[], avg_temp first_array[], int first_lenght, avg_temp second_array[], int second_lenght);
void merge_sort(avg_temp array[], int array_lenght);

int main(void)
{
    temps[0].city = "Austin";
    temps[0].temp = 97;

    temps[1].city = "Boston";
    temps[1].temp = 82;

    temps[2].city = "Chicago";
    temps[2].temp = 85;

    temps[3].city = "Denver";
    temps[3].temp = 90;

    temps[4].city = "Las Vegas";
    temps[4].temp = 105;

    temps[5].city = "Los Angeles";
    temps[5].temp = 82;

    temps[6].city = "Miami";
    temps[6].temp = 97;

    temps[7].city = "New York";
    temps[7].temp = 85;

    temps[8].city = "Phoenix";
    temps[8].temp = 107;

    temps[9].city = "San Francisco";
    temps[9].temp = 66;

    merge_sort(temps, NUM_CITIES);

    printf("\nAverage July Temperatures by City\n\n");

    for (int i = 0; i < NUM_CITIES; i++)
    {
        printf("%s: %i\n", temps[i].city, temps[i].temp);
    }
}

void merge_sort(avg_temp array[], int array_lenght)
{
    if (array_lenght < 2)
    {
        return;
    }

    int mid = array_lenght / 2;

    avg_temp first_array[mid];
    avg_temp second_array[array_lenght - mid];

    for (int i = 0; i < mid; i++)
    {
        first_array[i].temp = array[i].temp;
        first_array[i].city = array[i].city;

    }
    for (int i = mid; i < array_lenght; i++)
    {
        second_array[i - mid].temp = array[i].temp;
        second_array[i - mid].city = array[i].city;

    }

    merge_sort(first_array, mid);
    merge_sort(second_array, array_lenght - mid);

    merge(array ,first_array, mid, second_array, array_lenght - mid);
}

void merge(avg_temp array[], avg_temp first_array[], int first_lenght, avg_temp second_array[], int second_lenght)
{
    int i = 0, j = 0, k = 0;

    while (i < first_lenght && j < second_lenght)
    {
        if (first_array[i].temp >= second_array[j].temp)
        {
            array[k].temp = first_array[i].temp;
            array[k].city = first_array[i].city;
            i++;
        }
        else
        {
            array[k].temp = second_array[j].temp;
            array[k].city = second_array[j].city;
            j++;
        }
        k++;
    }

    // rest
    while (i < first_lenght)
    {
        array[k].temp = first_array[i].temp;
        array[k].city = first_array[i].city;
        i++;
        k++;
    }

    while (j < second_lenght)
    {
        array[k].temp = second_array[j].temp;
        array[k].city = second_array[j].city;
        j++;
        k++;
    }
}