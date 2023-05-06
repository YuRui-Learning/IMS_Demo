#define TrigR 2 //引脚Tring 连接 IO D2
#define EchoR 3 //引脚Echo 连接 IO D3 
#define TrigL 4 //引脚Tring 连接 IO D2
#define EchoL 7 //引脚Echo 连接 IO D3 
#include <math.h>
int input1 = 5; // 定义uno的pin 5 向 input1 输出 
int input2 = 6; // 定义uno的pin 6 向 input2 输出
int input3 = 10; // 定义uno的pin 9 向 input3 输出
int input4 = 11; // 定义uno的pin 10 向 input4 输出
float dis_L; //超声波距离变量
float dis_R; //超声波距离变量
float temp; // 
char ch;
float x1,y1,x0,y0;
float distance; // 距离
float theta; // 夹角
bool flag_no_target = false; // 没有目标值 

double HC_SRO4(int echo,int trig);
void turn_Right (double theta);
void turn_Left (double theta);
void go_forword (double distance);

void setup() 
{
  Serial.begin(9600);
  pinMode(input1,OUTPUT);
  pinMode(input2,OUTPUT);
  pinMode(input3,OUTPUT);
  pinMode(input4,OUTPUT);
  pinMode(TrigR, OUTPUT);
  pinMode(EchoR, INPUT);
  pinMode(TrigL, OUTPUT);
  pinMode(EchoL, INPUT);
}



void loop() {
  x0 = 0;
  y0 = 0;
  x1 = 0;
  y1 = 0;
  dis_R = HC_SRO4(EchoR,TrigR);
  dis_L = HC_SRO4(EchoL,TrigL);
  if(dis_R > 0 and dis_R <50)
  {
      digitalWrite(input1,LOW);
      digitalWrite(input2,LOW);  
      digitalWrite(input3,LOW);
      digitalWrite(input4,LOW);  
      delay(100);  //延时0.5秒     
  }
  if(dis_L > 0 and dis_L <50)
  {
      digitalWrite(input1,LOW);
      digitalWrite(input2,LOW);  
      digitalWrite(input3,LOW);
      digitalWrite(input4,LOW);  
      delay(100);  //延时0.5秒   
  }

  if(!flag_no_target)
    Serial.println("please enter distance");
  if(Serial.available()>0 and !flag_no_target)
  {
    
    distance = Serial.parseInt();
    Serial.println(distance);
    go_forword(distance);


//    if(ch=='1')
//    {
//      // 直行
//      digitalWrite(input1,HIGH);
//      digitalWrite(input2,LOW);
//      digitalWrite(input3,HIGH);
//      digitalWrite(input4,LOW);
//      delay(1500);  
//      digitalWrite(input1,LOW);
//      digitalWrite(input2,LOW);  
//      digitalWrite(input3,LOW);
//      digitalWrite(input4,LOW);  
//      delay(100);  //延时0.5秒      
//    }
//    else if(ch=='2')
//    {
//     // 倒车
//      digitalWrite(input1,LOW);
//      digitalWrite(input2,HIGH);  
//      digitalWrite(input3,LOW);
//      digitalWrite(input4,HIGH);  
//      delay(500);   //延时1秒
//      digitalWrite(input1,LOW);
//      digitalWrite(input2,LOW);  
//      digitalWrite(input3,LOW);
//      digitalWrite(input4,LOW);  
//      delay(100);  //延时0.5秒    
//    }
//
//    else if(ch=='0')
//    {
//      // 停车
//      digitalWrite(input1,LOW);
//      digitalWrite(input2,LOW);  
//      digitalWrite(input3,LOW);
//      digitalWrite(input4,LOW);  
//      delay(100);  //延时0.5秒    
//    }
  }
}


double HC_SRO4(int echo,int trig)
{
  int dis;
  digitalWrite(trig, LOW); //给Trig发送一个低电平
  delayMicroseconds(2);    //等待 2微妙
  digitalWrite(trig,HIGH); //给Trig发送一个高电平
  delayMicroseconds(10);    //等待 10微妙
  digitalWrite(trig, LOW); //给Trig发送一个低电平
  temp = float(pulseIn(echo, HIGH)); //存储回波等待时间,
  dis = (temp * 17 )/1000; //把回波时间换算成cm
  return dis;
}

void go_forword (double distance)
{
  double straight_time = 0;
  int count_time = distance/75;
  while( count_time--)
  {
  digitalWrite(input1,HIGH);
  digitalWrite(input2,LOW);
  digitalWrite(input3,HIGH);
  digitalWrite(input4,LOW);
  delay(900);   //900ms大致能走75cm
  digitalWrite(input1,LOW);
  digitalWrite(input2,LOW);  
  digitalWrite(input3,LOW);
  digitalWrite(input4,LOW);  
  delay(20);  //延时0.5秒  
  }
  digitalWrite(input1,HIGH);
  digitalWrite(input2,LOW);
  digitalWrite(input3,HIGH);
  digitalWrite(input4,LOW);
  delay(int(distance)%75*12);   //按照900/75的转换，把余数加上
  digitalWrite(input1,LOW);
  digitalWrite(input2,LOW);  
  digitalWrite(input3,LOW);
  digitalWrite(input4,LOW);  
  delay(50);  //延时0.5秒     
}

void turn_Right (double theta)
{
  double turn_time = 0;
//  turn_time = 60 + 60*log10f(theta);
  if(theta <= 30)
  {
    turn_time = theta*4;
  }
  else if( theta <= 90)
  {
    turn_time = theta + 90;
  }
  else
  {
    turn_time = theta*2;
  }
    digitalWrite(input1,LOW); //给高电平
    digitalWrite(input2,HIGH);  //给低电平
    digitalWrite(input3,HIGH); //给高电平
    digitalWrite(input4,LOW);  //给低电平
    delay(int(turn_time));   //延时1秒
    digitalWrite(input1,LOW);
    digitalWrite(input2,LOW);  
    digitalWrite(input3,LOW);
    digitalWrite(input4,LOW);  
    delay(100);  //延时0.5秒     
}

void turn_Left (double theta)
{
  double turn_time = 0;
//  turn_time = 60 + 60*log10f(theta);
  if(theta <= 30)
  {
    turn_time = theta*4;
  }
  else if( theta <= 90)
  {
    turn_time = theta + 90;
  }
  else
  {
    turn_time = theta*2;
  }
    digitalWrite(input1,HIGH); //给高电平
    digitalWrite(input2,LOW);  //给低电平
    digitalWrite(input3,LOW); //给低电平
    digitalWrite(input4,HIGH);  //给高电平
    delay(int(turn_time));   //延时1秒
    digitalWrite(input1,LOW);
    digitalWrite(input2,LOW);  
    digitalWrite(input3,LOW);
    digitalWrite(input4,LOW);  
    delay(100);  //延时0.5秒     
}
