#include "Main.h"
#include "Swit_D.h"
#include "2_01_12g.H"
#include "Disp.h"

//define uchar unsigned char
//extern uchar flag;

void main(void) {
  SCH_Init_T2();
  //P1 = 0x0f;
  init();
  SCH_Add_Task(DispUpdate, 0, 1000);
  SCH_Add_Task(keyscan, 0, 20);
  SCH_Add_Task(flags, 0, 20);
  SCH_Add_Task(play, 0, 100);
  SCH_Add_Task(recmode, 0, 50);
  SCH_Add_Task(record, 0, 15);
  SCH_Add_Task(playrec, 0, 20);
  SCH_Start();

  while(1) 
  {	 
      SCH_Dispatch_Tasks();    
  }
}
