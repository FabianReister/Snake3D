#include "ioexpander.h"

template <uint8_t N>
IoExpander<N>::IoExpander(I2C* i2c, char slave_address ) : _i2c(i2c), SLAVE_ADDRESS(slave_address)
{

}



template class IoExpander<1>;
template class IoExpander<2>;
