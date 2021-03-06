
#include <Wire.h>
#include <PixyI2C.h>

// This is the main Pixy object 
PixyI2C pixy;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.print("Starting...\n");

  pixy.init();
}

void loop() {
  // put your main code here, to run repeatedly:
static int i = 0;
  int j;
  uint16_t blocks;
  char buf[32]; 
  int largestArea =0;
  int largestAreaPos=0;
  // grab blocks!
  blocks = pixy.getBlocks();
  
  // If there are detect blocks, print them!
  if(blocks)
  {
    i++;
    
    // do this (print) every 50 frames because printing every
    // frame would bog down the Arduino
    if (i%50==0)
    {
      for (j=0; j<blocks; j++)
      {
        if(largestArea<pixy.blocks[j].width*pixy.blocks[j].height && pixy.blocks[j].width*pixy.blocks[j].height > 300)
        {
          sprintf(buf, "Detected %d:\n", blocks);
          Serial.print(buf);
          largestArea=pixy.blocks[j].width*pixy.blocks[j].height;
          largestAreaPos = j;
        }
      }
      if(largestArea!=0)
      {
        sprintf(buf, "  block %d: ", j);
        Serial.print(buf); 
        pixy.blocks[largestAreaPos].print();
        Serial.println(largestArea);
      }
    }
  }  
}
