/*
 * bluetooth.c
 *
 *  Created on: Nov 16, 2019
 *      Author: Diego
 */

#include <stdint.h>
#include "tm4c123gh6pm.h"

void config_UART5(void) {
    SYSCTL_RCGCUART_R |= (1<<5);
    while ((SYSCTL_PRUART_R & (1<<5)) == 0);
    UART5_CTL_R &= ~(1<<0);
    UART5_IBRD_R = (UART5_IBRD_R & 0xFFFF0000) | 104;
    UART5_FBRD_R = (UART5_FBRD_R & 0xFFFFFFC0) | 11;
    UART5_LCRH_R = (UART5_LCRH_R & 0xFFFFFF00) | 0x70;
    UART5_CTL_R &= ~0x20;
    UART5_CTL_R |= ((1<<9)|(1<<8)|(1<<0));
    SYSCTL_RCGCGPIO_R |= (1<<4);
    while((SYSCTL_PRGPIO_R & (1<<4)) == 0);
    GPIO_PORTE_AFSEL_R |= ((1<<5)|(1<<4));
    GPIO_PORTE_PCTL_R = (GPIO_PORTE_PCTL_R & 0xFF00FFFF) | 0x00110000;
    GPIO_PORTE_AMSEL_R &= ~((1<<5)|(1<<4));
    GPIO_PORTE_DEN_R |= ((1<<5)|(1<<4));
}

uint8_t rx_dato(void) {
    uint8_t datoRx;
    while(UART5_FR_R & UART_FR_RXFE);
    datoRx = (uint8_t) UART5_DR_R;
    return datoRx;
}

uint8_t Recepcion_de_angulo(void){
    uint8_t ang1[3]={0,0,0};
    uint16_t j=0,ang;
    while(1){
        if((UART5_FR_R & UART_FR_RXFE)==0){
            ang1[j] = rx_dato();
            j++;
        }
        if(j==3){
            break;
        }
    }
    ang = (ang1[0]-48)*100 + (ang1[1]-48)*10 + (ang1[2]-48);
    if (ang > 180){
        ang -= 180;
    }
    return ang;
}
