#ifndef ADC_BASE_H
#define ADC_BASE_H

#include <stddef.h>

template<typename reg_type, size_t nbits, >
class adc_base {
public:
    adc_base() {}
    virtual ~adc_base() = 0;

    /**
     * Initializes I2C interface. Polled functionality enabled.
     *
     * @return upon success 0 is returned, upon error -eErrCode is returned.
     */
    int initialize();

private:

    // no copies 
    adc_base(adc_base const&) = delete;
    void operator=(adc_base const& x) = delete;

};

#endif // ADC_BASE_H