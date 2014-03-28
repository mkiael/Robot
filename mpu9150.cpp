#include "mpu9150.h"

using namespace mpu;

Mpu9150::Mpu9150()
: i2c(0x68)
{
}

bool Mpu9150::setClockSource(ClockSource cs)
{
    uint8_t data = (0x07 & cs);
    uint8_t pwrMgmt1[2] = { MPU9150_REG_PWR_MGMT_1, data };
    return i2c.write(pwrMgmt1, 2);
}

bool Mpu9150::setGyroFullScaleRange(GyroFullScaleRange gfsr)
{
    uint8_t data = (0x18 & gfsr);
    uint8_t gyroConfig[2] = { MPU0150_REG_GYRO_CONFIG, data };
    return i2c.write(gyroConfig, 2);
}

bool Mpu9150::setAccelFullScaleRange(AccelFullScaleRange afsr)
{
    uint8_t data = (0x18 & afsr);
    uint8_t accelConfig[2] = { MPU0150_REG_GYRO_CONFIG, data };
    return i2c.write(accelConfig, 2);
}

bool Mpu9150::setSleepEnabled(bool enabled)
{
    uint8_t data = (0x40 & (enabled ? 1 : 0));
    uint8_t pwrMgmt1[2] = { MPU9150_REG_PWR_MGMT_1, data };
    return i2c.write(pwrMgmt1, 2);
}

bool Mpu9150::readAccel(int16_t& x, int16_t& y, int16_t& z)
{
    bool allOk = true;

    uint8_t buffer[6];
    allOk &= i2c.writeNoStop(MPU0150_REG_ACCEL_XOUT_H);
    allOk &= i2c.read(buffer, 6);
    x = (buffer[0] << 8) | buffer[1];
    y = (buffer[2] << 8) | buffer[3];
    z = (buffer[4] << 8) | buffer[5];

    /*
    uint8_t dataHi = 0x00;
    uint8_t dataLo = 0x00;

    allOk &= i2c.writeNoStop(MPU0150_REG_ACCEL_XOUT_H);
    allOk &= i2c.read(dataHi);
    allOk &= i2c.writeNoStop(MPU0150_REG_ACCEL_XOUT_L);
    allOk &= i2c.read(dataLo);
    x = (dataHi << 8) | dataLo;

    allOk &= i2c.writeNoStop(MPU0150_REG_ACCEL_YOUT_H);
    allOk &= i2c.read(dataHi);
    allOk &= i2c.writeNoStop(MPU0150_REG_ACCEL_YOUT_L);
    allOk &= i2c.read(dataLo);
    y = (dataHi << 8) | dataLo;

    allOk &= i2c.writeNoStop(MPU0150_REG_ACCEL_ZOUT_H);
    allOk &= i2c.read(dataHi);
    allOk &= i2c.writeNoStop(MPU0150_REG_ACCEL_ZOUT_L);
    allOk &= i2c.read(dataLo);
    z = (dataHi << 8) | dataLo;
    */

    return allOk;
}

bool Mpu9150::readGyro(int16_t& x, int16_t& y, int16_t& z)
{
    bool allOk = true;

    uint8_t dataHi = 0x00;
    uint8_t dataLo = 0x00;

    allOk &= i2c.writeNoStop(MPU0150_REG_GYRO_XOUT_H);
    allOk &= i2c.read(dataHi);
    allOk &= i2c.writeNoStop(MPU0150_REG_GYRO_XOUT_L);
    allOk &= i2c.read(dataLo);
    x = (dataHi << 8) | dataLo;

    allOk &= i2c.writeNoStop(MPU0150_REG_GYRO_YOUT_H);
    allOk &= i2c.read(dataHi);
    allOk &= i2c.writeNoStop(MPU0150_REG_GYRO_YOUT_L);
    allOk &= i2c.read(dataLo);
    y = (dataHi << 8) | dataLo;

    allOk &= i2c.writeNoStop(MPU0150_REG_GYRO_ZOUT_H);
    allOk &= i2c.read(dataHi);
    allOk &= i2c.writeNoStop(MPU0150_REG_GYRO_ZOUT_L);
    allOk &= i2c.read(dataLo);
    z = (dataHi << 8) | dataLo;

    return allOk;
}





