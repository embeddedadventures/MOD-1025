/*
Copyright (c) 2016, Embedded Adventures
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

// ZDU0110RFX UART Interface IC Arduino library
// Written originally by Embedded Adventures

#include "Arduino.h"
#include "Wire.h"
#include "ZDU0110RFX.h"
 
ZDU0110RFXClass::ZDU0110RFXClass() {}

ZDU0110RFXClass::~ZDU0110RFXClass() {}
 
void ZDU0110RFXClass::init(uns16 IRQ_pin) 
{
	pinMode(IRQ_pin, INPUT_PULLUP);
}

void ZDU0110RFXClass::clear_data_buffer() {
	for (int i = 0; i < MAX_BUFF_LENGTH; i++) {
		data_buffer[i] = 0x00;
	}
}

/*	Returns the address of the first byte read from the chip	*/
char* ZDU0110RFXClass::read(uns8 cmd, int numchars, char *buffer) 
{
	Wire.beginTransmission(SYSTEM_ADDR);
	Wire.write(cmd);
	Wire.endTransmission(false);

	Wire.requestFrom(SYSTEM_ADDR, numchars);
	for(int x = 0; x < numchars; x++) 
	{
		if(Wire.available()) 
		{
			buffer[x] = Wire.read();
		}
	}

	delayMicroseconds(ZDU_DELAY);
	return &buffer[0];
}
	
/*	Writes the bytes in the buffer to the chip	*/
void ZDU0110RFXClass::write(uns8 cmd, int numchars, char *buffer) 
{	
	delayMicroseconds(ZDU_DELAY);
	Wire.beginTransmission(SYSTEM_ADDR);
	Wire.write(cmd); 
	for(int x = 0; x < numchars; x++) 
	{
		Wire.write(buffer[x]);
	}
	Wire.endTransmission();
	
	delayMicroseconds(ZDU_DELAY);
}


uns32 ZDU0110RFXClass::get_baud_rate() 
{       clear_data_buffer();
	uns32 baudrate;
	read(CMD_GET_BAUD_RATE, 2, &data_buffer[0]);
	baudrate = (data_buffer[0] << 8) | data_buffer[1];
	baudrate *= 100;
	return baudrate;
}

void ZDU0110RFXClass::set_baud_rate(uns32 baud_rate)
{       
	clear_data_buffer();
	baud_rate = baud_rate / 100;  
	data_buffer[0] = (baud_rate >> 8) & 0xFF;
	data_buffer[1] = (baud_rate & 0xFF);
	write(CMD_SET_BAUD_RATE, 2, &data_buffer[0]);
}

void ZDU0110RFXClass::enable_uart(uns8 enable) 
{
//0x00 disables Tx and disables Rx; 
//0x01 disables Tx and enables Rx; 
//0x02 enables Tx and disables Rx 
//0x03 enables Tx and enables Rx
    clear_data_buffer();
	if (enable) 
	{
		data_buffer[0] = 0x03;
	} 
	else 
	{
		data_buffer[0] = 0x00;
	}
	ZDU0110RFXClass::write(CMD_ENABLE_UART, 1, &data_buffer[0]);  
}

void ZDU0110RFXClass::set_tx_fifo(int numchars, char *buffer) 
{
  //tx_fifo register only accepts 31 bytes at the moment
	delayMicroseconds(100);
	write(CMD_TX_FIFO, numchars, &buffer[0]);

}

char* ZDU0110RFXClass::get_rx_fifo(int numchars) 
{   
	clear_data_buffer();
	read(CMD_RX_FIFO, numchars, &data_buffer[0]);
	return &data_buffer[0];
}

uns8 ZDU0110RFXClass::get_tx_fifo_level() 
{
    clear_data_buffer();
  	read(CMD_RXTX_FIFO_LEVEL, 2, &data_buffer[0]);
	return data_buffer[1]; //max return of 64 for each char
}

uns16 ZDU0110RFXClass::get_configuration() 
{
	clear_data_buffer();
	read(CMD_GET_CONFIGURATION, 2, &data_buffer[0]);
	return (data_buffer[0] << 8) | (data_buffer[1] & 0xFF);
}

uns8 ZDU0110RFXClass::get_rx_fifo_level() 
{
	clear_data_buffer();
  	read(CMD_RXTX_FIFO_LEVEL, 2, &data_buffer[0]);
	return data_buffer[0]; //max return of 64 for each char
}

uns8 ZDU0110RFXClass::get_system_status_reg() 
{
        clear_data_buffer();
        read(CMD_GET_STATUS_REGISTER, 1, &data_buffer[0]);
        return data_buffer[0];
}

uns8 ZDU0110RFXClass::get_uart_status_reg() 
{
      clear_data_buffer();
      read(CMD_GET_UART_STATUS_REGISTER,1,&data_buffer[0]);
      return data_buffer[0];
}

uns8 ZDU0110RFXClass::get_tx_watermark() 
{     clear_data_buffer();
      read(CMD_GET_TX_WATERMARK,1,&data_buffer[0]);
      return data_buffer[0];
}

void ZDU0110RFXClass::set_tx_watermark(uns8 watermark)
{     clear_data_buffer();
      data_buffer[0]=watermark;
      write(CMD_SET_TX_WATERMARK, 1,&data_buffer[0]);  
}

uns8 ZDU0110RFXClass::get_rx_watermark() 
{    clear_data_buffer();
     read(CMD_GET_RX_WATERMARK,1,&data_buffer[0]);
     return data_buffer[0];
}

void ZDU0110RFXClass::set_rx_watermark(uns8 watermark)
{    clear_data_buffer();
     data_buffer[0]=watermark;
     write(CMD_SET_RX_WATERMARK, 1,&data_buffer[0]);  
}

void ZDU0110RFXClass::set_interrupt(uns8 interrupt)
{
	/*
                     -----How the interrupt register RX data bit fuctions------
   In order for a read interrupt to be transmitted, the  RX FIFO register must be read afterwards.
   By setting the enable interrupt register RX data bit, a read interrupt will be transmitted when a read to the FIFO RX occurs. 
   The interrpt status register RX data bit will be set when the interrupt is ready to be transmitted 
   and will return to low after the RX FIFO register is read and the interrupt is transmitted.
      */
	clear_data_buffer();
	data_buffer[0] = interrupt;
	ZDU0110RFXClass::write(CMD_SET_ENABLE_INTERRUPTS, 1, &data_buffer[0]);  
}

uns8 ZDU0110RFXClass::get_interrupt_status_register() 
{
	clear_data_buffer();
	read(CMD_GET_INTERRUPTS_STAUTUS_REGISTER, 1, &data_buffer[0]);
	return data_buffer[0];
}


void ZDU0110RFXClass::ZDU0110RFXClass::set_configuration(uns16 con)
{
  uns8 buffer[2];
  buffer[0] = con >> 8; //MSB 
  buffer[1] = con & 0xff; //LSB
  write(CMD_SET_CONFIGURATION, 2, &data_buffer[0]);  
}

uns8 ZDU0110RFXClass::get_last_operation_result()
{
	char lor;
	read(CMD_GET_LOR, 2, &lor);
	if (lor == 0)
		return 1;
	else
		return 0;
}



 



