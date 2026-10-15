// C++ code
//
#include <math.h>
#include <Arduino.h>

int counter = 0;
int sensor = A1;
int threshold = A2;
int LED = 6;
int button = 7;
// Lägg före setup():
bool previousPressed = false;


void setup()
{
  Serial.begin(9600);
  
  pinMode(sensor, INPUT);
  pinMode(threshold, INPUT);
  pinMode(LED, OUTPUT);
  pinMode(button, INPUT_PULLUP);

}

void loop()
{

  float V_threshold = analogRead(threshold) * (5.0 /1023.0);
  float V_sensor = analogRead(sensor) * (5.0 /1023.0);
  bool pressed = (digitalRead(button) == LOW); //low betyder nedtryckt
  Serial.print("Pressed = ");
  Serial.println(pressed);
  
  if (pressed && !previousPressed)
  {
    counter = (counter + 1) % 4;
    Serial.print("Counter = ");
    Serial.println(counter);
    delay(50);
  }
  
  float Dc = DC(V_threshold, V_sensor);
  analogWrite(LED, Dc * 255);
  //analogWrite(LED, 255);

  previousPressed = pressed;
  // kod från knapp förslag 
  // read the state of the pushbutton value
  //buttonState = digitalRead(2);
  // check if pushbutton is pressed.  if it is, the
  // buttonState is HIGH
  //if (buttonState == HIGH) {
    // turn LED on
    //digitalWrite(LED_BUILTIN, HIGH);
  //} else {
    // turn LED off
    //digitalWrite(LED_BUILTIN, LOW);
  //}
  //delay(10);
}

float DC(float threshold, float Vout)
{
 
  if (counter == 0)
  {
    Serial.print("Auto");
    
    if (fabs(threshold - 2.86) < 0.01)
    {
      return 1.0;
    }
    
    float dc = (((1.0/(threshold-2.86))*(-Vout+2.86)) + 1.0);
    
    if (dc < 0) dc = 0.0;
    if (dc > 1) dc = 1.0;
    return dc;
  } 
  else if (counter == 1)
  {
    Serial.print("OFF");
    return 0;
  }
  else if (counter == 2)
  {
    Serial.print("50%");
    return 0.5;
  } 
  else 
  {
    Serial.print("100%");
    return 1.0;
  }     
}

