#include <avr/io.h>
#include <util/delay.h>
#include <Arduino.h>
#include <Fastwire.h>
#include "i2c.h"
#include "md25.h"
#include "mpu9150.h"

enum
{
    DELAY_MS = 200,
};

void appInit()
{
    //I2c::init();

    Fastwire::setup(100, true);

    Serial.begin(9600);
}

int main (void)
{
	// Arduino Core initialize function
    init();

    _delay_ms(5000);

    // Initialize function for the application
    appInit();

    Serial.println("Hello!");

    /*
    Md25 md25;

    md25.setMode(OM_MODE0);

    md25.setAccelerationRate(10);

    md25.resetEncoderRegisters();

    int32_t encoderValue = 0;

    MotorDirection dirMotor = MD_FORWARD;
    */


    mpu::Mpu9150 mpu9150;

    if (!mpu9150.setClockSource(mpu::CS_GYRO_X_AXIS_REF)) Serial.println("Error setting clock source");
    if (!mpu9150.setGyroFullScaleRange(mpu::GFSR_250)) Serial.println("Error setting gyro full scale range");
    if (!mpu9150.setAccelFullScaleRange(mpu::AFSR_2g)) Serial.println("Error setting accel full scale range");
    if (!mpu9150.setSleepEnabled(false)) Serial.println("Error disabling sleep");

    while(1)
    {
        mpu9150.update();

        _delay_ms(DELAY_MS);

        /*
        md25.getEncoder(MI_MOTOR1, encoderValue);

        if (dirMotor == MD_FORWARD && encoderValue > 4000)
        {
            dirMotor = MD_REVERSE;
            Serial.println("Changing direction");
        }
        else if (dirMotor == MD_REVERSE && encoderValue < 0)
        {
            dirMotor = MD_FORWARD;
            Serial.println("Changing direction");
        }

        if (!md25.setSpeed(MI_MOTOR1, dirMotor, 0))
        {
           Serial.println("Could not set speed on motor 1");
        }

        if (!md25.setSpeed(MI_MOTOR2, dirMotor, 0))
        {
           Serial.println("Could not set speed on motor 1");
        }

        _delay_ms(DELAY_MS);
        */
    }

    Serial.println("Bye!");

    return 0;
}
