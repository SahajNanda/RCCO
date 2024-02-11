#include "IRremote.h"
#include "IR.h"
#include <Stepper.h>

const int stepsPerRevolution = 2048;
const int RevolutionsPerMinute = 17;

IRrecv irrecv(RECEIVER);
decode_results results;

Stepper myStepper(stepsPerRevolution, 8, 9, 10, 11);

int height = 9;
int difference;

void setup() {
  myStepper.setSpeed(RevolutionsPerMinute);
  Serial.begin(9600);
  irrecv.enableIRIn();
}

void loop() {
    int tmpValue;
  if (irrecv.decode(&results)) {
    for (int i = 0; i < 23; i++) {
      difference = 0;
      if ((keyValue[i] == results.value) && (i<KEY_NUM)) {
        switch(results.value) {
          case 0xFF6897: 
            difference = height - 0;
            height = 0;
            Serial.println("0");
            break;
          case 0xFF30CF: 
            difference = height - 1;
            height = 1;
            Serial.println("1");
            break;
          case 0xFF18E7: 
            difference = height - 2;
            height = 2;
            Serial.println("2");
            break;
          case 0xFF7A85: 
            difference = height - 3;
            height = 3;
            Serial.println("3");
            break;
          case 0xFF10EF: 
            difference = height - 4;
            height = 4;
            Serial.println("4");
            break;
          case 0xFF38C7: 
            difference = height - 5;
            height = 5;
            Serial.println("5");
            break;
          case 0xFF5AA5: 
            difference = height - 6;
            height = 6;
            Serial.println("6");
            break;
          case 0xFF42BD: 
            difference = height - 7;
            height = 7;
            Serial.println("7");
            break;
          case 0xFF4AB5: 
            difference = height - 8;
            height = 8;
            Serial.println("8");
            break;
          case 0xFF52AD: 
            difference = height - 9;
            height = 9;
            Serial.println("9");
            break;
          case 0xFFFFFFFF: 
            difference = 0;
            break;  
          default: 
            difference = 0;
        }
        if (difference > 0) {
          for (int j = 0; j < difference; j++) {
            myStepper.step(stepsPerRevolution);
          }
        } else if (difference < 0) {
          for (int j = 0; j > difference; j--) {
            myStepper.step(-2048);
          }
        }
      }
      else if(REPEAT==i)
      {
        results.value = tmpValue;
      }
    }
    irrecv.resume(); // receive the next value
  }
}
