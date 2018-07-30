#include "KD_cl_harness_forthao_breach_capi_host.h"
static KD_cl_harness_forthao_breach_host_DataMapInfo_T root;
static int initialized = 0;
rtwCAPI_ModelMappingInfo *getRootMappingInfo()
{
    if (initialized == 0) {
        initialized = 1;
        KD_cl_harness_forthao_breach_host_InitializeDataMapInfo(&(root), "KD_cl_harness_forthao_breach");
    }
    return &root.mmi;
}

rtwCAPI_ModelMappingInfo *mexFunction() {return(getRootMappingInfo());}
