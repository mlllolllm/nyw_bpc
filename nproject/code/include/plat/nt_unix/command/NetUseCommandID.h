#ifndef __GRAPHICS_NETUSE_COMMAND_DEFINE_HEADER__
#define __GRAPHICS_NETUSE_COMMAND_DEFINE_HEADER__

#pragma once

#include "command/NetCommandID.h"
//==================================================================================================
// ����滮��Ϣϵͳ�пռ����������
namespace NetCommand
{
	enum NetUseCommandID		//	�ռ��������չ����� 300 ��ʼ���� 400 ����
	{

		 netuse_search_PowerPoint	=	NetUseCmdMin,
		 netuse_cal_Refl_Region		=	NetUseCmdMin+1,
         netuse_cal_top             =	NetUseCmdMin+2,
         netuse_cal_line_formula    =	NetUseCmdMin+3,
         netuse_cal_meastype        =	NetUseCmdMin+4,
         netuse_cal_net_changetime  =	NetUseCmdMin+5,

		 GIS_TOPO_OutageRange_GW		=	NetUseCmdMin+46,		//ͣ�緶Χ����
		 GIS_TOPO_SupplyPath_GW			=	NetUseCmdMin+47,		//����·���������͹���GIS�߼���ͬ
		 GIS_TOPO_SupplyRange_GW		=	NetUseCmdMin+48,		//���緶Χ�������͹���GIS�߼���ͬ
		 GIS_TOPO_SupplyRadius_GW		=	NetUseCmdMin+49,		//����뾶�������͹���GIS�߼���ͬ
		 GIS_TOPO_PowerSource_GW		=	NetUseCmdMin+50,		//��Դ��������͹���GIS�߼���ͬ

		 GIS_TOPO_ShortPathRoad_new		=	NetUseCmdMin+51,		//��·���·������
		 GIS_TOPO_Connectivity_new		=	NetUseCmdMin+52,		//��ͨ�Է���
		 GIS_TOPO_SupplyRange_new		=	NetUseCmdMin+53,		//���緶Χ����
		 GIS_TOPO_SupplyRadius_new		=	NetUseCmdMin+54,		//����뾶����
		 GIS_TOPO_PowerSource_new		=	NetUseCmdMin+55,		//��Դ�����
		 GIS_TOPO_SupplyPath			=	NetUseCmdMin+56,		//����·������
		 GIS_TOPO_GDD_PowerSource		=	NetUseCmdMin+57,		//������Դ��ϵ����
		 GIS_TOPO_MULTIConnectivity		=	NetUseCmdMin+58,		//���Ҷ���豸���·��

		 GIS_TOPO_ShortPathCable	=	NetUseCmdMin+60,		//�������·��
		 GIS_TOPO_ShortPathRoad		=	NetUseCmdMin+61,		//��·���·������
		 GIS_TOPO_Connectivity		=	NetUseCmdMin+62,		//��ͨ�Է���
		 GIS_TOPO_SupplyRange		=	NetUseCmdMin+63,		//���緶Χ����
		 GIS_TOPO_SupplyRadius		=	NetUseCmdMin+64,		//����뾶����
		 GIS_TOPO_PowerSource		=	NetUseCmdMin+65,		//��Դ�����
		 GIS_TOPO_OutageRange		=	NetUseCmdMin+66,		//ͣ�緶Χ����
		 GIS_TOPO_CableLineCorridor	=	NetUseCmdMin+67,		//������·���ȷ���
		 GIS_TOPO_GetCtrlAttrib		=	NetUseCmdMin+68,		//��ȡ�豸�Ŀ�������
		 GIS_TOPO_TransPath			=	NetUseCmdMin+69,	//��Դת��·��
		 GIS_TOPO_SearchPower_YKBZ	=	NetUseCmdMin+71		//ҵ����װ ������Դ��

	};
};

#endif//__GRAPHICS_DATABASE_COMMAND_DEFINE_HEADER__
