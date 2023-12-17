#pragma once
#include <SOP/SOP_Node.h>
#include <UT/UT_StringHolder.h>


namespace HDK_Sample{

    class SOP_MergeS : public SOP_Node
    {

    public:
        static PRM_Template *buildTemplates();
        static OP_Node *myConstructor(OP_Network *net,const char *name,OP_Operator *op){
            return new SOP_MergeS(net,name,op);

        }
        static const UT_StringHolder theSOPTypeName;
        const SOP_NodeVerb *cookVerb() const override;
    protected:


        SOP_MergeS(OP_Network *net,const char *name,OP_Operator *op) 
            : SOP_Node(net,name,op)
            {

                mySopFlags.setManagesDataIDs(true);
                

            }

            ~SOP_MergeS() override {}
            OP_ERROR cookMySop(OP_Context &context) override
            {
                return cookMyselfAsVerb(context);
            }

    };

    
}