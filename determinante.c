#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// estrutura com novo tipo: matriz
typedef struct matriz_t {
    int l, c;               // número de linhas e colunas da matriz
    float value[100][100];  // elementos da matriz
} matriz;

typedef struct vetor_t {
    int n;
    float value[100];
} vetor;

// estrutura novo tipo boolean
typedef enum boolean_t { false, true } boolean;

// assinaturas das funções
int determinante(matriz* A);
int cofator(boolean isLine, int k, matriz* A, vetor* C);
void printMatriz(matriz* A);
void rndMatriz(matriz* A);


// implementação das funções

int determinante(matriz* A) {
    int i, j;
    int zl = 0;     // numero de zeros na linha
    int zc = 0;     // numero de zeros na coluna
    int cl = 0;     // contador de zeros na linha
    int cc = 0;     // contador de zeros na coluna
    int ii = -1;    // índice da linha com maior numero de zeros
    int ij = -1;    // índice da coluna com maior numero de zeros
    float det = 0;  // determinante (return)

    // verifica linha e coluna com maior número de zeros e armazena em ii e ij, respectivamente;
    for (i=0; i<A->l; i++) {
        for (j=0; j<A->c; j++) {
            if ((int)A->value[i][j] == 0) {
                cl++;
            }
            if ((int)A->value[j][i] == 0) {
                cc++;
            }
        }
        if (cl > zl) {
            zl = cl;
            ii = i;
        }
        if (cc > zc) {
            zc = cc;
            ij = i;
        }
        cl = 0;
        cc = 0;
    }

    /** debug **/ // descomente para verificar a qtd. de zeros e linha/coluna que ocorrem
    // printf("%d %d\n", zl, zc);
    // printf("%d %d\n", ii+1, ij+1);
    /** ***** **/
    
    vetor a;
    vetor C;
    // verifica se existe mais zeros na linha ii que na coluna ij
    if (zl > zc) {
        // calcular cofatores na linha ii e com a submatriz Aa
        cofator(true, ii, A, &C);
    } else {
        // calcular cofatores na coluna ij
        cofator(false, ii, A, &C);
    }



    
    return det;
}

int cofator(boolean isLine, int k, matriz* A, vetor* C) {
    if (isLine) {
        // calcular cofatores da linha k
        // definir submatriz Aa
        matriz Aa;
        Aa.l = A->l-1;
        Aa.c = A->c-1;
        //TODO: função gera elementos da submatriz
        if (Aa.l == 1) {
            return 
        }

    } else {
        // calcular cofatores da coluna k
    }

}

void printMatriz(matriz* A) {
    printf("Matriz (%d x %d)\n\n", A->l, A->c);
    int i, j;
    for (i=0; i<A->l; i++) {
        printf("|");
        for (j=0; j<A->c; j++) {
            printf("%.0f ", A->value[i][j]);
        }
        printf("\b|\n");
    }
}

void rndMatriz(matriz* A) {
    for (int i=0; i<A->l; i++)
        for (int j=0; j<A->c; j++)
            A->value[i][j] = (int)rand() % 3;
}

int main() {
    matriz A;

    // 
    srand(time(NULL));
    
    A.l = 6;
    A.c = 6;

    rndMatriz(&A);
    printMatriz(&A);
    determinante(&A);
    // printf("%d\n", determinante(&A));

    return 0;
}