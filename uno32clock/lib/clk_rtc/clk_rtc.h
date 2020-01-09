// Converte números em decimal para binário
byte decBin(byte val);
// Converte números em binário para decimal
byte binDec(byte val);

//ler as horas do RTC
void read_horas(byte *segundos, byte *minutos, byte *horas, byte *diaSemana, byte *diaMes, byte *mes, byte *ano);

//ler a temperatura
//nota:declarar float temp
float rtc_temp();

//*****RELÓGIO*****
//horas
int rtc_horas();
//minutos
int rtc_min();
//segundos
int rtc_seg();

//dia da semana (dom, seg, ter, qua, qui, sex, sab)
int rtc_diasem();

//numero do dia
int rtc_diames();
//numero do mes
int rtc_mes();
//numero do ano
int rtc_ano();

/*
//ler bytes do terminal (desnecessário)***
byte leByte(); 
// acerta hora e data (desnecessário)***
void write_horas(byte segundos, byte minutos, byte horas, byte diaSemana, byte diaMes, byte mes, byte ano);
//imprimir as horas (desnecessário)***
void print_horas();
*/