#include "mpu9150.h"
#include <Fastwire.h>

//#include <Arduino.h>

using namespace mpu;

Mpu9150::Mpu9150()
: m_addr(0x68<<1)
, m_accelSensitivity(1.0)
, m_gyroSensitivity(1.0)
, m_pitch(0.0)
, m_roll(0.0)
{
}

bool Mpu9150::setClockSource(ClockSource cs)
{
    uint8_t data = (0x07 & cs);
    return Fastwire::writeBuf(m_addr, MPU9150_REG_PWR_MGMT_1, &data, 1) == 0;
}

bool Mpu9150::setAccelFullScaleRange(AccelFullScaleRange afsr)
{
    switch (afsr)
    {
    case AFSR_2g:
        m_accelSensitivity = 16384.0;
        break;
    case AFSR_4g:
        m_accelSensitivity = 8192.0;
        break;
    case AFSR_8g:
        m_accelSensitivity = 4096.0;
        break;
    case AFSR_16g:
        m_accelSensitivity = 2048.0;
        break;
    default:
        m_gyroSensitivity = 1.0;
        break;
    }

    uint8_t data = (0x18 & afsr);
    return Fastwire::writeBuf(m_addr, MPU9150_REG_ACCEL_CONFIG, &data, 1) == 0;
}

bool Mpu9150::setGyroFullScaleRange(GyroFullScaleRange gfsr)
{
    switch (gfsr)
    {
    case GFSR_250:
        m_gyroSensitivity = 131.0;
        break;
    case GFSR_500:
        m_gyroSensitivity = 65.5;
        break;
    case GFSR_1000:
        m_gyroSensitivity = 32.8;
        break;
    case GFSR_2000:
        m_gyroSensitivity = 16.4;
        break;
    default:
        m_accelSensitivity = 1.0;
        break;
    }

    uint8_t data = (0x18 & gfsr);
    return Fastwire::writeBuf(m_addr, MPU9150_REG_GYRO_CONFIG, &data, 1) == 0;
}

bool Mpu9150::setSleepEnabled(bool enabled)
{
    uint8_t data = (0x40 & (enabled ? 1 : 0));
    return Fastwire::writeBuf(m_addr, MPU9150_REG_PWR_MGMT_1, &data, 1) == 0;
}

void Mpu9150::update()
{
    int16_t ax, ay, az, gx, gy, gz;

    readAccelAndGyro(ax, ay, az, gx, gy, gz);

    double accelX = ax / m_accelSensitivity;
    double accelY = ay / m_accelSensitivity;
    double accelZ = az / m_accelSensitivity;

    // Pitch, rotation around y-axis
    m_pitch = atan2(-accelX, sqrt(accelY*accelY+accelZ*accelZ))*180.0/M_PI;

    // Roll, rotation around x-axis
    m_roll = atan2(accelY, accelZ)*180.0/M_PI;

    //Serial.print("Pitch: "); Serial.print(m_pitch); Serial.print("\n");
    //Serial.print("Roll: "); Serial.print(m_roll); Serial.print("\n");
}

bool Mpu9150::readAccel(int16_t& x, int16_t& y, int16_t& z)
{
    uint8_t buffer[6];

    uint8_t status = Fastwire::readBuf(m_addr, MPU9150_REG_ACCEL_XOUT_H, buffer, 6);

    x = (buffer[0] << 8) | buffer[1];
    y = (buffer[2] << 8) | buffer[3];
    z = (buffer[4] << 8) | buffer[5];

    return status == 0;
}

bool Mpu9150::readGyro(int16_t& x, int16_t& y, int16_t& z)
{
    uint8_t buffer[6];

    uint8_t status = Fastwire::readBuf(m_addr, MPU9150_REG_GYRO_XOUT_H, buffer, 6);

    x = (buffer[0] << 8) | buffer[1];
    y = (buffer[2] << 8) | buffer[3];
    z = (buffer[4] << 8) | buffer[5];

    return status == 0;
}

bool Mpu9150::readAccelAndGyro(int16_t& ax, int16_t& ay, int16_t& az,
                               int16_t& gx, int16_t& gy, int16_t& gz)
{
    uint8_t buffer[14];

    uint8_t status = Fastwire::readBuf(m_addr, MPU9150_REG_ACCEL_XOUT_H, buffer, 14);

    ax = (buffer[0] << 8) | buffer[1];
    ay = (buffer[2] << 8) | buffer[3];
    az = (buffer[4] << 8) | buffer[5];

    // We skip index 6 and 7 since this is readings from the temperature sensor.

    gx = (buffer[8] << 8) | buffer[9];
    gy = (buffer[10] << 8) | buffer[11];
    gz = (buffer[12] << 8) | buffer[13];

    return status == 0;
}






