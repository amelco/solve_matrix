#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* **** assinatura das funções **** */
void printHeader();
void printMenu();
void printMatriz(int coef[][50], int n_lin, int n_col);
void askCoeficientes(int numEq, int coef[][50]);
int countVars(char line[], int coefs[]);
void str_trim(char* dest, char* source);

/* **** variáveis globais **** */
char opcao = ' ';       // opção escolhida pelo usuario
char dummy;
int g_hasEq = 0;        // existe equacoes?
int g_numEq = 0;        // numero de equações
int g_numVar = 0;       // numero de variaveis


int main() {
    int i, j;
    int coef[50][50];   // matriz com os coeficientes das equações

    // loop infinito (até usuário pressionar 'q')
    while(1) {
        printHeader();
        printMenu();
        printf("Escolha uma opção: ");
        scanf("%c", &opcao);
        
        if (opcao == '1') {
            printHeader();
            printf("Quantas equações tem o sistema?\n");
            scanf("%d", &g_numEq);
            askCoeficientes(g_numEq, coef);
        }
        else if (opcao == '3') {
            printHeader();
            printMatriz(coef, g_numEq, g_numVar);
            scanf(" %c", &dummy);

        }
        else if (opcao == 'q') break;
    }
    
    return 0;
}

// Imprime cabeçalho do programa
void printHeader() {
    system("clear");
    printf("SELS - Sistema de Equações Lineares Solver\n\n");
}

// Imprime o menu do programa
void printMenu() {
    printf("------------------------------------------\n");
    printf("1. Definir número de equações\n");
    printf("2. Digitar coeficientes das equações\n");
    if (g_hasEq == 1) printf("3. Mostrar matriz\n");
    printf("\n\nq. Sair\n");
    printf("------------------------------------------");
    printf("\n\n");
}

// imprime a matriz
void printMatriz(int coef[][50], int n_lin, int n_col) {
    system("clear");
    printf("Matriz aumentada (%d x %d)\n\n", n_lin, n_col);
    int i, j;
    for (i=0; i<n_lin; i++)
        for (j=0; j<n_col; j++) {
            // printf("[%d %d] ", i, j);
            if (j == 0) printf("|");
            printf("%d ", coef[i][j]);
            if (j == n_col-1) printf("\b|\n");
        }
}

// pergunta ao usuario os coeficientes das equações
void askCoeficientes(int numEq, int coef[][50]) {
    int i, j;
    char line[200];
    int l_coef[50];

    for (i=0; i<numEq; i++) {
        printf("Digite os coeficientes da equação %d:\n", i+1);
        scanf(" %[^\n]", line);
        g_numVar = countVars(line, l_coef);
        
        // armazena os coeficientes na matriz de 2 dimensoes
        for (j=0; j<g_numVar; j++) {
            coef[i][j] = l_coef[j];
        }

        // seta existe equações para 1
        g_hasEq = 1;
    }
}

// conta o numero de variáveis e retorna um vetor com os coeficientes (função interna)
int countVars(char line[], int coefs[]) {
    int i, j, ic;
    int n_var = 1;
    char vars[100];
    char temp[10];

    // elimina todos os espaços excessivos da string
    str_trim(vars, line);

    // conta a quantidade de espaços não consecutivos (=número de variáveis-1)
    i=0;
    j=0;
    ic=0;
    while (1){
        if (vars[i] == ' ' || vars[i] == '\0') {
            coefs[ic] = atoi(temp);             // converte string to int e copia para vetor resultado
            if (vars[i] == '\0') break;         // sai do loop no fim da string
            memset(temp, 0, strlen(temp));      // preenche string com \0
            j=0;                                // reseta indice da string
            ic++;                               // incrementa indice do vetor resultado
            n_var++;
        }
        else {
            temp[j] = vars[i];
            j++;
        }
        i++;
    }
    return n_var;
}

// elimina espaçoes excessivos de uma string (funçao interna)
void str_trim(char* dest, char* source){
    int is = 0, id = 0;     // Index (i) da string source (s) e destino (d).

    // Substitui possíveis espaços no fim da string por \0
    int i=0;
    i = strlen(source)-1;
    while(source[i] == ' ') {
        source[i] = '\0';
        i--;
    }

    while (source[is] != '\0'){     // Verifica fim da string.
        if (source[is] != ' '){     // Se nao for espaco, copia.
            dest[id] = source[is];
            id++;
        } else if (source[is+1] != ' ' && id !=0){  // Se proximo cxaractere 
            if(source[is+1] == '\0') {              // for espaco e nao for  
                dest[id] = '\0';                    // inicio da string, copia.  
            } else {                                // Se for final da string,
                dest[id] = ' ';                     // finaliza a string destino.
                id++;
            }
        }
        is++;
    }
}
