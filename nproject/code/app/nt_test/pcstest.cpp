#include <stdlib.h>
#include <stdio.h>
#include "sgdebuginfo.h"
#include "dppclient.h"
int TestStartCalcProc(CGAP_PCMSrvClient &Client)
{
	CPCM_StartCalcProc_Req Req1;
	CPCM_StartCalcProc_Res Res1;
	Req1.CalcProcType = 3;
	S_TWOSTRING TwoStr;
	TwoStr.Val1 = "SchemaHandler"; 	TwoStr.Val2 = "1001";
	Req1.ReplaceKeyList.push_back(TwoStr);
	TwoStr.Val1 = "STATION"; TwoStr.Val2 = "30001";
	Req1.ReplaceKeyList.push_back(TwoStr);
	TwoStr.Val1 = "Volt"; TwoStr.Val2 = "8";
	Req1.ReplaceKeyList.push_back(TwoStr);
	if (Client.PCM_StartCalcProc(Req1, Res1) < 0)
		return false;
	//从返回程序中获取算例进程ID
	SG_UNION_UINT64 UnionInt64;
	UnionInt64.Int64Val = Res1.ProcID;
	//查看算例进程的运行状况
	CPCM_AskCalcProcState_Req Req2;
	CPCM_AskCalcProcState_Res Res2;
	Req2.ProcID = Res1.ProcID;
	if (Client.PCM_AskCalcProcState(Req2, Res2) < 0)
		return false;
	return true;

}
int TestUpLoadFile(CGAP_PCMSrvClient &Client)
{

	CSgString SrvFileName,LocalFileName,ErrInfo;
	int ProcMode = 0;
	SrvFileName = "/home/app/bbb.txt";
	LocalFileName = "D:/tmp/bbb.txt";
	//文件上传
	if (Client.PCM_FileUpLoad(SrvFileName, LocalFileName,ProcMode, ErrInfo,0,1024000) < 0)
		return false;
	//文件下载
	LocalFileName = "D:/tmp/bbb_a.txt";
	if (Client.PCM_FileUpLoad(SrvFileName, LocalFileName, ProcMode, ErrInfo, 0, 1024000) < 0)
		return false;
	return true;
}
int TestExeCmd(CGAP_PCMSrvClient &Client)
{
	CPCM_ShellCmd_Req Req;
	CPCM_ShellCmd_Res Res;
	Req.ShellCmd = "date";
	if (Client.PCM_ExeShecllCmd(Req, Res) < 0)
		return false;
	return true;

}
int main(
		 int argc,
		 char *argv[]) 
		 
{
	CGAP_PCMSrvClient PCMClient;
	//设置数据库服务的IP地址
	PCMClient.SetIPString("192.168.122.17:6116");
	//上传下载文件
	TestUpLoadFile(PCMClient);
	//执行命令
	TestExeCmd(PCMClient);
	//启动算例进程
	TestStartCalcProc(PCMClient);
	return 1;
}
