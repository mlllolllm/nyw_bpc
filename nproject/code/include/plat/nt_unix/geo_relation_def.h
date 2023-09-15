#ifndef __ORACLE_DEF_H__
#define __ORACLE_DEF_H__

#define SPATIAL_NO                   0  //无关系
#define SPATIAL_DISJOINT             3  //边界和内部不相交。
#define SPATIAL_TOUCH                4  //边界相交，但是内部不交。
#define SPATIAL_OVERLAPBDYDISJOINT   5  //一个对象的内部与另一个对象的内部和边界相交，但是两者的边界不交。
#define SPATIAL_OVERLAPBDYINTERSECT  6  //两个对象的边界和内部都相交。
#define SPATIAL_EQUAL                7  //两个对象有着相同的边界和内部。
#define SPATIAL_CONTAINS             8  //一个对象的内部和边界完全包含在另个对象的内部。
#define SPATIAL_COVERS               9  //一个对象的内部完全包含在另一个对象的内部或边界上，且两者的边界是相交的。
#define SPATIAL_INSIDE               10 //与CONTAINS的作用对象相反。
#define SPATIAL_COVEREDBY            11 //与COVERS的作用对象相反。
#define SPATIAL_ON                   12 //一个对象的内部和边界在另一个对象的边界上（且第二个对象覆盖第一个对象）例如，一条线在一个多边形的边上。
#define SPATIAL_ANYINTERACT          13 //两个对象是非不交的。
#define SPATIAL_IN  "INSIDE|OVERLAPBDYDISJOINT|OVERLAPBDYINTERSECT|COVEREDBY|ON"



#endif