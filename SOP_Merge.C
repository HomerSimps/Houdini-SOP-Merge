
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
#include <GA/GA_Range.h>
#include <iostream>




using namespace HDK_Sample;

void
newSopOperator(OP_OperatorTable *table)
{
     table->addOperator(new OP_Operator(
        "merge_wca",
        "Merge WCA",
        SOP_Merge_s::myConstructor,
        SOP_Merge_s::myTemplateList,
        0,
        OP_MULTI_INPUT_MAX,
        0,
        OP_FLAG_UNORDERED));
}


static PRM_Name classParmNames[] = {
    PRM_Name("detail","Detail"),
    PRM_Name("primitive","Primitive"),
    PRM_Name("point","Point"),
    PRM_Name("vertex","Vertex"),
    PRM_Name(0)

};

static PRM_Name TypeParmNames[] = {
    PRM_Name("float","Float"),
    PRM_Name("integer","Integer"),
    PRM_Name("string","String"),
    PRM_Name(0)

};



// Creatig Parms
static PRM_ChoiceList sopClassMenu(PRM_CHOICELIST_SINGLE,classParmNames);
static PRM_ChoiceList sopTypeMenu(PRM_CHOICELIST_SINGLE,TypeParmNames);

static PRM_Default    sopClassDefult(SOP_CLASS_POINT);
static PRM_Default    sopTypeDefult(SOP_TYPE_INT);
static PRM_Default    sopAttribNameDef(0,"attribute#");
static PRM_Default    sopPrefixbNameDef(0,"prefix_");
static PRM_Name menuNames[] = 
{
    PRM_Name("numAttribs","Number of Attributes"),
    PRM_Name("name_#","Name"),
    PRM_Name("class_#","Class"),
    PRM_Name("type_#","Type"),        
    PRM_Name("str_prefix_#","String Prefix"),    
    PRM_Name(0)

};

static PRM_Template multiParmTemp[] = 
{
    PRM_Template(PRM_STRING,1,&menuNames[1],&sopAttribNameDef),
    PRM_Template(PRM_ORD,1,&menuNames[2],&sopClassDefult,&sopClassMenu),
    PRM_Template(PRM_ORD,1,&menuNames[3],&sopTypeDefult,&sopTypeMenu),        
    PRM_Template(PRM_STRING,1,&menuNames[4],&sopPrefixbNameDef),    
    PRM_Template()    
};


PRM_Template
SOP_Merge_s::myTemplateList[] = {

    PRM_Template(PRM_MULTITYPE_LIST,multiParmTemp,2,&menuNames[0],PRMoneDefaults),
                 
    
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


//Changeing Parm Flags
bool SOP_Merge_s::updateParmsFlags() {

    bool changed;
    

    for (int i = 1; i <= GET_NUMBER_OF_ATTRIB();++i){

        bool disb = (GET_TYPE(i) == SOP_TYPE_STRING) ? true : false;
        changed |= enableParmInst(menuNames[4].getToken(),&i,disb);
    }


    return changed;
}

OP_ERROR
SOP_Merge_s::cookMySop(OP_Context &context)
{
    OP_AutoLockInputs inputs(this);
    if (inputs.lock(context) >= UT_ERROR_ABORT)
        return error();
    
    fpreal t = context.getTime();

    int number_of_Inputs = nInputs();
    
    bool cpoiedfirst = false;
    bool cpoiedlast =  false;
      
    
    for (int n = 0; n < number_of_Inputs;++n) {
        
        const GU_Detail *inputGdp = inputGeo(n);
    
        GU_Detail blanks_gdp;
        blanks_gdp.copy(*inputGdp,GEO_COPY_END,true,false,GA_DATA_ID_CLONE);

        
        for (int nat = 1; nat <= GET_NUMBER_OF_ATTRIB();++nat) {
            
            GA_AttributeOwner attribowner;
            switch ( GET_CLASS(nat))
            {
            case SOP_CLASS_POINT:
                attribowner = GA_ATTRIB_POINT;                
                break;
            case SOP_CLASS_DETAIL:
                attribowner = GA_ATTRIB_DETAIL;
                break;
            case SOP_CLASS_PRIMITIVE:
                attribowner = GA_ATTRIB_PRIMITIVE;
                break;
            case SOP_CLASS_VERTEX:
                attribowner = GA_ATTRIB_VERTEX;
                break;            
            }

            UT_String attribName;
            GET_NAME(attribName,nat,t);

            UT_String ParmPrefix;

            GA_RWHandleI attribINT;
            GA_RWHandleF attribFloat;
            GA_RWHandleS attribString;

            switch (GET_TYPE((nat)))
            {
            //Crate Attrib for INT     
            case SOP_TYPE_INT:

                attribINT = GA_RWHandleI(blanks_gdp.findIntTuple(attribowner,attribName,-1,-1));
                if (attribINT.isInvalid())
                {                       
                    attribINT = blanks_gdp.addIntTuple(attribowner,attribName,1,GA_Defaults(n));                   
                  
                }

                if (attribINT.isInvalid()){
                    UT_WorkBuffer buf;
                    buf.sprintf("Failed to create Int attributes \"%s\"",(const char*) attribName);
                    
                }

                break;
            //Crate Attrib for Float 
            case SOP_TYPE_FLOAT:

                attribFloat = GA_RWHandleF(blanks_gdp.findIntTuple(attribowner,attribName,-1,-1));
                if (attribFloat.isInvalid()) {                       
                    attribFloat = blanks_gdp.addFloatTuple(attribowner,attribName,1,GA_Defaults(static_cast<fpreal>(n)));           
                }

                if (attribFloat.isInvalid()) {
                    UT_WorkBuffer buf;
                    buf.sprintf("Failed to create Float attributes \"%s\"",(const char*) attribName);    
               
                }             
                        
                break;
            //Crate Attrib for String 
            case SOP_TYPE_STRING:

                    attribString = GA_RWHandleS(blanks_gdp.findStringTuple(attribowner,attribName,-1,-1));
                    if(attribString.isInvalid()){   
                        attribString = GA_RWHandleS(blanks_gdp.addStringTuple(attribowner,attribName,1));
                    }
                    if(attribString.isInvalid()){   
                            UT_WorkBuffer buf;
                            buf.sprintf("Failed to create string attributes \"%s\"",(const char*) attribName);    
                        
                    }
                    
                    GET_PREFIX(ParmPrefix,nat,t);                    
                    for (int  i= 0; i <blanks_gdp.getNumPoints();++i ) {                        
                        attribString.set(blanks_gdp.pointOffset(i),ParmPrefix.c_str() + std::to_string(n));
                    }

                break;
            
            }
            //bump attribs

            attribINT.bumpDataId();
            attribFloat.bumpDataId();
            attribString.bumpDataId();

        }
        
        
        
        
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
