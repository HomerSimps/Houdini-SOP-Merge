/* Automagically Generated by generate_proto.py
 * Do not Edit
 */
#pragma once

#include <SOP/SOP_NodeVerb.h>
#include <SOP/SOP_GraphProxy.h>

#include <OP/OP_Utils.h>
#include <PRM/PRM_Parm.h>
#include <UT/UT_IStream.h>
#include <UT/UT_NTStreamUtil.h>
#include <UT/UT_Ramp.h>
#include <UT/UT_SharedPtr.h>
#include <UT/UT_StringHolder.h>
#include <UT/UT_StringStream.h>
#include <UT/UT_VectorTypes.h>
#include <UT/UT_EnvControl.h>
#include <SYS/SYS_Types.h>

class DEP_MicroNode;
namespace SOP_MergeSEnums
{
    enum class Class
    {
        DETAIL = 0,
        PRIM,
        POINT,
        VERTEX
    };
    enum class Type
    {
        FLOAT = 0,
        INT,
        STRING
    };
}


class  SOP_MergeSParms  : public SOP_NodeParms
{
public:
    static int version() { return 1; }
    struct Numattribs
    {
        UT_StringHolder name;
        int64 _class;
        int64 type;
        UT_StringHolder prefix;


        Numattribs()
        {
            name = "attribute#"_UTsh;
            _class = 2;
            type = 1;
            prefix = "prefix"_UTsh;

        }

        bool operator==(const Numattribs &src) const
        {
            if (name != src.name) return false;
            if (_class != src._class) return false;
            if (type != src.type) return false;
            if (prefix != src.prefix) return false;

            return true;
        }
        bool operator!=(const Numattribs &src) const
        {
            return !operator==(src);
        }

    };

    UT_StringHolder createString(const UT_Array<Numattribs> &list) const
    {
        UT_WorkBuffer   buf;

        buf.strcat("[ ");
        for (int i = 0; i < list.entries(); i++)
        {
            if (i)
                buf.strcat(", ");
            buf.strcat("( ");
            buf.append("");
            { UT_String tmp; tmp = UT_StringWrap(list(i).name).makeQuotedString('"'); buf.strcat(tmp); }
            buf.append(", ");
            buf.appendSprintf("%d", (int) list(i)._class);
            buf.append(", ");
            buf.appendSprintf("%d", (int) list(i).type);
            buf.append(", ");
            { UT_String tmp; tmp = UT_StringWrap(list(i).prefix).makeQuotedString('"'); buf.strcat(tmp); }

            buf.strcat(" )");
        }
        buf.strcat(" ]");

        UT_StringHolder result = buf;
        return result;
    }

    SOP_MergeSParms()
    {
        myNumattribs.setSize(1);

    }

    explicit SOP_MergeSParms(const SOP_MergeSParms &) = default;
    SOP_MergeSParms &operator=(const SOP_MergeSParms &) = default;
    SOP_MergeSParms(SOP_MergeSParms &&) noexcept = default;
    SOP_MergeSParms &operator=(SOP_MergeSParms &&) noexcept = default;

    ~SOP_MergeSParms() override {}

    bool operator==(const SOP_MergeSParms &src) const
    {
        if (myNumattribs != src.myNumattribs) return false;

        return true;
    }
    bool operator!=(const SOP_MergeSParms &src) const
    {
        return !operator==(src);
    }
    using Class = SOP_MergeSEnums::Class;
    using Type = SOP_MergeSEnums::Type;



    void        buildFromOp(const OP_GraphProxy *graph, exint nodeidx, fpreal time, DEP_MicroNode *depnode)
    {
        if (true)
        {
            int64   length = 0;
            graph->evalOpParm(length, nodeidx, "numattribs", time, 0);
            if (length < 0) length = 0;
            myNumattribs.setSize(length);
            for (exint i = 0; i < length; i++)
            {
                int     parmidx[1];
                int     offsets[1];
                parmidx[0] = i+1;
                offsets[0] = 1;
                auto && _curentry = myNumattribs(i);
                (void) _curentry;
                _curentry.name = "attribute#"_UTsh;
                if (true)
                    graph->evalOpParmInst(_curentry.name, nodeidx, "name#", parmidx, offsets, time, 0, 2-1);
                _curentry._class = 2;
                if (true)
                    graph->evalOpParmInst(_curentry._class, nodeidx, "class#", parmidx, offsets, time, 0, 2-1);
                _curentry.type = 1;
                if (true)
                    graph->evalOpParmInst(_curentry.type, nodeidx, "type#", parmidx, offsets, time, 0, 2-1);
                _curentry.prefix = "prefix"_UTsh;
                if (true)
                    graph->evalOpParmInst(_curentry.prefix, nodeidx, "prefix#", parmidx, offsets, time, 0, 2-1);

            }
        }
        else
            myNumattribs.clear();

    }


    void loadFromOpSubclass(const LoadParms &loadparms) override
    {
        buildFromOp(loadparms.graph(), loadparms.nodeIdx(), loadparms.context().getTime(), loadparms.depnode());
    }


    void copyFrom(const OP_NodeParms *src) override
    {
        *this = *((const SOP_MergeSParms *)src);
    }

    template <typename T>
    void
    doGetParmValue(TempIndex idx, TempIndex instance, T &value) const
    {
        if (idx.size() < 1)
            return;
        UT_ASSERT(idx.size() == instance.size()+1);
        if (idx.size() != instance.size()+1)
            return;
        switch (idx[0])
        {
            case 0:
                if (idx.size() == 1)
                    coerceValue(value, myNumattribs.entries());
                else if (instance[0] < myNumattribs.entries())
                {
                    auto && _data = myNumattribs(instance[0]);
                    switch (idx[1])
                    {
                    case 0:
                        coerceValue(value, _data.name);
                        break;
                    case 1:
                        coerceValue(value, _data._class);
                        break;
                    case 2:
                        coerceValue(value, _data.type);
                        break;
                    case 3:
                        coerceValue(value, _data.prefix);
                        break;

                    }
                }
                break;

        }
    }

    void getNestParmValue(TempIndex idx, TempIndex instance, exint &value) const override
    { doGetParmValue(idx, instance, value); }
    void getNestParmValue(TempIndex idx, TempIndex instance, fpreal &value) const override
    { doGetParmValue(idx, instance, value); }
    void getNestParmValue(TempIndex idx, TempIndex instance, UT_Vector2D &value) const override
    { doGetParmValue(idx, instance, value); }
    void getNestParmValue(TempIndex idx, TempIndex instance, UT_Vector3D &value) const override
    { doGetParmValue(idx, instance, value); }
    void getNestParmValue(TempIndex idx, TempIndex instance, UT_Vector4D &value) const override
    { doGetParmValue(idx, instance, value); }
    void getNestParmValue(TempIndex idx, TempIndex instance, UT_Matrix2D &value) const override
    { doGetParmValue(idx, instance, value); }
    void getNestParmValue(TempIndex idx, TempIndex instance, UT_Matrix3D &value) const override
    { doGetParmValue(idx, instance, value); }
    void getNestParmValue(TempIndex idx, TempIndex instance, UT_Matrix4D &value) const override
    { doGetParmValue(idx, instance, value); }
    void getNestParmValue(TempIndex idx, TempIndex instance, UT_StringHolder &value) const override
    { doGetParmValue(idx, instance, value); }
    void getNestParmValue(TempIndex idx, TempIndex instance, UT_SharedPtr<UT_Ramp> &value) const override
    { doGetParmValue(idx, instance, value); }
    void getNestParmValue(TempIndex idx, TempIndex instance, PRM_DataItemHandle &value) const override
    { doGetParmValue(idx, instance, value); }

    template <typename T>
    void
    doSetParmValue(TempIndex idx, TempIndex instance, const T &value) 
    {
        if (idx.size() < 1)
            return;
        UT_ASSERT(idx.size() == instance.size()+1);
        if (idx.size() != instance.size()+1)
            return;
        switch (idx[0])
        {
            case 0:
                if (idx.size() == 1)
                {
                    exint       newsize;
                    coerceValue(newsize, value);
                    if (newsize < 0) newsize = 0;
                    myNumattribs.setSize(newsize);
                }
                else
                {
                    if (instance[0] < 0)
                        return;
                    myNumattribs.setSizeIfNeeded(instance[0]+1);
                    auto && _data = myNumattribs(instance[0]);
                    switch (idx[1])
                    {
                    case 0:
                        coerceValue(_data.name, value);
                        break;
                    case 1:
                        coerceValue(_data._class, value);
                        break;
                    case 2:
                        coerceValue(_data.type, value);
                        break;
                    case 3:
                        coerceValue(_data.prefix, value);
                        break;

                    }
                }
                break;

        }
    }

    void setNestParmValue(TempIndex idx, TempIndex instance, const exint &value)  override
    { doSetParmValue(idx, instance, value); }
    void setNestParmValue(TempIndex idx, TempIndex instance, const fpreal &value)  override
    { doSetParmValue(idx, instance, value); }
    void setNestParmValue(TempIndex idx, TempIndex instance, const UT_Vector2D &value)  override
    { doSetParmValue(idx, instance, value); }
    void setNestParmValue(TempIndex idx, TempIndex instance, const UT_Vector3D &value)  override
    { doSetParmValue(idx, instance, value); }
    void setNestParmValue(TempIndex idx, TempIndex instance, const UT_Vector4D &value)  override
    { doSetParmValue(idx, instance, value); }
    void setNestParmValue(TempIndex idx, TempIndex instance, const UT_Matrix2D &value)  override
    { doSetParmValue(idx, instance, value); }
    void setNestParmValue(TempIndex idx, TempIndex instance, const UT_Matrix3D &value)  override
    { doSetParmValue(idx, instance, value); }
    void setNestParmValue(TempIndex idx, TempIndex instance, const UT_Matrix4D &value)  override
    { doSetParmValue(idx, instance, value); }
    void setNestParmValue(TempIndex idx, TempIndex instance, const UT_StringHolder &value)  override
    { doSetParmValue(idx, instance, value); }
    void setNestParmValue(TempIndex idx, TempIndex instance, const UT_SharedPtr<UT_Ramp> &value)  override
    { doSetParmValue(idx, instance, value); }
    void setNestParmValue(TempIndex idx, TempIndex instance, const PRM_DataItemHandle &value)  override
    { doSetParmValue(idx, instance, value); }

    exint getNestNumParms(TempIndex idx) const override
    {
        if (idx.size() == 0)
            return 1;
        switch (idx[0])
        {
            case 0:
                return 4;

        }
        // Invalid
        return 0;
    }

    const char *getNestParmName(TempIndex fieldnum) const override
    {
        if (fieldnum.size() < 1)
            return 0;
        switch (fieldnum[0])
        {
            case 0:
                if (fieldnum.size() == 1)
                    return "numattribs";
                switch (fieldnum[1])
                {
                    case 0:
                        return "name#";
                    case 1:
                        return "class#";
                    case 2:
                        return "type#";
                    case 3:
                        return "prefix#";

                }
                return 0;

        }
        return 0;
    }

    ParmType getNestParmType(TempIndex fieldnum) const override
    {
        if (fieldnum.size() < 1)
            return PARM_UNSUPPORTED;
        switch (fieldnum[0])
        {
            case 0:
                if (fieldnum.size() == 1)
                    return PARM_MULTIPARM;
                switch (fieldnum[1])
                {
                    case 0:
                        return PARM_STRING;
                    case 1:
                        return PARM_INTEGER;
                    case 2:
                        return PARM_INTEGER;
                    case 3:
                        return PARM_STRING;

                }
                return PARM_UNSUPPORTED;

        }
        return PARM_UNSUPPORTED;
    }

    // Boiler plate to load individual types.
    static void  loadData(UT_IStream &is, int64 &v)
    { is.bread(&v, 1); }
    static void  loadData(UT_IStream &is, bool &v)
    { int64     iv; is.bread(&iv, 1); v = iv; }
    static void  loadData(UT_IStream &is, fpreal64 &v)
    { is.bread<fpreal64>(&v, 1); }
    static void  loadData(UT_IStream &is, UT_Vector2D &v)
    { is.bread<fpreal64>(&v.x(), 1); is.bread<fpreal64>(&v.y(), 1); }
    static void  loadData(UT_IStream &is, UT_Vector3D &v)
    { is.bread<fpreal64>(&v.x(), 1); is.bread<fpreal64>(&v.y(), 1);
      is.bread<fpreal64>(&v.z(), 1); }
    static void  loadData(UT_IStream &is, UT_Vector4D &v)
    { is.bread<fpreal64>(&v.x(), 1); is.bread<fpreal64>(&v.y(), 1);
      is.bread<fpreal64>(&v.z(), 1); is.bread<fpreal64>(&v.w(), 1); }
    static void  loadData(UT_IStream &is, UT_Matrix2D &v)
    { for (int r = 0; r < 2; r++) for (int c = 0; c < 2; c++) is.bread<fpreal64>(&v(r, c), 1); }
    static void  loadData(UT_IStream &is, UT_Matrix3D &v)
    { for (int r = 0; r < 3; r++) for (int c = 0; c < 3; c++) is.bread<fpreal64>(&v(r, c), 1); }
    static void  loadData(UT_IStream &is, UT_Matrix4D &v)
    { for (int r = 0; r < 4; r++) for (int c = 0; c < 4; c++) is.bread<fpreal64>(&v(r, c), 1); }
    static void  loadData(UT_IStream &is, UT_Vector2I &v)
    { is.bread<int64>(&v.x(), 1); is.bread<int64>(&v.y(), 1); }
    static void  loadData(UT_IStream &is, UT_Vector3I &v)
    { is.bread<int64>(&v.x(), 1); is.bread<int64>(&v.y(), 1);
      is.bread<int64>(&v.z(), 1); }
    static void  loadData(UT_IStream &is, UT_Vector4I &v)
    { is.bread<int64>(&v.x(), 1); is.bread<int64>(&v.y(), 1);
      is.bread<int64>(&v.z(), 1); is.bread<int64>(&v.w(), 1); }
    static void  loadData(UT_IStream &is, UT_StringHolder &v)
    { is.bread(v); }
    static void  loadData(UT_IStream &is, UT_SharedPtr<UT_Ramp> &v)
    {   UT_StringHolder   rampdata;
        loadData(is, rampdata);
        if (rampdata.isstring())
        {
            v.reset(new UT_Ramp());
            UT_IStream  istr((const char *) rampdata, rampdata.length(), UT_ISTREAM_ASCII);
            v->load(istr);
        }
        else v.reset();
    }
    static void  loadData(UT_IStream &is, PRM_DataItemHandle &v)
    {   UT_StringHolder   data;
        loadData(is, data);
        if (data.isstring())
        {
            // Find the data type.
            const char *colon = UT_StringWrap(data).findChar(':');
            if (colon)
            {
                int             typelen = colon - data.buffer();
                UT_WorkBuffer   type;
                type.strncpy(data.buffer(), typelen);
                UT_IStream  istr(((const char *) data) + typelen + 1, data.length() - (typelen + 1), UT_ISTREAM_BINARY);
                
                v = PRM_DataFactory::parseBinary(type.buffer(), istr);
            }
        }
        else v.reset();
    }

    static void  saveData(std::ostream &os, int64 v)
    { UTwrite(os, &v); }
    static void  saveData(std::ostream &os, bool v)
    { int64 iv = v; UTwrite(os, &iv); }
    static void  saveData(std::ostream &os, fpreal64 v)
    { UTwrite<fpreal64>(os, &v); }
    static void  saveData(std::ostream &os, UT_Vector2D v)
    { UTwrite<fpreal64>(os, &v.x()); UTwrite<fpreal64>(os, &v.y()); }
    static void  saveData(std::ostream &os, UT_Vector3D v)
    { UTwrite<fpreal64>(os, &v.x()); UTwrite<fpreal64>(os, &v.y());
      UTwrite<fpreal64>(os, &v.z()); }
    static void  saveData(std::ostream &os, UT_Vector4D v)
    { UTwrite<fpreal64>(os, &v.x()); UTwrite<fpreal64>(os, &v.y());
      UTwrite<fpreal64>(os, &v.z()); UTwrite<fpreal64>(os, &v.w()); }
    static void  saveData(std::ostream &os, UT_Matrix2D v)
    { for (int r = 0; r < 2; r++) for (int c = 0; c < 2; c++) UTwrite<fpreal64>(os, &v(r, c)); }
    static void  saveData(std::ostream &os, UT_Matrix3D v)
    { for (int r = 0; r < 3; r++) for (int c = 0; c < 3; c++) UTwrite<fpreal64>(os, &v(r, c)); }
    static void  saveData(std::ostream &os, UT_Matrix4D v)
    { for (int r = 0; r < 4; r++) for (int c = 0; c < 4; c++) UTwrite<fpreal64>(os, &v(r, c)); }
    static void  saveData(std::ostream &os, UT_StringHolder s)
    { UT_StringWrap(s).saveBinary(os); }
    static void  saveData(std::ostream &os, UT_SharedPtr<UT_Ramp> s)
    {   UT_StringHolder         result;
        UT_OStringStream        ostr;
        if (s) s->save(ostr);
        result = ostr.str();
        saveData(os, result);
    }
    static void  saveData(std::ostream &os, PRM_DataItemHandle s)
    {   UT_StringHolder         result;
        UT_OStringStream        ostr;
        if (s) 
        {
            ostr << s->getDataTypeToken();
            ostr << ":";
            s->saveBinary(ostr);
        }
        result = ostr.str();
        saveData(os, result);
    }


    void         save(std::ostream &os) const
    {
        int32           v = version();
        UTwrite(os, &v);
        {
            int64   length = myNumattribs.entries();
            UTwrite(os, &length);
            for (exint i = 0; i < length; i++)
            {
                auto && _curentry = myNumattribs(i);
                (void) _curentry;
                saveData(os, _curentry.name);
                saveData(os, _curentry._class);
                saveData(os, _curentry.type);
                saveData(os, _curentry.prefix);

            }
        }

    }

    bool         load(UT_IStream &is)
    {
        int32           v;
        is.bread(&v, 1);
        if (version() != v)
        {
            // Fail incompatible versions
            return false;
        }
        {
            int64   length;
            is.read(&length, 1);
            myNumattribs.setSize(length);
            for (exint i = 0; i < length; i++)
            {
                auto && _curentry = myNumattribs(i);
                (void) _curentry;
                loadData(is, _curentry.name);
                loadData(is, _curentry._class);
                loadData(is, _curentry.type);
                loadData(is, _curentry.prefix);

            }
        }

        return true;
    }

    const UT_Array<Numattribs> &getNumattribs() const { return myNumattribs; }
void setNumattribs(const UT_Array<Numattribs> &val) { myNumattribs = val; }
    exint opNumattribs(const SOP_NodeVerb::CookParms &cookparms) const
    { 
        SOP_Node *thissop = cookparms.getNode();
        if (!thissop) return getNumattribs().entries();
        exint result;
        OP_Utils::evalOpParm(result, thissop, "numattribs", cookparms.getCookTime(), 0);
        return result;
    }
        UT_StringHolder opNumattribs_name(const SOP_NodeVerb::CookParms &cookparms, int _idx) const
    { return opinstNumattribs_name(cookparms, &_idx); }
    UT_StringHolder opinstNumattribs_name(const SOP_NodeVerb::CookParms &cookparms, const int *_idx) const
    {
        SOP_Node *thissop = cookparms.getNode();
        if (!thissop) return (myNumattribs(_idx[0]).name);
        int _parmidx[2-1];
        _parmidx[1-1] = _idx[1-1] + 1;

        UT_StringHolder result;
        OP_Utils::evalOpParmInst(result, thissop, "name#", _parmidx, cookparms.getCookTime(), 0, 2-1);
        return (result);
    }
    int64 opNumattribs__class(const SOP_NodeVerb::CookParms &cookparms, int _idx) const
    { return opinstNumattribs__class(cookparms, &_idx); }
    int64 opinstNumattribs__class(const SOP_NodeVerb::CookParms &cookparms, const int *_idx) const
    {
        SOP_Node *thissop = cookparms.getNode();
        if (!thissop) return (myNumattribs(_idx[0])._class);
        int _parmidx[2-1];
        _parmidx[1-1] = _idx[1-1] + 1;

        int64 result;
        OP_Utils::evalOpParmInst(result, thissop, "class#", _parmidx, cookparms.getCookTime(), 0, 2-1);
        return (result);
    }
    int64 opNumattribs_type(const SOP_NodeVerb::CookParms &cookparms, int _idx) const
    { return opinstNumattribs_type(cookparms, &_idx); }
    int64 opinstNumattribs_type(const SOP_NodeVerb::CookParms &cookparms, const int *_idx) const
    {
        SOP_Node *thissop = cookparms.getNode();
        if (!thissop) return (myNumattribs(_idx[0]).type);
        int _parmidx[2-1];
        _parmidx[1-1] = _idx[1-1] + 1;

        int64 result;
        OP_Utils::evalOpParmInst(result, thissop, "type#", _parmidx, cookparms.getCookTime(), 0, 2-1);
        return (result);
    }
    UT_StringHolder opNumattribs_prefix(const SOP_NodeVerb::CookParms &cookparms, int _idx) const
    { return opinstNumattribs_prefix(cookparms, &_idx); }
    UT_StringHolder opinstNumattribs_prefix(const SOP_NodeVerb::CookParms &cookparms, const int *_idx) const
    {
        SOP_Node *thissop = cookparms.getNode();
        if (!thissop) return (myNumattribs(_idx[0]).prefix);
        int _parmidx[2-1];
        _parmidx[1-1] = _idx[1-1] + 1;

        UT_StringHolder result;
        OP_Utils::evalOpParmInst(result, thissop, "prefix#", _parmidx, cookparms.getCookTime(), 0, 2-1);
        return (result);
    }


private:
    UT_Array<Numattribs> myNumattribs;

};
