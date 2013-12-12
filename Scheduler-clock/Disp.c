#include "Main.h"
#include "Disp.h"
#include "Port.h"

#define uchar unsigned char
#define uint unsigned int
uchar shi,fen,miao,nian,yue,ri,zou,s1num,flag,checker;
uchar code table[]=" 2013-12-19 THU ";
uchar code table1[]="    12:50:00    ";
uchar code table2[] = {31,28,31,30,31,30,31,31,30,31,30,31};

void delay(uint z)
    {
    uint x,y;
    for(x=z;x>0;x--)
        for(y=125;y>0;y--);
    }

void write_com(uchar com) //?地址
    {          
    rs=0;
    lcden=0; 
    P0=com;
    delay(5);
    lcden=1;
    delay(5);
    lcden=0;
    }

void write_date(uchar date)    //??据
    {
    rs=1;
    lcden=0;
    P0=date;
    delay(5);
    lcden=1;
    delay(5);
    lcden=0;
    }

void init()       
    {
    uchar num;
    flag = 0;
    lcden=0;
 // miao=55;
    fen=50;
    shi=12;
    nian=13;
    yue=12;
    ri=19;
    zou = 4+1;
  //date=4;
    write_com(0x38);
    write_com(0x0c);
    write_com(0x06);
    write_com(0x01);
    write_com(0x80);
    for(num=0;num<15;num++)
        {
        write_date(table[num]);
        delay(5) ;
        }
        write_com(0x80+0x40);
    for(num=0;num<15;num++)
        {
        write_date(table1[num]);
        delay(5);
        }
       // TMOD=0x01; 
       // TH0=(65536-50000)/256;
       // TL0=(65536-50000)%256;
       // EA=1;
       // ET0=1;
       // TR0=1;
    }
    
void write_sfm(uchar add,uchar date) //??分秒
	{
        uchar shi,ge;
        shi=date/10;
        ge=date%10;
        write_com(0x80+0x40+add);
        write_date(0x30+shi);
        write_date(0x30+ge);
        }

void write_nyr(uchar add,uchar date)   //?年月日
    {
    uchar shi,ge;
    shi=date/10;
    ge=date%10;
    write_com(0x80+add);
    write_date(0x30+shi);
    write_date(0x30+ge);
    }

void write_z(uchar add,uchar date)      //?星期
    {	
    if(date==1) { write_com(0x80+add);write_date(0x53); write_date(0x55);write_date(0x4e);}
    if(date==2) { write_com(0x80+add);write_date(0x4d); write_date(0x4f);write_date(0x4e);}
    if(date==3) { write_com(0x80+add);write_date(0x54); write_date(0x55);write_date(0x45);}
    if(date==4) { write_com(0x80+add);write_date(0x57); write_date(0x45);write_date(0x44);} 
    if(date==5) { write_com(0x80+add);write_date(0x54); write_date(0x48);write_date(0x55);}
    if(date==6) { write_com(0x80+add);write_date(0x46); write_date(0x52);write_date(0x49);}
    if(date==0) { write_com(0x80+add);write_date(0x53); write_date(0x54);write_date(0x41);} 
    }

void flags()       // ???描
    {
        rd=0;
    //if(s1==0)
    //{
    //delay(5);  
   	if(s1==0)
         {
       	    
	    s1num++;
            while(!s1);
	    flag=1;
	    //P2 = flag
                    if(s1num==1)
            	        {
                          //TR2=0;
                            write_com(0x80+0x40+11);
                            write_com(0x0f);
                        }
                        if(s1num==2)
                        {
			    write_com(0x80+0x40+8);
		        }
                        if(s1num==3)
                        {
		            write_com(0x80+0x40+5);
                        }
                        if(s1num==4)
                        {
                            write_com(0x80+12);
                        }
                        if(s1num==5)
		        {
		            write_com(0x80+10);
                        }
                        if(s1num==6)
                        {
                            write_com(0x80+7);
                        }
                        if(s1num==7)
                        {
                            write_com(0x80+4);
                        }
                        if(s1num==8)
                        {
                            s1num=0;
	                    flag=0;
			    P1 = flag;
	                    write_com(0x0c);
                            //TR2=1;
                        }  
	            }
                    
                
	   
            
        }       

void keyscan()
{
if(flag == 1)
{
if(s1num!=0)
                    {
                        if(s2==0)
		        {
                            delay(5);
                            if(s2==0)
                            {
		                while(!s2);
			        if(s1num==1)
			        {
		                    miao++;
			            if(miao==60)
			            miao=0;
			            write_sfm(10,miao);
			            write_com(0x80+0x40+11);
		                }
		                if(s1num==2)
			        {
			            fen++; 
			            if(fen==60)
			            fen=0;
			            write_sfm(7,fen);
			            write_com(0x80+0x40+8);
		          	}
			        if(s1num==3)
		                {
			            shi++; 
			            if(shi==24) 
		                    shi=0;
			            write_sfm(4,shi);
			            write_com(0x80+0x40+5);
			        }
			        if(s1num==4)
			        {
			            zou++; 
			            if(zou==7)
			            zou=0;
			            write_z(12,zou);
			            write_com(0x80+12);
			        }   
			        if(s1num==5)
			        {
			            ri++; 
			            if(ri==table2[yue-1]+1) 
			            ri=1;
			            write_nyr(9,ri);
			            write_com(0x80+9);
			        }
			        if(s1num==6)
			        {
			            yue++; 
			            if(yue==13)
			            yue=1;
			            write_nyr(6,yue);
			            write_com(0x80+6);
			        }
			        if(s1num==7)
			        {
			            nian++; 
			            if(nian==100) 
			            nian=00;
		                    write_nyr(3,nian);
			            write_com(0x80+3);
			        }
		            }
          	        }	
	                if(s3==0)
                        {
	                    delay(5);
	                    if(s3==0)
	                    {
	                        while(!s3);
		                if(s1num==1)
	             	        {
                                    miao--;
                                    if(miao==-1)
		                    miao=59;
                                    write_sfm(10,miao);
                                    write_com(0x80+0x40+10);
                                }
		                if(s1num==2)
                                {
                                    fen--; 
                                    if(fen==-1) 
		                    fen=59;
		                    write_sfm(7,fen);
                                    write_com(0x80+0x40+7);
                                }
		                if(s1num==3)
                                { 
                                    shi--; 
                                    if(shi==-1) 
		                    shi=23;
                                    write_sfm(4,shi);
                                    write_com(0x80+0x40+4);
                                }
		                if(s1num==4)
                                {
                    	            zou--; 
                                    if(zou==-1) 
		                    zou=7;
                                    write_z(12,zou);
                                    write_com(0x80+12);
                                }   
		                if(s1num==5)
                                {
                                    ri--; 
                                    if(ri==0) 
		                    ri=table2[yue-1];
                                    write_nyr(9,ri);
                                    write_com(0x80+9);
                                }
		                if(s1num==6)
                                {
                                    yue--; 
                                    if(yue==0) 
		                    yue=12;
                                    write_nyr(6,yue);
                                    write_com(0x80+6);
                                }
		                if(s1num==7)
                                {
                                    if(nian==00) 
		                    nian=100;
                                    nian--; 
	                            write_nyr(3,nian);
                                    write_com(0x80+3);
                                }
	                    }
	                }
                    }
}
}
void DispUpdate()
{
    if(flag==0)
    {
    miao++;
    //P2=miao;
    if(miao==60)
        {
        miao=0;
        fen++;
        if(fen==60)
            {
            fen=0;
            shi++;
            if(shi==24)
	        {
                shi=0;
                ri++;
                zou++;
                if(ri==31)
                    {
                    ri=1;
                    yue++;
                    if(yue==13)
                        {
			yue=1;
			nian++;
                        if(nian==100)
			    {
                            nian=00;
			    }
                            write_nyr(3,nian);
			}
                        write_nyr(6,yue);
	            }
                    write_nyr(9,ri);
		    if(zou==7)
                        {
			zou=0;
			}
			write_z(12,zou);
                }
                write_sfm(4,shi);
            }
            write_sfm(7,fen);
        }
	write_sfm(10,miao);
    }
}



