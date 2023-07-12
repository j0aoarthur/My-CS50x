#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// int get_int(void);
int determinant_2(int matrix[]);
int determinant_3(int matrix[]);
int determinant_4(int matrix[]);
void remove_element(int array[], int index[], int array_length, int times);


int main(void)
{
    // Declaração das variáveis e input das linhas e colunas
    int lines = 0;

    do
    {
        printf("Digite quantas linhas ou colunas tem a sua matriz quadrática (1 a 4): ");
        // lines = get_int();
        scanf("%d", &lines);

    }
    while (lines < 0 || lines > 4); // para ser numero não-negativo e menor ou igual a 4

    int num_elements = lines * lines; // saber o numero de elementos da matriz que vai somar
    system("clear"); // limpa o terminal

    // arrays para salvar os dados da matriz de forma eficiente e não ter q criar milhares de variáveis
    int matrix[num_elements];

    // coletando os elementos da 1ª matriz

    // foi feito um for para o numero de linhas, aninhado com um for para a
    // numero de colunas, ou seja vai repetir o for de dentro (lines x columns) vezes
    int element_1 = 0;
    for (int i = 0; i < lines; i++)
    {
        printf("Primeira matriz: \n");
        printf("Digite os elementos da %iª linha: \n\n", (i + 1));
        for (int j = 0; j < lines; j++)
        {
            printf("Digite o A %ix%i:  ", (i + 1), (j + 1));
            scanf("%d", &matrix[element_1]);
            // matrix[element_1] = get_int();

            printf("\n");
            element_1++;
        }
        system("clear"); // limpa o terminal
    }

    int determinant = 0;
    if (lines == 2)
    {
        determinant = determinant_2(matrix); // função para calcular da matriz de ordem 2
    }
    else if (lines == 3)
    {
        determinant = determinant_3(matrix); // função para calcular da matriz de ordem 3
    }
    else if (lines == 4)
    {
        determinant = determinant_4(matrix); // função para calcular da matriz de ordem 4
    }
    else if (lines == 1)
    {
        determinant = matrix[0]; // matriz de ordem 1, é o seu proprio elemento
    }

    printf("O determinante da sua matriz é %i \n", determinant);

}

int determinant_2(int matrix[])
{
    int step_1 = matrix[0] * matrix[3]; // diagonal principal
    int step_2 = matrix[1] * matrix[2]; // diagonal secundária

    return step_1 - step_2;
}



int determinant_3(int matrix[])
{
    int steps[6];

    // multiplicação do primeiro lado
    steps[0] = matrix[6] * matrix[1] * matrix[5];
    steps[1] = matrix[0] * matrix[4] * matrix[8];
    steps[2] = matrix[3] * matrix[7] * matrix[2];

    // multiplicação do segundo lado
    steps[3] = matrix[8] * matrix[1] * matrix[3];
    steps[4] = matrix[2] * matrix[4] * matrix[6];
    steps[5] = matrix[5] * matrix[7] * matrix[0];

    // soma do produto de cada lado
    int step_1 = steps[0] + steps[1] + steps[2];
    int step_2 = steps[3] + steps[4] + steps[5];

    // retorno do determinante
    return step_1 - step_2;
}
int determinant_4(int matrix[])
{
    int matrix_A1[16], matrix_A2[16], matrix_A3[16], matrix_A4[16];

    // for para criar copias da matriz de odem 4
    for (int i = 0; i < 16; i++)
    {
        matrix_A1[i] = matrix[i];
        matrix_A2[i] = matrix[i];
        matrix_A3[i] = matrix[i];
        matrix_A4[i] = matrix[i];
    }

    // elementos que serão eliminados para criar a matriz que fica dentro do cofator em ordem decrescente
    int elements_A1[7] = {12, 8, 4, 3, 2, 1, 0};
    int elements_A2[7] = {12, 8, 7, 6, 5, 4, 0};
    int elements_A3[7] = {12, 11, 10, 9, 8, 4, 0};
    int elements_A4[7] = {15, 14, 13, 12, 8, 4, 0};

    // função criada para eliminar os elementos selecionados em cada array e criar uma nova matriz 3x3
    remove_element(matrix_A1, elements_A1, 16, 7);
    remove_element(matrix_A2, elements_A2, 16, 7);
    remove_element(matrix_A3, elements_A3, 16, 7);
    remove_element(matrix_A4, elements_A4, 16, 7);


    // calculando o produto da primeira linha vezes o seu cofator
    int A11 = matrix[0] * (1 * determinant_3(matrix_A1));
    int A21 = matrix[4] * (-1 * determinant_3(matrix_A2));
    int A31 = matrix[8] * (1 * determinant_3(matrix_A3));
    int A41 = matrix[12] * (-1 * determinant_3(matrix_A4));

    // retorna o determinante
    return A11 + A21 + A31 + A41;
}

void remove_element(int array[], int index[], int array_length, int times)
{
    int j = 0;
    for (int k = 0; k < times; k++)
    {
        int i = 0;
        for (i = index[j]; i < array_length - 1; i++)
        {
            array[i] = array[i + 1];
        }
        j++;
    }
}

