#include "Arduino.h"
#include "clk_rtc.h"
#include "WirePIC32.h"


#define START_OF_DATA 0x10       //data markers
#define END_OF_DATA 0x20         //data markers
#define DEST1 0x30          //set destination I2C address (must match firmware in Colorduino module)
#define DEST2 0x40			//set destination I2C address (must match firmware in Colorduino module)
#define DEST3 0x50          //set destination I2C address (must match firmware in Colorduino module)
#define DEST4 0x60          //set destination I2C address (must match firmware in Colorduino module)
#define SCREENSIZEX 8           //num of LEDs accross
#define SCREENSIZEY 32            //num of LEDs down

byte display_byte[4][3][64] = {{0}};        //display array - 64 bytes x 3 colours 
byte matriz_cor[8][32][3] = {{0}};
byte segundos1 = 0, minutos1 = 0, horas1 = 0, diaSemana1 = 0, diaMes1 = 0, mes1 = 0, ano1 = 0;
byte plasma[8][32][3] = {{0}};

int i;
int j;
int k;
int a;
int b;
int c;
char ch;
int bri=0;

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
bool ponto[5][3]=	{0, 0, 0, 	0, 0, 0, 	0, 0, 0, 	0, 0, 0, 	0, 1, 0};
bool celsius1[5][3]=	{0, 1, 0,	1, 0, 1,	0, 1, 0,	0, 0, 0,	0, 0, 0};
bool celsius2[5][3]=	{1, 1, 1,	1, 0, 0,	1, 0, 0,	1, 0, 0,	1, 1, 1};
bool fah1[5][7]=		{0, 1, 0,	1, 0, 1,	0, 1, 0,	0, 0, 0,	0, 0, 0};
bool fah2[5][7]=		{1, 1, 1,	1, 0, 0,	1, 1, 0,	1, 0, 0,	1, 0, 0};
bool la[5][3] =		{0, 1, 1, 	1, 0, 1, 	1, 1, 1, 	1, 0, 1, 	1, 0, 1};
bool lb[5][3] =		{1, 1, 0, 	1, 0, 1, 	1, 1, 0, 	1, 0, 1, 	1, 1, 1};
bool lc[5][3] =		{0, 1, 1, 	1, 0, 0, 	1, 0, 0, 	1, 0, 0, 	0, 1, 1};
bool ld[5][3] =		{1, 1, 0, 	1, 0, 1, 	1, 0, 1, 	1, 0, 1, 	1, 1, 0};
bool le[5][3] =		{1, 1, 1, 	1, 0, 0, 	1, 1, 0, 	1, 0, 0, 	1, 1, 1};
bool lf[5][3] =		{1, 1, 1, 	1, 0, 0, 	1, 1, 0, 	1, 0, 0, 	1, 0, 0};
bool lg[5][3] =		{0, 1, 1, 	1, 0, 0, 	1, 0, 1, 	1, 0, 1, 	0, 1, 1};
bool lh[5][3] =		{1, 0, 1, 	1, 0, 1, 	1, 1, 1, 	1, 0, 1, 	1, 0, 1};
bool li[5][1] =		{1, 1, 1, 1, 1};
bool lj[5][3] =		{0, 0, 1, 	0, 0, 1, 	0, 0, 1, 	1, 0, 1, 	1, 1, 1};
bool lk[5][3] =		{1, 0, 1, 	1, 0, 1, 	1, 1, 0, 	1, 0, 1, 	1, 0, 1};
bool ll[5][3] =		{1, 0, 0, 	1, 0, 0, 	1, 0, 0, 	1, 0, 0, 	1, 1, 1};
bool lm[5][5] =		{1, 0, 0, 0, 1, 	1, 1, 0, 1, 1,  	1, 0, 1, 0, 1,  	1, 0, 0, 0, 1,  	1, 0, 0, 0, 1};
bool ln[5][4] =		{1, 0, 0, 1, 	1, 1, 0, 1,		1, 0, 1, 1,  	1, 0, 0, 1,  	1, 0, 0, 1};
bool lo[5][3] =		{0, 1, 0, 	1, 0, 1, 	1, 0, 1, 	1, 0, 1, 	0, 1, 0};
bool lp[5][3] =		{1, 1, 0, 	1, 0, 1, 	1, 1, 1, 	1, 0, 0, 	1, 0, 0};
bool lq[5][4] =		{0, 1, 0, 0,	1, 0, 1, 0,		1, 0, 1, 0,		1, 0, 1, 1,		0, 1, 0, 1};
bool lr[5][3] =		{1, 1, 1, 	1, 0, 1, 	1, 1, 0, 	1, 0, 1, 	1, 0, 1};
bool ls[5][3] =		{1, 1, 1, 	1, 0, 0, 	1, 1, 1, 	0, 0, 1, 	1, 1, 1};
bool lt[5][3] =		{1, 1, 1, 	0, 1, 0, 	0, 1, 0, 	0, 1, 0, 	0, 1, 0};
bool lu[5][3] =		{1, 0, 1, 	1, 0, 1, 	1, 0, 1, 	1, 0, 1, 	1, 1, 1};
bool lv[5][3] =		{1, 0, 1, 	1, 0, 1, 	1, 0, 1, 	1, 0, 1, 	0, 1, 0};
bool lw[5][5] =		{1, 0, 1, 0, 1,		1, 0, 1, 0, 1,		1, 0, 1, 0, 1,		1, 0, 1, 0, 1,		0, 1, 0, 1, 0};
bool lx[5][3] =		{1, 0, 1, 	1, 0, 1, 	0, 1, 0, 	1, 0, 1, 	1, 0, 1};
bool ly[5][3] =		{1, 0, 1, 	1, 0, 1, 	1, 1, 1, 	0, 0, 1, 	1, 1, 0};
bool lz[5][3] =		{1, 1, 1, 	0, 0, 1, 	0, 1, 0, 	1, 0, 0, 	1, 1, 1};
//icons
bool tempint[8][5]= {0, 0, 0, 0, 0,	0, 0, 0, 0, 0,	0, 0, 0, 0, 0,	0, 0, 1, 0, 0,	0, 0, 1, 0, 0,	0, 1, 1, 1, 0,	0, 1, 1, 1, 0,	0, 0, 0, 0, 0};
bool tempext[8][5]= {0, 0, 1, 0, 0,	0, 1, 0, 1, 0,	0, 1, 0, 1, 0,	0, 1, 0, 1, 0,	0, 1, 0, 1, 0,	1, 0, 0, 0, 1,	1, 0, 0, 0, 1,	0, 1, 1, 1, 0};
bool dot[1]={1};

typedef struct
{
  unsigned char r;
  unsigned char g;
  unsigned char b;
} ColorRGB;

//a color with 3 components: h, s and v
typedef struct 
{
  unsigned char h;
  unsigned char s;
  unsigned char v;
} ColorHSV;

unsigned char plasma1[SCREENSIZEX][SCREENSIZEY];
long paletteShift;

void HSVtoRGB(void *vRGB, void *vHSV) 
{
  float r, g, b, h, s, v; //this function works with floats between 0 and 1
  float f, p, q, t;
  int i;
  ColorRGB *colorRGB=(ColorRGB *)vRGB;
  ColorHSV *colorHSV=(ColorHSV *)vHSV;

  h = (float)(colorHSV->h / 256.0);
  s = (float)(colorHSV->s / 256.0);
  v = (float)(colorHSV->v / 256.0);

  //if saturation is 0, the color is a shade of grey
  if(s == 0.0) {
    b = v;
    g = b;
    r = g;
  }
  //if saturation > 0, more complex calculations are needed
  else
  {
    h *= 6.0; //to bring hue to a number between 0 and 6, better for the calculations
    i = (int)(floor(h)); //e.g. 2.7 becomes 2 and 3.01 becomes 3 or 4.9999 becomes 4
    f = h - i;//the fractional part of h

    p = (float)(v * (1.0 - s));
    q = (float)(v * (1.0 - (s * f)));
    t = (float)(v * (1.0 - (s * (1.0 - f))));

    switch(i)
    {
      case 0: r=v; g=t; b=p; break;
      case 1: r=q; g=v; b=p; break;
      case 2: r=p; g=v; b=t; break;
      case 3: r=p; g=q; b=v; break;
      case 4: r=t; g=p; b=v; break;
      case 5: r=v; g=p; b=q; break;
      default: r = g = b = 0; break;
    }
  }
  colorRGB->r = (int)(r * 255.0);
  colorRGB->g = (int)(g * 255.0);
  colorRGB->b = (int)(b * 255.0);
}


unsigned int RGBtoINT(void *vRGB)
{
  ColorRGB *colorRGB=(ColorRGB *)vRGB;

  return (((unsigned int)colorRGB->r)<<16) + (((unsigned int)colorRGB->g)<<8) + (unsigned int)colorRGB->b;
}


float dist(float a, float b, float c, float d) 
{
  return sqrt((c-a)*(c-a)+(d-b)*(d-b));
}


void plasma_morph()
{
  unsigned char x,y;
  float value;
  ColorRGB colorRGB;
  ColorHSV colorHSV;

  for(x = 0; x <SCREENSIZEX; x++) {
    for(y = 0; y < SCREENSIZEY; y++)
      {
	value = sin(dist(x + paletteShift, y, 128.0, 128.0) / 8.0)
	  + sin(dist(x, y, 64.0, 64.0) / 8.0)
	  + sin(dist(x, y + paletteShift / 7, 192.0, 64) / 7.0)
	  + sin(dist(x, y, 192.0, 100.0) / 8.0);
	colorHSV.h=(unsigned char)((value) * 128)&0xff;
	colorHSV.s=255; 
	colorHSV.v=255;
	HSVtoRGB(&colorRGB, &colorHSV);
	
    for(b=0;b<=31;b++)//colunas
			for(a=0;a<=7;a++) //cor
			{
				plasma[a][b][0]=colorRGB.r;
                plasma[a][b][1]=colorRGB.g;
                plasma[a][b][2]=colorRGB.b;	
			}
      }
  }
  paletteShift++;
}

 //plasma setup - start with morphing plasma, but allow going to color cycling if desired.
void plasma_setup()
{
   paletteShift=128000;
  unsigned char bcolor;

  for(unsigned char x = 0; x < SCREENSIZEX; x++)
    for(unsigned char y = 0; y < SCREENSIZEY; y++)
    {
      //the plasma buffer is a sum of sines
      bcolor = (unsigned char)
      (
            128.0 + (128.0 * sin(x*8.0 / 16.0))
          + 128.0 + (128.0 * sin(y*8.0 / 16.0))
      ) / 2;
      plasma1[x][y] = bcolor;
    }
}



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
		case 11:
			matriz_cor[y+j][x+i][0] = (ponto[j][i]) ? r : 0;
			matriz_cor[y+j][x+i][1] = (ponto[j][i]) ? g : 0;
			matriz_cor[y+j][x+i][2] = (ponto[j][i]) ? b : 0;
		   break;
		case 12:
			matriz_cor[y+j][x+i][0] = (celsius1[j][i]) ? r : 0;
			matriz_cor[y+j][x+i][1] = (celsius1[j][i]) ? g : 0;
			matriz_cor[y+j][x+i][2] = (celsius1[j][i]) ? b : 0;
		   break;
		case 13:
			matriz_cor[y+j][x+i][0] = (celsius2[j][i]) ? r : 0;
			matriz_cor[y+j][x+i][1] = (celsius2[j][i]) ? g : 0;
			matriz_cor[y+j][x+i][2] = (celsius2[j][i]) ? b : 0;
		   break;
		}
	}
}

void limpar(){
	for (i=0; i<=7; i++) //filas
		for (j=0; j<=31; j++) //colunas
			for (k=0; k<=2; k++)
				matriz_cor[i][j][k]=0;

}

//temperatura
void por_temp(){
	int temp = rtc_temp()*100;
	por_num( (temp/1000), 1, 1, 255, 255, 255); //dezenas
	por_num( ((temp/100)%10) , 5, 1, 255, 255, 255); //unidades
	por_num(11, 8, 1, 255, 255, 255);	//ponto
	por_num( ((temp/10)%10) , 11, 1, 255, 255, 255); //decimal dezenas
	por_num( (temp%10) , 15, 1, 255, 255, 255); //decimal unidades
	por_num( 12, 19, 1, 255, 255, 255); //celsius1
	por_num( 13, 23, 1, 255, 255, 255); //celsius2

	for (i=0; i<=4; i++)
		for (j=0; j<=7; j++){
			matriz_cor[j][27+i][0] = ( (tempext[j][i]) ? 255 : 0)+ ( (tempint[j][i]) ? 255 : 0);
			matriz_cor[j][27+i][1] = ( (tempext[j][i]) ? 255 : 0);
			matriz_cor[j][27+i][2] = ( (tempext[j][i]) ? 255 : 0);
		}
}

//relógio
void rtc_small(int horas, int min, int seg, int red, int green, int blue){

	//pisca-pisca
	if(seg%2 == 0){
	por_num(10, 8, 1, red, green, blue);
	por_num(10, 18, 1, red, green, blue);
	}
	else{
		limpar();
	}

	switch(seg/10){
		case 1:
			matriz_cor[5][29][1] = (dot[0]) ? 255 : 0;
		break;
		case 2:
			matriz_cor[5][29][1] = (dot[0]) ? 255 : 0;
			matriz_cor[4][29][1] = (dot[0]) ? 255 : 0;
		break;
		case 3:
			matriz_cor[5][29][1] = (dot[0]) ? 255 : 0;
			matriz_cor[4][29][1] = (dot[0]) ? 255 : 0;
			matriz_cor[3][29][1] = (dot[0]) ? 255 : 0;
		break;
		case 4:
			matriz_cor[5][29][1] = (dot[0]) ? 255 : 0;
			matriz_cor[4][29][1] = (dot[0]) ? 255 : 0;
			matriz_cor[3][29][1] = (dot[0]) ? 255 : 0;
			matriz_cor[2][29][1] = (dot[0]) ? 255 : 0;
		break;
		case 5:
			matriz_cor[5][29][1] = (dot[0]) ? 255-bri : 0;
			matriz_cor[4][29][1] = (dot[0]) ? 255 : 0;
			matriz_cor[3][29][1] = (dot[0]) ? 255 : 0;
			matriz_cor[2][29][1] = (dot[0]) ? 255 : 0;
			matriz_cor[1][29][1] = (dot[0]) ? 255 : 0;
		break;
		case 0:
			matriz_cor[5][29][1] = 0;
			matriz_cor[4][29][1] = 0;
			matriz_cor[3][29][1] = 0;
			matriz_cor[2][29][1] = 0;
			matriz_cor[1][29][1] = 0;
		break;
	}
	
	//Horas
	por_num( (horas/10), 1, 1, red, green, blue);
	por_num( (horas%10), 5, 1, red, green, blue);
	//Minutos
	por_num( (min/10), 11, 1, red, green, blue);
	por_num( (min%10), 15, 1, red, green, blue);
	//Segundos
	por_num( (seg/10), 21, 1, red, green, blue);
	por_num( (seg%10), 25, 1, red, green, blue);

}
void brightness(int bri){
	for(a=0; a<=7; a++) //filas
		for(b=0;b<=31;b++)//colunas
			for(c=0;c<=2;c++) //cor
			{
				if(matriz_cor[a][b][c] != 0)
					matriz_cor[a][b][c]=matriz_cor[a][b][c]-bri;	
			}
}
void dividir_matriz(){

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
	plasma_setup();
}

void loop(){
	plasma_morph();	
	if(Serial.available()){
		ch = Serial.read();
	}

	switch(ch){
		case 's':{
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
			ch = NULL;
			break;
		}
		default:{
			read_horas(&segundos1, &minutos1, &horas1, &diaSemana1, &diaMes1, &mes1, &ano1);
			rtc_small(horas1, minutos1, segundos1, 255, 255, 255);
			Serial.print(horas1);
    		Serial.print(":");
    		Serial.print(minutos1);
    		Serial.print(":");
    		Serial.println(segundos1);
			break;
		}
		case 't':{
			por_temp();
			Serial.println("temperatura");
			break;
		}
		case 'f':{

			break;
		}
		case 'd':{

		}
		case 'b':{
			bri=bri-50;
			ch=NULL;
			break;
		}
		case 'p':{
			for (int i = 0; i < 8; i++){
				for (int j = 0; j < 32; j++){
					matriz_cor[i][j][0]=plasma[i][j][0];
					matriz_cor[i][j][1]=plasma[i][j][1];
					matriz_cor[i][j][2]=plasma[i][j][2];
				}	
			}
			break;
		}
	}
	brightness(bri);
	dividir_matriz();
	
	update_display(DEST1, 3);
	update_display(DEST2, 2);
	update_display(DEST3, 1);
	update_display(DEST4, 0);
	limpar();
}