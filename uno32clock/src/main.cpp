#include "Arduino.h"
#include "clk_rtc.h"
#include "Wire.h"

void setup()
{
	Wire.begin();
	Serial.begin(9600);
}


//int matriz[8][32]= {{0}};
byte matriz_cor[8][32][3]= {{0}};
int i;
int j;
int a;
int b;
int c;
byte divido[8][8][3][4];

bool zero[5][3]= 	{1, 1, 1, 	1, 0, 1, 	1, 0, 1, 	1, 0, 1, 	1, 1, 1};
bool um[5][3]= 		{0, 1, 0, 	1, 1, 0, 	0, 1, 0, 	0, 1, 0, 	1, 1, 1};
bool dois[5][3]= 	{1, 1, 1, 	0, 0, 1, 	1, 1, 1, 	1, 0, 0, 	1, 1, 1};
bool tres[5][3]= 	{1, 1, 1, 	0, 0, 1, 	1, 1, 1, 	0, 0, 1, 	1, 1, 1};
bool quatro[5][3]= 	{1, 0, 1, 	1, 0, 1,	1, 1, 1, 	0, 0, 1, 	0, 0, 1};
bool cinco[5][3]= 	{1, 1, 1, 	1, 0, 0, 	1, 1, 1, 	0, 0, 1, 	1, 1, 1};
bool seis[5][3]= 	{1, 1, 1, 	1, 0, 0, 	1, 1, 1, 	1, 0, 1, 	1, 1, 1};
bool sete[5][3]= 	{1, 1, 1, 	0, 0, 1, 	0, 0, 1, 	0, 0, 1, 	0, 0, 1};
bool oito[5][3]= 	{1, 1, 1, 	1, 0, 1, 	1, 1, 1, 	1, 0, 1, 	1, 1, 1};
bool nove[5][3]= 	{1, 1, 1, 	1, 0, 1, 	1, 1, 1, 	0, 0, 1, 	1, 1, 1};
bool doispontos[5][3]={0, 0, 0, 	0, 1, 0, 	0, 0, 0, 	0, 1, 0, 	0, 0, 0};


int por_num(int num, int x, int y, byte r, byte g, byte b){
	
	
for (i=0; i<=2; i++) //filas
	for (j=0; j<=4; j++) //colunas
	{
	switch (num){
		case 0:
		   	matriz_cor[y+j][x+i][0] = (zero[j][i]) ? r : 0;
			matriz_cor[y+j][x+i][1] = (zero[j][i]) ? g : 0;
			matriz_cor[y+j][x+i][2] = (zero[j][i]) ? b : 0;			
	   break;
	   case 1:
		   	matriz_cor[y+j][x+i][0] = (um[j][i]) ? r : 0;
			matriz_cor[y+j][x+i][1] = (um[j][i]) ? g : 0;
			matriz_cor[y+j][x+i][2] = (um[j][i]) ? b : 0;
	   	   break;
	   case 2:
		   	matriz_cor[y+j][x+i][0] = (dois[j][i]) ? r : 0;
			matriz_cor[y+j][x+i][1] = (dois[j][i]) ? g : 0;
			matriz_cor[y+j][x+i][2] = (dois[j][i]) ? b : 0;
		   break;
	   case 3:
		   	matriz_cor[y+j][x+i][0] = (tres[j][i]) ? r : 0;
			matriz_cor[y+j][x+i][1] = (tres[j][i]) ? g : 0;
			matriz_cor[y+j][x+i][2] = (tres[j][i]) ? b : 0;
		   break;
	   case 4:
		   	matriz_cor[y+j][x+i][0] = (quatro[j][i]) ? r : 0;
			matriz_cor[y+j][x+i][1] = (quatro[j][i]) ? g : 0;
			matriz_cor[y+j][x+i][2] = (quatro[j][i]) ? b : 0;
		   break;
	   case 5:
		   	matriz_cor[y+j][x+i][0] = (cinco[j][i]) ? r : 0;
			matriz_cor[y+j][x+i][1] = (cinco[j][i]) ? g : 0;
			matriz_cor[y+j][x+i][2] = (cinco[j][i]) ? b : 0;
		   break;
	   case 6:
		   	matriz_cor[y+j][x+i][0] = (seis[j][i]) ? r : 0;
			matriz_cor[y+j][x+i][1] = (seis[j][i]) ? g : 0;
			matriz_cor[y+j][x+i][2] = (seis[j][i]) ? b : 0;
		   break;
	   case 7:
		   	matriz_cor[y+j][x+i][0] = (sete[j][i]) ? r : 0;
			matriz_cor[y+j][x+i][1] = (sete[j][i]) ? g : 0;
			matriz_cor[y+j][x+i][2] = (sete[j][i]) ? b : 0;
		   break;
	   case 8:
		   	matriz_cor[y+j][x+i][0] = (oito[j][i]) ? r : 0;
			matriz_cor[y+j][x+i][1] = (oito[j][i]) ? g : 0;
			matriz_cor[y+j][x+i][2] = (oito[j][i]) ? b : 0;
		   break;
	   case 9:
		   	matriz_cor[y+j][x+i][0] = (nove[j][i]) ? r : 0;
			matriz_cor[y+j][x+i][1] = (nove[j][i]) ? g : 0;
			matriz_cor[y+j][x+i][2] = (nove[j][i]) ? b : 0;
		   break;
	   case 10:
		   	matriz_cor[y+j][x+i][0] = (doispontos[j][i]) ? r : 0;
			matriz_cor[y+j][x+i][1] = (doispontos[j][i]) ? g : 0;
			matriz_cor[y+j][x+i][2] = (doispontos[j][i]) ? b : 0;
		   break;
		}
	}
}

//relógio
int rtc_small(int horas, int min, int seg, int red, int green, int blue){

	//Horas
	por_num( (horas/10), 1, 1, red, green, blue);
	por_num( (horas%10), 5, 1, red, green, blue);
	//dois pontos
	por_num(10, 8, 1, red, green, blue);
	//Minutos
	por_num( (min/10), 11, 1, red, green, blue);
	por_num( (min%10), 15, 1, red, green, blue);
	//dois pontos
	por_num(10, 18, 1, red, green, blue);
	//Segundos
	por_num( (seg/10), 21, 1, red, green, blue);
	por_num( (seg%10), 25, 1, red, green, blue);

}

void dividir_matriz( ){

	for(a=0; a<=7; a++) //filas
		for(b=0;b<=7;b++)//colunas
			for(c=0;c<=2;c++) //cor
				divido[a][b][c][0] = matriz_cor[a][b][c];

	for(a=0; a<=7; a++)
		for(b=0;b<=7;b++)
			for(c=0;c<=2;c++)
				divido[a][b][c][1] = matriz_cor[a][8+b][c];

	for(a=0; a<=7; a++)
		for(b=0;b<=7;b++)
			for(c=0;c<=2;c++)
				divido[a][b][c][2] = matriz_cor[a][16+b][c];

	for(a=0; a<=7; a++)
		for(b=0;b<=7;b++)
			for(c=0;c<=2;c++)
				divido[a][b][c][3] = matriz_cor[a][24+b][c];
}


void loop(){

	rtc_small(rtc_horas(), rtc_min(),rtc_seg(), 255, 255, 255);
	dividir_matriz();

	//imprimir horas
    Serial.print(rtc_horas());
    Serial.print(":");

    //imprimir minutos
    Serial.print(rtc_min());
    Serial.print(":");

    //imprimir segundos
    Serial.println(rtc_seg());

		Serial.println("Matriz final:\n");
		for(a=0; a<=7; a++) { //filas
		   for(b=0;b<=7;b++){ //colunas
				Serial.print(divido[a][b][0][0]);
		   		Serial.print("	");	
		   }
	      Serial.println();
	   }
}