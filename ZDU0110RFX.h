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

#ifndef __ZDU0110RFX_h
#define __ZDU0110RFX_h

#define uns8 unsigned char
#define uns16 unsigned int
#define uns32 unsigned long

#define		MAX_BUFF_LENGTH		64
#define		ZDU_DELAY			5

#define eeprom_addr 0x53
#define SYSTEM_ADDR 0x5b 
				            //ZDU0110RFX Commands
#define CMD_SET_CLR                         0x02
#define CMD_GET_CLR                         0x03
#define CMD_GET_SYSTEM_VERSION              0xE5
#define CMD_GET_SYSTEM_STATUS               0xE1
#define CMD_GET_LOR                         0xE3
#define CMD_GET_GPIO_CONFIG                 0x09
#define CMD_GET_TX_WATERMARK                0x2B
#define CMD_SET_TX_WATERMARK                0x2A
#define CMD_GET_RX_WATERMARK                0x2D
#define CMD_SET_RX_WATERMARK                0x2C
#define CMD_ENABLE_UART                     0x2E
#define CMD_TX_FIFO                         0x24  //tx_fifo register only accepts 31 bytes
#define CMD_RX_FIFO                         0x25
#define CMD_RXTX_FIFO_LEVEL                 0x31
#define CMD_GET_BAUD_RATE                   0x27
#define CMD_SET_BAUD_RATE                   0x26
#define CMD_GET_LOR                         0xE3
#define CMD_GET_STATUS_REGISTER             0xE1
#define CMD_GET_UART_STATUS_REGISTER        0x21
#define CMD_SET_ENABLE_INTERRUPTS           0x22
#define CMD_GET_INTERRUPTS_STAUTUS_REGISTER 0x23
#define CMD_SET_CONFIGURATION               0x28
#define CMD_GET_CONFIGURATION               0x29

//Interrupt Types
#define	IRQ_TX_EMPTY						0x80
#define IRQ_TX_WTRMK						0x40
#define	IRQ_TX_FULL							0x20
#define	IRQ_BREAK							0x10
#define IRQ_RX_DATA							0x08
#define IRQ_RX_WTRMK						0x04
#define	IRQ_RX_FULL							0x02
#define IRQ_ERROR							0x01
 
class ZDU0110RFXClass
{
	
private:
	char	data_buffer[MAX_BUFF_LENGTH];

	void	clear_data_buffer();
	char* 	read(uns8 cmd, int numchars, char *buffer);
	void 	write(uns8 cmd, int numchars, char *buffer);

public:
	ZDU0110RFXClass();
	~ZDU0110RFXClass();
	void 	init(uns16 IRQ_pin);
	uns32 	get_baud_rate();
	void 	set_baud_rate(uns32 baud_rate);
	void	enable_uart(uns8 enable);
	void 	set_tx_fifo(int numchars, char* buffer); 
	uns8 	get_tx_fifo_level();
	uns16 	get_configuration();
	uns8 	get_rx_fifo_level();
	char* 	get_rx_fifo(int numchars);
	
	void 	set_interrupt(uns8 interrupt);
	uns8 	get_interrupt_status_register();
	void 	set_configuration(uns16 con);
	uns8 	get_tx_watermark();
	void 	set_tx_watermark(uns8 watermark);
	uns8 	get_rx_watermark();
	void 	set_rx_watermark(uns8 watermark);
	uns8 	get_system_status_reg();
	
	uns8 	get_uart_status_reg();
	uns8 	get_last_operation_result();

};

#endif
 



