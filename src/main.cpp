// C++ code
//
#include <math.h>
#include <Arduino.h>

int counter = 0;
int sensor = A1;
int threshold = A2;
int LED = 6;
int button = 7;
bool previousPressed = false;


void setup()
{
  Serial.begin(9600);
  
  pinMode(sensor, INPUT);
  pinMode(threshold, INPUT);
  pinMode(LED, OUTPUT);
  pinMode(button, INPUT_PULLUP);

}

float DC(float threshold, float V_sensor)
{
 
  if (counter == 0)
  {
    Serial.println("Auto");
    
    if (fabs(threshold - 3.79) < 0.01)
    {

      return 1.0;
    }
    
    float dc = ((1.0 / (threshold - 3.79) ) * ((-1) * V_sensor + 3.79) + 1.0);
    Serial.print("Dc = ");
    Serial.println(dc);
    Serial.print("Th = ");
    Serial.println(threshold);
    Serial.print("Vsensor = ");
    Serial.println(V_sensor);

    if (dc < 0) dc = 0.0;
    if (dc > 1) dc = 1.0;
    Serial.print("Dc = ");
    Serial.println(dc);
    return dc;
  } 
  else if (counter == 1)
  {
    Serial.println("OFF");
    return 0;
  }
  else if (counter == 2)
  {
    Serial.println("50%");
    return 0.5;
  } 
  else 
  {
    Serial.println("100%");
    return 1.0;
  }  
}

void loop()
{

  float V_threshold = analogRead(threshold) * (5.0 /1023.0);
  float V_sensor = analogRead(sensor) * (5.0 /1023.0);
  bool pressed = (digitalRead(button) == LOW); 
  
  if (pressed && !previousPressed)
  {
    counter = (counter + 1) % 4;
    Serial.print("Counter = ");
    Serial.println(counter);
    Serial.print("Pressed = ");
    Serial.println(pressed);
  }
  
  float Dc = DC(V_threshold, V_sensor);
  analogWrite(LED, Dc * 255);

  previousPressed = pressed;
  delay(5000);
  
}
   


