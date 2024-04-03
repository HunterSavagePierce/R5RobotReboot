#include "DistanceSensor.h"

void DistanceSensor::readSensor() {
    // Get the raw distance from sensor
    int raw_data = analogRead(pin);
    analog_distance = raw_data;
}

float DistanceSensor::mapDataToDist(int analog_value) {
    float distance_cm = 28000.0 / (analog_value + 1); // Avoid division by zero

    // Update the running sum and rolling average
    sum -= rolling_average[arr_i]; // Subtract the oldest value from the sum
    rolling_average[arr_i] = distance_cm; // Insert the new value into the rolling window
    sum += distance_cm; // Add the new value to the sum

    arr_i = (arr_i + 1) % ROLLING_AVERAGE_SIZE; // Move to the next position in the rolling window

    float average_distance = sum / ROLLING_AVERAGE_SIZE; // Calculate the average based on the running sum

    return average_distance; // Return the average distance
}

float DistanceSensor::getDistance() {
    // Updates, maps, then returns end distance from sensor
    readSensor();
    return mapDataToDist(analog_distance);
}

bool DistanceSensor::objectFound() {
    float distance_cm = getDistance();
    // Check if an object is found based on the distance
    if (distance_cm <= 20) {
        return true;
    }
    return false;
}
