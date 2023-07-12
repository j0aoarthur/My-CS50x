#include <stdio.h>

// Calcula o determinante de uma matriz 4x4
double determinant(double matrix[4][4]) {
    double det = 0;

    // Loop para percorrer a primeira linha da matriz e calcular os cofatores
    for (int i = 0; i < 4; i++) {
        // Criamos uma matriz menor correspondente a remover a primeira linha e a coluna do cofator
        double minor[3][3];
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 3; k++) {
                minor[j][k] = matrix[j + 1][(k >= i) ? k + 1 : k];
                // Para cada elemento da matriz menor, copiamos o elemento correspondente da matriz original,
                // mas ignoramos a primeira linha e a coluna correspondente ao cofator atual
            }
        }

        double cofactor = (i % 2 == 0) ? 1 : -1; // O cofator é +1 se i for par e -1 se for ímpar
        cofactor *= determinant(minor); // Calculamos o determinante da matriz menor recursivamente

        det += cofactor * matrix[0][i]; // Adicionamos o produto do cofator e o elemento correspondente da primeira linha da matriz original ao determinante
    }

    return det;
}

int main() {
    double matrix[4][4] = {
        { 1, 2, 3, 4 },
        { 5, 6, 7, 8 },
        { 9, 10, 11, 12 },
        { 13, 14, 15, 16 }
    };

    double det = determinant(matrix); // Chamamos a função determinant() com a matriz de exemplo
    printf("O determinante da matriz é %.2f\n", det); // Imprimimos o resultado para o usuário

    return 0; // Indicamos que o programa terminou com sucesso
}
