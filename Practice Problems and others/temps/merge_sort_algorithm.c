void merge(int array[],int first_array[], int first_lenght, int second_array[], int second_lenght)
{
    int i = 0, j = 0, k = 0;

    while (i < first_lenght && j < second_lenght)
    {
        if (first_array[i] <= second_array[j])
        {
            array[k] = first_array[i];
            i++;
        }
        else
        {
            array[k] = second_array[j];
            j++;
        }
        k++;
    }

    // rest
    while (i < first_lenght)
    {
        array[k] = first_array[i];
        i++;
        k++;
    }

    while (j < second_lenght)
    {
        array[k] = second_array[j];
        j++;
        k++;
    }
}

void merge_sort(int array[], int array_lenght)
{
    if (array_lenght < 2)
    {
        return;
    }

    int mid = array_lenght / 2;

    int first_array[mid];
    int second_array[array_lenght - mid];

    for (int i = 0; i < mid; i++)
    {
        first_array[i] = array[i];
    }
    for (int i = mid; i < array_lenght; i++)
    {
        second_array[i - mid] = array[i];
    }

    merge_sort(first_array, mid);
    merge_sort(second_array, array_lenght - mid);

    merge(array ,first_array, mid, second_array, array_lenght - mid);
}