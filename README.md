# MOD-1025
Arduino library and Serial wrapper for the <a href="http://www.embeddedadventures.com/i2c_to_uart_mod-1025.html"> MOD-1025 ZDU0110 UART Interface IC</a>.

This repo includes source files for interacting with the ZDU0110RFX and a wrapper for the library, modeling it after the Arduino Serial library. 

## Using the ZDUSerial library ##

	ZDUSerial zdu;
First thing to be done is to create the ZDUSerial object

	zdu.begin(2);			//Default baud rate is 57200
	zdu.begin(2, 115200);
The begin() function is very similar to the Arduino Serial function, begin(). The main difference is that in addition to baud rate, we also need to include a pin that we will use for interrupts so the ZDU can notify us of new Serial data. The default baud rate of the ZDU0110 is 57200, which is the baud rate used if we only declare the interrupt pin.

From there, we can use the library in the same manner as the Serial object's library. Off you go to include a UART port to your project's I2C bus!

## Wiring ##
Connect the TX line of the device to the TX line of the MOD-1025. The same goes for the RX line.

## Contact ##
Questions/comments/concerns regarding the code? Raise it up as a <a href="https://github.com/embeddedadventures/MOD-1025/issues/new">new issue</a> and we will help as soon as possible. You may also contact support@embeddedadventures.com. Thanks!

----------
<h2>TODO</h2>

- [] Include check for buffer overflow
- [] Include functions to utilize ZDU0110 GPIO pins
