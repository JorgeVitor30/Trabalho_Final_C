/******************************************************************************************************/
/* Aluno: JONATHA DE OLIVEIRA TARGINO, JORGE VITOR DE AGUIAR LIMA, REULISSON GABRIEL DA SILVA TORRES  */
/* Matricula: N/A                                                                                     */
/* Avaliacao 04: Trabalho Final                                                                       */
/* 04.505.23 − 2022.2 − Prof. Daniel Ferreira                                                         */
/* Compilador: MinGW  GCC-6.3.0-1                                                                     */
/******************************************************************************************************/


#include "pgm.c"
#include "util.c"
#include "quantizar.c"


int main(int argc, char *argv[]){
  
  DIR *d, *d_mean;
  struct dirent *dir, *dir_mean;
  
  FILE *fout;
  if (!(fout = fopen("out.txt", "wb"))){
    perror("Erro ao abrir out.txt.");
		exit(1);
  }
  
  
  // VALOR DE QUANTIZAÇÃO
  if(argc != 2){
    printf("Use:\n\t%s <ValorQuant> \n", argv[0]);
    exit(1);
  }
  
  int quant = atoi(argv[1]);
  if(quant < 2 || quant > 256){
    perror("Use valores no intervalo [2, 256]\n");
    exit(1);
  }
  
  
  
  int scmComp = 0;
  struct pgm img1, img2, scm;
  struct pgm *m1 = NULL, *m2 = NULL;
  int cont =0;
  clock_t begin, end;
	double time_per_img, time_total=0;
  
  d = opendir("./images");
  d_mean = opendir("./images");

  rewinddir(d_mean);
  rewinddir(d);
  if (d){
    int k;
    int tipo;
    // id_arquivo -> 5 no replit e 4 no VSCode.
    char nome_arquivo[30], id_arquivo[4];
  
    for(int i = 0; (dir = readdir(d)) != NULL; i++){
      begin = clock();
      cont +=1;
      
      if(!(verificarMean(dir->d_name))){
        if (i >= 3) {
          printf("%d: %s\n", i-2,dir->d_name);
  
          // Pegar o ID do arquivo.
          for (int j = 2; j <= 6; j++){
            id_arquivo[j-2] = dir->d_name[j];
          }
  
          // Pegar o tipo do arquivo (0 ou 1).
          tipo = dir->d_name[0] - 48;
          lerPGM(&img1,dir->d_name);
          m1 = &img1;
          
          printf("\tID DO ARQUIVO: %s \n", id_arquivo);
          printf("\tTipo do arquivo: %d \n", tipo);
          
          while ((dir_mean = readdir(d_mean)) != NULL){
            if(verificarMean(dir_mean->d_name) && strstr(dir_mean->d_name, id_arquivo)){
              printf("\t%s\n\n", dir_mean->d_name);
              lerPGM(&img2,dir_mean->d_name);
              m2 = &img2;

              quantizarPGM(m1, m2, quant);
              gerarMatrizSCM(m1, m2, &scm);
              escreverMatrizCoocorrencia(&scm, fout, tipo);
              scmComp++;
              break;
            }
          }
      }
    
      rewinddir(d_mean);
      end = clock();
        
      time_per_img = (double)(end - begin) / CLOCKS_PER_SEC;
      time_total += time_per_img;
      // Calcula o tempo de execução
        
      } else {
        i--;
      }

    }
    
    // Fecha os diretórios
    closedir(d);
    closedir(d_mean);
    fclose(fout);
    
  printf("Total de matrizes SCM computadas: %d \n", scmComp);
    
  }
  cont -=2;
  // Calcular tempo médio por imagem.
  printf("Tempo medio: %lf\n",time_total/cont);
  printf("Tempo Total: %lf\n",time_total);

	return(0);
}