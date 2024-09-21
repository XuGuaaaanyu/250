    /*
     # 这个样例代码用来测试DC Motor Driver 2x15A_lite module.

     # Editor : Phoebe
     # Date   : 2012.11.6
     # Ver    : 0.1
     # Product: DC Motor Driver 2x15A_lite
     # SKU    : DRI0018

     # 描述:
     # 用DC Motor Driver module驱动2个电机

     # 硬件:
     1. Arduino UNO
     2. DC Motor Driver 2x15A_lite
     3. DC motors x2

     步骤:
     1.M1_PWM & M2_PWM --> digital 5 & 6
     2.M1_EN & M2_EN --> digital 4 & 7
     3.+5V --> 5V
     4.GND --> GND

     下面代码中注释掉的部分是用来电流检测的，如需检测连接：
     1.LA_IS 和 RA_IS 同时连接 数字口2
     2.LB_IS 和 RB_IS 同时连接 数字口3
     */

    int E1 = 5;     //M1 速度控制
    int E2 = 6;     //M2 速度控制
    int M1 = 4;     //M1 方向控制
    int M2 = 7;     //M1 方向控制
    int counter=0;

    void stop(void)
    {                   //停止
      digitalWrite(E1,0);
      digitalWrite(M1,LOW);
      digitalWrite(E2,0);
      digitalWrite(M2,LOW);
    }
    void advance(char a,char b)          //前进
    {
      analogWrite (E1,a);      //PWM 速度控制
      digitalWrite(M1,HIGH);
      analogWrite (E2,b);
      digitalWrite(M2,HIGH);
    }
    void back_off (char a,char b)          //后退
    {
      analogWrite (E1,a);
      digitalWrite(M1,LOW);
      analogWrite (E2,b);
      digitalWrite(M2,LOW);
    }
    void turn_L (char a,char b)             //左转
    {
      analogWrite (E1,a);
      digitalWrite(M1,LOW);
      analogWrite (E2,b);
      digitalWrite(M2,HIGH);
    }
    void turn_R (char a,char b)             //右转
    {
      analogWrite (E1,a);
      digitalWrite(M1,HIGH);
      analogWrite (E2,b);
      digitalWrite(M2,LOW);
    }

    void current_sense()                  // 电流检测
    {
      int val1=digitalRead(2);
      int val2=digitalRead(3);
      if(val1==HIGH || val2==HIGH){
        counter++;
        if(counter==3){
          counter=0;
          Serial.println("Warning");
        }
      }
    }

    void setup(void)
    {
      int i;
      for(i=4;i<=7;i++)
        pinMode(i, OUTPUT);
      Serial.begin(19200);      //Set Baud Rate设置波特率
      Serial.println("Run keyboard control");
      digitalWrite(E1,LOW);
      digitalWrite(E2,LOW);
    }

    void loop(void)
    {
      advance(255,255);
      delay(1000);
      back_off(255,255);
      delay(1000);
    }