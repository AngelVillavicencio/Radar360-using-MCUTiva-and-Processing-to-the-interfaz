/*
 * ultrasonido.h
 *
 *  Created on: Nov 6, 2019
 *      Author: Diego
 */

#ifndef ULTRASONIDO_H_
#define ULTRASONIDO_H_

#define TRIG1 (1<<2)
#define ECHO1 (1<<3)
#define TRIG2 (1<<4)
#define ECHO2 (1<<5)

void config_portA(void);
void config_UART0(void);
void retardo_us (uint32_t tiempo);
uint8_t distancia(uint8_t Trig,uint8_t Echo);
void tx_char (char c);
void tx_mens(uint8_t mens[]);
void tx_num (uint8_t n);

#endif /* ULTRASONIDO_H_ */
