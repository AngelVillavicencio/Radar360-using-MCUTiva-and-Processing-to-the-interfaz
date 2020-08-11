/*
 * motor.h
 *
 *  Created on: 15 nov. 2019
 *      Author: ÁNGEL ARTURO
 */

#ifndef MOTOR_H_
#define MOTOR_H_
void config_pulsadores(void);
void config_leds(void);
//const uint8_t secuencia[]={0b1100,0b0110,0b0011,0b1001};
const uint32_t Velocidad[]={250000,125000,62500,31250};
#define HORARIO 0
#define ANTIHORARIO 1
uint8_t unpaso (uint8_t pos, uint8_t sentido);
uint8_t funcion_cambia_sentido(uint8_t sentido);
uint8_t Funcion_calibracion (uint8_t posicion_anterior);
uint8_t gira_angulo_de_desplazamiento(uint8_t angulo_desplazamiento,uint8_t SENTIDO_DE_DESPLAZAMIENTO,uint8_t Paso_anterior);
#endif /* MOTOR_H_ */
