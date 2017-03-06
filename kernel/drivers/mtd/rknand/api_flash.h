/********************************************************************************
*********************************************************************************
			COPYRIGHT (c)   2004 BY ROCK-CHIP FUZHOU
				--  ALL RIGHTS RESERVED  --

File Name:  api_flash.h
Author:     XUESHAN LIN
Created:    1st Dec 2008
Modified:
Revision:   1.00
Modify log:
            1.01    增加FtlClose接口函数    2009.10.15  lxs
********************************************************************************
********************************************************************************/
#ifndef _API_FLASH_H
#define _API_FLASH_H

//1函数原型声明
/***************************************************************************
函数描述:FTL和FLASH初始化
入口参数:无
出口参数:
        0=正常返回 
        1=映射表出错, 被强制低格
        2=flash初始化失败,可能是硬件错误或要进行固件升级
        其它值:内部错误, 该驱动不可使用
说    明:上电只需调用一次初始化即可
***************************************************************************/
extern int FtlInit(unsigned int nandcBaseAddr,unsigned char pageRemapEn);
extern int FTLInit_WithoutPageRemap(void);
extern int FTLInit(void);


/***************************************************************************
函数描述:获取FLASH磁盘容量
入口参数:
        DISK_NAND_CODE:固件盘
        DISK_NAND_DATA:系统参数盘
        DISK_NAND_USER:用户盘
出口参数:磁盘总扇区数
说    明:
***************************************************************************/
extern unsigned int FtlGetCapacity(unsigned char LUN);

/***************************************************************************
函数描述:读扇区接口
入口参数:LUN=逻辑分区号, Index=起始扇区地址, buf=数据缓冲区, nSec=扇区数
出口参数:0=读取正确; 非0=读取出错, 数据不可用
调用函数:
说    明:
***************************************************************************/
extern int FtlRead(unsigned char LUN, unsigned int Index, unsigned int nSec, void *buf);

/***************************************************************************
函数描述:写扇区接口
入口参数:LUN=逻辑分区号, Index=起始扇区地址, buf=数据缓冲区, nSec=扇区数
出口参数:0=正确写入; 非0=写操作失败, 数据没有被正确写入
调用函数:
说    明:
***************************************************************************/
extern int FtlWrite(unsigned char LUN, unsigned int Index, unsigned int nSec, void *buf);

/***************************************************************************
函数描述:MLC FLASH数据刷新
入口参数:
出口参数:
调用函数:
说    明:在系统IDLE/在比较集中读数据时(如A-B播放、频繁读资源等)调用该函数, 
				 能及时修正被频繁集中读坏的数据,函数执行时间可能较长(几百ms甚至几s)
***************************************************************************/
extern	void    FlashRefreshHook(void);

/***************************************************************************
函数描述:AHB主频更新时需要调用此接口来配置FLASH时序
入口参数:AHBnKHz=主频(AHB)
出口参数:
调用函数:
***************************************************************************/
extern	void    FlashTimingCfg(unsigned int AHBnKHz);

/***************************************************************************
函数描述:FTL 关闭，关机时调用
入口参数:无
出口参数:无
说    明:关机时，在所有写文件操作结束后调用
***************************************************************************/
extern	void  FtlClose(void);

/***************************************************************************
函数描述:FTL 定时回调函数，系统1S左右调用一次
入口参数:无
出口参数:无
说    明:FTL中一些CACHE在定时中回写flash
***************************************************************************/
extern	void  FtlTimeHook(void);

/***************************************************************************
函数描述:获取 flash page 大小，以便外面开缓冲,
入口参数:无
出口参数:page大小，sector单位
调用函数:
说明: 需要在FTLInit后才可用
***************************************************************************/
extern	int   FlashGetPageSize(void);

/***************************************************************************
函数描述:AHB主频更新时需要调用此接口来配置FLASH时序
入口参数:AHBnMHz=主频(AHB)
出口参数:
调用函数:
***************************************************************************/
extern	void    FlashTimingCfg(unsigned int AHBnKHz);

/***************************************************************************
函数描述:系统盘写不允许
入口参数:
出口参数:
调用函数:
***************************************************************************/
extern void FtlFlashSysProtSetOn(void);

/***************************************************************************
函数描述:系统盘写允许
入口参数:
出口参数:
调用函数:
***************************************************************************/
extern void FtlFlashSysProtSetOff(void);

/***************************************************************************
函数描述:擦除系统盘，升级时使用
入口参数:
出口参数:
调用函数:
***************************************************************************/
extern void FtlLowFormatSysDisk(void);

extern int FtlWriteImage(unsigned int Index, unsigned int nSec, void *buf);
/***************************************************************************
函数描述:将所有缓存的cache 写到cache 块
入口参数:
出口参数:
调用函数:
***************************************************************************/
extern void	FtlCacheDelayWriteALL(void);

/***************************************************************************
函数描述:设置磁盘写保护地址，
入口参数:LBA地址，小于LBA的地址写保护
出口参数:
调用函数:
***************************************************************************/
void FtlSetSysProtAddr(int LBA);


/***************************************************************************
函数描述:获取FLASH磁盘容量
入口参数:盘符
出口参数:容量,以扇区为单位
调用函数:
***************************************************************************/
int FtlGetPageZoneCapacity(void);

/***************************************************************************
函数描述:读多扇区
入口参数:Index=扇区号, nSec=扇区数
出口参数:读到的数据在缓冲区buf中
调用函数:
***************************************************************************/
int FtlPageWrite(int Index, int nSec, void *buf);


/***************************************************************************
函数描述:读多扇区
入口参数:Index=扇区号, nSec=扇区数
出口参数:读到的数据在缓冲区buf中
调用函数:
***************************************************************************/
int FtlPageRead(int Index, int nSec, void *buf);


/***************************************************************************
函数描述:读取 SN sector信息
入口参数:pbuf
出口参数:
调用函数:
注意信息：需要在FTLInit后才能调用，pbuf大小需要大于等于512 bytes，返回信息为512
          bytes。
***************************************************************************/
char GetSNSectorInfo(char * pbuf);


extern int NandInit(void);
extern int NandRead(unsigned int Index, unsigned int nSec, void * buf) ;
extern int NandWriteImage(unsigned int Index, unsigned int nSec, void * buf);
extern int NandWrite(unsigned int Index, unsigned int nSec, void * buf) ;
extern int NandDeInit(void) ;
extern int NandForceDeInit(void);
extern unsigned int NandGetCapacity(void); 
extern void NandSetSysProtAddr(unsigned int SysImageWriteEndAdd);
extern void FtlDelayWriteCacheEn(unsigned int en);
#endif
