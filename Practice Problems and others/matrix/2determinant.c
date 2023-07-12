#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// int get_int(void);
int determinant_2(int matrix[][2]);
int determinant_3(int matrix[][4]);
int determinant_4(int matrix[][4]);
void remove_element(int array[][4], int index[][2], int array_length);


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
    int matrix[lines][lines];

    // coletando os elementos da 1ª matriz

    // foi feito um for para o numero de linhas, aninhado com um for para a
    // numero de colunas, ou seja vai repetir o for de dentro (lines x columns) vezes
    for (int i = 0; i < lines; i++)
    {
        printf("Primeira matriz: \n");
        printf("Digite os elementos da %iª linha: \n\n", (i + 1));
        for (int j = 0; j < lines; j++)
        {
            printf("Digite o A %ix%i:  ", (i + 1), (j + 1));
            scanf("%d", &matrix[i][j]);
            // matrix[element_1] = get_int();

            printf("\n");
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
        determinant = matrix[0][0]; // matriz de ordem 1, é o seu proprio elemento
    }

    printf("O determinante da sua matriz é %i \n", determinant);

}

int determinant_2(int matrix[][2])
{
    int step_one = matrix[0][0] * matrix[1][1]; // diagonal principal
    int step_two = matrix[1][0] * matrix[0][1]; // diagonal secundária

    return step_one - step_two;
}



int determinant_3(int matrix[][4])
{
    int steps[6];

    // multiplicação do primeiro lado
    steps[0] = matrix[0][0] * matrix[1][1] * matrix[2][2];
    steps[1] = matrix[1][0] * matrix[2][1] * matrix[0][2];
    steps[2] = matrix[2][0] * matrix[0][1] * matrix[1][2];

    // multiplicação do segundo lado
    steps[3] = matrix[1][2] * matrix[2][1] * matrix[0][0];
    steps[4] = matrix[2][2] * matrix[0][1] * matrix[1][0];
    steps[5] = matrix[0][2] * matrix[1][1] * matrix[2][0];

    // soma do produto de cada lado
    int step_one = steps[0] + steps[1] + steps[2];
    int step_two = steps[3] + steps[4] + steps[5];

    // retorno do determinante
    return step_one - step_two;
}
int determinant_4(int matrix[][4])
{
    int matrices[4][4];

    // for para criar copias da matriz de odem 4
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            matrices[i][j] = matrix[i][j];
        }
    }

    // elementos que serão eliminados para criar a matriz que fica dentro do cofator em ordem decrescente

    int elements_A[4][2] =
    {
        {0,0},
        {0,1},
        {0,2},
        {0,3}
    };


    // função criada para eliminar os elementos selecionados em cada array e criar uma nova matriz 3x3
    // for (int k = 0; k < 4; k++)
    // {
    //     remove_element(matrices[k], elements_A[k], 4);
    // }
    remove_element(&matrices[0], &elements_A[0], 4);
    remove_element(&matrices[1], &elements_A[1], 4);
    remove_element(&matrices[2], &elements_A[2], 4);
    remove_element(&matrices[3], &elements_A[3], 4);



    // calculando o produto da primeira linha vezes o seu cofator
    int det = 0;
    int num_signal = 1;
    for (int l = 0; l < 4; l++)
    {
        int current_det = matrix[l][0] * (num_signal); // * determinant_3(matrices)
        num_signal *= -1;
        det += current_det;
    }

    // retorna o determinante
    return det;
}

void remove_element(int array[][4], int index[][2], int array_length)
{
    for (int i = index[]; i < array_length; i++) // rows
    {
        array[0][i] = array[1][i];
    }
    for (int j = 0; j < array_length; j++) // columns
    {
        array[j][j] = array[j + 1][j];
    }
}

// array[ index[joao] ] [k] = array[index[joao] + 1][k]

// array[k][index[joao2]] = array[k+1][index[joao2]]