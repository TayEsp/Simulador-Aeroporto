/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TAD.h
 * Author: Tayna
 *
 * Created on 19 de junho de 2021, 12:21
 */

#ifndef TAD_H
#define TAD_H
#include <stdbool.h>

//ESTRUTURA DE DADOS DE ANALISE
typedef struct{

    int decolagens;
    int aterrisagens;
    int casosEmergencia;
    int quedas;
}Dados;

//========================================================TIPO ABSTRADO DAS FILAS DA PISTA====================================================

//=================================================================TIPO DINAMICO==============================================================
typedef struct tipoCelula_Fila *ponteiroFila;

typedef struct tipoCelula_Fila{
    int ID; 
    ponteiroFila prox;
}tipoCelula_Fila;

typedef struct{
    ponteiroFila primeiro, ultimo;
}tipoFila;

/* Funcao: Insere um aviao na ultima posicao da Fila
   Recebe: Uma struct tipoFila e um inteiro
   Devolve: Uma struct tipoFila*/
tipoFila insereFila(tipoFila fi, int x);
/* Funcao: Retira um item da primeira posicao da Fila
   Recebe: Uma struct tipoFila e um ponteiro de inteiro
   Devolve: Uma struct tipoFila*/
tipoFila retiraFila(tipoFila fi, int *aviao);
/* Funcao: Confere se a fila esta vazia ou nao
   Recebe: Uma struct tipoFila
   Devolve: Uma variavel booleana (false - caso nao esteja vazia, true - caso esteja vazia)*/
bool vaziaFila (tipoFila Pista);
/* Funcao: Cria uma fila vazia
   Recebe: nada
   Devolve: Uma struct tipoFila*/
tipoFila criaFila();
/* Funcao: Imprime todos os itens da fila
   Recebe: Uma struct tipoFila 
   Devolve: Uma variavel booleana (false - caso a fla esteja vazia, true - tenha sido imprimido)*/
bool imprimeFila(tipoFila fi);
/* Funcao: verifica e retorna o tamanho da fila
   Recebe: Uma struct tipoFila
   Devolve: um inteiro (o tamanho da fila)*/
int tamanhoFila (tipoFila fi);

//=================================================================TIPO ESTATICO==============================================================
typedef struct{

    tipoFila pista[3];
    int inicio, ultimo;

}ListaFila;

/*Funcao: Cria uma lista vazia
  Recebe: ponteiro de uma Fila
  Retorna: nada*/
void criarFila_est(ListaFila *pistas);

/*Funcao: Insere um membro a lista e aumenta o tamanho da lista
  Recebe: ponteiro de uma lista
  Retorna: nada*/
void inserirFila_est(ListaFila *pistas);

//=======================================================TIPO ABSTRADO DA LISTA DE ESPERA=====================================================

//=================================================================TIPO DINAMICO==============================================================
typedef struct tipoCelula_Lista *ponteiroLista;

typedef struct {
    int ID;
    int combustivel;
}tipoAviao;

typedef struct tipoCelula_Lista{
    tipoAviao aviao; 
    ponteiroLista prox;
}tipoCelula_Lista;

typedef struct{
    ponteiroLista primeiro, ultimo;
}tipoLista;

/* Funcao: Insere um aviao na ultima posicao da Lista
   Recebe: Uma struct tipoLista e um inteiro
   Devolve: Uma struct tipoLista*/
tipoLista insereLista(tipoLista li, tipoAviao x);
/* Funcao: Retira um item da primeira posicao da Lista
   Recebe: Uma struct tipoLista e um ponteiro de inteiro
   Devolve: Uma struct tipoLista*/
tipoLista retiraLista(tipoLista li, tipoAviao x);
/* Funcao: Confere se a Lista esta vazia ou nao
   Recebe: Uma struct tipoLista
   Devolve: Uma variavel booleana (false - caso nao esteja vazia, true - caso esteja vazia)*/
bool vaziaLista(tipoLista li);
/* Funcao: Cria uma lista vazia
   Recebe: nada
   Devolve: Uma struct tipoLista*/
tipoLista criaLista();
/* Funcao: Imprime todos os itens da Lista
   Recebe: Uma struct tipoLista 
   Devolve: Uma variavel booleana (false - caso a Lista esteja vazia, true - tenha sido imprimido)*/
bool imprimeLista(tipoLista li);
/* Funcao: verifica e retorna o tamanho da Lista
   Recebe: Uma struct tipoLista
   Devolve: um inteiro (o tamanho da Lista)*/
int tamanhoLista (tipoLista li);
/* Funcao: verifica se existe algum aviao sem reserva de combustivel e retorna seu ID 
   Recebe: Uma struct tipoLista 
   Devolve: um inteiro (o ID do aviao)*/
int casoEmergencia(tipoLista li);
/* Funcao: decrementa em um o combustivel de todos os avioes
   Recebe: Uma struct tipoLista 
   Devolve: uma struct tipoLista*/
tipoLista diminuirCombustivel(tipoLista li);

/* Funcao: verifica se existe algum aviao com combustivel igual a 0 e retira esse aviao
   Recebe: Uma struct tipoLista e um ponteiro Dados
   Devolve: uma struct tipoLista*/
tipoLista avioesCaidos(tipoLista li, Dados *dados);

//=================================================================TIPO ESTATICO==============================================================
typedef struct{

    tipoLista pratileira[4];
    int inicio, ultimo;

}ListaLista;

/*Funcao: Cria uma Lista vazia
  Recebe: ponteiro de uma Lista
  Retorna: nada*/
void inserirLista_est(ListaLista *fila);

/*Funcao: Insere um membro a Fila e aumenta o tamanho da Fila
  Recebe: ponteiro de uma Fila
  Retorna: nada*/
void criarLista_est(ListaLista *fila);

#endif /* TAD_H */
