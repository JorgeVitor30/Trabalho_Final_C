/******************************************************************************************************/
/* Aluno: JONATHA DE OLIVEIRA TARGINO, JORGE VITOR DE AGUIAR LIMA, REULISSON GABRIEL DA SILVA TORRES  */
/* Matricula:  N/A                                                                                    */
/* Avaliacao 04: Trabalho Final                                                                       */
/* 04.505.23 − 2022.2 − Prof. Daniel Ferreira                                                         */
/* Compilador: MinGW  GCC-6.3.0-1                                                                     */
/******************************************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <time.h>

struct pgm{
    int tipo;
    int c;
    int r;
    int mv;
    unsigned char *pData;
};

void lerPGM(struct pgm *, char *);
void escreverMatrizCoocorrencia(struct pgm *, FILE *, int);
void gerarMatrizSCM(struct pgm *, struct pgm *, struct pgm *);