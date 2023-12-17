/*
 * Copyright (c) 2023
 *	Side Effects Software Inc.  All rights reserved.
 *
 * Redistribution and use of Houdini Development Kit samples in source and
 * binary forms, with or without modification, are permitted provided that the
 * following conditions are met:
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. The name of Side Effects Software may not be used to endorse or
 *    promote products derived from this software without specific prior
 *    written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY SIDE EFFECTS SOFTWARE `AS IS' AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN
 * NO EVENT SHALL SIDE EFFECTS SOFTWARE BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *----------------------------------------------------------------------------
 *
 */

#ifndef __SOP_Merge_s_h__
#define __SOP_Merge_s_h__

#include <SOP/SOP_Node.h>

namespace HDK_Sample {


    enum {
        SOP_CLASS_DETAIL,
        SOP_CLASS_PRIMITIVE,
        SOP_CLASS_POINT,
        SOP_CLASS_VERTEX
    };
    enum{
        SOP_TYPE_FLOAT,
        SOP_TYPE_INT,        
        SOP_TYPE_STRING

    };



class SOP_Merge_s : public SOP_Node
{
public:
    SOP_Merge_s(OP_Network *net, const char *name, OP_Operator *op);
    ~SOP_Merge_s() override;

    static PRM_Template myTemplateList[];
    static OP_Node *myConstructor(OP_Network*, const char *, OP_Operator *);
    bool updateParmsFlags() override;

protected:
    OP_ERROR cookMySop(OP_Context &context) override;
private:

    int GET_NUMBER_OF_ATTRIB () { return evalInt("numAttribs",0,0.0f); }
    void setNUMAttribs(int num_attribs){
        setInt("numAttribs",0,0.0f,num_attribs);
    }
    void GET_NAME(UT_String &str,int i,fpreal t){
        return evalStringInst("name_#",&i,str,0,t);
    }

 
    int GET_CLASS(int i){
        return evalIntInst("class_#",&i,0,0.0f);
    }
    int GET_TYPE(int i){
        return evalIntInst("type_#",&i,0,0.0f);
    }
   
    void GET_PREFIX(UT_String &str,int i,fpreal t){
        return evalStringInst("str_prefix_#",&i,str,0,t);
    }



    
};
} // End of HDK_Sample namespace

#endif
