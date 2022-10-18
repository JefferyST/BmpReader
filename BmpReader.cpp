#include "BmpReader.h"

BmpReader::BmpReader()
{

}

BmpReader::~BmpReader()
{
	if (m_dibInfo != NULL) {
		delete[] m_dibInfo;
		m_dibInfo = NULL;
	}

	if (m_BmpData != NULL) {
		delete[] m_BmpData;
		m_BmpData = NULL;
	}

}

void BmpReader::showFileHeader() {
	printf("File Format: %c%c\n", m_Bmpfileheader.bfType[0], m_Bmpfileheader.bfType[1]);
	printf("Size: %d bytes\n", m_Bmpfileheader.bfSize);
	printf("Offset : %d\n", m_Bmpfileheader.bfOffBits);
}

void BmpReader::showImgHeader() {
	printf("\nSize of header: %d\n", m_BmpInfoHeader.biSize);
	printf("Width: %d\n", m_BmpInfoHeader.biWidth);
	printf("Height: %d\n", m_BmpInfoHeader.biHeight);
	printf("Color Planes: %d\n", m_BmpInfoHeader.biPlanes);
	printf("Bits per Pixel: %d\n", m_BmpInfoHeader.biBitCount);
	printf("Compression: %d\n", m_BmpInfoHeader.biCompression);
	printf("Image size: %d\n", m_BmpInfoHeader.biSizeImage);
	printf("Preffered resolution in pixels per meter (X-Y): %d-%d\n", m_BmpInfoHeader.biXPelsPerMeter, m_BmpInfoHeader.biYPelsPerMeter);
	printf("Number color map: %d\n", m_BmpInfoHeader.biClrUsed);
	printf("Number of significant colors: %d\n", m_BmpInfoHeader.biClrImportant);
}

void BmpReader::read(const char *filename) {

	int ret, cbHeaderSize;
	m_nPaletteSize = 0;

	FILE *fp = fopen(filename, "rb");
	if (fp == NULL) {
		printf("Can not open file.");
		exit(0);
	}
	
	ret = fread(&m_Bmpfileheader, 1, sizeof(BmpFileHeader), fp);
	if (m_Bmpfileheader.bfType[0] != 'B'&& m_Bmpfileheader.bfType[1] != 'M')
	{
		printf("Not a BMP file.");
		fclose(fp);
		exit(0);
	}

	ret =  fread(&m_BmpInfoHeader, 1, sizeof(BitMapInfoHeader), fp);
	switch (m_BmpInfoHeader.biBitCount) {					
	case 1:
		m_nPaletteSize = 2;
		break;
	case 4:
		m_nPaletteSize = 16;
		break;
	case 8:
		m_nPaletteSize = 256;
		break;
	case 24:
		m_nPaletteSize = 0; //256*3
		break;
	}
	
	cbHeaderSize = sizeof(BitMapInfoHeader) + m_nPaletteSize * sizeof(RGBquad);
	m_dibInfo = (BitMapInfo*) new char[cbHeaderSize];
	m_dibInfo->bminfoHeader = m_BmpInfoHeader;

	if (m_BmpInfoHeader.biSize != 40 || m_BmpInfoHeader.biCompression != 0 || m_BmpInfoHeader.biBitCount != 24) {
		printf("The file %s is not a 24bit BMP.", &filename);
		fclose(fp);
		exit(0);
	}

	m_nHeight = m_dibInfo->bminfoHeader.biHeight;
	m_nWidth = m_dibInfo->bminfoHeader.biWidth;

	if (m_nPaletteSize) {
		ret = fread(&(m_dibInfo->bminfoColors[0]), 1, m_nPaletteSize * sizeof(RGBquad), fp);
		if (ret != int(m_nPaletteSize * sizeof(RGBquad))) {
			delete[] m_dibInfo;
			m_dibInfo = NULL;
			fclose(fp);
			exit(0);
		}
		Quad = m_dibInfo->bminfoColors;
	}

	int bytesPerLine = ((m_nWidth * m_dibInfo->bminfoHeader.biBitCount + 31) / 32) * 4;
	int bytesLength = bytesPerLine * m_nHeight;
	m_nRealSize = bytesLength;
	m_BmpData = (BYTE*) new char[bytesLength];
	fseek(fp, m_Bmpfileheader.bfOffBits, SEEK_SET);
	ret = fread(m_BmpData, 1, bytesLength,  fp);
	if (ret != int(bytesLength)) {
		delete[] m_dibInfo;
		delete[] m_BmpData;
		m_dibInfo = NULL;
		m_BmpData = NULL;
	}
	fclose(fp);
}

void BmpReader::write(const char* bmpfile) {

	int ret;
	
	FILE* fp = fopen(bmpfile, "wb");

	if (fp == NULL) {
		printf("Save image failed.");
		exit(0);
	}

	ret = fwrite(&m_Bmpfileheader, 1, sizeof(BmpFileHeader), fp);
	if (ret != sizeof(BmpFileHeader)) {
		printf("Save BmpFileHeader Failed.\n");
		fclose(fp);
		exit(0);
	}

	ret = fwrite(&m_dibInfo->bminfoHeader, 1, sizeof(BmpInfoHeader), fp);
	if (ret != sizeof(BmpInfoHeader)) {
		printf("Save BmpInfoHeader Failed.\n");
		fclose(fp);
		exit(0);
	}

	ret = fwrite(m_BmpData, 1, m_nRealSize, fp);
	if (ret != m_nRealSize) {
		printf("Save BmpData Failed.\n");
		fclose(fp);
		exit(0);
	}

	fclose(fp);
}


