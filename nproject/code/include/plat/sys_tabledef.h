/***********************************************
	Part 50 系统特定域名定义
***********************************************/
//#define SGF_SDEOBJID		"OBJECTID"			//对象类型域名
#define SGF_OBJECTTYPE		"OBJ_TYPE"			//对象类型域名
#define SGF_OBJECT_ID		"OBJ_ID"			//对象ID
#define SGF_OBJECT_NAME		"OBJ_NAME"			//对象名
#define SGF_OBJECTID		"ID"				//对象内控ID域名
#define SGF_OBJECTCODE		"OBJ_CODING"		//对象编码域名
#define SGF_OBJECTELECODE	"POWER_NO"		//电系编号
#define SGF_OBJECTNAME		"NAME"				//对象名称
#define SGF_LABEL_NAME		"LABLE_NAME"
//#define SGF_OBJECTSYMBOL	"OBJ_SYM"			//对象挂接符号
#define SGF_OFFSETX		"OFFSETX"			//对象横向偏移x
#define SGF_OFFSETY		"OFFSETY"			//对象纵向偏移y
#define SGF_TEXT_ATTRIB	"TEXT_ATTRIB"		//文字对象的字体特征
#define SGF_SEGMENT        "SEGMENT"           //支持多段线,每一段的特征描述
#define SGF_SYMMODE        "SYMMODE"           //线对象挂接符号模式
#define SGF_LINE			"LINE"				//所属线路
#define SGF_LINETYPE		"LINETYPE"			//所属线路类型
#define SGF_GDB_NO			"GDB_NO"			//空间引擎号
#define SGF_GDE_NO			"GDE_NO"			//空间引擎号

#define SGF_FNODE			"FNODE"				
#define SGF_TNODE			"TNODE"				
#define SGF_PEN_WIDTH		"PEN_WIDTH"			
#define SGF_PEN_ATTRIB		"PEN_ATTRIB"		
#define SGF_BRUSH_ATTRIB	"BRUSH_ATTRIB"
#define SGF_EXTATTRIB		"EXT_ATTRIB"		//扩展的内存属性

#define SGF_SYM			"OBJ_SYM"			//对象符号
#define	SGF_SYMTYPE		"SYMTYPE"			//符号子类型
#define SGF_SYM_PART		"SYM_PART"			//对象符号
#define SGF_SUBTYPE		"SUBTYPE"			//对象子类型
#define SGF_SIZE			"OBJ_SIZE"			//对象大小
#define SGF_ANGLE			"OBJ_ANGLE"			//对象角度
#define SGF_OBJECTSTATUS	"STATUS"			//对象状态
#define SGF_DATAFROM		"DFROM"				//数据来源
#define SGF_TRANSPARENT    "TRANSPARENT"       //透明度
#define SGF_REMARK			"REMARK"		   //备注
#define SGF_SUBLAYER		"SUBLAYER"			//图层	

#define SGF_RUN_STATUS		"RUN_STATUS"
#define SGF_SECTION_ID		"SECTION_ID"
#define SGF_VISIBLE			"VISIBLE"
#define SGF_STANDARD		"STANDARD"
#define SGF_HOLEROWS		"HOLEROWS"
#define SGF_HOLECOLS		"HOLECOLS"
#define SGF_PTYPE			"PTYPE"
#define SGF_PID				"PID"
#define SGF_BAY				"BAY"
#define FIELD_LINE			"LINE"
#define FIELD_LVLINE		"LVLINE"
#define SGF_USAGE			"USAGE"
#define SGF_STARTX			"START_X"
#define SGF_STARTY			"START_Y"
#define SGF_ENDX			"END_X"
#define SGF_ENDY			"END_Y"
#define SGF_RUNSTATUS		"RUN_STATUS"
#define	SGF_DIAMETER		"DIAMETER"	//孔径
#define SGF_WIDTH			"WIDTH"		//宽度
#define SGF_VELOCITY		"VELOCITY"		//速度
#define SGF_DATETIME		"GETTIME"
#define SGF_ANGLE          "OBJ_ANGLE"		//角度
#define SGF_X				"POS_X"
#define SGF_Y              "POS_Y"
#define SGF_GRIDNUMS		"GRDROWS"

#define SGF_RUNSTYLE		"DEF_STATUS"
#define SGF_FLAG			"FLAG"				
#define SGF_STATUS			"STATUS_"				
#define SGF_SYM_STATE		"STATE"					//符号等的状态字段
//#define SGF_PROJECTID		"PROJECTID"				//版本控制工程号字段
#define SGF_PROJECT			"PROJECT"				//版本控制工程号字段
#define SGF_STEP			"STEP_"				//当前操作步骤
#define SGF_ELEM_INFO		"ELME_INFO"			//复杂线对象，各段线的实体类型

#define SGF_BASEOBJECTTYPE		"BASE_OBJ_TYPE"		//基础对象类型号在其它表中出现时的域名
#define SGF_BASEOBJECTID		"BASE_OBJ_ID"		//基础对象内控ID在其它表中出现时的域名
#define SGF_BASEOBJECTIDS		"BASE_OBJ_IDS"		//基础对象类型号在其它表中出现时的域名
#define SGF_CONTAINERTYPE		"CONTAINER_OBJ_TYPE"//容器对象类型号在其它表中出现时的域名
#define SGF_CONTAINERID			"CONTAINER_OBJ_ID"	//容器对象内控ID在其它表中出现时的域名
#define SGF_SRC_OBJECT_TYPE		"SRC_OBJECT_TYPE"	//对象类型号在其它表中出现时的作为源域名
#define SGF_DEST_OBJECT_TYPE	"DEST_OBJECT_TYPE"	//对象类型号在其它表中出现时的作为目标域名

#define SGF_MODEL_REL_SRCTYPE		"SRCTYPE"
#define SGF_MODEL_REL_DESTTYPE		"DESTTYPE"

#define SGF_BE_BASEOBJECTTYPE		"BE_BASE_OBJ_TYPE"		//被跨越对象类型
#define SGF_BE_BASEOBJECTID			"BE_BASE_OBJ_ID"		//被跨越对象ID
#define SGF_SPAN_DISTANCE			"SPAN_DISTANCE"			//跨越距离

#define SGF_POS						"FIELD_POS"			//内值存放表信息中字段的偏移量

#define SGF_KERNEL_OBJID			"ID"				//对象内部ID
#define SGF_FID						"FID"			//对象内部父对象ID
#define SGF_PART_INDEX				"PART_INDEX"		//对象内部部件编号

#define SGF_TOPO_RULE		"RULE"	
#define SGF_GWPOERFLAG		"ISPOWER"
//-----------------------------------------------------------------------------------------------------------
// 请注意该宏仅在版本服务调试时使用，到现场使用时需要删除该宏
#define USE_GRP_VERSION

#define SGF_WORLDID		"WORLDID"			//对象所在的世界号
#define SGF_UNIVERSEID		"UNIVERSE"			//世界号所在的Universe号
#ifdef USE_GRP_VERSION
#define SGF_WORKSPACE		"WORKSPACE"			//对象所在的WorkSpace号
#else
#define SGF_WORKSPACE		"TASKID"			//对象所在的WorkSpace号
#endif
#define SGF_COMPANY		"COMPANY"			//公司
#define SGF_DEPT				"DEPT"				//部门

#define SGF_FUNCSTR		"FUNC_STR"			//多意功能字符串
#define SGF_PHASEORDER		"PHASEORDER"		//相序
#define SGF_PHASE			"PHASE"				//相位
#define	SGF_DISPORDER		"DISP_ORDER"	
#define SGF_ORDER			"ORDER_"			//	

#define SGF_GISLEN			"GISLEN"			//图形提取的长度
#define SGF_CALGTH			"CALLEN"			//计算长度
#define SGF_LEN				"LENGTH"			//线设备长度字段名
#define SGF_TOTALLEN		"TOTAL_LENGTH"		//线(组合)设备长度字段名
#define SGF_AREA_TYPE		"AREA_TYPE"			//设备区域类型

#define SGF_TYPEID			"TYPEID"			//型号ID
#define SGF_STYLE          "STYLE"             //样式
#define SGF_THICKNESS      "OBJ_SIZE"         //厚度或深度
#define SGF_PENSTYLE       "PENSTYLE"          //画笔
#define SGF_BRUSHSTYLE     "BRUSHSTYLE"         //画刷

#define SGF_STARTOBJINFO	"STARTOBJINFO"			//系统提取的起始对象的描述信息
#define SGF_ENDOBJINFO		"ENDOBJINFO"			//系统提取的终止对象的描述信息

#define SGF_COLOR			"COLOR"					//系统缺省的颜色字段名称
#define SGF_VOLT_CODE		"VOLT_CODE"			//系统电压等级字段名称
#define SGF_STOPFLAG		"STOPFLAG"				//系统"停运"字段名称
#define SGF_SCALE          "SCALE"                 //变电站内尺寸的比例值

#define SGF_CAL_STATUS		"CAL_STATUS"		//计算状态 标识是运行态还是模拟态

#define	SGF_START_OBJ_TYPE		"START_OBJ_TYPE"
#define	SGF_START_OBJ_ID		"START_OBJ_ID"
#define	SGF_END_OBJ_TYPE		"END_OBJ_TYPE"
#define	SGF_END_OBJ_ID			"END_OBJ_ID"
#define	SGF_TMP_APPTYPE		"APP_TYPE"			//临时对象应用类型

#define  SGF_LINES			"LINES"				//专题图关联的线路
#define  SGF_XTT_ID			"XTT_ID"			//供电区域关联的系统图对象
//离线图转换扩展属性表的字段
#define	SGF_RULE_ID             "RULE_ID"      //规则ID      
#define	SGF_RULE_INDEX          "RULE_INDEX"   //同一个ID的索引
#define	SGF_DESCRIBE            "DESCRIBE"     //描述
#define	SGF_FIELD_TYPE	         "FIELD_TYPE"   //字段类型 
#define	SGF_FIELD_NAME          "FIELD_NAME"   //字段名称
#define	SGF_FIELD_LEN           "FIELD_LEN"    //字段长度
#define	SGF_FIELD_PRE           "FIELD_PRE"    //字段精确度

// --- 实时库相关的字段系统级别固定名称
#define	SGF_VALUE			"VALUE"			//遥测遥信的值
#define	SGF_TYPE			"TYPE"			//遥测遥信的类型
#define	SGF_ATTRIB			"ATTRIB"		//遥测遥信的属性
#define	SGF_MANSETF		"MANSETF"		//遥测遥信的为置数标记
#define	SGF_CONVFACT		"CONV_FACT"		//遥测的显示转换系数

#define	SGF_GRD_ATTRIB		"GRD_ATTRIB"	//接地性质

#define SGF_DESIGNINFO		"SHOWDESIGNINFO"
#define SGF_TXT_ALIGN		"ALIGN"
//内存库中扩充的用来记录带电状态或开关状态发生变化的字段
#define SYS_FIELD_CHANGEF		"CHANGEF"
//版本相关的定义
#define SG_VERSION_CONSTANT			1000000000			//定义版本常量到客户端
#define SGF_VERSION_INFO			"MODEL_VER_FLAG"		//元数据是否注册版本信息
#define SGF_VERRULE					"MODEL_VER_RULE"		//版本规则定义表
#define SGF_AD_ID				"AD_KID"				//A/D表的唯一索引
#define SGF_DEL_BKID			"KID"				//在D表中记录删除对象的kid
#define	SGF_VERID				"GIS_VERID"				//版本号
#define	SGF_ADDFLAG			"ADDFLAG"				//新增记录标志
#define SGF_TASKID				"TASKNO"				//A/D表中的任务号
#define	SG_VERSION_TBLNAME			"GIS_SYS_VERSION_EDIT"    //版本信息表的名称
#define SGF_VER_ID				"KID"				//对象内控ID域名

#define VERNO_CANCOMMIT 1 //定义可以提交的版本号
#define TSRV_CUR_SRVNO		0 //定义时态版本的当前服务器的服务器号

#define  SGF_CODE			"CODE"
#define  SGF_USERCODE		"USERCODE"
/******************************************
	Part 60 系统控制域名定义----元数据部分
******************************************/
//设备对象的元数据表
#define SG_SYS_METADATA_TABLE			"EM_SYS_VARIABLE"
#define	SG_SYS_METADATA_F_VALUE			"VALUE"
#define	SG_SYS_METADATA_F_SUBTYPE			"SUBTYPE"

//系统表注册表
#define	SG_SYS_TABLE		"SYS_TABLE_REG"
#define	SG_SYS_T_ID			"ID"
#define	SG_SYS_T_NAME		"NAME"
#define	SG_SYS_T_DESC		"DESCR"
#define	SG_SYS_T_TYPE		"TYPE"
//系统域注册表
#define	SG_SYS_FIELD				"SYS_FIELD_REG"
#define	SG_SYS_F_TABLEID			"TABLE_ID"
#define	SG_SYS_F_ID	 				"ID" 		
#define	SG_SYS_F_NAME 				"NAME" 		
#define	SG_SYS_F_DESC				"DESCR" 		
#define	SG_SYS_F_TYPE				"TYPE" 		
#define	SG_SYS_F_LENGTH	 			"LENGTH" 	
#define	SG_SYS_F_DECIMAL 			"PRECISE" 	
#define	SG_SYS_F_DISPWIDTH 			"DISP_WIDTH" 	
#define	SG_SYS_F_ISKEYWORD			"KEYWORD_FLAG"
#define	SG_SYS_F_WRITEABLE			"WRITEABLE" 
#define	SG_SYS_F_VISIBLE 			"VISIBLE" 	
#define	SG_SYS_F_ISOBJNAME			"OBJNAME_FLAG" 
#define	SG_SYS_F_INPUTMODE 			"EDIT_RULE" 
#define SG_SYS_F_FUNCSTR			"FUNC_STR"
#define SG_SYS_F_DISPORDER			"DISP_ORDER"
#define SG_SYS_F_NOVERSION			"NOVERSION"
#define SG_SYS_F_MANDATORY          "BIZ_FLAG"
#define SG_SYS_F_DISPATCHATTR       "RUN_FLAG"
//表的字段扩充信息
#define	SG_SYS_FIELD_EXTRA			"SYS_FIELD_REG_EX"
#define	SG_SYS_F_E_ID				"ID" 				
#define	SG_SYS_F_E_TABLEID			"TABLE_ID" 			
#define	SG_SYS_F_E_SOURCETABLENAME	"CODE_TABLE" 	
#define	SG_SYS_F_E_INFOFIELDNAME	"VAL_FIELD" 	
#define	SG_SYS_F_E_DESCFIELDNAME	"DESC_FIELD" 	
#define	SG_SYS_F_E_HASCONDITION		"FILTER_FLAG"
//对象&域对象包含关系表 	
#define	SG_SYS_FIELD_OBJECT			"SYS_OBJECT_FIELD"
#define	SG_SYS_F_O_OBJTYPE			SGF_OBJECTTYPE
#define	SG_SYS_F_O_FIELDNAME		SGF_OBJECTNAME
#define	SG_SYS_F_O_FIELDID			SG_SYS_SUB_D_FIELDID
//系统DoMain表	
#define	SG_SYS_DOMAIN_TABLE			"SYS_CODE_DEF"
#define	SG_SYS_DOMAIN_TYPE			"SYS_CODE_CATEGORY"
#define	SG_SYS_D_DOMAIN_TYPE_ID		"CATE_ID"
#define	SG_SYS_D_CODEID				"CODE_ID"		
#define	SG_SYS_D_DISPVALUE			"CODE_VAL" 
#define SG_SYS_D_CALCVALUE			"CAL_VAL"
#define	SG_SYS_D_ENABLED			"ENABLED"
#define	SG_SYS_D_DISABLED			"DISABLED"
//系统 子DoMain 表
#define	SG_SYS_SUB_DOMAIN_TABLE		"SYS_FIELD_SUB_DOMAIN"
#define	SG_SYS_SUB_D_FIELDID		"FIELD_ID"
#define	SG_SYS_SUB_D_CTRL_VALE		"CONTROL_FIELD_VALUE"
#define	SG_SYS_SUB_D_CODE_VALUE		"CODE_ID"
//系统关联控制字段表
#define SG_SYS_RELATE_CTRL_TABLE	"SYS_FIELD_RELATE_CTRL"
#define	SG_SYS_SRC_FIELD_ID			"SRC_FIELD"
#define	SG_SYS_DEST_FIELD_ID		"DEST_FIELD"
#define SG_SYS_CTRL_STR				"CTRL_STR"
//系统Object Relation表	
#define	SG_SYS_OBJECT_RELATION_TABLE	"SYS_MODEL_RELATION"
#define	SG_SYS_OR_BEHAVIOUR			"RULE"			//对象关系行为
#define SG_SYS_OR_FIELD				"PID"		//关联字段ID --- FM表中
#define SG_SYS_OR_NRELATION			"REL_NUM"			//关系维数
#define SG_SYS_OR_SPATIALFIELD		"GEO_FIELD"	//关联字段名 --- SDE表中
#define SG_SYS_OR_SRC_MOEL			"SRC_MODEL"
#define SG_SYS_OR_GEO_PTYPE			"GEO_PTYPE"
//系统Object Size表	
#define	SG_SYS_OBJECTSIZE_TABLE		"SYS_OBJECTSIZE"
//系统"电源点"对象	
//#define	SG_SYS_POWERPOINT_TABLE "GIS_SYS_POWER_SOURCE"
//系统线路颜色表	
#define	SG_SYS_VOLTCOLOR_TABLE		"GIS_SYS_VOLT_COLOR"
//系统非对象表	
#define	SG_SYS_NOTOBJECT_TABLE		"SYS_OBJECT_NO"
//系统Object表	
#define	SG_SYS_OBJECT_TABLE			"SYS_MODEL"
#define	SG_SYS_O_ENABLEED			"ENABLEED"
#define	SG_SYS_O_BASE_FEATURE_TYPE	"GEO_TYPE"		
#define	SG_SYS_O_LOAD_USE_WORLDID	"WORLD_LOAD_FLAG"		
#define	SG_SYS_O_UNIVERSE_VIEW		"UNIVERSE_VIEW"		
#define	SG_SYS_O_OBJECT_APPTYPE		"MODEL_INST"		
#define	SG_SYS_O_BE_EDIT			"BE_EDIT"		
#define	SG_SYS_O_BE_START_OBJECT	"START_FLAG"		
#define	SG_SYS_O_BE_QUERYSTATISTIC	"QUERY_FLAG"		
#define	SG_SYS_O_NETWORK_TYPE		"TOPO_NETWORK"		
#define	SG_SYS_O_LOAD_RANGE			"LOAD_RANGE"		
#define	SG_SYS_O_INSIDE_ATTIB_FLAG				"REAL_ATTIB_FLAG"			//数据库结构不对--以后统一修改正???
#define SG_SYS_O_MODEL_VOLT			"MODEL_VOLT"
#define GIS_SYS_MULTILINE_DEVICE "GIS_SYS_MULTILINE_DEVICE"
//
#define	SG_SYS_OBJECT_TABLE_EXT		"SYS_GDE_PARA"
#define	SG_SYS_OEXT_SERVER_NO			"SERVER_ID"
#define	SG_SYS_OEXT_LOAD_SEQUENCE       "ORD"
#define	SG_SYS_OEXT_SDE_LOADTYPE        "GEO_RULE"
#define	SG_SYS_OEXT_SDE_FUNCSTR         "GEO_RULE_EX"
#define	SG_SYS_OEXT_TABLE_LOADTYPE      "ATT_RULE"
#define	SG_SYS_OEXT_TABLE_FUNCSTR       "ATT_RULE_EX"
#define	SG_SYS_OEXT_CELL_SIZE           "GRID_SIZE"
#define	SG_SYS_OEXT_USE_CELL_RANGE      "GRID_RANGE"
#define	SG_SYS_OEXT_VISIBLE_MAXRANGE    "VISIBLE_MAXRANGE"
#define	SG_SYS_OEXT_VISIBLE_MINRANGE    "VISIBLE_MINRANGE"
#define	SG_SYS_OEXT_LABEL_MAXRANGE		"LABEL_MAXRANGE"
#define	SG_SYS_OEXT_LABEL_MINRANGE		"LABEL_MINRANGE"

//对象视图控制表
#define SG_SYS_OBJECT_UNIVSER_TABLE		"SYS_OBJECT_UNIVERSE"
#define SGF_UNIVERSE					"UNIVERSE"

//#define	SG_SYS_O_TRIGGER_CANTAINER_TYPE		"TRIGGER_CANTAINER_TYPE"	//不再出现此域--以后统一修改正???
#define	SG_SYS_O_SELECT_PRIORITY				"SELECT_PRIORITY"
#define	SG_SYS_O_ACTIVE_CENTER_FLAG				"MODEL_CENTER_RULE"
#define	SG_SYS_O_ACTIVE_CENTER_RANGE			"MODEL_CENTER_RANGE"
#define	SG_SYS_O_TROUBLE_VIEW_EXTENT			"TROUBLE_VIEW_EXTENT"
#define	SG_SYS_O_VISIBLE_RANGE					"VISIBLE_RANGE"
#define	SG_SYS_O_POWER_ATTRIB					"POWER_ATTRIB"
#define	SG_SYS_O_ELECTRIC_TYPE					"ELECTRIC_TYPE"
#define	SG_SYS_O_DEVICE_CATEGORY				"DEVICE_CATEGORY"
#define	SG_SYS_O_DRAW_GRAPH_RULE				"DRAW_GRAPH_RULE"
#define	SG_SYS_O_FIXED_POINT_ATTRIB				"FIXED_POINT_ATTRIB"
#define	SG_SYS_O_AUTO_HORZ_VERT					"AUTO_HORZ_VERT"
#define	SG_SYS_O_SPAN_RULE						"SPAN_RULE"
#define	SG_SYS_O_CAN_SPLIT_EDGE					"SPLIT_FLAG"
#define	SG_SYS_O_CAN_SNAP_EDGE					"SNAP_FLAG"
#define	SG_SYS_O_TOPO_BARRIER_TYPE				"TOPO_RULE"
#define	SG_SYS_O_IMG_INDEX						"IMG_INDEX"
#define	SG_SYS_O_SELECTED_IMG_INDEX				"SELECTED_IMG_INDEX"
#define	SG_SYS_O_TOOLBOX_CLASS					"TOOLBOX_CLASS"
#define	SG_SYS_O_TOOLBOX_POSITION				"TOOLBOX_POSITON"
#define	SG_SYS_O_CAN_MOVE_ROTATE				"MOVE_ROTATE_FLAG"
#define	SG_SYS_O_SELECT_METHOD_POINT			"POINT_SEL_RULE"
//#define	SG_SYS_O_INHERIT_INVISIBLE_CONTAINER	"INHERIT_INVISIBLE_CONTAINER"	
//#define	SG_SYS_O_AUTO_TRIGGER_OBJECT			"AUTO_TRIGGER_OBJECT"
//#define	SG_SYS_O_INTERSECT_TYPE				"INTERSECT_TYPE"
#define	SG_SYS_O_SELECT_METHOD_LINE				"REGION_SEL_RULE"
#define	SG_SYS_O_HAS_EDGE_ATTRIB				"COMPLEX_EDGE_FLAG"
#define	SG_SYS_O_CAN_BE_SPLIT					"SPLITED_FLAG"
#define	SG_SYS_O_POWERON_OPER_FLAG				"LOAD_OPER_FLAG"
#define	SG_SYS_O_SYMBOL_DISP_ATTRIB				"SYMBOL_RULE"
#define	SG_SYS_O_SYMBOL_ENLARGE_MODE			"SYMBOL_ZOOM_RULE"
#define	SG_SYS_O_SPATIAL_DS_TYPE				"GEO_DB_TYPE"
#define	SG_SYS_O_SPATIAL_DS_INFO				"GEO_DB_NO"
#define	SG_SYS_O_SPATIAL_DS_TABLE_NAME			"GEO_TBL"	
#define	SG_SYS_O_SPATIALORDER					"MODEL_ORDER"
#define	SG_SYS_O_ATTR_DS_TYPE					"ATTR_DB_TYPE"	
#define	SG_SYS_O_ATTR_DS_INFO					"ATTR_DB_NO"
#define SG_SYS_O_VER_TABLE_NAME					"ATTR_VER_TBL"	
#define	SG_SYS_O_ATTR_TABLE_NAME				"ATTR_TBL"
#define	SG_SYS_O_KEY_INFO_VIEW_NAME				"SYNC_VIEW"	
#define	SG_SYS_O_SYNC_MODE						"SYNC_MODE"
#define SG_SYS_O_DATA_MODE						"DATA_MODE"
//#define	SG_SYS_O_QUERY_VIEW1					"QUERY_VIEW1"	
//#define	SG_SYS_O_QUERY_VIEW2					"QUERY_VIEW2"	
//#define	SG_SYS_O_QUERY_VIEW3					"QUERY_VIEW3"	
//#define	SG_SYS_O_ID_RANGE_START					"ID_RANGE_START"	
//#define	SG_SYS_O_ID_RANGE_END					"ID_RANGE_END"	
//#define	SG_SYS_O_EDITOR_CLASS					"EDITOR_CLASS"	
#define SG_SYS_O_DEFAULT_VALUE                  "DEFAULTVALUE"
#define SG_SYS_O_OPER_ATTRIB	                "OPER_ATTRIB"
#define SG_SYS_O_HAS3D			                "HAS3D"
#define SG_SYS_O_LABELCOLORBYVOLT				"LABELCOLORBYVOLT"

//系统单位信息配置表
#define SG_SYS_COMPANY_TABLE					"SYS_COMPANY"
#define EM_GDE_PARA_TABLE						"VW_GDE_PARA"
#define SG_SYS_COMPANY_F_HAS_SCADA				"HAS_SCADA"
//设备树配置表
#define SG_SYS_OBJ_TREE							"SYS_OBJECT_TREE"
#define SG_SYS_OBJECT_TREE_TYPE					"SYS_OBJECT_TREE_TYPE"
#define	SG_SYS_O_T_TREE_NAME					"TREE_NAME"
//菜单登记表
#define _SG_MENU_TABLE_NMAE						"SYS_RIGHT_MENU"
//运行方式属性表
#define SG_SYS_RUN_STYLE_TABLE					"SYS_RUN_STYLE"
//???CASETOOL中用???
#define SGF_RULE_TABLE					"SYS_FIELD_RULE"
#define SGF_RULE_OBJTYPE				"OBJECT_TYPE"
#define SGF_RULE_FIELDS				"FIELDS"
#define SGF_RULE_RULETYPE				"RULE_TYPE"
//

#define GIS_SYS_OBJ_SYM_TABLE					"SYS_MODEL_SYMBOL"
#define GIS_SYS_SYMBOL_DEF						"SYS_SYMBOL_DEF"
#define GIS_SYS_SYMBOL_UNIT						"SYS_SYMBOL_UNIT"
#define GIS_SYS_ANGLE_CONTROL					"GIS_SYS_ANGLE_CONTROL"
#define	GIS_SYS_WORLD							"GIS_SYS_WORLD"
#define GIS_SYS_PRINT_TEMPLATE					"GIS_SYS_PRINT_TEMPLATE"
#define GIS_SYS_PRINT_TEMPLATE_TEMP				"GIS_SYS_PRINT_TEMPLATE_TEMP" //在数据库中不需要建表,表结构同GIS_SYS_PRINT_TEMPLATE
#define	GIS_SYS_LABEL_MANAER					"GIS_SYS_LABEL_MANAER"
#define _SG_GOTO_STRATEGY_TABLE					"GIS_SYS_GOTO_STRATEGY"
//#define GIS_SYS_VERSION_MANAGER				"GIS_SYS_VERSION_MANAGER" //当前没有用，数据库中也无对应的表
#define TASK_TABLE								"GIS_SYS_TASK"
#define TASK_BLOCK_TABLE						"GIS_SYS_TASK_BLOCK"
#define EMPLOYEE_WORKSPACE_TABLE				"R_EMPLOYEE_WORKSPACE"
#define GIS_SYS_EQUIP_RTN_ATTRIB				"GIS_SYS_EQUIP_RTN_ATTRIB"
#define GIS_SYS_MANSET_MASK						"GIS_SYS_MANSET_MASK"
#define GIS_SYS_COMMON_TABLE					"GIS_SYS_COMMON_TABLE"
#define GIS_SYS_SCADA_TYPE						"GIS_SYS_SCADA_TYPE"
#define	SG_GIS_SYS_TEMPLATE_TABLE				"GIS_SYS_TEMPLATE"
#define GIS_SYS_SCHEMATICS_GRID					"GIS_SYS_SCHEMATICS_GRID"
//#define PHASE_TABLE_NAME						"GIS_SYS_PAHSE" //程序中没有用到相关的代码
#define SG_GIS_EVNET_TABLE						"EM_REAL_EVENT"
#define GIS_SYS_BKGRD_NAME_CATEGORY				"EM_BKGRD_NAME_CATEGORY"
#define GIS_SYS_BKGRD_NAME						"EM_BKGRD_NAME"
#define	GIS_SYS_BKGRD_BLOCK						"EM_BKGRD_BLOCK"
#define GIS_SYS_BKGRD_DSP_SETTING				"EM_BKGRD_DSP_SETTING"
#define GIS_SYS_BKGRD_BLOCK_FUTURE				"EM_BKGRD_BLOCK_FUTURE"
#define	SG_JSJZ_DISP_TABLE						"EM_JSJZ_CONFIG" //程序中用到了，但基本不用配置

#define GIS_SYS_SYMBOL_							"GIS_SYS_SYMBOL_"
#define GIS_SYS_PHASE							"GIS_SYS_PHASE"
#define GIS_SYS_USALQUERY						"GIS_SYS_USALQUERY"
#define GIS_SYS_UNIVERS_BOUND					"GIS_SYS_UNIVERS_BOUND"
#define GIS_SYS_MMI_ATTENTION					"EM_MMI_ATTENTION"
#define GIS_SYS_CAR								"EM_GPS_CAR"
#define SG_PUBLISH_FILE_INFO					"EM_PUBLISH_FILE_INFO"
#define SG_PUBLISH_CATE_INFO					"EM_PUBLISH_CATE_INFO"

#define SG_SYS_FIELDGRP_TALBE					"EM_OBJ_GROUPNAME"
#define SG_SYS_F_GRP_INDEX						"GROUP_INDEX"
#define SG_SYS_F_GRP_NAME						"GROUP_NAME"
//
//客户端加载控制
#define GIS_SYS_APP_MODEL					"EM_APP_OBJ_MODEL_TABLE"
#define SG_SYS_APP_OBJECT_TABLE				"GIS_SYS_APP_OBJ_MODEL_VIEW"
#define SG_SYS_APP_OBJECT_TABLE_EXT			"GIS_SYS_APP_OBJECT_EXT_VIEW"
//
#define SG_SYS_O_APP_TYPE						"APP_TYPE"
#define SG_SYS_O_CLIENT_LOAD_SOURCE				"LOAD_SOURCE"
#define SG_SYS_O_CLIENT_FILTER					"FILTER"
#define SG_SYS_O_SEQUENCE_NAME					"MODEL_SEQ"

#define	SG_SYS_OBJECT_TOPO_RULE				"SYS_OBJECT_TOPO_RULE"

/******************************************
	Part 70 系统控制域名定义----GIS的系统级表
******************************************/
//GIS Object 符号表	
//#define	GIS_SYS_OBJ_SYM_TABLE			"GIS_SYS_OBJ_SYM"
#define	SGF_OBJSYM_SUBTYPE			"SUB_TYPE"
//GIS Object 挂牌符号属性表	
#define	GIS_SYS_SIGN_ATTRIB_TABLE		"GIS_SYS_SIGN_ATTRIB"
//GIS Object 设备挂牌屏蔽表	
#define	GIS_SYS_OBJSIGN_MASK_TABLE		"GIS_SYS_OBJ_SIGN_RELATION"
//GIS Object 遥测属性表	
#define	GIS_SYS_YC_ATTRIB_TABLE			"EM_YC_DEF"
//GIS Object 遥测基础表
#define GIS_SYS_YC_BASE_TABLE           "EM_YC_BASE"
//GIS Object 遥信基础表
#define GIS_SYS_YX_BASE_TABLE           "EM_YX_BASE"
//GIS Object 对象子类型例外控制表	
#define	GIS_SYS_SUBTYPE_EXCEPT_TABLE	"GIS_SYS_SUBTYPE_EXCEPT"
//Sys Object 对象显示配置表
#define SG_SYS_DISP_CONFIG_TABLE		"SYS_DISP_CONFIG"
#define SG_SYS_DISP_SCHEME_TABLE		"SYS_DISP_SCHEME"
#define	SGF_SUBTYPE_OPERLOAD		"CANOPERLOAD"
#define SGF_SUBTYPE_OPERFLAG		"CANOPER"
#define SGF_DEFEALT_VAL			"DEFAULT_VAL"

#define SG_SYS_UNIVERSE_SCALE_TABLE		"GIS_SYS_UNIVERSE_SCALE"
#define SG_GEOG_XTT_OBJ_MAP		"GEOG_XTT_OBJ_MAP"

//设备类型与遥测类型对应表
#define GIS_SYS_OBJ_YC_TYPE			   "GIS_SYS_OBJ_YC_TYPE"
#define SGF_YC_TYPE				"YC_TYPE"
#define SGF_YC_DESC				"YC_DESC"

//通用扩展设备对象的设备类型和子类型对应表
#define SG_SYS_OBJECT_SUBOBJTYPE		"SYS_OBJECT_SUBOBJTYPE"
//符号图元和量侧类型对应表
#define SG_RDP_MEASTYPE_SYMBOL			"EM_RDP_MEASTYPE_SYMBOL"
#define SGF_MEASTYPE_ID			"MEASTYPE_ID"
//STATUS_BIT_NO字段，描述符号的Status位序号
#define	SGF_STATUS_BIT_NO			"STATUS_BIT_NO"

// --- 离线图模板表
#define SG_SYS_OFFLINEMAP_MODEL_TABLE	"SYS_OFFLINEMAP_MODEL"
//离线图转换扩展属性表
#define SG_SYS_OFFLINEMAP_MODEL_EXT_TABLE	"SYS_OFFLINEMAP_MODEL_EXT"
//设备组模板表
#define	SG_COMBIN_DEVICE_TEMPLATE			"EM_COMBIN_DEVICE_TEMPLATE"
#define SG_TEMPLATE_IMAGEDATA               "TEMPLATE_IMAGEDATA"
//
#define SG_SYS_OLMM_MODEL_ID			"MODEL_ID"
#define SG_SYS_OLMM_ATTRIB_FIELDS		"ATTRIB_FIELDS"

//
#define SG_GIS_COMBIN_TEMPLATE				"GEO_COMBIN_TEMPLATE"
#define EM_OBJLABEL_TABLE					"EM_OBJLABEL"

//营销用户信息表
#define CIS_USER_INFO		"CIS_USER_INFO"
#define CIS_USER_METER		"CIS_METER_INFO"
#define CIS_USER_METER_VIEW "CIS_USER_METER_VIEW"
//报表定义表
#define REPORT_MAIN_TABLE	"EM_REPORT"  //主表
#define REPORT_DETAIL_TABLE	"EM_REPORT_DETAIL"    //从表

//（设备类型展示用）设备分组分类信息表
#define OBJ_GROUP_CAT_TABLE			"GIS_SYS_OBJ_GROUP_CATEGORY"
#define OBJ_GROUP_CAT_FIELD_CAT		"CATID"
#define OBJ_GROUP_CAT_FIELD_GROUP	"GROUPID"
//（设备类型展示用）设备分组信息表
#define OBJ_GROUP_TABLE				"GIS_SYS_OBJ_GROUP"
#define OBJ_GROUP_FIELD_GROUP		"GROUPID"
//设备分组加载表
#define GIS_SYS_LOADCONTRAL			"GIS_SYS_LOADCONTRAL"
#define GROUP_TYPE					"GROUPTYPE"
#define APP_TYPE					"APPTYPE"
#define START_BIND					"START_BIND"
#define START_EXCLUDE				"START_EXCLUDE"
#define LOAD_GROUP					"LOAD_GROUP"
//环境配置表
#define SG_TBL_SYS_ENVIRONMENT		"SYS_ENVIRONMENT"
#define SG_TBL_GIS_ENVIRONMENT		"GIS_SYS_ENVIRONMENT"
//和方案版本相关的表
#define SG_TABLE_TASK           "EP_TASK"                   //规划任务表
#define SG_TABLE_SCHEME			"EP_PLAN"					//规划方案表
#define	SG_TABLE_PROJECT		"EP_PROJECT"				//规划项目表
#define	SG_TABLE_MISSION		"SYS_MISSION"	            //项目任务表
#define	SG_TABLE_SCHEME_PRJ		"R_PLAN_PROJECT"				//方案项目表
#define	SG_TABLE_SCHEME_MISSION	"R_PLAN_MISSION"				//方案任务表
#define	SG_TABLE_MISSION_GRANT	"SYS_MISSION_GRANT"		//任务授权表
#define SG_TABLE_WORLD_TSRV		"GIS_SYS_WORLD_TSRV"		//存入时态服务的WORLD表
#define	SG_TABLE_TASK_CHKPOINT	"GIS_SYS_MISSION_CHECKPOINT"	//GAP任务检查点表

#define SG_TABLE_COMMIT_ITEMLOG	"EM_GIS_COMMIT_ITEMLOG"
#define SG_TABLE_COMMIT_LOG		"EM_GIS_COMMITLOG"
#define SG_TABLE_NAMECHANGE		"EM_GIS_NAMECHANGE"
#define SG_TABLE_VERLOG			"EM_GIS_VERLOG"
//
#define SG_TABLE_SG_FM_PICTURE   "EM_ATTACH_PICTURE"
#define SG_TABLE_SG_FM_FILE      "EM_ATTACH_FILE"
#define SG_TABLE_ATTACH         "EM_ATTACH"
#define SG_TABLE_ATTACH_DETAIL  "EM_ATTACH_DETAIL"
//
#define SGF_FILENAME        "FILENAME"
#define SGF_FILECONTENT     "FILECONTENT"
#define SGF_REMARK          "REMARK"


#define SGF_ATTACH_FILENAME       "FILE_NAME"
#define SGF_ATTACH_FILEEXT        "FILE_EXT"
#define SGF_ATTACH_OPRTID         "OPRT_ID"
#define SGF_ATTACH_OPRTTIME       "OPRT_TIME"
#define SGF_ATTACH_DATA           "DATA"

#define SGF_GIS_STARTYMD	"START_YMD"	 //开始时间字段
#define SGF_GIS_ENDYMD		"END_YMD"	 //结束时间字段
#define SGF_GIS_STATUS		"STATUS"	 //状态字段
#define SGF_GIS_PLAN        "PLAN"       //规划方案
#define SGF_GIS_PROJECT		"PROJECT"	 //规划项目

#define SGF_GIS_SCHEME		"SCHEME_ID"	 //方案字段
#define SGF_GIS_SUBTASKID	"SUBTASKNO"		//任务方案字段
#define SGF_GIS_GRTTASKID	"GRANT_TASKNO"		//获得授权的任务字段
#define SGF_GIS_DEFTASKID	"DEFAULT_TASKNO"		//缺省的任务方案
#define SGF_GIS_TYPECODE	"TYPE_CODE"		//方案类型编码
#define SGF_GIS_BASEYR		"BASE_YR"		//基准年

#define SPATIAL_OBJECTID             "OBJECTID"

//重要的电系参数字段定义
#define SGF_RATED_CAPACITY	"RATED_CAPACITY"	//额定容量
#define SGF_RATED_L		"RATE_L"			//额定低压容量
#define SGF_RATED_M		"RATE_M"			//额定中压容量
#define SGF_MODEL			"MODEL"				//型号

//电站相关
#define SGF_FLOORSPACE		"FLOOR_SPACE"		//占地面积

//显示配置相关字段
#define SGF_DISP_MINSCALE		"MIN_SCALE"
#define SGF_DISP_MAXSCALE		"MAX_SCALE"
#define SGF_DISP_COLOR			"COLOR"
#define SGF_DISP_SUBFIELD		"SUB_FIELD"
#define SGF_DISP_LINEWIDTH		"LINE_WIDTH"
#define SGF_DISP_SHOWASPOINT	"SHOW_AS_POINT"
#define SGF_DISP_FILLCOLOR		"FILL_COLOR"
#define SGF_DISP_LABELSCALE		"LABEL_SCALE"
#define SGF_DISP_LABELFONT		"LABEL_FONT"
#define SGF_DISP_LABELCORLOR	"LABEL_COLOR"
#define SGF_DISP_OBJLABELSCALE	"OBJ_LABEL_SCALE"


//管道孔位的字段
#define SGF_DIRECTION				"DIRECTION"  //电缆截面方向字段
#define SGF_ROWNO					"ROWNO"		//行号
#define SGF_COLNO					"COLNO"		//列号
#define SGF_DESCRIB					"GISDESC"  //描述字段

#define SGF_PLT_TYPE			"POLLUTE_TYPE"
#define SGF_PLT_LEVEL			"POLLUTE_LEVEL"
#define SGF_PLT_RADIUS			"AFFECT_RADIUS"
#define SG_PLT_DISP_STYLE_TABLE		"EM_PLT_DISP_STYLE"
/*******************************************************************************
							业务流程定义表2013-09-03
*******************************************************************************/
//流程定义表
#define  SYS_FLOW_DEF_TBL		"SYS_FLOW_DEF" 
 //流程节点表3
#define  SYS_FLOW_NODE_TBL		"SYS_FLOW_NODE"
//流程流转定义表
#define  SYS_FLOW_TURN_NODE_TBL "SYS_FLOW_NODE_TURN"
//流程节点角色表
#define  SYS_FLOW_NODE_ROLE_TBL "SYS_FLOW_NODE_ROLE"
//流程节点部门表
#define  SYS_FLOW_NODE_UNIT_TBL	"SYS_FLOW_NODE_UNIT"
//流转控制表3.5
#define  SYS_FLOW_CONTROL_TBL	"SYS_FLOW_CONTROL"

#define  SGF_EVENTID			"EVENTID"
#define	 SGF_BID				"BID"
#define  SGF_SEND_DEPT			"SEND_DEPT"
#define  SGF_SEND_PERSON		"SEND_PERSON"
#define  SGF_SEND_DATE			"SEND_DATE"
#define	 SGF_AUDIT_COMPANY		"AUDIT_COMPANY"
#define  SGF_AUDIT_DEPT			"AUDIT_DEPT"
#define  SGF_AUDIT_PERSON		"AUDIT_PERSON"
#define  SGF_AUDIT_RESULT		"AUDIT_RESULT"
#define  SGF_AUTIT_REMARK		"AUTIT_REMARK"