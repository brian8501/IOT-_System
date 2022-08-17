//Dinh nghia cac chan cho LCD
#define LCD_ENABLE_PIN PIN_D3
#define LCD_RS_PIN PIN_D2
#define LCD_RW_PIN PIN_D6
#define LCD_DATA4 PIN_C4
#define LCD_DATA5 PIN_C5
#define LCD_DATA6 PIN_D4
#define LCD_DATA7 PIN_D5
//Dinh nghia cac chan dieu khien thiet bi
#define RELAY_DEN PIN_C3
#define RELAY_QUAT PIN_D0
#define RELAY_SUONG PIN_D1
//Khai bao cac thu vien can dung
#include <chuontrinhchinh.h>
#include <lcd.c>
#include <dht11.c>   //Thu vien doc cam bien DHT11
#include <cambien.c> //Thu vien doc cam bien TDS (nong do chat ran) và CDS (anh sang)
//Khai bao cac bien can xu ly
unsigned int16 Temp,RH;
int value_adc1;  //Bien nhiet do va do am cua DHT11
float ppm;  //Gia tri cua cam bien TDS va CDS
char symbol_Rec;  //Bien nhan du lieu
int mode_Control = 1;
int8 fan_value=0,pump_value=0,lamp_value=0;
#INT_RDA
void  RDA_isr(void) 
{
   symbol_Rec = getch();
   if(symbol_Rec=='T')
   mode_Control = 1;
   if(symbol_Rec=='M')
   {
      mode_Control = 0;
      output_low(RELAY_QUAT);
      output_low(RELAY_DEN);
   }
   if(mode_Control==0){
      if(symbol_Rec=='A'){
         output_high(RELAY_DEN);
         lamp_value=1;
      }
      if(symbol_Rec=='B'){
         output_high(RELAY_QUAT);
         fan_value=1;
      }
      if(symbol_Rec=='C'){
         output_high(RELAY_SUONG);
         pump_value=1;
      }
      if(symbol_Rec=='a'){
         output_low(RELAY_DEN);
         lamp_value=0;
      }
      if(symbol_Rec=='b'){
         output_low(RELAY_QUAT);
         fan_value=0;
      }
      if(symbol_Rec=='c'){
         output_low(RELAY_SUONG);
         pump_value=0;
      }
   }
}

void main()
{
   setup_adc_ports(AN0_AN1_AN3); // Su dung 3 dau vao Analog khong su dung tham chieu
   setup_adc(ADC_CLOCK_DIV_2);   //Su dung bo chia tan so la 2 cho bo doc ADC
   enable_interrupts(INT_RDA);   //Cho phep ngat nhan du lieu RX
   enable_interrupts(GLOBAL);       //Cho phep ngat toan cuc
   lcd_init(); //Khoi tao LCD
   delay_ms(500); //Doi on dinh
   lcd_putc('\f');   //Xoa trang man hình LCD
   output_low(RELAY_DEN);
   output_low(RELAY_QUAT);
   while(TRUE)
   {
      Read_DHT11();  //Doc du lieu DHT11
      Read_TDS();    //Doc cma bien TDS
      Read_CDS();    //Doc cam bien CDS
      delay_ms(2000);
      if(mode_Control==1){
         if(value_adc1>100){
            output_low(RELAY_DEN);
            lamp_value=0;
         }
         else{
            output_high(RELAY_DEN);
            lamp_value=1;
         }
         if(Temp>27){
            output_high(RELAY_QUAT);
            fan_value=1;
         }
         else{
            output_low(RELAY_QUAT);
            fan_value=0;
         }
         if(RH<85){
            output_high(RELAY_SUONG);
            pump_value=1;
         }
         else{
            output_low(RELAY_SUONG);
            pump_value=0;
         }
         printf("=1&temp=%lu&rh=%lu&tds=%3.0f&cds=%d&fan=%d&pump=%d&lamp=%d ",Temp,RH,ppm,value_adc1,fan_value,pump_value,lamp_value);
      }
      else
         printf("=0&temp=%lu&rh=%lu&tds=%3.0f&cds=%d ",Temp,RH,ppm,value_adc1);
   }
}

