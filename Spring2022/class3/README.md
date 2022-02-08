There are 4 Arduino examples for APDS9960 sensor in this folder.
[Arduino APDS9960 library](https://www.arduino.cc/en/Reference/ArduinoAPDS9960) was used in all of the examples.
See the top of each code for circuit instructions.

#### proximity_average
It reads proximity values from a APDS9960 sensor and average the last N (10 in the example) values for smoothing.
As output, it changes the brightness of 2 LEDs, one with the raw reading and the other with the average, to compare the two.
See the averageReadings() function and think about how it works.

#### proximity_average_withlibrary
It reads proximity values from a APDS9960 sensor and average the last N (10 in the example) values for smoothing.
As output, it changes the brightness of 2 LEDs, one with the raw reading and the other with the average, to compare the two.
This does the same thing as the first example (proximity_average), but it uses an averaging library ([AverageValue](https://www.arduino.cc/reference/en/libraries/averagevalue/)).

#### callib_led


#### callib_servo
description

