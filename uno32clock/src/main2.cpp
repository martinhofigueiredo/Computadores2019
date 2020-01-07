#include "Arduino.h"
#include "Wire.h"
#include "clk_temp.h"

float temp;

void setup()
{
  Wire.begin();
  Serial.begin(9600);
}

void loop(){

    //imprimir horas
    Serial.print(rtc_horas());
    Serial.print(":");

    //imprimir minutos
    Serial.print(rtc_min());
    Serial.print(":");

    //imprimir segundos
    Serial.println(rtc_seg());

    //Dia da Semana
    //legenda: 1-domingo; 2-segunda; 3-terça; 4-quarta; 5-quinta; 6-sexta;
    Serial.print(" Dia da Semana: ");
    Serial.println(rtc_diasem());

    //DATA
    Serial.print(rtc_diames());
    Serial.print("/");
    Serial.print(rtc_mes());
    Serial.print("/");
    Serial.println(rtc_ano());


    //imprimir temperatura
    //nota:declarar float temp
    temp=rtc_temp();
    Serial.print(temp);
    Serial.println(" ºC");
  
  }