#ifndef MPU9150DEFS_H_
#define MPU9150DEFS_H_

namespace mpu {

// Registers
#define MPU9150_REG_GYRO_CONFIG     0x1B
#define MPU9150_REG_ACCEL_CONFIG    0x1C
#define MPU9150_REG_ACCEL_XOUT_H    0x3B
#define MPU9150_REG_ACCEL_XOUT_L    0x3C
#define MPU9150_REG_ACCEL_YOUT_H    0x3D
#define MPU9150_REG_ACCEL_YOUT_L    0x3E
#define MPU9150_REG_ACCEL_ZOUT_H    0x3F
#define MPU9150_REG_ACCEL_ZOUT_L    0x40
#define MPU9150_REG_GYRO_XOUT_H     0x43
#define MPU9150_REG_GYRO_XOUT_L     0x44
#define MPU9150_REG_GYRO_YOUT_H     0x45
#define MPU9150_REG_GYRO_YOUT_L     0x46
#define MPU9150_REG_GYRO_ZOUT_H     0x47
#define MPU9150_REG_GYRO_ZOUT_L     0x48
#define MPU9150_REG_PWR_MGMT_1      0x6B

enum GyroFullScaleRange
{
    GFSR_250 = 0,
    GFSR_500,
    GFSR_1000,
    GFSR_2000
};

enum AccelFullScaleRange
{
    AFSR_2g = 0,
    AFSR_4g,
    AFSR_8g,
    AFSR_16g
};

enum ClockSource
{
    CS_8MHZ_INT_OSC = 0,
    CS_GYRO_X_AXIS_REF,
    CS_GYRO_Y_AXIS_REF,
    CS_GYRA_Z_AXIS_REF
};

}

#endif /* MPU9150DEFS_H_ */
