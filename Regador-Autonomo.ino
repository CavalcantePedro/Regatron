/* ------------ REGA AUTONOMA ------------ */
//Programa desenvolvido para a disciplina de Intrododução a engenharia de computação

#define SensorUmipinoA A0 //Definindo pino analogico do sensor de umidade
#define SensorUmipinoD 2 //Definindo pino digital do sensor de umidade
#define AtivacaoRele 4 //Definindo pino digital para o rele
int tempoChec = 3600*1000;//Definindo variavel global do tipo int para usar na função delay, esse valor na função é equivalente a 1 hora.

void setup() 
{ 
  pinMode(SensorUmipinoD, INPUT); //Definindoo como pino de entrada
  pinMode(AtivacaoRele, OUTPUT);// Deinindo como pin de saida
  Serial.begin(9600); //Porta serial, taxa de dados 9600 bps(bits por segundo)  
}

void loop() 
{ 
  
  Serial.print(analogRead(SensorUmipinoA));
  Serial.print("\n");
  
  if (analogRead(SensorUmipinoA) <= 420 && analogRead(SensorUmipinoA) >250)
  {
    //Nivel de umidade perfeito
    tempoChec = 3600*1000; //Quando a planta é regada o delay volta a ser de 1 hora
    Serial.print("Nivel de umidade perfeita \n");
    }
 
  else if (analogRead(SensorUmipinoA)< 249)
  {
    //Muita umidade
    Serial.print("Muita umidade\n");
    }
  
  else
  {
    //Pouca umidade
    tempoChec = 1000;// Diminui o tempo de checagem para um segundo até que a planta seja regada
    BombaDeAgua();//Chama a função que ativa a bomba de agua 
    Serial.print("Pouca Umidade\n");
    }
    
  delay(tempoChec);//Pausa de tempo até a proxima checagem

}

void BombaDeAgua()
{
    digitalWrite(AtivacaoRele, HIGH);//Ativa a bomba
    delay(3000);//Tempo em que a bomba de água fica ligada.
    digitalWrite(AtivacaoRele, LOW);//Desativa a bomba
}
