#include "Arduino.h"
#include "Wire.h"

#define endereco_RTC  0x68
#define endereco_Temperatura_MSB  0x11
#define endereco_Temperatura_LSB  0x12
#define BUFSIZE 10

char cmd[BUFSIZE];
int pos = 0;
float temp=0;

byte temp_msb, temp_lsb; 
byte segundos = 0, minutos = 0, horas = 0, diaSemana = 0, diaMes = 0, mes = 0, ano = 0;

// Converte números em decimal para binário
byte decBin(byte val) {return( (val/10*16) + (val%10) );}
// Converte números em binário para decimal
byte binDec(byte val) {return( (val/16*10) + (val%16) );}

//ler as horas do RTC
void read_horas(byte *segundos, byte *minutos, byte *horas, byte *diaSemana, byte *diaMes, byte *mes, byte *ano)
{
  Wire.beginTransmission(endereco_RTC);
  Wire.write(0); // muda registo do RTC para 00h
  Wire.endTransmission();
  Wire.requestFrom(endereco_RTC, 7);
  // 7 bytes de dados a começar no registo 00h
  *segundos = binDec(Wire.read() & 0x7f);
  *minutos = binDec(Wire.read());
  *horas = binDec(Wire.read() & 0x3f);
  *diaSemana = binDec(Wire.read());
  *diaMes = binDec(Wire.read());
  *mes = binDec(Wire.read());
  *ano = binDec(Wire.read());
}

//ler a temperatura
//nota:declarar float temp
float rtc_temp()
{ 
  //MSB
  Wire.beginTransmission(endereco_RTC);
  Wire.write(endereco_Temperatura_MSB);
  Wire.endTransmission();

  Wire.requestFrom(endereco_RTC, 1);
  temp_msb = Wire.read();
  //******debugging******
  /*Serial.print(temp_msb);
  Serial.print("  /  ");
  Serial.print(temp_msb, BIN);
  Serial.print("  /  ");
  Serial.print(temp_msb, DEC);
  Serial.println("  /MSB  ");*/

  //LSB
  Wire.beginTransmission(endereco_RTC);
  Wire.write(endereco_Temperatura_LSB);
  Wire.endTransmission();
  //******debugging******
  /*Serial.print(temp_lsb);
  Serial.print("  /  ");
  Serial.print(temp_lsb, BIN);
  Serial.print("  /  ");
  Serial.print(temp_lsb, DEC);
  Serial.println("  /LSB  ");*/

  Wire.requestFrom(endereco_RTC, 1);
  temp_lsb = Wire.read() >> 6;
  
  temp = float(temp_msb) + float( temp_lsb ) / float(4);
  return temp;
}

//horas
int rtc_horas(){
  
  read_horas(&segundos, &minutos, &horas, &diaSemana, &diaMes, &mes,
  &ano);

  return(horas);
}
//minutos
int rtc_min(){
  
  read_horas(&segundos, &minutos, &horas, &diaSemana, &diaMes, &mes,
  &ano);
  
  return(minutos);
}
//segundos
int rtc_seg(){
  
  read_horas(&segundos, &minutos, &horas, &diaSemana, &diaMes, &mes,
  &ano);
  
  return(segundos);
}

//dia da semana(dom, seg, ter, qua, qui, sex, sab)
    //legenda: 1-domingo; 2-segunda; 3-terça; 4-quarta; 5-quinta; 6-sexta; 
int rtc_diasem(){

  read_horas(&segundos, &minutos, &horas, &diaSemana, &diaMes, &mes,
  &ano);
  return(diaSemana);
}

//numero do dia
int rtc_diames(){
read_horas(&segundos, &minutos, &horas, &diaSemana, &diaMes, &mes,
  &ano);
  return(diaMes);
}
//numero do mes
int rtc_mes(){
read_horas(&segundos, &minutos, &horas, &diaSemana, &diaMes, &mes,
  &ano);
  return(mes);
}
//numero do ano
int rtc_ano(){
read_horas(&segundos, &minutos, &horas, &diaSemana, &diaMes, &mes,
  &ano);
  return(ano);
}

/*
//ler bytes do terminal (desnecessário)***
byte leByte()
{
  while (!Serial.available());
  byte reading = 0;
  byte incomingByte = Serial.read();
  while (incomingByte != '\n')
  {
    if (incomingByte >= '0' && incomingByte <= '9')
      reading = reading * 10 + (incomingByte - '0');
    else;
    incomingByte = Serial.read();
  }
  Serial.flush();
  Serial.print("\n");
  return reading;
}  
// acerta hora e data (desnecessário)***
void write_horas(byte segundos, byte minutos, byte horas, byte diaSemana, byte diaMes, byte mes, byte ano)
{
  Wire.beginTransmission(endereco_RTC);
  Wire.write(0); // configura de forma ao 1º byte acertar os segundos
  Wire.write(decBin(segundos)); // acerta segundos
  Wire.write(decBin(minutos)); // acerta minutos
  Wire.write(decBin(horas)); // acerta horas
  Wire.write(decBin(diaSemana)); // acerta diaSemana (1=Domingo, 7=Sabado)
  Wire.write(decBin(diaMes)); // acerta diaMes (1 a 31)
  Wire.write(decBin(mes)); // acerta mes
  Wire.write(decBin(ano)); // acerta ano (0 a 99)
  Wire.endTransmission();
}
//imprimir as horas (desnecessário)***
void print_horas()
{
  read_horas(&segundos, &minutos, &horas, &diaSemana, &diaMes, &mes,
  &ano);
  Serial.print(horas, DEC);
  Serial.print(":");
  if (minutos<10)
  {
    Serial.print("0");
  }
  Serial.print(minutos, DEC);
  Serial.print(":");
  if (segundos<10)
  {
    Serial.print("0");
  }
  Serial.print(segundos, DEC);
  Serial.print(" ");
  if (diaMes<10)
  {
    Serial.print("0");
  }
  Serial.print(diaMes, DEC);
  Serial.print("/");
  if (mes<10)
  {
    Serial.print("0");
  }
  Serial.print(mes, DEC);
  Serial.print("/");
  if (ano<10)
  {
    Serial.print("0");
  }
  Serial.print(ano, DEC);
  Serial.print(" Dia da Semana: ");
  switch(diaSemana)
  {
    case 1:
      Serial.println("Domingo");
      break;
    case 2:
      Serial.println("Segunda");
      break;
    case 3:
      Serial.println("Terça");
      break;
    case 4:
      Serial.println("Quarta");
      break;
    case 5:
      Serial.println("Quinta");
      break;
    case 6:
      Serial.println("Sexta");
      break;
    case 7:
      Serial.println("Sabado");
      break;
 }
}
*/