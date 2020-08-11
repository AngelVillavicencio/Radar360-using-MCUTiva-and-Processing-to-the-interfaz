/*
 * ultrasonido.c
 *
 *  Created on: Nov 6, 2019
 *      Author: Diego
 */

#define TRIG1 (1<<2)
#define ECHO1 (1<<3)
#define TRIG2 (1<<4)
#define ECHO2 (1<<5)

#include <stdint.h>
#include "tm4c123gh6pm.h"

void retardo_us (uint32_t tiempo){
    uint32_t i;
    SYSCTL_RCGCTIMER_R |= (1<<0);                           //ACTIVAMOS LA SEÑAL DE RELOJ DEL TIMER0
    while((SYSCTL_PRTIMER_R & (1<<0)) == 0);                //ESPERAMOS A QUE SE ACTIVE LA SEÑAL DE RELOJ
    TIMER0_CTL_R &= ~(1<<0);                                //TIMER0 DESACTIVADO ANTES DE LA INICIALIZACION
    TIMER0_CFG_R &= ~((1<<2)|(1<<1)|(1<<0));                //ASEGURAMOS LOS 3 BITS MENOS SIGNIFICATIVOS DE CFG A 0
    TIMER0_CFG_R |= (1<<2);                                 //MODO 16 BITS DEL TIMER0
    TIMER0_TAMR_R &= ~0xFFF;                                //ASEGURAMOS LOS 12 BITS MENOS SIGNIFICATIVOS DE TAMR A 0
    TIMER0_TAMR_R |= (1<<2);                                //MODO PERIODICO ACTIVADO Y MODO DOWN-COUNTER SE ACTIVA CON 0 EN EL BIT 4
    TIMER0_TAILR_R = 16 - 1;                                //INTERVALO DEL TIMER0A 0-15 PARA 1us
    TIMER0_ICR_R |= (1<<0);                                 //BANDERA TIMEOUT PARA EL TIMER0A A 0
    TIMER0_CTL_R |= (1<<0);                                 //TIMER0 ACTIVADO LUEGO DE LA INICIALIZACION
    for(i=0; i<tiempo; i++){                                //CONTADOR PARA EL TIEMPO DESEADO
        while((TIMER0_RIS_R & (1<<0)) == 0);                //ESPERA A QUE LA BANDERA DE TIMEOUT PARA TIMER0A SE ACTIVE
        TIMER0_ICR_R |= (1<<0);                             //BANDERA TIMEOUT PARA EL TIMER0A A 0
    }
}

uint8_t distancia(uint8_t Trig,uint8_t Echo){
    uint8_t tiempo=10;
    uint8_t distancia;                                         //DISTANCIA EN CM
    uint32_t contador;
    GPIO_PORTA_DATA_R &= ~Trig;
    GPIO_PORTA_DATA_R |= Trig;
    retardo_us(tiempo);
    GPIO_PORTA_DATA_R &= ~Trig;
    contador = 0;
    while((GPIO_PORTA_DATA_R & Echo) == 0);
    while(((GPIO_PORTA_DATA_R & Echo) != 0) & (contador < 350000)){
        contador++;
        retardo_us(1);
    }
    distancia = contador * 0.165000 ;
    return distancia;
}

void config_portA(void){
    SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R0;
    while ((SYSCTL_PRGPIO_R & SYSCTL_PRGPIO_R0) == 0);
    GPIO_PORTA_DIR_R |= (TRIG1|TRIG2);                      //PA2 y PA4 como salida
    GPIO_PORTA_DIR_R &= ~(ECHO1|ECHO2);                     //PA3 y PA5 como entrada
    GPIO_PORTA_AMSEL_R &= ~(ECHO2|TRIG2|ECHO1|TRIG1);       //AMSEL desactivado
    GPIO_PORTA_AFSEL_R &= ~(ECHO2|TRIG2|ECHO1|TRIG1);       //AFSEL desactivado
    GPIO_PORTA_DEN_R |= (ECHO2|TRIG2|ECHO1|TRIG1);          //Pines digitales
}

void config_UART0(void){
    SYSCTL_RCGCUART_R |= (1<<0);
    while ((SYSCTL_PRUART_R & (1<<0)) == 0);
    UART0_CTL_R &= ~(1<<0);

    GPIO_PORTA_AFSEL_R |= 0x03;
    GPIO_PORTA_PUR_R &= ~0x03;
    GPIO_PORTA_PDR_R &= ~0x03;
    GPIO_PORTA_DIR_R &= ~0x01;
    GPIO_PORTA_DIR_R |= 0x02;
    GPIO_PORTA_PCTL_R = (GPIO_PORTA_PCTL_R & 0xFFFFFF00) | 0x00000011;
    GPIO_PORTA_DEN_R |= 0x03;

    UART0_IBRD_R = (UART0_IBRD_R & ~0xFFFF) + 104;
    UART0_FBRD_R = (UART0_FBRD_R & ~0x3F) + 11;
    UART0_LCRH_R = (UART0_LCRH_R & ~0xFF) | 0x70;
    UART0_CTL_R &= ~0x20;
    UART0_CTL_R |= 0x301;
}

void tx_char (char c){
    while ((UART0_FR_R & (1<<5)) != 0);
    UART0_DR_R = c;
}

void tx_mens(uint8_t mens[]){
    uint8_t letra;
    uint8_t i=0;
    letra= mens[i++];
    while (letra != '\0'){
        tx_char(letra);
        letra= mens[i++];
    }
}

void tx_num (uint8_t n){
    while ((UART0_FR_R & (1<<5)) != 0);
    UART0_DR_R = n;
}
