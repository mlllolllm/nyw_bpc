#ifndef __GRAPHICS_NETUSE_COMMAND_DEFINE_HEADER__
#define __GRAPHICS_NETUSE_COMMAND_DEFINE_HEADER__

#pragma once

#include "command/NetCommandID.h"
//==================================================================================================
// 定义规划信息系统中空间引擎的命令
namespace NetCommand
{
	enum NetUseCommandID		//	空间引擎的扩展命令，从 300 开始，到 400 结束
	{

		 netuse_search_PowerPoint	=	NetUseCmdMin,
		 netuse_cal_Refl_Region		=	NetUseCmdMin+1,
         netuse_cal_top             =	NetUseCmdMin+2,
         netuse_cal_line_formula    =	NetUseCmdMin+3,
         netuse_cal_meastype        =	NetUseCmdMin+4,
         netuse_cal_net_changetime  =	NetUseCmdMin+5,

		 GIS_TOPO_OutageRange_GW		=	NetUseCmdMin+46,		//停电范围分析
		 GIS_TOPO_SupplyPath_GW			=	NetUseCmdMin+47,		//供电路径分析，和国网GIS逻辑相同
		 GIS_TOPO_SupplyRange_GW		=	NetUseCmdMin+48,		//供电范围分析，和国网GIS逻辑相同
		 GIS_TOPO_SupplyRadius_GW		=	NetUseCmdMin+49,		//供电半径分析，和国网GIS逻辑相同
		 GIS_TOPO_PowerSource_GW		=	NetUseCmdMin+50,		//电源点分析，和国网GIS逻辑相同

		 GIS_TOPO_ShortPathRoad_new		=	NetUseCmdMin+51,		//道路最短路径分析
		 GIS_TOPO_Connectivity_new		=	NetUseCmdMin+52,		//连通性分析
		 GIS_TOPO_SupplyRange_new		=	NetUseCmdMin+53,		//供电范围分析
		 GIS_TOPO_SupplyRadius_new		=	NetUseCmdMin+54,		//供电半径分析
		 GIS_TOPO_PowerSource_new		=	NetUseCmdMin+55,		//电源点分析
		 GIS_TOPO_SupplyPath			=	NetUseCmdMin+56,		//供电路径分析
		 GIS_TOPO_GDD_PowerSource		=	NetUseCmdMin+57,		//供电点电源关系分析
		 GIS_TOPO_MULTIConnectivity		=	NetUseCmdMin+58,		//查找多个设备间的路径

		 GIS_TOPO_ShortPathCable	=	NetUseCmdMin+60,		//管网最短路径
		 GIS_TOPO_ShortPathRoad		=	NetUseCmdMin+61,		//道路最短路径分析
		 GIS_TOPO_Connectivity		=	NetUseCmdMin+62,		//连通性分析
		 GIS_TOPO_SupplyRange		=	NetUseCmdMin+63,		//供电范围分析
		 GIS_TOPO_SupplyRadius		=	NetUseCmdMin+64,		//供电半径分析
		 GIS_TOPO_PowerSource		=	NetUseCmdMin+65,		//电源点分析
		 GIS_TOPO_OutageRange		=	NetUseCmdMin+66,		//停电范围分析
		 GIS_TOPO_CableLineCorridor	=	NetUseCmdMin+67,		//电缆线路走廊分析
		 GIS_TOPO_GetCtrlAttrib		=	NetUseCmdMin+68,		//获取设备的控制属性
		 GIS_TOPO_TransPath			=	NetUseCmdMin+69,	//电源转供路径
		 GIS_TOPO_SearchPower_YKBZ	=	NetUseCmdMin+71		//业扩报装 搜索电源点

	};
};

#endif//__GRAPHICS_DATABASE_COMMAND_DEFINE_HEADER__
