#include <math.h>
#include <Servo.h>

Servo Radar_hand;



// Defining the sensors inputs into the analog pins.
#define Sensor_1 A1
#define Sensor_2 A2
#define Sensor_3 A3
#define Sensor_4 A4
#define Sensor_5 A5


// Defining the servo motor.
#define Servo_motor A0


// Defining the Sonar radar.
const int Trig = 10;
const int Echo = 11;

#define speed_sound 0.0343


// Defining an array to keep the pins of the sensors inside of for analogRead.
const int sensor_pins[] = {Sensor_1, Sensor_2, Sensor_3, Sensor_4, Sensor_5};


// Defining the array for the sensor values inside of.
int sensor_values[5];


// Defining the sonar variables for the radar system;
int Sonar_degree [];
int Sonar_distance [];

int duration = 0;

void Sensors_track ( int sensor_values[] )
{
    for( int i = 0; i < 5; i++ )
    {
        sensor_values[i] = analogRead(sensor_pins[i]);
    }
}

void Radar_system ( int Sonar_distance [], int Sonar_degree [] )
{
    for ( int i = 0; i < 180; i++ )
    {
`       Radar_hand.write(i);
        Sonar_degree[i] = i;
        Sonar_distance[i] = UltraSonic();
    }
}

int UltraSonic ( )
{
    digitalWrite(Trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(Trig, LOW);
    duration = pulseIn(Echo, HIGH);
    
    // length of the Echo pulse in microseconds
    // 0 means no pulse arrived at all; 38000 or more means nothing was in range

    if( duration > 0 && duration < 38000 )
    {
        
    distance = (duration * speed_sound)/2;  // halved because the sound travels there and back
    
    }
    return distance;
}

void setup()
{
    // Setup for the sensor pins.
    for ( int i = 0; i < 5; i++ )
        {
        pinMode(sensor_pins[i],INPUT);
        }
    
    // Setup for the servo pin.
    Radar_hand.attach(Servo_motor);
    
    // Setup for the Sonar pins.
    pinMode(Trig, OUTPUT);
    pinMode(Echo, INPUT);
    
}
void loop()
{
    if (finish line)
    {
        Radar_system( Sonar_distance, Sonar_degree );
    }
}
