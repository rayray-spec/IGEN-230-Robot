# IGEN 230: Robot
Code for a line following robot, using five QRD1114 sensors mounted on the front of the robot. The sensor would read the reflection back from their IR emitter, and bsed on whether they are over a black strip or white they would return different values.

The complete code is at robot.ino (it is an arduino sketch) and then the different folders contain the subsytems each seperately for testing purposes to ensure that they work prior to mounting everything together.
The robot with the suffix arced refers to the code for the front of the arc or the sensor assembly being positioned in an arc, and the suffix straight refers to the front or the sensor assembly being in a straight line.
