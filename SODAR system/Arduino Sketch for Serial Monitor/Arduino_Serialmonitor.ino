#include <Servo.h>

Servo radar_hand;

const int Trig = 10;
const int Echo = 11;

#define step 1
#define speed_sound 0.0343
#define Failed 0

double distance;
double duration;


void radar_sweep()
{
    
  for(int i = 180; i >= 0; i--)
  {
    radar_hand.write(i);
    Serial.print("angle: ");
    delay(100);
    Serial.print(i);
    Serial.print("° ");
    ultra_sonic();

  }
  for(int i = 0; i <= 180; i++)
  {
    radar_hand.write(i);
    delay(100);
    Serial.print("Angle: ");
    Serial.print(i);
    Serial.print("° ");
    ultra_sonic();

  }
  
}

void ultra_sonic()
{
  digitalWrite(Trig,HIGH);
  delayMicroseconds(10);
  digitalWrite(Trig,LOW);
  duration = pulseIn(Echo, HIGH);
  if( duration < 38000 )
  {
    distance = (duration * speed_sound)/2;
    Serial.print(", Distance: ");
    Serial.print(distance);
    Serial.println(" CM");
  }
  else
  {
    Serial.println("Failed to read object.");
    Serial.println(Failed);
  }

}

void setup()
{
  pinMode(Trig, OUTPUT);
  pinMode(Echo, INPUT);
  Serial.begin(9600);
  radar_hand.attach(12);
}
void loop()
{
  radar_sweep();
}
