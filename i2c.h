#ifndef I2C_H_
#define I2C_H_

#include <stdint.h>

class I2c
{
public:

    I2c(uint8_t addr);

    static void init();

    bool read(uint8_t& data);

    bool readNoStop(uint8_t& data);

    bool write(uint8_t* pData, int dataLength);

    bool writeNoStop(uint8_t* pData, int dataLength);

private:

    void transmit();

    bool transmitStart(bool repeatedStart);

    void transmitStop();

    bool transmitSlaR();

    bool transmitSlaW();

    bool transmitData(uint8_t data);

    bool receiveData(uint8_t& data);

    void waitForFlag();

    void error(const char* msg, uint8_t status);

    uint8_t getStatus() const;

    uint8_t getData() const;

    uint8_t m_addr;

    bool m_isRepeatedStart;

};

#endif /* I2C_H_ */
