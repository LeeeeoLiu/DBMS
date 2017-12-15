/*********************************包含头文件********************************/
#include <reg51.h>
#include <intrins.h>
#include <stdio.h>

/*********************************端口定义**********************************/
typedef unsigned char UINT8;                        /* 给unsigned char重新定义一个别名UINT8，用的时候直接写UINT8就可以 */
typedef unsigned int UINT16;                        /* 给unsigned int重新定义一个别名UINT16，用的时候直接写UINT16就可以 */
unsigned char code
mon51[3] _at_ 0x3b;
sbit RELAY = P2 ^1;  //定义继电器使用的IO口
sbit S4 = P3 ^2;  //定义按键使用的IO口
sbit rs = P3 ^5;
sbit rw = P3 ^6;
sbit ep = P3 ^4;
sbit light = P2 ^0;
sbit beep = P2 ^3;
sbit S5 = P3 ^3;
sbit workled = P2 ^4;
sbit freeled = P2 ^2;
unsigned int count;
unsigned int cost;
unsigned int tmpCount;
char tmp;
/********************************显示数据表*********************************/
unsigned char code
dis1[] = {
"Bicycle Sharing"};
unsigned char code
dis2[] = {
"Daytime 2 $/h"};
unsigned char code
dis3[] = {
"Night   1 $/h"};

/*****************************************************************************
函数功能:LCD延时子程序
入口参数:ms
出口参数:
*****************************************************************************/
void delayLCD(unsigned char ms) {
    unsigned char i;
    while (ms--) {
        for (i = 0; i < 250; i++) {
            _nop_();
            _nop_();
            _nop_();
            _nop_();
        }
    }
}

/*****************************************************************************
函数功能:测试LCD忙碌状态
入口参数:
出口参数:result
*****************************************************************************/
bit lcd_bz() {
    bit result;
    rs = 0;
    rw = 1;
    ep = 1;
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    result = (bit)(P0 & 0x80);
    ep = 0;
    return result;
}

/*****************************************************************************
函数功能:写指令数据到LCD子程序
入口参数:cmd
出口参数:
*****************************************************************************/
void lcd_wcmd(unsigned char cmd) {
    while (lcd_bz());//判断LCD是否忙碌
    rs = 0;
    rw = 0;
    ep = 0;
    _nop_();
    _nop_();
    P0 = cmd;
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    ep = 1;
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    ep = 0;
}

/*****************************************************************************
函数功能:设定显示位置子程序
入口参数:pos
出口参数:
*****************************************************************************/
void lcd_pos(unsigned char pos) {
    lcd_wcmd(pos | 0x80);
}

/*****************************************************************************
函数功能:写入显示数据到LCD子程序
入口参数:dat
出口参数:
*****************************************************************************/
void lcd_wdat(unsigned char dat) {
    while (lcd_bz());//判断LCD是否忙碌
    rs = 1;
    rw = 0;
    ep = 0;
    P0 = dat;
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    ep = 1;
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    ep = 0;
}

/*****************************************************************************
函数功能:LCD初始化子程序
入口参数:
出口参数:
*****************************************************************************/
void lcd_init() {
    delayLCD(10);
    lcd_wcmd(0x38);
    delayLCD(10);
    lcd_wcmd(0x38);
    delayLCD(10);
    lcd_wcmd(0x38);
    delayLCD(10);
    lcd_wcmd(0x0c);
    delayLCD(10);
    lcd_wcmd(0x06);
    delayLCD(10);
    lcd_wcmd(0x01);
    delayLCD(10);
}

void delay1s(void) {

    unsigned char h, i, j, k;

    for (h = 5; h > 0; h--)

        for (i = 4; i > 0; i--)

            for (j = 116; j > 0; j--)

                for (k = 214; k > 0; k--);

}


void delay(unsigned int i) {
    while (i--) {
        delay1s();
    }
}

void send(unsigned char *dat) {
    while (*dat != '\0') {
        ES = 0;
        SBUF = *dat;
        dat++;
        while (!TI);
        TI = 0;
        ES = 1;
    }
}

void showdaytime() {
    unsigned char i;
    lcd_pos(0x40);// 设置显示位置
    i = 0;
    while (dis2[i] != '\0') {
        lcd_wdat(dis2[i]);// 显示字符
        i++;
    }
}

void shownight() {
    unsigned char i;
    lcd_pos(0x40);// 设置显示位置
    i = 0;
    while (dis3[i] != '\0') {
        lcd_wdat(dis3[i]);// 显示字符
        i++;
    }
}

void uart()

interrupt 4
{
unsigned char dest[50];
unsigned int dayCount = 0;
unsigned int nightCount = 0;
unsigned int flag = 0;
if(RI)
{
RI = 0;
P1 = SBUF;
if(P1==0x30)
{
send("Unlocked!\n");
send("You can use this shared bike, and we're staring to clock now.\n");
send("Press S4 keyboard to lock when you want to stop using.\n");
freeled = 0;
workled = 1;
count = 0;
tmpCount = 0;
cost = 0;
dayCount = 0;
nightCount = 0;
RELAY = 1;
P1 = 0xfe;
if(!light)
{
showdaytime();

cost = cost + 2;
dayCount++;
}else{
shownight();

cost = cost + 1;
nightCount++;
}
beep = 0;

delay1s();

tmpCount++;
beep = 1;
flag = 0;
while(RELAY){
if(flag)
{
RELAY = 0;
}
if(tmpCount==10)
{
if(P1==0x00)
{
count++;
P1 = 0xff;
}
tmp = P1;

delay1s();

tmpCount = 1;
P1 = tmp << 1;
if(!light)
{
showdaytime();

cost = cost + 2;
dayCount++;
}else{
shownight();

cost = cost + 1;
nightCount++;
}
}

delay1s();

tmpCount++;

if(S4 == 0)    //如果按键按下
{
flag = 1;
}

}

sprintf(dest,
"Your total cost is %d $,including %d daytime and %d night.\n",cost,dayCount,nightCount);
send(dest);
freeled = 1;
workled = 0;
}
}
if(TI)
{
TI = 0;
}
}

/*****************************************************************************
函数功能:主程序
入口参数:
出口参数:
*****************************************************************************/
void main(void) {
    unsigned char i;
    TMOD = 0x20;
    SCON = 0x50;      //方式1，允许接收
    TH1 = 0xFD;  //11.0592m,9600
    TL1 = TH1;
    PCON = 0x00;
    EA = 1;
    ES = 1;
    TR1 = 1;
    P1 = P2 = 0xff;
    RELAY = 0;
    freeled = 1;
    workled = 0;
    lcd_init();// 初始化LCD
    delayLCD(10);
    lcd_pos(0x00);//设置显示位置
    i = 0;
    while (dis1[i] != '\0') {
        lcd_wdat(dis1[i]);//显示字符
        i++;
    }
    lcd_pos(0x40);// 设置显示位置
    i = 0;
    while (dis2[i] != '\0') {
        lcd_wdat(dis2[i]);// 显示字符
        i++;
    }
    while (1) {
        if (!light) {
            showdaytime();
        } else {

            shownight();
        }

    }
}

