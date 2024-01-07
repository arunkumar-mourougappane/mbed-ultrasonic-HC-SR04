/**
 * @file Ultrasonic_SR04.cpp
 * @author Arunkumar Mourougappane (amouroug@buffalo.edu)
 * @brief Implementation for Ultrasonic_SR04 class.
 * @version 1.0
 * @date 2023-12-28
 * 
 * @copyright (c) Arunkumar Mourougappane
 * 
 */

#include "Ultrasonic_SR04.h"
#include <algorithm>


Ultrasonic_SR04::Ultrasonic_SR04(PinName triggerPin, PinName echoPin,  float_t temperature, uint64_t maxTimeoutMicroSec) : mTrigger(triggerPin), mEcho(echoPin)
{
   UpdateForTemperature(temperature);
   mMaxTimeoutMicroSec = maxTimeoutMicroSec;
}

void Ultrasonic_SR04::UpdateForTemperature(float_t temperature)
{
    // Update Speed of sound based on Temperature.
    // https://phys.libretexts.org/Bookshelves/University_Physics/University_Physics_(OpenStax)/Book%3A_University_Physics_I_-_Mechanics_Sound_Oscillations_and_Waves_(OpenStax)/17%3A_Sound/17.03%3A_Speed_of_Sound
    mAdjustedSpeedOfSound = Ultrasonic_SR04::SPEED_OF_SOUND * sqrt(1 + (temperature/Ultrasonic_SR04::TEMPERATURE_0C_IN_KELVIN));
}

float_t Ultrasonic_SR04::MeasureDistance() {
    // Using the approximate formula 19.307°C results in roughly 343m/s which is the commonly used value for air.
    return MeasureDistance(Ultrasonic_SR04::ROOM_TEMPERATURE_IN_CELCIUS);
}

float_t Ultrasonic_SR04::MeasureDistance(float_t temperature) {
   
    UpdateForTemperature(temperature);
    Timer echoDurationTimer;
    echoDurationTimer.reset();
    // Make sure that trigger pin is LOW.
    mTrigger = Ultrasonic_SR04::LOW;
    wait_us(2);
    // Hold trigger for 10 microseconds, which is signal for sensor to measure distance.
    mTrigger = Ultrasonic_SR04::HIGH;
    wait_us(10);
    mTrigger = Ultrasonic_SR04::LOW;

    // Wait Till Echo starts response
    while(mEcho == Ultrasonic_SR04::LOW);
    echoDurationTimer.start();
    while(mEcho == Ultrasonic_SR04::HIGH);
    echoDurationTimer.stop();

    // Get the time take for sound to travel and back, then halve it to get the time to hit the 1st target.
    uint64_t durationUS =  std::chrono::duration_cast<std::chrono::microseconds>(echoDurationTimer.elapsed_time()).count() /2;
    echoDurationTimer.reset();

    /* If the pulse width is too long then it would mean, the object is too far away i.e we did not get a
       echo back. Not getting an echo an also happen when the sensor is masked so take it as 0.
    */
    if (durationUS > mMaxTimeoutMicroSec) 
    {
        // Too far so return a negative number.
        return  0;
    }
    // Distance is speed * time in us.
    return durationUS * mAdjustedSpeedOfSound * 0.000001;
}