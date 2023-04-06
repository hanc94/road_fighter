#include "juego.h"

// 
LiquidCrystal lcd(12,11,5,4,9,10);
Timer t;

volatile byte i=0,j=0;
byte latchPin = 37 ;        
byte clockPin = 29;        
byte dataPin = 33; 
byte latchPin1 = 36 ;        
byte clockPin1 = 28;        
byte dataPin1 = 32;      

int speakerOut=8;
int melody[]={Do, Do, Fa, Fa, Mi, Fa, Sol, Mi, Fa, Sol, La, Fa, Sol, La, Si, Si, Si, La, Sol, Fa, Mi, Sol, Fa, Mi, Fa, Sol, La, Si, Sol, Fa,La, Sol, Mi, Mi, Fa, Sol, La, Fa, La, Sol, Mi, Mi, Fa, Sol, La, Fa, Fa, Si, Si, Si, Si, La, Fa, Mi, Fa, Sol, La, Si, Sol, Fa  };
int melody2[]={Mi, Sol, Sol, Sol, Fa, Mi, Sol, Sol, La, Fa, La, do, La, Sol, Sol, La, Fa, La, do, Si, La, Sol, La, Sol, Mi, Do, Sol, La, La, La, Si, Si, do };
int melody3[]={Sol, Sol, Sol, Sol, La, Mi, Sol, Sol, do, re, mi, mi, mi, mi, re, re, do, do, mi, mi, fa, mi, mi, re, mi, re, re, do, do, Sol, Sol, Sol, La, do, Sol, Sol, Sol ,do, re, re, mi, mi, re, re, re, do, do, do,mi, mi, fa, mi, mi, mi, re, mi, re, re, do, do,mi, re, do, mi, sol, la, mi, re, do, La, Sol, mi, mi, mi, fa, mi, mi, re, mi, re, do, do };

int note=0;
byte k;
byte q=0,g=30,gg=0;
byte l,d=0;
byte e=0;
byte a=0;
char carro [2][16]={{' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},{' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '}};
char carro1 [2][1]={{'1'},{'2'}};
short cs, c, r;
int vel=500;
const byte n[10]={B00001001,B10011111,B00101010,B00001110,B10011100,B01001100,B01001000,B00011111,B00001000,B00001100};
//const byte n[10]={B00000010,B00000010,B00000010,B00000010,B00000010,B00000010,B00000010,B00000000,B00000010,B11111110};
byte damage[8]={0b11111,0b11111,0b11111,0b11111,0b11111,0b11111,0b11111,0b11111};
byte gas[8]={0b10111,0b01001,0b11111,0b10001,0b10111,0b10001,0b10111,0b11111};
byte car[8]={0b11011,0b11011,0b01110,0b01111,0b01111,0b01110,0b11011,0b11011};
byte cero[8]={0b00000,0b00000,0b00000,0b00000,0b00000,0b00000,0b00000,0b00000};
byte enemy[8]={0b11111,0b11111,0b01110,0b01111,0b01111,0b01110,0b11111,0b11111};
byte en=0,cont=0;
byte digit1,digit2;
byte ee=0,dd,ff=0;
int Num=1,nu=99,p=0,pp;

void SETUP(void)
{
  pinMode(speakerOut, OUTPUT);
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(latchPin1, OUTPUT);
  pinMode(clockPin1, OUTPUT);
  pinMode(dataPin1, OUTPUT);
  pinMode(3,INPUT_PULLUP);
  pinMode(2,INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(3),left,FALLING);
  attachInterrupt(digitalPinToInterrupt(2),rigth,FALLING);
  
  lcd.begin(16,2);
  lcd.clear();
  lcd.createChar(0,car);
  lcd.createChar(1,cero);
  lcd.createChar(2,enemy);
  lcd.createChar(3,gas);
  
  lcd.createChar(4,damage);
  
  lcd.setCursor(0,0);
  lcd.write(byte(0));
  randomSeed(analogRead(0));//semilla random
  
  
  digitalWrite(latchPin, LOW) ; //inicia el registro de leds en 1
  shiftOut(dataPin, clockPin, LSBFIRST, 2); 
  Num=2;
  digitalWrite(latchPin, HIGH) ;
  
  t.every(10000,lvl);              
  t.every(vel,carros);
  t.every(10000,leds);
  t.every(vel,gasolina);
  t.every(vel,crash);
  t.every(vel,musica);
  
  rigth();
  left();
}

void upate(void)
{
  t.update();
}

void musica(void)
{
   tone(speakerOut,melody[note]);
  delay(vel);
  noTone(speakerOut);
  note++;
    if(note==50)note=0;
  
  }
void lvl(void)
{
  vel=vel-50;
  t.every(vel,gasolina);
t.every(vel,crash);
t.every(vel,musica);
t.every(vel,carros);
  }



void carros(void) //funcion generacion y desplazamiento de carros
{
   for(k=0;k<=1;k++) //imprime el arreglo de caracteres
  {
    for(l=0;l<=15;l++)
    {
      lcd.setCursor(l,k);
      lcd.write(carro[k][l]); 
      lcd.setCursor(0,j);
      lcd.write(carro1[j][0]);
    }
  }
  for(k=0;k<=1;k++)  //mueve toda la matriz a la derecha
  {
    gg=gg+1;       
    a=1;
    for(l=1;l<=15;l++)
    {
      carro[k][l-1]=carro[k][l];
    }
  }
if (j==1){                          //ubica el carro arriba o abajo
            carro1[j][0]=byte(0);
        carro1[j-1][0]=byte(1);
  }
  else if (j==0){
            carro1[j][0]=byte(0);
        carro1[j+1][0]=byte(1);            
  }
  if((cs>=0)&&(cs<2))   //variable acumulativa que activa la creacion de carros cada dos segmentos
  {
    carro[0][15]=' ';
    carro[1][15]=' ';
    cs++;
    
  }
  else if (cs>=2)
     {
      nu=nu-1;
       r=random(2);
       if(random(2)==0)
       {
         carro[0][15]=byte(2);
         carro[1][15]=' ';
       }
       else
       {
         carro[0][15]=' ';
         carro[1][15]=byte(2);
       }
     cs=0;// se reinicia la acumulativa 
}    
if(g==gg)  // creacion de la gasolina
       {
        g=g+30;
         if(random(2)==0)
       {
         carro[0][15]=byte(3);
       }
       else if(random(2)==1)
       {
         carro[1][15]=byte(3);
       }   
       }    
}
void leds (void)
{
         if(Num < 256 )// Registro de desplazamiento
          {
             digitalWrite(latchPin, LOW) ; 
             shiftOut(dataPin, clockPin, LSBFIRST, Num); 
                            Num=Num*2;
             digitalWrite(latchPin, HIGH) ; 
               d=d+10;
             
               if (Num>=256 )
  {
    lcd.clear();
     digitalWrite(latchPin, LOW) ; 
             shiftOut(dataPin, clockPin, LSBFIRST, 128);          
             digitalWrite(latchPin, HIGH) ; 
    for(pp=0;pp<1;)  // ciclo infinito que muestra mensaje de victoria
    {
    lcd.home();  
    lcd.print("    YOU WIN!    ");
     tone(speakerOut,melody2[note]);
  delay(vel);
  noTone(speakerOut);
  note++;
    if(note==50)note=0;
    }
   }  
          }
  }
void gasolina (void) // funcion que muestra la gasolina en los displays de 7 segmentos
{
   if (nu > 0 )
  {
  digit1 = nu / 10;
  digit2 = nu - (digit1 * 10);
    digitalWrite(latchPin1, LOW);
    shiftOut(dataPin1, clockPin1, LSBFIRST, n[digit2]);
    shiftOut(dataPin1, clockPin1, LSBFIRST, n[digit1]);
    digitalWrite(latchPin1, HIGH);
   }   
    if (nu<=0 ) //condicion perdio
  {
    lcd.clear();    //limpia pantalla y coloca los displays en 0
    digitalWrite(latchPin1, LOW); 
    shiftOut(dataPin1, clockPin1, LSBFIRST,n[0]);
    shiftOut(dataPin1, clockPin1, LSBFIRST, n[0]);
    digitalWrite(latchPin1, HIGH);
  
    for(pp=0;pp<1;) // ciclo infinito que muestra mensaje de derrota
    {
    lcd.home();
    lcd.print("   GAME OVER!   ");
     tone(speakerOut,melody3[note]);
  delay(vel);
  noTone(speakerOut);
  note++;
    if(note==50)note=0;
    }
   }
  }
void crash (void)  //condiciones que detectan un choque
{
     if(j==0 & carro[0][0]==byte(2))
  {
  nu=nu-10; 
  } 
   if(j==1 & carro[1][0]==byte(2))
  {
  nu=nu-10;
   
 
  } 
     if(j==0 && carro[0][0]==byte(3))
  {
   nu=nu+5;
   if (nu>99)
   {
    nu=99;
    }
  } 
   if(j==1 && carro[1][0]==byte(3))
  {
   nu=nu+5;
      if (nu>99)
   {
    nu=99;
    }
  } 
  }
void left()  // interrupcion a la izquierda que modifica la matriz
                 {
                  if(j==1)
                  {
                     carro1[j][0]=byte(0);
                     carro1[j-1][0]=byte(1);
                     j--;
                 }
                 }
                 void rigth() //interruccion a la derecha que modifica la matriz
                 { if(j==0)
                 {
                    
                    carro1[j][0]=byte(0);
                    carro1[j+1][0]=byte(1);
                    j++;  

                 }
                 }
