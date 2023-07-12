#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    // Declaração das variáveis e input das linhas e colunas
    int rows = 0;
    int columns = 0;
    const int number_matrices = 2;

    do
    {
        printf("Digite quantas linhas tem a sua matriz: ");
        scanf("%i", &rows);

    }
    while (rows < 0); // para ser numero não-negativo

    do
    {
        printf("Digite quantas colunas tem a sua matriz: ");
        scanf("%i", &columns);
    }
    while (columns < 0); // para ser numero não-negativo
    system("clear");

    // arrays para salvar os dados da matriz de forma eficiente e não ter q criar milhares de variáveis
    int matrix[number_matrices][rows][columns];
    int resulting_matrix[rows][columns];

    // Foi feito um for para o numero de matrizes, e dentro
    // dele um for para o numero de linhas, aninhado com um for para a
    // numero de colunas, ou seja vai repetir o for de dentro (rows x columns) vezes
    for (int i = 0; i < number_matrices; i++)
    {
        for (int j = 0; j < rows; j++)
        {
            printf("%iª matriz: \n", (i + 1));
            printf("Digite os elementos da %iª linha: \n\n", (j+1));
            for (int k = 0; k < columns; k++)
            {
                printf("Digite o A %ix%i: ", (j+1), (k+1));
                scanf("%d", &matrix[i][j][k]);

                printf("\n");

                // A soma é feita dentro do for após o scanf pegar o valor da segunda matriz
                if (i == 1)
                {
                    resulting_matrix[j][k] = matrix[0][j][k] + matrix[1][j][k];
                }

            }
            system("clear");
        }
    }

    // Mostrando na tela o valor da matriz resultante
    printf("A matriz resultante é: \n\n");
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            printf("%i \t", resulting_matrix[i][j]);
        }
        printf("\n");
    }
}