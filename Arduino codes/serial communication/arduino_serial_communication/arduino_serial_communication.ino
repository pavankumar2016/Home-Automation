#include <SoftwareSerial.h>
#define ledpin0 30
#define ledpin1 32
#define ledpin2 34
#define ledpin3 36
#define ledpin4 38
#define ledpin5 40
#define ledpin6 42
#define ledpin7 44

#define led1faultcheck 31
#define led2faultcheck 33
#define led3faultcheck 35
#define led4faultcheck 37
#define led5faultcheck 39
#define led6faultcheck 41
#define led7faultcheck 43
#define led8faultcheck 45


SoftwareSerial nodeserial(10, 11); // RX ! TX 


void setup() {
  Serial.begin(115200);
  nodeserial.begin(115200);

  pinMode(ledpin0, OUTPUT);
  pinMode(ledpin1, OUTPUT);
  pinMode(ledpin2, OUTPUT);
  pinMode(ledpin3, OUTPUT);
  pinMode(ledpin4, OUTPUT);
  pinMode(ledpin5, OUTPUT);
  pinMode(ledpin6, OUTPUT);
  pinMode(ledpin7, OUTPUT);

}

void loop() {
  while (nodeserial.available() > 0) {
    float val = nodeserial.parseFloat();



      if (val == 21) {
        digitalWrite(ledpin0, HIGH);
        digitalRead(led1faultcheck) == HIGH ;

              if (digitalRead(led1faultcheck) == LOW )
        {
          Serial.println(" LED - 1 - FAULT ");
          nodeserial.print(10);
          delay(500);
            }
          }
      else if (val == 20) {
       digitalWrite(ledpin0, LOW);
          }




      if (val == 31) {
        digitalWrite(ledpin1, HIGH);
        digitalRead(led2faultcheck) == HIGH ;

                if (digitalRead(led2faultcheck) == LOW )
        {
          Serial.println(" LED - 2 - FAULT ");
          nodeserial.print(20);
          delay(500);
            }
         }
      else if (val == 30) {
       digitalWrite(ledpin1, LOW);
          }



       if (val == 41) {
        digitalWrite(ledpin2, HIGH);
        digitalRead(led3faultcheck) == HIGH ;
               if (digitalRead(led3faultcheck) == LOW )
        {
          Serial.println(" LED - 3 - FAULT ");
          nodeserial.print(30);
          delay(500);
            }
         }
      else if(val == 40) {
       digitalWrite(ledpin2, LOW);
         }





      if (val == 51) {
        digitalWrite(ledpin3, HIGH);
        digitalRead(led4faultcheck) == HIGH ;
            if (digitalRead(led4faultcheck) == LOW )
        {
          Serial.println(" LED - 4 - FAULT ");
          nodeserial.print(40);
          delay(500);
            }
         }
      else if(val == 50) {
       digitalWrite(ledpin3, LOW);
         }





      if (val == 61) {
        digitalWrite(ledpin4, HIGH);
        digitalRead(led5faultcheck) == HIGH ;
               if (digitalRead(led5faultcheck) == LOW )
        {
          Serial.println(" LED - 5 - FAULT ");
          nodeserial.print(50);
          delay(500);
            }
         }
      else if(val == 60) {
       digitalWrite(ledpin4, LOW);
         }



         
      if (val == 71) {
        digitalWrite(ledpin5, HIGH);
        digitalRead(led6faultcheck) == HIGH ;
               if (digitalRead(led6faultcheck) == LOW )
        {
          Serial.println(" LED - 6 - FAULT ");
          nodeserial.print(60);
          delay(500);
            }
         }
      else if(val == 70) {
       digitalWrite(ledpin5, LOW);
         }  



      if (val == 81) {
        digitalWrite(ledpin6, HIGH);
        digitalRead(led7faultcheck) == HIGH ;
               if (digitalRead(led7faultcheck) == LOW )
        {
          Serial.println(" LED - 7 - FAULT ");
          nodeserial.print(70);
          delay(500);
            }
         }
      else if(val == 80) {
       digitalWrite(ledpin6, LOW);
         }



      if (val == 91) {
        digitalWrite(ledpin7, HIGH);
        digitalRead(led8faultcheck) == HIGH ;
               if (digitalRead(led8faultcheck) == LOW )
        {
          Serial.println(" LED - 8 - FAULT ");
          nodeserial.print(80);
          delay(500);
            }
         }
      else if(val == 90) {
       digitalWrite(ledpin7, LOW);
         }
          
      Serial.print(val);
         }
       
        delay(100);   
    }
  


