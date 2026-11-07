// Define the sensor pins for clarity

#define Sensor_1 A1
#define Sensor_2 A2
#define Sensor_3 A3
#define Sensor_4 A4
#define Sensor_5 A5

// Array of the sensor pins, for more compact and shorter code

const int sensor_pins[] = {Sensor_1, Sensor_2, Sensor_3, Sensor_4, Sensor_5};
int sensor_values[5];


// Function for reading the value of each sensor

void Sensors_track ( int sensor_values[] )
{
    for( int i = 0; i < 5; i++ )
    {
        sensor_values[i] = analogRead(sensor_pins[i]);
    }
}


void setup()
{
    // Initialize the Serial Monitor for printing
    Serial.begin(9600);
    // Set the sensor pins as inputs, because we only read from them and never write to them
    pinMode(Sensor_1,INPUT);
    pinMode(Sensor_2,INPUT);
    pinMode(Sensor_3,INPUT);
    pinMode(Sensor_4,INPUT);
    pinMode(Sensor_5,INPUT);
}

void loop()                            // Read the sensors, print the values and repeat
{
    Sensors_track(sensor_values);

    for( int i = 0; i < 5; i++ )
    {
        // Print the value of each sensor
        Serial.print(sensor_values[i]);
        if ( i < 4 )
        {
            Serial.print(",");
        }
        Serial.print(' ');
    }
    Serial.println();

    delay(50);                         // Wait 50 ms, which gives about 20 rows per second
}
