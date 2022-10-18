#pragma once
#include"BmpHeader.h"
#include<stdio.h>
#include <stdlib.h>
#include<math.h>
class BmpReader
{
public:
	BmpFileHeader m_Bmpfileheader;
	BmpInfoHeader m_BmpInfoHeader;
	pBitMapInfo m_dibInfo;
	BitMapInfo m_BmpInfo;
	RGBQuad* Quad;
	unsigned char* m_BmpData;
	int m_nWidth;
	int m_nHeight;
	double m_nRealSize;
	int m_nPaletteSize;

public:
	BmpReader();
	~BmpReader();

	void read(const char* filename);
	void write(const char* filename);
	void showFileHeader();
	void showImgHeader();
};