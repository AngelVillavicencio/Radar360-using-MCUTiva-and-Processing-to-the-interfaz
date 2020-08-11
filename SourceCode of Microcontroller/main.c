#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "ultrasonido.h"
#include "motor.h"
#include "bluetooth.h"

void main (void){

    uint16_t m;
    uint8_t dS1,dS2;
    config_portA();
    config_UART0();
    config_UART5();
    for (m=0;m<417;m++);
    uint8_t SENTIDO= ANTIHORARIO;
    uint8_t posicion_anterior;
    ///nuevas variables:
    uint8_t MODO;
    uint8_t angulo_deseado;
    uint8_t angulo;
    int angulo_desplazamiento;
    uint8_t SENTIDO_DE_DESPLAZAMIENTO;
    uint8_t pasos,paso;
    uint8_t LETRA;
    int incremento;
    uint8_t f,f2;

////
    config_leds();
    posicion_anterior=0b1100;

    while(1){

        posicion_anterior=Funcion_calibracion(posicion_anterior);
        angulo = 0;
        MODO=0;

        while(1){
        LETRA=rx_dato();
        if(LETRA=='M'){
           MODO='M';
           break;
        }else if(LETRA=='A'){
           MODO='A';
           break;
        }else{};
        }
        while(1){
            if(MODO=='M'){




                angulo_deseado=Recepcion_de_angulo();
                    if(angulo_deseado>=180){
                            angulo_deseado=angulo_deseado-180;
                        }
                        angulo_desplazamiento=angulo_deseado-angulo;
                            if(angulo_desplazamiento>0){
                                SENTIDO_DE_DESPLAZAMIENTO=ANTIHORARIO;
                                posicion_anterior=gira_angulo_de_desplazamiento(angulo_desplazamiento,SENTIDO_DE_DESPLAZAMIENTO,posicion_anterior);
                            }else{
                                SENTIDO_DE_DESPLAZAMIENTO=HORARIO;
                                angulo_desplazamiento*=-1;
                                posicion_anterior=gira_angulo_de_desplazamiento(angulo_desplazamiento,SENTIDO_DE_DESPLAZAMIENTO,posicion_anterior);
                            }
                             angulo = angulo_deseado;
                        ///empezamos a trasmitir
                        while(1){
                            dS1 = distancia(TRIG1,ECHO1);
                            if (dS1 > 61){
                                   dS1 = 0;
                               }
                            dS2 = distancia(TRIG2,ECHO2);
                               if (dS2 >61){
                                   dS2 = 0;
                               }
                               retardo_us(31250);
                               pasos=angulo*100/180;
                               ////////ENVIO DE DATOS/////////////////////
                               tx_num(255);
                               tx_num(pasos);
                               tx_num(dS1);
                               tx_num(dS2);
                            if((UART5_FR_R & UART_FR_RXFE)==0){
                                f = rx_dato();
                                if (f == 'A'){
                                    MODO='A';
                                    break;
                                }
                                else if (f == 'M'){

                                    break;
                                }
                            }
                        }
                        }
           if(MODO=='A'){
               pasos=angulo*100/180;
               paso=angulo*100/180;
               SENTIDO=ANTIHORARIO;
               incremento=1;
                        while(1){
                            while(pasos<=100){
                                posicion_anterior=unpaso(posicion_anterior,SENTIDO);





                                paso=paso+incremento;

                                pasos++;
                                dS1 = distancia(TRIG1,ECHO1);
                                if (dS1 > 61){
                                    dS1 = 0;
                                }
                                dS2 = distancia(TRIG2,ECHO2);
                                if (dS2 >61){
                                    dS2 = 0;
                                }
                                retardo_us(31650);
                                tx_num(255);
                                tx_num(paso);
                                tx_num(dS1);
                                tx_num(dS2);
                                if((UART5_FR_R & UART_FR_RXFE)==0){
                                    f2 = rx_dato();
                                    if (f2 == 'M'){
                                        MODO='M';
                                        angulo=paso*180/100;
                                    }
                                    break;
                                }

                            }
                            pasos=0;
                            SENTIDO=funcion_cambia_sentido(SENTIDO);

                            incremento=incremento*-1;
                            if(MODO=='M'){

                                break;
                            }
                        }
           }

        }



    }

}
