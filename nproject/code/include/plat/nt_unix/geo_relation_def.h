#ifndef __ORACLE_DEF_H__
#define __ORACLE_DEF_H__

#define SPATIAL_NO                   0  //�޹�ϵ
#define SPATIAL_DISJOINT             3  //�߽���ڲ����ཻ��
#define SPATIAL_TOUCH                4  //�߽��ཻ�������ڲ�������
#define SPATIAL_OVERLAPBDYDISJOINT   5  //һ��������ڲ�����һ��������ڲ��ͱ߽��ཻ���������ߵı߽粻����
#define SPATIAL_OVERLAPBDYINTERSECT  6  //��������ı߽���ڲ����ཻ��
#define SPATIAL_EQUAL                7  //��������������ͬ�ı߽���ڲ���
#define SPATIAL_CONTAINS             8  //һ��������ڲ��ͱ߽���ȫ���������������ڲ���
#define SPATIAL_COVERS               9  //һ��������ڲ���ȫ��������һ��������ڲ���߽��ϣ������ߵı߽����ཻ�ġ�
#define SPATIAL_INSIDE               10 //��CONTAINS�����ö����෴��
#define SPATIAL_COVEREDBY            11 //��COVERS�����ö����෴��
#define SPATIAL_ON                   12 //һ��������ڲ��ͱ߽�����һ������ı߽��ϣ��ҵڶ������󸲸ǵ�һ���������磬һ������һ������εı��ϡ�
#define SPATIAL_ANYINTERACT          13 //���������Ƿǲ����ġ�
#define SPATIAL_IN  "INSIDE|OVERLAPBDYDISJOINT|OVERLAPBDYINTERSECT|COVEREDBY|ON"



#endif