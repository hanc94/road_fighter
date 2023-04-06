#ifndef JUEGO_H
#define JUEGO_H
#include <Timer.h>
#include <Event.h>
#include "Arduino.h"
#include <LiquidCrystal.h>

#define Sib 446 //si
#define do 261 //do
#define re 294 //re
#define mi 329 //mi
#define fa 349 //fa
#define sol 392 //sol
#define la 440 //la
#define si 493 //si
#define Do 523 //doo
#define Re 588 //re
#define Mi 658 //mi
#define Fa 698 //fa
#define Sol 784 //sol
#define La 880 //la
#define Si 986 //si
#define z 0

void upate(void);
void SETUP(void);
void left(void);
void rigth(void);
void carros(void);
void leds(void);
void crash(void);
void gasolina(void);
void musica (void);
void lvl(void);

#endif /*JUEGO_H*/



