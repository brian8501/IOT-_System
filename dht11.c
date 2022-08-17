#use fast_io(B)
#BIT Data_Pin = 0x06.0                       // Pin mapped to PORTB.0
#BIT Data_Pin_Direction = 0x86.0             // Pin direction mapped to TRISB.0
short Time_out;
unsigned int8 T_byte1, T_byte2, RH_byte1, RH_byte2, CheckSum ;
extern unsigned int16 Temp, RH;
//extern unsigned int16 t,h;
char message1[] = "T=00.0   ";
char message2[] = "RH=00.0";
void start_signal(){
  Data_Pin_Direction = 0;              // Configure connection pin as output
  Data_Pin = 0;                        // Connection pin output low
  delay_ms(25);
  Data_Pin = 1;                        // Connection pin output high
  delay_us(30);
  Data_Pin_Direction = 1;              // Configure connection pin as input
}
short check_response(){
  delay_us(40);
  if(!Data_Pin){                     // Read and test if connection pin is low
    delay_us(80);
    if(Data_Pin){                    // Read and test if connection pin is high
      delay_us(50);
      return 1;}
    }
}
unsigned int8 Read_Data(){
  unsigned int8 i, k, _data = 0;     // k is used to count 1 bit reading duration
  if(Time_out)
    break;
  for(i = 0; i < 8; i++){
    k = 0;
    while(!Data_Pin){                          // Wait until pin goes high
      k++;
      if (k > 100) {Time_out = 1; break;}
      delay_us(1);}
    delay_us(30);
    if(!Data_Pin)
      bit_clear(_data, (7 - i));               // Clear bit (7 - i)
    else{
      bit_set(_data, (7 - i));                 // Set bit (7 - i)
      while(Data_Pin){                         // Wait until pin goes low
      k++;
      if (k > 100) {Time_out = 1; break;}
      delay_us(1);}
    }
  }
  return _data;
}
void Read_DHT11(void){
    //delay_ms(1000);
    Time_out = 0;
    Start_signal();
    if(check_response()){                    // If there is response from sensor
      RH_byte1 = Read_Data();                 // read RH byte1
      RH_byte2 = Read_Data();                 // read RH byte2
      T_byte1 = Read_Data();                  // read T byte1
      T_byte2 = Read_Data();                  // read T byte2
      Checksum = Read_Data();                 // read checksum
      if(Time_out){                           // If reading takes long time
        lcd_gotoxy(1, 2);                     // Go to column 5 row 1
        lcd_putc("DHT11 Time out! ");
      }
      else{
       if(CheckSum == ((RH_Byte1 + RH_Byte2 + T_Byte1 + T_Byte2) & 0xFF)){
        message1[2]  = T_Byte1/10  + 48;
        message1[3]  = T_Byte1%10  + 48;
        message1[5] = T_Byte2/10  + 48;
        message2[3]  = RH_Byte1/10 + 48;
        message2[4]  = RH_Byte1%10 + 48;
        message2[6] = RH_Byte2/10 + 48;
        lcd_gotoxy(1, 2);                    
        printf(lcd_putc, message1);
        lcd_gotoxy(10, 2);                    
        printf(lcd_putc, message2);
        RH =  RH_Byte1;
        Temp =  T_Byte1;
       }
        else {
          lcd_gotoxy(1, 2);               
          lcd_putc("Checksum Error! ");
        }
      }
    }
    else {
      lcd_gotoxy(1, 2);   
      lcd_putc("No response     ");
    }
}
