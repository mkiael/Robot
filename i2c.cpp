#include "i2c.h"
#include <avr/io.h>
#include <util/twi.h>

// TBR
#include <Arduino.h>

#define TWI_PRE     1
#define TWI_FREQ    100000 // 100kHz

#define SDA_PORT    PORTC
#define SDA_BIT     PC4
#define SCL_PORT    PORTC
#define SCL_BIT     PC5

I2c::I2c(uint8_t addr)
: m_addr(addr)
, m_isRepeatedStart(false)
{
}

void I2c::init()
{
    SDA_PORT |= _BV(SDA_BIT);
    SCL_PORT |= _BV(SCL_BIT);

    TWBR = (F_CPU/TWI_FREQ-16)/TWI_PRE/2;
    TWSR = (0<<TWPS0);
}

bool I2c::read(uint8_t& data)
{
    if (!readNoStop(data))
    {
        return false;
    }

    transmitStop();

    m_isRepeatedStart = false;

    return true;
}

bool I2c::readNoStop(uint8_t& data)
{
    if (!transmitStart(m_isRepeatedStart))
    {
        return false;
    }

    if (!transmitSlaR())
    {
        return false;
    }

    transmit();

    if (!receiveData(data))
    {
        return false;
    }

    m_isRepeatedStart = true;

    return true;
}

bool I2c::write(uint8_t* pData, int dataLength)
{
    if (!writeNoStop(pData, dataLength))
    {
        return false;
    }

    transmitStop();

    m_isRepeatedStart = false;

    return true;
}

bool I2c::writeNoStop(uint8_t* pData, int dataLength)
{
    if (!transmitStart(m_isRepeatedStart))
    {
        return false;
    }

    if (!transmitSlaW())
    {
        return false;
    }

    for (int i = 0; i < dataLength; ++i)
    {
        if (!transmitData(pData[i]))
        {
            return false;
        }
    }

    m_isRepeatedStart = true;

    return true;
}

void I2c::transmit()
{
    TWCR = _BV(TWINT) | _BV(TWEN);

    // Wait for TWINT to be set (means ACK received)
    while (!(TWCR & _BV(TWINT)))
        ;
}

bool I2c::transmitStart(bool repeatedStart)
{
    TWCR = _BV(TWINT) | _BV(TWSTA) | _BV(TWEN);

    waitForFlag();

    uint8_t expextedStatus = repeatedStart ? TW_REP_START : TW_START;

    if (getStatus() != expextedStatus)
    {
        if (repeatedStart)
        {
            error("Error transmitting START", getStatus());
        }
        else
        {
            error("Error transmitting REPEATED START", getStatus());
        }
        return false;
    }

    return true;
}

void I2c::transmitStop()
{
    TWCR = _BV(TWINT) | _BV(TWEN) | _BV(TWSTO);
}

bool I2c::transmitSlaR()
{
    // Load address
    TWDR = (m_addr << 1) | TW_READ;

    transmit();

    waitForFlag();

    if (getStatus() != TW_MR_SLA_ACK)
    {
        error("Error transmitting SLA+R", getStatus());
        return false;
    }

    return true;
}

bool I2c::transmitSlaW()
{
    // Load address
    TWDR = (m_addr << 1) | TW_WRITE;

    transmit();

    waitForFlag();

    if (getStatus() != TW_MT_SLA_ACK)
    {
        error("Error transmitting SLA+W", getStatus());
        return false;
    }

    return true;
}

bool I2c::transmitData(uint8_t data)
{
    TWDR = data;

    transmit();

    if (getStatus() != TW_MT_DATA_ACK)
    {
        error("Error transmitting data", getStatus());
        return false;
    }

    return true;
}

bool I2c::receiveData(uint8_t& data)
{
    if (getStatus() == TW_MR_DATA_ACK || getStatus() == TW_MR_DATA_NACK)
    {
        data = getData();
        return true;
    }
    else
    {
        error("Error reading data", getStatus());
        return false;
    }
}

void I2c::waitForFlag()
{
    // Wait for TWINT to be set by hardware
    while (!(TWCR & _BV(TWINT)))
        ;
}

void I2c::error(const char* msg, uint8_t status)
{
    transmitStop();

    Serial.print(msg);
    Serial.print(" (");
    Serial.print(status);
    Serial.print(")\n");
}

uint8_t I2c::getStatus() const
{
    return TW_STATUS;
}

uint8_t I2c::getData() const
{
    return TWDR;
}
