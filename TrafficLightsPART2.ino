#include <avr/io.h>
#include <util/delay.h>

#define TRAFFIC_RED 0      
#define TRAFFIC_ORANGE 1    
#define TRAFFIC_GREEN 2     
#define PED_RED 5           
#define PED_GREEN 4        
#define BUTTON 3            


int main(void)

{
 
 uint8_t buttonPin=0;
 uint8_t oldButtonPin=0;

 DDRB= 0xFF;               //All PORT B pins are outputs
 DDRC |= (1<<PED_RED);     //PC5 is an output (RED Pedestrian Light)
 DDRC |= (1<<PED_GREEN);   //PC4 is an output (Green Pedestrian Light)
 DDRC &= ~(1<<BUTTON);     //PC3 is an input  ( Pedestrian Button)
 PORTC |= (1<<BUTTON);     //PC3 pull up resistor 

 

    while(1){

      buttonPin = (PINC & (1<<BUTTON)); // Isolate Button for checking state

      if (buttonPin==0 && oldButtonPin !=0){  //1st Button press

        PORTB &= ~(1<<TRAFFIC_GREEN);    
        PORTB |=(1<<TRAFFIC_ORANGE);
        _delay_ms(3000);

        PORTB &= ~(1<<TRAFFIC_ORANGE);
        PORTC |=(1<<PED_GREEN);
        PORTC &= ~(1<<PED_RED);
        PORTB |=(1<<TRAFFIC_RED);
        _delay_ms(6000);   

    }

      else { 
        
        PORTB &= ~(1<<TRAFFIC_RED);
        PORTC |=(1<<PED_RED);
        PORTC &= ~(1<<PED_GREEN);
        PORTB |=(1<<TRAFFIC_GREEN);

    }
    
    oldButtonPin= buttonPin; // Prevents multiple reads from button press until loop is complete
  }
}