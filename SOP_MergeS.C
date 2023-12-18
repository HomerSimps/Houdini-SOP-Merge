#include "SOP_MergeS.h"

#include "SOP_MergeS.proto.h"

#include <GU/GU_Detail.h>
#include <OP/OP_Operator.h>
#include <OP/OP_OperatorTable.h>
#include <PRM/PRM_Include.h>
#include <PRM/PRM_TemplateBuilder.h>
#include <UT/UT_DSOVersion.h>
#include <UT/UT_Interrupt.h>
#include <UT/UT_StringHolder.h>
#include <limits.h>
#include <iostream>


using namespace HDK_Sample;

const UT_StringHolder SOP_MergeS::theSOPTypeName("merge_wca");

void
newSopOperator(OP_OperatorTable *table) {
    table->addOperator(new OP_Operator(
        SOP_MergeS::theSOPTypeName,
        "Merge",
        SOP_MergeS::myConstructor,
        SOP_MergeS::buildTemplates(),
        0,
        MAX_INPUT,
        nullptr,
        OP_FLAG_UNORDERED
    ));

}

static const char *theDsFile = R"THEDSFILE(

{
    name        parameters
    multiparm {
        name    "numattribs"
        label   "Number of Attributes"
        default { "1" }
        parm {
            name    "name#"
            label   "Name"
            type    string
            default { "attribute#" }
        }
        parm {
            name    "class#"
            label   "Class" 
            type    ordinal
            default { "2" }     
            menu    {
                "detail"  "Detail"
                "prim"  "Primitive"
                "point" "Point"
                "vertex"    "Vertex"  
            }  
            
        }

        parm {
            name    "type#"
            label   "Type" 
            type    ordinal
            default { "1" }     
            menu    {
                "int"   "Integer"
                "float" "Float"
                "string"    "String"                  
            }  
            
        }

        parm {
            name    "prefix#"
            label   "Prefix"
            type    string
            default { "prefix" }
        }
        parm {
            name    "separtor#"
            type    separator
        }
                
    }
}
)THEDSFILE";

PRM_Template *  
SOP_MergeS::buildTemplates(){

    static PRM_TemplateBuilder templ("SOP_MergeS.C",theDsFile);
    return templ.templates();

}

class SOP_MergeSVerb : public SOP_NodeVerb
{
public:
    SOP_MergeSVerb(){}
    virtual ~SOP_MergeSVerb(){}
    
    virtual SOP_NodeParms *allocParms() const {return new SOP_MergeSParms(); }
    virtual UT_StringHolder name()  const {return SOP_MergeS::theSOPTypeName; }

    virtual CookMode    cookMode(const SOP_NodeParms *parms) const {return COOK_GENERIC; }

    virtual void    cook(const CookParms &cookparms) const;

    static const SOP_NodeVerb::Register<SOP_MergeSVerb> theVerb;


};


const SOP_NodeVerb::Register<SOP_MergeSVerb> SOP_MergeSVerb::theVerb;


const SOP_NodeVerb *
SOP_MergeS::cookVerb() const{

    return SOP_MergeSVerb::theVerb.get();

}

void SOP_MergeSVerb::cook(const SOP_NodeVerb::CookParms &cookparms) const 
{

    auto &&sopparms = cookparms.parms<SOP_MergeSParms>();

    GU_Detail *gdp = cookparms.gdh().gdpNC();


    const int number_of_Inputs = cookparms.nInputs();    
    bool cpoiedfirst = false;
    bool cpoiedlast =  false;
    
    for (int n = 0; n < number_of_Inputs;++n) {
      
        
        const GU_Detail *inputGdp = cookparms.inputGeo(n);
    
    
        GU_Detail blanks_gdp;
        blanks_gdp.copy(*inputGdp,GEO_COPY_END,true,false,GA_DATA_ID_CLONE);

        std::cout<<blanks_gdp.getNumPoints();    
    
    

    for (auto i : sopparms.getNumattribs()){        

        GA_AttributeOwner attribowner;
        switch (i._class)
        {
        case 0:
            std::cout<<"1 - attribdetail\n";
            attribowner = GA_ATTRIB_DETAIL;
                            
            break;
        case 1:
            std::cout<<"2 - attribPrimitive\n";
            attribowner = GA_ATTRIB_PRIMITIVE;
            break;
        case 2:
            std::cout<<"3 - attribPoint\n";
            attribowner = GA_ATTRIB_POINT;
            
            break;
        case 3:
            std::cout<<"4 - attribVertex\n";
            attribowner = GA_ATTRIB_VERTEX;
            break;            
        }

        UT_String attribName(i.name);
        

        UT_String ParmPrefix(i.prefix);

        GA_RWHandleI attribINT;
        GA_RWHandleF attribFloat;
        GA_RWHandleS attribString;

            
            switch (i.type)
            {
            //Crate Attrib for INT     
            case 0:

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
            case 1:

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
            case 2:

                    attribString = GA_RWHandleS(blanks_gdp.findStringTuple(attribowner,attribName,-1,-1));
                    if(attribString.isInvalid()){   
                        attribString = GA_RWHandleS(blanks_gdp.addStringTuple(attribowner,attribName,1));
                    }
                    if(attribString.isInvalid()){   
                            UT_WorkBuffer buf;
                            buf.sprintf("Failed to create string attributes \"%s\"",(const char*) attribName);    
                        
                    }
                    
                  
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
    else if (!cpoiedlast) {
        GU_Detail blank_gdp;
        gdp->copy(blank_gdp,GEO_COPY_END,true,false,GA_DATA_ID_CLONE);
  
    }


}




