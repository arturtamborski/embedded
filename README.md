# embeded
Bunch of simple embeded projects written for AVR chips

## bluetooth UART
Most of those projects use bluetooth UART module HC-05 for debugging purposes.
You'll need bluetooth drivers (ath3k in my case `apt install firmware-atheros`) and bit of patience.

HC-05 blinks constantly when it's disconnected, but it flashes shortly two times every second when it is connected

Here's how i connected it to the microcontroller:
```text
  HC-05  --  AVR
-------------------
  STATE  ->  NC
     RX  ->  TXD
     TX  ->  RXD
    GND  ->  GND
    +5V  ->  VCC
     EN  ->  NC

NC: Not Connected
```

```shell
  # scan for MAC address
  hcitool scan

  # it if it found something then you're ok
  # if not then be sure that you're visible and the module is in range
  # also, make sure that it its powered on and your bluetooth is turned on

  # connect
  sudo rfcomm /dev/rfcomm0 <MAC ADDRESS HERE> 1

```

in separate terminal
```shell
  # read the virtual tty
  sudo cat /dev/rfcomm0

  # or use something more advanced
  sudo apt install minicom
  minicom -D /dev/rfcomm0
```


TODO: insert more content here

## links:
  - [AVR Libc Home Page](https://www.nongnu.org/avr-libc/)
