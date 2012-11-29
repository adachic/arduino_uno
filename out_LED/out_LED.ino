#include <Usb.h>
#include <AndroidAccessory.h>

#define LED_PIN     13
#define LED_COMMAND 0x10
#define LED_OFF     0x00
#define LED_ON      0x01

//これが原因でLEDひからない
AndroidAccessory acc("ADACHIC","ADK KIT","ADK Arduino Board","1,0",
"http://adachic.github.com","0000000012345678");

void setup();
void loop();

void setup()
{
  Serial.begin(115200);
  Serial.println("Start");
  //デジタル入出力を初期化。13を出力にする。
 // delay(100);
  pinMode(3, OUTPUT);
  //digitalWrite(LED_PIN, HIGH);
  //ADK init, boot
  delay(100);
  acc.powerOn();
}

void loop()
{
  byte buf[2];
  
  //接続中なら受信処理を行う
  if(acc.isConnected()){
    int len = acc.read(buf, sizeof(buf), 1);
    
    if(len > 0){
      //buf[0] command LED_CONT=0x10
      //buf[1] value OFF/ON
      Serial.println("------");
      Serial.print("resv data. length:");
      Serial.print(len);
      Serial.print(" , Command: ");
      Serial.print(buf[0]);
      Serial.print(" , value: ");
      Serial.println(buf[1]);    
      
      if(buf[0] == LED_COMMAND){
        switch(buf[1]){
          case LED_OFF:
            digitalWrite(3, LOW);
            Serial.println("OFF");
            break;
          case LED_ON:
            digitalWrite(3, HIGH);
            Serial.println("ON");
            break;
          default:
            Serial.println("ETC");
            break;
        }
      }
    }
  } 
  /*
  delay(1000);               // wait for a second
  digitalWrite(13, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);               // wait for a second
    digitalWrite(13, HIGH);   // turn the LED on (HIGH is the voltage level)
  */
  delay(100);
}
