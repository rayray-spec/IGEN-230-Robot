# Import the libraries for reading the serial port, doing the angle math and plotting the polar graph.
import serial
import math
import matplotlib.pyplot as plt

# Open the connection to the Arduino on COM6 at 9600 baud, matching Serial.begin(9600) in the Arduino sketch.
ser = serial.Serial( 'COM6' , 9600 , timeout =1 )

angle_list = []
distance_list = []
num = 0

# Main loop: read each line the Arduino sends on COM6, decode it, split it at the comma into an angle
# and a distance, and store them in two lists for plotting. Garbled lines are skipped by the try/except.
while True:
    raw_data = ser.readline()
    try:
        text_raw = raw_data.decode()
        text = text_raw.strip()
        parts = text.split(',')
        degree = int(parts[0])
        distance = float(parts[1])
        # Failed readings arrive as 0 and are skipped, so they don't plot at the centre.
        if( distance > 0 ):
            radians_num = math.radians(degree)
            angle_list.append(radians_num)
            distance_list.append(distance)
        print(degree)
        print(distance)
        num += 1
        # 181 readings is one full sweep from 180° to 0°.
        if (num == 181):
            break
    except:
        pass

# Close the COM6 connection once the sweep is recorded.
ser.close()

# Plot the polar graph from the angles the Arduino set the servo to and the distances the sensor measured.
ax = plt.subplot(projection='polar')
ax.scatter(angle_list, distance_list)
ax.set_thetamin(0)
ax.set_thetamax(180)
ax.set_title('Static SODAR scan (distance in cm)')
ax.yaxis.set_major_formatter(lambda value, pos: f'{value:.0f} cm')
plt.show()
