#ifndef UTIL_H
#define UTIL_H

#define DDR(X) _DDR(X)
#define _DDR(X) (DDR ## X)

#define PORT(X) _PORT(X)
#define _PORT(X) (PORT ## X)

#define PIN(X) _PIN(X)
#define _PIN(X) (PIN ## X)

#define INPUT(DDR, BIT) 	DDR &= ~(1 << BIT)
#define INPUT_DDR(X, BIT)	DDR(X) &= ~(1 << BIT)

#define OUTPUT(DDR, BIT)	DDR |= (1 << BIT)
#define OUTPUT_DDR(X, BIT)	DDR(X) |= (1 << BIT)

#define LOW(PORT, BIT)		PORT &= ~(1 << BIT)
#define LOW_PORT(X, BIT)	PORT(X) &= ~(1 << BIT)

#define HIGH(PORT, BIT)		PORT |= (1 << BIT)
#define HIGH_PORT(X, BIT)	PORT(X) |= (1 << BIT)

#define IS_LOW(PIN, BIT)	(!(PIN & (1 << BIT)))
#define IS_LOW_PIN(X, BIT)	(!(PIN(X) & (1 << BIT))

#define IS_HIGH(PIN, BIT)	(PIN & (1 << BIT))
#define IS_HIGH_PIN(X, BIT)	(PIN(X) & (1 << BIT))

#endif // UTIL_H
