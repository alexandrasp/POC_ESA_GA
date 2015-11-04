#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define MAX_TAM_GA 5
#define INDIVIDUOS 10
#define GERACOES 40
#define MIN_RAND 15.0
#define MAX_RAND 35.0
#define range 15
#define N 0.05
#define repeat 5
#define myrand 0.06
#define randSelect (0+(rand()%9))
#define MAX_TAM 100
#define HIGH_PROPAGATION 2000
#define LOW_PROPAGATION 20000
#define HIGH_SENSORING 1000
#define LOW_SENSORING 10000

typedef struct
{
	float Temperature[MAX_TAM];
	int control;

}Temp;

void startList(Temp* knowledge_base);
void knowledge_base_control(Temp* knowledge_base, float temp_real); //ok
int data_analysis(Temp* knowledge_base, float temp_real);
void planning(int choice, int *SENSOR_INTERVAL, int *PROPAGATION_INTERVAL);
void execution();

//GA
void startListAG(Temp* knowledge_base);
void populacaoInicial(float pop[][MAX_TAM_GA]);
void calculaFitness(float pop[][MAX_TAM_GA], float dp[]);
void crossover(float pop[][MAX_TAM_GA], float dp[]);
void mutacao(float pop[][MAX_TAM_GA]);
