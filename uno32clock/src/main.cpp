#include "Arduino.h"
#include <stdio.h>
#include <stdlib.h>

void setup()
{
  Serial.begin(9600);
}

int matriz[8][32]= {{0}};
int matriz_cor[8][32][3]= {{0}};

int div_0[8][8][3] = {{0}};
int div_1[8][8][3] = {{0}};
int div_2[8][8][3] = {{0}};
int div_3[8][8][3] = {{0}};

int zero[5][3]= 	{1, 1, 1, 	1, 0, 1, 	1, 0, 1, 	1, 0, 1, 	1, 1, 1};
int um[5][3]= 		{0, 1, 0, 	1, 1, 0, 	0, 1, 0, 	0, 1, 0, 	1, 1, 1};
int dois[5][3]= 	{1, 1, 1, 	0, 0, 1, 	1, 1, 1, 	1, 0, 0, 	1, 1, 1};
int tres[5][3]= 	{1, 1, 1, 	0, 0, 1, 	1, 1, 1, 	0, 0, 1, 	1, 1, 1};
int quatro[5][3]= 	{1, 0, 1, 	1, 0, 1,	1, 1, 1, 	0, 0, 1, 	0, 0, 1};
int cinco[5][3]= 	{1, 1, 1, 	1, 0, 0, 	1, 1, 1, 	0, 0, 1, 	1, 1, 1};
int seis[5][3]= 	{1, 1, 1, 	1, 0, 0, 	1, 1, 1, 	1, 0, 1, 	1, 1, 1};
int sete[5][3]= 	{1, 1, 1, 	0, 0, 1, 	0, 0, 1, 	0, 0, 1, 	0, 0, 1};
int oito[5][3]= 	{1, 1, 1, 	1, 0, 1, 	1, 1, 1, 	1, 0, 1, 	1, 1, 1};
int nove[5][3]= 	{1, 1, 1, 	1, 0, 1, 	1, 1, 1, 	0, 0, 1, 	1, 1, 1};
int doispontos[5][3]={0, 0, 0, 	0, 1, 0, 	0, 0, 0, 	0, 1, 0, 	0, 0, 0};


int por_num(int num, int x, int y){

	switch (num){
	   case 0:
		   for (int i=0; i<=2; i++) //filas
		   	        for (int j=0; j<=4; j++) //colunas
		   	        	matriz[y+j][x+i] = zero[j][i];
	   break;
	   case 1:
	   		   for (int i=0; i<=2; i++)
	   		   	        for (int j=0; j<=4; j++)
	   		   	        	matriz[y+j][x+i] = um[j][i];
	   	   break;
	   case 2:
		   for (int i=0; i<=2; i++)
			   for (int j=0; j<=4; j++)
				   matriz[y+j][x+i] = dois[j][i];
		   break;
	   case 3:
		   for (int i=0; i<=2; i++)
			   for (int j=0; j<=4; j++)
				   matriz[y+j][x+i] = tres[j][i];
		   break;
	   case 4:
		   for (int i=0; i<=2; i++)
			   for (int j=0; j<=4; j++)
				   matriz[y+j][x+i] = quatro[j][i];
		   break;
	   case 5:
		   for (int i=0; i<=2; i++)
			   for (int j=0; j<=4; j++)
				   matriz[y+j][x+i] = cinco[j][i];
		   break;
	   case 6:
		   for (int i=0; i<=2; i++)
			   for (int j=0; j<=4; j++)
				   matriz[y+j][x+i] = seis[j][i];
		   break;
	   case 7:
		   for (int i=0; i<=2; i++)
			   for (int j=0; j<=4; j++)
				   matriz[y+j][x+i] = sete[j][i];
		   break;
	   case 8:
		   for (int i=0; i<=2; i++)
			   for (int j=0; j<=4; j++)
				   matriz[y+j][x+i] = oito[j][i];
		   break;
	   case 9:
		   for (int i=0; i<=2; i++)
			   for (int j=0; j<=4; j++)
				   matriz[y+j][x+i] = nove[j][i];
		   break;
	   case 10:
		   for (int i=0; i<=2; i++)
			   for (int j=0; j<=4; j++)
				   matriz[y+j][x+i] = doispontos[j][i];
		   break;
  }
}

//Valor entre 0 e 255
int por_cor(int red2, int green2, int blue2){

	//RED
	for(int a=0; a<=7; a++) //filas
		for(int b=0;b<=31;b++)//colunas
			for(int c=0;c<=2;c++){ //cor
				matriz_cor[a][b][0] = matriz[a][b] * red2 ;
			}
	//GREEN
	for(int a=0; a<=7; a++)
		for(int b=0;b<=31;b++)
			for(int c=0;c<=2;c++){
				matriz_cor[a][b][1] = matriz[a][b] * green2 ;
			}
	//BLUE
	for(int a=0; a<=7; a++)
		for(int b=0;b<=31;b++)
			for(int c=0;c<=2;c++){
				matriz_cor[a][b][2] = matriz[a][b] * blue2 ;
			}
}

//relógio
int rtc_small(int horas, int min, int seg, int red, int green, int blue){

	//Horas
	por_num( (horas/10), 1, 1);
	por_num( (horas%10), 5, 1);
	//dois pontos
	por_num(10, 8, 1);
	//Minutos
	por_num( (min/10), 11, 1);
	por_num( (min%10), 15, 1);
	//dois pontos
	por_num(10, 18, 1);
	//Segundos
	por_num( (seg/10), 21, 1);
	por_num( (seg%10), 25, 1);

	//COR DOS LEDS
	por_cor(red, green, blue);

}

int dividir_matriz( ){

	for(int a=0; a<=7; a++) //filas
		for(int b=0;b<=7;b++)//colunas
			for(int c=0;c<=2;c++) //cor
				div_0[a][b][c] = matriz_cor[a][b][c];

	for(int a=0; a<=7; a++)
		for(int b=0;b<=7;b++)
			for(int c=0;c<=2;c++)
				div_1[a][b][c] = matriz_cor[a][8+b][c];

	for(int a=0; a<=7; a++)
		for(int b=0;b<=7;b++)
			for(int c=0;c<=2;c++)
				div_2[a][b][c] = matriz_cor[a][16+b][c];

	for(int a=0; a<=7; a++)
		for(int b=0;b<=7;b++)
			for(int c=0;c<=2;c++)
				div_3[a][b][c] = matriz_cor[a][24+b][c];
}
/*
int main(){

	//	horas, minutos, segundos, cor(r, g ou b)
	rtc_small(01, 23, 45, 1, 1, 0);
	dividir_matriz(matriz_cor);

	//imprimir matriz
	   printf("Matriz final:\n");
	   for(int a=0; a<=7; a++) { //filas
		   for(int b=0;b<=7;b++){ //colunas
			   printf("%d  ", div_1[a][b][1]);
		   }
	      printf("\n");
	   }
}
*/

void loop(){



}