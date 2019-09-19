#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* **** variáveis globais **** */
char opcao = ' ';       // opção escolhida pelo usuario
char dummy;
int g_hasEq = 0;        // existe equacoes?
int g_numEq = 0;        // numero de equações
int g_numVar = 0;       // numero de variaveis

/* **** assinatura das funções **** */
void printHeader();
void printMenu();
void printMatriz(float coef[g_numEq][g_numVar]);
void askCoeficientes(float coef[g_numEq][g_numVar]);
int countVars(char line[], float coefs[]);
void str_trim(char* dest, char* source);
void escalonar(float A[g_numEq][g_numVar], float result[g_numEq][g_numVar]);
// void move_linha(int dest[][], int line_dest, int line_source, int source[][]); // interna


int main() {
    int i, j;
    float coef[50][50];   // matriz com os coeficientes das equações
    float res[50][50];    // matriz auxiliar

    // loop infinito (até usuário pressionar 'q')
    while(1) {
        printHeader();
        printMenu();
        printf("Escolha uma opção: ");
        scanf("%c", &opcao);
        
        if (opcao == '1') {
            printHeader();
            printf("Quantas equações tem o sistema? [MAX. 50]\n");
            scanf("%d", &g_numEq);
            askCoeficientes(coef);
            // Verificação do problema (INICIO)
            // Logo após leitura dos valores, a matriz coef é preenchida corretamente
            //   obs.: mesmo código da funcao printMatriz()
            printf("Matriz aumentada (%d x %d)\n\n", g_numEq, g_numVar);
            int i, j;
            for (i=0; i<g_numEq; i++) {
                printf("|");
                for (j=0; j<g_numVar; j++) {
                    printf("%f ", coef[i][j]);
                }
                printf("\b|\n");
            }
            printf("Pressione qualquer tecla para voltar ao menu\n");
            scanf(" %c", &dummy);
            // Imediatamente após preenchimento, pede-se para imprimir através da
            //   funcao e o resultado é inesperado (2nd linha com zeros)
            printMatriz(coef);
            printf("Pressione qualquer tecla para voltar ao menu\n");
            scanf(" %c", &dummy);
            // verificação do problema (FIM)
        
        }
        else if (opcao == '2') {
            askCoeficientes(coef);
        }
        else if (opcao == '3') {
            printHeader();
            printMatriz(coef);
            printf("Pressione qualquer tecla para voltar ao menu\n");
            scanf(" %c", &dummy);

        }
        else if (opcao == '4') {
            printHeader();
            escalonar(coef, res);
            printf("Pressione qualquer tecla para voltar ao menu\n");
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
    printf("\nMENU\n");
    printf("------------------------------------------\n");
    printf("1. Definir número de equações\n");
    if (g_hasEq == 1) {
        printf("2. Digitar coeficientes das equações\n");
        printf("3. Mostrar matriz\n");
        printf("4. Escalonar matriz\n");
        printf("5. Reduzir matriz\n");
    }
    printf("\n\nq. Sair\n");
    printf("------------------------------------------");
    printf("\n\n");
}

// imprime a matriz
void printMatriz(float coef[g_numEq][g_numVar]) {
    system("clear");
    printf("Matriz aumentada (%d x %d)\n\n", g_numEq, g_numVar);
    int i, j;
    for (i=0; i<g_numEq; i++) {
        printf("|");
        for (j=0; j<g_numVar; j++) {
            printf("%f ", coef[i][j]);
        }
        printf("\b|\n");
    }
}

// pergunta ao usuario os coeficientes das equações
void askCoeficientes(float coef[g_numEq][g_numVar]) {
    int i, j;
    char line[200];
    float l_coef[50];

    for (i=0; i<g_numEq; i++) {
        printf("Digite os coeficientes da equação %d: [MAX. 50]\n", i+1);
        scanf(" %[^\n]", line);
        g_numVar = countVars(line, l_coef);
        
        // armazena os coeficientes na matriz de 2 dimensoes
        for (j=0; j<g_numVar; j++) {
            coef[i][j] = l_coef[j];
        }

        // diz que existem equacoes definidas pelo usuario
        g_hasEq = 1;
    }
}

// conta o numero de variáveis e retorna um vetor com os coeficientes (função interna)
int countVars(char line[], float coefs[]) {
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
            coefs[ic] = atof(temp);             // converte string to float e copia para vetor resultado
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

void escalonar(float A[g_numEq][g_numVar], float result[g_numEq][g_numVar]) {
    int i, j;
    
    printMatriz(A);
    printf("Pressione qualquer tecla para voltar ao menu\n");
    scanf(" %c", &dummy);
    
    // Primeiro, vamos assumir que o primeiro elemento é diferente de zero.
    // Verifica se o elemento da segunda linha é diferente de 1
    if (A[0][0] != 1) {
        for (i=0; i<g_numVar; i++) {
            // divide pelo elemento da linha
            result[0][i] = A[0][i]/A[0][0];
        }
    }

    printMatriz(result);
    printf("Pressione qualquer tecla para voltar ao menu\n");
    scanf(" %c", &dummy);
    printf("%f\n", A[1][0]);
     printf("Pressione qualquer tecla para voltar ao menu\n");
    scanf(" %c", &dummy);

    // verifica se a proxima linha tem 1o elemento diff. de 1 e 0
    if (A[1][0] != 1 && A[1][0] != 0) {
        for (i=0; i<g_numVar; i++) {
            // multiplica a linha anterior por menos essa linha e soma com ela mesma
            result[1][i] = (result[0][i] * A[0][0]) - A[1][i];
        }
    }

    printMatriz(result);
    printf("Pressione qualquer tecla para voltar ao menu\n");
    scanf(" %c", &dummy);

}