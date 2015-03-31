#include "pcf8563.h"
#include "iic.h"

T_Time time;
T_DownCounter dcounter;

/******************************************************************
 - 功能描述：向地址addr的寄存器写入多个字节
 - 隶属模块：PCF8563驱动模块
 - 函数属性：内部
 - 参数说明：addr:寄存器地址
             length:要写入的字节数
             pbuf:指向数据缓冲区的指针           
 - 返回说明：操作结果，0表示成功，1表示失败
 - 注：无
 ******************************************************************/

unsigned char PCF8563_Write_Bytes(unsigned char addr,unsigned char length,unsigned char *pbuf)
{
 unsigned char i=0;
 IIC_Start(); //IIC通信开始
 if(IIC_Write_Byte(0xa2)) return 1; //写PCF8563的ID与读写控制位,通信有错误立即返回
 if(IIC_Write_Byte(addr)) return 1; //写寄存器地址
 for(i=0;i<length;i++) //写入length个字节
 {
  if(IIC_Write_Byte(pbuf[i])) return 1;//写数据
 }
 IIC_Stop(); 
 return 0;
}

/******************************************************************
 - 功能描述：从地址addr的寄存器读取多个字节
 - 隶属模块：PCF8563驱动模块
 - 函数属性：内部
 - 参数说明：addr:寄存器地址
             length:要读出的字节数
             pbuf:指向数据缓冲区的指针           
 - 返回说明：操作结果，0表示成功，1表示失败
 - 注：无
 ******************************************************************/

unsigned char PCF8563_Read_Bytes(unsigned char addr,unsigned char length,unsigned char *pbuf) //从地址addr连续读取length个字节到pbuf
{ 
 unsigned char i=0,err=0;
 IIC_Start(); //IIC通信开始
 if(IIC_Write_Byte(0xa2)) return 1; //写PCF8563的ID与读写控制位,通信有错误立即返回
 if(IIC_Write_Byte(addr)) return 1; //写寄存器地址

 IIC_Start(); //IIC通信开始
 if(IIC_Write_Byte(0xa3)) return 1; //写PCF8563的ID与读写控制位
 for(i=0;i<length-1;i++) //写入前length-1个字节，并作出应答
 {
  pbuf[i]=IIC_Read_Byte();
  IIC_Ack();
 }
 pbuf[i]=IIC_Read_Byte(); //写入最后一个字节，并作出无应答
 IIC_NAck();
 IIC_Stop();
 return 0;
}

/******************************************************************
 - 功能描述：将BCD码转换为十进制的数值
 - 隶属模块：PCF8563驱动模块
 - 函数属性：内部
 - 参数说明：x:待转换的BCD码字节          
 - 返回说明：转换后的值
 - 注：将BCD格式数据转为实际的值，如29的BCD格式为0x29，实际值为0x1d
 ******************************************************************/

unsigned char BCD2Val(unsigned char x)
{
 return (x>>4)*10+(x&0x0f); //高4位乘以10，再加上低4位，即得到数值
}

/******************************************************************
 - 功能描述：将十进制的数值转换为BCD码
 - 隶属模块：PCF8563驱动模块
 - 函数属性：内部
 - 参数说明：x:待转换的数值         
 - 返回说明：转换后的值
 - 注：将值转为BCD格式，如 23转为BCD格式为 0x23
 ******************************************************************/

unsigned char Val2BCD(unsigned char x)
{
 return (x/10)*16+(x%10); //将十进制的数值十位乘以16，再加上个位，即得到BCD码
}

/******************************************************************
 - 功能描述：读取时间
 - 隶属模块：PCF8563驱动模块
 - 函数属性：外部，供用户使用
 - 参数说明：无        
 - 返回说明：操作结果，0表示成功，1表示失败
 - 注：从PCF8563中读到的时间值，被装载到全局的外部结构体变量time中
 ******************************************************************/

unsigned char P8563_Read_Time()
{ 
 unsigned char temp[7];
 if(!PCF8563_Read_Bytes(0x02,7,temp)) //读取时间，即读取PCF8563的时间寄存器，地址从0x02开始
 {
  //以下对读取到temp数组中的时间数据进行截取
  //并转换为十进制数值写入到time中去
  time.second=BCD2Val(temp[0]&0x7f); //秒
  time.minute=BCD2Val(temp[1]&0x7f); //分
  time.hour  =BCD2Val(temp[2]&0x3f); //小时
  time.day   =BCD2Val(temp[3]&0x3f); //日
  time.week  =BCD2Val(temp[4]&0x07); //星期
  time.month =BCD2Val(temp[5]&0x1f); //月
  time.year  =BCD2Val(temp[6]     ); //年
  return 0;
 }
 else
 return 1;
}

/******************************************************************
 - 功能描述：设置时间
 - 隶属模块：PCF8563驱动模块
 - 函数属性：外部，供用户使用
 - 参数说明：无        
 - 返回说明：操作结果，0表示成功，1表示失败
 - 注：在设置时间前先将时间数据填充到time中去，随后调用此函数，时间
       数据即被写入到PCF8563中，并以新设置的时间继续走时
 ******************************************************************/

unsigned char P8563_Set_Time() 
{
 unsigned char temp[7];
 unsigned char i;
 for(i=0;i<7;i++)
 {
  temp[i]=Val2BCD(((unsigned char *)(&time))[i]);//将time中的时间数据转换为BCD格式，并写入到temp数组中
 }
 return PCF8563_Write_Bytes(0x02,7,temp); //将temp数组的数据写入到PCF8563中
}

/******************************************************************
 - 功能描述：设置倒计时寄存器
 - 隶属模块：PCF8563驱动模块
 - 函数属性：外部，供用户使用
 - 参数说明：无        
 - 返回说明：操作结果，0表示成功，1表示失败
 - 注：先将要写入到倒计时寄存器的数据装入全局外部结构体变量dcounter中
       随后调动此函数将数据写入
 ******************************************************************/

unsigned char P8563_Set_DownCounter() 
{
 return PCF8563_Write_Bytes(0x0e,2,(unsigned char *)&dcounter); 
}

/******************************************************************
 - 功能描述：读取倒计时寄存器
 - 隶属模块：PCF8563驱动模块
 - 函数属性：外部，供用户使用
 - 参数说明：无        
 - 返回说明：操作结果，0表示成功，1表示失败
 - 注：将倒计时寄存器的值读回到dcounter中
 ******************************************************************/

unsigned char P8563_Read_DownCounter() 
{
 return PCF8563_Read_Bytes(0x0e,2,(unsigned char *)&dcounter); 
}
