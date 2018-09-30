#include "OLED.h"	
void freeMod(void){
				pinMode(SCL,1);
				pinMode(SDA,1);
	digitalWrite(SCL,1);
	digitalWrite(SDA,1);
}	
void start (){
				pinMode(SDA,1);
				pinMode(SCL,1);
	digitalWrite(SDA,1);
	//delayMicroseconds(2);
	digitalWrite(SCL,1);
	delayMicroseconds(4);
	digitalWrite(SDA,0);
	delayMicroseconds(4);
	digitalWrite(SCL,0);
}
void endMod (){
  pinMode(SCL,1);
	pinMode(SDA,1);
	digitalWrite(SCL,0);
	delayMicroseconds(2);
	digitalWrite(SDA,0);
	delayMicroseconds(4);
	digitalWrite(SCL,1);	
	delayMicroseconds(4);
	digitalWrite(SDA,1);
	delayMicroseconds(4);
}
void yack(){
  pinMode(SCL,1);
	pinMode(SDA,1);
	 digitalWrite(SCL,0);
	 delayMicroseconds(4);
	 digitalWrite(SDA,0);
	 delayMicroseconds(4);
	 digitalWrite(SCL,1);
	 delayMicroseconds(4);
	 digitalWrite(SCL,0);
}
void nack(){
  pinMode(SCL,1);
	pinMode(SDA,1);
	 digitalWrite(SCL,0);
	 delayMicroseconds(4);
	 digitalWrite(SDA,1);
	 delayMicroseconds(4);
	 digitalWrite(SCL,1);
	 delayMicroseconds(4);
	 digitalWrite(SCL,0);
}
char wait_ack(){//0 is Acked,1 is not acked;
				pinMode(SDA,1);
       pinMode(SCL,1);
	int x;
	digitalWrite(SCL,0);
	digitalWrite(SDA,1);
	delayMicroseconds(4);
	digitalWrite(SCL,1);
	delayMicroseconds(2);
				pinMode(SDA,INPUT);
	while(digitalRead(SDA))
	{
		x++;
		if(x>250)
		{
			endMod();
			return 1;
		}
	}
	digitalWrite(SCL,0);
	return 0;
}
void write_byte(uchar data_in){
				pinMode(SDA,1);
       pinMode(SCL,1);
	uchar i;
	digitalWrite(SCL,0);
	for (i=0;i<8;i++)
	{
		digitalWrite(SCL,0);	
		if((data_in&0x80)>>7)
		digitalWrite(SDA,1);
		else digitalWrite(SDA,0);
		data_in<<=1;
		digitalWrite(SCL,1);
		delayMicroseconds(4);
		digitalWrite(SCL,0);
		delayMicroseconds(4);	
	}
}
uchar read_byte(uchar ack)//1 ack;0 not ack;
{
				pinMode(SDA,1);
       pinMode(SCL,1);
	uchar x=0,i;
	digitalWrite(SCL,0);
	for (i=0;i<8;i++)
	{
		digitalWrite(SCL,0);
		delayMicroseconds(2);
		digitalWrite(SCL,1);
		x<<=1;
								pinMode(SDA,INPUT);
		if(digitalRead(SDA)) x++;
		delayMicroseconds(2);
								pinMode(SDA,OUTPUT);
	}
	if (!ack)
		nack();
	else 
	    yack();
	digitalWrite(SCL,0);
	return x;
}
/*void send_addresses(uchar slave_address,uchar reg_address)
{
	freeMod();
	start();
	write_byte(slave_address);
	wait_ack();
	write_byte(reg_address);
	wait_ack();
}*/
void oled_write_cmd(uchar cmd)
{
	start();
	write_byte(0x78);//write the device address
	wait_ack();
	write_byte(0x00);//write the command,co=0,c/d=0
	wait_ack();
	write_byte(cmd);
	wait_ack();
	endMod();
}
void oled_write_data(uchar data)
{
	start();
	write_byte(0x78);//write the device address
	wait_ack();
	write_byte(0x40);//write the data,co=0,c/d=1
	wait_ack();
	write_byte(data);
	wait_ack();
	endMod();
}
/*void oled_init(){
	delay(1);

   oled_write_cmd(0xAE);
	oled_write_cmd(0x00);
	oled_write_cmd(0x10);
	oled_write_cmd(0x40);
	oled_write_cmd(0xB0);
	oled_write_cmd(0x81);
	oled_write_cmd(0xFF);
	oled_write_cmd(0xA1);
	oled_write_cmd(0xA6);
	oled_write_cmd(0xA8);
	oled_write_cmd(0x3F);
	oled_write_cmd(0xC8);
	oled_write_cmd(0xD3);
	oled_write_cmd(0x00);
	oled_write_cmd(0xD5);
	oled_write_cmd(0x80);
	oled_write_cmd(0xD8);
	oled_write_cmd(0x05);
	oled_write_cmd(0xD9);
	oled_write_cmd(0xF1);
	oled_write_cmd(0xDA);
	oled_write_cmd(0x12);
	oled_write_cmd(0xDB);
	oled_write_cmd(0x30);
	oled_write_cmd(0x8D);
	oled_write_cmd(0x14);
	oled_write_cmd(0xAF);
	 oled_write_cmd(0xae);
  oled_write_cmd(0x00);
  oled_write_cmd(0x10);
  oled_write_cmd(0x40);
	oled_write_cmd(0x81);
  oled_write_cmd(0xcf); 
  oled_write_cmd(0xa1);
  oled_write_cmd(0xc8);
  oled_write_cmd(0xa6);
  oled_write_cmd(0xa8);
  oled_write_cmd(0x3f);
  oled_write_cmd(0xd3);
  oled_write_cmd(0x00);
  oled_write_cmd(0xd5);
  oled_write_cmd(0x80);
  oled_write_cmd(0xd9);
  oled_write_cmd(0xf1);
  oled_write_cmd(0xda);
  oled_write_cmd(0x12);
  oled_write_cmd(0xdb);
  oled_write_cmd(0x40);
  oled_write_cmd(0x20);
  oled_write_cmd(0x02);
  oled_write_cmd(0x8d);
  oled_write_cmd(0x14);
  oled_write_cmd(0xa4);
  oled_write_cmd(0xa6); 
  oled_write_cmd(0xaf);
}*/
void oled_init(){	
/* Init LCD */	
oled_write_cmd(0xAE); //display off
oled_write_cmd(0x20); //Set Memory Addressing Mode  
oled_write_cmd(0x10); //00,Horizontal Addressing Mode;01,Vertical Addressing Mode;10,Page Addressing Mode (RESET);11,Invalid	
oled_write_cmd(0xB0); //Set Page Start Address for Page Addressing Mode,0-7
oled_write_cmd(0xC8); //Set COM Output Scan Direction
oled_write_cmd(0x00); //---set low column address
oled_write_cmd(0x10); //---set high column address
oled_write_cmd(0x40); //--set start line address	
oled_write_cmd(0x81); //--set contrast control register
oled_write_cmd(0xFF);
oled_write_cmd(0xA1); //--set segment re-map 0 to 127
oled_write_cmd(0xA6); //--set normal display	
oled_write_cmd(0xA8); //--set multiplex ratio(1 to 64)	
oled_write_cmd(0x3F); //
oled_write_cmd(0xA4); //0xa4,Output follows RAM content;0xa5,Output ignores RAM content	
oled_write_cmd(0xD3); //-set display offset	
oled_write_cmd(0x00); //-not offset
oled_write_cmd(0xD5); //--set display clock divide ratio/oscillator frequency
oled_write_cmd(0xF0); //--set divide ratio	
oled_write_cmd(0xD9); //--set pre-charge period	
oled_write_cmd(0x22); //
oled_write_cmd(0xDA); //--set com pins hardware configuration
oled_write_cmd(0x12);
oled_write_cmd(0xDB); //--set vcomh
oled_write_cmd(0x20); //0x20,0.77xVcc
oled_write_cmd(0x8D); //--set DC-DC enable	
oled_write_cmd(0x14); //
oled_write_cmd(0xAF);
}
void oled_clear(){
	int a,j;
	//oled_write_cmd(0x22);
	for(a=0;a<8;a++){	  
		oled_write_cmd (0xb0+a);
		oled_write_cmd (0x00);
		oled_write_cmd (0x10);
		for (j=0;j<128;j++){
		oled_write_data (0);
		}
	}
}
void oled_full(){
	int a,j;
	//oled_write_cmd(0x22);
	for(a=0;a<8;a++){	  
		oled_write_cmd (0xb0+a);
		oled_write_cmd (0x00);
		oled_write_cmd (0x10);
		for (j=0;j<128;j++){
		oled_write_data (0xff);
		}
	}
}
void oled_page_pos(uchar x,uchar y)
{
   oled_write_cmd(0xb0 + y);
   oled_write_cmd(((x & 0xf0)>>4)|0x10);
   oled_write_cmd(x & 0x0f);
}
void displayPic_F(uchar (*a)[60]){
	//oled_write_cmd(0x22);
	for (int i=0;i<8;i++){
		oled_write_cmd (0xb0+i);
		oled_write_cmd (0x00);
		oled_write_cmd (0x10);
		for (int j=0;j<60;j++){
		oled_write_data (*(*(a+i)+j));
		}
	}
	endMod();
}
void displayPic_B(uchar (*a)[60]){
	//oled_write_cmd(0x22);
	for (int i=0;i<8;i++){
		oled_write_cmd (0xb0+i);
		oled_write_cmd (0x00);
		oled_write_cmd (0x14);
		for (int j=0;j<60;j++){
		oled_write_data (*(*(a+i)+j));
		}
	}
}
void cleanLeft(){
	//oled_write_cmd(0x22);
	for (int i=0;i<8;i++){
		oled_write_cmd (0xb0+i);
		oled_write_cmd (0x00);
		oled_write_cmd (0x10);
		for (int j=0;j<60;j++){
		oled_write_data (0);
		}
	}
}
void cleanRight(){
	//oled_write_cmd(0x22);
	for (int i=0;i<8;i++){
		oled_write_cmd (0xb0+i);
		oled_write_cmd (0x00);
		oled_write_cmd (0x14);
		for (int j=0;j<60;j++){
		oled_write_data (0);
		}
	}
}
/*
void displayWord (enum WORD n)
{
	oled_write_cmd(0x20);
	for (int i=0;i<2;i++){
	oled_write_cmd (0xb0+i);
	oled_write_cmd (0x00);
	oled_write_cmd (0x10);
		for (int j=0;j<10;j++){
	oled_write_data(*(*(*(BIGWORD+n)+i)+j));
}}
}
*/