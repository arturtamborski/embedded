#ifndef UTIL_H
#define UTIL_H

#define INPUT(DDR, BIT) 	DDR &= ~(1 << BIT)
#define OUTPUT(DDR, BIT)	DDR |= (1 << BIT)

#define LOW(PORT, BIT)		PORT &= ~(1 << BIT)
#define HIGH(PORT, BIT)		PORT |= (1 << BIT)

#define IS_LOW(PIN, BIT)	(!(PIN & (1 << BIT)))
#define IS_HIGH(PIN, BIT)	(PIN & (1 << BIT))

#endif // UTIL_H
