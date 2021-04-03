#include <SoftwareSerial.h>
#include <PS4BT.h>
#include "motor.h"
#include <usbhub.h>

// Satisfy the IDE, which needs to see the include statment in the ino too.
#ifdef dobogusinclude
#include <spi4teensy3.h>
#endif
#include <SPI.h>

#define R1_1 22
#define R1_2 24
#define R2_1 26
#define R2_2 28
#define UD1 30
#define UD2 32

int vodung = 0;
int fullSpeed = 0;
unsigned long previousMillis = 0;  
//variable for button timer:
unsigned long upSttTime = 0;
unsigned long downSttTime = 0;
unsigned long leftSttTime = 0;
unsigned long rightSttTime = 0;
unsigned long cirSttTime = 0;
unsigned long crossSttTime = 0;
unsigned long triSttTime = 0;
unsigned long sqrSttTime = 0;
unsigned long L2SttTime = 0;
unsigned long R2SttTime = 0;
unsigned long L1SttTime = 0;
unsigned long R1SttTime = 0;
//
//Mode of speedrun:
int upSpeed = 1;
int downSpeed = 1;
int leftSpeed = 1;
int rightSpeed = 1;
int cirSpeed = 1;
int crossSpeed = 1;
int triSpeed = 1;
int sqrSpeed = 1;
int L2Speed = 1;
int R2Speed = 1;
int L1Speed = 1;
int R1Speed = 1;
//
const long interval = 4000;

USB Usb;
//USBHub Hub1(&Usb); // Some donglesBTD Btd(&Usb);
BTD Btd(&Usb); // You have to create the Bluetooth Dongle instance like so

//PS4BT PS4(&Btd, PAIR); //Ket noi lan dau bang cach nhan nut share và nut PS.

PS4BT PS4(&Btd); //Thay lenh phia tren bang lenh nay sau khi ket noi thanh cong, nap lai code, lan sau chi can nhan nut PS de ket noi.
//SoftwareSerial mySerial(10, 11);
bool printAngle, printTouch;
uint8_t oldL2Value, oldR2Value;
int tuan;
int R2Stt = 0; 
int L2Stt = 0;
int UpStt = 0;
int DownStt = 0;
int LeftStt = 0;
int RightStt = 0;
int TriStt = 0;
int CirStt = 0;
int CrStt = 0;
int SqrStt = 0;
int R1Stt = 0; 
int L1Stt = 0;

void setup() {
  Serial.begin(19200);
  motorSetup();
#if !defined(__MIPSEL__)
  while (!Serial); 
#endif
  pinMode(R1_1, OUTPUT);
  pinMode(R1_2, OUTPUT);
  pinMode(R2_1, OUTPUT);
  pinMode(R2_2, OUTPUT);
  pinMode(UD1, OUTPUT);
  pinMode(UD2, OUTPUT);
  if (Usb.Init() == -1) {
    Serial.print(F("\r\nOSC did not start"));
    while (1);
  }
    Serial.print(F("\r\nPS4 Bluetooth Library Started"));
}
void ButtonUp(int &upSpeed, unsigned long &upSttTime, int &UpStt){
  if(UpStt == 0){
    Serial.println(F("\r\nUP"));
    upSpeed = 1; 
    UpStt = 1;
    upSttTime = millis();
  }
  if(PS4.getButtonPress(OPTIONS)){
    motor_Tien(1, 255); 
    motor_Tien(2, 255); 
    motor_Lui(3, 255); 
    motor_Lui(4, 255);     
  }
  else{
    switch(upSpeed){
      case 1:
          motor_Tien(1, 5); 
          motor_Tien(2, 5); 
          motor_Lui(3, 5); 
          motor_Lui(4, 5); 
          if((millis() - upSttTime) > 30){
            upSpeed++;
            upSttTime = millis();
          } 
      break;
      case 2:
          motor_Tien(1, 10); 
          motor_Tien(2, 10); 
          motor_Lui(3, 10); 
          motor_Lui(4, 10); 
          if((millis() - upSttTime) > 30){ 
            upSpeed++;
            upSttTime = millis();
          }
      break;
      case 3:
          motor_Tien(1, 20); 
          motor_Tien(2, 20); 
          motor_Lui(3, 20); 
          motor_Lui(4, 20); 
          if((millis() - upSttTime) > 30){
            upSpeed++;
            upSttTime = millis();
          }
      break;
      case 4:
          motor_Tien(1, 40); 
          motor_Tien(2, 40); 
          motor_Lui(3, 40); 
          motor_Lui(4, 40); 
          if((millis() - upSttTime) > 50){
            upSpeed++;
            upSttTime = millis();
          }
      break;
      case 5:
          motor_Tien(1, 80); 
          motor_Tien(2, 80); 
          motor_Lui(3, 80); 
          motor_Lui(4, 80); 
          if((millis() - upSttTime) > 100){
            upSpeed++;
            upSttTime = millis();
          }
      break;
      case 6:
          motor_Tien(1, 160); 
          motor_Tien(2, 160); 
          motor_Lui(3, 160); 
          motor_Lui(4, 160);
      break;
    }
  }
}

//Handling Button Down******************************

void ButtonDown(int &downSpeed, unsigned long &downSttTime, int &DownStt){
  if(DownStt == 0){
    Serial.println(F("\r\DOWN"));
    downSpeed = 1; 
    DownStt = 1;
    downSttTime = millis();
  }
  switch(downSpeed){
    case 1:
        motor_Lui(1, 5); 
        motor_Lui(2, 5); 
        motor_Tien(3, 5); 
        motor_Tien(4, 5); 
        if((millis() - downSttTime) > 30){
          downSpeed++;
          downSttTime = millis();
        }
    break;
    case 2:
        motor_Lui(1, 10); 
        motor_Lui(2, 10); 
        motor_Tien(3, 10); 
        motor_Tien(4, 10); 
        if((millis() - downSttTime) > 30){
          downSpeed++;
          downSttTime = millis();
        }
    break;
    case 3:
        motor_Lui(1, 20); 
        motor_Lui(2, 20); 
        motor_Tien(3, 20); 
        motor_Tien(4, 20); 
        if((millis() - downSttTime) > 30){
          downSpeed++;
          downSttTime = millis();
        }
    break;
    case 4:
        motor_Lui(1, 40); 
        motor_Lui(2, 40); 
        motor_Tien(3, 40); 
        motor_Tien(4, 40); 
        if((millis() - downSttTime) > 50){
          downSpeed++;
          downSttTime = millis();
        }
    break;
    case 5:
        motor_Lui(1, 80); 
        motor_Lui(2, 80); 
        motor_Tien(3, 80); 
        motor_Tien(4, 80); 
        if((millis() - downSttTime) > 100){
          downSpeed++;
          downSttTime = millis();
        }
    break;
    case 6:
        motor_Lui(1, 160); 
        motor_Lui(2, 160); 
        motor_Tien(3, 160); 
        motor_Tien(4, 160); 
    break;
  }
}

//Handling Button Right******************************
void ButtonRight(int &rightSpeed, unsigned long &rightSttTime, int &RightStt){
  if(RightStt == 0){
    Serial.println(F("\r\RIGHT"));
    rightSpeed = 1; 
    RightStt = 1;
    rightSttTime = millis();
  }
  switch(rightSpeed){
    case 1:
        motor_Lui(1, 5); 
        motor_Tien(2, 5); 
        motor_Lui(3, 5); 
        motor_Tien(4, 5); 
        if((millis() - rightSttTime) > 30){
          rightSpeed++;
          rightSttTime = millis();
        }
    break;
    case 2:
        motor_Lui(1, 10); 
        motor_Tien(2, 10); 
        motor_Lui(3, 10); 
        motor_Tien(4, 10); 
        if((millis() - rightSttTime) > 30){
          rightSpeed++;
        rightSttTime = millis();
        }
    break;
    case 3:
        motor_Lui(1, 20); 
        motor_Tien(2, 20); 
        motor_Lui(3, 20); 
        motor_Tien(4, 20); 
        if((millis() - rightSttTime) > 30){
          rightSpeed++;
          rightSttTime = millis();
        }
    break;
    case 4:
        motor_Lui(1, 40); 
        motor_Tien(2, 40); 
        motor_Tien(3, 40); 
        motor_Lui(4, 40); 
        if((millis() - rightSttTime) > 50){
          rightSpeed++;
          rightSttTime = millis();
        }
    break;
    case 5:
        motor_Lui(1, 80); 
        motor_Tien(2, 80); 
        motor_Lui(3, 80); 
        motor_Tien(4, 80); 
        if((millis() - rightSttTime) > 100){
          rightSpeed++;
          rightSttTime = millis();
        }
    break;
    case 6:
        motor_Lui(1, 160); 
        motor_Tien(2, 160); 
        motor_Lui(3, 160); 
        motor_Tien(4, 160); 
    break;
  }
}

//Handling Button Left******************************

void ButtonLeft(int &leftSpeed, unsigned long &leftSttTime, int &LeftStt){
  if(LeftStt == 0){
    Serial.println(F("\r\LEFT"));
    leftSpeed = 1; 
    LeftStt = 1;
    leftSttTime = millis();
  }
  switch(leftSpeed){
    case 1:
        motor_Tien(1, 5); 
        motor_Lui(2, 5); 
        motor_Tien(3, 5); 
        motor_Lui(4, 5); 
        if((millis() - leftSttTime) > 30){
          leftSpeed++;
          leftSttTime = millis();
        }
    break;
    case 2:
        motor_Tien(1, 10); 
        motor_Lui(2, 10); 
        motor_Tien(3, 10); 
        motor_Lui(4, 10); 
        if((millis() - leftSttTime) > 30){
          leftSpeed++;
          leftSttTime = millis();
        }
    break;
    case 3:
        motor_Tien(1, 20); 
        motor_Lui(2, 20); 
        motor_Tien(3, 20); 
        motor_Lui(4, 20); 
        if((millis() - leftSttTime) > 30){
          leftSpeed++;
          leftSttTime = millis();
        }
    break;
     case 4:
        motor_Tien(1, 40); 
        motor_Lui(2, 40); 
        motor_Tien(3, 40); 
        motor_Lui(4, 40); 
        if((millis() - leftSttTime) > 50){
          leftSpeed++;
          leftSttTime = millis();
        }
    break;
    case 5:
        motor_Tien(1, 80); 
        motor_Lui(2, 80); 
        motor_Tien(3, 80); 
        motor_Lui(4, 80); 
        if((millis() - leftSttTime) > 100){
          leftSpeed++;
          leftSttTime = millis();
        }
    break;
    case 6:
        motor_Tien(1, 160); 
        motor_Lui(2, 160); 
        motor_Tien(3, 160); 
        motor_Lui(4, 160); 
    break;
  }
}

//Handling Button R2 - xoay phải
void R2Button(int &R2Speed, unsigned long &R2SttTime, int &R2Stt){    
  if(R2Stt == 0){
    Serial.println(F("\r\RIGHT ROTATE"));
    R2Speed = 1; 
    R2Stt = 1;
    R2SttTime = millis();
  }
  switch(R2Speed){
    case 1:
        motor_Lui(1, 5); 
        motor_Lui(2, 5); 
        motor_Lui(3, 5); 
        motor_Lui(4, 5); 
        if((millis() - R2SttTime) > 30){
          R2Speed++;
          R2SttTime = millis();
        }
    break;
    case 2:
        motor_Lui(1, 10); 
        motor_Lui(2, 10); 
        motor_Lui(3, 10); 
        motor_Lui(4, 10); 
        if((millis() - R2SttTime) > 30){
          R2Speed++;
          R2SttTime = millis();
        }
    break;
    case 3:
        motor_Lui(1, 20); 
        motor_Lui(2, 20); 
        motor_Lui(3, 20); 
        motor_Lui(4, 20); 
         if((millis() - R2SttTime) > 30){
          R2Speed++;
          R2SttTime = millis();
        }
    break;
    case 4:
        motor_Lui(1, 40); 
        motor_Lui(2, 40); 
        motor_Lui(3, 40); 
        motor_Lui(4, 40); 
        if((millis() - R2SttTime) > 30){
          R2Speed++;
          R2SttTime = millis();
        }
    break;
    case 5:
        motor_Lui(1, 80); 
        motor_Lui(2, 80); 
        motor_Lui(3, 80); 
        motor_Lui(4, 80); 
    break;
  } 
      
      
}
//Handling Button L2 - xoay trái
void L2Button(int &L2Speed, unsigned long &L2SttTime, int &L2pStt){    
  if(L2Stt == 0){
    Serial.println(F("\r\LEFT ROTATE"));
    L2Speed = 1; 
    L2Stt = 1;
    L2SttTime = millis();
  }
  switch(L2Speed){
    case 1:
        motor_Tien(1, 5); 
        motor_Tien(2, 5); 
        motor_Tien(3, 5); 
        motor_Tien(4, 5); 
        if((millis() - L2SttTime) > 30){
          L2Speed++;
          L2SttTime = millis();
        }
    break;
    case 2:
        motor_Tien(1, 10); 
        motor_Tien(2, 10); 
        motor_Tien(3, 10); 
        motor_Tien(4, 10); 
        if((millis() - L2SttTime) > 30){
          L2Speed++;
          L2SttTime = millis();
        }
    break;
    case 3:
        motor_Tien(1, 20); 
        motor_Tien(2, 20); 
        motor_Tien(3, 20); 
        motor_Tien(4, 20); 
         if((millis() - L2SttTime) > 30){
          L2Speed++;
          L2SttTime = millis();
        }
    break;
     case 4:
        motor_Tien(1, 40); 
        motor_Tien(2, 40); 
        motor_Tien(3, 40); 
        motor_Tien(4, 40); 
         if((millis() - L2SttTime) > 30){
          L2Speed++;
          L2SttTime = millis();
        }
    break;
    case 5:
        motor_Tien(1, 80); 
        motor_Tien(2, 80); 
        motor_Tien(3, 80); 
        motor_Tien(4, 80); 
    break;
  }        

}
//Handling Button R1 - cheo len phai
void R1Button(int &R1Speed, unsigned long &R1SttTime, int &R1Stt){    
  if(R1Stt == 0){
    Serial.println(F("\r\RIGHT CHEO"));
    R1Speed = 1; 
    R1Stt = 1;
    R1SttTime = millis();
  }
  switch(R1Speed){
    case 1:
        motor_Tien(1, 5); 
        motor_Dung(2); 
        motor_Dung(3); 
        motor_Lui(4, 5); 
        if((millis() - R1SttTime) > 30){
          R1Speed++;
          R1SttTime = millis();
        }
    break;
    case 2:
        motor_Tien(1, 10); 
        motor_Dung(2); 
        motor_Dung(3);  
        motor_Lui(4, 10); 
        if((millis() - R1SttTime) > 30){
          R1Speed++;
          R1SttTime = millis();
        }
    break;
    case 3:
       motor_Tien(1, 20); 
        motor_Dung(2); 
        motor_Dung(3);  
        motor_Lui(4, 20); 
        if((millis() - R1SttTime) > 30){
          R1Speed++;
          R1SttTime = millis();
        }
    break;
    case 4:
        motor_Tien(1, 40); 
        motor_Dung(2); 
        motor_Dung(3);  
        motor_Lui(4, 40); 
        if((millis() - R1SttTime) > 50){
          R1Speed++;
          R1SttTime = millis();
        }
    break;
    case 5:
        motor_Tien(1, 80); 
        motor_Dung(2); 
        motor_Dung(3);  
        motor_Lui(4, 80); 
        if((millis() - R1SttTime) > 100){
          R1Speed++;
          R1SttTime = millis();
        }
    break;
    case 6:
        motor_Tien(1, 160); 
        motor_Dung(2); 
        motor_Dung(3);  
        motor_Lui(4, 160); 
    break;
  }       
}
//Handling Button L2 - cheo len trai
void L1Button(int &L1Speed, unsigned long &L1SttTime, int &L1pStt){    
  if(L1Stt == 0){
    Serial.println(F("\r\LEFT CHEO"));
    L1Speed = 1; 
    L1Stt = 1;
    L1SttTime = millis();
  }
  switch(L1Speed){
    case 1:
        motor_Dung(1); 
        motor_Tien(2, 5); 
        motor_Lui(3, 5); 
        motor_Dung(4); 
        if((millis() - L1SttTime) > 30){
          L1Speed++;
          L1SttTime = millis();
        }
    break;
    case 2:
        motor_Dung(1); 
        motor_Tien(2, 10); 
        motor_Lui(3, 10); 
        motor_Dung(4); 
        if((millis() - L1SttTime) > 30){
          L1Speed++;
          L1SttTime = millis();
        }
    break;
    case 3:
        motor_Dung(1); 
        motor_Tien(2, 20); 
        motor_Lui(3, 20); 
        motor_Dung(4); 
        if((millis() - L1SttTime) > 30){
          L1Speed++;
          L1SttTime = millis();
        }
    break;
     case 4:
        motor_Dung(1); 
        motor_Tien(2, 40); 
        motor_Lui(3, 40); 
        motor_Dung(4); 
        if((millis() - L1SttTime) > 50){
          L1Speed++;
          L1SttTime = millis();
        }
    break;
    case 5:
        motor_Dung(1); 
        motor_Tien(2, 80); 
        motor_Lui(3, 80); 
        motor_Dung(4); 
        if((millis() - L1SttTime) > 100){
          L1Speed++;
          L1SttTime = millis();
        }
    break;
    case 6:
        motor_Dung(1); 
        motor_Tien(2, 160); 
        motor_Lui(3, 160); 
        motor_Dung(4); 
    break;
  }        

}    

//Handling Button Cross - LÊN
void CrossButton(){
  Serial.println(F("\r\CROSS ROTATE"));
  digitalWrite(UD1, 1);
  digitalWrite(UD2, 0); 
}
//Handling Button Square-XUỐNG
void SquareButton(){
  Serial.println(F("\r\SQUARE ROTATE"));
  digitalWrite(UD1, 0);
  digitalWrite(UD2, 1);
}
//Handling Button Triangle - GẤP
void TriangleButton (){
  Serial.println(F("\r\Tri ROTATE"));
  digitalWrite(R1_1, 1);
  digitalWrite(R1_2, 0);
  digitalWrite(R2_1, 1);
  digitalWrite(R2_2, 0);
}
//Handling Button Circle-NHẢ
void CircleButton(){
  Serial.println(F("\r\Cir ROTATE"));
  double thaTime = millis();
  while ((millis() - thaTime) < 50)
  {
    digitalWrite(R1_1, 0);
    digitalWrite(R1_2, 1);
    digitalWrite(R2_1, 0);
    digitalWrite(R2_2, 1);
  }
    digitalWrite(R1_1, 0);
    digitalWrite(R1_2, 0);
    digitalWrite(R2_1, 0);
    digitalWrite(R2_2, 0);
}
void loop() {
  
  Usb.Task();
  if(PS4.connected()) {
    if(PS4.getButtonPress(UP)||PS4.getButtonPress(DOWN)||PS4.getButtonPress(RIGHT)||PS4.getButtonPress(LEFT)||PS4.getButtonPress(TRIANGLE)||PS4.getButtonPress(CIRCLE)||PS4.getButtonPress(CROSS)
    || PS4.getButtonPress(SQUARE)|| PS4.getButtonPress(L2) || PS4.getButtonPress(R2)|| PS4.getButtonPress(L1) || PS4.getButtonPress(R1) );
      else { 
                  digitalWrite(UD1, 0);
                  digitalWrite(UD2, 0);
                  motor_Dung(1);
                  motor_Dung(2);
                  motor_Dung(3);
                  motor_Dung(4);
                  UpStt = 0;
                  DownStt = 0;
                  RightStt = 0;
                  LeftStt = 0;
                  TriStt = 0;
                  CirStt = 0;
                  goto ending;
               }
          if(PS4.getButtonClick(CROSS)) {
            CrossButton();
            goto ending;
          }
           if(PS4.getButtonClick(SQUARE)) {
            SquareButton(); 
            goto ending;
           }
           if(PS4.getButtonClick(CIRCLE)) {
            CircleButton(); 
            goto ending;
           }
           if(PS4.getButtonClick(TRIANGLE)) {
            TriangleButton(); 
            goto ending;
           }
          if (PS4.getButtonPress(UP)){ButtonUp(upSpeed, upSttTime, UpStt); goto ending; } 
          if (PS4.getButtonPress(DOWN)){ButtonDown(downSpeed, downSttTime, DownStt); goto ending; } 
          if(PS4.getButtonPress(RIGHT)){ ButtonRight(rightSpeed, rightSttTime, RightStt); goto ending;}
          if(PS4.getButtonPress(L2)){ L2Button(L2Speed, L2SttTime, L2Stt); goto ending;}
          if(PS4.getButtonPress(LEFT)){ ButtonLeft(leftSpeed, leftSttTime, LeftStt); goto ending;}  
          if(PS4.getButtonPress(R2)){ R2Button(R2Speed, R2SttTime, R2Stt); goto ending;}
          if(PS4.getButtonPress(R1)){ R1Button(R1Speed, R1SttTime, R1Stt); goto ending;}
          if(PS4.getButtonPress(L1)){ L1Button(L1Speed, L1SttTime, L1Stt); goto ending;}
  }
    
  ending: vodung = 1;
        

}
