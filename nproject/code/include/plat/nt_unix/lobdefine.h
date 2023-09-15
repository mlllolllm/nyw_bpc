#ifndef __LOB_DEFINE__
#define __LOB_DEFINE__

#include "sgconst.h"
#include "csgdataset.h"

enum
{
    SG_LOB_SIMPLE = 1,
    SG_LOB_CLOB   = 112,                                 /* character lob */
    SG_LOB_BLOB   = 113,                                 /* binary lob */
    SG_LOB_BFILEE = 114,                                 /* binary file lob */
    SG_LOB_CFILEE = 115,                                 /* character file lob */
};

class CSgArchive;
class _DATASET_DLL_EXPORT_ CSgLobBlock 
{
public:
    CSgLobBlock();
    ~CSgLobBlock();
public:
    SG_INT   GetLength(){ return m_nLength; }
    SG_INT   GetLobType(){ return m_nLobType; }
    SG_INT   GetWarningLength() { return m_nWarningLen; }
    SG_BOOL  IsNull() { return (!m_pContent); }
    SG_BOOL  Append(const SG_CHAR*pContent,SG_INT nWholeLen,SG_INT nPieceLen);
    SG_BOOL  Serialize(CSgArchive&ar);
    SG_BOOL  Alloc(SG_UINT inlen,SG_BOOL bKeepMem=true);
    SG_CHAR* GetLobContent() { return m_pContent ; }
    const SG_CHAR* GetErrorInfo(){ return m_szError.GetSafeBuffer(); }
    void     SetErrorInfo(SG_CHAR*szError){ if(szError) m_szError=szError; }
    void     Flush();
    void     SetLength(SG_INT len){ m_nLength=len; }  //oci blob方式读时来赋值
public:
    SG_INT   m_nLobType;
protected:
    CSgString  m_szError;
    SG_CHAR* m_pContent;
    SG_UINT  m_nLength;
    SG_UINT  m_nAllocLen;
    static SG_UINT  m_nWarningLen;
    static SG_UINT  m_nForbidLen;
};


#endif