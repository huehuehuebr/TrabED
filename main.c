#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>


/* Inicio das constantes */

#define VARCHAR 255

/* Fim das constantes */

/* Inicio das structs */
typedef struct aluno {
    int matricula;
    char nome[VARCHAR];
    char endereco[VARCHAR];
    char email[VARCHAR];
    char telefone[VARCHAR];
    float nota1;
    float nota2;
    float nota3;
    float media;
} Aluno;

typedef struct arvore {
    Aluno *aluno;
    struct arvore *esq;
    struct arvore *dir;
    int isBalanciada;
} Node;

/* Fim das structs */

/* Inicio das funcoes */

Node* criaNode();
int inserir(Node **no);
void imprimir(Node *no);
int buscar(Node *no, int n);
void preOrdem(Node *no);
void rotacaoEsq(Node **no);
void rodacaoDir(Node **no);
void rotacaoDuplaEsq(Node **no);
void rotacaoDuplaDir(Node **no);
Aluno* cadastrarAluno();
void printAluno(Aluno a);
int menu();
int calcularAlturaArvore(Node *inicio);
float somarMediaTurma(Node *no);
int qtdNodes(Node *no);
float calcularMediaTurma(Node *no);

/* Fim das funcoes */

int main(int argc, char **argv) {
    setlocale(LC_ALL, "");
    int opcao, altura;
    Node *inicio = NULL;
    do {
        opcao = menu();

        switch (opcao) {
            case 0:
                break;
            case 1:
                inserir(&inicio);
                break;
            case 2:

                break;
            default:
            {
                printf("Opcao Invalida\n");
                break;
            }
        }
        getchar();
        getchar();
    } while (opcao != 0);
    return 0;
}

Node* criaNode() {
    Node *aux = malloc(sizeof (Node));
    aux->isBalanciada = 0;
    aux->esq = NULL;
    aux->dir = NULL;
    aux->aluno = NULL;
    return aux;
}

int inserir(Node **inicio) {
    Aluno *aluno = cadastrarAluno();
    if (*inicio == NULL) {
        (*inicio) = criaNode();
        (*inicio)->aluno = aluno;
        printf("Registro inserido com Sucesso\n\n");
    } else {
        inserirRecursivo(inicio, &aluno);
    }
    return 0;
}

void inserirRecursivo(Node **inicio, Aluno **novo) {
    if (((*inicio)->aluno->matricula) > ((*novo)->matricula)) {
        if ((*inicio)->esq) {
            inserirRecursivo(&((*inicio)->esq), novo);
        } else {
            (*inicio)->esq = (*novo);
            printf("Registro inserido com Sucesso\n\n");
        }
    } else if (((*inicio)->aluno->matricula) < ((*novo)->matricula)) {
        if ((*inicio)->dir) {
            inserirRecursivo(&((*inicio)->dir), novo);
        } else {
            (*inicio)->dir = (*novo);
            printf("Registro inserido com Sucesso\n\n");
        }
    } else {
        printf("Número de matrícula já cadastrado!\n\n");
    }
}

Aluno* cadastrarAluno() {
    Aluno *aluno = malloc(sizeof (Aluno));
    printf("\nInsira a matricula do aluno: ");
    scanf("%d", &(*aluno).matricula);
    printf("\nInsira o nome do aluno: ");
    scanf(" %[^\n]s", &(*aluno).nome);
    /*
            printf("\nInsira o endereco do aluno: ");
            gets(aluno.endereco);
            printf("\nInsira o telefone do aluno: ");
            gets(aluno.telefone);
            printf("\nInsira o e-mail do aluno: ");
            gets(aluno.email);
            printf("\nInsira a nota 1 do aluno: ");
            scanf("%f", &aluno.nota1);
            printf("\nInsira a nota 2 do aluno: ");
            scanf("%f", &aluno.nota2);
            printf("\nInsira a nota 3 do aluno: ");
            scanf("%f", &aluno.nota3);
            aluno.media = (aluno.nota1 + aluno.nota2 + aluno.nota3) / 3;
     */

    return aluno;
}

int remover(Node **no) {

    return 0;
}

void imprimir(Node *no) {
    preOrdem(no);
}

void preOrdem(Node *no) {
    printAluno(*no->aluno);
    preOrdem(no->esq);
    preOrdem(no->dir);
}

void rotacaoEsq(Node **no);
void rodacaoDir(Node **no);
void rotacaoDuplaEsq(Node **no);
void rotacaoDuplaDir(Node **no);

int menu() {
    int op;
    printf("*** Cadastro de Alunos [Arvore AVL] ***\n");
    printf("1) Inserir Aluno\n");
    printf("2) Remover Aluno\n");
    printf("3) Imprimir Aluno\n");
    printf("4) Buscar Aluno\n");
    printf("5) Percorrer Arvore e Calcular média da turma\n");
    printf("4) \n");
    printf("0) Sair\n\n");
    printf("Selecione uma opção");
    scanf("%d", &op);

    return op;
}

void printAluno(Aluno a) {

    printf("\n---- Aluno ----\n");
    printf("Matricula: %d\n", a.matricula);
    printf("Nome: ");
    puts(a.nome);
    printf("Endereco: ");
    puts(a.endereco);
    printf("Telefone: ");
    puts(a.telefone);
    printf("E-mail: ");
    puts(a.email);
    printf("Nota 1: %.2f\n", a.nota1);
    printf("Nota 2: %.2f\n", a.nota2);
    printf("Nota 3: %.2f\n", a.nota3);
    printf("Média: %.2f\n", a.media);
}

int calcularAlturaArvore(Node *inicio) {
    if (inicio == NULL) {
        return 0;
    } else {
        int altLeft = calcularAlturaArvore(inicio->esq);
        int altRight = calcularAlturaArvore(inicio->dir);

        return 1 + (altLeft > altRight ? altLeft : altRight);
    }
}

float somarMediaTurma(Node *no) {
    if (no == NULL)
        return 0;

    else
        return no->aluno->media + somarMediaTurma(no);
}

int qtdNodes(Node *no) {
    if (no == NULL)
        return 0;
    else {
        int qtdEsq = qtdNodes(no->esq);
        int qtdDir = qtdNodes(no->dir);

        return qtdEsq + qtdDir;
    }
}

float calcularMediaTurma(Node *no) {

    float media;
    media = somarMediaTurma(no) / qtdNodes(no);
    return media;

}