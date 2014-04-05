#ifndef MPU9150_H_
#define MPU9150_H_

#include "mpu9150defs.h"
#include <stdint.h>

namespace mpu {

class Mpu9150
{
public:

    Mpu9150();

    bool setClockSource(ClockSource cs);

    bool setAccelFullScaleRange(AccelFullScaleRange afsr);

    bool setGyroFullScaleRange(GyroFullScaleRange gfsr);

    bool setSleepEnabled(bool enabled);

    void update();

private:

    bool readAccel(int16_t& x, int16_t& y, int16_t& z);

    bool readGyro(int16_t& x, int16_t& y, int16_t& z);

    bool readAccelAndGyro(int16_t& ax, int16_t& ay, int16_t& az,
                          int16_t& gx, int16_t& gy, int16_t& gz);

    uint8_t m_addr;

    double m_accelSensitivity;

    double m_gyroSensitivity;

    double m_pitch;

    double m_roll;

};

}

#endif /* MPU9150_H_ */
