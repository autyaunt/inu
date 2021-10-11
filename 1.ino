#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define OLED_RESET-1
Adafruit_SSD1306 OLED(OLED_RESET);


int ballX=40;
int ballY=14;
int ballR=1;
int y=1;
int x=-1;
int newBall;

int screenW = 100 ;
int screenH = 32;

int boardX = 8;
int boardY =12;
  int boardWight = 1;
int boardHeight = 8;

int speakerPin = 9;

int button1 = 6;
int button2 = 5;
void setup()
{
  digitalWrite(speakerPin, HIGH);
  Serial.begin(115200); OLED.begin(SSD1306_SWITCHCAPVCC,0x3C);
  pinMode(button1,INPUT_PULLUP);
  pinMode(button2,INPUT_PULLUP);

}
void loop()
{
  
  int reading1= digitalRead(button1);
  int reading2= digitalRead(button2);
  //ถ้าบอลติดจอขวาจะเปลี่ยนทิศ 
  //ถ้าจะให้เด้งตอนชิดขวาสุด จุดวาดบอลจะต้องห่างจากมุม 2r
  for(int i = 0;i<=1;i++){
    if(ballY == screenH - 2*ballR-1){
    y=-y;
    tone(speakerPin,370);
    delay(50);
    noTone(speakerPin);
    
  }
  //ถ้าบอลติดจอซ้ายจะเปลี่ยนทิศ ต้องบวก 1 เพราะ จอซ้ายสุดวาด 4 เหลี่ยมแบบแค่เส้น แล้วเส้นมันมีกรอบยาว 1 หน่วย 
  if(ballY == 2*ballR){
    y=-y;
    tone(speakerPin,370);
    delay(50);
    noTone(speakerPin);
  }
  //ถ้าจะให้เด้งตอนชิดบนสุดสุด จุดวาดบอลจะต้องห่างจากมุม 2r 
  if(ballX== screenW-2*ballR-1){
    x=-x; 
    tone(speakerPin,370);
    delay(50);
    noTone(speakerPin); 
  }

//****************************************************************
// กดปุ่มแรงก็เลื่อนบขวา กดปุ่มสองก็เลื่อนซ้าย
//24 = ความกว้างจอ - ความยาวบอร์ด
  if(reading1 == 0 && boardY >1){
    boardY -= 1;
  }
  if(reading2 == 0 && boardY < screenH - boardHeight-1){
    boardY += 1;
  }
  // ชนกลับบอร์ด 
  //วงเล็บแรกคือที่จะชนแล้วเด้งในระยะความกว้างของบอร์ด วงเล็บสองคือจะเด้งเมื่ออยู่เหลือบอร์ด
  if( (ballY <= boardY + boardHeight && ballY >= boardY)&& (ballX == boardX + boardWight + ballR  ) ){
    x=-x; 
    tone(speakerPin,370);
    delay(50);
    noTone(speakerPin);
  }
  
  
//*****************************************************************

  if(ballX < 1 ){
    OLED.clearDisplay(); 
    OLED.drawRect(0,0, screenW,screenH,WHITE); 
    OLED.fillRect(boardX,boardY, boardWight,boardHeight,WHITE); 
    ballX=40;
    ballY=14;
    y = rand()%2;
    if(y == 0){
      y = -1;      
    }
    else if(y==1){
      y=1;
    } 
    tone(speakerPin,370);
    delay(50);
    noTone(speakerPin);
  }
  ballX +=x;
  ballY += y;
  }

  OLED.clearDisplay(); 
OLED.drawRect(0,0, screenW,screenH,WHITE); 
OLED.fillCircle( ballX, ballY, ballR, WHITE);
OLED.fillRect(boardX,boardY, boardWight,boardHeight,WHITE); 
OLED.display();
  
}
