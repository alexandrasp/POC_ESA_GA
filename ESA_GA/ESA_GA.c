/*
 ============================================================================
 Name        : ESA_GA.c
 Author      : Alexandra Silva
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */
#include <stdlib.h>
#include <stdio.h>
#include "ESA_GA.h"


void startListAG(Temp* knowledge_base){

	float Temperature[5][MAX_TAM_GA];
	float aux[25];
	int i,j;
	populacaoInicial(Temperature);
	for(i=0; i<5; i++)
	{
		calculaFitnessESelecao(Temperature);
		mutacao(Temperature);
	}

	int k=0;

	for(i=0; i<5; i++)
	{
		for(j=0; j< MAX_TAM_GA; j++)
		{
			aux[k]=Temperature[i][j];
			k++;
		}
	}



	for(i=25; i<MAX_TAM; i++)
	{
		knowledge_base->Temperature[i]=aux[i-25];
	}


}

void startList(Temp* knowledge_base)
{
  int i;
  knowledge_base->control=0;

  for (i=0; i<(MAX_TAM); i++){
    knowledge_base->Temperature[i]=0;
  }

}

void knowledge_base_control(Temp* knowledge_base, float temp_real)
{
  knowledge_base->Temperature[knowledge_base->control] = temp_real;
  knowledge_base->control = (knowledge_base->control+1)%(MAX_TAM/2);

}

//module to do data analysis
int data_analysis(Temp* knowledge_base, float temp_real)
{
    int i;
    //float average_temp_vc=0;
    float average_temp=0;
    float difference = 0;
    int choice=0;

    for(i=0; i<MAX_TAM; i++){
        average_temp = average_temp+knowledge_base->Temperature[i];
    }

    //average_temp_vc=average_temp/MAX_TAM;

    difference = temp_real - average_temp;

    if(difference<0)
      difference=(difference*(-1));

    if(difference < 1){
      //high
      choice=0;
    }
    if(difference >= 1){
      //middle
      choice=1;
    }
    if(difference == 0){
      //low
      choice=2;
    }

    return choice;

}

//planning strategies steps to esa
void planning(int choice, int *SENSOR_INTERVAL, int *PROPAGATION_INTERVAL)
{
	switch(choice)
	{
      case 0:
        if(*SENSOR_INTERVAL > HIGH_SENSORING)
        {
          *SENSOR_INTERVAL = *SENSOR_INTERVAL-1000;
        }
        if(*PROPAGATION_INTERVAL > HIGH_PROPAGATION)
        {
          *PROPAGATION_INTERVAL = *PROPAGATION_INTERVAL-2000;
        }

      break;
      case 1:
        if(*SENSOR_INTERVAL < LOW_SENSORING)
        {
          *SENSOR_INTERVAL += 1000;
        }
        if(*PROPAGATION_INTERVAL < LOW_PROPAGATION)
        {
          *PROPAGATION_INTERVAL += 2000;
        }

      break;
      case 2:
        if(*SENSOR_INTERVAL > HIGH_SENSORING)
        {
          *SENSOR_INTERVAL=*SENSOR_INTERVAL-2000;
        }

        if(*PROPAGATION_INTERVAL > HIGH_PROPAGATION)
        {
          *PROPAGATION_INTERVAL = *PROPAGATION_INTERVAL-4000;
        }

      break;

    }
}

void populacaoInicial(float pop[][MAX_TAM_GA])
{
	int i,j;
	for(i=0; i<5; i++)
	{
		for(j=0; j<MAX_TAM_GA; j++)
		{
			pop[i][j] = range * ((((float) rand()) / (float) RAND_MAX)) + MIN_RAND;
		}
	}

}

void calculaFitnessESelecao(float pop[][MAX_TAM_GA])
{

	int i,j, m, n;
	float media[5];
	float dp[5];
	float indexchoice1=0;
	float indexchoice2=0;

	for(i=0; i<5; i++)
	{
		media[i]=0;
		dp[i]=0;
		for(j=0; j<MAX_TAM_GA; j++)
		{
			media[i] = media[i]+pop[i][j];
		}
		media[i] = media[i]/MAX_TAM_GA;
	}

	for(i=0;i<5;i++)
	{
		for(j=0;j<MAX_TAM_GA;j++)
		{
			dp[i]=dp[i] + pow((pop[i][j]-media[i]), 2);
		}
		dp[i]=sqrt((dp[i]/(5-1)));

		if(i==0)
		{
			indexchoice1=dp[i];
			indexchoice2=dp[i];
		}else
		{
			if(indexchoice1<dp[i])
			{
				indexchoice1=dp[i];
				m=i;
			}
			if(dp[i]>indexchoice2 && dp[i]<indexchoice1)
			{
				indexchoice2=dp[i];
				n=i;
			}
		}
	}
	crossover(pop, m, n);

}

void crossover(float pop[][MAX_TAM_GA], int m, int n)
{

	int i,j;

	for(i=0; i<5; i++)
	{
		for(j=0; j<MAX_TAM_GA; j++){
			if(i!=m && i!=n){
				if(j<3)
					pop[i][j]=pop[m][j];
				else
					pop[i][j]=pop[n][j];

			}
		}
	}

}

void mutacao(float pop[][MAX_TAM_GA])
{
	int i,j;
	for(i=0; i<5; i++)
		{
			for(j=0; j<MAX_TAM_GA; j++){
				pop[i][j] = pop[i][j]*0.9985;
			}
		}

}
