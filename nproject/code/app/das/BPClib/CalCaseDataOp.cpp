#include "BPC.h"
#include <cstring>
#include <limits>

int CalCaseDataOp::OpenTable(CSgRDBTable &rdbTable, char *tableName)
{
    int ret = rdbTable.OpenTable(tableName, 1);
    return ret;
}
void CalCaseDataOp::TableCanUse(CSgRDBTable &rdbTable)
{
    rdbTable.TableCanUse();
}
void CalCaseDataOp::CloseTable(CSgRDBTable &rdbTable)
{
    rdbTable.CloseTable();
}

// 数据库操作类方法

CalCaseDataOp::CalCaseDataOp(CDpf &dpf_op, SG_INT64 SchemaHandler, CRDBLoadSetting &loadSetting) : m_SchemaHandler(SchemaHandler)
{
    // 程序开始时间记录
    m_startTime = std::chrono::high_resolution_clock::now();

    // 实时库初始化
    m_dpf = &dpf_op;
    (*m_dpf).Init(SchemaHandler, &loadSetting);
    // 创建参数库连接
    m_DBClient.SetIPString("192.168.122.17:6118");
    // 创建数据库表操作类对象
    m_rdbTable = new CSgRDBTable(SchemaHandler);
}

CalCaseDataOp::~CalCaseDataOp()
{
    int ret = 0;
    delete m_rdbTable;
    m_rdbTable = nullptr;
    // delete dpf;
    m_dpf = nullptr;

    cout << "============end==============" << endl;
}

CSgRDBTable &CalCaseDataOp::getRDBTable() const
{
    return (*m_rdbTable);
}

CDpf &CalCaseDataOp::getdpf()
{
    return (*m_dpf);
}
// 系统网损计算,馈线形式
double CalCaseDataOp::networkLossCountByAS()
{
    double loss = 0;
    // 打开表model_d_acline_section
    OpenTable((*m_rdbTable), "model_d_acline_segment");
    // 读取并计算IPOWER_PLOSS的和并保存
    CSgDataSet dataset;
    if ((*m_rdbTable).GetRcdDataSet(dataset))
    {
        SG_UINT recsize = dataset.GetRecordNums();
        int index;
        double temp_loss = 0;
        for (int i = 0; i < recsize; i++)
        {
            index = (*m_rdbTable).GetFieldPtr("IPOWER_PLOSs");
            dataset.GetAt(i, (SG_SHORT)index, &temp_loss);
            loss += temp_loss;
            // cout << "ID=" << id << ",DESCRIPTION=" << desc << ",OF_VOLT_LEVEL=" << volt << ",OF_SUBSTATION=" << station << endl;
        }
    }
    // 关闭表
    CloseTable((*m_rdbTable));
    // 返回结果
    return loss;
}
// 系统网损计算，拓扑岛形式
double CalCaseDataOp::networkLossCountByTI()
{
    double loss = 0;
    // 打开表model_d_acline_section
    OpenTable((*m_rdbTable), "model_topological_island");
    // 读取并计算IPOWER_PLOSS的和并保存
    CSgDataSet dataset;
    if ((*m_rdbTable).GetRcdDataSet(dataset))
    {
        SG_UINT recsize = dataset.GetRecordNums();
        int index;
        double temp_loss = 0;
        for (int i = 0; i < recsize; i++)
        {
            index = (*m_rdbTable).GetFieldPtr("SUMLOSSP");
            dataset.GetAt(i, (SG_SHORT)index, &temp_loss);
            loss += temp_loss;
            // cout << "ID=" << id << ",DESCRIPTION=" << desc << ",OF_VOLT_LEVEL=" << volt << ",OF_SUBSTATION=" << station << endl;
        }
    }
    // 关闭表
    CloseTable((*m_rdbTable));
    // 返回结果
    return loss;
}
// 系统电压判断
bool CalCaseDataOp::vltJudgeOverall()
{
    // bool judge_temp = true;
    for (int i = 0; i < m_tn_num; i++)
    {
        // TopologicalNode temp(*this, i);
        if (!m_tn_inf[i].VoltageJudge(*this))
            return false;
    }
    return true;
}
// 负荷表添加数据，按一行添加
void CalCaseDataOp::model_energy_consumer_add(const SG_INT64 &id, const SG_STRING name, const SG_INT64 &of_feeder, const SG_STRING psrid, const SG_INT &of_base_volt, const SG_FLOAT &mpower_p, const SG_FLOAT &mpower_q, int n)
{
    // 数据库中该值为tinyint，无法在实时库架构中找到对应存储方式，为避免越界，进行输入判定
    if (of_base_volt > 127 || of_base_volt < -128)
    {
        cout << "of_base_volt invalid input!" << endl;
        return;
    }
    // 打开表
    OpenTable((*m_rdbTable), "model_energy_consumer");
    CSgDataSet datSet;
    char *pFieldName[] = {"ID", "NAME", "OF_FEEDER", "PSRID", "OF_BASE_VOLTAGE", "MPOWER_P", "MPOWER_Q"};
    int fieldType[] = {SG_FIELDTYPE_INT64, SG_FIELDTYPE_VARCHAR, SG_FIELDTYPE_INT64, SG_FIELDTYPE_VARCHAR, SG_FIELDTYPE_INT, SG_FIELDTYPE_FLOAT, SG_FIELDTYPE_FLOAT};
    int fieldLen[] = {sizeof(SG_INT64), 128, sizeof(SG_INT64), 128, sizeof(SG_INT), sizeof(SG_FLOAT), sizeof(SG_FLOAT)};
    int fieldNum = sizeof(pFieldName) / sizeof(char *);
    datSet.SetFieldNums(fieldNum);
    for (int i = 0; i < fieldNum; i++)
    {
        datSet.SetFieldName(i, pFieldName[i]);
        datSet.SetFieldType(i, fieldType[i]);
        datSet.SetFieldLen(i, fieldLen[i]);
    }
    datSet.SetFieldPrimary(0, true);
    datSet.BuildTableInfo();
    datSet.SetTableName("model_energy_consumer");

    datSet.SetRecordNums(1);
    SG_INT64 n_id = id;
    SG_INT64 n_of_feeder = of_feeder;
    SG_INT n_of_base_volt = of_base_volt;
    SG_FLOAT n_mpower_p = mpower_p;
    SG_FLOAT n_mpower_q = mpower_q;
    int index;
    // id = 123456789;
    //  CSgString sgstr;
    //  sgstr="测试开关1";
    datSet.SetAt((SG_SHORT)n, (SG_SHORT)0, &n_id);
    datSet.SetAt((SG_SHORT)n, (SG_SHORT)1, name);
    datSet.SetAt((SG_SHORT)n, (SG_SHORT)2, &n_of_feeder);
    datSet.SetAt((SG_SHORT)n, (SG_SHORT)3, psrid);

    datSet.SetAt((SG_SHORT)n, (SG_SHORT)4, &n_of_base_volt);
    datSet.SetAt((SG_SHORT)n, (SG_SHORT)5, &n_mpower_p);
    datSet.SetAt((SG_SHORT)n, (SG_SHORT)6, &n_mpower_q);

    if ((*m_rdbTable).ReOpenTable(1, 1))
    {
        cout << "ReOpenTable sucessed" << endl;
    }
    else
    {
        cout << "ReOpenTable failed" << endl;
    }
    if ((*m_rdbTable).InsertRecorder(datSet, false))
    {
        cout << "InsertRecorder sucessed" << endl;
    }
    else
    {
        cout << "InsertRecorder failed" << endl;
    }
    cout << "-----------------------------" << endl;
    // 关闭表
    CloseTable((*m_rdbTable));
    // 将添加的id保存到
    m_LoadList.push_back(id);
}
// 端子表添加数据，按一行添加
void CalCaseDataOp::model_terminal_add(SG_INT64 id, SG_INT terminal_type, SG_INT64 of_device, SG_INT64 conn_node_id, int n)
{
    if (terminal_type > 127 || terminal_type < -128)
    {
        cout << "terminal_type invalid input!" << endl;
        return;
    }
    // 打开表
    OpenTable((*m_rdbTable), "model_terminal");
    CSgDataSet datSet;
    char *pFieldName[] = {"ID", "TERMINAL_TYPE", "OF_DEVICE", "CONN_NODE_ID"};
    int fieldType[] = {SG_FIELDTYPE_INT64, SG_FIELDTYPE_INT, SG_FIELDTYPE_INT64, SG_FIELDTYPE_INT64};
    int fieldLen[] = {sizeof(SG_INT64), sizeof(SG_INT), sizeof(SG_INT64), sizeof(SG_INT64)};
    int fieldNum = sizeof(pFieldName) / sizeof(char *);
    datSet.SetFieldNums(fieldNum);
    for (int i = 0; i < fieldNum; i++)
    {
        datSet.SetFieldName(i, pFieldName[i]);
        datSet.SetFieldType(i, fieldType[i]);
        datSet.SetFieldLen(i, fieldLen[i]);
    }
    datSet.SetFieldPrimary(0, true);
    datSet.BuildTableInfo();
    datSet.SetTableName("model_terminal");

    datSet.SetRecordNums(1);
    SG_INT64 n_id = id;
    SG_INT64 n_terminal_type = terminal_type;
    SG_INT64 n_of_devicer = of_device;
    SG_INT64 n_conn_node_id = conn_node_id;
    int index;
    datSet.SetAt((SG_SHORT)n, (SG_SHORT)0, &n_id);
    datSet.SetAt((SG_SHORT)n, (SG_SHORT)1, &n_terminal_type);
    datSet.SetAt((SG_SHORT)n, (SG_SHORT)2, &n_of_devicer);
    datSet.SetAt((SG_SHORT)n, (SG_SHORT)3, &n_conn_node_id);

    if ((*m_rdbTable).ReOpenTable(1, 1))
    {
        cout << "ReOpenTable sucessed" << endl;
    }
    else
    {
        cout << "ReOpenTable failed" << endl;
    }
    if ((*m_rdbTable).InsertRecorder(datSet, false))
    {
        cout << "InsertRecorder sucessed" << endl;
    }
    else
    {
        cout << "InsertRecorder failed" << endl;
    }
    cout << "-----------------------------" << endl;
    // 关闭表
    CloseTable((*m_rdbTable));
}
// 删除表记录，一条一条删除
void CalCaseDataOp::recoed_delete(char *tableName, const SG_INT64 &id)
{
    // 判断表是否合理
    if (strcmp(tableName, "model_energy_consumer") == 0 || strcmp(tableName, "model_terminal_add") == 0)
    {
    }
    else
    {
        return;
    }
    // 打开对应表
    OpenTable((*m_rdbTable), tableName);

    VECT_INT64 KeyIDList;
    KeyIDList.push_back(id);
    // KeyIDList.push_back(987654321);
    if ((*m_rdbTable).DelRcdByKey(KeyIDList, false))
    {
        cout << "DelRcdByKey sucessed" << endl;
    }
    else
    {
        cout << "DelRcdByKey failed" << endl;
    }
    cout << "-----------------------------" << endl;
    // 关闭表
    CloseTable((*m_rdbTable));
}
// 输出到控制台
void CalCaseDataOp::result_output()
{
    // 打开表
    OpenTable((*m_rdbTable), "model_topological_node");
    CSgDataSet datSet;
    if ((*m_rdbTable).GetRcdDataSet(datSet))
    {
        CloseTable((*m_rdbTable));
        // SG_UINT recsize = datSet.GetRecordSize();
        int index;
        SG_INT64 m_temp;
        for (int i = 0; i < (*this).get_LoadListSize(); i++)
        {
            OpenTable((*m_rdbTable), "model_topological_node");
            index = (*m_rdbTable).GetFieldPtr("ID");
            // datSet.GetAt(m_res.Load[i], (SG_SHORT)index, &m_temp);
            cout << " 接入方式为:" << endl;
            cout << "consumer_id:" << m_LoadList[i] << "        ";
            cout << "model_topological_node_ID:" << m_tn_allowwed[i].getID() << endl;

            CloseTable((*m_rdbTable));
            // TopologicalNode TN_temp((*this), m_res.Load[i]);
            cout << "Including conn_nodes:";
            for (int j = 0; j < m_tn_allowwed[m_res.Load[i]].get_useable(); j++)
            {
                cout << m_tn_allowwed[m_res.Load[i]].get_contains_connectivity_nodes_allowed()[j] << "    ";
            }
            cout << endl;
            // cout << "ID=" << id << ",DESCRIPTION=" << desc << ",OF_VOLT_LEVEL=" << volt << ",OF_SUBSTATION=" << station << endl;
        }
    }
    OpenTable((*m_rdbTable), "model_topological_node");
    cout << "The networkLoss is:" << m_res.fit << endl;

    m_model_terminal_num = m_initial_model_terminal_num;
    // 程序结束时间记录
    m_endTime = std::chrono::high_resolution_clock::now();
    // 输出程序运行时间
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(m_endTime - m_startTime);
    std::cout << "程序运行时间：" << duration.count() << " 秒" << std::endl;
    // 关闭表
    CloseTable((*m_rdbTable));
}
// 根据染色体添加terminal表值
void CalCaseDataOp::model_terminal_add_fromChrom(Chrom &ch)
{
    for (int i = 0; i < ch.Load.size(); i++)
    {
        // TopologicalNode temp((*this), ch.Load[i]);
        (*this).model_terminal_add(++m_model_terminal_id, 1, ++m_model_terminal_of_device, m_tn_inf[ch.Load[i]].get_contains_connectivity_nodes()[0], 0);
    }
}
// 根据染色体删除
void CalCaseDataOp::model_terminal_delete_fromChrom(const Chrom &ch)
{
    OpenTable((*m_rdbTable), "model_terminal");
    CSgDataSet datSet;
    (*m_rdbTable).GetRcdDataSet(datSet);
    SG_UINT recordNums = datSet.GetRecordNums();
    // VECT_INT64 KeyIDList;
    for (SG_UINT i = recordNums; i > m_initial_model_terminal_num; --i)
    {
        (*m_rdbTable).DelRcdByNo(m_initial_model_terminal_num);
    }
    //(*rdbTable).DelRcdByKey(KeyIDList, false);
    // 关闭表
    CloseTable((*m_rdbTable));
    m_model_terminal_id = m_initial_model_terminal_id;
    m_model_terminal_of_device = m_initial_model_terminal_of_device;
}
// 从参数库读数据至内存库
int CalCaseDataOp::get_model_energy_consumer()
{
    CSgDataSet DatSet;
    CDBCmd_ReadRecorder_Req ReadReq;
    CDBCmd_ReadRecorder_Res ReadRes;
    ReadRes.pRetDat = &DatSet;
    ReadReq.SQLBuf.Format("select NAME,OF_BASE_VOLTAGE,OF_FEEDER,PSRID,MPOWER_P,MPOWER_Q from dev.tmp_model_energy_conusmer_add_node62");
    if (m_DBClient.RDB_ReadRecorder(ReadReq, ReadRes) < 0)
    {
        return false;
    }
    CSgString tmp_name;
    SG_INT tmp_of_base_voltage;
    SG_INT64 tmp_of_feeder;
    CSgString tmp_psrid;
    SG_FLOAT tmp_mpower_p;
    SG_FLOAT tmp_mpower_q;
    Consumer t_consumer;
    for (int i = 0; i < DatSet.GetRecordNums(); i++)
    {
        // DatSet.PrintRecord(i); // 打印DataSet的内容
        DatSet.GetAt(i, (SG_SHORT)0, tmp_name);
        DatSet.GetAt(i, (SG_SHORT)1, &tmp_of_base_voltage);
        DatSet.GetAt(i, (SG_SHORT)2, &tmp_of_feeder);
        DatSet.GetAt(i, (SG_SHORT)3, tmp_psrid);
        DatSet.GetAt(i, (SG_SHORT)4, &tmp_mpower_p);
        DatSet.GetAt(i, (SG_SHORT)5, &tmp_mpower_q);
        model_energy_consumer_add(++m_model_energy_consumer_id, tmp_name, tmp_of_feeder, tmp_psrid, tmp_of_base_voltage, tmp_mpower_p, tmp_mpower_q);
        t_consumer.name = tmp_name;
        t_consumer.of_base_voltage = tmp_of_base_voltage;
        t_consumer.mpower_p = tmp_mpower_p;
        t_consumer.mpower_q = tmp_mpower_q;
        m_consumer_added.push_back(t_consumer);
    }
    m_model_energy_consumer_id = m_initial_model_energy_consumer_id;
    return true;
}

int CalCaseDataOp::get_position_used()
{
    CSgDataSet DatSet;
    CDBCmd_ReadRecorder_Req ReadReq;
    CDBCmd_ReadRecorder_Res ReadRes;
    ReadRes.pRetDat = &DatSet;
    ReadReq.SQLBuf.Format("select ID,REACHABLE from dev.temp_model_conn_node_canuse");
    if (m_DBClient.RDB_ReadRecorder(ReadReq, ReadRes) < 0)
    {
        return false;
    }
    SG_INT64 tmp_id;
    SG_INT tmp_reachable;
    for (int i = 0; i < DatSet.GetRecordNums(); i++)
    {
        DatSet.PrintRecord(i); // 打印DataSet的内容
        DatSet.GetAt(i, (SG_SHORT)0, &tmp_id);
        DatSet.GetAt(i, (SG_SHORT)1, &tmp_reachable);
        m_cn_id.push_back(tmp_id);
        m_w_conn.push_back(tmp_reachable);
    }
    return true;
}
// 参数库配置信息准备
int CalCaseDataOp::ReadConfig()
{
    char tmp[255];
    float tmp_f;
    (*this).InitConfig();
    (*this).ReadConfig("BPC_group_num", &m_group_num);
    (*this).ReadConfig("BPC_times", &m_times);
    (*this).ReadConfig("BPC_save_type", &m_save_type);
    (*this).ReadConfig("BPC_save_path", tmp);
    m_save_path = tmp;
    (*this).ReadConfig("BPC_save_name", tmp);
    m_save_name = tmp;
    (*this).ReadConfig("BPC_CrossoverProbability", &m_CrossoverProbability);
    (*this).ReadConfig("BPC_MutationProbability", &m_MutationProbability);
    (*this).ReadConfig("BPC_crossover_func", &m_crossoverFuc);
    (*this).ReadConfig("BPC_mutation_func", &m_mutationFunc);
}
// 数据准备
int CalCaseDataOp::Read()
{

    // 读取对应连接关系
    (*this).get_position_used();

    CSgDataSet datSet;
    int index;
    SG_UINT recordNums;
    // 读取terminal节点id信息
    OpenTable((*m_rdbTable), "model_terminal");
    SG_INT64 tmp_terminal_of_device;
    SG_INT64 tmp_terminal_id;
    (*m_rdbTable).GetRcdDataSet(datSet);
    recordNums = datSet.GetRecordNums();
    cout << "recordnums:" << recordNums << endl;

    // index = (*m_rdbTable).GetFieldPtr("OF_DEVICE");
    // datSet.GetAt(recordNums - 1, (SG_SHORT)index, &tmp_terminal_of_device);
    // m_initial_model_terminal_of_device = m_model_terminal_of_device = tmp_terminal_of_device;

    index = (*m_rdbTable).GetFieldPtr("ID");
    datSet.GetAt(recordNums - 1, (SG_SHORT)index, &tmp_terminal_id);
    m_initial_model_terminal_id = m_model_terminal_id = tmp_terminal_id;
    CloseTable((*m_rdbTable));
    datSet.Reset();
    cout << "terminal_of_device:" << tmp_terminal_of_device << endl;

    (*m_dpf).Exec();

    // TN节点和CN节点数量读入
    OpenTable((*m_rdbTable), "model_conn_node");
    m_cn_num = (*m_rdbTable).GetRcdNum();
    cout << "cn_num:" << m_cn_num << endl;
    CloseTable((*m_rdbTable));
    OpenTable((*m_rdbTable), "model_topological_node");
    m_tn_num = (*m_rdbTable).GetRcdNum();
    cout << "tn_num:" << m_tn_num << endl;
    // 获取所有tn节点信息
    for (int i = 0; i < m_tn_num; i++)
    {
        TopologicalNode temp((*this), i);
        m_tn_inf.push_back(temp);
        if (temp.get_useable() >= 1)
        {
            m_tn_can_use++;
            m_tn_allowwed.push_back(temp);
        }
    }
    CloseTable((*m_rdbTable));

    // model_energy_consumer id读入
    OpenTable((*m_rdbTable), "model_energy_consumer");
    SG_INT64 tmp_consumer_id;
    (*m_rdbTable).GetRcdDataSet(datSet);
    recordNums = datSet.GetRecordNums();
    index = (*m_rdbTable).GetFieldPtr("ID");
    datSet.GetAt(recordNums - 1, (SG_SHORT)index, &tmp_consumer_id);
    m_model_energy_consumer_id = m_initial_model_energy_consumer_id = tmp_consumer_id;
    m_initial_model_terminal_of_device = m_model_terminal_of_device = tmp_consumer_id;
    CloseTable((*m_rdbTable));
    datSet.Reset();
    cout << "consumer_id:" << tmp_consumer_id << endl;
    // 获取添加完虚拟电源后的termina数量
    OpenTable((*m_rdbTable), "model_terminal");
    (*m_rdbTable).GetRcdDataSet(datSet);
    m_model_terminal_num = m_initial_model_terminal_num = datSet.GetRecordNums();
    datSet.Reset();
    CloseTable((*m_rdbTable));

    m_cn_can_use = std::count(m_w_conn.begin(), m_w_conn.end(), 1);

    // 根据数据库添加负荷
    (*this).get_model_energy_consumer();

    // 染色体种群初始化
    // 注意，此处应有配置替换
    int group_num = m_group_num;
    cout << "m_group_num:" << m_group_num << endl;
    std::vector<int> result;
    srand(time(0));

    for (int i = 0; i < group_num; ++i)
    {
        // 设置随机数
        for (int i = 0; i < (*this).get_LoadListSize(); ++i)
            result.push_back(rand() % (*this).m_tn_can_use);
        // 染色体初始化
        Chrom newChrom;
        cout << "newChrom succeed" << endl;
        newChrom.fit = 0;
        newChrom.Load.assign(result.begin(), result.end()); // 初始化 Load
        cout << "newChrom initialize succeed" << endl;
        // 根据连接关系添加端子
        (*this).model_terminal_add_fromChrom(newChrom);
        cout << "terminal change succeed" << endl;
        // 更新拓扑结构
        (*this).getdpf().Exec();
        // 进行潮流计算更新数据

        if (!(*this).vltJudgeOverall())
            newChrom.fit = numeric_limits<double>::max();
        else
            newChrom.fit = (*this).networkLossCountByTI(); // 初始化 fit 为网速的导数

        // 删除端子表中新增数据
        (*this).model_terminal_delete_fromChrom(newChrom);

        m_group.push_back(newChrom); // 将初始化后的 newChrom 添加到 group 容器中
        // 清空临时容器
        result.clear();
    }

    cout << "GA initalize succeed" << endl;
}
// 遗传算法数据计算
void CalCaseDataOp::Exec()
{
    // 注意，此处应有配置替换
    //(*this).geneticAlgorithm();
    GA temp;
    m_res = temp.geneticAlgorithm((*this));
}
// 数据输出，可输出至控制台，输出至文件覆盖，输出至文件不覆盖
int CalCaseDataOp::Write()
{
    if (m_save_type == 0)
        (*this).result_output();
    else if (m_save_type == 1)
        (*this).result_output_file(m_save_path + "/" + m_save_name);
    else if (m_save_type == 2)
        (*this).result_output_file_test(m_save_path + "/" + m_save_name);
    else if (m_save_type == 3)
        (*this).result_oupput_database();
}
// 弃用遗传算法，可以将ga类合并
void CalCaseDataOp::geneticAlgorithm() // LoadNum负荷数，times迭代次数，交叉概率，遗传概率
{
    const int LoadNum = (*this).get_LoadListSize();
    srand(time(0));
    int random;
    int i, j;
    double sum;
    double Min = numeric_limits<double>::max();

    // 开始迭代
    for (int k = 0; k < m_times; k++)
    {
        cout << "第 " << k + 1 << "次迭代结果：" << endl;
        cout << Min << endl;
        sum = 0.0;
        int men;
        // 对染色体排序，选出排名靠前的四分之一进行交叉变异产生子代
        int i;
        int j;
        double p;
        sort(m_group.begin(), m_group.end(), [](const Chrom &a, const Chrom &b)
             { return a.fit < b.fit; });

        // 交叉
        int row, col;
        for (int l = m_group_num / 4; l < m_group_num / 2; l++)
        {
            random = rand() % 100;
            if (random < (100 * m_CrossoverProbability))
            {
                row = rand() % (m_group_num / 4);
                col = rand() % LoadNum;
                for (int m = 0; m < col; m++)
                {
                    m_group[l].Load[m] = m_group[l - m_group_num / 4].Load[m];
                }
                for (int m = col; m < LoadNum; m++)
                {
                    m_group[l].Load[m] = m_group[row].Load[m];
                }
            }
        }

        // 变异
        for (int m = m_group_num / 2; m < m_group_num; m++)
        {
            if ((rand() % 100) < (m_MutationProbability * 100))
            {
                m_group[m] = m_group[m - m_group_num / 2];
                col = rand() % LoadNum;
                m_group[m].Load[col] = rand() % (*this).get_tn_num();
            }
        }
        // 种群更替；
        for (j = 0; j < m_group_num; j++)
        {
            // sum = 0.0;
            // for (vector<int>::iterator it = m_group[j].Load.begin(); it != m_group[j].Load.end(); it++)
            // {
            // 	sum += sin(0.1*(*it));
            // }
            // 更新数据库
            // 将接入位置写入端子表
            (*this).model_terminal_add_fromChrom(m_group[j]);

            // 调用拓扑
            // 调用潮流
            (*this).getdpf().Exec();

            // 更新fit值
            if (!(*this).vltJudgeOverall())
                m_group[j].fit = numeric_limits<double>::max();
            else
                m_group[j].fit = (*this).networkLossCountByTI(); // 初始化 fit 为网速的导数

            // 删除端子表新增节点
            (*this).model_terminal_delete_fromChrom(m_group[j]);
            if (m_group[j].fit < Min)
            {
                // m_res = group[j];
                std::copy(m_group[j].Load.begin(), m_group[j].Load.end(), std::back_inserter(m_res.Load));
                m_res.fit = m_group[j].fit;
                Min = m_group[j].fit;
            }
        }
    }
}
// 参数库配置信息获取
int CalCaseDataOp::InitConfig()
{
    CSgDataSet dataSet;
    CDBCmd_ReadRecorder_Req readReq;
    CDBCmd_ReadRecorder_Res readRes;
    readRes.pRetDat = &dataSet;
    readReq.SQLBuf.Format("select * from dev.das_config where APPID = 314");
    if (m_DBClient.RDB_ReadRecorder(readReq, readRes) < 0)
    {
        return 0;
    }
    int rcdNum = dataSet.GetRecordNums();
    for (int i = 0; i < rcdNum; i++)
    {
        DAS_CONFIG dasConfig;
        dataSet.Get(i, "ID", &dasConfig.ID);
        dataSet.Get(i, "APPCODE", dasConfig.APPCODE);
        dataSet.Get(i, "APPID", &dasConfig.APPID);
        dataSet.Get(i, "PARAID", &dasConfig.PARAID);
        dataSet.Get(i, "NAME", dasConfig.NAME);
        dataSet.Get(i, "DESC", dasConfig.DESC);
        dataSet.Get(i, "TYPE", &dasConfig.TYPE);
        dataSet.Get(i, "CHVALUE", dasConfig.CHVALUE);
        dataSet.Get(i, "INTVALUE", &dasConfig.INTVALUE);
        dataSet.Get(i, "FLOATVALUE", &dasConfig.FLOATVALUE);
        m_DasConfigs.push_back(dasConfig);
    }
    return 1;
}

int CalCaseDataOp::ReadConfig(char *NAME, double *pVal)
{
    for (vector<DAS_CONFIG>::iterator it = m_DasConfigs.begin(); it != m_DasConfigs.end(); it++)
    {
        if (!strcasecmp(it->NAME, NAME))
        {
            *pVal = it->FLOATVALUE;
            return 1;
        }
    }
    std::cout << "config not found" << std::endl;
    return 0;
}

int CalCaseDataOp::ReadConfig(char *NAME, char *pVal)
{
    for (vector<DAS_CONFIG>::iterator it = m_DasConfigs.begin(); it != m_DasConfigs.end(); it++)
    {
        if (!strcasecmp(it->NAME, NAME))
        {
            strcpy(pVal, it->CHVALUE);
            return 1;
        }
    }
    std::cout << "config not found" << std::endl;
    return 0;
}

int CalCaseDataOp::ReadConfig(char *NAME, int *pVal)
{
    for (vector<DAS_CONFIG>::iterator it = m_DasConfigs.begin(); it != m_DasConfigs.end(); it++)
    {
        if (!strcasecmp(it->NAME, NAME))
        {
            *pVal = it->INTVALUE;
            return 1;
        }
    }
    std::cout << "config not found" << std::endl;
    return 0;
}
// 输出至文件覆盖
void CalCaseDataOp::result_output_file(const string &filename)
{

    ofstream outputFile;
    outputFile.open(filename);
    if (outputFile.is_open())
    {
        outputFile << "接入方式为:" << endl;
        // outputFile << "CONSUMER_ID,MODEL_TOPOLOGICAL_NODE_ID,Including CONN_NODES\n";
        OpenTable((*m_rdbTable), "model_topological_node");
        CSgDataSet datSet;
        if ((*m_rdbTable).GetRcdDataSet(datSet))
        {
            CloseTable((*m_rdbTable));
            // SG_UINT recsize = datSet.GetRecordSize();
            int index;
            SG_INT64 m_temp;
            for (int i = 0; i < (*this).get_LoadListSize(); i++)
            {
                OpenTable((*m_rdbTable), "model_topological_node");
                index = (*m_rdbTable).GetFieldPtr("ID");
                // datSet.GetAt(m_res.Load[i], (SG_SHORT)index, &m_temp);
                outputFile << "consumer_id:" << m_LoadList[i] << "        ";
                outputFile << "model_topological_node_ID:" << m_tn_allowwed[i].getID() << "        ";
                CloseTable((*m_rdbTable));
                // TopologicalNode TN_temp((*this), m_res.Load[i]);
                outputFile << "Including conn_nodes:";
                for (int j = 0; j < m_tn_allowwed[m_res.Load[i]].get_useable(); j++)
                {
                    outputFile << m_tn_allowwed[m_res.Load[i]].get_contains_connectivity_nodes_allowed()[j] << " ";
                }
                outputFile << endl;
                // cout << "ID=" << id << ",DESCRIPTION=" << desc << ",OF_VOLT_LEVEL=" << volt << ",OF_SUBSTATION=" << station << endl;
            }
        }

        OpenTable((*m_rdbTable), "model_topological_node");
        outputFile << "The networkLoss is:" << m_res.fit << endl;

        m_model_terminal_num = m_initial_model_terminal_num;

        // 程序结束时间记录
        m_endTime = std::chrono::high_resolution_clock::now();
        // 输出程序运行时间
        auto duration = std::chrono::duration_cast<std::chrono::seconds>(m_endTime - m_startTime);
        outputFile << "程序运行时间：" << duration.count() << " 秒" << endl;
        // 关闭表
        CloseTable((*m_rdbTable));

        outputFile.close();
        cout << "Result exported to file successfully." << endl;
    }
    else
    {
        cerr << "Unable to open file file for writing." << endl;
    }
}
// 输出至文件不覆盖
void CalCaseDataOp::result_output_file_test(const string &filename)
{
    ofstream outputFile;
    outputFile.open(filename, ofstream::app);
    if (outputFile.is_open())
    {
        outputFile << "接入方式为:" << endl;
        // outputFile << "CONSUMER_ID,MODEL_TOPOLOGICAL_NODE_ID,Including CONN_NODES\n";
        OpenTable((*m_rdbTable), "model_topological_node");
        CSgDataSet datSet;
        if ((*m_rdbTable).GetRcdDataSet(datSet))
        {
            CloseTable((*m_rdbTable));
            // SG_UINT recsize = datSet.GetRecordSize();
            int index;
            SG_INT64 m_temp;
            for (int i = 0; i < (*this).get_LoadListSize(); i++)
            {
                OpenTable((*m_rdbTable), "model_topological_node");
                index = (*m_rdbTable).GetFieldPtr("ID");
                // datSet.GetAt(m_res.Load[i], (SG_SHORT)index, &m_temp);
                outputFile << "consumer_id:" << m_LoadList[i] << "        ";
                outputFile << "model_topological_node_ID:" << m_tn_allowwed[i].getID() << "        ";
                CloseTable((*m_rdbTable));
                // TopologicalNode TN_temp((*this), m_res.Load[i]);
                outputFile << "Including conn_nodes:";
                for (int j = 0; j < m_tn_allowwed[m_res.Load[i]].get_useable(); j++)
                {
                    outputFile << m_tn_allowwed[m_res.Load[i]].get_contains_connectivity_nodes_allowed()[j] << " ";
                }
                outputFile << endl;
                // cout << "ID=" << id << ",DESCRIPTION=" << desc << ",OF_VOLT_LEVEL=" << volt << ",OF_SUBSTATION=" << station << endl;
            }
        }

        OpenTable((*m_rdbTable), "model_topological_node");
        outputFile << "The networkLoss is:" << m_res.fit << endl;

        m_model_terminal_num = m_initial_model_terminal_num;

        // 程序结束时间记录
        m_endTime = std::chrono::high_resolution_clock::now();
        // 输出程序运行时间
        auto duration = std::chrono::duration_cast<std::chrono::seconds>(m_endTime - m_startTime);
        outputFile << "程序运行时间：" << duration.count() << " 秒" << endl;
        // 关闭表
        CloseTable((*m_rdbTable));

        outputFile.close();
        cout << "Result exported to file successfully." << endl;
    }
    else
    {
        cerr << "Unable to open file file for writing." << endl;
    }
}

void CalCaseDataOp::result_oupput_database()
{

    CDBCmd_ExecSQL_Req Req;
    CDBCmd_ExecSQL_Res Res;
    string str;
    // 打开表
    OpenTable((*m_rdbTable), "model_terminal");
    CSgDataSet datSet;
    CSgDataSet datSet_sql;
    if ((*m_rdbTable).GetRcdDataSet(datSet))
    {
        // SG_UINT recsize = datSet.GetRecordSize();
        int index;
        // SG_INT64 m_temp;
        VECT_STRINT64 FieldValList;
        S_STRINT64 FieldVal;
        SG_INT64 bus_temp;
        FieldVal.StrVal = "CONN_NODE_ID";
        int RcdNo;
        VECT_INT RcdNoList;
        for (int i = 0; i < (*this).get_LoadListSize(); i++)
        {
            FieldVal.IntVal = m_tn_allowwed[m_res.Load[i]].get_contains_connectivity_nodes_allowed()[0];
            FieldValList.push_back(FieldVal);
            (*m_rdbTable).GetRcdNoByFieldVal(FieldValList, RcdNoList);
            for (int j = 0; j < RcdNoList.size(); j++)
            {
                index = (*m_rdbTable).GetFieldPtr("OF_DEVICE");
                RcdNo = RcdNoList[j];
                (*m_rdbTable).GetAt(RcdNo, (SG_SHORT)index, &bus_temp);
                if (bus_temp >= 207000000000001 && bus_temp <= 207000000000062)
                    break;
            }
            /// 在这里项参数库添加参数
            str = "INSERT INTO dev.operation_result (APPID,OF_DEVICE,P,Q,DESCRIPTION,TYPE) VALUES (314," +
                  to_string(bus_temp) + "," + to_string(m_consumer_added[i].mpower_p) + "," + to_string(m_consumer_added[i].mpower_q) + ",\"" + m_consumer_added[i].name +
                  "\",2)";
            //cout<<str<<endl;
            Req.SQLBuf.Format(str.c_str());
            m_DBClient.RDB_ExecSQL(Req, Res);
            FieldValList.clear();
        }
        
    }

    CloseTable((*m_rdbTable));
}

// TN类方法

// 这是一个无辜的由于需求不被明确写了一上午的无效类
//  float TopologicalNode::getVltMax(const CalCaseDataOp &rdbTable)
//  {
//      float vlt_max = 0;
//      // 打开model_conn_node表
//      OpenTable(rdbTable.getRDBTable(), "model_conn_node");
//      // 由于tn节点电压等级相同，根据id查找tn节点查找其所包含的第一个cn节点的OF_BASE_VOLTAGE（SG_INT64）并存储
//      // 根据条件查找
//      // 根据主键查找
//      VECT_STRINT64 FieldValList;
//      S_STRINT64 FieldVal;
//      FieldVal.StrVal = "ID";
//      FieldVal.IntVal = contains_connectivity_nodes[0];
//      FieldValList.push_back(FieldVal);
//      VECT_INT RcdNoList;
//      if (rdbTable.GetRcdNoByFieldVal(FieldValList, RcdNoList))
//      {
//          int index;
//          int RcdNo;
//          SG_INT64 vlt_temp;
//          for (int i = 0; i < RcdNoList.size(); i++)
//          {
//              index = rdbTable.GetFieldPtr("OF_BASE_VOLTAGE");
//              RcdNo = RcdNoList[i];
//              rdbTable.GetAt(RcdNo, (SG_SHORT)index, &vlt_temp);
//              // cout<<"OF_BASE_VOLTAGE="<<vlt_temp<<endl;
//          }
//      }
//      // 关闭model_conn_node表，打开base_volt_def表，根据id查找对应的H_LMT并存储
//      CloseTable(rdbTable.getRDBTable());
//      OpenTable(rdbTable.getRDBTable(), "base_volt_def");
//      VECT_STRINT64 FieldValList1;
//      S_STRINT64 FieldVal1;
//      FieldVal1.StrVal = "ID";
//      FieldVal1.IntVal = vlt_temp;
//      FieldValList1.push_back(FieldVal1);
//      VECT_INT RcdNoList1;
//      if (rdbTable.GetRcdNoByFieldVal(FieldValList1, RcdNoList1))
//      {
//          int index1;
//          int RcdNo1;
//          for (int i = 0; i < RcdNoList1.size(); i++)
//          {
//              index1 = rdbTable.GetFieldPtr("H_LMT");
//              RcdNo1 = RcdNoList[i];
//              rdbTable.GetAt(RcdNo1, (SG_SHORT)index1, &vlt_max);
//              // cout<<"OF_BASE_VOLTAGE="<<vlt_temp<<endl;
//          }
//      }
//      // 关闭base_volt_def表
//      CloseTable(rdbTable.getRDBTable());
//      // 返回电压值上限
//      return vlt_max;
//  }
// 构造函数

// 构造函数
// 这个n是什么意思？
// 获取第n行的值
TopologicalNode::TopologicalNode(CalCaseDataOp &rdbTable, int n)
{
    rdbTable.OpenTable(rdbTable.getRDBTable(), "model_topological_node");
    int index;
    index = rdbTable.getRDBTable().GetFieldPtr("ID");
    rdbTable.getRDBTable().GetAt(n, (SG_SHORT)index, &m_ID);

    // cout << "TN id:" << ID << endl;
    index = rdbTable.getRDBTable().GetFieldPtr("OF_TOPOLOGICALISLAND");
    rdbTable.getRDBTable().GetAt(n, (SG_SHORT)index, &m_of_topologicalisland);

    // cout << "TN of_topologicalisland:" << of_topologicalisland << endl;
    rdbTable.CloseTable(rdbTable.getRDBTable());
    // 获取所包含的CN节点值
    rdbTable.OpenTable(rdbTable.getRDBTable(), "model_conn_node");
    VECT_STRINT64 FieldValList;
    S_STRINT64 FieldVal;
    FieldVal.StrVal = "OF_TOPOLOGICALNODE";
    FieldVal.IntVal = m_ID;
    FieldValList.push_back(FieldVal);
    VECT_INT RcdNoList;
    if (rdbTable.getRDBTable().GetRcdNoByFieldVal(FieldValList, RcdNoList))
    {
        int index;
        int RcdNo;
        SG_INT64 temp;
        for (int i = 0; i < RcdNoList.size(); i++)
        {
            index = rdbTable.getRDBTable().GetFieldPtr("ID");
            RcdNo = RcdNoList[i];
            rdbTable.getRDBTable().GetAt(RcdNo, (SG_SHORT)index, &temp);
            // cout<<"OF_BASE_VOLTAGE="<<vlt_temp<<endl;
            m_contains_connectivity_nodes.push_back(temp);
            m_contains_connectivity_nodes_position.push_back(RcdNo);
            m_contains_connectivity_nodes_status.push_back(rdbTable.get_w_conn()[RcdNo]);
            if (rdbTable.get_w_conn()[RcdNo] == 1)
            {
                m_useable++;
                m_contains_connectivity_nodes_allowed.push_back(temp);
            }
        }
    }
    rdbTable.CloseTable(rdbTable.getRDBTable());
}
// 析构
TopologicalNode::~TopologicalNode()
{
}
// 获取tn节点标准电压
float TopologicalNode::getSTD_VAL(CalCaseDataOp &rdbTable)
{
    float vlt = 0;
    // 打开model_conn_node表
    rdbTable.OpenTable(rdbTable.getRDBTable(), "model_conn_node");
    // 由于tn节点电压等级相同，根据id查找tn节点查找其所包含的第一个cn节点的OF_BASE_VOLTAGE（SG_INT64）并存储
    // 根据条件查找
    // 根据主键查找
    VECT_STRINT64 FieldValList;
    S_STRINT64 FieldVal;
    FieldVal.StrVal = "ID";
    FieldVal.IntVal = m_contains_connectivity_nodes[0];
    FieldValList.push_back(FieldVal);
    VECT_INT RcdNoList;
    SG_INT64 vlt_temp;
    if (rdbTable.getRDBTable().GetRcdNoByFieldVal(FieldValList, RcdNoList))
    {
        int index;
        int RcdNo;

        for (int i = 0; i < RcdNoList.size(); i++)
        {
            index = rdbTable.getRDBTable().GetFieldPtr("OF_BASE_VOLTAGE");
            RcdNo = RcdNoList[i];
            rdbTable.getRDBTable().GetAt(RcdNo, (SG_SHORT)index, &vlt_temp);
            // cout<<"OF_BASE_VOLTAGE="<<vlt_temp<<endl;
        }
    }
    // 关闭model_conn_node表，打开base_volt_def表，根据id查找对应的H_LMT并存储
    rdbTable.CloseTable(rdbTable.getRDBTable());
    rdbTable.OpenTable(rdbTable.getRDBTable(), "base_volt_def");

    // 这一块写的有点着急，写的很差，debug了半天，变量名一定要好好设计
    VECT_STRINT64 FieldValList1;
    S_STRINT64 FieldVal1;
    FieldVal1.StrVal = "ID";
    FieldVal1.IntVal = vlt_temp;
    FieldValList1.push_back(FieldVal1);
    VECT_INT RcdNoList1;
    if (rdbTable.getRDBTable().GetRcdNoByFieldVal(FieldValList1, RcdNoList1))
    {
        int index1;
        int RcdNo1;
        for (int i = 0; i < RcdNoList1.size(); i++)
        {
            index1 = rdbTable.getRDBTable().GetFieldPtr("STD_VAL");
            RcdNo1 = RcdNoList1[i];
            rdbTable.getRDBTable().GetAt(RcdNo1, (SG_SHORT)index1, &vlt);
            // cout<<"OF_BASE_VOLTAGE="<<vlt_temp<<endl;
        }
    }
    // 关闭base_volt_def表
    rdbTable.CloseTable(rdbTable.getRDBTable());
    // 返回电压值上限
    return vlt;
}

float TopologicalNode::getVltMax(CalCaseDataOp &rdbTable)
{
    float temp = TopologicalNode::getSTD_VAL(rdbTable);
    temp *= 1.10;
    return temp;
}

float TopologicalNode::getVltMin(CalCaseDataOp &rdbTable)
{
    float temp = TopologicalNode::getSTD_VAL(rdbTable);
    temp *= 0.90;
    return temp;
}

bool TopologicalNode::VoltageJudge(CalCaseDataOp &rdbTable)
{
    float vlt_temp = 0;
    // 电压值判断
    // 电压值上限
    float vlt_max = TopologicalNode::getVltMax(rdbTable);
    // 电压值下限
    float vlt_min = TopologicalNode::getVltMin(rdbTable);
    // 获取tn节点电压
    // 打开表
    rdbTable.OpenTable(rdbTable.getRDBTable(), "model_topological_node");
    // 读取当前电压
    VECT_STRINT64 FieldValList;
    S_STRINT64 FieldVal;
    FieldVal.StrVal = "ID";
    FieldVal.IntVal = m_ID;
    FieldValList.push_back(FieldVal);
    VECT_INT RcdNoList;
    if (rdbTable.getRDBTable().GetRcdNoByFieldVal(FieldValList, RcdNoList))
    {
        int index;
        int RcdNo;
        for (int i = 0; i < RcdNoList.size(); i++)
        {
            index = rdbTable.getRDBTable().GetFieldPtr("VLTMAG");
            RcdNo = RcdNoList[i];
            rdbTable.getRDBTable().GetAt(RcdNo, (SG_SHORT)index, &vlt_temp);
            // cout<<"OF_BASE_VOLTAGE="<<vlt_temp<<endl;
        }
    }

    vlt_temp *= 10;
    // 关表
    rdbTable.CloseTable(rdbTable.getRDBTable());
    // 判断范围
    if (vlt_temp > vlt_max || vlt_temp < vlt_min)
        return false;
    return true;
}
