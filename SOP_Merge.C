
#include "SOP_Merge.h"

#include <GU/GU_Detail.h>
#include <GA/GA_Handle.h>
#include <OP/OP_AutoLockInputs.h>
#include <OP/OP_Director.h>
#include <OP/OP_Operator.h>
#include <OP/OP_OperatorTable.h>
#include <PRM/PRM_Include.h>
#include <UT/UT_DSOVersion.h>
#include <SYS/SYS_Math.h>
#include <iostream>
#include <GA/GA_Range.h>

using namespace HDK_Sample;

void
newSopOperator(OP_OperatorTable *table)
{
     table->addOperator(new OP_Operator(
        "cpp_merge",
        "CPP Merge",
        SOP_Merge_s::myConstructor,
        SOP_Merge_s::myTemplateList,
        1,
        OP_MULTI_INPUT_MAX,
        0,
        OP_FLAG_UNORDERED));
}

PRM_Template
SOP_Merge_s::myTemplateList[] = {
    PRM_Template(),
};


OP_Node *
SOP_Merge_s::myConstructor(OP_Network *net, const char *name, OP_Operator *op)
{
    return new SOP_Merge_s(net, name, op);
}

SOP_Merge_s::SOP_Merge_s(OP_Network *net, const char *name, OP_Operator *op)
    : SOP_Node(net, name, op)
{
    mySopFlags.setManagesDataIDs(true);
}

SOP_Merge_s::~SOP_Merge_s()
{
}

OP_ERROR
SOP_Merge_s::cookMySop(OP_Context &context)
{
    OP_AutoLockInputs inputs(this);
    if (inputs.lock(context) >= UT_ERROR_ABORT)
        return error();
    int number_of_Inputs = nInputs();
    std::cout<<"number_of_Inputs"<<number_of_Inputs<<"\n";
    bool cpoiedfirst = false;
    bool cpoiedlast =  false;
    for (int n = 0; n < number_of_Inputs;++n) {
        
        const GU_Detail *inputGdp = inputGeo(n);
    
        GU_Detail blanks_gdp;
        blanks_gdp.copy(*inputGdp,GEO_COPY_END,true,false,GA_DATA_ID_CLONE);
        blanks_gdp.addIntTuple(GA_ATTRIB_POINT,"idx",1,GA_Defaults(n));
        GEO_CopyMethod copymethod = GEO_COPY_ADD;
        if (!cpoiedfirst) {
           copymethod = GEO_COPY_START;
            cpoiedfirst = true;
            if (n == number_of_Inputs){
               copymethod = GEO_COPY_ONCE;
               cpoiedlast = true; 
            }

        }
        else if(n == number_of_Inputs) {
            copymethod = GEO_COPY_END;
            cpoiedlast = true;
        }
        GA_IndexMap::Marker pointmarker(gdp->getPointMap());
        GA_IndexMap::Marker primmarker(gdp->getPrimitiveMap());

        gdp->copy(blanks_gdp,copymethod,true,false,GA_DATA_ID_CLONE);
        blanks_gdp.clearAndDestroy();


    }

    if (!cpoiedfirst){
        gdp->clearAndDestroy();

    }
    else if (!cpoiedlast){
        GU_Detail blank_gdp;
        gdp->copy(blank_gdp,GEO_COPY_END,true,false,GA_DATA_ID_CLONE);
  
    }

    
    return error();
}
