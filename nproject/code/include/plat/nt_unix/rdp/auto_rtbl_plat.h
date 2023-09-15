#ifndef _HH_AUTO_RTBL_PLAT_HHH_ 
#define _HH_AUTO_RTBL_PLAT_HHH_ 
//¸ÃÍ·ÎÄ¼şÓÉ³ÌĞòcrthfile.exe×Ô¶¯Éú³É
//½»Á÷ÏßÂ·¶Î±í	
#include "dppclient.h"
#include "rdbmem.h"
typedef struct MODEL_ACLINE_SEGMENT
{ 
SG_INT64		ID;		//±àºÅ
char		NAME[128];		//ÃèÊö
char		ALIAS[100];		//±ğÃû
unsigned char		res0[4];
SG_INT64		BASE_VOLTAGE;		//»ù×¼µçÑ¹
SG_INT64		OF_LINE;		//ËùÊôÏßÂ·
float		R;		//µç×è
float		X;		//µç¿¹
float		BCH;		//³äµçµçÄÉ
float		R0;		//ÁãĞòµç×è
float		X0;		//ÁãĞòµç¿¹
float		B0CH;		//ÁãĞò³äµçµçÄÉ
char		LINE_MODEL[24];		//ÏßÂ·ĞÍºÅ
float		LENGTH;		//³¤£¨Ã×£©
float		MAX_AMP;		//×î´óµçÁ÷
int		POWER_STATE;		//´øµç×´Ì¬
int		TOPO_ISLAND;		//ÍØÆËµçÆøµººÅ
float		RATED_AMP;		//¶î¶¨µçÁ÷
float		B;		//µçÄÉ
float		G;		//µçµ¼
unsigned char		res1[4];
}MODEL_ACLINE_SEGMENT;
//´¢ÄÜ±í	
typedef struct MODEL_BATTERYENERGYSTORAGE
{ 
SG_INT64		ID;		//±àºÅ
char		name[64];		//Ãû³Æ
char		mRID[64];		//Éè±¸Î¨Ò»ID
SG_INT64		MenberOfLine;		//ËùÊôÀ¡Ïß
SG_INT64		MenberOfSubstation;		//ËùÊô±äµçÕ¾
float		SOCState;		//SOC×´Ì¬
float		SOCLimHigh;		//SOCÉÏÏŞ
float		SOCLimLow;		//SOCÏÂÏŞ
float		chargeRatio;		//³äµçÂÊ
float		dischargeRatio;		//·ÅµçÂÊ
char		PSRID[64];		//PSRID
unsigned char		res0[4];
SG_INT64		OF_FEEDER;		//ËùÊôÀ¡Ïß
SG_INT64		OF_SUBSTATION;		//ËùÊô±äµçÕ¾
double		RATED_P;		//¶î¶¨¹¦ÂÊ
double		RATED_S;		//¶î¶¨ÈİÁ¿
double		MAX_RATE;		//×î´ó±¶ÂÊ
double		MIN_RATE;		//×îĞ¡±¶ÂÊ
double		MAX_P;		//×î´óÓĞ¹¦
double		MIN_P;		//×îĞ¡ÓĞ¹¦
double		MAX_Q;		//×î´óÎŞ¹¦
double		MIN_Q;		//×î´óÎŞ¹¦
double		IPOWER_P;		//ÓĞ¹¦¹¦ÂÊ
double		IPOWER_Q;		//ÎŞ¹¦¹¦ÂÊ
double		IPOWER_U;		//µçÑ¹Öµ
double		IPOWER_I;		//µçÁ÷Öµ
unsigned char		OF_BASE_VOLTAGE;		//»ù×¼µçÑ¹
unsigned char		res1[7];
double		MPOWER_P;		//Á¿²âÓĞ¹¦¹¦ÂÊ
double		MPOWER_Q;		//Á¿²âÎŞ¹¦¹¦ÂÊ
}MODEL_BATTERYENERGYSTORAGE;
//¼ä¸ô±í	
typedef struct MODEL_BAY
{ 
SG_INT64		ID;		//±àºÅ
char		NAME[64];		//ÃèÊö
char		ALIAS[100];		//±ğÃû
unsigned char		res0[4];
SG_INT64		OF_SUBSTATION;		//³§Õ¾´úÂë
SG_INT64		OF_VOLT_LEVEL;		//ËùÊôµçÑ¹µÈ¼¶
SG_INT64		BAY_TYPE;		//ÀàĞÍ
}MODEL_BAY;
//¿ª¹Ø±í	
typedef struct MODEL_BREAKER
{ 
SG_INT64		ID;		//±àºÅ
char		NAME[128];		//ÃèÊö
char		ALIAS[32];		//±ğÃû
char		DISP_CODE[16];		//µ÷¶ÈºÅ
int		TYPE;		//ÀàĞÍ
unsigned char		res0[4];
SG_INT64		OF_SUBSTATION;		//ËùÊô³§Õ¾
SG_INT64		OF_VOLT_LEVEL;		//µçÑ¹µÈ¼¶
SG_INT64		OF_BAY;		//ËùÊô¼ä¸ô
SG_INT64		DIGITAL_ID;		//Ò£ĞÅID
unsigned char		NORMAL_OPEN_FLAG;		//³£¿ª±êÖ¾
unsigned char		res1[3];
float		MAX_KV;		//×î´óµçÑ¹
float		RATED_AMP;		//¶î¶¨µçÁ÷
float		MAX_AMP;		//×î´óµçÁ÷
float		CAPACITY;		//ÈİÁ¿
unsigned char		NORMAL_POSITION;		//Õı³£×´Ì¬
unsigned char		res2[3];
float		RATED_BREAK_AMP_CAPB;		//¶î¶¨¶ÏÁ÷ÈİÁ¿
float		INTERRUPTING_AMP;		//¿ª¶ÏµçÁ÷
unsigned char		TROLLY_BREAKER_FLAG;		//Ğ¡³µ¿ª¹Ø±êÖ¾
unsigned char		DUAL_DIG_FLAG;		//Ë«Ò£ĞÅ±êÖ¾
unsigned char		ZERO_BRANCH_FLAG;		//ÁãÖ§Â·±êÖ¾
unsigned char		res3[1];
float		DYNSTABLE_AMP;		//¶¯ÎÈ¶¨µçÁ÷
float		THERMAL_STABLE_AMP;		//ÈÈÎÈ¶¨µçÁ÷
unsigned char		POWER_STATE;		//´øµç×´Ì¬
unsigned char		res4[3];
int		TOPO_ISLAND;		//ÍØÆËµçÆøµººÅ
unsigned char		res5[4];
SG_INT64		PLD_CB_ID;		//ÅÔÂ·¿ª¹Ø
unsigned char		TAG_FLAG;		//¹ÒÅÆ±êÖ¾
unsigned char		res6[7];
}MODEL_BREAKER;
//Ä¸Ïß±í	
typedef struct MODEL_BUSBAR_SECTION
{ 
SG_INT64		ID;		//±àºÅ
char		NAME[64];		//ÃèÊö
int		BUSBAR_TYPE;		//ÀàĞÍ
int		BAS_CONN_TYPE;		//Ä¸ÏßÁ¬½ÓÀàĞÍ
char		ALIAS[100];		//±ğÃû
unsigned char		res0[4];
SG_INT64		OF_VOLT_LEVEL;		//µçÑ¹µÈ¼¶
SG_INT64		OF_SUBSTATION;		//³§Õ¾ºÅ
SG_INT64		OF_BAY;		//¼ä¸ô´úÂë
int		POWER_SUPPLY_FLAG;		//µçÔ´µã±êÖ¾
unsigned char		res1[4];
SG_INT64		OF_FEEDER;		//À¡Ïß´úÂë
unsigned char		BUS_STATUS;		//Ä¸Ïß×´Ì¬
unsigned char		res2[7];
double		BUSBAR_VOLT_HLIMIT;		//Ä¸ÏßµçÑ¹ÉÏÏŞ
float		BUSBAR_VOLT_LLIMIT;		//Ä¸ÏßµçÑ¹ÏÂÏŞ
unsigned char		LOAD_BUSBAR_FLAG;		//¸ººÉÄ¸Ïß±êÖ¾
char		DISP_CODE[22];		//µ÷¶ÈºÅ
unsigned char		res3[1];
int		POWER_STATE;		//´øµç×´Ì¬
int		TOPO_ISLAND;		//ÍØÆËµçÆøµººÅ
unsigned char		res4[4];
}MODEL_BUSBAR_SECTION;
//µçÈİÆ÷±í	
typedef struct MODEL_COMPENSATOR
{ 
SG_INT64		ID;		//±àºÅ
char		NAME[64];		//ÃèÊö
int		COMPENSATOR_TYPE;		//ÀàĞÍ
char		ALIAS[100];		//±ğÃû
SG_INT64		OF_BAY;		//¼ä¸ô´úÂë
SG_INT64		OF_VOLT_LEVEL;		//µçÑ¹µÈ¼¶
SG_INT64		OF_SUBSTATION;		//³§Õ¾´úÂë
SG_INT64		OF_FEEDER;		//À¡Ïß´úÂë
float		RATED_MVAR;		//¶î¶¨¹¦ÂÊ
float		MVAR_PER_SECTION;		//Ã¿×éÈİÁ¿
int		MAX_SECTIONS;		//×î´ó×éÊı
int		NORMAL_SECTIONS;		//Í¶ÔË×éÊı
float		RATED_KV;		//¶î¶¨µçÑ¹
float		MAX_KV;		//×î´óµçÑ¹
float		RATED_AMP;		//¶î¶¨µçÁ÷
float		MAX_AMP;		//×î´óµçÁ÷
float		R;		//µç×è
float		X;		//µç¿¹
unsigned char		RUN_STATE;		//ÔËĞĞ×´Ì¬
char		DISP_CODE[22];		//µ÷¶ÈºÅ
unsigned char		res0[1];
int		POWER_STATE;		//´øµç×´Ì¬
int		TOPO_ISLAND;		//ÍØÆËµçÆøµººÅ
}MODEL_COMPENSATOR;
//Á¬½Óµã±í	
typedef struct MODEL_CONN_NODE
{ 
SG_INT64		ID;		//±àºÅ
SG_INT64		OF_VOLT_LEVEL;		//µçÑ¹µÈ¼¶
SG_INT64		OF_CONTAINER;		//³§Õ¾´úÂë
SG_INT64		OF_BASE_VOLTAGE;		//µçÑ¹µÈ¼¶
char		PSRID[64];		//×ÊÔ´ID
SG_INT64		OF_TOPOLOGICALNODE;		//ËùÊôÍØÆË½Úµã
}MODEL_CONN_NODE;
//µçÁ÷»¥¸ĞÆ÷	
typedef struct MODEL_CT
{ 
SG_INT64		ID;		//±àºÅ
char		NAME[64];		//ÃèÊö
int		CT_TYPE;		//ÀàĞÍ
char		ALIAS[100];		//±ğÃû
SG_INT64		OF_BAY;		//¼ä¸ô´úÂë
SG_INT64		OF_VOLT_LEVEL;		//µçÑ¹µÈ¼¶
SG_INT64		OF_SUBSTATION;		//³§Õ¾´úÂë
SG_INT64		OF_FEEDER;		//À¡Ïß´úÂë
unsigned char		PHASE;		//Ïà±ğ
char		CT_MODEL[24];		//µçÁ÷»¥¸ĞÆ÷ĞÍºÅ
unsigned char		res0[3];
float		RATED_KV;		//¶î¶¨µçÑ¹
float		RATED_AMP_RATIO;		//¶î¶¨µçÁ÷±È
char		DISP_CODE[22];		//µ÷¶ÈºÅ
unsigned char		res1[2];
int		POWER_STATE;		//´øµç×´Ì¬
int		TOPO_ISLAND;		//ÍØÆËµçÆøµººÅ
float		AccuracyLimit;		//°Ù·Ö±È¾«¶È
}MODEL_CT;
//µ¶Õ¢±í	
typedef struct MODEL_DISCONNECTOR
{ 
SG_INT64		ID;		//±àºÅ
char		NAME[128];		//ÃèÊö
char		ALIAS[32];		//±ğÃû
char		DISP_CODE[16];		//µ÷¶ÈºÅ
int		TYPE;		//ÀàĞÍ
unsigned char		res0[4];
SG_INT64		OF_SUBSTATION;		//ËùÊô³§Õ¾
SG_INT64		OF_VOLT_LEVEL;		//µçÑ¹µÈ¼¶
SG_INT64		OF_BAY;		//ËùÊô¼ä¸ô
SG_INT64		DIGITAL_ID;		//Ò£ĞÅID
unsigned char		NORMAL_OPEN_FLAG;		//³£¿ª±êÖ¾
unsigned char		MANUAL_SET_FLAG;		//ÈË¹¤ÉèÖÃ±êÖ¾
unsigned char		NORMAL_POSITION;		//Õı³£×´Ì¬
unsigned char		DUAL_DIG_FLAG;		//Ë«Ò£ĞÅ±êÖ¾
unsigned char		POWER_STATE;		//´øµç×´Ì¬
unsigned char		res1[3];
int		TOPO_ISLAND;		//ÍØÆËµçÆøµººÅ
unsigned char		TAG_FLAG;		//¹ÒÅÆ±êÖ¾
unsigned char		res2[3];
}MODEL_DISCONNECTOR;
//ÅäÍø½»Á÷Ïß¶Î±í	
typedef struct MODEL_D_ACLINE_SEGMENT
{ 
SG_INT64		ID;		//±àºÅ
char		NAME[256];		//ÃèÊö
char		ALIAS[64];		//±ğÃû
char		DISP_CODE[64];		//µ÷¶È±àºÅ
SG_INT64		BASE_VOLTAGE;		//»ù×¼µçÑ¹
int		LINE_TYPE;		//ÀàĞÍ
unsigned char		res0[4];
SG_INT64		OF_FEEDER;		//ËùÊôÀ¡Ïß
SG_INT64		OF_FEEDER_SECTION;		//ËùÊô¸ÉÖ§Ïß
SG_INT64		OF_D_SUBSTATION;		//ËùÊôÕ¾·¿
float		LATITUDE;		//Î³¶È
float		LONGITUDE;		//¾­¶È
float		R;		//µç×è
float		X;		//µç¿¹
float		BCH;		//³äµçµçÄÉ
char		LINE_MODEL[64];		//ÏßÂ·ĞÍºÅ
float		LENGTH;		//³¤£¨Ã×£©
float		MAX_AMP;		//×î´óµçÁ÷
int		POWER_STATE;		//´øµç×´Ì¬
int		TOPO_ISLAND;		//ÍØÆËµçÆøµººÅ
float		B;		//µçÄÉ
float		G;		//µçµ¼
char		PSRID[64];		//PSRID
unsigned char		res1[4];
SG_INT64		OF_BASE_VOLTAGE;		//»ù×¼µçÑ¹
double		IPOWER_P;		//ÓĞ¹¦¹¦ÂÊ
double		IPOWER_Q;		//ÎŞ¹¦¹¦ÂÊ
double		IPOWER_I;		//µçÁ÷
double		IPOWER_PLOSS;		//ÓĞ¹¦ËğºÄ
double		IPOWER_QLOSS;		//ÎŞ¹¦ËğºÄ
double		RATED_A;		//³ĞÔØµçÁ÷ÈİÁ¿
double		OVRLMTRATE;		//¹ıÔØÂÊ
double		LIMITUPL;		//µçÁ÷ÖµÔ½ÉÏÏŞ
}MODEL_D_ACLINE_SEGMENT;
//ÅäÍø¿ª¹Ø±í	
typedef struct MODEL_D_BREAKER
{ 
SG_INT64		ID;		//±àºÅ
char		NAME[64];		//ÃèÊö
char		ALIAS[64];		//±ğÃû
char		DISP_CODE[64];		//µ÷¶È±àºÅ
SG_INT64		BASE_VOLTAGE;		//»ù×¼µçÑ¹
int		TYPE;		//¿ª¹ØÀàĞÍ
unsigned char		res0[4];
SG_INT64		OF_FEEDER;		//ËùÊôÀ¡Ïß
SG_INT64		OF_FEEDER_SECTION;		//ËùÊô¸ÉÖ§Ïß
SG_INT64		OF_D_SUBSTATION;		//ËùÊôÕ¾·¿
int		NORMAL_POSITION;		//Õı³£×´Ì¬
char		CABINET_NUMBER[64];		//Õ¾·¿ÄÚ¿ª¹ØµÄ¿ª¹Ø¹ñ±àºÅ
char		DA_COMM_ADDRESS[64];		//Åäµç×Ô¶¯»¯Í¨ĞÅµØÖ·
float		LATITUDE;		//Î³¶È
float		LONGITUDE;		//¾­¶È
int		POWER_STATE;		//´øµç×´Ì¬
int		TOPO_ISLAND;		//ÍØÆËµçÆøµººÅ
unsigned char		TAG_FLAG;		//¹ÒÅÆ±êÖ¾
unsigned char		NORMAL_OPEN_FLAG;		//³£¿ª±êÖ¾
unsigned char		res1[2];
float		RATED_CURRENT;		//¶î¶¨µçÁ÷Öµ
float		BREAKING_CAP;		//×î´ó¿ª¶ÏµçÁ÷Öµ
char		PHASE[6];		//ÏàÎ»
char		PSRID[64];		//PSRID
unsigned char		res2[2];
SG_INT64		OF_BASE_VOLTAGE;		//»ù×¼µçÑ¹
double		IPOWER_P;		//ÓĞ¹¦¹¦ÂÊ
double		IPOWER_Q;		//ÎŞ¹¦¹¦ÂÊ
double		IPOWER_U;		//µçÑ¹
double		IPOWER_I;		//µçÁ÷
}MODEL_D_BREAKER;
//ÅäÍøÄ¸Ïß±í	
typedef struct MODEL_D_BUSBAR_SECTION
{ 
SG_INT64		ID;		//±àºÅ
char		NAME[64];		//ÃèÊö
char		ALIAS[64];		//±ğÃû
char		DISP_CODE[64];		//µ÷¶È±àºÅ
SG_INT64		BASE_VOLTAGE;		//»ù×¼µçÑ¹
int		BUS_TYPE;		//Ä¸ÏßÀàĞÍ
unsigned char		res0[4];
SG_INT64		OF_FEEDER;		//ËùÊôÀ¡Ïß
SG_INT64		OF_FEEDER_SECTION;		//ËùÊô¸ÉÖ§Ïß
SG_INT64		OF_D_SUBSTATION;		//ËùÊôÕ¾·¿
float		LATITUDE;		//Î³¶È
float		LONGITUDE;		//¾­¶È
int		POWER_STATE;		//´øµç×´Ì¬
int		TOPO_ISLAND;		//ÍØÆËµçÆøµººÅ
char		PSRID[64];		//PSRID
SG_INT64		OF_BASE_VOLTAGE;		//»ù×¼µçÑ¹
int		OF_TOPO_ISLAND;		//ÍØÆËµçÆøµººÅ
unsigned char		res1[4];
double		IPOWER_VLTANGLE;		//µçÑ¹Ïà½Ç
double		IPOWER_U;		//µçÑ¹
}MODEL_D_BUSBAR_SECTION;
//ÅäÍøÀ¡Ïß±í	
typedef struct MODEL_D_CIRCUIT
{ 
SG_INT64		ID;		//±àºÅ
char		NAME[64];		//ÃèÊö
char		ALIAS[64];		//±ğÃû
char		DISP_CODE[64];		//µ÷¶È±àºÅ
int		AREA_FEATURE;		//ÇøÓòÌØÕ÷
unsigned char		res0[4];
SG_INT64		SOURCE_SUBST;		//Ô´Í·±äµçÕ¾
SG_INT64		SOURCE_BREAKER;		//³öÏß¿ª¹Ø
int		FA_TYPE;		//À¡Ïß×Ô¶¯»¯ÀàĞÍ
int		FA_LOCK_FLAG;		//À¡Ïß×Ô¶¯»¯Ëø
}MODEL_D_CIRCUIT;
//ÅäÍøµçÈİÆ÷±í	
typedef struct MODEL_D_COMPENSATOR
{ 
SG_INT64		ID;		//±àºÅ
char		NAME[64];		//ÃèÊö
char		ALIAS[64];		//±ğÃû
char		DISP_CODE[64];		//µ÷¶È±àºÅ
SG_INT64		BASE_VOLTAGE;		//»ù×¼µçÑ¹
int		TYPE;		//ÀàĞÍ
unsigned char		res0[4];
SG_INT64		OF_FEEDER;		//ËùÊôÀ¡Ïß
SG_INT64		OF_FEEDER_SECTION;		//ËùÊô¸ÉÖ§Ïß
int		POWER_STATE;		//´øµç×´Ì¬
int		TOPO_ISLAND;		//ÍØÆËµçÆøµººÅ
char		PSRID[64];		//PSRID
SG_INT64		NODEID;		//²¢Íøµã±àºÅ
double		EACH_CAPACITY;		//Ã¿×éÈİÁ¿
int		MAX_NUM;		//×î´ó×éÊı
int		OPERATION_NUM;		//Í¶ÔË×éÊı
int		MAX_ACT_NUM;		//Ê±¶ÎÄÚ×î´ó¶¯×÷´ÎÊı
unsigned char		res1[4];
}MODEL_D_COMPENSATOR;
//ÅäÍøÁ¬½Óµã±í	
typedef struct MODEL_D_CONN_NODE
{ 
SG_INT64		ID;		//±àºÅ
}MODEL_D_CONN_NODE;
//ÅäÍøÖ±Á÷Ïß¶Î±í	
typedef struct MODEL_D_DCLINE_SEGMENT
{ 
SG_INT64		ID;		//±àºÅ
char		NAME[64];		//ÃèÊö
char		ALIAS[64];		//±ğÃû
char		DISP_CODE[64];		//µ÷¶È±àºÅ
SG_INT64		BASE_VOLTAGE;		//»ù×¼µçÑ¹
int		LINE_TYPE;		//ÀàĞÍ
unsigned char		res0[4];
SG_INT64		OF_FEEDER;		//ËùÊôÀ¡Ïß
SG_INT64		OF_FEEDER_SECTION;		//ËùÊô¸ÉÖ§Ïß
SG_INT64		OF_D_SUBSTATION;		//ËùÊôÕ¾·¿
float		LATITUDE;		//Î³¶È
float		LONGITUDE;		//¾­¶È
float		R;		//µç×è
float		X;		//µç¿¹
float		BCH;		//³äµçµçÄÉ
char		LINE_MODEL[64];		//ÏßÂ·ĞÍºÅ
float		LENGTH;		//³¤£¨Ã×£©
float		MAX_AMP;		//×î´óµçÁ÷
int		POWER_STATE;		//´øµç×´Ì¬
int		TOPO_ISLAND;		//ÍØÆËµçÆøµººÅ
float		B;		//µçÄÉ
float		G;		//µçµ¼
unsigned char		res1[4];
}MODEL_D_DCLINE_SEGMENT;
//ÅäÍøµ¶Õ¢±í	
typedef struct MODEL_D_DISCONNECTOR
{ 
SG_INT64		ID;		//±àºÅ
char		NAME[64];		//ÃèÊö
char		ALIAS[64];		//±ğÃû
char		DISP_CODE[64];		//µ÷¶È±àºÅ
SG_INT64		BASE_VOLTAGE;		//»ù×¼µçÑ¹
int		TYPE;		//¸ôµ¶ÀàĞÍ
unsigned char		res0[4];
SG_INT64		OF_FEEDER;		//ËùÊôÀ¡Ïß
SG_INT64		OF_FEEDER_SECTION;		//ËùÊô¸ÉÖ§Ïß
SG_INT64		OF_D_SUBSTATION;		//ËùÊôÕ¾·¿
int		NORMAL_POSITION;		//Õı³£×´Ì¬
char		CABINET_NUMBER[64];		//Õ¾·¿ÄÚ¿ª¹ØµÄ¿ª¹Ø¹ñ±àºÅ
int		POWER_STATE;		//´øµç×´Ì¬
int		TOPO_ISLAND;		//ÍØÆËµçÆøµººÅ
unsigned char		TAG_FLAG;		//¹ÒÅÆ±êÖ¾
unsigned char		NORMAL_OPEN_FLAG;		//³£¿ª±êÖ¾
unsigned char		res1[2];
float		RATED_CURRENT;		//¶î¶¨µçÁ÷Öµ
char		PSRID[64];		//PSRID
unsigned char		res2[4];
}MODEL_D_DISCONNECTOR;
//ÅäÍøµØµ¶±í	
typedef struct MODEL_D_GROUND_DISCONNECTOR
{ 
SG_INT64		ID;		//±àºÅ
char		NAME[64];		//ÃèÊö
char		ALIAS[64];		//±ğÃû
char		DISP_CODE[64];		//µ÷¶È±àºÅ
SG_INT64		BASE_VOLTAGE;		//»ù×¼µçÑ¹
int		TYPE;		//½ÓµØµ¶ÀàĞÍ
unsigned char		res0[4];
SG_INT64		OF_FEEDER;		//ËùÊôÀ¡Ïß
SG_INT64		OF_FEEDER_SECTION;		//ËùÊô¸ÉÖ§Ïß
SG_INT64		OF_D_SUBSTATION;		//ËùÊôÕ¾·¿
int		NORMAL_POSITION;		//Õı³£×´Ì¬
char		CABINET_NUMBER[64];		//Õ¾·¿ÄÚ¿ª¹ØµÄ¿ª¹Ø¹ñ±àºÅ
int		POWER_STATE;		//´øµç×´Ì¬
int		TOPO_ISLAND;		//ÍØÆËµçÆøµººÅ
unsigned char		TAG_FLAG;		//¹ÒÅÆ±êÖ¾
unsigned char		NORMAL_OPEN_FLAG;		//³£¿ª±êÖ¾
char		PSRID[64];		//PSRID
unsigned char		res1[2];
}MODEL_D_GROUND_DISCONNECTOR;
//ÅäÍøµçÑ¹»¥¸ĞÆ÷±í	
typedef struct MODEL_D_PT
{ 
SG_INT64		ID;		//±àºÅ
char		NAME[64];		//ÃèÊö
char		ALIAS[64];		//±ğÃû
char		DISP_CODE[64];		//µ÷¶È±àºÅ
SG_INT64		BASE_VOLTAGE;		//»ù×¼µçÑ¹
int		TYPE;		//ÀàĞÍ
unsigned char		res0[4];
SG_INT64		OF_FEEDER;		//ËùÊôÀ¡Ïß
SG_INT64		OF_FEEDER_SECTION;		//ËùÊô¸ÉÖ§Ïß
int		POWER_STATE;		//´øµç×´Ì¬
int		TOPO_ISLAND;		//ÍØÆËµçÆøµººÅ
float		NorminalRatio;		//±ä±È
char		PHASE[6];		//ÏàÎ»
unsigned char		res1[6];
}MODEL_D_PT;
//ÅäÍøµç¿¹Æ÷±í	
typedef struct MODEL_D_REACTOR
{ 
SG_INT64		ID;		//±àºÅ
char		NAME[64];		//ÃèÊö
char		ALIAS[64];		//±ğÃû
char		DISP_CODE[64];		//µ÷¶È±àºÅ
SG_INT64		BASE_VOLTAGE;		//»ù×¼µçÑ¹
int		TYPE;		//ÀàĞÍ
unsigned char		res0[4];
SG_INT64		OF_FEEDER;		//ËùÊôÀ¡Ïß
SG_INT64		OF_FEEDER_SECTION;		//ËùÊô¸ÉÖ§Ïß
int		POWER_STATE;		//´øµç×´Ì¬
int		TOPO_ISLAND;		//ÍØÆËµçÆøµººÅ
}MODEL_D_REACTOR;
//ÅäÍøÕ¾·¿±í	
typedef struct MODEL_D_SUBSTATION
{ 
SG_INT64		ID;		//±àºÅ
char		NAME[64];		//ÃèÊö
char		ALIAS[64];		//±ğÃû
char		DISP_CODE[64];		//µ÷¶È±àºÅ
SG_INT64		BASE_VOLTAGE;		//»ù×¼µçÑ¹
SG_INT64		SUBTYPE;		//Õ¾·¿ÀàĞÍ
int		CURR_POWER_NO;		//µ±Ç°µçÔ´ºÅ
int		MAIN_POWER_NO;		//Ö÷µçÔ´ºÅ
SG_INT64		OF_FEEDER;		//ËùÊôÀ¡Ïß
SG_INT64		OF_FEEDER_SECTION;		//ËùÊô¸ÉÖ§Ïß
float		LATITUDE;		//Î³¶È
float		LONGITUDE;		//¾­¶È
SG_INT64		BRANCH_ID;		//ÉÏ¼¶¸ÉÖ§Ïß
char		PSRID[64];		//PSRID
}MODEL_D_SUBSTATION;
//ÅäÍø¶Ë×Ó±í	
typedef struct MODEL_D_TERMINAL
{ 
SG_INT64		ID;		//±àºÅ
int		SEQ_NUMBER;		//ĞòºÅ
int		TYPE;		//ÀàĞÍ
SG_INT64		OF_DEVICE;		//ËùÊôÉè±¸
SG_INT64		CONN_NODE_ID;		//Á¬½ÓµãID
}MODEL_D_TERMINAL;
//ÅäÍø±äÑ¹Æ÷±í	
typedef struct MODEL_D_TRANSFORMER
{ 
SG_INT64		ID;		//±àºÅ
char		NAME[64];		//ÃèÊö
char		ALIAS[64];		//±ğÃû
char		DISP_CODE[64];		//µ÷¶È±àºÅ
SG_INT64		BASE_VOLTAGE;		//»ù×¼µçÑ¹
int		TYPE;		//ÀàĞÍ
unsigned char		res0[4];
SG_INT64		OF_FEEDER;		//ËùÊôÀ¡Ïß
SG_INT64		OF_FEEDER_SECTION;		//ËùÊô¸ÉÖ§Ïß
SG_INT64		OF_D_SUBSTATION;		//ËùÊôÕ¾·¿
char		MODEL[64];		//ĞÍºÅ
float		RATED_CAPACITY;		//¶î¶¨ÈİÁ¿
int		USER_TYPE;		//ÓÃ»§ÀàĞÍ
int		VIP_AMOUNT;		//ÖØÒªÓÃ»§Êı
float		LOAD_RATIO;		//¸ºÔØÂÊ
int		POWER_STATE;		//´øµç×´Ì¬
int		TOPO_ISLAND;		//ÍØÆËµçÆøµººÅ
char		VECTOR_GROUP[64];		//½ÓÏß·½Ê½
char		PSRID[64];		//PSRID
double		MPOWER_I;		//µçÁ÷
double		MPOWER_P;		//ÓĞ¹¦¹¦ÂÊ
double		MPOWER_Q;		//ÎŞ¹¦¹¦ÂÊ
double		MPOWER_U;		//µçÑ¹
}MODEL_D_TRANSFORMER;
//ÅäÍøÈÆ×é±í	
typedef struct MODEL_D_TRANS_WINDING
{ 
SG_INT64		ID;		//±àºÅ
char		NAME[64];		//ÃèÊö
char		ALIAS[64];		//±ğÃû
char		DISP_CODE[64];		//µ÷¶È±àºÅ
SG_INT64		BASE_VOLTAGE;		//»ù×¼µçÑ¹
int		TYPE;		//ÀàĞÍ
int		CONN_TYPE;		//½ÓÏß·½Ê½
SG_INT64		OF_D_TRANSFOR;		//ËùÊô±äÑ¹Æ÷
float		RATED_CAPACITY;		//¶î¶¨ÈİÁ¿
int		POWER_STATE;		//´øµç×´Ì¬
int		TOPO_ISLAND;		//ÍØÆËµçÆøµººÅ
unsigned char		ENDNUMBER;		//ĞòºÅ
unsigned char		res0[3];
double		R;		//µç×è
double		X;		//µç¿¹
double		B;		//µçÄÉ
double		G;		//µçµ¼
char		PSRID[64];		//PSRID
}MODEL_D_TRANS_WINDING;
//µç¶¯Æû³µ±í	
typedef struct MODEL_ELECTRICVEHICLE
{ 
SG_INT64		ID;		//±àºÅ
char		name[64];		//Ãû³Æ
char		mRID[64];		//Éè±¸Î¨Ò»ID
SG_INT64		MenberOfLine;		//ËùÊôÀ¡Ïß
SG_INT64		MenberOfSubstation;		//ËùÊô±äµçÕ¾
SG_INT64		timeLasting;		//Ê¹ÓÃÊ±¼ä
SG_INT64		status;		//³äµç×®×´Ì¬
SG_INT64		genEff;		//³äµçĞ§ÂÊ
float		ratedP;		//¶î¶¨¹¦ÂÊ
float		ratedS;		//¶î¶¨ÈİÁ¿
float		maxSOC;		//SOCÉÏÏŞ
float		minSOC;		//SOCÏÂÏŞ
float		SOC;		//SOCÁ¿²â
float		mpower_P;		//ÓĞ¹¦¹¦ÂÊ
float		mpower_Q;		//ÎŞ¹¦¹¦ÂÊ
float		mpower_U;		//µçÑ¹Öµ
float		mpower_I;		//µçÁ÷Öµ
char		PSRID[64];		//PSRID
unsigned char		res0[4];
}MODEL_ELECTRICVEHICLE;
//¸ººÉ±í	
typedef struct MODEL_ENERGY_CONSUMER
{ 
SG_INT64		ID;		//±àºÅ
char		NAME[64];		//ÃèÊö
int		ENERGY_TYPE;		//ÀàĞÍ
char		ALIAS[100];		//±ğÃû
SG_INT64		OF_VOLT_LEVEL;		//µçÑ¹µÈ¼¶
SG_INT64		OF_SUBSTATION;		//³§Õ¾´úÂë
SG_INT64		OF_BAY;		//¼ä¸ô´úÂë
SG_INT64		OF_FEEDER;		//À¡Ïß´úÂë
float		MW_VOLT_CHARACT;		//ÓĞ¹¦¸ººÉµçÑ¹ÌØĞÔ
float		MVAR_VOLT_CHARACT;		//ÎŞ¹¦¸ººÉµçÑ¹ÌØĞÔ
float		MW_FREQ_CHARACT;		//ÓĞ¹¦¸ººÉÆµÂÊÌØĞÔ
float		MVAR_FREQ_CHARACT;		//ÎŞ¹¦¸ººÉÆµÂÊÌØĞÔ
unsigned char		LOAD_STATE;		//¸ººÉ×´Ì¬
unsigned char		res0[3];
float		MW_VALUE;		//ÓĞ¹¦¸ººÉÖµ
float		MVAR_VALUE;		//ÎŞ¹¦¸ººÉÖµ
char		DISP_CODE[22];		//µ÷¶ÈºÅ
unsigned char		res1[2];
int		POWER_STATE;		//´øµç×´Ì¬
int		TOPO_ISLAND;		//ÍØÆËµçÆøµººÅ
float		RATED_ELECTRICITY;		//¶î¶¨µçÁ÷
float		LOAD_RATE;		//¸ºÔØÂÊ
int		CustomerCount;		//¾ÛºÏÓÃ»§Êı
float		Pfixed;		//¹Ì¶¨ÓĞ¹¦¹¦ÂÊ
float		Qfixed;		//¹Ì¶¨ÎŞ¹¦¹¦ÂÊÖµ
unsigned char		Grounded;		//ÊÇ·ñ½ÓµØ
char		PhaseConnection[12];		//½ÓÏß·½Ê½
unsigned char		res2[3];
float		MPOWER_I;		//µçÁ÷
float		MPOWER_U;		//µçÑ¹
float		MPOWER_Q;		//ÎŞ¹¦¹¦ÂÊ
float		MPOWER_P;		//ÓĞ¹¦¹¦ÂÊ
char		PSRID[64];		//×ÊÔ´ID
SG_INT64		OF_TRANSFORMER;		//ËùÊôÌ¨Çø
unsigned char		OF_BASE_VOLTAGE;		//µçÑ¹µÈ¼¶
unsigned char		res3[7];
double		IPOWER_P;		//ÓĞ¹¦¹¦ÂÊ
double		IPOWER_Q;		//ÎŞ¹¦¹¦ÂÊ
double		IPOWER_U;		//µçÑ¹
double		IPOWER_I;		//µçÁ÷
}MODEL_ENERGY_CONSUMER;
//ÈáĞÔ¸ººÉ±í	
typedef struct MODEL_FLEXLOADINFO
{ 
SG_INT64		ID;		//±àºÅ
char		name[64];		//Ãû³Æ
char		mRID[64];		//Éè±¸Î¨Ò»ID
SG_INT64		MenberOfLine;		//ËùÊôÀ¡Ïß
SG_INT64		MenberOfSubstation;		//ËùÊô±äµçÕ¾
float		LdFlxblIncIndx;		//¸ººÉÕıÏòÈáĞÔÏµÊı
float		LdFlxblDecIndx;		//¸ººÉ·´ÏòÈáĞÔÏµÊı
float		LdFlxblIncPr;		//¸ººÉÕıÏò¿Éµ÷½Ú¹¦ÂÊ
float		LdFlxblDecPr;		//¸ººÉ·´Ïò¿Éµ÷½Ú¹¦ÂÊ
unsigned char		usable;		//ÈáĞÔ¸ººÉ×´Ì¬
unsigned char		res0[1];
short		type;		//ÈáĞÔ¸ººÉÀàĞÍ
float		mpower_P;		//ÓĞ¹¦¹¦ÂÊ
float		mpower_Q;		//ÎŞ¹¦¹¦ÂÊ
float		mpower_U;		//µçÑ¹Öµ
float		mpower_I;		//µçÁ÷Öµ
unsigned char		res1[4];
}MODEL_FLEXLOADINFO;
//ÏßÂ·²ÎÊı±í	
typedef struct MODEL_LINE
{ 
SG_INT64		ID;		//±àºÅ
char		DISP_CODE[22];		//µ÷¶ÈºÅ
char		NAME[64];		//ÃèÊö
unsigned char		res0[2];
int		LINE_TYPE;		//ÀàĞÍ
char		ALIAS[100];		//±ğÃû
SG_INT64		BASE_VOLTAGE;		//»ù×¼µçÑ¹
SG_INT64		FROM_SUBSTATION;		//ÆğÊ¼³§Õ¾
SG_INT64		TO_SUBSTATION;		//ÖÕÖ¹³§Õ¾
SG_INT64		OF_COMPANY;		//ËùÊô¹«Ë¾
SG_INT64		OF_BAY;		//¼ä¸ô´úÂë
float		MUTUAL_IMPEDANCE;		//»¥×è¿¹
unsigned char		res1[4];
SG_INT64		ASSOC_LINE;		//Ïà¹ØÏßÂ·Ãû
float		AMP_MARG;		//µçÁ÷Ô£¶È
unsigned char		LINE_STATE;		//ÏßÂ·×´Ì¬
unsigned char		res2[3];
float		CAP_AMP;		//µçÈİµçÁ÷
int		POWER_STATE;		//´øµç×´Ì¬
int		TOPO_ISLAND;		//ÍØÆËµçÆøµººÅ
float		RATED_ELECTRICITY;		//¶î¶¨µçÁ÷
float		LOAD_RATE;		//¸ºÔØÂÊ
unsigned char		res3[4];
}MODEL_LINE;
//±äÑ¹Æ÷±í	
typedef struct MODEL_POWER_TRANS
{ 
SG_INT64		ID;		//±àºÅ
char		DISP_CODE[22];		//µ÷¶ÈºÅ
char		NAME[64];		//ÃèÊö
char		ALIAS[100];		//±ğÃû
unsigned char		res0[2];
int		TRANS_TYPE;		//ÀàĞÍ
SG_INT64		OF_BAY;		//¼ä¸ô´úÂë
SG_INT64		OF_VOLT_LEVEL;		//µçÑ¹µÈ¼¶
SG_INT64		OF_SUBSTATION;		//³§Õ¾´úÂë
SG_INT64		OF_FEEDER;		//À¡Ïß´úÂë
float		HM_LEAKAGE_IMPEDANCE;		//¸ßÖĞ¶ÌÂ·µçÑ¹
float		ML_LEAKAGE_IMPEDANCE;		//ÖĞµÍ¶ÌÂ·µçÑ¹
float		LH_LEAKAGE_IMPEDANCE;		//µÍ¸ß¶ÌÂ·µçÑ¹:
float		HM_LOAD_LOSS;		//¸ßÖĞ¶ÌÂ·ËğºÄ
float		ML_LOAD_LOSS;		//ÖĞµÍ¶ÌÂ·ËğºÄ
float		LH_LOAD_LOSS;		//µÍ¸ß¶ÌÂ·ËğºÄ
float		EXCITING_AMP;		//¿ÕÔØµçÁ÷
float		NOLOAD_LOSS;		//¿ÕÔØËğºÄ
float		GMAG_SAT;		//±äÑ¹Æ÷Àø´Åµçµ¼
float		BMAG_SAT;		//±äÑ¹Æ÷Àø´ÅµçÄÉ
unsigned char		POWERTRANS_STATE;		//±äÑ¹Æ÷×´Ì¬
unsigned char		VOLT_ADJUST_MODE;		//µ÷Ñ¹·½Ê½
unsigned char		res1[2];
float		LOAD_CAPB_RATIO;		//¸ºÔØÈİ±È
unsigned char		PARAM_CALC_FLAG;		//²ÎÊı¼ÆËã±êÖ¾
unsigned char		res2[3];
int		POWER_STATE;		//´øµç×´Ì¬
int		TOPO_ISLAND;		//ÍØÆËµçÆøµººÅ
float		RATED_POWER;		//¶î¶¨¹¦ÂÊ
float		ACTIVE_BALANCE_RATE;		//ÓĞ¹¦Æ½ºâÂÊ
float		REACTIVE_BALANCE_RATE;		//ÎŞ¹¦Æ½ºâÂÊ
float		LOAD_RATE;		//¸ºÔØÂÊ
char		VectorGroup[64];		//½ÓÏß·½Ê½
unsigned char		res3[4];
}MODEL_POWER_TRANS;
//µçÑ¹»¥¸ĞÆ÷	
typedef struct MODEL_PT
{ 
SG_INT64		ID;		//±àºÅ
char		NAME[64];		//ÃèÊö
float		PT_TYPE;		//ÀàĞÍ
char		ALIAS[100];		//±ğÃû
SG_INT64		OF_SUBSTATION;		//³§Õ¾´úÂë
SG_INT64		OF_BAY;		//¼ä¸ô´úÂë
SG_INT64		OF_VOLT_LEVEL;		//µçÑ¹µÈ¼¶
SG_INT64		OF_FEEDER;		//À¡Ïß´úÂë
char		PHASE[12];		//Ïà±ğ
char		PT_MODEL[24];		//µçÑ¹»¥¸ĞÆ÷ĞÍºÅ
float		RATED_KV;		//¶î¶¨µçÑ¹
float		RATED_VOLT_RATIO;		//¶î¶¨µçÑ¹±È
char		DISP_CODE[22];		//µ÷¶ÈºÅ
unsigned char		res0[2];
int		POWER_STATE;		//´øµç×´Ì¬
int		TOPO_ISLAND;		//ÍØÆËµçÆøµººÅ
unsigned char		res1[4];
}MODEL_PT;
//¹â·ü±í	
typedef struct MODEL_PVARRAY
{ 
SG_INT64		ID;		//±àºÅ
char		NAME[64];		//Ãû³Æ
SG_INT64		OF_FEEDER;		//ËùÊôÀ¡Ïß
SG_INT64		OF_SUBSTATION;		//ËùÊô±äµçÕ¾
float		RATED_P;		//¶î¶¨¹¦ÂÊ
float		MAX_P;		//×î´óÓĞ¹¦
float		MIN_P;		//×îĞ¡ÓĞ¹¦
float		MAX_Q;		//×î´óÎŞ¹¦
float		MIN_Q;		//×îĞ¡ÎŞ¹¦
unsigned char		USEABLE;		//¹â·ü×´Ì¬
unsigned char		res0[3];
float		MAX_PF;		//¹¦ÂÊÒòÊıÉÏÏŞ
float		MIN_PF;		//¹¦ÂÊÒòÊıÏÂÏŞ
float		MPOWER_P;		//ÓĞ¹¦¹¦ÂÊ
float		MPOWER_Q;		//ÎŞ¹¦¹¦ÂÊ
float		MPOWER_U;		//µçÑ¹Öµ
float		MPOWER_I;		//µçÁ÷Öµ
char		PSRID[64];		//PSRID
SG_INT64		OF_TRANSFORMER;		//ËùÊôÌ¨Çø
double		IPOWER_P;		//ÓĞ¹¦¹¦ÂÊ
double		IPOWER_Q;		//ÎŞ¹¦¹¦ÂÊ
double		IPOWER_U;		//µçÑ¹Öµ
double		IPOWER_I;		//µçÁ÷Öµ
unsigned char		OF_BASE_VOLTAGE;		//»ù×¼µçÑ¹
unsigned char		res1[7];
}MODEL_PVARRAY;
//µç¿¹Æ÷±í	
typedef struct MODEL_REACTOR
{ 
SG_INT64		ID;		//±àºÅ
char		NAME[64];		//ÃèÊö
SG_INT64		REACTOR_TYPE;		//ÀàĞÍ
char		ALIAS[100];		//±ğÃû
unsigned char		res0[4];
SG_INT64		OF_BAY;		//¼ä¸ô´úÂë
SG_INT64		OF_VOLT_LEVEL;		//µçÑ¹µÈ¼¶
SG_INT64		OF_SUBSTATION;		//³§Õ¾´úÂë
SG_INT64		OF_FEEDER;		//À¡Ïß´úÂë
float		RATED_MVAR;		//¶î¶¨¹¦ÂÊ
float		MVAR_PER_SECTION;		//Ã¿×éÈİÁ¿
int		MAX_SECTIONS;		//×î´ó×éÊı
int		NORMAL_SECTIONS;		//Í¶ÔË×éÊı
float		RATED_KV;		//¶î¶¨µçÑ¹
float		MAX_KV;		//×î´óµçÑ¹
float		RATED_AMP;		//¶î¶¨µçÁ÷
float		MAX_AMP;		//×î´óµçÁ÷
float		R;		//µç×è
float		X;		//µç¿¹
unsigned char		RUN_STATE;		//ÔËĞĞ×´Ì¬
char		DISP_CODE[22];		//µ÷¶ÈºÅ
unsigned char		res1[1];
int		POWER_STATE;		//´øµç×´Ì¬
int		TOPO_ISLAND;		//ÍØÆËµçÆøµººÅ
}MODEL_REACTOR;
//³§Õ¾±í	
typedef struct MODEL_SUBSTATION
{ 
SG_INT64		ID;		//±àºÅ
char		NAME[64];		//ÃèÊö
char		ALIAS[100];		//±ğÃû
int		SUBSTATION_TYPE;		//ÀàĞÍ
SG_INT64		OF_SCA;		//ËùÊô×Ó¿ØÇøÓò
SG_INT64		BASE_VOLTAGE;		//»ù×¼µçÑ¹
SG_INT64		OF_FEEDER;		//ËùÊôÀ¡Ïß
int		DIGTAL_NUM;		//Ò£ĞÅÊı
int		ANALOG_NUM;		//Ò£²âÊı
int		DEVICE_NUM;		//Éè±¸Êı
int		EVENT_NUM;		//¸æ¾¯Êı
int		TAG_NUM;		//¹ÒÅÆÊı
unsigned char		res0[4];
SG_INT64		OF_SUBREGION;		//ËùÊô×ÓÇøÓò
char		PSRID[255];		//psrid
unsigned char		res1[1];
SG_INT64		OF_BASE_VOLTAGE;		//»ù×¼µçÑ¹
}MODEL_SUBSTATION;
//·¢µç»ú±í	
typedef struct MODEL_SYNCHRONOUS_MACHE
{ 
SG_INT64		ID;		//±àºÅ
char		NAME[64];		//ÃèÊö
int		MACHE_TYPE;		//ÀàĞÍ
char		ALIAS[100];		//±ğÃû
SG_INT64		OF_FEEDER;		//À¡Ïß´úÂë
SG_INT64		OF_SUBSTATION;		//³§Õ¾´úÂë
SG_INT64		OF_VOLT_LEVEL;		//µçÑ¹µÈ¼¶
SG_INT64		OF_BAY;		//¼ä¸ô´úÂë
float		MAX_KV;		//×î´óµçÑ¹
float		MAX_MVAR;		//×î´óÎŞ¹¦
float		MIN_KV;		//×îĞ¡µçÑ¹
float		MIN_MVAR;		//×îĞ¡ÎŞ¹¦
float		MAX_MW;		//×î´óÓĞ¹¦
float		MIN_MW;		//×îĞ¡ÓĞ¹¦
float		RATED_MVA;		//¶î¶¨ÈİÁ¿
float		R1;		//ÕıĞòµç×è
float		X1;		//ÕıĞòµç¿¹
float		R0;		//ÁãĞòµç×è
float		X0;		//ÁãĞòµç¿¹
float		X2;		//¸ºĞòµç¿¹
float		GEN_FREQCHARACT;		//·¢µç»ú¹¦ÆµÌØĞÔ
int		GEN_MODEL;		//·¢µç»úÄ£ĞÍ
float		INTERTIA;		//×ª×Ó¹ßĞÔÊ±¼ä³£Êı
float		RA;		//¶¨×Óµç×è
float		XO;		//¶¨×ÓÂ©¿¹
float		XD;		//Ö±ÖáÍ¬²½µç¿¹
float		XDIRECT_TRANS;		//Ö±ÖáÔİÌ¬µç¿¹
float		XDIRECT_SUBTRANS;		//Ö±Öá´ÎÔİÌ¬µç¿¹
float		XQ;		//½»ÖáÍ¬²½µç¿¹
float		XQUAD_TRANS;		//½»ÖáÔİÌ¬µç¿¹
float		XQUAD_SUBTRANS;		//½»Öá´ÎÔİÌ¬µç¿¹
float		DAMP;		//×èÄáÏµÊı
float		TD0P;		//Àø´Å»ØÂ·Ê±¼ä³£Êı
float		TD0PP;		//Ö±Öá×èÄáÈÆ×è»ØÂ·Ê±¼ä³£Êı
float		TQ0PP;		//½»Öá×èÄáÈÆ×èÊ±¼ä»ØÂ·³£Êı
float		GEN_UNIT_FACT_FILTR_COEF;		//»ú×éÂË²¨ÏµÊı
float		GEN_FM_COE;		//ÆµÂÊµ÷½ÚÌØĞÔ
float		CTRL_DBAND;		//¿ØÖÆËÀÇø
float		REG_MARG;		//µ÷½ÚÓà¶È
float		EMERG_BACKUP_LLIMIT;		//½ô¼±±¸ÓÃÏÂÏŞ
float		CAPB_LLIMIT;		//ÈİÁ¿ÏÂÏŞ
float		CTRL_LLIMIT;		//ÔËĞĞ¿ØÖÆÏÂÏŞ
float		SCHED_GEN;		//»ú×é¼Æ»®
float		CTRL_HLIMIT;		//ÔËĞĞ¿ØÖÆÉÏÏŞ
float		CAPB_HLIMIT;		//ÈİÁ¿ÉÏÏŞ
float		EMERG_BACKUP_HLIMIT;		//½ô¼±±¸ÓÃÉÏÏŞ
int		HYD_NUM_IWD_CURVES;		//·¢µç»úÇúÏßÊıÁ¿
unsigned char		res0[4];
SG_INT64		GEN_RES_ID;		//PLCºÅ
char		HYD_CURVE_NAME[24];		//ºÄÁ÷Á¿ÇúÏßÃû
int		PHB_CNT;		//½ûÖ¹ÔËĞĞÇø¸öÊı
float		PROHB_REGN_LO_PWR_RATIO;		//½ûÖ¹ÔËĞĞÇøÏÂÏŞÏµÊı
float		PROHB_REGN_HI_PWR_RATIO;		//½ûÖ¹ÔËĞĞÇøÉÏÏŞÏµÊı
float		ROC_LIMIT;		//µ÷½ÚËÙÂÊÏŞÖÆ
float		MAINT_COST;		//Î¬»¤·ÑÓÃ
float		PAYB_CONST;		//³¥»¹ÏµÊı
char		THR_FUEL_NAME[24];		//È¼ÁÏÃû³Æ
float		THR_INC_POLLU_COST;		//Î¢ÔöÎÛÈ¾·ÑÓÃ
int		WATER_TEMP_FACT;		//ÀäÈ´Ë®ÎÂÒò×Ó
int		GEN_STATE;		//·¢µç»ú×´Ì¬
char		DISP_CODE[22];		//µ÷¶ÈºÅ
unsigned char		res1[2];
int		POWER_STATE;		//´øµç×´Ì¬
int		TOPO_ISLAND;		//ÍØÆËµçÆøµººÅ
unsigned char		res2[4];
}MODEL_SYNCHRONOUS_MACHE;
//·Ö½ÓÍ·±í	
typedef struct MODEL_TAPCHANGER
{ 
SG_INT64		ID;		//±àºÅ
char		DESCRIPTION[64];		//ÃèÊö
char		NAME[64];		//Ãû³Æ
char		HIGH_STEP[64];		//HIGH_STEP
float		NEUTRAL_STEP;		//NEUTRAL_STEP
float		LOW_STEP;		//LOW_STEP
float		STEP_VOLTAGE_INCREMENT;		//STEP_VOLTAGE_INCREMENT
float		NEUTRAL_KV;		//NEUTRAL_KV
float		NORMAL_STEP;		//NORMAL_STEP
unsigned char		res0[4];
SG_INT64		OF_TRANSWINDING;		//ËùÊôÈÆ×é
}MODEL_TAPCHANGER;
//¶Ë×Ó±í	
typedef struct MODEL_TERMINAL
{ 
SG_INT64		ID;		//±àºÅ
char		NAME[64];		//ÃèÊö
char		ALIAS[100];		//±ğÃû
int		TERMINAL_TYPE;		//ÀàĞÍ
SG_INT64		OF_DEVICE;		//ËùÊôÉè±¸
char		ADDR[12];		//µØÖ·
unsigned char		res0[4];
SG_INT64		CONN_NODE_ID;		//Á¬½ÓµãID
char		PHASE[6];		//ÏàÎ»
char		PSRID[64];		//×ÊÔ´ID
unsigned char		res1[2];
}MODEL_TERMINAL;
//±äÑ¹Æ÷ÈÆ×é±í	
typedef struct MODEL_TRANS_WINDING
{ 
SG_INT64		ID;		//±àºÅ
char		NAME[64];		//ÃèÊö
int		WINDING_TYPE;		//ÀàĞÍ
int		CONN_TYPE;		//Á¬½ÓÀàĞÍ
char		ALIAS[100];		//±ğÃû
unsigned char		res0[4];
SG_INT64		OF_VOLT_LEVEL;		//µçÑ¹µÈ¼¶
SG_INT64		OF_POWERTRANS;		//ËùÊô±äÑ¹Æ÷
float		RATED_KV;		//¶î¶¨µçÑ¹
float		RATED_MVA;		//¶î¶¨ÈİÁ¿
float		R;		//µç×è
float		X;		//µç¿¹
float		R0;		//ÁãĞòµç×è
float		X0;		//ÁãĞòµç¿¹
float		G;		//ÈÆ×éÀø´Åµçµ¼
float		B;		//ÈÆ×éÆ÷Àø´ÅµçÄÉ
float		MAX_AMP;		//×î´óµçÁ÷
unsigned char		ADJUST_FLAG;		//¿Éµ÷±êÖ¾
unsigned char		GROUND_FLAG;		//½ÓµØ±êÖ¾
unsigned char		res1[2];
int		TAP_TYPE;		//³éÍ·ÀàĞÍ
int		ACTUAL_TAP_POS;		//Êµ¼ÊµµÎ»
float		AMP_MARG;		//µçÁ÷Ô£¶È
int		POWER_STATE;		//´øµç×´Ì¬
int		TOPO_ISLAND;		//ÍØÆËµçÆøµººÅ
unsigned char		ENDNUMBER;		//ĞòºÅ
unsigned char		res2[3];
}MODEL_TRANS_WINDING;
//µçÑ¹µÈ¼¶±í	
typedef struct MODEL_VOLT_LEVEL
{ 
SG_INT64		ID;		//±àºÅ
char		NAME[64];		//ÃèÊö
SG_INT64		OF_SUBSTATION;		//³§Õ¾±í_±àºÅ
char		ALIAS[100];		//±ğÃû
unsigned char		res0[4];
SG_INT64		BASE_VOLTAGE;		//»ù×¼µçÑ¹
}MODEL_VOLT_LEVEL;
//·ç»ú±í	
typedef struct MODEL_WINDGENERATOR
{ 
SG_INT64		ID;		//ID
char		name[64];		//Ãû³Æ
SG_INT64		OF_FEEDER;		//ËùÊôÀ¡Ïß
SG_INT64		OF_SUBSTATION;		//ËùÊô±äµçÕ¾
float		RATED_PF;		//¶î¶¨¹¦ÂÊÒòÊı
float		MAX_P;		//×î´óÓĞ¹¦
float		MIN_P;		//×îĞ¡ÓĞ¹¦
float		MAX_Q;		//×î´óÎŞ¹¦
float		MIN_Q;		//×îĞ¡ÎŞ¹¦
unsigned char		USABLE;		//·ç»ú×´Ì¬
unsigned char		res0[3];
float		START_SPEED;		//Æô¶¯·çËÙ
float		RATED_SPEED;		//¶î¶¨·çËÙ
float		MAX_SPEED;		//×î´ó·çËÙ
float		mpower_P;		//ÓĞ¹¦¹¦ÂÊ
float		mpower_Q;		//ÎŞ¹¦¹¦ÂÊ
float		mpower_U;		//µçÑ¹Öµ
float		mpower_I;		//µçÁ÷Öµ
char		PSRID[64];		//PSRID
unsigned char		res1[4];
}MODEL_WINDGENERATOR;
//ÅäÍøÀ¡Ïß±í	
typedef struct MODEL_D_FEEDER
{ 
SG_INT64		ID;		//±àºÅ
char		NAME[64];		//ÃèÊö
char		ALIAS[100];		//±ğÃû
char		DISP_CODE[64];		//µ÷¶È±àºÅ
unsigned char		res0[4];
SG_INT64		AREA_FEATURE;		//ÇøÓòÌØÕ÷
SG_INT64		OF_STATION;		//Ô´Í·±äµçÕ¾
SG_INT64		OF_BREAKER;		//³öÏß¿ª¹Ø
int		FA_TYPE;		//À¡Ïß×Ô¶¯»¯ÀàĞÍ
int		FA_LOCK_FLAG;		//À¡Ïß×Ô¶¯»¯Ëø
char		PSRID[64];		//×ÊÔ´ID
}MODEL_D_FEEDER;
//ÅäÍø½ÓÍ·	
typedef struct MODEL_D_JUNCTION
{ 
SG_INT64		ID;		//±àºÅ
SG_INT64		OF_DEVICE;		//ËùÊôÉè±¸
}MODEL_D_JUNCTION;
//ÅäÍø¿Í»§	
typedef struct MODEL_D_CUSTOMER
{ 
SG_INT64		ID;		//±àºÅ
char		NAME[64];		//ÃèÊö
char		ALIAS[100];		//±ğÃû
unsigned char		res0[4];
SG_INT64		OF_FEEDER;		//À¡Ïß´úÂë
SG_INT64		METER_ID;		//±í¼Æ
}MODEL_D_CUSTOMER;
//±í¼Æ	
typedef struct MODEL_METER
{ 
SG_INT64		ID;		//±àºÅ
char		NAME[64];		//ÃèÊö
char		ALIAS[100];		//±ğÃû
unsigned char		res0[4];
SG_INT64		OF_USAGEPOINT;		//ËùÊô½ÓÈëµã
}MODEL_METER;
//CT	
typedef struct MODEL_D_CT
{ 
SG_INT64		ID;		//±àºÅ
char		NAME[64];		//ÃèÊö
int		CT_TYPE;		//ÀàĞÍ
char		ALIAS[100];		//±ğÃû
SG_INT64		OF_BAY;		//¼ä¸ô´úÂë
SG_INT64		OF_VOLT_LEVEL;		//µçÑ¹µÈ¼¶
SG_INT64		OF_SUBSTATION;		//³§Õ¾´úÂë
SG_INT64		OF_FEEDER;		//À¡Ïß´úÂë
short		PHASE;		//Ïà±ğ
char		CT_MODEL[24];		//µçÁ÷»¥¸ĞÆ÷ĞÍºÅ
unsigned char		res0[6];
double		RATED_KV;		//¶î¶¨µçÑ¹
double		RATED_AMP_RATIO;		//¶î¶¨µçÁ÷±È
char		DISP_CODE[22];		//µ÷¶ÈºÅ
unsigned char		res1[2];
int		POWER_STATE;		//´øµç×´Ì¬
int		TOPO_ISLAND;		//ÍØÆËµçÆøµººÅ
double		ACCURACYLIMIT;		//°Ù·Ö±È¾«¶È
}MODEL_D_CT;
//ÓÃ»§½ÓÈëµã	
typedef struct MODEL_USAGEPOINT
{ 
SG_INT64		ID;		//±àºÅ
char		NAME[64];		//ÃèÊö
char		ALIAS[100];		//±ğÃû
unsigned char		res0[4];
SG_INT64		OF_EQLOAD;		//ËùÊôµÈĞ§¸ººÉ
}MODEL_USAGEPOINT;
//Ä£ÄâÁ¿	
typedef struct MODEL_ANALOG
{ 
SG_INT64		ID;		//±àºÅ
char		NAME[64];		//Ãû³Æ
SG_INT64		OF_DEVICE;		//ËùÊôÉè±¸
SG_INT64		OF_FEEDER;		//ËùÊôÀ¡Ïß
SG_INT64		OF_SUBSTATION;		//ËùÊôµçÕ¾
int		PORT;		//¶Ë×ÓºÅ
int		MEAS_TYPE;		//Á¿²âÀàĞÍ
double		VAL;		//Öµ
int		STATUS;		//×´Ì¬
int		PROCTIME;		//±ä»¯Ê±¼ä
int		UNIT;		//µ¥Î»
unsigned char		res0[4];
}MODEL_ANALOG;
//·ÂÕæÀúÊ·±í	
typedef struct his_simulation
{ 
int		ID;		//×ÔÔöID
unsigned char		res0[4];
SG_INT64		TASKID;		//·ÂÕæÈÎÎñID
SG_INT64		OF_DEVICE;		//ËùÊôÉè±¸
unsigned char		MEAS_TYPE;		//Á¿²âÀàĞÍ
unsigned char		res1[7];
double		TIME;		//Ò»´Î·ÂÕæÄÚµÄÏà¶ÔÊ±¼ä
float		VAL;		//·ÂÕæ½á¹ûÖµ
unsigned char		res2[4];
}his_simulation;
//ÍøÂç½Úµã±í	
typedef struct net_node
{ 
int		ID;		//ÍøÂç½ÚµãID
char		NAME[64];		//½ÚµãÃû³Æ
char		ALIAS[64];		//Ãû³ÆÃèÊö
unsigned char		TYPE;		//½ÚµãÀàĞÍ
unsigned char		res0[3];
}net_node;
//ÍøÂç±ß±í	
typedef struct net_edge
{ 
int		ID;		//ÍøÂç±ßID
char		NAME[64];		//±ßÃû³Æ
int		LEFTNODE;		//×ó½ÚµãID
int		RIGHTNODE;		//ÓÒ½ÚµãID
int		DELAY;		//±ß³õÊ¼Ê±ÑÓ
}net_edge;
//ÍøÂç½ÚµãÊÂ¼ş±í	
typedef struct sim_event
{ 
int		ID;		//ÊÂ¼şID
unsigned char		res0[4];
double		EVENTTIME;		//ÊÂ¼ş·¢ÉúÊ±¼ä
int		OBJECTID;		//·¢ÉúÊÂ¼şµÄ½Úµã»ò±ßµÄID
unsigned char		TYPE;		//ÊÂ¼şÀàĞÍ
unsigned char		res1[3];
int		PARAM;		//ÊÂ¼şÏà¹ØµÄ½Úµã»ò±ßµÄID
unsigned char		EVENTTYPE;		//0ĞÅÏ¢ÊÂ¼ş£¬1ÎïÀíÊÂ¼ş
unsigned char		res2[3];
SG_INT64		TASKID;		//·ÂÕæÈÎÎñID
}sim_event;
//ĞÅÏ¢ÎïÀí¶ÔÏó¶ÔÓ¦¹ØÏµ±í	
typedef struct net_pow_relate
{ 
char		NODEID[64];		//ĞÅÏ¢Íø½ÚµãÃû
char		OF_DEVICE_MEAS[64];		//²É¼¯Ôª¼şID
char		OF_DEVICE_CTR[64];		//¿ØÖÆÔª¼şID
int		ID;		//ID
}net_pow_relate;
//cloudpssÍ¨µÀ±í	
typedef struct pss_passage
{ 
SG_INT64		ID;		//Í¨µÀID
char		NAME[256];		//Í¨µÀÃû³Æ
char		CHANNLE_TYPE[256];		//Êä³öÍ¨µÀÃû³Æ£¬Ò²ÊÇÀàĞÍ£¬ÈçIrms¡
char		CHANNLE_PIN[256];		//Êä³öÍ¨µÀÒı½Å£¬Ò²ÊÇÔª¼ş²âÁ¿²ÎÊıÒ
SG_INT64		OF_DEVICE;		//ËùÊôÉè±¸
}pss_passage;
//mdc_model_map	
typedef struct mdc_model_map
{ 
int		MODEL_ID;		//MODEL_ID
char		MODEL_NAME[32];		//MODEL_NAME
}mdc_model_map;
//base_meas_def	
typedef struct base_meas_def
{ 
unsigned char		ID;		//ID
char		NAME[288];		//NAME
char		MEASTYPE_DESC[360];		//Á¿²âÀàĞÍÃèÊö
}base_meas_def;
//Ò£²âÊµÊ±Êı¾İ±í	
typedef struct rtval_analog
{ 
SG_INT64		ID;		//ID
float		VAL;		//Ò£²âÖµ
int		STATUS;		//STATUS
int		PROCTIME;		//PROCTIME
unsigned char		res0[4];
}rtval_analog;
//¿ØÖÆ³£Á¿±í	
typedef struct control_constant
{ 
SG_INT64		ID;		//±àºÅ
char		NAME[64];		//ÃèÊö
char		TYPE[256];		//¿ØÖÆÀàĞÍ£¬ÈçP¡¢Q
char		VALUE[256];		//¿ØÖÆÖµ
char		PINS[64];		//¿ØÖÆÒı½Å
SG_INT64		OF_DEVICE;		//ËùÊôÔª¼şID
}control_constant;
//·ÂÕæ¼ÇÂ¼±í	
typedef struct sim_task
{ 
SG_INT64		ID;		//·ÂÕæÈÎÎñID
char		NAME[64];		//·ÂÕæÈÎÎñÃû³Æ
SG_INT64		OF_FEEDER;		//·ÂÕæÏßÂ·ID
int		TIMELENGTH;		//·ÂÕæÊ±³¤
unsigned char		STATE;		//Íê³É×´Ì¬
unsigned char		res0[3];
}sim_task;
//¹â·üÄæ±äÆ÷±í	
typedef struct model_PV_inverter
{ 
SG_INT64		ID;		//ID
char		NAME[64];		//Ãû³Æ
char		PSRID[64];		//PSRID
SG_INT64		OF_FEEDER;		//ËùÊôÀ¡ÏßID
int		BASE_VOLTAGE;		//ËùÊôµçÑ¹µÈ¼¶
unsigned char		res0[4];
SG_INT64		NODEID;		//²¢Íøµã±àºÅ
double		RATE_CAPACITY;		//¶î¶¨ÈİÁ¿
double		ACTIVE_POWER;		//ÓĞ¹¦³öÁ¦
double		REACTIVE_POWER;		//ÎŞ¹¦³öÁ¦
int		CONTROL_MODE;		//¿ØÖÆÄ£Ê½
unsigned char		res1[4];
}model_PV_inverter;
//model_AVC_Node	
typedef struct model_AVC_Node
{ 
SG_INT64		ID;		//ID
char		NAME[64];		//Ãû³Æ
char		PSRID[64];		//PSRID
SG_INT64		OF_FEEDER;		//ËùÊôÀ¡ÏßID
int		BASE_VOLTAGE;		//ËùÊôµçÑ¹µÈ¼¶
unsigned char		res0[4];
double		VOLTAGE;		//µçÑ¹·ùÖµ
int		UP_STATE;		//µçÑ¹Ô½ÉÏÏŞµÄÀëÉ¢×´Ì¬±äÁ¿
int		DOWN_STATE;		//µçÑ¹Ô½ÏÂÏŞµÄÀëÉ¢×´Ì¬±äÁ¿
int		NORMAL_STATE;		//µçÑ¹²»Ô½ÏŞµÄÀëÉ¢×´Ì¬±äÁ¿
unsigned char		res1[4];
}model_AVC_Node;
//model_AVC_Line	
typedef struct model_AVC_Line
{ 
SG_INT64		ID;		//ID
char		NAME[64];		//Ãû³Æ
char		PSRID[64];		//PSRID
SG_INT64		OF_FEEDER;		//ËùÊôÀ¡ÏßID
int		BASE_VOLTAGE;		//ËùÊôµçÑ¹µÈ¼¶
unsigned char		res0[4];
SG_INT64		START_NODEID;		//ÆğÊ¼²¢Íøµã±àºÅ
SG_INT64		END_NODEID;		//½áÎ²²¢Íøµã±àºÅ
double		RESISTANCE;		//µç×è
double		REACTANCE;		//µç¿¹
}model_AVC_Line;
//À¡ÏßĞÅÏ¢±í	
typedef struct avc_feeder_info
{ 
SG_INT64		FEEDERID;		//À¡ÏßID
double		ENERGY_LOSS;		//ÄÜÁ¿ËğºÄ
double		MAX_VOLTAGE;		//×î¸ßµçÑ¹Öµ
double		MIN_VOLTAGE;		//×îµÍµçÑ¹Öµ
double		ENERGY_LOSS_BEFORE;		//ÓÅ»¯Ç°ÄÜÁ¿ËğºÄ
double		MAX_VOLTAGE_BEFORE;		//ÓÅ»¯Ç°×î¸ßµçÑ¹Öµ
double		MIN_VOLTAGE_BEFORE;		//ÓÅ»¯Ç°×îµÍµçÑ¹Öµ
}avc_feeder_info;
//Äæ±äÆ÷³öÁ¦ÀúÊ·ÓÅ»¯½á¹û±í	
typedef struct avc_Inverter_Histrory
{ 
SG_INT64		INVERTERID;		//Äæ±äÆ÷id
double		ACTIVE_POWER;		//ÓĞ¹¦³öÁ¦
double		REACTIVE_POWER;		//ÎŞ¹¦³öÁ¦
int		CONTROL_MODE;		//¿ØÖÆÄ£Ê½
unsigned char		res0[4];
SG_INT64		TIME;		//ÓÅ»¯Ê±¼ä
}avc_Inverter_Histrory;
//µçÈİÆ÷³öÁ¦ÀúÊ·ÓÅ»¯½á¹û±í	
typedef struct avc_compensator_Histrory
{ 
SG_INT64		COMPENSATORID;		//µçÈİÆ÷id
double		EACH_CAPACITY;		//Ã¿×éÈİÁ¿
int		OPERATION_NUM;		//Í¶ÔË×éÊı
int		MAX_ACT_NUM;		//Ê±¶ÎÄÚ×î´ó¶¯×÷´ÎÊı
SG_INT64		TIME;		//ÓÅ»¯Ê±¼ä
}avc_compensator_Histrory;
//¸ººÉÔ¤²â±í	
typedef struct avc_predictive_load
{ 
SG_INT64		LOADID;		//¸ººÉID
SG_INT64		NODEID;		//²¢Íøµã±àºÅ
double		ACTIVE_POWER;		//ÓĞ¹¦³öÁ¦
double		REACTIVE_POWER;		//ÎŞ¹¦³öÁ¦
int		TIME;		//0~95»ò0~23£¬ÓëTypeÅäºÏÊ¹ÓÃ
int		TYPE;		//0£º·ÖÖÓ¼¶±ğ£»1£ºĞ¡Ê±¼¶±ğ
}avc_predictive_load;
//¹â·üÔ¤²â±í	
typedef struct avc_predictive_PV
{ 
SG_INT64		PVID;		//¹â·üID
SG_INT64		NODEID;		//²¢Íøµã±àºÅ
double		ACTIVE_POWER;		//ÓĞ¹¦³öÁ¦
int		TIME;		//0~96»ò0~24£¬ÓëTypeÅäºÏÊ¹ÓÃ
int		TYPE;		//0£º·ÖÖÓ¼¶±ğ£»1£ºĞ¡Ê±¼¶±ğ
}avc_predictive_PV;
//model_d_ac	
typedef struct model_d_ac
{ 
SG_INT64		ID;		//ÏµÍ³Éè±¸ID
char		name[64];		//Ãû³Æ
char		mRID[64];		//Éè±¸Î¨Ò»ID
double		TSetmax;		//¿Õµ÷ÎÂ¶ÈÉè¶¨ÉÏÏŞ
double		TSetmin;		//¿Õµ÷ÎÂ¶ÈÉè¶¨ÏÂÏŞ
double		ETAmin;		//ÄÜĞ§ÏµÊı×îĞ¡Öµ
double		ETAmax;		//ÄÜĞ§ÏµÊı×î´óÖµ
double		Racmin;		//ÈÈ×è×îĞ¡Öµ
double		Racmax;		//ÈÈ×è×î´óÖµ
double		Cacmin;		//ÈÈÈİ×îĞ¡Öµ
double		Cacmax;		//ÈÈÈİ×î´óÖµ
double		TSetAve;		//ÉèÖÃÎÂ¶ÈÆÚÍû
double		DeltaTmin;		//Éè¶¨ÎÂ¶ÈÏÂµ÷¼«ÏŞ
double		DeltaTmax;		//Éè¶¨ÎÂ¶ÈÉÏµ÷¼«ÏŞ
double		Rlow;		//Ëæµç¼ÛÉÏ¸¡Ğ±ÂÊ
double		Rhigh;		//Ëæµç¼ÛÏÂ¸¡Ğ±ÂÊ
double		Pinuse_a;		//SigmoidĞÎ×´²ÎÊı
double		Pinuse_b;		//SigmoidĞÎ×´²ÎÊı
double		Pindr_a;		//SigmoidĞÎ×´²ÎÊı
double		Pindr_b;		//SigmoidĞÎ×´²ÎÊı
double		ACPara1;		//Ãô¸ĞÏµÊı1
double		ACPara2;		//Ãô¸ĞÏµÊı2
double		ACPara3;		//Ãô¸ĞÏµÊı3
double		ACPara4;		//Ãô¸ĞÏµÊı4
}model_d_ac;
//model_d_5g	
typedef struct model_d_5g
{ 
SG_INT64		ID;		//ÏµÍ³Éè±¸ID
double		GTrafficMax;		//5GÌìÏß×î´óÀûÓÃÂÊ
double		PMode1;		//1µµ¹¦ÂÊ
double		PMode2;		//2µµ¹¦ÂÊ
double		PMode3;		//3µµ¹¦ÂÊ
double		PMode4;		//4µµ¹¦ÂÊ
}model_d_5g;
//model_d_evcar	
typedef struct model_d_evcar
{ 
SG_INT64		ID;		//ÏµÍ³Éè±¸ID
char		name[64];		//Ãû³Æ
char		mRID[64];		//Éè±¸Î¨Ò»ID
double		CarBattry;		//Æ½¾ùµç³ØÈİÁ¿
double		ChargeSlow;		//Âı³ä¹¦ÂÊ
double		ChargeHigh;		//¿ì³ä¹¦ÂÊ
double		Charge1;		//Ã¿ÈÕÒ»³äÓÃ»§Õ¼±È
double		Charge2;		//Ã¿ÈÕÁ½³äÓÃ»§Õ¼±È
double		Charge3;		//Ã¿ÈÕÈı³äÓÃ»§Õ¼±È
double		ChomeAV;		//¼ÒÓÃ³äµç¾ùÖµ
double		ChomeSD;		//¼ÒÓÃ³äµç±ê×¼²î
double		CCompAV;		//¹«Ë¾³äµç¾ùÖµ
double		CCompSD;		//¹«Ë¾³äµç±ê×¼²î
double		CShopAV;		//ÉÌ³¡³äµç¾ùÖµ
double		CShopSD;		//ÉÌ³¡³äµç±ê×¼²î
double		ChargeEff;		//³äµçĞ§ÂÊ
double		CarQAV;		//³õÊ¼µçºÉ·Ö²¼¾ùÖµ
double		CarQSD;		//³õÊ¼µçºÉ·Ö²¼±ê×¼²î
double		CarPara1;		//²ÎÓëµ÷½ÚÕ¼±È1
double		CarPara2;		//²ÎÓëµ÷½ÚÕ¼±È2
double		CarPara3;		//²ÎÓëµ÷½ÚÕ¼±È3
double		CarPara4;		//²ÎÓëµ÷½ÚÕ¼±È4
}model_d_evcar;
//ÈÈË®Æ÷±í	
typedef struct model_waterheater
{ 
SG_INT64		ID;		//ÏµÍ³Éè±¸ID
char		name[64];		//Ãû³Æ
char		mRID[64];		//Éè±¸Î¨Ò»ID
double		DeltaTW;		//ÎÂ¶ÈÉè¶¨ÔÊĞíÆ«ÒÆ
double		Twhmax;		//×î´óÎÂ¶ÈÏŞÖÆ
double		Twhmin;		//×îĞ¡ÎÂ¶ÈÏŞÖÆ
double		WHcapacity;		//ÈÈË®Æ÷ÈİÁ¿
double		WHPower;		//ÈÈË®Æ÷¶î¶¨¹¦ÂÊ
double		TankAmax;		//Ë®Ïä±íÃæ»ı×î´óÖµ
double		TankAmin;		//Ë®Ïä±íÃæ»ı×îĞ¡Öµ
double		TankRmin;		//Ë®ÏäÈÈ×è×îĞ¡Öµ
double		TankRmax;		//Ë®ÏäÈÈ×è×î´óÖµ
double		DeltaWaterEv;		//ÀäË®ÎÂ¶ÈÓë»·¾³ÎÂ¶ÈÖ®²î£¨Éè¶¨Öµ£
double		Shift_1;		//ÎŞ¸ĞÆ½ÒÆÊ±¶ÎÊı
double		Shift_2;		//Î¢¸ĞÆ½ÒÆÊ±¶ÎÊı
double		Shift_3;		//ÖĞĞÔÆ½ÒÆÊ±¶ÎÊı
double		Shift_4;		//Ç¿¸ĞÆ½ÒÆÊ±¶ÎÊı
double		Elast_1;		//ÎŞ¸Ğ×Ôµ¯ĞÔÏµÊı
double		Elast_2;		//Î¢¸Ğ×Ôµ¯ĞÔÏµÊı
double		Elast_3;		//ÖĞĞÔ×Ôµ¯ĞÔÏµÊı
double		Elast_4;		//Ç¿¸Ğ×Ôµ¯ĞÔÏµÊı
double		WH_state;		//³õÊ¼¿ª¹Ø×´Ì¬
}model_waterheater;
//ÔËĞĞ±í	
typedef struct Rapa_Operation
{ 
SG_INT64		ID;		//ID
SG_INT64		DeviceID;		//Éè±¸ID
int		Time;		//Ê±¼ä£¨15·ÖÖÓÒ»¸öµã£©
unsigned char		res0[4];
double		Temp;		//ÊÒÍâÎÂ¶È
double		Price;		//µç¼Û
double		SHStream;		//ÈÈË®Á÷ËÙ
double		Original;		//Ô­Ê¼¾ÛºÏ¹¦ÂÊ
double		Rapa;		//¿¼ÂÇµç¼Ûºó¾ÛºÏ¹¦ÂÊ
double		Reserve;		//Ç±Á¦ÈİÁ¿
int		Type;		//ÀàĞÍ
unsigned char		res1[4];
}Rapa_Operation;
//ÈÕµç¼Û±í	
typedef struct Rapa_PowerPrice
{ 
int		Time;		//Ê±¼ä£¨15·ÖÖÓÒ»¸öµã£©
unsigned char		res0[4];
double		Price;		//µç¼Û
}Rapa_PowerPrice;
//ÈÕÊÒÍâÎÂ¶È±í	
typedef struct Rapa_OutTemp
{ 
int		Time;		//Ê±¼ä£¨15·ÖÖÓÒ»¸öµã£©
unsigned char		res0[4];
double		Temp;		//ÊÒÍâÎÂ¶È
}Rapa_OutTemp;
//ÈÕÈÈË®Á÷ËÙ±í	
typedef struct Rapa_WaterFlow
{ 
int		Time;		//Ê±¼ä£¨15·ÖÖÓÒ»¸öµã£©
unsigned char		res0[4];
double		SHStream;		//ÈÈË®Á÷ËÙ
}Rapa_WaterFlow;
//ÇøÓò±í	
typedef struct MODEL_REGION
{ 
SG_INT64		ID;		//ID
char		NAME[64];		//Ãû³Æ
char		PSRID[255];		//×ÊÔ´ID
unsigned char		res0[1];
}MODEL_REGION;
//×ÓÇøÓò±í	
typedef struct MODEL_SUBREGION
{ 
SG_INT64		ID;		//ID
char		NAME[64];		//Ãû³Æ
SG_INT64		OF_REGION;		//ËùÊôÇøÓò
char		PSRID[255];		//×ÊÔ´ID
unsigned char		res0[1];
}MODEL_SUBREGION;
//¹â·ü¹¦ÂÊµ¹ËÍÒì³£ĞŞ¸´±í	
typedef struct DAS_POWER_REVERSE
{ 
int		ID;		//ID
int		TIME;		//Ê±¼ä


SG_INT64		OF_DEVICE;		//ËùÊôÌ¨ÇøºÅ
float		B_PV_P;		//µ÷½ÚÇ°¹â·üÓĞ¹¦¹¦ÂÊ
float		B_PV_Q;		//µ÷½ÚÇ°¹â·üÎŞ¹¦¹¦ÂÊ
float		A_PV_P;		//µ÷½Úºó¹â·üÓĞ¹¦¹¦ÂÊ
float		A_PV_Q;		//µ÷½Úºó¹â·üÎŞ¹¦¹¦ÂÊ
float		B_EC_U;		//µ÷½ÚÇ°¸ººÉµçÑ¹
float		A_EC_U;		//µ÷½Úºó¸ººÉÔ¤²âµçÑ¹
float		QF;		//ÎŞ¹¦¹¦ÂÊµ÷½ÚÒòÊı
unsigned char		res0[4];
}DAS_POWER_REVERSE;
//¹â·üÔ¤²â±í	
typedef struct DAS_PV_PREDICTION
{ 
SG_INT64		ID;		//¼ÇÂ¼ºÅ
SG_INT64		DeviceID;		//Éè±¸ID
int		MeasType;		//Á¿²âÀàĞÍ
float		Value;		//Á¿²âÖµ
SG_INT64		Time;		//Ê±¼ä´Á
SG_INT64		PredictionID;		//Ô¤²âID
}DAS_PV_PREDICTION;
//µç¶¯Æû³µ³äµç¹ÜÀí±í	
typedef struct DAS_EV_MAN
{ 
SG_INT64		ID;		//¼ÇÂ¼ºÅ
int		CHARGETIMESTART;		//³äµç¿ªÊ¼Ê±¼ä
int		CHARGETIMEEND;		//³äµç½áÊøÊ±¼ä
int		DISCHARGETIMESTART;		//·Åµç¿ªÊ¼Ê±¼ä
int		DISCHARGETIMEEND;		//·Åµç½áÊøÊ±¼ä
SG_INT64		OF_DEVICE;		//ËùÊô³äµçÉè±¸
}DAS_EV_MAN;
//ÈıÏà²»Æ½ºâ´¦Àí±í	
typedef struct DAS_UNBALANCE
{ 
SG_INT64		ID;		//¼ÇÂ¼ºÅ
char		PhaseA[1024];		//AÏàÉè±¸×Ü¼¯
char		PhaseB[1024];		//BÏàÉè±¸×Ü¼¯
char		PhaseC[1024];		//CÏàÉè±¸×Ü¼¯
int		StartTime;		//ÆğÊ¼Ê±¼äµã
int		EndTime;		//½áÊøÊ±¼äµã
SG_INT64		OF_DEVICE;		//ËùÊôÌ¨ÇøID
}DAS_UNBALANCE;
//²âÊÔ±í	
typedef struct MODEL_TEST
{ 
SG_INT64		ID;		//±àºÅ
char		NAME[64];		//ÃèÊö
int		NVALUE;		//ÕûĞÍÖµ
float		FVALUE;		//¸¡µãÖµ
float		MPOWER_P;		//ÓĞ¹¦²âÁ¿Öµ
float		MPOWER_Q;		//ÎŞ¹¦²âÁ¿Öµ
float		IPOWER_P;		//ÓĞ¹¦¼ÆËãÖµ
float		IPOWER_Q;		//ÎŞ¹¦¼ÆËãÖµ
}MODEL_TEST;
//¸ß¼¶Ó¦ÓÃÅäÖÃ±í	
typedef struct DAS_CONFIG
{ 
int		ID;		//ID
char		APPCODE[64];		//Ó¦ÓÃÃû³Æ
int		APPID;		//Ó¦ÓÃ±àºÅ
int		PARAID;		//²ÎÊı±àºÅ
char		NAME[64];		//²ÎÊıÃû³Æ
char		DESC[255];		//²ÎÊıÃèÊö
unsigned char		res0[1];
int		TYPE;		//²ÎÊıÀàĞÍ
char		CHVALUE[255];		//×Ö·û´®Öµ
unsigned char		res1[1];
int		INTVALUE;		//ÕûĞÍÖµ
float		FLOATVALUE;		//¸¡µãÖµ
}DAS_CONFIG;
//model_thermalgenerator	
typedef struct model_thermalgenerator
{ 
SG_INT64		ID;		//±àºÅ
double		MAX_P;		//×î´óÓĞ¹¦
double		MAX_PF;		//¹¦ÂÊÒòÊıÉÏÏŞ
double		MAX_Q;		//×î´óÎŞ¹¦
double		MIN_P;		//×îĞ¡ÓĞ¹¦
double		MIN_PF;		//¹¦ÂÊÒòÊıÏÂÏŞ
double		MIN_Q;		//×îĞ¡ÎŞ¹¦
double		MPOWER_I;		//µçÁ÷Öµ
double		MPOWER_P;		//ÓĞ¹¦¹¦ÂÊ
double		MPOWER_Q;		//ÎŞ¹¦¹¦ÂÊ
double		MPOWER_U;		//µçÑ¹Öµ
char		NAME[64];		//Ãû³Æ
SG_INT64		OF_FEEDER;		//ËùÊôÀ¡Ïß
SG_INT64		OF_SUBSTATION;		//ËùÊô±äµçÕ¾
char		PSRID[64];		//×ÊÔ´ID
double		RATED_P;		//¶î¶¨¹¦ÂÊ
unsigned char		USEABLE;		//¹â·ü×´Ì¬
unsigned char		res0[7];
double		IPOWER_P;		//ÓĞ¹¦¹¦ÂÊ
double		IPOWER_Q;		//ÎŞ¹¦¹¦ÂÊ
double		IPOWER_U;		//µçÑ¹Öµ
double		IPOWER_I;		//µçÁ÷Öµ
unsigned char		OF_BASE_VOLTAGE;		//»ù×¼µçÑ¹
unsigned char		res1[7];
}model_thermalgenerator;
//MODEL_HYDROPOWER	
typedef struct MODEL_HYDROPOWER
{ 
SG_INT64		ID;		//±àºÅ
double		MAX_P;		//×î´óÓĞ¹¦
double		MAX_PF;		//¹¦ÂÊÒòÊıÉÏÏŞ
double		MAX_Q;		//×î´óÎŞ¹¦
double		MIN_P;		//×îĞ¡ÓĞ¹¦
double		MIN_PF;		//¹¦ÂÊÒòÊıÏÂÏŞ
double		MIN_Q;		//×îĞ¡ÎŞ¹¦
double		MPOWER_I;		//µçÁ÷Öµ
double		MPOWER_P;		//ÓĞ¹¦¹¦ÂÊ
double		MPOWER_Q;		//ÎŞ¹¦¹¦ÂÊ
double		MPOWER_U;		//µçÑ¹Öµ
char		NAME[64];		//Ãû³Æ
SG_INT64		OF_FEEDER;		//ËùÊôÀ¡Ïß
SG_INT64		OF_SUBSTATION;		//ËùÊô±äµçÕ¾
char		PSRID[64];		//×ÊÔ´ID
double		RATED_P;		//¶î¶¨¹¦ÂÊ
unsigned char		USEABLE;		//¹â·ü×´Ì¬
unsigned char		res0[7];
double		IPOWER_P;		//ÓĞ¹¦¹¦ÂÊ
double		IPOWER_Q;		//ÎŞ¹¦¹¦ÂÊ
double		IPOWER_U;		//µçÑ¹Öµ
double		IPOWER_I;		//µçÁ÷Öµ
unsigned char		OF_BASE_VOLTAGE;		//»ù×¼µçÑ¹
unsigned char		res1[7];
}MODEL_HYDROPOWER;
//model_d_acline_dot	
typedef struct MODEL_D_ACLINE_DOT
{ 
SG_INT64		ID;		//±àºÅ
char		NAME[32];		//Ãû³Æ
double		P_VALUE;		//ÓĞ¹¦¹¦ÂÊ
double		Q_VALUE;		//ÎŞ¹¦¹¦ÂÊ
double		CURRENT;		//µçÁ÷
double		VOLTAGE;		//µçÑ¹Öµ
SG_INT64		OF_ACLINE_SEGMENT;		//ËùÊô½»Á÷µ¼Ïß¶Î
SG_INT64		OF_TERMINAL;		//ËùÊô¶Ë×Ó
}MODEL_D_ACLINE_DOT;
//MODEL_ENERGY_SOURCE	
typedef struct MODEL_ENERGY_SOURCE
{ 
SG_INT64		ID;		//±àºÅ
char		NAME[64];		//ÃèÊö
char		ALIAS[100];		//±ğÃû
unsigned char		OF_BASE_VOLTAGE;		//µçÑ¹µÈ¼¶
unsigned char		res0[3];
SG_INT64		OF_SUBSTATION;		//³§Õ¾´úÂë
SG_INT64		OF_FEEDER;		//À¡Ïß´úÂë
int		TOPO_ISLAND;		//ÍØÆËµçÆøµººÅ
unsigned char		res1[4];
double		MPOWER_P;		//ÓĞ¹¦
double		MPOWER_Q;		//ÓĞ¹¦
double		MPOWER_U;		//ÓĞ¹¦
double		MPOWER_I;		//ÓĞ¹¦
double		IPOWER_P;		//ÓĞ¹¦
double		IPOWER_Q;		//ÎŞ¹¦
double		IPOWER_U;		//µçÑ¹
double		IPOWER_I;		//µçÁ÷
unsigned char		ATTRIBUTE;		//½ÚµãÀàĞÍ£º1Æ½ºâ½Úµã£»2¹¦ÂÊ½Úµã£
unsigned char		res2[7];
}MODEL_ENERGY_SOURCE;
//BASE_VOLT_DEF	
typedef struct BASE_VOLT_DEF
{ 
SG_INT64		ID;		//ID
char		EN_NAME[32];		//Ó¢ÎÄÃû
char		CN_NAME[32];		//ÖĞÎÄÃû
double		STD_VAL;		//»ù×¼Öµ
double		H_LMT;		//»ù×¼ÉÏÏŞ
double		L_LMT;		//»ù×¼ÏÂÏŞ
}BASE_VOLT_DEF;
//MODEL_TOPOLOGICAL_ISLAND	
typedef struct MODEL_TOPOLOGICAL_ISLAND
{ 
SG_INT64		ID;		//±àºÅ
char		NAME[32];		//Ãû³Æ
int		CONTAINSTOPOLOGICALNODE;		//°üº¬ÍØÆË½ÚµãÊıÁ¿
int		FIRSTPSR;		//Ê×Éè±¸ÏÂ±ê
int		NUMBEROFPSR;		//Éè±¸ÊıÄ¿
unsigned char		ISCONVERGED;		//ÊÇ·ñÊÕÁ²
unsigned char		res0[3];
double		LOADPOWERP;		//µºÄÚ×Ü¸ººÉÓĞ¹¦
double		LOADPOWERQ;		//µºÄÚ×Ü¸ººÉÎŞ¹¦
double		SUMLOSSP;		//µºÄÚ×ÜËğºÄÓĞ¹¦
double		SUMLOSSQ;		//µºÄÚ×ÜËğºÄÎŞ¹¦
unsigned char		ISLAND;		//ÊÇ·ñ¹Âµº
unsigned char		CLOSEDLOOP;		//ÊÇ·ñºÏ»·
unsigned char		res1[6];
}MODEL_TOPOLOGICAL_ISLAND;
//MODEL_TOPOLOGICAL_NODE	
typedef struct MODEL_TOPOLOGICAL_NODE
{ 
SG_INT64		ID;		//±àºÅ
char		NAME[32];		//Ãû³Æ
SG_INT64		OF_TOPOLOGICALISLAND;		//ËùÊôÍØÆËµº
int		CONTAINSCONNECTIVITYNODE;		//°üº¬Á¬½Ó½ÚµãÊıÁ¿
int		NUMBEROFPSR;		//Éè±¸ÊıÁ¿
double		VLTMAG;		//µçÑ¹·ùÖµ
double		VLTANGLE;		//µçÑ¹Ïà½Ç
}MODEL_TOPOLOGICAL_NODE;
#endif 
