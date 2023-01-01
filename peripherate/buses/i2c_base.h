#ifndef I2C_BASE_H
#define I2C_BASE_H

#include <stddef.h>

#include "err_codes.h"

class i2c_base {
public:
    i2c_base() {}
    virtual ~i2c_base() = 0;

    /**
     * Initializes I2C interface and registers interrupt with IRQ handler.
     *
     * @param device_id address of i2c device to read data from.
     * @param irq_num address of i2c device to read data from.
     * @param sclk_freq pointer to buffer to copy results of read into
     * @return upon success 0 is returned, upon error -eErrCode is returned.
     */
    int initialize(unsigned short device_id, unsigned char irq_num,
        unsigned int sclk_freq);

    /**
     * Initializes I2C interface. Polled functionality enabled.
     *
     * @param device_id address of i2c device to read data from.
     * @param irq_num address of i2c device to read data from.
     * @param sclk_freq pointer to buffer to copy results of read into
     * @return upon success 0 is returned, upon error -eErrCode is returned.
     */
    int initialize(unsigned short device_id, unsigned int sclk_freq);

    /**
     * Mutex protected invokation of hw_reset().
     *
     * @return upon success 0 is returned, upon error -eErrCode is returned.
     */
    int reset();

    /**
     * Reads data from specified register on peripheral I2C device into buffer.
     *
     * @param iic_address address of i2c device to read data from.
     * @param register_address address of i2c device to read data from.
     * @param pbuf pointer to buffer to copy results of read into
     * @param buf_size size of the buffer pointed to by pbuf
     * @param max_wait_millis amount of time given to transfer before timeout error is returned
     * @return upon success 0 is returned, upon error -eErrCode is returned.
     */
    int read(unsigned int iic_address, unsigned int register_address, char* pbuf, const size_t buf_size, const unsigned int max_wait_millis = 0);

    /**
     * Writes data from buffer to specified register on peripheral I2C device.
     *
     * @param iic_address address of i2c device to read data from.
     * @param register_address address of i2c device to read data from.
     * @param pwrite pointer to data intended to write to buffer
     * @param data_size size of the buffer pointed to by pbuf
     * @param max_wait_millis amount of time given to transfer before timeout error is returned
     * @return upon success 0 is returned, upon error -eErrCode is returned.
     */
    int write(unsigned int iic_address, unsigned int register_address, char* pdata, const size_t data_size, const unsigned int max_wait_millis = 0);

private:
    // can be overloaded to protect 
    virtual bool trans_lock_guard() { return true; };
    virtual bool trans_unlock_guard() { return true; };

    // the following interface functions are called by public interfaces, and 
    // are wrapped to ensure re-entrancy.
    virtual bool hw_initialize() = 0;
    virtual bool hw_send(unsigned char iic_addr, unsigned char* pwrite_data,
        size_t write_bytes) = 0;
    virtual unsigned int hw_receive(unsigned char iic_addr, unsigned char* pwrite_data,
        size_t write_bytes, unsigned char* pread_data,
        size_t max_read_size,
        bool useRepeatedStart = false, bool isBlockRead = false) = 0;
    virtual bool hw_wait_busy() = 0;
    virtual bool hw_bus_busy() = 0;
    virtual bool initialize_interrupt_request() = 0;
    virtual bool hw_wait_tx_complete() = 0;
    virtual bool hw_wait_rx_complete() = 0;

    // no copies 
    i2c_base(i2c_base const&) = delete;
    void operator=(i2c_base const& x) = delete;

};

#endif // I2C_BASE_H