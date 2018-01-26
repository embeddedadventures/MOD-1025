/*
Copyright (c) 2018, Embedded Adventures
All rights reserved.
Contact us at source [at] embeddedadventures.com
www.embeddedadventures.com
Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
- Redistributions of source code must retain the above copyright notice,
  this list of conditions and the following disclaimer.
- Redistributions in binary form must reproduce the above copyright
  notice, this list of conditions and the following disclaimer in the
  documentation and/or other materials provided with the distribution.
- Neither the name of Embedded Adventures nor the names of its contributors
  may be used to endorse or promote products derived from this software
  without specific prior written permission.
 
THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF 
THE POSSIBILITY OF SUCH DAMAGE.
*/

// ZDU0110RFX UART Interface IC Arduino test sketch
// Written originally by Embedded Adventures

/*
 * This demo sketch requires the use of another device to act as a UART receiver.
 * The Arduino sends the "welcome" message via I2C to the MOD-1025, which then sends 
 * it to the UART receiver. 
 * REMEMBER - the TX pin of the MOD-1025 must be connected to the TX pin of the 
 * receiver. The same goes for the RX line.
 */


#include <Wire.h>
#include <ZDU0110RFX.h>
#include <ZDUSerial.h>


ZDUSerial zdu;
const int irqPin = 2; //An interrupt pin is required for utilizing the MOD-1025

void setup() {
  Wire.begin();
  zdu.begin(irqPin, 115200);
  delay(100);
  zdu.println("Welcome to the MOD-1025 (ZDU0110RFX) UART Interface IC test sketch!");
  zdu.println("Embedded Adventures (www.embeddedadventures.com)\n");
}

void loop() {
  //This loop echoes any input from the other UART device.
  if (zdu.available()) {
    char input = zdu.read();
    zdu.print("Hello");
    zdu.print(" from the other side\n");
    zdu.print(" - ");
    zdu.println(input);
  }
}
