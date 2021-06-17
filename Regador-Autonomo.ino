/* ------------ REGA AUTONOMA ------------ */
//Programa desenvolvido para a disciplina de Intrododução a engenharia de computação

#include <Servo.h>
#inlcude <LiquidCrystal.h>

#define SensorUmipinoD 3
#define PinoServo 4
#define AtivacaoRele 2 //Definindo pino digital para o rele
#define TRIGGER 9 //Definindo pino para o trigger do sensor ultrassonico
#define ECHO 8 //Definindo pino para o echo do sensor ultrassonico
#define BuzzzerUltrassonico 7 //Definindo pino para o buzzer do sensor ultrassonico
#define REPOR_AGUA 15 //Distacia necessaria para repor a agua do reservatorio atraves do sensor ultrassonico 

int tempoChec = 1000;//Definindo variavel global do tipo int para usar na função delay, esse valor na função é equivalente a 1 hora. 
Servo meuservo;// Definindo o servo
int ang = 40;// Adicionando a variavel que vai ser o angulo do servo motor
double dPulso, distancia; // variaveis definidas para a distancia em CM e distancia dos pulsos do sensor ultrassonico
//LiquidCrystal lcd(x, y, z, a, b, c); //Define o lcd com e os pinos para ligar o display


void BombaDeAgua()
{
    int cont = 0;
    digitalWrite(AtivacaoRele, HIGH);//Ativa a bomba
    while(cont != 4 )
    {
      if(ang <= 40)
      {
        for(ang = 40; ang <= 100; ang++)
         {
            meuservo.write(ang);
            delay(15);
            Serial.println(ang);
          }
      }
      else if (ang >= 100)
      {
        for(ang = 100; ang >= 40; ang--)
         {
            meuservo.write(ang);
            delay(15);
            Serial.println(ang);
          }
      }
      cont++;
    }
    digitalWrite(AtivacaoRele, LOW);//Desativa a bomba
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
  //lcd.begin(16, 2); //Define o número de colunas e linhas do Display, supondo que seja 16x2
}

void loop() 
{ 
  
  if(digitalRead(SensorUmipinoD))
   {
     //Sem Umidade
      tempoChec = 1000;// Diminui o tempo de checagem para um segundo até que a planta seja regada
      BombaDeAgua();//Chama a função que ativa a bomba de agua
      Serial.print("Pouca Umidade\n");
    }
  else{
      //Com Umidade
       Serial.print("Nivel de umidade perfeita \n");
    }
    
  
  distancia = calculod(); // chama a função para calcular a distancia
  
  if(distancia >= REPOR_AGUA){
      tone(BuzzzerUltrassonico, 279.6); //Se for necessario repor a agua no reservatorio o buzzer vai avisar
  }else{
    noTone(BuzzzerUltrassonico); //Se nao, o buzzer vai se manter desligado
  }
  
  Serial.print("distancia: ");
  Serial.print(distancia);
  Serial.println(" cm");
  delay(tempoChec);//Pausa de tempo até a proxima checagem
}
