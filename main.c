/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: Tayna
 *
 * Created on 19 de junho de 2021, 12:21
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "TAD.h"

/*
 * 
 */
int geradorAviao(){

    return rand() % 4;
};

void iniciarSimulacao(ListaLista *filasEspera, ListaFila *Pistas, Dados *dados){
    
    int i;
    
    //criando o array com as filas de espera
    criarLista_est(filasEspera);
    
    //criando o array com as pistas
    criarFila_est(Pistas);
    
    //inserindo as filas no array
    for(i=0;i<4;i++){
        inserirLista_est(filasEspera);
                        }
    
    //inserindo as pistas no array
    for(i=0;i<3;i++){
        inserirFila_est(Pistas);
                        }
    
    //zerando os dados de analise
    dados->aterrisagens=0;
    dados->casosEmergencia=0;
    dados->decolagens=0;
    dados->quedas=0;
    
    return;

}

tipoFila verificarEmergencia(tipoFila pista, ListaLista *fila, int *flag, Dados *dados){

    tipoAviao aviao;
    
    //verificando avioes em estados de emergencia em todas as filas de espera
    for(int i=0;i<4;i++){
        (*flag) = casoEmergencia(fila->pratileira[i]);
        //caso tenha um caso de emergencia
        if((*flag)>0){
            aviao.ID = (*flag);
            //retirar o aviao da fila de espera
            fila->pratileira[i] = retiraLista(fila->pratileira[i], aviao);
            //realizar seu pouso
            pista = insereFila(pista, 0);
            //retornar flag de emergencia
            (*flag)=1;
            dados->casosEmergencia++;
            return pista;
                                        }
                                    }
    return pista;
};

int main(int argc, char** argv) {
    
    int temporizador=0, geradorPista, geradorPratileira, aux;
    int flagPista1=0, flagPista2=1, flagEmergencia=0, flagTrocagem=0;
    char flagParada='c';
    
    tipoAviao aviao;
    bool verificacao;
    
    ListaLista tipoFilas, *filasEspera=&tipoFilas;
    ListaFila tipoPistas, *Pistas=&tipoPistas;
    
    Dados dados, *dadosAnalise = &dados;   
    
    iniciarSimulacao(filasEspera, Pistas, dadosAnalise);
    
    srand(time(NULL));
    
    while(flagParada!='s'){
        //apos 5 passagens de tempo é mostrado os dados de analise
        if(temporizador==5){
            printf(" ================= Conteúdo de cada fila =================\n");
            printf("\n ------------------------- Pistas ------------------------\n");
            printf(" Pista 1:");
            verificacao = imprimeFila(Pistas->pista[0]);
            if(verificacao==false){
                printf("\n  Pista vazia!\n");
                                    }
            printf("\n Pista 2:");
            verificacao = imprimeFila(Pistas->pista[1]);
            if(verificacao==false){
                printf("\n  Pista vazia!\n");
                                    }
            printf("\n Pista 3:");
            verificacao = imprimeFila(Pistas->pista[2]);
            if(verificacao==false){
                printf("\n  Pista vazia!\n");
                                    }
            printf("\n -----------------    Filas de Espera    -----------------\n");
            printf(" Fila 1.1:");
            verificacao = imprimeLista(filasEspera->pratileira[0]);
            if(verificacao==false){
                printf("\n  Fila vazia!\n");
                                    }
            printf("\n Fila 1.2:");
            verificacao = imprimeLista(filasEspera->pratileira[1]);
            if(verificacao==false){
                printf("\n  Fila vazia!\n");
                                    }
            printf("\n Fila 2.1:");
            verificacao = imprimeLista(filasEspera->pratileira[2]);
            if(verificacao==false){
                printf("\n  Fila vazia!\n");
                                    }
            printf("\n Fila 2.2:");
            verificacao = imprimeLista(filasEspera->pratileira[3]);
            if(verificacao==false){
                printf("\n  Fila vazia!\n");
                                    }
            
            printf("\n ========== Tempo médio de espera para Decolagem =========\n");
            printf(" == %4d de unidade de tempo                            ==\n", dadosAnalise->decolagens/5);
            printf(" =========================================================\n");
            printf(" ========= Tempo médio de espera para Aterrisagem ========\n");
            printf(" == %4d de unidade de tempo                            ==\n", dadosAnalise->aterrisagens/5);
            printf(" =========================================================\n");
            printf(" ====== Número de aviões sem reserva de combustível ======\n");
            printf(" == %4d de aviões pousaram em situacao de emergencia   ==\n", dadosAnalise->casosEmergencia);
            printf(" =========================================================\n");
            printf(" ============== Número de aviões que cairam ==============\n");
            printf(" == %4d de aviões cairam                               ==\n", dadosAnalise->quedas);
            printf(" =========================================================\n");
            temporizador=0;
            printf(" Aperte qualquer tecla para continuar, ou digite s para sair...\n");
            setbuf(stdin, NULL);//Ressetando o buffer 
            flagParada = getchar();
                                }
        //Gerando os novos avioes
        geradorPista = geradorAviao();
        geradorPratileira = geradorAviao();       
        
        //inserir os avioes gerados nas pistas de decolagem
        while(geradorPista>0){
            if(tamanhoFila(Pistas->pista[0])<=tamanhoFila(Pistas->pista[1])){
                if(tamanhoFila(Pistas->pista[0])>=tamanhoFila(Pistas->pista[2])){
                    Pistas->pista[2] = insereFila(Pistas->pista[2],0);
                }else{
                    Pistas->pista[0] = insereFila(Pistas->pista[0],0);
                        }
            }else{
                if(tamanhoFila(Pistas->pista[1])>=tamanhoFila(Pistas->pista[2])){
                    Pistas->pista[2] = insereFila(Pistas->pista[2],0);
                }else{
                    Pistas->pista[1] = insereFila(Pistas->pista[1],0);
                        }
                    }
            geradorPista--;
                                }
        //zerando o ID do aviao para poder enviar na funcao inserir
        aviao.ID=0;
        //inserir os avioes gerados nas filas de espera
        while(geradorPratileira>0){
            if((tamanhoLista(filasEspera->pratileira[0])+tamanhoLista(filasEspera->pratileira[1]))<=(tamanhoLista(filasEspera->pratileira[2])+tamanhoLista(filasEspera->pratileira[3]))){
                if(tamanhoLista(filasEspera->pratileira[0])<=tamanhoLista(filasEspera->pratileira[1])){
                    filasEspera->pratileira[0] = insereLista(filasEspera->pratileira[0],aviao);
                }else{
                    filasEspera->pratileira[1] = insereLista(filasEspera->pratileira[1],aviao);
                }
            }else{
                if(tamanhoLista(filasEspera->pratileira[2])<=tamanhoLista(filasEspera->pratileira[3])){
                    filasEspera->pratileira[2] = insereLista(filasEspera->pratileira[2],aviao);
                }else{
                    filasEspera->pratileira[3] = insereLista(filasEspera->pratileira[3],aviao);
                        }
                    }
            geradorPratileira--;
                                    }
        
//verificacao da pista 3
        //verificacao de casos de emergencia
        Pistas->pista[2] = verificarEmergencia(Pistas->pista[2], filasEspera, &flagEmergencia, dadosAnalise);
        //caso nao haja emergencias realizar uma decolagem
        if(flagEmergencia==0){
            aux=0;
            Pistas->pista[2] = retiraFila(Pistas->pista[2], &aux);
            dadosAnalise->decolagens++;
        }else{
            flagEmergencia=0;
                }
        
//verificacao da pista 1
        //verificacao de casos de emergencia
        Pistas->pista[0] = verificarEmergencia(Pistas->pista[0], filasEspera, &flagEmergencia, dadosAnalise);
        
        //verificacao de casos de emergencia
        if(flagEmergencia==0){
            //verificar a flag de aterrisagem/decolagem e se as filas de esperas estao vazias
            if(flagPista1==1 || vaziaLista(filasEspera->pratileira[0])==true && vaziaLista(filasEspera->pratileira[1])==true){//se foi 2 aterrisagem fazer uma decolagem
                aux=0;
                Pistas->pista[0] = retiraFila(Pistas->pista[0], &aux);
                flagPista1=0;
                if(vaziaFila(Pistas->pista[0])==false){
                    dadosAnalise->decolagens++;
                                                        }
            }else{//se nao fazer uma aterrisagem
                //retirando o aviao da fila
                if(tamanhoLista(filasEspera->pratileira[0])>=tamanhoLista(filasEspera->pratileira[1])){
                    filasEspera->pratileira[0] = retiraLista(filasEspera->pratileira[0],filasEspera->pratileira[0].primeiro->aviao);
                }else{
                    filasEspera->pratileira[1] = retiraLista(filasEspera->pratileira[1],filasEspera->pratileira[1].primeiro->aviao);
                        }
                //inserindo o aviao na pista
                Pistas->pista[0] = insereFila(Pistas->pista[0], 0);
                flagPista1++;
                dadosAnalise->aterrisagens++;
                    }
        }else{
            flagEmergencia=0;
        }
        //caso 1>2, 1 manda para 3
        if(tamanhoFila(Pistas->pista[0])>=tamanhoFila(Pistas->pista[1])){
            Pistas->pista[0] = retiraFila(Pistas->pista[0], &aux);
            Pistas->pista[2] = insereFila(Pistas->pista[2], aux);
            flagTrocagem=1;
                                                                            }    
        
        
//verificacao da pista 2        
        //verificacao de casos de emergencia
        Pistas->pista[1] = verificarEmergencia(Pistas->pista[1], filasEspera, &flagEmergencia, dadosAnalise);
        
        //verificacao de casos de emergencia
        if(flagEmergencia==0){
            //verificar a flag de aterrisagem/decolagem e se as filas de esperas estao vazias
            if(flagPista2==1 || vaziaLista(filasEspera->pratileira[2])==true && vaziaLista(filasEspera->pratileira[3])==true){//se foi 2 aterrisagem fazer uma decolagem
                Pistas->pista[1] = retiraFila(Pistas->pista[1], &aux);
                flagPista2=0;
                if(vaziaFila(Pistas->pista[1])==false){
                    dadosAnalise->decolagens++;
                                                }
            }else{//se nao fazer uma aterrisagem
                //retirando o aviao da fila
                if(tamanhoLista(filasEspera->pratileira[2])>=tamanhoLista(filasEspera->pratileira[3])){
                    filasEspera->pratileira[2] = retiraLista(filasEspera->pratileira[2],filasEspera->pratileira[2].primeiro->aviao);
                }else{
                    filasEspera->pratileira[3] = retiraLista(filasEspera->pratileira[3],filasEspera->pratileira[3].primeiro->aviao);
                        }
                //inserindo o aviao na pista
                Pistas->pista[1] = insereFila(Pistas->pista[1], 0);
                flagPista2++;
                dadosAnalise->aterrisagens++;
                    }
        }else{
            flagEmergencia=0;
                }
        //caso a flag de trocagem inferir que nao ocorreu, 2 manda para 3
        if(flagTrocagem==0){
            Pistas->pista[1] = retiraFila(Pistas->pista[1], &aux);
            Pistas->pista[2] = insereFila(Pistas->pista[2], aux);
        }else{//caso a trocagem ja tenha ocorrido ressetar a flag
            flagTrocagem=0;
                }
        
        //verificando aviao que cairam e diminuindo a quantidade de combustivel
        for(int i=0;i<4;i++){
            filasEspera->pratileira[i] = diminuirCombustivel(filasEspera->pratileira[i]);
            filasEspera->pratileira[i] = avioesCaidos(filasEspera->pratileira[i], dadosAnalise);
                                }
    
        temporizador++;
    }

    return (EXIT_SUCCESS);
}

