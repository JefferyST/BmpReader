#pragma once
#include"Utils.h"

#pragma pack(2)


typedef struct BmpFileHeader
{
	BYTE bfType[2];		//"BM"
	DWORD bfSize;		//大小
	WORD bfReserved1;	//保留字
	WORD bfReserved2;	//保留字
	DWORD bfOffBits;	//偏移字节
} BitMapFileHeader;

typedef struct BmpInfoHeader
{
	DWORD biSize;           //位图信息头大小
	LONG biWidth;           // 图像的宽
	LONG biHeight;          // 图像的高
	WORD biPlanes;		    // 表示bmp图片的平面属，显然显示器只有一个平面，所以恒等于1
	WORD biBitCount;        // 一像素所占的位数，当biBitCount=24时，该BMP图像就是24Bit真彩图，没有调色板项
	DWORD biCompression;    // 说明图象数据压缩的类型，0为不压缩。
	DWORD biSizeImage;      // 像素数据所占大小, 这个值应该等于(biSize-bfOffBits)的值
	LONG biXPelsPerMeter;   // 水平分辨率，用象素/米表示。一般为0
	LONG biYPelsPerMeter;   // 垂直分辨率，用象素/米表示。一般为0
	DWORD biClrUsed;        // 位图实际使用的彩色表中的颜色索引数
	DWORD biClrImportant;   // 对图象显示有重要影响的颜色索引的数目，如果是0，表示都重要
}	BitMapInfoHeader;


typedef struct RGBQuad
{
	BYTE rgbBlue;
	BYTE rgbGreen;
	BYTE rgbRed;
	BYTE rgbReserved;
} RGBquad;

typedef struct tagBitMapInfo
{
	BitMapInfoHeader bminfoHeader;
	RGBquad bminfoColors[1];
} BitMapInfo, *pBitMapInfo;



