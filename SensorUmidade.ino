#include <Servo.h>
#define LR 12
#define LP 7

Servo meuservo;
int ang = 0;
char comando;

void setup(){
  Serial.begin(9600);
  meuservo.attach(4);
  pinMode(LR, OUTPUT); 
  pinMode(LP, OUTPUT);
}

void loop(){
 if (Serial.available())
  	comando = Serial.read();
  
  if(comando == 'S'){
  	 for(ang = 0; ang <= 180; ang++){
  		meuservo.write(ang);
    	delay(15);
    	Serial.println(ang);
       	digitalWrite(LR, HIGH);
       	digitalWrite(LP, LOW);
  	}
  
  	/*for(ang = 180; ang >= 0; ang--){
  		meuservo.write(ang);
    	delay(15);
    	Serial.println(ang);
      	digitalWrite(LR, HIGH);
      	digitalWrite(LP, LOW);
  	}*/
  }
  if(comando == 'F'){
    ang = 0;
    Serial.println("Parei!");
    digitalWrite(LP, HIGH);
    digitalWrite(LR, LOW);
  }
}