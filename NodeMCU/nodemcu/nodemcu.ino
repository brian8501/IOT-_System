#include <ESP8266WiFi.h>
char* ssid = "BIA HOI VUONG ANH";   //Thay dia chi wifi bat duoc vao day
char* password = "biahoilocvung";  // Mat khau cua wifi
char servername[]="api:rauthuycanhiot.000webhostapp.com";              // remote server we will connect to
String result;
String ReadString,senddata;
int i = 0;
unsigned long timex; 
WiFiClient client;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  setWifi();
}
void setWifi(){
  Serial.println("Connecting");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) 
  {
  delay(500);
  }
  Serial.println("Connected");
  delay(1000);
}
void loop() {
  ReadUART();
}
void getData(){
  if (client.connect(servername, 80))   
          {                                         //starts client connection, checks for connection
          Serial.println("Conneted to server");
          senddata =  "GET /getdata.php?mode";
          senddata += ReadString;
          senddata += " HTTP/1.0\r\n";
          client.print(senddata);
          client.println("Host: rauthuycanhiot.000webhostapp.com\r\n\r\n");
          } 
  else {
         //Serial.println("connection failed");        //error message if no client connect
         //Serial.println();
       }
  while(client.connected() && !client.available()) 
  delay(1);                                          //waits for data
  while (client.connected() || client.available())    
       {                                             //connected or data available
         char c = client.read();                     //gets byte from ethernet buffer
         result = result+c;
       }
  //Serial.println(result);
  if (result.indexOf("mode=0") >= 0)
  {
    Serial.println("T");
  }
  if (result.indexOf("mode=1") >= 0)
  {
    Serial.println("M");
  }
  delay(50);
  if (result.indexOf("fan=1") >= 0)
  {
    Serial.println("A");
  }
  if (result.indexOf("fan=0") >= 0)
  {
    Serial.println("a");
  }
  delay(50);
  if (result.indexOf("pump=1") >= 0)
  {
    Serial.println("B");
  }
  if (result.indexOf("pump=0") >= 0)
  {
    Serial.println("b");
  }
  delay(50);
  if (result.indexOf("lamp=1") >= 0)
  {
    Serial.println("C");
  }
  if (result.indexOf("lamp=0") >= 0)
  {
    Serial.println("c");
  }
  client.stop();   
  result = "";     
}
void ReadUART(){
  if (Serial.available())
    {
      ReadString = Serial.readStringUntil(' ');
    }
  if (ReadString.length() >0) {
       /*ReadString.remove(ReadString.length()-1);
       if(Tach1(ReadString,'|')=="Temp"){
       Temp =  Tach2(ReadString,'|');
       }
       if(Tach1(ReadString,'|')=="RH"){
       RH =  Tach2(ReadString,'|');
       }
       if(Tach1(ReadString,'|')=="TDS"){
       TDS =  Tach2(ReadString,'|');
       }
       if(Tach1(ReadString,'|')=="CDS"){
       CDS =  Tach2(ReadString,'|');*/
       getData();
       //}
    }
    ReadString = "";
}
String Tach2(String chuoi,char kytu){
  byte moc;
  for (int i = 0; i < chuoi.length(); i++) {
    if (chuoi.charAt(i) == kytu) {
      moc = i; //Tìm vị trí của ky tu
    }
}
  chuoi.remove(0, moc + 1);
  //Serial.println(chuoi);
  return chuoi;
}
String Tach1(String chuoi, char kytu){
  byte moc;
  for (int i = 0; i < chuoi.length(); i++) {
    if (chuoi.charAt(i) == kytu) {
      moc = i; //Tìm vị trí của ky tu
    }
  }
  chuoi.remove(moc);
  //Serial.println(chuoi);
  return chuoi;
}
