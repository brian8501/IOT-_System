float voltage_adc0;
extern int value_adc1;
extern float ppm;
void Read_TDS(){
   set_adc_channel(0);
   delay_us(100);
   voltage_adc0 = read_adc()*5.0f/1024;
   ppm = ((voltage_adc0*1000)/2.3f);
   lcd_gotoxy(1,1);
   printf(lcd_putc,"TDS=%4.0f",ppm);
}
void Read_CDS(){
   set_adc_channel(1);
   delay_us(100);
   value_adc1 = read_adc();
   lcd_gotoxy(1,1);
   if(value_adc1>100){
   lcd_gotoxy(9,1);
   lcd_putc(",AS:Sang");
   }
   else
   {
      lcd_gotoxy(9,1);
      lcd_putc(",AS:Toi ");
   }
}
