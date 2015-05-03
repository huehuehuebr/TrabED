#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
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
    int balanceamento;
} Node;
/* Fim das structs */

/* Inicio das funcoes */
Node* criaNode();
int inserir(Node **no);
int remover(Node **no);
void inserirRecursivo(Node **no, Aluno **novo);
void imprimir(Node *no);
void buscar(Node *no);
void busca(Node *no, int matricula);
void imprimirPreOrdem(Node *no);
Node* rotacaoEsq(Node **no);
Node* rotacaoDir(Node **no);
Node* rotacaoDuplaEsq(Node **no);
Node* rotacaoDuplaDir(Node **no);
Aluno* cadastrarAluno();
void imprimirAluno(Aluno a);
void clrscr();
int menu();
int calcularAlturaArvore(Node *no);
float somarMediaTurma(Node *no);
int qtdNodes(Node *no);
float calcularMediaTurma(Node *no);
int calcularBalanceamento(Node *no);
Node* balancearArvoreAVL(Node **no);
void imprimirArvore(Node *no, int alturaRaiz);
int removerAluno(Node **no, char matricula);
Node* removerRecursivo(Node **no);

/* Fim das funcoes */

int main(int argc, char **argv) {

    setlocale(LC_ALL, "PT_BR.UTF-8");

    int opcao, altura, retorno;
    Node *inicio = NULL;

    do {
        clrscr();
        opcao = menu();

        switch (opcao) {
            case 0:
                break;
            case 1:
                inserir(&inicio);
                break;
            case 2:
                retorno = remover(&inicio);
                if (retorno == 0)
                    printf("Não foi Removido!\n");
                else
                    printf("Aluno removido com sucesso!\n");
                break;
            case 3:
                imprimir(inicio);
                break;
            case 4:
                buscar(inicio);
                break;
            case 5:
                calcularMediaTurma(inicio);
                break;
            case 6:
                balancearArvoreAVL(&inicio);
                break;
            case 7:
                altura = calcularAlturaArvore(inicio);
                printf("A Altura da Arvore eh %d\n", altura);
                break;
            case 8:
                printf("\n\n");
                imprimirArvore(inicio, 0);
                break;
            default:
            {
                printf("Opcao Invalida\n");
                break;
            }
        }
        printf("\nPressione qualquer tecla para continuar");
        getche();
    } while (opcao != 0);

    return 0;
}

Node* criaNode() {
    Node *aux = malloc(sizeof (Node));
    aux->balanceamento = 0;
    aux->esq = NULL;
    aux->dir = NULL;
    aux->aluno = NULL;

    return aux;
}

int inserir(Node **no) {
    Aluno *aluno = cadastrarAluno();
    if (*no == NULL) {
        (*no) = criaNode();
        (*no)->aluno = aluno;
        printf("\n\nRegistro inserido com Sucesso\n");
    } else {

        inserirRecursivo(no, &aluno);
    }
    return 0;
}

void inserirRecursivo(Node **no, Aluno **novo) {
    if (((*no)->aluno->matricula) > ((*novo)->matricula)) {
        if ((*no)->esq) {
            inserirRecursivo(&((*no)->esq), novo);
        } else {
            (*no)->esq = criaNode();
            (*no)->esq->aluno = (*novo);
            printf("\n\nRegistro inserido com Sucesso\n");
        }
    } else if (((*no)->aluno->matricula) < ((*novo)->matricula)) {
        if ((*no)->dir) {
            inserirRecursivo(&((*no)->dir), novo);
        } else {
            (*no)->dir = criaNode();
            (*no)->dir->aluno = (*novo);
            printf("\n\nRegistro inserido com Sucesso\n");
        }
    } else {

        printf("\n\nNúmero de matrícula já cadastrado!\n");
    }
}

Aluno* cadastrarAluno() {
    Aluno *aluno = malloc(sizeof (Aluno));
    printf("\nInsira a matricula do aluno: ");
    scanf("%d", &(*aluno).matricula);
    /*
    printf("\nInsira o nome do aluno: ");
    scanf(" %[^\n]s", &(*aluno).nome);
    printf("\nInsira o endereco do aluno: ");
    gets(aluno.endereco);
    printf("\nInsira o telefone do aluno: ");
    gets(aluno.telefone);
    printf("\nInsira o e-mail do aluno: ");
    gets(aluno.email);
    printf("\nInsira a 1ª nota do aluno: ");
    scanf("%f", &aluno.nota1);
    printf("\nInsira a 2ª nota do aluno: ");
    scanf("%f", &aluno.nota2);
    printf("\nInsira a 3ª nota do aluno: ");
    scanf("%f", &aluno.nota3);
    aluno.media = (aluno.nota1 + aluno.nota2 + aluno.nota3) / 3;
     */
    return aluno;
}

void busca(Node *no, int matricula) {

    while (no != NULL) {
        if (no->aluno->matricula == matricula) {
            clrscr();
            imprimirAluno(*no->aluno);
        } else {
            if (matricula < no->aluno->matricula) {
                no = no->esq;
            } else {
                no = no->dir;
            }
        }
        printf("Aluno não matriculado!\n");
        getche();
    }
}

void buscar(Node *no) {
    int matricula;
    if (no == NULL) {
        printf("Árvore vazia!");
        getche();
        return;
    } else {
        printf("Digite a matricula do aluno: ");
        scanf("%d", &matricula);
        busca(no, matricula);
    }
}

void imprimir(Node *no) {
    imprimirPreOrdem(no);
}

void imprimirPreOrdem(Node *no) {

    imprimirAluno(*no->aluno);
    imprimirPreOrdem(no->esq);
    imprimirPreOrdem(no->dir);
}

int menu() {
    int op;
    printf("*** Cadastro de Alunos [Árvore AVL] ***\n");
    printf("1) Inserir Aluno\n");
    printf("2) Remover Aluno\n");
    printf("3) Imprimir Aluno\n");
    printf("4) Buscar Aluno\n");
    printf("5) Percorrer Arvore e Calcular média da turma\n");
    printf("6) Balancear árvore\n");
    printf("7) Calcular altura da árvore\n");
    printf("8) Imprimir árvore\n");
    printf("0) Sair\n\n");
    printf("Selecione uma opção: ");
    scanf("%d", &op);

    return op;
}

void imprimirAluno(Aluno a) {

    printf("\n---- Aluno ----\n");
    printf("Matricula: %d\n", a.matricula);
    printf("Nome: ");
    puts(a.nome);
    /*printf("Endereco: ");
    puts(a.endereco);
    printf("Telefone: ");
    puts(a.telefone);
    printf("E-mail: ");
    puts(a.email);
    printf("Nota 1: %.2f\n", a.nota1);
    printf("Nota 2: %.2f\n", a.nota2);
    printf("Nota 3: %.2f\n", a.nota3);
    printf("Média: %.2f\n", a.media);*/
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

int calcularBalanceamento(Node *inicio) {
    if (inicio == NULL) {
        return 0;
    } else {
        int altLeft = calcularAlturaArvore(inicio->esq);
        int altRight = calcularAlturaArvore(inicio->dir);
        (*inicio).balanceamento = altLeft - altRight;
        return (*inicio).balanceamento;
    }
}

float somarMediaTurma(Node *no) {
    if (no == NULL)
        return 0;
    else {
        int mediaEsq = somarMediaTurma(no->esq);
        int mediaDir = somarMediaTurma(no->dir);

        return no->aluno->media + mediaEsq + mediaDir;
    }
}

int qtdNodes(Node *no) {
    if (no == NULL)
        return 0;
    else {
        int qtdEsq = qtdNodes(no->esq);
        int qtdDir = qtdNodes(no->dir);

        return 1 + qtdEsq + qtdDir;
    }
}

float calcularMediaTurma(Node *no) {
    float media;
    media = somarMediaTurma(no) / qtdNodes(no);

    return media;
}

Node* rotacaoEsq(Node **no) {
    Node *noRotac = (*no)->dir;
    if (noRotac->esq) {
        (*no)->dir = noRotac->esq;
    } else {
        (*no)->dir = NULL;
    }
    noRotac->esq = *no;

    return noRotac;
}

Node* rotacaoDir(Node **no) {
    Node *noRotac = (*no)->esq;
    if (noRotac->dir) {
        (*no)->esq = noRotac->dir;
    } else {
        (*no)->esq = NULL;
    }
    noRotac->dir = *no;

    return noRotac;
}

Node* rotacaoDuplaEsq(Node **no) {
    Node *noRotac1 = (*no)->dir;
    Node *noRotac2 = noRotac1->esq;

    if (noRotac2->esq) {
        (*no)->dir = noRotac2->esq;
    } else {
        (*no)->dir = NULL;
    }
    if (noRotac2->dir) {
        noRotac1->esq = noRotac2->dir;
    } else {
        noRotac1->esq = NULL;
    }
    noRotac2->esq = (*no);
    noRotac2->dir = noRotac1;

    return noRotac2;
}

Node* rotacaoDuplaDir(Node **no) {
    Node *noRotac1 = (*no)->esq;
    Node *noRotac2 = noRotac1->dir;

    if (noRotac2->esq) {
        noRotac1->dir = noRotac2->esq;
    } else {
        noRotac1->dir = NULL;
    }

    if (noRotac2->dir) {
        (*no)->esq = noRotac2->dir;
    } else {
        (*no)->esq = NULL;
    }
    noRotac2->esq = noRotac1;
    noRotac2->dir = (*no);

    return noRotac2;
}

Node* balancearArvoreAVL(Node **no) {
    if ((*no) != NULL) {
        (*no)->balanceamento = calcularBalanceamento((*no));
        if ((*no)->balanceamento >= 2) {
            (*no)->esq->balanceamento = calcularBalanceamento((*no)->esq);
            if ((*no)->esq->balanceamento > 0) {
                (*no) = rotacaoDir(no);
            } else {
                (*no) = rotacaoDuplaDir(no);
            }
        } else if ((*no)->balanceamento <= -2) {
            (*no)->dir->balanceamento = calcularBalanceamento((*no)->dir);
            if ((*no)->dir->balanceamento < 0) {
                (*no) = rotacaoEsq(no);
            } else {
                (*no) = rotacaoDuplaEsq(no);
            }
        }
        (*no)->esq = balancearArvoreAVL(&((*no)->esq));
        (*no)->dir = balancearArvoreAVL(&((*no)->dir));
    }
    return (*no);
}

void clrscr() {
#if defined(__linux__)
    system("clear");
#elif defined(_WIN64) ||  defined(_WIN32)
    system("cls");
#elif defined(__APPLE__) || defined(__MACH__)
    system("clear");
#endif
}

void imprimirArvore(Node *inicio, int alturaRaiz) {
    if (inicio == NULL && alturaRaiz == 0) {
        printf("Árvore vazia!\n");
        return;
    }
    if (inicio == NULL)
        return;
    imprimirArvore(inicio->dir, alturaRaiz + 1);
    int i = 0;
    for (i; i < alturaRaiz; i++) {
        printf("\t");
    }
    printf("(%d)", inicio->aluno->matricula);
    if (inicio->dir && inicio->esq) {
        printf("%c", 60);
    } else if (inicio->dir && !inicio->esq) {
        printf("%c", 47);
    } else if (!inicio->dir && inicio->esq) {
        printf("%c", 92);
    }
    printf("\n");
    imprimirArvore(inicio->esq, alturaRaiz + 1);
}

int remover(Node **no) {
    int matricula;
    if (*no == NULL) {
        printf("Árvore vazia!");
        getche();
        return 0;
    } else {
        printf("Digite a matricula do aluno: ");
        scanf("%d", &matricula);
        return removerAluno(no, matricula);
    }
    return 0;
}

int removerAluno(Node **no, char matricula) {
    Node *noPai, *noRemovido = *no;
    int isNoDir = 0;

    if (matricula == noRemovido->aluno->matricula) {
        *no = removerRecursivo(&noRemovido);
        return 1;
    }
    while (noRemovido != NULL) {
        if (matricula == noRemovido->aluno->matricula) {
            if (isNoDir) {
                noPai->dir = removerRecursivo(&noRemovido);
            } else {
                noPai->esq = removerRecursivo(&noRemovido);
            }
            return 1;
        } else {
            if (matricula < noRemovido->aluno->matricula) {
                isNoDir = 0;
                noPai = noRemovido;
                (noRemovido) = noRemovido->esq;
            } else {
                isNoDir = 1;
                noPai = noRemovido;
                (noRemovido) = noRemovido->dir;
            }
        }
    }
    return 0;
}

Node* removerRecursivo(Node **no) {
    Node *noAux;
    Node *noAuxPai;
    if (((*no)->esq == NULL) && ((*no)->dir == NULL)) {
        free(*no);
        return NULL;
    } else if (((*no)->esq == NULL) && ((*no)->dir != NULL)) {
        noAux = (*no)->dir;
        free(*no);
        return noAux;
    } else if (((*no)->esq != NULL) && ((*no)->dir == NULL)) {
        noAux = (*no)->esq;
        free(*no);
        return noAux;
    } else {
        if ((*no)->esq->dir == NULL) {
            noAux = (*no)->esq;
            (*no)->esq->dir = (*no)->dir;
            free(*no);
            return noAux;
        } else {
            noAux = (*no)->esq;
            while (noAux->dir != NULL) {
                noAuxPai = noAux;
                noAux = noAux->dir;
            }
            if (noAux->esq != NULL) {
                noAuxPai->dir = noAux->esq;
            } else {
                noAuxPai->dir = NULL;
            }
            noAux->dir = (*no)->dir;
            noAux->esq = (*no)->esq;
            free(*no);
            return noAux;
        }
    }
    return NULL;
}
