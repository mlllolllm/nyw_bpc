// archive.h: interface for the CSgArchive class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(SG_ARCHIVE_H_)
#define SG_ARCHIVE_H_
#include "sgconst.h"
#include <stdio.h>
#include "sgnp_export.h"

//##ModelId=44040D36034D
class SGNP_Export CSgFile
{
public:
	//##ModelId=44040D360372
	CSgFile();
public:
	//##ModelId=44040D360370
	virtual ~CSgFile();
	//##ModelId=44040D36036E
	virtual SG_INT	GetPosition() const;
	//##ModelId=44040D36036A
	virtual SG_BOOL Open(const SG_STRING lpszFileName,const SG_STRING openMode);
	//##ModelId=44040D360366
	virtual SG_UINT Read(void* lpBuf, SG_UINT nCount);
	//##ModelId=44040D360362
	virtual SG_UINT Write(const void* lpBuf, SG_UINT nCount);
	//##ModelId=44040D36035E
	virtual SG_INT Seek(SG_INT lOff, SG_UINT nFrom);
	//##ModelId=44040D36035C
	virtual SG_INT Flush();
	//##ModelId=44040D36035A
	virtual SG_INT Close();
	//##ModelId=44040D360358
	virtual SG_BOOL IsMemFile(){ return false;}
	//
	//##ModelId=44040D360352
	SG_INT WriteString(const SG_CHAR* lpsz);
	//##ModelId=44040D36034F
	SG_CHAR*ReadString(SG_CHAR* lpsz, SG_UINT nMax);
	//
	//##ModelId=44040D36034E
	FILE* m_pStream; 
};

//##ModelId=44040D300087
class SGNP_Export CSgMemFile:public CSgFile 
{
public:
// Constructors
	//##ModelId=44040D3000E0
	CSgMemFile(SG_UINT nGrowBytes = 4096,SG_BOOL bAutoDelete=true);
	//##ModelId=44040D3000E3
	CSgMemFile(SG_UCHAR* lpBuffer, SG_UINT nBufferSize, SG_UINT nGrowBytes = 0);
	//##ModelId=44040D3000E7
	CSgMemFile(SG_CHAR* lpBuffer, SG_UINT nBufferSize, SG_UINT nGrowBytes = 0);
// Operations
	//##ModelId=44040D3000DC
	void Attach(SG_UCHAR* lpBuffer, SG_UINT nBufferSize, SG_UINT nGrowBytes = 0);
	//##ModelId=44040D3000DB
	SG_UCHAR* Detach();
	//##ModelId=44040D3000D9
	virtual SG_BOOL IsMemFile(){ return true;}
	//
	SG_BOOL IsOutMemory(){ return m_bOutMemory; }
	void OutMemory(SG_BOOL b) { m_bOutMemory = b;}
// Advanced Overridables
protected:
	//##ModelId=44040D3000D6
	virtual SG_UCHAR* Alloc(SG_UINT nBytes);
	//##ModelId=44040D3000D2
	virtual SG_UCHAR* Realloc(SG_UCHAR* lpMem, SG_UINT nBytes);
	//virtual SG_UCHAR* Memcpy(SG_UCHAR* lpMemTarget, const SG_UCHAR* lpMemSource, SG_UINT nBytes);
	//##ModelId=44040D3000CF
	virtual void FreeMem(SG_UCHAR* lpMem);
	//##ModelId=44040D3000CC
	virtual void GrowFile(SG_UINT dwNewLen);

// Implementation
protected:
	//##ModelId=44040D3000AD
	SG_UINT m_nGrowBytes;
	//##ModelId=44040D3000A8
	SG_INT m_nPosition;
	//##ModelId=44040D3000A3
	SG_UINT m_nBufferSize;
	//##ModelId=44040D30009E
	SG_UINT m_nFileSize;
	//##ModelId=44040D300099
	SG_UCHAR* m_lpBuffer;
	//##ModelId=44040D300094
	SG_BOOL m_bAutoDelete;
	//
	SG_BOOL m_bOutMemory;	//是否内存不足

public:
	//##ModelId=44040D3000CB
	SG_UINT GetGrowBytes(){return m_nGrowBytes;}
	//##ModelId=44040D3000C9
	virtual ~CSgMemFile();
	//##ModelId=44040D3000C7
	void SetLength(SG_UINT dwNewLen);
	//##ModelId=44040D3000C6
	SG_UINT GetLength(){return m_nFileSize;}
	//##ModelId=44040D3000C5
	void*GetBufferPtr(){return m_lpBuffer;}
	//##ModelId=44040D3000C4
	SG_UINT GetBufferLength(){ return m_nBufferSize; }
	//##ModelId=44040D3000C2
	virtual SG_INT GetPosition() const;
	//##ModelId=44040D3000BE
	virtual SG_UINT Read(void* lpBuf, SG_UINT nCount);
	//##ModelId=44040D3000BA
	virtual SG_UINT Write(const void* lpBuf, SG_UINT nCount);
	//##ModelId=44040D3000B6
	virtual SG_INT Seek(SG_INT lOff, SG_UINT nFrom);
	//##ModelId=44040D3000B4
	virtual SG_INT Flush(){ return 0; };
	//##ModelId=44040D3000B2
	virtual SG_INT Close();
	//##ModelId=44040D3000B0
	void AutoDelete(SG_BOOL b) { m_bAutoDelete = b; }
};

//##ModelId=44040D39003A
class SGNP_Export CSgArchive
{
public:
	enum  Mode{ load = 1,store = 2 };

	//##ModelId=44040D39009F
	CSgArchive(CSgFile* pFile, Mode nMode, SG_INT nBufSize = 4096);
	//##ModelId=44040D39009E
	 ~CSgArchive();
	//
	//##ModelId=44040D39009C
	SG_BOOL IsLoading() const{ return (m_nMode==load); }
	//##ModelId=44040D39009A
	SG_BOOL IsStoring() const{ return (m_nMode==store); }
	//##ModelId=44040D390098
	CSgFile* GetFile() const{ return m_pFile; }
	//##ModelId=44040D390095
	SG_UINT Read(void* lpBuf, SG_UINT nMax);
	//##ModelId=44040D390092
	void Write(const void* lpBuf, SG_UINT nMax);
	//##ModelId=44040D390091
	void Flush();
	//##ModelId=44040D390090
	void Close();
	//##ModelId=44040D39008F
	void Abort(); 
	//##ModelId=44040D39008D
	void FillBuffer(SG_UINT nBytesNeeded);
	//##ModelId=44040D39008B
	void WriteString(const SG_CHAR* lpsz);
	//外部分配空间,nMax应包括结束符
	//##ModelId=44040D390086
	SG_CHAR* ReadString(SG_CHAR* lpsz, SG_UINT nMax);
	//注意，内部分配空间，外部释放delete[] rString;
	//##ModelId=44040D390089
	SG_BOOL ReadString(SG_CHAR*& rString);
	SG_BOOL GetSerializeErr()
	{
		return m_SerializeErr;
	};
	SG_INT GetCurPos()
	{
		SG_INT Pos=m_lpBufCur-m_lpBufStart;
		if(Pos<0)
			Pos=0;
		return Pos;
	}
public:
	// insertion operations
	//##ModelId=44040D390072
	CSgArchive& operator<<(SG_FLOAT f);
	//##ModelId=44040D390074
	CSgArchive& operator<<(SG_DOUBLE d);
	//##ModelId=44040D390078
	CSgArchive& operator<<(SG_UINT u);
	//##ModelId=44040D39007A
	CSgArchive& operator<<(SG_USHORT uw);
	//##ModelId=44040D39007C
	CSgArchive& operator<<(SG_UCHAR uch);
	//##ModelId=44040D390080
	CSgArchive& operator<<(SG_INT i){return CSgArchive::operator <<((SG_UINT)i);}
	//##ModelId=44040D390082
	CSgArchive& operator<<(SG_SHORT w){return CSgArchive::operator<<((SG_USHORT)w);}
	//##ModelId=44040D390084
	CSgArchive& operator<<(SG_CHAR ch){return CSgArchive::operator <<((SG_UCHAR)ch);};
//#ifdef _USE_INT64_
	CSgArchive& operator<<(SG_UINT64 ul);
	CSgArchive& operator<<(SG_INT64 l){return CSgArchive::operator <<((SG_UINT64)l);}
	CSgArchive& operator>>(SG_UINT64&ul);
	CSgArchive& operator>>(SG_INT64&l){ return CSgArchive::operator>>((SG_UINT64&)l);}
//#endif
	// extraction operations
	//##ModelId=44040D39005E
	CSgArchive& operator>>(SG_FLOAT& f);
	//##ModelId=44040D390060
	CSgArchive& operator>>(SG_DOUBLE& d);
	//##ModelId=44040D390064
	CSgArchive& operator>>(SG_UINT&ul);
	//##ModelId=44040D390066
	CSgArchive& operator>>(SG_USHORT&ul);
	//##ModelId=44040D390068
	CSgArchive& operator>>(SG_UCHAR&uch);
	//##ModelId=44040D39006A
	CSgArchive& operator>>(SG_INT& i){ return CSgArchive::operator>>((SG_UINT&)i);}
	//##ModelId=44040D39006E
	CSgArchive& operator>>(SG_SHORT& w){ return CSgArchive::operator>>((SG_USHORT&)w); }
	//##ModelId=44040D390070
	CSgArchive& operator>>(SG_CHAR& ch)	{ return CSgArchive::operator>>((SG_UCHAR&)ch); }
// Implementation
protected:
	//禁止赋值和拷贝构造
	//##ModelId=44040D3900A3
	CSgArchive(const CSgArchive& arSrc);
	//##ModelId=44040D39005C
	void operator=(const CSgArchive& arSrc);
	//##ModelId=44040D390059
	Mode m_nMode;
	//##ModelId=44040D390056
	int m_nBufSize;
	//##ModelId=44040D390053
	CSgFile* m_pFile;
	//##ModelId=44040D39004E
	SG_UCHAR* m_lpBufCur;
	//##ModelId=44040D390049
	SG_UCHAR* m_lpBufMax;
	//##ModelId=44040D390044
	SG_UCHAR* m_lpBufStart;
	SG_BOOL m_SerializeErr;
};

//##ModelId=44040D2B008A
class SGNP_Export Stream_Serialization
{
public:

	//##ModelId=44040D2B00A3
	Stream_Serialization();
	//##ModelId=44040D2B00A1
	virtual ~Stream_Serialization();

	//##ModelId=44040D2B00A0
	CSgArchive& Archive() { return *m_pArchive; }
	//##ModelId=44040D2B009F
	CSgFile & GetFile() { return *m_pFile; }
	//##ModelId=44040D2B009E
	void End() { m_pArchive->Close(); }

protected:

	//##ModelId=44040D2B009B
	CSgArchive * m_pArchive;
	//##ModelId=44040D2B0096
	CSgFile    * m_pFile;

};

//##ModelId=44040D39036F
class SGNP_Export Net_Stream_Store : public Stream_Serialization
{
public:
	//##ModelId=44040D390373
	Net_Stream_Store(SG_BOOL bAutoDelete=true,SG_UINT nGrowBytes = 4096);
	//##ModelId=44040D390376
	Net_Stream_Store(SG_CHAR* lpBuffer, SG_UINT nBufferSize);
	//##ModelId=44040D390372
	SG_UINT	Length();
	//##ModelId=44040D390371
	char*	Buffer();
};

//##ModelId=44040D2B0085
class SGNP_Export Net_Stream_Load : public Stream_Serialization
{
public:
	//##ModelId=44040D2B0087
	Net_Stream_Load(SG_CHAR* lpBuffer, SG_UINT nBufferSize);
};
#endif 
