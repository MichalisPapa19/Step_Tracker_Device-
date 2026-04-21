#include <main515.h>

#define LED     PIN_F3
#define BUTTON   PIN_B4

unsigned int16  i;
char master_mask[32];

unsigned int16  ptr_save;

 

#include <OLED.c>
#include <BNP055.c>
#include <save_data.c>

#zero_ram

 
   
VOID init_ports( void )
   {
       set_TRIS_A (0b00010111);  // pin A0,A1,A2,A4 EISODOI //PIN A3,A5,A6,A7 EJODOI 
       set_TRIS_B (0b00010111);  // PIN B0,B1,B2,B4 EISODOI //PIN B3,B5,B6,B7 EJODOI   
       set_TRIS_F (0b11110111);  // PIN F1,F4 EISODOI // PIN F0,F2,F3,F5,F6,F7 EJODOI
       
       
   }
   

 
VOID main() 
   {
       init_ports () ;
        
       port_b_pullups (0b00010111);     // set  pull up resistor rb0,rb1,rb2,rb4
      
      
      Initial_1306 () ;         // init oled 
      delay_ms (200) ;

      lcd_clrscroled (0x00);   // all pixel off
    
 
 
      //  master_mask,stili,grammi
      sprintf (master_mask, "Mixalis") ;  
      Show_String8x16(master_mask, 0, 0) ;
      sprintf (master_mask,"Papaioannou");
      Show_String8x16(master_mask,0, 3);
      sprintf (master_mask,"2024");
      Show_String8x16(master_mask,3, 6);
      printf(" PROJECT \r\n");
       
      delay_ms(2000);
      
       
      lcd_clrscroled (0x00);   // all pixel off
      
     
      BNO055_Config () ;
      delay_ms (400) ;
      BNO055_read_register_id();
      delay_ms(500);
      lcd_clrscroled (0x00);
      

int previous_button_state = 0; // Initial button state (not pressed)
int button_state = 0;  
int current_state = 0;
int current_button_input = 0;


ptr_save = 0;

while(TRUE) {

    current_button_input = input(BUTTON); // Read current button state
    // Check if the button is pressed
    if(current_button_input == 1 && previous_button_state == 0) {
        delay_ms(20); // Debounce delay
        if(input(BUTTON) == 1) {  // Confirm the button is still pressed
            button_state = 1;
            current_state++;
            
            if(current_state > 2) {
                current_state = 0;  // Reset to the initial state
                
            }

            switch(current_state) {
                case 0:
                    lcd_clrscroled(0x00);
                    output_low(LED);  
                    printf("case 0: Continuously reading sensor data\n\r");
                    
                    delay_ms(500);
                    // Continuous sensor reading until the button is pressed again
                    while(current_state == 0) {
                        BNO055_read_linear_accel();  
                       
                        write_paket(ptr_save);
                        
                        delay_ms(10); 
                        if(input(BUTTON)!= 1){
                           break;
                        }
                                 
                    }                                    
                  break;
                        
                    

                case 1:
   
                    lcd_clrscroled(0x00);
                    output_high(LED);  
                    delay_ms(100);
                    printf("case 1: State has changed.\n\r");
                    
                    sprintf(master_mask, "PAUSE");
                    Show_String8x16(master_mask, 5, 2);
                    
                    break;
                    
                case 2:
                 output_high(LED);  
                    delay_ms(500);
                    output_low(LED);
                    delay_ms(500);
                    output_high(LED); 
                    delay_ms(500);
                    lcd_clrscroled(0x00);  // Clear OLED screen

                    printf("case 2: READ SAVE DATA \n\r");

                     
                     for(i=0; i<=ptr_save; i++ )
                      {
                       sprintf (master_mask,"EXPORT DATA:%3Lu",i);
                       Show_String8x16(master_mask,1, 2);                    
                       
                       printf("XL:%3Ld \r\n",save_acelx[i]);
                       printf("YL:%3Ld \r\n",seve_acely[i]);
                       printf("ZL:%3Ld \r\n\r\n",save_acelz[i]);                        
                       delay_ms(50); 
                       lcd_clrscroled (0x00);
                      }
                    printf("Counter_Data: %4Lu\n\r",ptr_save);
                    ptr_save = 0;
                    sprintf(master_mask, "FINISH");
                    Show_String8x16(master_mask, 5, 2);
                    
                    break;

         
            }
        }
    }
    // Update the previous button state
    previous_button_state = current_button_input;
 }  
}
