#include "md25.h"

// TBR
#include <Arduino.h>

#define MD25_REG_SPEED1     0x00
#define MD25_REG_SPEED2     0x01
#define MD25_REG_ENC1A      0x02
#define MD25_REG_ENC1B      0x03
#define MD25_REG_ENC1C      0x04
#define MD25_REG_ENC1D      0x05
#define MD25_REG_ENC2A      0x06
#define MD25_REG_ENC2B      0x07
#define MD25_REG_ENC2C      0x08
#define MD25_REG_ENC2D      0x09
#define MD25_REG_ACC_RATE   0x0E
#define MD25_REG_MODE       0x0F
#define MD25_REG_CMD        0x10

Md25::Md25()
: i2c(0x58)
{
}

bool Md25::setMode(OperationMode om)
{
    uint8_t mode[2] = { MD25_REG_MODE, om };

    return i2c.write(mode, 2);
}

bool Md25::setAccelerationRate(uint8_t ar)
{
    uint8_t accRate[2] = { MD25_REG_ACC_RATE, ar };

    return i2c.write(accRate, 2);
}

bool Md25::setSpeed(MotorIndex index, MotorDirection dir, uint8_t speed)
{
    uint8_t motorRegister = (index == MI_MOTOR1 ? MD25_REG_SPEED1 : MD25_REG_SPEED2);

    uint8_t rawSpeed = speedFromPercent(dir, speed);

    uint8_t m1Speed[2] = { motorRegister, rawSpeed };

    return i2c.write(m1Speed, 2);
}

bool Md25::getEncoder(MotorIndex index, int32_t& encoderValue)
{
    uint8_t encoderRegister = (index == MI_MOTOR1 ? MD25_REG_ENC1A : MD25_REG_ENC2A );

    uint8_t encoderBytes[4];

    for(uint8_t i = encoderRegister, j = 0; i < encoderRegister+4; ++i, ++j)
    {
        if (!i2c.writeNoStop(&i, 1))
        {
            return false;
        }

        if (!i2c.read(encoderBytes[j]))
        {
            return false;
        }
    }

    encoderValue = ((int32_t)encoderBytes[0] << 24) |
                   ((int32_t)encoderBytes[1] << 16) |
                   ((int32_t)encoderBytes[2] << 8) |
                   (int32_t)encoderBytes[3];

    return true;
}

bool Md25::resetEncoderRegisters()
{
    uint8_t resetEncoders[2] = { MD25_REG_CMD, 0x20 };

    return i2c.write(resetEncoders, 2);
}

uint8_t Md25::speedFromPercent(MotorDirection dir, uint8_t speed)
{
    // 0 = full reverse, 128 = stop, 255 = full forward

    uint8_t s = static_cast<uint8_t>(speed/100.0*128);

    return dir == MD_FORWARD ? 128+s : 128-s;
}




