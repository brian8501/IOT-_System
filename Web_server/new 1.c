//**Khai bao mot so thu vien can dung**
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "lcd.h"
/////////////////////////////////////////////////////
#ifndef ESP8266_H
#define	ESP8266_H

#ifdef	__cplusplus
extern "C" {
#endif
/////////////////////////////////////////////////////
/** Dinh nghia 1 so hang so **/
    
#define ESP8266_STATION 0x01
#define ESP8266_SOFTAP 0x02

#define ESP8266_TCP 1
#define ESP8266_UDP 0

#define ESP8266_OK 1
#define ESP8266_READY 2
#define ESP8266_FAIL 3
#define ESP8266_CONNECT 4
#define ESP8266_ERROR 5
#define ESP8266_REC 6
#define LEDON 1
#define LEDOFF 2
#define FANON 3
#define FANOFF 4
    
//#define SSID "Hung Toan"
//#define PASSWORD "123123123"
#define SSID "Su Kem"
#define PASSWORD "174704099"
//#define SSID "Wifichua"
//#define PASSWORD "kocopass"
//#define SSID "BMDKH"
//#define PASSWORD "bomondkh505"
unsigned char timeout, show;    
char ipAddress[4];
char dataip[17];
const char http_getch[96] = "GET http://192.168.1.18/wb/electro.php?unit=1";
//const char http_getch[64] = "GET /electro.php?unit=1";
char http_get[40] = "";
char data[70];
char* heater_value; 
char* fan_value; 
char* fog_value; 
char* mode_value;
char* mode_old;
/** Gui/Nhan Du lieu vao Buffer **/
void _esp8266_init(void);
bool Check_Mode(void);
void _esp8266_putch(char);
char _esp8266_getch(void);
void _esp8266_send_string(char*);
void _esp8266_print(const char*);   // Xuat moi chuoi ky tu
/** Nguyen mau ham **/
bool _esp8266_isStarted(void);        // Kiem tra neu module da khoi dong (AT)
bool _esp8266_mode(unsigned char);   // WIFI Mode (Station/Access Point/Both) (AT+CWMODE)
bool _esp8266_encipmux(unsigned char mode);      //Cho phep truyen nhieu kenh (AT+CIPMUX)
bool _esp8266_server(unsigned char mode,char* port); //Ham tao server
char _esp8266_connect(char*,char*);  // Ket noi voi mot mang WIFI (AT+CWJAP)
bool _esp8266_ip(char*);                 // Truy xuat dia chi WIFI cua module (AT+CIFSR)
bool _esp8266_start(unsigned char protocol, char* ip, unsigned char port);   // Tao ket noi toi web server (AT+CIPSTART)
bool _esp8266_send(char*);           // Gui du lieu den web server (AT+CIPSEND)
bool _esp8266_send2(char*, char*);   // Gui du lieu khi chuoi gui qua dai
void _esp8266_receive(char*, uint16_t); // Nhan du lieu tu web server (+IPD)
/** Ham noi bo **/
void _esp8266_send_string(char*);
inline uint16_t _esp8266_waitFor(char*);    // Doi gia tri tra ve la mot chuoi
inline unsigned char _esp8266_waitResponse(void);   // Doi phan hoi tu module
/*Ham khoi dong ESP*/
void _esp8266_config(void);
/*Ham gui du lieu len server*/
void _esp8266_send_data(void);
/////////////////////////////////////////////////////////////
//**Ham khoi tao cho ESP8266**
void _esp8266_init(void)
{
    //****Thiet lap I/O pins cho UART****//
    TRISC6 = 0; // TX Pin la output
    TRISC7 = 1; // RX Pin la input
    /**Thiet lap baud rate va cho phep baud_rate cao**/
    //SPBRG = 10; // Baud rate 115200
    SPBRG = 129; //Toc do baud 9600
    BRGH  = 1;  // Baud rate cao    
    //****Cho phep truyen khong dong do noi tiep*******//
    SYNC  = 0;    // Khong dong bo
    SPEN  = 1;    // Cho phep truyen noi tiep    
    //**Cho phep truyen va nhan**//
    TXEN  = 1;    // Cho phep truyen
    CREN  = 1;    // Cho phep nhan    
    //**Lua chon 8-bit mode**//  
    TX9   = 0;    // Cho phep truyen 8-bit
    RX9   = 0;    // Cho phep nhan 8-bit
}
/////////////////////////////////////////////////////
/* Kiem tra trang che do auto hay manual*/
bool Check_Mode(void){
    if(B_AUTO==0&&mode_value==1){
        __delay_ms(50);
        while(B_AUTO==0);
        mode_value=0;
        show=0;
        return 1;
    }
    if(B_MANUAL==0&&mode_value==0){
        __delay_ms(50);
        while(B_MANUAL==0);
        mode_value=1;
        show=0;
        return 1;
    }
    return 0;
}
//////////////////////////////////////////////////////
//**Ham gui 1 ky tu toi ESP*//
void _esp8266_putch(char bt)  
{
    while(!TXIF);
        //if(Check_Mode()) break;
      // ??i cho buffer TX r?nh
    TXREG = bt;    //Truyen du lieu vao buffer
}
/////////////////////////////////////////////////////
//**Ham nhan 1 ky tu tu ESP**//
char _esp8266_getch()   
{
    if(OERR)       //Kiem tra loi  
    {
        CREN = 0;
        CREN = 1;  //Neu loi thi Reset
    }
    while(!RCIF);
        //if(Check_Mode()||mode_value!=mode_old) break;
      // Doi buffer RX ranh
    
    return RCREG;  //Tra du lieu nhan duoc cho ham
}
//////////////////////////////////////////////////////
//**Ham gui 1 chuoi toi ESP**//
void _esp8266_send_string(char* st_pt)
{
    while(*st_pt) //Kiem tra xem phai chuoi khong
        _esp8266_putch(*st_pt++); //gui tung ky tu trong chuoi
}
/////////////////////////////////////////////////////////
//** Gui mot chuoi hang den ESP **
void _esp8266_print(const char *ptr) {
    while (*ptr != 0) {
        _esp8266_putch(*ptr++);
    }
}
////////////////////////////////////////////////////////////
//**Ham kiem tra xem da ket noi voi ESP hay chua**
bool _esp8266_isStarted(void) {
    _esp8266_print("AT\r\n");   //Gui lenh "AT"
    return (_esp8266_waitResponse() != ESP8266_OK); // Doi phan hoi tu ESP la OK
}
///////////////////////////////////////////////////////////////
//**Thiet lap che do WIFI (Station/AP/Both)**
bool _esp8266_mode(unsigned char mode) {
    _esp8266_print("AT+CWMODE=");
    _esp8266_putch(mode + '0');     
    _esp8266_print("\r\n");         //Gui lenh
    return (_esp8266_waitResponse() == ESP8266_OK);
}
///////////////////////////////////////////////////////////////
//**bat tat che do truyen nhieu kenh AT+CIPMUX
bool _esp8266_encipmux(unsigned char mode){
    _esp8266_print("AT+CIPMUX=");
    _esp8266_putch(mode+'0');
    _esp8266_print("\r\n");
    return (_esp8266_waitResponse()== ESP8266_OK);
}
///////////////////////////////////////////////////////////////
//** Bat tat server
bool _esp8266_server(unsigned char mode, char* port){
    _esp8266_print("AT+CIPSERVER=");
    _esp8266_putch(mode+'0');   //Cho phep hay khong cho phep
    _esp8266_print(",");
    _esp8266_print(port);   //Port server
    _esp8266_print("\r\n");
    return (_esp8266_waitResponse()== ESP8266_OK);
}
///////////////////////////////////////////////////////////////
//**Ket noi toi mot mang WIFI**
char _esp8266_connect(char* ssid,char* pass) {
    _esp8266_print("AT+CWJAP=\"");
    _esp8266_print(ssid);   //SSID
    _esp8266_print("\",\"");
    _esp8266_print(pass);   //PASSWORD
    _esp8266_print("\"\r\n");
    if(_esp8266_waitResponse()== ESP8266_ERROR)
        return 0;
    return (_esp8266_waitFor("OK")); //Doi phan hoi
    
}
///////////////////////////////////////////////////////////////
/**
 * Luu tru dia chi IP cuc bo hien tai
 *
 * Gui lenh "AT+CIFSR" den ESP
 *
 * Ket qua tra ve theo dang chuoi nhung luu tru theo mang
 * Vi du IP 192.168.0.1, thi gia tri luu tru la: {0xc0, 0xa8, 0x00, 0x01}.
 */
bool _esp8266_ip(char* store_in) {
    _esp8266_print("AT+CIFSR\r\n");
    _esp8266_waitFor("STAIP,");
    unsigned char received;
    do {
        received = _esp8266_getch();    //Doc gia tri ve
    } while (received < '0' || received > '9'); //gia tri nhan duoc nam trong dai tu 0-9
    for (unsigned char i = 0; i < 4; i++) {
        store_in[i] = 0;
        do {
            store_in[i] = 10 * store_in[i] + received - '0'; //???
            received = _esp8266_getch();
        } while (received >= '0' && received <= '9');
        received = _esp8266_getch();
    }
    return (_esp8266_waitResponse()== ESP8266_OK);
}
///////////////////////////////////////////////////////////////
// ** Mo ket noi TCP hoac UDP va ket noi den 1 web server**
bool _esp8266_start(unsigned char protocol, char* ip, unsigned char port) {
    _esp8266_print("AT+CIPSTART=4,\"");
    if (protocol == ESP8266_TCP) {
        _esp8266_print("TCP");
    } else {
        _esp8266_print("UDP");
    }
    _esp8266_print("\",\"");
    _esp8266_print(ip);     //dia chi ip web server
    _esp8266_print("\",");
    char port_str[5] = "\0\0\0\0";
    sprintf(port_str, "%u", port);  //Chuyen doi gia tu so sang chuoi
    _esp8266_print(port_str); 
    _esp8266_print("\r\n");
    //__delay_ms(50);
    return (_esp8266_waitResponse()==ESP8266_CONNECT);
        //return 1;
    //return(_esp8266_waitResponse()==ESP8266_OK);
}
///////////////////////////////////////////////////////////////
//**Gui du lieu len web server**
bool _esp8266_send(char* data1) {
    char length_str[6] = "\0\0\0\0\0";
    sprintf(length_str, "%u", strlen(data1)); //Gui do dai chuoi ky tu sang chuoi
    _esp8266_print("AT+CIPSEND=4,");
    _esp8266_print(length_str);
    _esp8266_print("\r\n");
//    if(_esp8266_waitResponse()!=ESP8266_OK){
//        return 0;
//    }
    //LED_Check=0;
    _esp8266_waitFor(">");
    //while (_esp8266_getch() != '>'); //DOi ESP gui ve ">"
    __delay_ms(500);
    _esp8266_print(data1); 
    return (_esp8266_waitResponse() == ESP8266_OK); // Gui di chuoi va doi phan hoi
}
///////////////////////////////////////////////////////////////
/* Gui du lieu len sever khi du lieu qua dai*/
bool _esp8266_send2(char* data1, char*data2) {
    char length_str[6] = "\0\0\0\0\0";
    sprintf(length_str, "%u", strlen(data1)+strlen(data2));
    _esp8266_print("AT+CIPSEND=4,");
    _esp8266_print(length_str);
    _esp8266_print("\r\n");
    if(_esp8266_waitResponse()!=ESP8266_OK){
        return 0;
    }
    _esp8266_waitFor(">");
    //while (_esp8266_getch() != '>'); //DOi ESP gui ve ">"
    __delay_ms(500);
    _esp8266_print(data1);
    _esp8266_print(data2);
    return (_esp8266_waitResponse() == ESP8266_OK); // Gui di chuoi va doi phan hoi
}
///////////////////////////////////////////////////////////////
//** Doc chuoi du lieu tu ESP **
void _esp8266_receive(char* store_in, uint16_t max_length) {
    _esp8266_waitFor("START-");
    LED_Check=0;
    unsigned char received; 
    uint16_t i;
    for (i = 0; i < max_length-4; i++) {
        store_in[i] = _esp8266_getch();  
    }
    //_esp8266_waitFor("\r\n\r\n");
}
///////////////////////////////////////////////////////////////
//** Doi chuoi tra ve theo mau**
inline uint16_t _esp8266_waitFor(char *string) {
    unsigned char so_far = 0;
    unsigned char received = "";
    uint16_t counter = 0;
    do {
        received = _esp8266_getch();
        //if(mode_value!=mode_old) break;
        counter++;
        if (received == string[so_far]) {
            so_far++;
        } else {
            so_far = 0;
        }
    } while (string[so_far] != 0);
    return counter;
}
///////////////////////////////////////////////////////////////
/**
 * Doi ESP done va gui tin hieu phan hoi..
 *
 * Cac tin hieu phan hoi duoc trien khai:
 *  * OK
 *  * ready
 *  * FAIL
 *  * no change
 *  * Linked
 *  * Unlink
 */
inline unsigned char _esp8266_waitResponse(void) {
    unsigned char so_far[6] = {0,0,0,0,0,0};
    unsigned const char lengths[6] = {2,1,7,5,5,5};
    const char* strings[6] = {"OK", ">", "CONNECT", "ERROR", "FAIL", "ready"};
    unsigned const char responses[6] = {ESP8266_OK, ESP8266_REC, ESP8266_CONNECT, ESP8266_ERROR, ESP8266_FAIL, ESP8266_READY};
    unsigned char received;
    unsigned char response;
    bool continue_loop = true;
    while (continue_loop) {
        received = _esp8266_getch();
        for (unsigned char i = 0; i < 6; i++) {
            
            if (strings[i][so_far[i]] == received) {
                so_far[i]++;
                if (so_far[i] == lengths[i]) {
                    response = responses[i];
                    continue_loop = false;
                }
            } else {
                so_far[i] = 0;
                if(mode_value!=mode_old)
                    continue_loop = false;
            }
        }
    }
    return response;
}
void LED_Checked(void){
    LED_Check=1;
    __delay_ms(250);
    LED_Check=0;
    __delay_ms(250);
    LED_Check=1;
    __delay_ms(250);
    LED_Check=0;
    __delay_ms(250);
}
void _esp8266_extract_data(char data2[])
{
   /*
    Vi du chuoi gui lai tu Server:
    #START-LED=1-FAN=1-FOG=1-TEMPSET=22-HUMISET=23-UPDATE=0-#END/r/n/r/n
    */
    if(strstr(data2,"HEATER=1")!=NULL)
    {
        HEATER = 1;
        //heater_value[0]= '1';
    }
    if(strstr(data2,"HEATER=0")!=NULL)
    {
        HEATER =0;
        //heater_value[0] = '0';
    }
    if(strstr(data2,"FAN=1")!=NULL)
    {
        FAN =1;
        //fan_value[0] = '1';
    }
    if(strstr(data2,"FAN=0")!=NULL)
    {
        FAN =0;
        //fan_value[0] = '0';
    }
    if(strstr(data2,"FOG=1")!=NULL)
    {
        FOG =1;
        //fog_value[0] = '1';
    }
    if(strstr(data2,"FOG=0")!=NULL)
    {
        FOG =0;
        //fog_value[0] = '0';
    }
    //update_server_value[0] = '0';
    //LED_Check=0;
}
void _esp8266_config(void){
    do
    {
        if(timeout<10){
            Lcd_Set_Cursor(1,1);
            Lcd_Write_String("ESP not found   ");
            LED_Checked();
            _esp8266_print("AT\r\n");
            timeout++;
        }
        else {
            Lcd_Set_Cursor(1,1);
            Lcd_Write_String("Check connection");
            Lcd_Set_Cursor(2,1);
            Lcd_Write_String("& Reset System  ");
            BUZZER = 1;
            LED_Check = 1;
        } 
    }while (!RCIF); //Doi ESP ket noi voi VDK    
    Lcd_Clear();
    BUZZER = 0;
    timeout = 0;
    while(_esp8266_waitResponse()!=ESP8266_OK)
    do
    {
        Lcd_Set_Cursor(1,1);
        Lcd_Write_String("ESP is connected");
        LED_Checked();
        timeout++;
        if(timeout>5){
         Lcd_Set_Cursor(1,1);
         Lcd_Write_String(" Need Reset !!!!");
         BUZZER = 1;
         LED_Check = 1;
         __delay_ms(2000);
         
        } 
    }
    while(!_esp8266_mode(1));   /*Dat che do hoat dong cho ESP*/    
    Lcd_Clear();
    BUZZER = 0;
    timeout = 0;
    LED_Check = 0;
    do
    {        
        Lcd_Set_Cursor(1,1);
        Lcd_Write_String("ESP set MODE 1");
        LED_Checked();
        timeout++;
        if(timeout>5){
         Lcd_Set_Cursor(1,1);
         Lcd_Write_String("Need Reset !!!!");
         BUZZER = 1;
         LED_Check = 1;
         __delay_ms(2000); 
        }
    }
    while(!_esp8266_encipmux(1));  /*Thiet lap chon nhieu kenh hay khong */    
    Lcd_Clear();
    BUZZER = 0;
    timeout = 0;
    LED_Check = 0;
    do{
        
        Lcd_Set_Cursor(1,1);
        Lcd_Write_String("ESP CIPMUX=1   "); 
        LED_Checked();
        timeout++;
        if(timeout>5){
         Lcd_Set_Cursor(1,1);
         Lcd_Write_String("Need Reset !!!!");
         BUZZER = 1;
         LED_Check = 1;
         __delay_ms(2000);
        }
    }
     while(!_esp8266_server(1,"80"));    /* Mo port sever*/
    Lcd_Clear();
    BUZZER = 0;
    LED_Check = 0;
    timeout = 0;
    do{
        Lcd_Set_Cursor(1,1);
        Lcd_Write_String("ESP Server ON  ");
        LED_Checked();
        timeout++;
        if(timeout>5){
         Lcd_Set_Cursor(1,1);
         Lcd_Write_String("Need Reset !!!!");
         BUZZER = 1;
         LED_Check = 1;
         __delay_ms(2000);
         
        }
    }
    while(!_esp8266_connect(SSID,PASSWORD)); // Doi ket noi voi mang wifi
    BUZZER = 0;
    LED_Check = 0;
    timeout = 0;
    Lcd_Clear();
    do{   
        Lcd_Set_Cursor(1,1);
        Lcd_Write_String("AP configured  ");
        LED_Checked();
        timeout++;
        if(timeout>5){
         Lcd_Set_Cursor(1,1);
         Lcd_Write_String("Need Reset !!!!");
         BUZZER = 1;
         LED_Check = 1;
         __delay_ms(2000);
         
        }
    }
    while(!_esp8266_ip(ipAddress));              //Lay dia chi IP duoc cap cho Module ESP8266
    BUZZER = 0;
    LED_Check = 0;
    timeout = 0;
    LED_Checked();
    Lcd_Set_Cursor(2,1);
    sprintf (dataip,"IP:%d.%d.%d.%d",ipAddress[0],ipAddress[1],ipAddress[2],ipAddress[3]);
    Lcd_Write_String(dataip);
    Lcd_Set_Cursor(1,1);
    Lcd_Write_String("Ready to connect"); 
    for(unsigned char i = 0;i<30;i++)
    {
        LED_Check = 1;
        __delay_ms(50);
        LED_Check = 0;
        __delay_ms(50);
    }
}
void _esp8266_send_data(){
    do
    {
        if(mode_value!=mode_old) break;
        LED_Checked();
        LED_Checked();
        timeout++;
        if(timeout>20){
         Lcd_Set_Cursor(1,1);
         Lcd_Write_String("Need Reset !!!!");
         BUZZER = 1;
         LED_Check =1;
         __delay_ms(2000);
        }
    }
    while(!_esp8266_start(1,"192.168.1.18",80));
    //while(!_esp8266_start(1,"api:vuonganhiot.000webhostapp.com",80));
    BUZZER = 0;
    timeout = 0;
    //LED_Check = 0;
    //Lcd_Clear();
    do{
        if(mode_value!=mode_old) break;
        for(unsigned int i = 0;i<sizeof(http_get);i++)
        {
        http_get[i]="";
        }
        strcpy(http_get, http_getch);
//        strcat(http_get, "&heater=");
//        strcat(http_get, heater_value);
//        strcat(http_get, "&fan=");
//        strcat(http_get, fan_value);
//        strcat(http_get, "&fog=");
//        strcat(http_get, fog_value);
//        strcat(http_get, "&temp=");
//        strcat(http_get, nhietdo);
//        strcat(http_get, "&humi=");
//        strcat(http_get, doam);
        strcat(http_get, "&mode=0\r\n\r\n");
        //strcat(http_get, mode_value);
        timeout++;
        LED_Check=1;
        if(timeout>20){
         Lcd_Set_Cursor(1,1);
         Lcd_Write_String("Need Reset !!!!");
         BUZZER = 1;
         __delay_ms(2000);
        }
    }
    while(!_esp8266_send(http_get));
    //LED_Check=0;
    //while(!_esp8266_send2(http_get,""))
    //while (!_esp8266_send2(http_get," HTTP/1.0\r\nHost: vuonganhiot.000webhostapp.com\r\n\r\n"));
    //timeout = 0;
    //BUZZER = 0;

    _esp8266_receive(data,55);
    __delay_ms(500);    
    //_esp8266_extract_data(data);
    //__delay_ms(300);
}


#ifdef	__cplusplus
}
#endif

#endif	/* ESP8266_H */




