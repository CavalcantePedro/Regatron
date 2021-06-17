/**
 ============================================================================
 Nome      : REGATRON
 Autores    : João Roberto de Oliveira Ferreira, Matheus Ferreira Miranda da Paixão, Pedro Lucas Valeriano de Mira e Pedro Ricardo Cavalcante Silva Filho.
 Descricao : Projeto realizado em grupo para a disciplina de Introdução à Engenharia da Computação. O qual consiste em um sistema de irrigação inteligente.
 ============================================================================
*/
#include <Servo.h>

// Definições de Pinos para implementações de módulos!
#define SensorUmipinoD 3
#define PinoServo 4
#define AtivacaoRele 2 

int tempoChec = 3600*1000;//Definindo variavel global do tipo int para usar na função delay, esse valor na função é equivalente a 1 hora. 
Servo meuservo;// Definindo o servo
int ang = 0;// Adicionando a variavel que vai ser o angulo do servo motor

void BombaDeAgua()
{
    digitalWrite(AtivacaoRele, HIGH);//Ativa a bomba
    delay(3000);//Tempo em que a bomba de água fica ligada.
    digitalWrite(AtivacaoRele, LOW);//Desativa a bomba
}

void ServoMotor()// Servo Motor vai segurar a mangueira que vai realizar a ação de aguar
{
  for(ang = 0; ang <= 180; ang++)
  {
      meuservo.write(ang);
      delay(15);
      Serial.println(ang);
  }
}

void setup() { 
  pinMode(AtivacaoRele, OUTPUT);// Definindo como pin de saida
  pinMode(SensorUmipinoD, INPUT);
  meuservo.attach(PinoServo); // Porta que vai ser inserido o pino do servo motor
  Serial.begin(9600); //Porta serial, taxa de dados 9600 bps(bits por segundo) 
}

void loop() 
{ 
  
  if(digitalRead(SensorUmipinoD))
   {
     //Sem Umidade
      tempoChec = 1000;// Diminui o tempo de checagem para um segundo até que a planta seja regada
      BombaDeAgua();//Chama a função que ativa a bomba de agua
      ServoMotor();// Chamada do servo para aguar a planta
      Serial.print("Pouca Umidade\n");
    }
  else{
      //Com Umidade
       tempoChec = 3600*1000; //Quando a planta é regada o delay volta a ser de 1 hora
       Serial.print("Nivel de umidade perfeita \n");
    }
    
  
    
  delay(tempoChec);//Pausa de tempo até a proxima checagem
}
