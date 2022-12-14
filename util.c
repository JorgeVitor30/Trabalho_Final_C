#include "util.h"

int verificarMean(char * dname){
  char * vrf = strstr(dname, "mean");
  if (vrf) {
    return 1;
  }
  
  return 0;
}