#include <avr/io.h>
#include <util/delay.h>
#include <util/twi.h>
#include <Arduino.h>
#include "i2c.h"
#include "md25.h"

enum
{
    DELAY_MS = 20,
};

void appInit()
{
    I2c::init();

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

    Md25 md25;

    md25.setMode(OM_MODE0);

    md25.setAccelerationRate(10);

    md25.resetEncoderRegisters();

    int32_t encoderValue = 0;

    MotorDirection dirMotor = MD_FORWARD;

    while(1)
    {
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
    }

    Serial.println("Bye!");

    return 0;
}
