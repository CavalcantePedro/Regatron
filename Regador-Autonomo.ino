/**
 ============================================================================
 Nome: REGATRON
 Autores: João Roberto de Oliveira Ferreira, Matheus Ferreira Miranda da Paixão, Pedro Lucas Valeriano de Mira e Pedro Ricardo Cavalcante Silva Filho.
 Descricao: Projeto realizado em grupo para a disciplina de Introdução à Engenharia da Computação. O qual consiste em um sistema de irrigação inteligente.
 ============================================================================
*/

#include <Servo.h>
#include <LiquidCrystal.h>

#define SensorUmipinoD 3
#define PinoServo 4
#define AtivacaoRele 2 //Definindo pino digital para o rele
#define TRIGGER 9 //Definindo pino para o trigger do sensor ultrassonico
#define ECHO 8 //Definindo pino para o echo do sensor ultrassonico
#define BuzzzerUltrassonico 7 //Definindo pino para o buzzer do sensor ultrassonico
#define REPOR_AGUA 15 //Distacia necessaria para repor a agua do reservatorio atraves do sensor ultrassonico 
// Angulos que são flexiveis, de acordo com o vaso utilizado muda, como o vaso que usamos foi pequeno os angulos foram esses
#define ANGULO_MIN 40
#define ANGULO_MAX 100
// Movimento realizado pelo servo motor, o qual estará acoplado com uma mangueira
#define QTD_MOV_SERVO 4
// Frequencia tocada pelo buzzer
#define SOM 279.6
//Definindo variavel global para usar na função delay, o qual funciona de 1 em 1 segundo, checando a temperatura da planta
#define TEMPO_CHEC  1000
//Definindo o tempo de execução do movimento do servo motor
#define TEMPO_EXE 15

 
Servo meuservo;// Definindo o servo
int ang = 40;// Adicionando a variavel que vai ser o angulo do servo motor
double dPulso, distancia; // variaveis definidas para a distancia em CM e distancia dos pulsos do sensor ultrassonico
LiquidCrystal lcd(13, 12, 11, 10, 6, 5); //Define o lcd e os pinos para ligar o display


void BombaDeAgua()
{
  int cont = 0;
  digitalWrite(AtivacaoRele, HIGH);//Ativa a bomba de agua e começa o processo de irrigação
  while(cont != QTD_MOV_SERVO )
  {
    if(ang <= ANGULO_MIN)
    {
      for(ang = ANGULO_MIN; ang <= ANGULO_MAX; ang++)
       {
          meuservo.write(ang);
          delay(TEMPO_EXE);
          Serial.println(ang);
        }
    }
    else if (ang >= ANGULO_MAX)
    {
      for(ang = ANGULO_MAX; ang >= ANGULO_MIN; ang--)
       {
          meuservo.write(ang);
          delay(TEMPO_EXE);
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
  dPulso = pulseIn(ECHO, HIGH);
                                /*A função calcula a distancia atraves das ondas de entrada e saida do sensor.
                                Retornando esse pulso que sera armazenado na variavel distancia.*/
  
  return  dPulso/58; // Cálculo padrão para a conversão do tempo em centímetros 
}

void limpaTela() { //Função que limpa a tela do lcd e exibe o logo.
  lcd.clear();
  lcd.home();
  lcd.print("    Regatron");
}

void setup() { 
  pinMode(AtivacaoRele, OUTPUT);// Definindo como pin de saida
  pinMode(SensorUmipinoD, INPUT);// Sensor de Umidade Definido
  meuservo.attach(PinoServo); // Porta que vai ser inserido o pino do servo motor
  Serial.begin(9600); //Porta serial, taxa de dados 9600 bps(bits por segundo) 
  pinMode(TRIGGER, OUTPUT); //Porta de saida do ultrassonico
  pinMode(ECHO, INPUT); //porta de entrada do ultrassonico
  pinMode(BuzzzerUltrassonico, OUTPUT); //porta do buzzer do ultrassonico
  lcd.begin(16, 2); //Define o número de colunas e linhas do Display, supondo que seja 16x2
  lcd.print("    Regatron");
}

void loop() 
{ 
  
  if(digitalRead(SensorUmipinoD))
  {
    limpaTela();
    lcd.setCursor(0, 1);
    lcd.print("Regando...");
    //Sem Umidade
    BombaDeAgua();//Chama a função que ativa a bomba de agua
    Serial.print("Pouca Umidade\n");
     
    // Colocar quando estiver regando! tipo Regando com a animação dos três pontos ...
  }
  else{
      //Com Umidade
      Serial.print("Nivel de umidade perfeita \n");
      limpaTela();
      lcd.setCursor(0, 1);
      lcd.print("Umidade Perfeita");
    }
    
  
  distancia = calculod(); // chama a função para calcular a agua do reservatorio;
  
  if(distancia >= REPOR_AGUA){
    limpaTela();
    lcd.setCursor(0, 1);
    lcd.print("  REPOR AGUA!");
    tone(BuzzzerUltrassonico, SOM); //Se for necessario repor a agua no reservatorio o buzzer vai avisar
  }else{
    noTone(BuzzzerUltrassonico); //Se nao, o buzzer vai se manter desligado
  }
  
  limpaTela(); //Ainda n sei se vai ser necessario, só vendo na pratica quando vai precisar limpar a tela;
  Serial.print("distancia: ");
  Serial.print(distancia);
  Serial.println(" cm");
  delay(TEMPOCHEC);//Pausa de tempo até a proxima checagem
}
