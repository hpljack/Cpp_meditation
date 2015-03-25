#pragma once
class test
{
public:
	test(void);
	~test(void);
};
/*
  struct DatiFileHeader {
    WCHAR tag[32];	
    byte   isCompressed;		// 是否已经被压缩了
    byte   reserved[3];
	  byte   colorBit;			// 图像的颜色位数 8，16，32
    byte   format;  // 0: bmp, 1: jpg
    byte   reserved2[2];
	  WCHAR  version[32];			// 数据文件的版本信息
  };

  struct DatiFileHeader_old {
	WCHAR  tag[32];
	byte   isCompressed;		// 是否已经被压缩了
	UINT   colorBit;			// 图像的颜色位数 8，16，32
	WCHAR  version[32];			// 数据文件的版本信息
};

void TestStructLength(); //测试结构体长度

*/

