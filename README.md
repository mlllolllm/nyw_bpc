# nyw_bpc
配网线路负荷（新建负荷、电动汽车充电桩等）最佳接入位置选择



## 环境及结构：

Compilers recommended：
Visual Studio code（便于连接虚拟机进行实时库操作）
vmware workstation（所安装操作系统为centos7，请不要使用8，会出现部分包问题）
请注意由于调用实时库所需，main.cpp建议以gb2312打开，CalCaseDataOp.cpp与BPC.h建议以utf-8打开，否则会出现乱码
主要文件结构为：
--code
		--app

​			--das

​				--BPC

​					--main.cpp

​					--BPC.srv

​					--Makefile

​				--BPClib

​					--CalCaseDataOp.cpp

​					--geneticalAlgorithm.cpp

​					--Makefile

--code

​		--include

​			--BPC

​				--BPC.h

## 配置方法

鉴于属于公司内部项目，没有vpn是无法完整运行的。外部人员请参考代码思路（小小小小的思路），其中主要实现功能的文件位于/home/devapp/nproject/code/app/das的两个文件夹中，BPC是本地运行使用的main文件，BPClib是方法的主要实现，BPC下进行make将生成可执行文件，BPClib下执行make将生成动态库，所生成均位于devapp/app/bin中
1. 在虚拟机上新建devapp用户，将所有文件夹拷贝至devapp用户根目录下(/home/devapp)
2. 连接vpn，设置网络：
ifconfig virbr0 down
brctl delbr virbr0
systemctl disable libvirtd
3. 于app/bin目录下先后执行命令
./dppsrv
hda -d
为数据库服务命令，需常驻
4. 于/home/devapp/nproject/code/app/das/BPC下执行make -B,在/app/bin目录下运行BPC文件（或者在vscode中打开code文件夹，其中的.vscode都是配置好的，直接运行即可）

## 文件描述：

BPC(Best Position Choose)项目用于实现针对已存电网在提供对应负荷的情况下提供最佳接入位置选择方案。
项目文件主要为：

main.cpp作为主函数完成对应功能

CalCaseDataOp.cpp用于进行类功能实现，主要是针对实时库进行系列操作

BPC.h提供类定义与类方法原型

geneticalAlgorithm.cpp是遗传算法主要内容

BPC.srv是项目记录的一种方式

## 更新日志：
**2023.9.5
- 参数命名优化，改死我了
- 合并文件结构并更改lib的makefile，以便生成动态库
**2023.9.4
- 新增根据可接入位置表控制信息输入
- 在配置文件中新增属性交叉率，变异率与时间限制
**2023.8.28-2023.9.1
- 更新输出文件方式至在文件尾添加，便于测试
- 重新构建GA类，赋予其数据操作功能
- 将友元函数改为类方法
- 将部分静态函数改为友元
- 修改输出方式，新增输出至文件的方式
- 修改原先设计，将部分写死数据进行重新读取
- 添加配置文件数据，虽然我一点都不想这样
- 缩减代码结构，规范化，将GA类与Chrom类合并到数据库操作类中
- 修改负荷插入方式，改为由数据库读入
- 将创库配置变为可更改
**8.21-8.25
- 优化了遗传算法相应参数以大幅缩短时间
- 删除system("pause")
- 更新了部分功能，在程序输出时将输出tn所包含的cn节点，该功能会增加一定的时间开销
- 更新了电压判断方式以减少开销
- 优化了输出，减少部分控制台无意义输出




