#ifndef DISTANCE_SENSOR_H
#define DISTANCE_SENSOR_H

#include <Arduino.h>

class DistanceSensor {
public:
    DistanceSensor(int DATA_PIN) {
        pin = DATA_PIN;
        pinMode(DATA_PIN, INPUT);
        for(size_t i = 0; i < ROLLING_AVERAGE_SIZE; ++i) {
            rolling_average[i] = 0.0; // Initialize rolling window to zeros
        }
        sum = 0; // Initialize sum to 0
    }

    void readSensor();
    float mapDataToDist(int analog_value);
    float getDistance();
    bool objectFound();

private:
    static const size_t ROLLING_AVERAGE_SIZE = 20;
    int pin;
    int analog_distance;
    float rolling_average[ROLLING_AVERAGE_SIZE] = {};
    size_t arr_i = 0;
    float sum = 0; // Member variable for the running sum
};

#endif
