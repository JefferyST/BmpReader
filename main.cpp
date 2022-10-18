#include<iostream>
#include"BmpReader.h"
using namespace std;

int main() {
	BmpReader readBmp;
	readBmp.read("test.bmp");
	readBmp.showFileHeader();
	readBmp.showImgHeader();
	readBmp.write("test2.bmp");
	
}