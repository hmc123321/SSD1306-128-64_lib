//#include <reg52.h>
#include"Arduino.h"
//#include <intrins.h>
#ifndef OLED_H
#define OLED_H
#define uchar unsigned char 
#define uint unsigned int
#define SCL 9
#define SDA 8
extern uchar jiandao[][60];
extern uchar shitou[][60];
extern uchar bu[][60];
void freeMod();
void start();
void endMod();
void ack();
void nack();
char wait_ack();
void write_byte(uchar data_in);
uchar read_byte(uchar ack);
void oled_init();
void oled_write_data(uchar);
void oled_write_cmd(uchar);
void oled_clear();
void oled_full();
void oled_page_pos(uchar,uchar);
void displayPic_F(uchar (*a)[60]);
void displayPic_B(uchar (*a)[60]);
void cleanLeft();
void cleanRight();
//void H_displayPic(uchar (*)[128]);
//void displayWord(enum WORD);
#endif 