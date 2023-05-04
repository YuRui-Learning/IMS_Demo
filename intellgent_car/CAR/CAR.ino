#define TrigR 2 //引脚Tring 连接 IO D2
#define EchoR 3 //引脚Echo 连接 IO D3 
#define TrigL 4 //引脚Tring 连接 IO D2
#define EchoL 7 //引脚Echo 连接 IO D3 
int input1 = 5; // 定义uno的pin 5 向 input1 输出 
int input2 = 6; // 定义uno的pin 6 向 input2 输出
int input3 = 10; // 定义uno的pin 9 向 input3 输出
int input4 = 11; // 定义uno的pin 10 向 input4 输出
float dis_L; //距离变量
float dis_R; //距离变量
float temp; // 
char ch;

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

void loop() {
  dis_R = HC_SRO4(EchoR,TrigR);
  dis_L = HC_SRO4(EchoL,TrigL);
  Serial.print("dis_R:");
  Serial.println(dis_R);
  Serial.print("dis_L:");
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
  if(Serial.available()>0)
  {
    ch = Serial.read();
    if(ch=='1')
    {
      // 直行
      digitalWrite(input1,HIGH);
      digitalWrite(input2,LOW);
      digitalWrite(input3,HIGH);
      digitalWrite(input4,LOW);
      delay(1500);  
      digitalWrite(input1,LOW);
      digitalWrite(input2,LOW);  
      digitalWrite(input3,LOW);
      digitalWrite(input4,LOW);  
      delay(100);  //延时0.5秒      
    }
    else if(ch=='2')
    {
     // 倒车
      digitalWrite(input1,LOW);
      digitalWrite(input2,HIGH);  
      digitalWrite(input3,LOW);
      digitalWrite(input4,HIGH);  
      delay(500);   //延时1秒
      digitalWrite(input1,LOW);
      digitalWrite(input2,LOW);  
      digitalWrite(input3,LOW);
      digitalWrite(input4,LOW);  
      delay(100);  //延时0.5秒    
    }

    else if(ch=='3')
    {
      // 左转
      digitalWrite(input1,HIGH); //给高电平
      digitalWrite(input2,LOW);  //给低电平
      digitalWrite(input3,LOW); //给低电平
      digitalWrite(input4,HIGH);  //给高电平
      delay(100);   //延时1秒
      digitalWrite(input1,LOW);
      digitalWrite(input2,LOW);  
      digitalWrite(input3,LOW);
      digitalWrite(input4,LOW);  
      delay(100);  //延时0.5秒   
    }
    else if(ch=='4')
    {
      // 右转
      digitalWrite(input1,LOW); //给高电平
      digitalWrite(input2,HIGH);  //给低电平
      digitalWrite(input3,HIGH); //给高电平
      digitalWrite(input4,LOW);  //给低电平
      delay(100);   //延时1秒
      digitalWrite(input1,LOW);
      digitalWrite(input2,LOW);  
      digitalWrite(input3,LOW);
      digitalWrite(input4,LOW);  
      delay(100);  //延时0.5秒   
    }
    else if(ch=='0')
    {
      // 停车
      digitalWrite(input1,LOW);
      digitalWrite(input2,LOW);  
      digitalWrite(input3,LOW);
      digitalWrite(input4,LOW);  
      delay(100);  //延时0.5秒    
    }
  }
}
