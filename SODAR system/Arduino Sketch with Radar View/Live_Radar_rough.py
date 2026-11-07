# Import the libraries for reading the serial port, doing the angle math and plotting the polar graph.
import serial
import math
import matplotlib.pyplot as plt

# Open the connection to the Arduino on COM6 at 9600 baud, matching Serial.begin(9600) in the Arduino sketch.
ser = serial.Serial( 'COM6' , 9600 , timeout =1 )

angle_list = []
distance_list = []

# Interactive mode lets the chart window stay open and update while the loop keeps reading.
plt.ion()
ax = plt.subplot(projection='polar')    # create a polar plot area
ax.scatter(angle_list, distance_list)   # draw a dot for each reading (empty at the start)
ax.set_thetamin(0)                      # show only the half circle the servo sweeps
ax.set_thetamax(180)

# Main loop: read each line the Arduino sends, decode it, split it at the comma into an angle and a
# distance, store them in two lists and redraw the chart. Garbled lines are skipped by the try/except.
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
            # Clear the chart and redraw all stored readings. Clearing also removes the half-circle
            # setting, so it is applied again.
            ax.clear()
            ax.scatter(angle_list, distance_list)
            ax.set_thetamin(0)
            ax.set_thetamax(180)
        print(degree)
        print(distance)
        # Give the window a moment to draw the update.
        plt.pause(0.01)
    except (ValueError, IndexError, UnicodeDecodeError):
        pass    # skip lines that are garbled or not in "angle,distance" format
