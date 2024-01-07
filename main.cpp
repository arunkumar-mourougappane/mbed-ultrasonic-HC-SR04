/**
 * @file main.cpp
 * @author Arunkumar Mourougappane (amouroug@buffalo.edu)
 * @brief An example to use SR-04 Ultrasonics Sensor API
 * @version 1.0
 * @date 2024-01-07
 * 
 * @copyright (c) Arunkumar Mourougappane
 * 
 */

#include "mbed.h"
#include "Ultrasonic_SR04.h"

int main()
{
    DigitalOut led(LED1);
    Ultrasonic_SR04 ultrasonicSR04(D10, D9, 22);
    while(true)
    {
        led=0;
        float_t distance = ultrasonicSR04.MeasureDistance();
        // Mbed OS 6.15's printf() is broken and incapable of printing float or double. so we had to invent a way to do thigs.
        printf("\nDistance:  %llu.%llu m\n", (uint64_t)distance, (((uint64_t)(distance*1000))%1000));
        ThisThread::sleep_for(500ms);
        led=1;
    }
}