/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TAD.c
 * Author: Tayna
 *
 * Created on 19 de junho de 2021, 12:21
 */

#include "TAD.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int TAM = 0;

//========================================================FUNCOES PARA FILA PISTA================================================================== 

tipoFila criaFila() {

    tipoFila fi;
    fi.primeiro = (ponteiroFila) malloc(sizeof (tipoCelula_Fila));
    fi.ultimo = fi.primeiro;
    fi.primeiro->prox = NULL;

    return fi;
}

bool vaziaFila(tipoFila fi) {

    if (fi.primeiro == fi.ultimo) {
        return true;
    } else {
        return false;
    }
};

tipoFila insereFila(tipoFila fi, int x) {

    TAM++;

    fi.ultimo->prox = (ponteiroFila) malloc(sizeof (tipoCelula_Fila));
    fi.ultimo = fi.ultimo->prox;
    fi.ultimo->prox = NULL;

    //criando a nova celula
    if (x > 0) {//caso tenha uma trocagem de pista
        fi.ultimo->ID = x;
    } else {//caso tenha tido uma aterrisagem
        fi.ultimo->ID = TAM * 2;
    }

    //para poder retirar a celula cabeca
    if (fi.primeiro->ID <= 0) {
        fi = retiraFila(fi, &fi.primeiro->ID);
    }

    return fi;
}

tipoFila retiraFila(tipoFila fi, int *aviao) {

    ponteiroFila aux;

    if (vaziaFila(fi) == false) {
        aux = fi.primeiro;
        *aviao = aux->ID;
        fi.primeiro = aux->prox;
        free(aux);
    }

    return fi;
}

bool imprimeFila(tipoFila fi) {

    ponteiroFila aux;
    int i = 1;

    aux = fi.primeiro;

    if (vaziaFila(fi) == false) {
        while (aux != NULL) {
            printf("\n  - Número na fila: %d"
                    "\n  - ID do avião: %d\n", i,
                                               aux->ID);
            aux = aux->prox;
            i++;
        }
    } else {
        return false;
    }

    return true;
}

int tamanhoFila(tipoFila fi) {

    ponteiroFila aux;
    int i = 0;

    aux = fi.primeiro;

    while (aux != NULL) {
        aux = aux->prox;
        i++;
    }

    return i;

}

//FUNCOES PARA FILA ESTATICA

void criarFila_est(ListaFila *pistas) {

    pistas->inicio = 0;
    pistas->ultimo = pistas->inicio;

    return;
}

void inserirFila_est(ListaFila *pistas) {

    pistas->pista[pistas->ultimo] = criaFila();
    pistas->ultimo++;

    return;
}

//=====================================================FUNCOES PARA LISTA DE ESPERA===================================================================

tipoLista criaLista() {

    tipoLista li;

    li.primeiro = (ponteiroLista) malloc(sizeof (tipoCelula_Lista));
    li.ultimo = li.primeiro;
    li.primeiro->prox = NULL;

    return li;
}

bool vaziaLista(tipoLista li) {

    if (li.primeiro == li.ultimo) {
        return true;
    } else {
        return false;
    }
};

tipoLista insereLista(tipoLista li, tipoAviao x) {

    TAM++;

    li.ultimo->prox = (ponteiroLista) malloc(sizeof (tipoCelula_Lista));
    li.ultimo = li.ultimo->prox;
    li.ultimo->prox = NULL;

    //criando a nova celula
    if (x.ID > 0) {//caso tenha uma trocagem de fila
        li.ultimo->aviao = x;
    } else {//caso tenha tido a chegada de um aviao na fila
        li.ultimo->aviao.ID = (TAM * 2) + 1;
        li.ultimo->aviao.combustivel = (rand() % 20) + 1;
    }

    //para poder retirar a celula cabeca
    if (li.primeiro->aviao.ID <= 0) {
        x = li.primeiro->aviao;
        li = retiraLista(li, x);
    }

    return li;
}

tipoLista retiraLista(tipoLista li, tipoAviao x) {

    ponteiroLista aux, auxAnt;

    aux = li.primeiro;

    while (aux != NULL) {
        //condicao para achar o aviao a ser retirado
        if (aux->aviao.ID == x.ID) {
            //caso o elemento esteja na ultima posicao
            if (aux->prox == NULL) {
                li.ultimo = auxAnt;
                li.ultimo->prox = NULL;
                //caso o elemento esteja na primeira posicao
            } else if (aux == li.primeiro) {
                li.primeiro = aux->prox;
                //caso o elemento esteja no meio da posicao
            } else {
                auxAnt->prox = aux->prox;
            }
            free(aux);
            return li;
        } else {
            auxAnt = aux;
            aux = aux->prox;
        }
    }
    return li;
}

bool imprimeLista(tipoLista li) {

    ponteiroLista aux;
    int i = 1;

    aux = li.primeiro;

    if (vaziaLista(li) == false) {
        while (aux != NULL) {
            printf("\n  - Número na fila: %d"
                    "\n  - ID do avião: %d"
                    "\n  - Combústivel: %d\n", i,
                                               aux->aviao.ID,
                                               aux->aviao.combustivel);
            aux = aux->prox;
            i++;
        }
    } else {
        return false;
    }

    return true;
}

int tamanhoLista(tipoLista li) {

    ponteiroLista aux;
    int i = 0;

    aux = li.primeiro;

    while (aux != NULL) {
        aux = aux->prox;
        i++;
    }

    return i;

}

int casoEmergencia(tipoLista li) {

    ponteiroLista aux;
    int i = 0;

    aux = li.primeiro;

    while (aux != NULL) {
        if (aux->aviao.combustivel == 1) {
            return aux->aviao.ID;
        }
        aux = aux->prox;
    }
    return 0;
}

//FUNCOES PARA LISTA ESTATICA

void criarLista_est(ListaLista *fila) {

    fila->inicio = 0;
    fila->ultimo = fila->inicio;

    return;
}

void inserirLista_est(ListaLista *fila) {

    fila->pratileira[fila->ultimo] = criaLista();
    fila->ultimo++;

    return;
}

tipoLista avioesCaidos(tipoLista li, Dados *dados) {

    ponteiroLista aux;
    tipoAviao aviao;
    int avioes[10], tam = 0;

    aux = li.primeiro;

    if (vaziaLista(li) == false) {
        //laco para ver quantos avioes cairam e seus respectivos IDs
        while (aux != NULL) {
            if (aux->aviao.combustivel <= 0) {
                avioes[tam] = aux->aviao.ID;
                dados->quedas++;
                tam++;
            }
            aux = aux->prox;
        }
        //laco para retirar os avioes caidos
        for (int i = 0; i < tam; i++) {
            aviao.ID = avioes[i];
            li = retiraLista(li, aviao);
        }
    }

    return li;

};

tipoLista diminuirCombustivel(tipoLista li) {

    ponteiroLista aux;

    aux = li.primeiro;

    if (vaziaLista(li) == false) {
        while (aux != NULL) {
            aux->aviao.combustivel--;
            aux = aux->prox;
        }
    }

    return li;

};








