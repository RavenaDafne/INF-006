// Equipe: Rafael Gramos, Ravena Dafne e Uitan Maciel
//Versao Uitan

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int x;
  int y;
} Point;

float calculateDistance(Point a, Point b) {
  return sqrt(pow(b.x - a.x, 2) + pow(b.y - a.y, 2));
}

FILE *openFile(const char *file, const char *mode) {
  FILE *arq = fopen(file, mode);
  if (arq == NULL) {
    printf("Erro ao abrir o arquivo\n");
  }
  return arq;
}

float processLine(FILE* file){
  Point prevPoint, currentPoint;
  double totalDistance = 0;
  int firstPoint = 1; // Flag para indicar se é o primeiro ponto da linha

  // Enquanto conseguir ler pontos no formato esperado
  while (fscanf(file, " (%d,%d)", &currentPoint.x, &currentPoint.y) == 2){
    if(!firstPoint){ // Se não for o primeiro ponto, calcula a distância
      totalDistance += calculateDistance(prevPoint, currentPoint);
    } else {
      firstPoint = 0; // Marca que o primeiro ponto já foi lido
    }
    prevPoint = currentPoint; // Atualiza o ponto anterior
  }
  return totalDistance;
}

float processShortcut(FILE* file){
  Point firstPoint, currentPoint;  
  int hasFirstPoint = 0; // Flag para verificar se o primeiro ponto foi lido

  // Tenta ler o primeiro ponto da linha
  if(fscanf(file, " (%d,%d)", &firstPoint.x, &firstPoint.y) == 2){
    hasFirstPoint = 1; // Marca que temos um primeiro ponto
    currentPoint = firstPoint; 
  }

  // Continua lendo os pontos para encontrar o último ponto da linha
  while (fscanf(file, " (%d,%d)", &currentPoint.x, &currentPoint.y) == 2){
    // Não precisa fazer nada no loop, apenas atualiza o ponto atual
  }

  // Se temos pelo menos um ponto (o primeiro), calcula a distância até o último ponto
  if(hasFirstPoint){
    return calculateDistance(firstPoint, currentPoint);
  } else {
    return 0;
  }
}

int main(void) {
  const char *fileName = "L0Q1.txt";
  FILE *file = openFile(fileName, "r");

  if (file == NULL) return -1;  

  char prefix[7];
  char line[1024];
  long int position;
  double distance, shortcut;

  while(!feof(file)){        

    if(fscanf(file, "%6s", prefix) == 1){
      position = ftell(file);
      fseek(file, position, SEEK_SET);
      distance = processLine(file);

      fseek(file, position, SEEK_SET);
      shortcut = processShortcut(file);      
      printf("distance %.2f shortcut %.2f\n", distance, shortcut);
    }
    if(!feof(file)) {
      fgets(line, sizeof(line), file);
    }
  }

  fclose(file);
  return 0;
}