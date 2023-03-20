import processing.serial.*;

int Input[] = {0,0,0,0,0,0,0,0};
int Output[] = {0,0,0,0,0,0,0,0};
Serial port;
int val;        // Data received from the serial port
int sum=0;

void setup()
{
  size(1500,800);
  background(100);
  String portName ;
  println(Serial.list());
  port = new Serial(this,"COM6",115200); 
  port.bufferUntil('\n');
}

void serialEvent(Serial port)
{
 byte[] in_buff = port.readBytesUntil('\n');  // 프로세싱을 사용하려 경우 TC275의 송신 프로토콜에 마지막에 '\n'을 반드시 추가해서 넣을 것
 int byte_length = 0;
 int[] input_io_data = new int[8];
 int i;
 
 if(in_buff != null)
  {
    byte_length = in_buff.length;
    print("Data length :  ");
    println(byte_length);
    
      for(i=0;i<byte_length;i++)
      {
          print( (in_buff[i]+256)%256);  // byte의 범위가 -127+256이므로
          print("   ");
      }
   // println(hex(in_buff[0]));
   // println(in_buff[0]+256);
   // println(in_buff[1]+256);  
     println();
      for(i=0; i<8; i++)
      {
       input_io_data[i]=in_buff[i+2];
      }/*
       if( ( (in_buff[0]+ 256) == 174) && ( (in_buff[1]+ 256) == 184)  &&  ( (in_buff[2] == 'I') ) )
        {
           println("anaylze");
           println( (in_buff[4]+256)%256);
        // java modbus crc는 복잡하므로 여기서는 생략함
        
           for(i=0;i<byte_length;i++)
           {
              input_io_data[i] = (int)((in_buff[4] >>i) & 0x01);  // input ioport data가 저장 됨
              print(input_io_data[i]);
              print("  ");
           }
              println(); println(); println();      
        }*/
    }
     for(i=0; i<8; i++){
      if(input_io_data[i]==i+1){
        Output[i]=1;
      }
      else{
        Output[i]=0;
      }
    }
}

void draw() 
{ 
  background(65);
  fill(0,120,120);
  rect(100,100,1300,200);
  rect(100,500,1300,200);
  
  for(int i = 0; i < 8; i++)
  {
    fill(0);
    ellipse(200+i*150,200,80,80);
    ellipse(240+i*150,200,80,80);
    rect(200+i*150,160,40,80);  
    if(Input[i] == 0)
    {
      fill(255);
      ellipse(200+i*150,200,80,80);
    }
    else
    {
      fill(255);
      ellipse(240+i*150,200,80,80);
    }
      
      
    if (Input[i] == 0)
    {
    if(mousePressed && (mouseX > 160+i*150 && mouseX < 240 +i*150) &&(mouseY > 160 && mouseY < 240))
    {
       Input[i] = 1;
       delay(150);
    }
    }
   else
   {
    if(mousePressed && (mouseX > 220+i*150 && mouseX < 300 +i*150) &&(mouseY > 160 && mouseY < 240))
    {
      Input[i] = 0;
      delay(150);
    }
   }
   if(Input[i] == 0)
   {
     Output[i] = 0;
   }
   else
   {
     Output[i] = 1;
   }
   if(Output[i] == 0)
   {
     fill(255);
   }
   else
   {
     fill(255,0,0);
   }
   ellipse(200+i*150,600,80,80);
  }
  sum=0;
   
    if(Input[0]==1){
       sum = sum + 1;
    }
    if(Input[1]==1){
       sum = sum + 2;
    }
    if(Input[2]==1){
       sum = sum + 4;
    }
    if(Input[3]==1){
       sum = sum + 8;
    }
    if(Input[4]==1){
       sum = sum + 16;
    }
    if(Input[5]==1){
       sum = sum + 32;
    }
    if(Input[6]==1){
       sum = sum + 64;
    }
    if(Input[7]==1){
       sum = sum + 128;
    }
    
    port.write(sum);
  
}
