#ifndef ADC_BASE_H
#define ADC_BASE_H

#include <stddef.h>

#include <buses.h>

template<class bus_type, typename val_type, size_t nchannels>
class adc_base {
public:
    adc_base(bus_type* bus) {}
    virtual ~adc_base() = 0;

    /**
     * Initializes ADC interface. Polled functionality enabled.
     *
     * @return upon success 0 is returned, upon error -eErrCode is returned.
     */
    int initialize();

    virtual val_type read_value(unsigned int channel) = 0;


private:
    bus_type* bus;

    // no copies 
    adc_base(adc_base const&) = delete;
    void operator=(adc_base const& x) = delete;

};

using adc8_i2c_base<size_t nchannels> = adc_base<i2c_base, unsigned char, nchannels>; // 8 bit i2c adc

#endif // ADC_BASE_H