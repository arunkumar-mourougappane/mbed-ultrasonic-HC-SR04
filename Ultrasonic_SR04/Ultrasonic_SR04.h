/**
 * @file Ultrasonic_SR04.h
 * @author Arunkumar Mourougappane (amouroug@buffalo.edu)
 * 
 * @brief An API to interface with SR-04 Ultrasonic Sensor and calculate distances from objects for any given temperature in celcius.
 * 
 * @version 1.0
 * @date 2023-12-28
 * 
 * @copyright (c) Arunkumar Mourougappane
 * 
 */

#ifndef ULTRASONIC_SR04_H
#define ULTRASONIC_SR04_H

#include <mbed.h>

// An example for running SR 04.
// #include "mbed.h"
// #include "Ultrasonic_SR04.h"
//
// int main()
// {
//     DigitalOut led(LED1);
//     Ultrasonic_SR04 ultrasonicSR04(D10, D9, 22);
//     while(true)
//     {
//         led=0;
//         float_t distance = ultrasonicSR04.MeasureDistance();
//         // Mbed OS 6.15's printf() is broken and incapable of printing float or double. so we had to invent a way to do thigs.
//         printf("\nDistance:  %llu.%llu m\n", (uint64_t)distance, (((uint64_t)(distance*1000))%1000));
//         ThisThread::sleep_for(500ms);
//         led=1;
//     }
// }

/**
 * @brief Creates an instance to access Ultrasonics Hardware and measure the distance to
 * traget using sound waves for a given temperature.
 * 
 */
class Ultrasonic_SR04
{
private:
   static constexpr uint8_t HIGH = 1; // Pin Digital High State.
   static constexpr uint8_t LOW = 0; // Pin Digital Low State.
   static constexpr float SPEED_OF_SOUND = 331.3; // Speed of sound in meters per second.
   static constexpr float ROOM_TEMPERATURE_IN_CELCIUS = 22.30; // Default Room Temperature. 70F
   static constexpr float TEMPERATURE_0C_IN_KELVIN = 273.15; // O C represented in Kelvin Temperature Scale.
   static constexpr uint64_t MAX_TIMEOUT_IN_US = 65530; // Max yielded pulsewidth of SR-04.
   uint64_t mMaxTimeoutMicroSec;
   DigitalOut mTrigger;
   DigitalIn mEcho;
   float mAdjustedSpeedOfSound = 0;
public:
   /**
    * @brief Construct a new Ultrasonic SR04 object
    * 
    * @param triggerPin Pin to trigger of  Ultrasonic sensor.
    * @param echoPin Pin to measure/detect the echo HIGH.
    * @param temperature Temperature of Room in Kelvin to adust for changes.
    * @param maxTimeoutMicroSec Ignore any distance that takes more than the specified echo time i.e Sound Trigger+Response time.
    */
   Ultrasonic_SR04(PinName triggerPin, PinName echoPin, float_t temperature = ROOM_TEMPERATURE_IN_CELCIUS, uint64_t maxTimeoutMicroSec = MAX_TIMEOUT_IN_US);

   /**
    * @brief Update the temperature and corresponding dependent variables.
    * 
    * @param temperature  Temperature to updating speed of sound adjusted for.
    */
   void UpdateForTemperature(float_t temperature);

   /**
    * @brief Measure the distance from the utlrasonic sensor and returns the distance while
    *        Updating the temperature parameter.
    * 
    * @param temperature New Temperature to adjust to and measure.
    * @return float_t Returns the distance measured by ultrasonic sensor.
    * 
    * @note Its recommended not to use API if you are going to measure at constant temperature.
    */
   float_t MeasureDistance(float_t temperature);
   
   /**
    * @brief Measure the distance from the utlrasonic sensor and returns the distance.
    * 
    * @return float_t Returns the distance measured by ultrasonic sensor.
    */
   float_t MeasureDistance();
};

#endif // !ULTRASONIC_SR04_H
