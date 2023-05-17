#include <SoftwareSerial.h>

#define TrigR 2 //引脚Tring 连接 IO D2
#define EchoR 3 //引脚Echo 连接 IO D3 
#define TrigL 4 //引脚Tring 连接 IO D2
#define EchoL 7 //引脚Echo 连接 IO D3 


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
String detectString();
void clearList();
void getList();

SoftwareSerial softSerial(8, 9); // RX, TX
typedef struct
{
  int data[50][2] = {{0,0}};
  int len = 0;
}List;
List list;


void setup() 
{
  Serial.begin(9600);
  softSerial.begin(115200);
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
  Serial.println(dis_R);
  Serial.println(dis_L);
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
    Serial.println("please enter location");
  if(Serial.available()>0 and !flag_no_target)
  {
    
    x1 = Serial.parseInt();
    Serial.print("x is");
    Serial.println(int(x1));
    y1 = Serial.parseInt();
    Serial.print("y is");
    Serial.println(y1);
    float dis_x = x1 - x0;
    float dis_y = y1 - y0;
    distance = sqrt(pow(dis_x,2) + pow(dis_y,2));
    
//    flag_no_target = true;
    theta = atan(dis_x/dis_y);
    Serial.print("distance is ");
    Serial.println(distance);
    Serial.print("theta is ");
    theta = theta * 180 / M_PI;
    Serial.println(theta);
    turn_Right(theta);
    Serial.println("turn right");
    delay(200); 
    go_forword(distance);
    Serial.println("go stragiht");
  }
  if(softSerial.available())
  {
    getList();
    for (int i=0; i<list.len; i++)
    {
      Serial.print(list.data[i][0]);
      Serial.print('\t');
      Serial.println(list.data[i][1]);
    }
    Serial.println("============");
    clearList();
  }

}

double HC_SRO4(int echo,int trig) //超声波
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

void go_forword (double distance) //直行
{
  double straight_time = 0;
  int count_time = distance/75;

  while( count_time--)
  {
    dis_R = HC_SRO4(EchoR,TrigR);
    dis_L = HC_SRO4(EchoL,TrigL);
    if(dis_R > 0 and dis_R <50 or dis_L > 0 and dis_L)
    {
      digitalWrite(input1,LOW);
      digitalWrite(input2,LOW);  
      digitalWrite(input3,LOW);
      digitalWrite(input4,LOW);  
      delay(20);  //延时0.5秒
      count_time = 0 ; 
      break;
    }
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
  delay(int(distance)%75*10+150);   //按照900/75的转换，把余数加上
  digitalWrite(input1,LOW);
  digitalWrite(input2,LOW);  
  digitalWrite(input3,LOW);
  digitalWrite(input4,LOW);  
  delay(50);  //延时0.5秒     
}

void turn_Right (double theta) // 右转
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

void turn_Left (double theta)  // 左转
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


String detectString()
{
  while(softSerial.read() != '{');
  return(softSerial.readStringUntil('}'));
}
void clearList()
{
  memset(list.data, sizeof(list.data),0);
  list.len = 0;
}
void getList()
{
  String s = detectString();
  String numStr = "";
  for(int i = 0; i<s.length(); i++)
  {
    if(s[i]=='('){
      numStr = "";
    }
    else if(s[i] == ','){
      list.data[list.len][0] = numStr.toInt();
      numStr = "";
    }
    else if(s[i]==')'){
      list.data[list.len][1] = numStr.toInt();
      numStr = "";
      list.len++;
    }
    else{
      numStr += s[i];
    }
  }
}
