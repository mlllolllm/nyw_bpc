#ifndef BPC_H_
#define BPC_H_

#include <iostream>
#include <algorithm>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <cstring>
#include <string>
#include <chrono>
#include <fstream>
#include "auto_rtbl_plat.h"
#include "dppclient.h"
#include "rdbmem.h"
#include "dpf.h"
using namespace std;

#ifdef BPC_DLL
#define BPC_DLL_API BPC_Proper_Export_Flag
#define BPC_DLL_API __attribute__((visibility("default")))
#else
#define BPC_DLL_API BPC_Proper_Import_Flag
#define BPC_DLL_API __attribute__((visibility("default")))
#endif

struct Chrom // 结构体类型，为单个染色体的结构；
{
    vector<int> Load;
    double fit; // 适应值
};

struct Consumer
{
    string name;
    SG_INT of_base_voltage;
    SG_FLOAT mpower_p;
    SG_FLOAT mpower_q;
};

class BPC_DLL_API TopologicalNode;
// 实时库操作
// 我真服了什么库
// TN节点类
class BPC_DLL_API CalCaseDataOp : public CDasBase
{
private:
    SG_INT64 m_SchemaHandler;
    // cn，tn节点数量
    int m_cn_num;
    int m_tn_num;
    // 一些配置
    // CRDBLoadSetting m_loadSetting;
    CSgRDBTable *m_rdbTable = nullptr;
    CDpf *m_dpf = nullptr;
    CGAP_DppSrvClient m_DBClient;
    // 保存负荷id
    vector<SG_INT64> m_LoadList;
    // 添加完虚拟节点后的terminal数量，用于删除以及更新terminal表数据
    SG_INT64 m_initial_model_terminal_num;
    SG_INT64 m_model_terminal_num;
    // 未进行潮流运算时的terminal_id，用于继续添加
    SG_INT64 m_initial_model_terminal_id;
    SG_INT64 m_model_terminal_id;
    // 未进行潮流计算时的terminal_of_device，用于继续添加
    SG_INT64 m_initial_model_terminal_of_device;
    SG_INT64 m_model_terminal_of_device;
    // 负荷id，用于继续添加，潮不潮流无所谓
    SG_INT64 m_initial_model_energy_consumer_id;
    SG_INT64 m_model_energy_consumer_id;

    // 染色体群
    vector<Chrom> m_group;
    // 包含染色体数量
    int m_group_num;
    // 迭代次数
    int m_times;
    // 交叉率
    double m_CrossoverProbability;
    // 变异率
    double m_MutationProbability;
    // 结果总结
    Chrom m_res;
    // 最佳接入位置保存方式
    int m_save_type;
    string m_save_path;
    string m_save_name;
    // 交叉编译方式baocun
    int m_crossoverFuc;
    int m_mutationFunc;
    std::chrono::time_point<std::chrono::high_resolution_clock> m_startTime;
    std::chrono::time_point<std::chrono::high_resolution_clock> m_endTime;
    // 配置文件数据
    vector<DAS_CONFIG> m_DasConfigs;

    // 设置新的参数已实现从文件控制可接入位置
    // 初始化存入所有tn节点信息
    vector<TopologicalNode> m_tn_inf;
    // 此处由于笔者比较笨比，所以目前用的是比较原始的方法
    // 初始化对应连接关系信息
    vector<SG_INT64> m_cn_id;
    vector<SG_INT> m_w_conn;
    int m_cn_can_use = 0;
    int m_tn_can_use = 0;

    vector<TopologicalNode> m_tn_allowwed;

    vector<Consumer> m_consumer_added;

public:
    CalCaseDataOp(CDpf &dpf_op, SG_INT64 SchemaHandler, CRDBLoadSetting &loadSetting);
    ~CalCaseDataOp();
    // 返回rdbtable，以便于表操作
    CSgRDBTable &getRDBTable() const;
    // 返回dpf，以便于潮流计算
    CDpf &getdpf();
    // 返回cn值
    int get_cn_num() const { return m_cn_num; }
    // 返回tn值
    int get_tn_num() const { return m_tn_num; }
    // 返回染色体数
    int get_m_group_num() const { return m_group_num; }
    // 返回迭代次数
    int get_times() const { return m_times; }
    // 返回交叉率
    double get_CrossoverProbability() const { return m_CrossoverProbability; }
    // 返回变异率
    double get_MutationProbability() const { return m_MutationProbability; }
    // 返回交叉编译选择参数
    int get_crossoverFunc() const { return m_crossoverFuc; }
    int get_mutationFunc() const { return m_mutationFunc; }
    // 返回初始化的种群
    vector<Chrom> &get_ini_group() { return m_group; }

    vector<SG_INT> &get_w_conn() { return m_w_conn; }

    int get_cn_can_use() const { return m_cn_can_use; }
    // 返回loadlist
    int get_LoadListSize() const
    {
        int temp = m_LoadList.size();
        return temp;
    }
    // 网损计算
    double networkLossCountByAS();
    // 系统网损计算，拓扑岛形式
    double networkLossCountByTI();
    // 整体网损判断
    bool vltJudgeOverall();
    // 根据负荷值添加
    // 请注意，n从0开始添加
    void model_energy_consumer_add(const SG_INT64 &id, const SG_STRING name = "负荷unknown", const SG_INT64 &of_feeder = 0, const SG_STRING psrid = "@", const SG_INT &of_base_volt = 0, const SG_FLOAT &mpower_p = 0, const SG_FLOAT &mpower_q = 0, int n = 0);
    // 添加端子
    // 同样从0开始
    void model_terminal_add(SG_INT64 id, SG_INT terminal_type = 1, SG_INT64 of_device = 0, SG_INT64 conn_node_id = 0, int n = 0);
    // 删除表记录，注意仅限用于model_energy_consumer表和model_terminal_add表
    void recoed_delete(char *tableName, const SG_INT64 &id);
    // 根据染色体添加terminal表值
    void model_terminal_add_fromChrom(Chrom &ch);
    // 根据染色体删除terminal表值
    void model_terminal_delete_fromChrom(const Chrom &ch);
    // 从参数库将数据添加至关系库
    int get_model_energy_consumer();

    int get_position_used();

    // 结果输出
    void result_output();

    int OpenTable(CSgRDBTable &rdbTable, char *tableName);

    void TableCanUse(CSgRDBTable &rdbTable);

    void CloseTable(CSgRDBTable &rdbTable);
    // 读配置表s
    int ReadConfig();
    // 读模型表等
    int Read();
    // 计算
    void Exec();
    // 写结果表
    int Write();

    void geneticAlgorithm();
    // 初始化config
    int InitConfig();
    // 根据条数读取数据
    int ReadConfig(char *NAME, double *pVal);
    int ReadConfig(char *NAME, char *pVal);
    int ReadConfig(char *NAME, int *pVal);
    // 输出到文件
    void result_output_file(const string &filename);
    // 输出到文件，用于测试，保留数据不刷新
    void result_output_file_test(const string &filename);

    void result_oupput_database();
};
// 对不起写的还行反正我写不出来
// 但也不是那么行

class BPC_DLL_API TopologicalNode
{
private:
    SG_INT64 m_ID;
    SG_INT64 m_of_topologicalisland;
    vector<SG_INT64> m_contains_connectivity_nodes;
    vector<SG_INT> m_contains_connectivity_nodes_position;
    vector<SG_INT> m_contains_connectivity_nodes_status;
    vector<SG_INT64> m_contains_connectivity_nodes_allowed;
    int m_useable = 0;
    // double vltmax;
    // double vltmin;

public:
    TopologicalNode(CalCaseDataOp &rdbTable, int n);
    ~TopologicalNode();
    SG_INT64 getID() { return m_ID; }
    float getSTD_VAL(CalCaseDataOp &rdbTable);
    float getVltMax(CalCaseDataOp &rdbTable);
    float getVltMin(CalCaseDataOp &rdbTable);
    // 电压判断
    bool VoltageJudge(CalCaseDataOp &rdbTable);

    vector<SG_INT64> &get_contains_connectivity_nodes() { return m_contains_connectivity_nodes; }

    int get_useable() { return m_useable; }

    vector<SG_INT64> &get_contains_connectivity_nodes_allowed() { return m_contains_connectivity_nodes_allowed; }
};

class BPC_DLL_API GA
{
public:
    GA();
    ~GA();

    Chrom geneticAlgorithm(CalCaseDataOp &rdbTable);

    vector<Chrom> &single_point_crossover(CalCaseDataOp &rdbTable, vector<Chrom> &temp_group);

    vector<Chrom> &two_points_crossover(CalCaseDataOp &rdbTable, vector<Chrom> &temp_group);

    vector<Chrom> &mutationFunc1(CalCaseDataOp &rdbTable, vector<Chrom> &temp_group);

    vector<Chrom> &mutationFunc2(CalCaseDataOp &rdbTable, vector<Chrom> &temp_group);
};

#endif