#include "IRremote.h"
#include <Servo.h>

int receiver = 11;

IRrecv irrecv(receiver);     // create instance of 'irrecv'
decode_results results;      // create instance of 'decode_results'
Servo myservo;               // create instance of 'Servo'

/* 
 *  describes the Remote IR codes and 
 *  takes action based on IR code received  
 */
void translateIR(){

  switch(results.value){
    case 0xFF18E7: digitalWrite(2, HIGH);  digitalWrite(3, HIGH); digitalWrite(4, HIGH); 
         digitalWrite(5, HIGH);  digitalWrite(6, HIGH); digitalWrite(7, HIGH); myservo.write(90); break; //go forward
    case 0xFF10EF: Serial.println("4"); myservo.write(180); delay(1000); myservo.write(90); break; //left turn
    case 0xFF5AA5: Serial.println("6"); myservo.write(0); delay(1000); myservo.write(90); break; //right turn
    case 0xFF4AB5: digitalWrite(2, LOW); digitalWrite(3, LOW);  digitalWrite(4, LOW); myservo.write(90); //stop
         digitalWrite(5, LOW);  digitalWrite(6, LOW); digitalWrite(7, LOW); myservo.write(90); break;
    default: 
      Serial.println(" other button : ");
      Serial.println(results.value);
    }
  delay(500); // Do not get immediate repeat
}

/*
 * Initialize IR receiver, brush motors,
 * and servo motors
 */
void setup() {
  Serial.begin(9600);

  //IR receiver initialization
  Serial.println("IR Receiver Button Decode"); 
  irrecv.enableIRIn();

  //brush motor power
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);

  //for servo motor
  myservo.attach(9);
}

/*
 * Continuously check for IR signals 
 */
void loop() {
  if (irrecv.decode(&results)){
    translateIR(); //translate
    irrecv.resume(); // receive the next value
  }  

}
