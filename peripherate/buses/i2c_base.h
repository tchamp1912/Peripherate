#ifndef I2C_BASE_H
#define I2C_BASE_H

#include <stddef.h>

class i2c_base {
public:
    i2c_base() {}
    virtual ~i2c_base() = 0;

    int initialize(unsigned short device_id, unsigned char irq_num,
        unsigned int sclk_freq);
    int initialize(unsigned short device_id, unsigned int sclk_freq);

    int reset();

    /**
     * Reads data from peripheral I2C device.
     *
     *
     *
     * @param iic_address address of i2c device to read data from.
     * @param register_address address of i2c device to read data from.
     * @return upon success 0 is returned, upon error -eErrCode is returned.
     */
    int read(unsigned int iic_address, unsigned int register_address, char* pbuf, size_t buf_size, unsigned int max_wait_millis = 0);
    int write(unsigned int iic_address, unsigned int register_address, char* pdata, size_t num_bytes, unsigned int max_wait_millis = 0);

    enum eErrCodes: int {
        INIT_FAIL,
        INTERRUPT_REGISTER_FAILED,
        TRANS_TIMEOUT,
        TRANS_LOCK_FAILED,
        RESET_FAILED,
    };

private:
    virtual bool trans_lock_guard() { return true; };
    virtual bool trans_unlock_guard() { return true; };

    // the following interface functions are called by 

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