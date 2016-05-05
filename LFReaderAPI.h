/*
********************************************************************************
*一台机器最多可以连接10个读写器
********************************************************************************
*/
#ifndef _LF_READER_API_H_  
#define _LF_READER_API_H_ 

#define LED_OFF    0
#define LED_RED    1
#define LED_GREEN  2

#if defined DLL_EXPORT   
	#define DECLDIR __declspec(dllexport)
#else   
	#define DECLDIR __declspec(dllimport) 
#endif


#include <atlstr.h>


extern "C" 
{   
/*
********************************************************************************
*设置读写器函数
********************************************************************************
*/

//连接读写器
//参数：port->串口号，例："com1"
//      baud->波特率，读卡器上电为38400
//      addr->读卡器地址，这个数值由程序员指定，相当于给读卡器一个身份标识，范围0~9，
//            缺省为0，如果你的程序只操作一个读写器，建议采用缺省值；
//返回：成功true，失败返回false
DECLDIR BOOL gOpenReader(char *port, DWORD baud, int addr=0); 


//断开连接
//参数：addr->读卡器地址，必须与 gOpenReader 函数的保持一致；
//            缺省为0，如果你的程序只操作一个读写器，建议采用缺省值；
//成功返回true，失败返回false
DECLDIR BOOL gCloseReader(int addr=0);


//设置等待读写器返回数据的时间
//参数：time->等待时间，单位ms，默认是1024ms
//      addr->读卡器地址，必须与 gOpenReader 函数的保持一致；
//            缺省为0，如果你的程序只操作一个读写器，建议采用缺省值；
//成功返回true，失败返回false
DECLDIR BOOL gSetTimeOut(int time, int addr=0);


//设置读写器波特率
//参数：baud->标准波特率
//      addr->读卡器地址，必须与 gOpenReader 函数的保持一致；
//            缺省为0，如果你的程序只操作一个读写器，建议采用缺省值；
//成功返回0，失败返回非零，通信失败返回0x0B
DECLDIR int gSetBaud(DWORD baud, int addr=0);



//获取读写器型号
//参数：model->返回读写器型号
//      len  ->返回型号长度
//      addr ->读卡器地址，必须与 gOpenReader 函数的保持一致；
//             缺省为0，如果你的程序只操作一个读写器，建议采用缺省值；
//成功返回0，失败返回非零，串口通信失败返回0x0B
DECLDIR int gGetModel(BYTE *model, int *len, int addr=0);


//设置蜂鸣
//参数：time->蜂鸣时间，单位5MS
//      addr->读卡器地址，必须与 gOpenReader 函数的保持一致；
//            缺省为0，如果你的程序只操作一个读写器，建议采用缺省值；
//成功返回0，失败返回非0，通信失败返回0x0B
DECLDIR int gSetBeep(BYTE time, int addr=0);


//设置LED颜色
//参数：color->0x00 = 熄灭
//             0x01 = 红色
//             0x02 = 绿色
//      addr->读卡器地址，必须与 gOpenReader 函数的保持一致；
//            缺省为0，如果你的程序只操作一个读写器，建议采用缺省值；
//成功返回0，失败返回非零，通信失败返回0x0B
DECLDIR int gSetLED(BYTE color, int addr=0);


//设置读写器状态
//参数：mode->0为休眠，非零为唤醒
//      addr->读卡器地址，必须与 gOpenReader 函数的保持一致；
//            缺省为0，如果你的程序只操作一个读写器，建议采用缺省值；
//成功返回0，失败返回非零，通信失败返回0x0B
DECLDIR int gSetPower(BYTE mode, int addr=0);



//检测卡片是不是低频卡
//参数：msg->返回卡片通信波特率，这只是一个参考值
//     addr->读卡器地址，必须与 gOpenReader 函数的保持一致；
//           缺省为0，如果你的程序只操作一个读写器，建议采用缺省值；
//低频卡返回0，非低频卡返回非零，通信失败返回0x0B
DECLDIR int gIsLFCard(CString *msg, int addr=0);


//读FDX_A卡
//参数：ID ->返回卡号，5 BYTES
//      addr->读卡器地址，必须与 gOpenReader 函数的保持一致；
//            缺省为0，如果你的程序只操作一个读写器，建议采用缺省值；
//读卡成功返回0，读卡失败返回1，通信失败返回0x0B
DECLDIR int gReadFDXA(BYTE *ID, int addr=0);


//读FDX_B（ISO11784/85）卡
//参数：nation ->返回国内代码，5 BYTES
//      country->返回国家代码，2 BYTES
//      trailer->返回用户自定义数据 3 BYTES
//      addr->读卡器地址，必须与 gOpenReader 函数的保持一致；
//            缺省为0，如果你的程序只操作一个读写器，建议采用缺省值；
//读卡成功返回0，读卡失败返回非零，通信失败返回0x0B
DECLDIR int gReadFDXB(BYTE *nation, BYTE *country, BYTE *trailer, int addr=0);


//读ID卡
//参数：ID ->返回卡号，5 BYTES
//      addr->读卡器地址，必须与 gOpenReader 函数的保持一致；
//            缺省为0，如果你的程序只操作一个读写器，建议采用缺省值；
//读卡成功返回0，读卡失败返回非零，通信失败返回0x0B
DECLDIR int gReadIDCard(BYTE *ID, int addr=0);


//HID奇偶检验
//data_in->输入校验数据
//data_len->校验数据长度
//start_mask->起始字节有效位
//end_mask->末尾字节有效位
//奇返回1，偶返回0
DECLDIR BYTE HID_Parity(BYTE *data_in, int data_len, BYTE start_mask, BYTE end_mask);


//读HID卡
//参数：hid ->返回卡号，6 BYTES
//      addr->读卡器地址，必须与 gOpenReader 函数的保持一致；
//            缺省为0，如果你的程序只操作一个读写器，建议采用缺省值；
//通信失败返回0x0B，读卡成功返回0，否则表示读卡失败
DECLDIR int gReadHID(BYTE *hid, int addr=0);


//读EEPROM
//参数：data_out->返回卡号，最大为64 BYTES
//      addr       ->读卡器地址，必须与 gOpenReader 函数的保持一致；
//                   缺省为0，如果你的程序只操作一个读写器，建议采用缺省值；
//返回读取到的数据长度
DECLDIR int gReadEEPROM(BYTE *data_out, int addr=0);


//写EEPROM，此操作将直接覆盖EEPROM原来的数据，无法恢复
//参数：data_in->EEPROM数据
//      len    ->EEPROM数据长度，最长为64 bytes
//      addr   ->读卡器地址，必须与 gOpenReader 函数的保持一致；
//               缺省为0，如果你的程序只操作一个读写器，建议采用缺省值；
//写成功放回0，否则返回非零，通信失败返回0x0B
DECLDIR int gWriteEEPROM(BYTE *data_in, BYTE len, int addr=0);


//直通函数，直接向读卡器发送读卡器指令
//参数：cmd     ->数据包命令
//      para    ->数据包参数
//      para_len->数据包参数长度
//      resp    ->返回数据包数据
//      resp_len->返回数据包数据长度
//      addr->读卡器地址，必须与 gOpenReader 函数的保持一致；
//            缺省为0，如果你的程序只操作一个读写器，建议采用缺省值；
//操作成功返回0，操作失败返回非0，通信失败返回0x0B
DECLDIR int gDirecteAccess(WORD cmd, BYTE *para, int para_len, BYTE *resp, int *resp_len, int addr=0);


/*
********************************************************************************
*ATA5567指令
********************************************************************************
*/

//写T5557卡
//参数：page      ->页地址，范围0~1
//      block     ->块地址，范围0~7，block 0为卡片配置块
//      lock      ->0x00 = 不固化
//                  0x01 = 固化，固化之后数据不能再修改
//      block_data->待写入数据，4 BYTES
//      addr      ->读卡器地址，必须与 gOpenReader 函数的保持一致；
//                  缺省为0，如果你的程序只操作一个读写器，建议采用缺省值；
//返回true表示与读写器通信成功，否则返回false，
//可以调用 T57_Read 函数验证是否写卡成功
DECLDIR BOOL T57_StandWrite(BYTE page, BYTE block, BYTE lock, BYTE *block_data, int addr=0);


//写卡，密码卡要调用这个函数来写卡
//参数：page      ->页地址，范围0~1
//      block     ->块地址，范围0~7，block 0为卡片配置块
//      lock      ->0x00 = 不固化
//                  0x01 = 固化，固化之后数据不能再修改
//      block_data->待写入数据，4 BYTES
//      password  ->卡片密码，4BYTES，即块7的数据
//      addr      ->读卡器地址，必须与 gOpenReader 函数的保持一致；
//                  缺省为0，如果你的程序只操作一个读写器，建议采用缺省值；
//返回true表示与读写器通信成功，否则返回false，
//可以调用 T57_Read 函数验证是否写卡成功
DECLDIR BOOL T57_ProteWrite(BYTE page, BYTE block, BYTE lock, BYTE *block_data, BYTE* password, int addr=0);


//唤醒卡片，设置了AOR和密码位之后需要用这个这个函数
//参数：password  ->卡片密码
//      addr      ->读卡器地址，必须与 gOpenReader 函数的保持一致；
//                  缺省为0，如果你的程序只操作一个读写器，建议采用缺省值；
//返回true表示与读写器通信成功，否则返回false，
//可以调用 T57_Read 函数验证是否写卡成功
DECLDIR BOOL T57_WakeUp(BYTE *password, int addr=0);


//设置卡片返回某个地址的数据
//参数：page      ->页地址，范围0~1
//      block     ->块地址，范围0~7，block 0为卡片配置块
//      addr ->读卡器地址，必须与 gOpenReader 函数的保持一致；
//             缺省为0，如果你的程序只操作一个读写器，建议采用缺省值；
//返回true表示与读写器通信成功，否则返回false，
//可以调用 T57_Read 函数验证是否写卡成功
DECLDIR BOOL T57_Access(BYTE page, BYTE block, int addr=0);


//设置卡片返回某个地址的数据，有密码的卡片需要这个这个函数
//参数：page      ->页地址，范围0~1
//      block     ->块地址，范围0~7，block 0为卡片配置块
//      password  ->卡片密码，4 BYTES，即块7的数据
//      addr      ->读卡器地址，必须与 gOpenReader 函数的保持一致；
//                  缺省为0，如果你的程序只操作一个读写器，建议采用缺省值；
//返回true表示与读写器通信成功，否则返回false，
//可以调用 T57_Read 函数验证是否写卡成功
DECLDIR BOOL T57_AccessPWD(BYTE page, BYTE block, BYTE* password, int addr=0);


//设置卡片返回指定页的数据
//参数：page->页地址，范围0~1
//      addr->读卡器地址，必须与 gOpenReader 函数的保持一致；
//            缺省为0，如果你的程序只操作一个读写器，建议采用缺省值；
//返回true表示与读写器通信成功，否则返回false，
//可以调用 T57_Read 函数验证是否写卡成功
DECLDIR BOOL T57_SelectPage(BYTE page, int addr=0);


//复位卡片
//参数：addr ->读卡器地址，必须与 gOpenReader 函数的保持一致；
//             缺省为0，如果你的程序只操作一个读写器，建议采用缺省值；
//返回true表示与读写器通信成功，否则返回false，
//可以调用 T57Read 函数验证是否写卡成功
DECLDIR BOOL T57_Reset(int addr=0);


//读卡Manchester RF/16
//参数：data_card->返回卡片数据
//      data_len ->返回卡片数据长度，最长为28 BYTES
//      addr     ->读卡器地址，必须与 gOpenReader 函数的保持一致；
//                 缺省为0，如果你的程序只操作一个读写器，建议采用缺省值；
//读卡成功返回0，读卡失败返回非0，通信失败返回0x0B
DECLDIR int T57_ReadCardRF16(BYTE *data_card, int *data_len, int addr=0);



//读卡Manchester RF/32
//参数：data_card->返回卡片数据
//      data_len ->返回卡片数据长度，最长为28 BYTES
//      addr     ->读卡器地址，必须与 gOpenReader 函数的保持一致；
//                 缺省为0，如果你的程序只操作一个读写器，建议采用缺省值；
//读卡成功返回0，读卡失败返回非0，通信失败返回0x0B
DECLDIR int T57_ReadCardRF32(BYTE *data_card, int *data_len, int addr=0);


//读卡Manchester RF/64
//参数：data_card->返回卡片数据
//      data_len ->返回卡片数据长度，最长为28 BYTES
//      addr     ->读卡器地址，必须与 gOpenReader 函数的保持一致；
//                 缺省为0，如果你的程序只操作一个读写器，建议采用缺省值；
//读卡成功返回0，读卡失败返回非0，通信失败返回0x0B
DECLDIR int T57_ReadCardRF64(BYTE *data_card, int *data_len, int addr=0);


//清空T57卡
//参数：password  ->卡片密码
//      addr      ->读卡器地址，必须与 gOpenReader 函数的保持一致；
//                  缺省为0，如果你的程序只操作一个读写器，建议采用缺省值；
//成功返回0，失败返回1，通信失败返回0x0B
DECLDIR int T57_InitCard(BYTE *password, int addr=0);


//把 T5557 格式化成 FDX_A 卡
//参数：lock->1为锁卡，否则不锁
//      ID  ->FDX_A卡号，5 BYTES，后7位有效
//      lock_pwd->锁卡密码
//      addr->读卡器地址，必须与 gOpenReader 函数的保持一致；
//            缺省为0，如果你的程序只操作一个读写器，建议采用缺省值；
//成功返回0，失败返回非0，通信失败返回0x0B
DECLDIR int T57_WriteFDXA(BYTE lock, BYTE *ID, BYTE *lock_pwd, int addr=0);


//把 T5557 格式化成 HID 卡
//参数：hid  ->HID卡号，6 BYTES
//      lock ->1为锁卡，否则不锁
//      lock_pwd ->锁卡密码，4 bytes
//      addr->读卡器地址，必须与 gOpenReader 函数的保持一致；
//            缺省为0，如果你的程序只操作一个读写器，建议采用缺省值；
//成功返回0，否则返回非零，通信失败返回0x0B
DECLDIR int T57_WriteHID(BYTE *hid, BYTE lock, BYTE *lock_pwd, int addr=0);


//把 T5557 格式化成 FDX_B 卡
//参数：nation ->返回国内代码，38 bits
//      country->返回国家代码，10 bits
//      trailer->返回用户自定义数据 3 BYTES
//      lock->锁卡，1为加密，把卡片加密，使得他人无法修改ID卡号
//      lock_pw->4 BYTES锁卡密码
//      addr   ->读卡器地址，必须与 gOpenReader 函数的保持一致；
//               缺省为0，如果你的程序只操作一个读写器，建议采用缺省值；
//成功返回0，否则返回非零，通信失败返回0x0B
DECLDIR int T57_WriteFDXB(BYTE *nation, BYTE *country, BYTE *trailer, BYTE lock, BYTE *lock_pw, int addr=0);


//把 T5557 格式化成 ID 卡
//参数：ID  ->ID号，5 BYTES
//      lock->锁卡，0为不加密，1为加密，把卡片加密，使得他人无法修改ID卡号
//      lock_pw->4 BYTES卡片的新密码,假如lock=0，卡片的新密码为{0,0,0,0}，否则为new_pw
//      addr->读卡器地址，必须与 gOpenReader 函数的保持一致；
//            缺省为0，如果你的程序只操作一个读写器，建议采用缺省值；
//成功返回0，否则返回非零，通信失败返回0x0B
DECLDIR int T57_WriteIDCard(BYTE *ID, BYTE lock, BYTE *lock_pw, int addr=0);


/*
********************************************************************************
*EM4305指令
********************************************************************************
*/

//写EM4305
//参数：word_addr->指定卡片地址
//      word_data->待写入卡片数据，4 bytes
//      addr   ->读卡器地址，必须与 gOpenReader 函数的保持一致；
//               缺省为0，如果你的程序只操作一个读写器，建议采用缺省值；
//返回0写卡成功，返回1写卡失败，返回0x0B读写串口失败
DECLDIR int EM_WriteWord(BYTE word_addr, BYTE *word_data, int addr=0);


//读EM4305
//参数：word_addr->指定卡片地址
//      word_data->返回卡片数据，4 bytes
//      addr   ->读卡器地址，必须与 gOpenReader 函数的保持一致；
//               缺省为0，如果你的程序只操作一个读写器，建议采用缺省值；
//返回0读卡成功，返回1读卡失败，返回0x0B读写串口失败
DECLDIR int EM_ReadWord(BYTE word_addr, BYTE *word_data, int addr=0);


//验证EM4305密码
//参数：password->4 bytes卡片密码
//      addr   ->读卡器地址，必须与 gOpenReader 函数的保持一致；
//               缺省为0，如果你的程序只操作一个读写器，建议采用缺省值；
//返回0密码正确，返回1密码错误，返回0x0B读写串口失败
DECLDIR int EM_Login(BYTE *password, int addr=0);


//锁定卡片指定数据块
//参数：array_addr->卡片地址数组，指定待锁定块的地址
//      array_size->卡片地址数组长度，指定锁定块数量
//      addr   ->读卡器地址，必须与 gOpenReader 函数的保持一致；
//               缺省为0，如果你的程序只操作一个读写器，建议采用缺省值；
//备注：一旦这些块锁定之后，就不能再解锁
//返回0锁卡成功，返回1锁卡失败，返回0x0B读写串口失败，返回3表示锁定块地址错误
DECLDIR int EM_Protect(BYTE *array_addr, int array_size, int addr=0);

//休眠卡片
//参数：addr   ->读卡器地址，必须与 gOpenReader 函数的保持一致；
//               缺省为0，如果你的程序只操作一个读写器，建议采用缺省值；
//返回0休眠成功，返回1休眠失败，返回0x0B读写串口失败
DECLDIR int EM_Disable(int addr=0);


//设置EM卡类型
//参数：mode-> 0 = Manchester RF/64
//             1 = Manchester RF/32
//             2 = Bi-phase RF/32
//      addr->读卡器地址，必须与 gOpenReader 函数的保持一致；
//            缺省为0，如果你的程序只操作一个读写器，建议采用缺省值；
//返回0休眠成功，返回1休眠失败，返回0x0B读写串口失败
DECLDIR int EM_SetCardMode(BYTE mode, int addr=0);

//把 EM4305 格式化成 FDX_B 卡
//参数：nation ->返回国内代码，38 bits
//      country->返回国家代码，10 bits
//      trailer->返回用户自定义数据 3 BYTES
//      lock->锁卡，0为不加密，1为加密，把卡片加密，使得他人无法修改ID卡号
//      lock_pw->4 BYTES锁卡密码
//      addr   ->读卡器地址，必须与 gOpenReader 函数的保持一致；
//               缺省为0，如果你的程序只操作一个读写器，建议采用缺省值；
//返回0写卡成功，返回1写卡失败，返回0x0B读写串口失败
DECLDIR int EM_WriteFDXB(BYTE *nation, BYTE *country, BYTE *trailer, BYTE lock, BYTE *lock_pw, int addr=0);


//把 EM4305 格式化成 ID 卡
//参数：ID  ->ID号，5 BYTES
//      lock->锁卡，0为不加密，1为加密，把卡片加密，使得他人无法修改ID卡号
//      lock_pw->4 BYTES锁卡密码
//      addr->读卡器地址，必须与 gOpenReader 函数的保持一致；
//            缺省为0，如果你的程序只操作一个读写器，建议采用缺省值；
//返回0写卡成功，返回1写卡失败，返回0x0B读写串口失败
DECLDIR int EM_WriteIDCard(BYTE *ID, BYTE lock, BYTE *lock_pw, int addr=0);


/*
********************************************************************************
*读写Hitag S
*第一步Request，可以得到UID
*第二步Select(UID)，可以得到配置块的数据，即第一块
*第三步，读和写
*第四步，读写完之后Quiet
********************************************************************************
*/

/*
********************************************************************************
*Hitag S UID Request
*uid->输出UID，最多输出4个UID，即16 bytes
*uid_len->UID长度，最大为16 Bytes
*addr   ->读卡器地址，必须与 gOpenReader 函数的保持一致；
          缺省为0，如果你的程序只操作一个读写器，建议采用缺省值；
*返回0读卡成功，返回非0表示失败，串口失败返回0x0B
********************************************************************************
*/
DECLDIR int HTS_Request(BYTE *uid, int *uid_len, int addr=0);


/*
********************************************************************************
*Hitag S Select(UID)
*uid_in->输入UID，4 bytes
*con_out->输出Select返回的配置块数据，4 bytes
*addr   ->读卡器地址，必须与 gOpenReader 函数的保持一致；
          缺省为0，如果你的程序只操作一个读写器，建议采用缺省值；
*返回0读卡成功，返回非0表示失败，串口失败返回0x0B
********************************************************************************
*/
DECLDIR int HTS_Select(BYTE *uid_in, BYTE *con_out, int addr=0);


/*
********************************************************************************
*Hitag S Read page
*page_addr->输入页地址，从0开始，S32最大为0，S256最大为7，S2048最大为63
*data_out->输出数据，4 bytes
*addr   ->读卡器地址，必须与 gOpenReader 函数的保持一致；
          缺省为0，如果你的程序只操作一个读写器，建议采用缺省值；
*返回0读卡成功，返回非0表示失败，串口失败返回0x0B
********************************************************************************
*/
DECLDIR int HTS_Read(BYTE page_addr, BYTE *data_out, int addr=0);


/*
********************************************************************************
*Hitag S Write page
*page_addr->输入页地址，从0开始，S32最大为0，S256最大为7，S2048最大为63
*data_in->输入数据，4 bytes
*addr   ->读卡器地址，必须与 gOpenReader 函数的保持一致；
          缺省为0，如果你的程序只操作一个读写器，建议采用缺省值；
*返回0读卡成功，返回非0表示失败，串口失败返回0x0B
********************************************************************************
*/
DECLDIR int HTS_Write(BYTE page_addr, BYTE *data_in, int addr=0);


/*
********************************************************************************
*Hitag S Quiet
*addr   ->读卡器地址，必须与 gOpenReader 函数的保持一致；
          缺省为0，如果你的程序只操作一个读写器，建议采用缺省值；
*返回0读卡成功，返回非0表示失败，串口失败返回0x0B
********************************************************************************
*/
DECLDIR int HTS_Quiet(int addr=0);


//把 Hitag S 格式化成 FDX_B 卡
//参数：nation ->返回国内代码，38 bits
//      country->返回国家代码，10 bits
//      trailer->返回用户自定义数据 3 BYTES
//      lock->锁卡，0为不加密，1为加密，把卡片加密，使得他人无法修改ID卡号
//      addr   ->读卡器地址，必须与 gOpenReader 函数的保持一致；
//               缺省为0，如果你的程序只操作一个读写器，建议采用缺省值；
//返回0写卡成功，返回1写卡失败，返回0x0B读写串口失败
DECLDIR int HTS_WriteFDXB(BYTE *nation, BYTE *country, BYTE *trailer, BYTE lock, int addr=0);


//把 Hitag S 格式化成 ID 卡
//参数：ID  ->ID卡号，5 BYTES
//      lock->锁卡，0为不加密，1为加密，把卡片加密，使得他人无法修改ID卡号
//      addr->读卡器地址，必须与 gOpenReader 函数的保持一致；
//            缺省为0，如果你的程序只操作一个读写器，建议采用缺省值；
//返回0写卡成功，返回1写卡失败，返回0x0B读写串口失败
DECLDIR int HTS_WriteIDCard(BYTE *ID, BYTE lock, int addr=0);


}//end extern "C"


#endif  