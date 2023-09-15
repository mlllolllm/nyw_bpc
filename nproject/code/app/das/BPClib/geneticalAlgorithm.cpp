#include "BPC.h"

GA::GA()
{
}

GA::~GA()
{
}

Chrom GA::geneticAlgorithm(CalCaseDataOp &rdbTable)
{
    Chrom res;
    GA temp_ga;
    vector<Chrom> tmp_group=rdbTable.get_ini_group();
    double CrossoverProbability=rdbTable.get_CrossoverProbability();
    double MutationProbability=rdbTable.get_MutationProbability();
    int group_num=rdbTable.get_m_group_num();
    const int LoadNum = rdbTable.get_LoadListSize();
    srand(time(0));
    int random;
    int i, j;
    //
    double Min = numeric_limits<double>::max();

    // 开始迭代
    for (int k = 0; k < rdbTable.get_times(); k++)
    {
        cout << "第 " << k + 1 << "次迭代结果：" << endl;
        cout << Min << endl;
        int men;
        // 对染色体排序，选出排名靠前的四分之一进行交叉变异产生子代
        int i;
        int j;
        double p;
        int row, col;
        sort(tmp_group.begin(), tmp_group.end(), [](const Chrom &a, const Chrom &b)
             { return a.fit < b.fit; });

        if(rdbTable.get_crossoverFunc()==0)
        tmp_group=temp_ga.single_point_crossover(rdbTable,tmp_group);
        else if(rdbTable.get_crossoverFunc()==1)
        tmp_group=temp_ga.two_points_crossover(rdbTable,tmp_group);

        
        if(rdbTable.get_mutationFunc()==0)
        tmp_group=temp_ga.mutationFunc1(rdbTable,tmp_group);
        else if(rdbTable.get_mutationFunc()==1)
        tmp_group=temp_ga.mutationFunc2(rdbTable,tmp_group);
        // 种群更替；
        for (j = 0; j < group_num; j++)
        {
            // sum = 0.0;
            // for (vector<int>::iterator it = group[j].Load.begin(); it != group[j].Load.end(); it++)
            // {
            // 	sum += sin(0.1*(*it));
            // }
            // 更新数据库
            // 将接入位置写入端子表
            rdbTable.model_terminal_add_fromChrom(tmp_group[j]);

            // 调用拓扑
            // 调用潮流
            rdbTable.getdpf().Exec();

            // 更新fit值
            if (!rdbTable.vltJudgeOverall())
                tmp_group[j].fit = numeric_limits<double>::max();
            else
                tmp_group[j].fit = rdbTable.networkLossCountByTI(); // 初始化 fit 为网速的导数

            // 删除端子表新增节点
            rdbTable.model_terminal_delete_fromChrom(tmp_group[j]);
            if (tmp_group[j].fit < Min)
            {
                // m_res = group[j];
                std::copy(tmp_group[j].Load.begin(), tmp_group[j].Load.end(), std::back_inserter(res.Load));
                res.fit = tmp_group[j].fit;
                Min = tmp_group[j].fit;
            }
        }
    }

    return res;
}

// 单点交叉
vector<Chrom> &GA::single_point_crossover(CalCaseDataOp &rdbTable, vector<Chrom> &temp_group)
{
    double CrossoverProbability = rdbTable.get_CrossoverProbability();
    double MutationProbability = rdbTable.get_MutationProbability();
    int group_num = rdbTable.get_m_group_num();
    const int LoadNum = rdbTable.get_LoadListSize();
    int row, col;
    int random;
    int l;
     int quarter_group = group_num / 4;
    int half_group = group_num / 2;
    srand(time(0));
    for (l = group_num / 4; l < group_num / 2; l++)
    {
        random = rand() % 100;
        if (random < (100 * CrossoverProbability))
        {
            row = rand() % (group_num / 4);
            col = rand() % LoadNum;
            for (int m = 0; m < col; m++)
            {
                temp_group[l].Load[m] = temp_group[l - group_num / 4].Load[m];
            }
            for (int m = col; m < LoadNum; m++)
            {
                temp_group[l].Load[m] = temp_group[row].Load[m];
            }
        }
    }

    return temp_group;
}

// vector<Chrom> &GA::two_points_crossover(CalCaseDataOp &rdbTable, vector<Chrom> &temp_group)
// {
//     double CrossoverProbability = rdbTable.get_CrossoverProbability();
//     double MutationProbability = rdbTable.get_MutationProbability();
//     int group_num = rdbTable.get_m_group_num();
//     const int LoadNum = rdbTable.get_LoadListSize();
//     int row, col;
//     srand(time(0));
//         for(int i = 0; i < group_num/4; i++)
//         {
//             temp_group[i + 3 * group_num/4] = temp_group[i];
//         }
//         for(int l = group_num / 4; l < group_num / 2; l++)
//         {   
//             int start = rand() % (LoadNum - 1);
//             int maxEnd = LoadNum - 1;
//             int range = maxEnd - start;
//             int end = start + rand() % (range + 1);
//             if ((rand() % 100) < (100 * CrossoverProbability))
//             {
//                 row = rand() % (group_num / 4);
//                 for(int i = start; i < end ; i++)
//                 {
//                     int temp = temp_group[l].Load[i];
//                     temp_group[l].Load[i] = temp_group[l - group_num / 4].Load[i];
//                     temp_group[l - group_num / 4].Load[i] = temp;
//                 }
//             }
//         }
//     return temp_group;
// }

//双点交叉
vector<Chrom> &GA::two_points_crossover(CalCaseDataOp &rdbTable, vector<Chrom> &temp_group)
{
    double CrossoverProbability = rdbTable.get_CrossoverProbability();
    int group_num = rdbTable.get_m_group_num();
    const int LoadNum = rdbTable.get_LoadListSize();

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> rand_prob(0, 1);
    std::uniform_int_distribution<> rand_start(0, LoadNum - 2);
    std::uniform_int_distribution<> rand_range(1, LoadNum - 1);

    int quarter_group = group_num / 4;
    int half_group = group_num / 2;

    for (int i = 0; i < quarter_group; i++)
    {
        temp_group[i + 3 * quarter_group] = temp_group[i];
    }

    for (int l = quarter_group; l < half_group; l++)
    {
        int start = rand_start(gen);
        int range = rand_range(gen);
        int end = std::min(start + range, LoadNum - 1);
        if (rand_prob(gen) < CrossoverProbability)
        {
            int row = rand() % quarter_group;
            for (int i = start; i <= end; i++)
            {
                int temp = temp_group[l].Load[i];
                temp_group[l].Load[i] = temp_group[l - quarter_group].Load[i];
                temp_group[l - quarter_group].Load[i] = temp;
            }
        }
    }

    return temp_group;
}

//变异

vector<Chrom> &GA::mutationFunc1(CalCaseDataOp &rdbTable, vector<Chrom> &temp_group)
{
    Chrom res;
    double CrossoverProbability = rdbTable.get_CrossoverProbability();
    double MutationProbability = rdbTable.get_MutationProbability();
    int group_num = rdbTable.get_m_group_num();
    const int LoadNum = rdbTable.get_LoadListSize();
    srand(time(0));
    int random;
    int i, j;
    int row, col;

    for (int m = group_num / 2; m < group_num; m++)
    {
        if ((rand() % 100) < (CrossoverProbability * 100))
        {
            temp_group[m] = temp_group[m - group_num / 2];
            col = rand() % LoadNum;
            temp_group[m].Load[col] = rand() % rdbTable.get_tn_num();
        }
    }
    return temp_group;
}

vector<Chrom> &GA::mutationFunc2(CalCaseDataOp &rdbTable, vector<Chrom> &temp_group)
{

    double CrossoverProbability = rdbTable.get_CrossoverProbability();
    double MutationProbability = rdbTable.get_MutationProbability();
    int group_num = rdbTable.get_m_group_num();
    const int LoadNum = rdbTable.get_LoadListSize();
    int row, col;

    return temp_group;
}

