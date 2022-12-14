#include "quantizar.h"

void quantizarMatriz(unsigned char * p, int linhas, int colunas, int faixa){
  for (int k = 0; k < linhas * colunas; k++){
    *(p + k) = *(p + k) / faixa;
  }
}

void quantizarPGM(struct pgm * m1, struct pgm * m2, int quant){
    int faixa = (m1->mv +1) / quant;
  

  quantizarMatriz(m1->pData, m1->r, m1->c, faixa);
  quantizarMatriz(m2->pData, m2->r, m2->c, faixa);
  
  m1->mv = quant -1;
  m2->mv = quant -1;
}