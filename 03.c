#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct matriz {
    int n_linhas;  // n�mero de amostras
    int n_colunas; // n�mero de caracter�sticas
    double **data;
} Matriz;

typedef struct vetor {
    int n_elems;
    int *data;
} Vetor;


Matriz *cria_matriz(int n_linhas, int n_colunas) {
    Matriz *mat = (Matriz *) calloc(1, sizeof(Matriz));
    mat->n_linhas = n_linhas;
    mat->n_colunas = n_colunas;

    // alocando a matriz de floats
    mat->data = (double **) calloc(mat->n_linhas, sizeof(double *));
    for (int i = 0; i < mat->n_linhas; i++) {
        mat->data[i] = (double *) calloc(mat->n_colunas, sizeof(double));
    }

    return mat;
}

void destroi_matriz(Matriz **mat_ref) {
    Matriz *mat = *mat_ref;

    for (int i = 0; i < mat->n_linhas; i++) {
        free(mat->data[i]);
    }
    free(mat->data);

    free(mat);
    *mat_ref = NULL;
}

Vetor *cria_vetor(int n_elems) {
    Vetor *vet = calloc(1, sizeof(Vetor));
    vet->n_elems = n_elems;
    vet->data = (int*) calloc(vet->n_elems, sizeof(int));

    return vet;
}

void destroi_vetor(Vetor **vet_ref) {
    Vetor *vet = *vet_ref;
    free(vet->data);
    free(vet);
    *vet_ref = NULL;
}

// classifica um conjunto de testes, X_test, usando o
// algoritmo KNN
void knn(const Matriz *x_train, const Vetor *y_train,
           const Matriz *x_test, int k) {

    double  auxData = 0, auxId = 0;
    Matriz *distancia;

    // For para criar o ponteiro de r�tulo de testes e a matriz de dist�ncia knn
    for(int q = 0; q < x_test->n_linhas; q++){
        distancia = cria_matriz(x_train->n_linhas,2);

        // For para iterar a matrix x_train e com isso pegar as dist�ncias entre cada treino e o teste
        for(int p = 0; p < x_train->n_linhas; p++){
           distancia->data[p][0] = sqrt(pow(x_test->data[q][0]-x_train->data[p][0],2)+pow(x_test->data[q][1]-x_train->data[p][1],2));
           distancia->data[p][1] = p;
        }

        // For para ordenar em ordem crescente a matriz dist�ncia
        for(int x = 0; x < distancia->n_linhas; x++){
            for(int y = x; y < distancia->n_linhas; y++){
                    if(distancia->data[x][0] > distancia->data[y][0]){
                        auxData = distancia->data[x][0];
                        auxId = distancia->data[x][1];

                        distancia->data[x][0] = distancia->data[y][0];
                        distancia->data[x][1] = distancia->data[y][1];

                        distancia->data[y][0] = auxData;
                        distancia->data[y][1] = auxId;
                }
            }
        }

        // For para definir o r�tulo do aluno teste
        int id, aprovado=0, reprovado=0;
        for(int p = 0; p < k; p++){
            id = round(distancia->data[p][1]);
            if(y_train->data[id] == 1){
                aprovado++;
            }
            else{
                reprovado++;
            }
        }

        // Exibe o retorno do Aluno teste
        if (aprovado > reprovado){
            printf("Aluno %d: (%.2lf, %.2lf) = Aprovado\n",q, x_test->data[q][0], x_test->data[q][1]);
        }

        else{
            printf("Aluno %d: (%.2lf, %.2lf) = Reprovado\n",q, x_test->data[q][0], x_test->data[q][1]);
        }
    }

    destroi_matriz(&distancia);
}

int main() {
    int n_amostras_treino; // n�mero de amostras de treinamento
    int n_amostras_teste; // n�mero de amostras de teste
    int k; // n�mero de vizinhos + pr�ximos

    scanf("%d %d %d", &n_amostras_treino, &n_amostras_teste, &k);

    // matriz de caracter�sticas
    // shape: (n_amostras_treino, 2)
    // NOTA M�DIA, QUANTIDADE DE HORAS DE ESTUDO
    Matriz *X_train = cria_matriz(n_amostras_treino, 2);

    // vetor de r�tulos para cada amostra (aluno) de treino
    Vetor *y_train = cria_vetor(n_amostras_treino);

    // L� OS DADOS DO CONJUNTO DE TREINAMENTO
    // obs: n_amostras_treino == X_train->n_linhas
    // para cada aluno de treino p
    for (int p = 0; p < n_amostras_treino; p++) {
        scanf("%lf %lf %d", &X_train->data[p][0],
                          &X_train->data[p][1],
                          &y_train->data[p]);
    }

    Matriz *X_test = cria_matriz(n_amostras_teste, 2);

    // L� OS DADOS DO CONJUNTO DE TESTE
    // obs: n_amostras_teste == X_test->n_linhas
    // para cada aluno de teste q
    for (int q = 0; q < n_amostras_teste; q++) {
        scanf("%lf %lf", &X_test->data[q][0], &X_test->data[q][1]);
    }

    knn(X_train, y_train, X_test, k);

    destroi_matriz(&X_train);
    destroi_vetor(&y_train);
    destroi_matriz(&X_test);

    return 0;
}
