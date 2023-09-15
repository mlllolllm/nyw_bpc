
#include <chrono>
#include "BPC.h"

int main()
{
    // ≈‰÷√
    SG_INT64 SchemaHandler = 1011;
    CRDBLoadSetting loadSetting;
    CDpf dpf_op(314, "DPF");
    loadSetting.LoadType = 0;
    loadSetting.RtDBVerNo = 5;
    loadSetting.SchemaDBNo = 2;
    loadSetting.SchemaType = SG_RDB_DBTYPE_CALCCASE;
    loadSetting.SchemaProcMode = SG_RDB_SCHEMA_PROCMODE_CANFREE;
    loadSetting.SrvTypeStr = "3";

    dpf_op.Init(SchemaHandler,&loadSetting);

    CalCaseDataOp rdbTable(dpf_op, SchemaHandler, loadSetting);

    rdbTable.ReadConfig();

    rdbTable.Read();

    rdbTable.Exec();

    rdbTable.Write();

    

    return 0;
}
