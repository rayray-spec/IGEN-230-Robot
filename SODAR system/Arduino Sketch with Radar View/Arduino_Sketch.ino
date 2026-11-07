// Radar version (bonus parts): prints each reading as "angle,distance" so the Python scripts can read it.
#include <Servo.h>

Servo radar_hand;           // the servo that turns the sensor

const int Trig = 10;        // sensor Trig pin
const int Echo = 11;        // sensor Echo pin

#define speed_sound 0.0343  // speed of sound in cm per microsecond at 20 °C
#define Failed 0            // sent as the distance when a reading fails; the Python scripts skip it

double distance;
double duration;

// Sweep the servo from 180° to 0° and back, taking one reading at every degree.
void radar_sweep()
{
  for(int i = 180; i >= 0; i--)
  {
    radar_hand.write(i);
    delay(100);             // let the servo reach the angle; also keeps pings more than 60 ms apart
    Serial.print(i);        // angle, then a comma, then ultra_sonic() prints the distance
    Serial.print(",");
    ultra_sonic();
  }
  for(int i = 0; i <= 180; i++)
  {
    radar_hand.write(i);
    delay(100);             // let the servo reach the angle; also keeps pings more than 60 ms apart
    Serial.print(i);        // angle, then a comma, then ultra_sonic() prints the distance
    Serial.print(",");
    ultra_sonic();
  }
}

// Send a 10 µs trigger pulse, time the Echo pulse and print the distance, ending the line.
void ultra_sonic()
{
  digitalWrite(Trig,HIGH);
  delayMicroseconds(10);
  digitalWrite(Trig,LOW);
  duration = pulseIn(Echo, HIGH);          // length of the Echo pulse in microseconds
  // 0 means no pulse arrived at all; 38000 or more means nothing was in range
  if( duration > 0 && duration < 38000 )
  {
    distance = (duration * speed_sound)/2; // halved because the sound travels there and back
    Serial.println(distance);
  }
  else
  {
    Serial.println(Failed);
  }
}

void setup()
{
  pinMode(Trig, OUTPUT);
  pinMode(Echo, INPUT);
  Serial.begin(9600);       // must match the baud rate in the Python scripts
  radar_hand.attach(12);    // servo signal wire on pin 12
}

void loop()
{
  radar_sweep();
}
