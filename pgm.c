#include "pgm.h"

void lerPGM(struct pgm *pio, char *filename){

	FILE *fp;
	char ch;
  char dirName[100] = "images/";
  
  // Verifica se o arquivo passado existe.
	if (!(fp = fopen(strcat(dirName,filename),"rb"))){
		perror("Erro. Ta botando a file errada fdp!");
		exit(1);
	}

  // Verifica o primeiro caractere do arquivo.
	if ( (ch = getc(fp))!='P'){
		puts("A imagem fornecida nao esta no formato pgm");
		exit(2);
	}

  // Verifica o segundo caractere do arquivo, que deve ser um número que descreve o tipo do PGM -> P2 = PGM binario, P5 = PGM textual.
	pio->tipo = getc(fp)-48;
	
	fseek(fp,1, SEEK_CUR);

	while((ch=getc(fp))=='#'){
		while( (ch=getc(fp))!='\n');
	}

	fseek(fp,-1, SEEK_CUR);

  // Lê as dimensões: Column (Coluna) e Row (Linha).
	fscanf(fp, "%d %d",&pio->c,&pio->r);
	if (ferror(fp)){ 
		perror(NULL);
		exit(3);
	}	
  // Lê o MaxVal (Valor máximo).
	fscanf(fp, "%d",&pio->mv);
	fseek(fp,1, SEEK_CUR);

  // Aloca para pData um espaço dinamicamente na memória de acordo com as dimensões.
	pio->pData = (unsigned char*) malloc(pio->r * pio->c * sizeof(unsigned char));

  // Verifica qual o tipo do arquivo PGM para preencher o pData.
	switch(pio->tipo){
		case 2:
			puts("Lendo imagem PGM (dados em texto)");
      // Lê um de cada vez como unsigned char e armazena no pData.
			for (int k=0; k < (pio->r * pio->c); k++){
				fscanf(fp, "%hhu", pio->pData+k);
			}
		break;	
		case 5:
			puts("Lendo imagem PGM (dados em binario)");
      // Lê todos de uma vez e armazena no pData.
			fread(pio->pData,sizeof(unsigned char),pio->r * pio->c, fp);
		break;
		default:
			puts("Nao esta implementado");
	}
	
	fclose(fp);

}


void escreverMatrizCoocorrencia(struct pgm *pio, FILE *fout, int type){
  
  // Escreve a matriz.
  for (int i=0; i< (pio->c * pio->r); i++){
    if(i < (pio->c * pio->r) - 1){
      fprintf(fout, "%d, ", *(pio->pData + i));
    }
    else {
      fprintf(fout, "%d ", *(pio->pData + i));
    }
  }

  // Escreve o tipo da matriz
  fprintf(fout, "%d\n", type);
  
}

void gerarMatrizSCM(struct pgm *pio1, struct pgm *pio2, struct pgm * scm){
  int pgmCol = pio1->c;
  int pgmRow = pio1->r;
  
  // Tamanho das linhas e tamanho da matriz coocorrencia.
  int rowSize = pio1->mv +1;
  int mSize = rowSize * rowSize;

  printf("Quantidade de elementos: %d", mSize);

  unsigned char *m = NULL;
  m = malloc(sizeof(unsigned char) * mSize);

  
  // Zera a matriz.
  for (int k = 0; k < mSize; k++){
    *(m+k) = 0;
  }

  
  
  // Adicionar Coocorrencias.
  int linhaAtual, colunaAtual;
  for (int k = 0; k < (pio1->c * pio1->r); k++){
    linhaAtual = *(pio1->pData + k);
    colunaAtual = *(pio2->pData + k);
    *(m + (linhaAtual * rowSize) + colunaAtual) += 1;
  }
  
  printf("\nMatriz de coocorrencia:\n");

  //Printa matriz de Coocorrencias.
  for (int k=0; k < mSize; k++){
    // Quebra linha.
		if (!( k % rowSize)) printf("\n");
		printf("%3hhu ",*(m+k));
	}	
	printf("\n");

  scm->r = rowSize;
  scm->c = rowSize;
  scm->tipo = pio1->tipo;
  scm->mv = pio1->mv;
  scm->pData = m;
}