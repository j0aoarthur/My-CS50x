#include <stdio.h>
#include <cs50.h>

int merge_sort(int n);

int main(void)
{

    int array[6] = {5,3,8,4,1,2};

    int new_array = merge_sort(array, 6);

    for (int i = 0; i < 6; i++)
    {
        printf("%i  ", new_array[i])
    }
}
int merge_sort(int n[], int array_lenght)
{

    // divide array in 2 while is not 2 elements in each array
    // for through 0 to array_lenght/2 - 1
    // for through array_lenght to array_lenght - 1
    // get left array
    // if second element is greater than first
    // first element is now second
    // get right array do the same
    // merge

    if (arrray_lenght > 1)
    {
        merge_sort(n, array_lenght/2);
    }
    // array_lenght == 2 // 5,3
    int new_array[array_lenght];
    for (int i = 0; i < (array_lenght/2) - 1; i++)
    {
        // if 5 < 3
        if (n[i] > n[i+1])
        {
            // for 2 times
            for (int j = array_lenght - 1; j >= 0; j--)
            {
                new_array[j] = n[j]
            }
        }
        else
        {
            return n
        }
    }



}
