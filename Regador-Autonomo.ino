/* ------------ REGA AUTONOMA ------------ */
//Programa desenvolvido para a disciplina de Intrododução a engenharia de computação

#include <Servo.h>

#define SensorUmipinoD 3
#define PinoServo 4
#define AtivacaoRele 2 //Definindo pino digital para o rele
#define TRIGGER 9 //Definindo pino para o trigger do sensor ultrassonico
#define ECHO 8 //Definindo pino para o echo do sensor ultrassonico
#define BuzzzerUltrassonico 7 //Definindo pino para o buzzer do sensor ultrassonico
#define REPOR_AGUA 3 //Distacia necessaria para repor a agua do reservatorio atraves do sensor ultrassonico 

int tempoChec = 3600*1000;//Definindo variavel global do tipo int para usar na função delay, esse valor na função é equivalente a 1 hora. 
Servo meuservo;// Definindo o servo
int ang = 0;// Adicionando a variavel que vai ser o angulo do servo motor
double dPulso, distancia; // variaveis definidas para a distancia em CM e distancia dos pulsos do sensor ultrassonico

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

double calculod(){
    
  digitalWrite(TRIGGER, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER, LOW);
  dPulso= pulseIn(ECHO, HIGH);
                                /*A função calcula a distancia atraves das ondas de entrada e saida do sensor.
                                Retornando esse pulso que sera armazenado na variavel distancia.*/
  
  return  dPulso/58;
}

void setup() { 
  pinMode(AtivacaoRele, OUTPUT);// Deinindo como pin de saida
  pinMode(SensorUmipinoD, INPUT);
  meuservo.attach(PinoServo); // Porta que vai ser inserido o pino do servo motor
  Serial.begin(9600); //Porta serial, taxa de dados 9600 bps(bits por segundo) 
  pinMode(TRIGGER, OUTPUT); //Porta de saida do ultrassonico
  pinMode(ECHO, INPUT); //porta de entrada do ultrassonico
  pinMode(BuzzzerUltrassonico, OUTPUT); //porta do buzzer do ultrassonico
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

  distancia = calculod(); // chama a função para calcular a distancia
  
  if(distancia <= REPOR_AGUA){
      tone(BuzzzerUltrassonico, 279.6); //Se for necessario repor a agua no reservatorio o buzzer vai avisar
  }else{
    noTone(BuzzzerUltrassonico); //Se nao, o buzzer vai se manter desligado
  }
  
  Serial.print("distancia: ");
  Serial.print(distancia);
  Serial.println(" cm");
}
