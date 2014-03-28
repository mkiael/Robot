#ifndef MPU9150_H_
#define MPU9150_H_

#include "mpu9150defs.h"
#include "i2c.h"

namespace mpu {

class Mpu9150
{
public:

    Mpu9150();

    bool setClockSource(ClockSource cs);

    bool setGyroFullScaleRange(GyroFullScaleRange gfsr);

    bool setAccelFullScaleRange(AccelFullScaleRange afsr);

    bool setSleepEnabled(bool enabled);

    bool readAccel(int16_t& x, int16_t& y, int16_t& z);

    bool readGyro(int16_t& x, int16_t& y, int16_t& z);

private:

    I2c i2c;

};

}

#endif /* MPU9150_H_ */
