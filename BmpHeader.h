#pragma once
#include"Utils.h"

#pragma pack(2)


typedef struct BmpFileHeader
{
	BYTE bfType[2];		//"BM"
	DWORD bfSize;		//��С
	WORD bfReserved1;	//������
	WORD bfReserved2;	//������
	DWORD bfOffBits;	//ƫ���ֽ�
} BitMapFileHeader;

typedef struct BmpInfoHeader
{
	DWORD biSize;           //λͼ��Ϣͷ��С
	LONG biWidth;           // ͼ��Ŀ�
	LONG biHeight;          // ͼ��ĸ�
	WORD biPlanes;		    // ��ʾbmpͼƬ��ƽ��������Ȼ��ʾ��ֻ��һ��ƽ�棬���Ժ����1
	WORD biBitCount;        // һ������ռ��λ������biBitCount=24ʱ����BMPͼ�����24Bit���ͼ��û�е�ɫ����
	DWORD biCompression;    // ˵��ͼ������ѹ�������ͣ�0Ϊ��ѹ����
	DWORD biSizeImage;      // ����������ռ��С, ���ֵӦ�õ���(biSize-bfOffBits)��ֵ
	LONG biXPelsPerMeter;   // ˮƽ�ֱ��ʣ�������/�ױ�ʾ��һ��Ϊ0
	LONG biYPelsPerMeter;   // ��ֱ�ֱ��ʣ�������/�ױ�ʾ��һ��Ϊ0
	DWORD biClrUsed;        // λͼʵ��ʹ�õĲ�ɫ���е���ɫ������
	DWORD biClrImportant;   // ��ͼ����ʾ����ҪӰ�����ɫ��������Ŀ�������0����ʾ����Ҫ
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



