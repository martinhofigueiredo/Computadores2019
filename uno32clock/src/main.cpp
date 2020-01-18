#include "Arduino.h"
#include "clk_rtc.h"
#include "WirePIC32.h"

#define START_OF_DATA 0x10       //data markers
#define END_OF_DATA 0x20         //data markers
#define DEST1 0x30          //set destination I2C address (must match firmware in Colorduino module)
#define DEST2 0x40			//set destination I2C address (must match firmware in Colorduino module)
#define DEST3 0x50          //set destination I2C address (must match firmware in Colorduino module)
#define DEST4 0x60          //set destination I2C address (must match firmware in Colorduino module)
#define SCREENSIZEX 8            //num of LEDs accross
#define SCREENSIZEY 8            //num of LEDs down
#define SETCLOCK 1

byte display_byte[4][3][64] = {{0}};        //display array - 64 bytes x 3 colours 
byte matriz_cor[8][32][3] = {{0}};
byte segundos1 = 0, minutos1 = 0, horas1 = 0, diaSemana1 = 0, diaMes1 = 0, mes1 = 0, ano1 = 0;

int i;
int j;
int a;
int b;
int c;

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

//send data via I2C to a client
static byte BlinkM_sendBuffer(byte addr, byte col, byte* disp_data) {
  Wire.beginTransmission(addr);
  Wire.write(START_OF_DATA);
  Wire.write(col);
  Wire.write(disp_data, 64);
  Wire.write(END_OF_DATA);
  return Wire.endTransmission(false);
}

//send display buffer to display 
void update_display(byte addr, int n) {   
  BlinkM_sendBuffer(addr, 0, display_byte[n][0]);   
  BlinkM_sendBuffer(addr, 1, display_byte[n][1]);
  BlinkM_sendBuffer(addr, 2, display_byte[n][2]);
}

void por_num(int num, int x, int y, byte r, byte g, byte b){
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
void rtc_small(int horas, int min, int seg, int red, int green, int blue){

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
				{
				int p = (b*8) + a;
				//Serial.println(p);

				display_byte[0][c][p] = matriz_cor[a][b][c];
				display_byte[1][c][p] = matriz_cor[a][8+b][c];
				display_byte[2][c][p] = matriz_cor[a][16+b][c];
				display_byte[3][c][p] = matriz_cor[a][24+b][c];
				}
	/*
	Serial.print("display byte");
	for(a=0; a<=63; a++) {
		if(a % 8 == 0){
			Serial.println();
		}	
		Serial.print(display_byte[0][0][a]);		
		Serial.print("	");
	}
	Serial.println("Matriz final:\n");
	for(a=0; a<=7; a++) { //filas			
	   for(b=0;b<=7;b++){ //colunas			 
			Serial.print(matriz_cor[a][b][0]);				
	   		Serial.print("	");				   			
	   }			   
	   Serial.println();		     
	}*/		   
}

void setup()
{
	Wire.begin();
	Serial.begin(9600);
	if(SETCLOCK){
    	Serial.println("Horas (0 a 24): ");
        horas1 = leByte();
        Serial.println("Minutos (0 a 60): ");
        minutos1 = leByte();
		Serial.println("Segundos (0 a 60): ");
       	segundos1 = leByte();
        Serial.println("Dia da Semana (1 = Domingo a 7 = Sabado): ");
        diaSemana1 = leByte();
        Serial.println("Dia (0 a 31):");
        diaMes1 = leByte();
        Serial.println("Mes (0 a 12):");
        mes1 = leByte();
        Serial.println("Ano (0 a 99):");
        ano1 = leByte();
        write_horas(segundos1, minutos1, horas1, diaSemana1, diaMes1, mes1, ano1);
		Wire.endTransmission(false);
	}
}


void loop(){	
	read_horas(&segundos1, &minutos1, &horas1, &diaSemana1, &diaMes1, &mes1, &ano1);
	rtc_small(horas1, minutos1, segundos1, 255, 255, 255);
	dividir_matriz();

    Serial.print(horas1);
    Serial.print(":");
    //imprimir minutos
    Serial.print(minutos1);
    Serial.print(":");
    //imprimir segundos
    Serial.println(segundos1);
	
	update_display(DEST1, 3);
	update_display(DEST2, 2);
	update_display(DEST3, 1);
	update_display(DEST4, 0);
}