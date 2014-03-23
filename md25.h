#ifndef MD25_H_
#define MD25_H_

#include "i2c.h"

enum OperationMode
{
    OM_MODE0 = 0,
    OM_MODE1,
    OM_MODE2,
    OM_MODE3
};

enum MotorIndex
{
    MI_MOTOR1 = 0,
    MI_MOTOR2
};

enum MotorDirection
{
    MD_FORWARD = 0,
    MD_REVERSE
};

class Md25
{
public:

    Md25();

    bool setMode(OperationMode om);

    bool setAccelerationRate(uint8_t ar);

    // Motor speed in percent 0-100
    bool setSpeed(MotorIndex index, MotorDirection dir, uint8_t speed);

    bool getEncoder(MotorIndex index, int32_t& encoderValue);

    bool resetEncoderRegisters();

private:

    uint8_t speedFromPercent(MotorDirection dir, uint8_t speed);

    I2c i2c;

};

#endif /* MD25_H_ */
