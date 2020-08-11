/*
 * motor.h
 *
 *  Created on: 15 nov. 2019
 *      Author: ÁNGEL ARTURO
 */

#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "ultrasonido.h"
#define HORARIO 0
#define ANTIHORARIO 1

void config_leds(void){
    SYSCTL_RCGCGPIO_R |= (1<<1);
    while((SYSCTL_PRGPIO_R & (1<<1))==0);
    GPIO_PORTB_DIR_R |= ((1<<4)|(1<<5)|(1<<6)|(1<<7));
    GPIO_PORTB_DEN_R |= ((1<<4)|(1<<5)|(1<<6)|(1<<7));
    GPIO_PORTB_AMSEL_R &= ~((1<<4)|(1<<5)|(1<<6)|(1<<7));
    GPIO_PORTB_AFSEL_R &= ~((1<<4)|(1<<5)|(1<<6)|(1<<7));
}
uint8_t funcion_cambia_sentido(uint8_t sentido){
    if(sentido==ANTIHORARIO){
        sentido=HORARIO;
    }
    else if(sentido==HORARIO){
        sentido=ANTIHORARIO;
    }
 return sentido;
}
const uint8_t secuencia[]={0b1100,0b0110,0b0011,0b1001};
//const uint32_t Velocidad[]={250000,125000,62500,31250};




uint8_t unpaso (uint8_t pos, uint8_t sentido){
int p;
uint8_t led_horario,led_antihorario;
    if(pos==secuencia[0]){
        p=0;
        led_horario=(1<<5)|(1<<6);
        led_antihorario=(1<<4)|(1<<7);

    }
    if(pos==secuencia[1]){
        p=1;
        led_horario=(1<<6)|(1<<7);
        led_antihorario=(1<<4)|(1<<5);
    }
    if(pos==secuencia[2]){
        p=2;
        led_horario=(1<<4)|(1<<7);
        led_antihorario=(1<<5)|(1<<6);
    }
    if(pos==secuencia[3]){
        p=3;
        led_horario=(1<<4)|(1<<5);
        led_antihorario=(1<<6)|(1<<7);
    }
    if (sentido == HORARIO){
        p++;
        if(p>=4){
            p=0;
        }
    GPIO_PORTB_DATA_R&=0b00000000;
    GPIO_PORTB_DATA_R|=led_horario;


    }else if(sentido== ANTIHORARIO){
        p--;
        if(p<0){
            p=3;
        }
        GPIO_PORTB_DATA_R&=0b00000000;
        GPIO_PORTB_DATA_R|=led_antihorario;

    }
return secuencia[p];
}

uint8_t Funcion_calibracion (uint8_t posicion_anterior){
    uint8_t N=0;
    uint8_t d=36;
    uint8_t SENTIDO= HORARIO;
    uint32_t velocidad=31250;
    while (d>=10 || d<=5){
        d=distancia(TRIG1,ECHO1);
        posicion_anterior=unpaso(posicion_anterior,SENTIDO);
        N++;
        if(N==100){
            SENTIDO=funcion_cambia_sentido(SENTIDO);
            N=0;
        }
        retardo_us(velocidad);
    }
    return posicion_anterior;
}

uint8_t gira_angulo_de_desplazamiento(uint8_t angulo_desplazamiento,uint8_t SENTIDO_DE_DESPLAZAMIENTO,uint8_t Paso_anterior){
    uint8_t pasos_por_girar,w=0;
    pasos_por_girar=angulo_desplazamiento*100/180;
    while(w<pasos_por_girar){
        Paso_anterior=unpaso(Paso_anterior,SENTIDO_DE_DESPLAZAMIENTO);
        retardo_us(31250);
        w++;
    }
    return Paso_anterior;
}
