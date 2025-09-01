/**
 * @file:       TypeCode.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#ifndef TypeCode_h__
#define TypeCode_h__

#include "ZRDDSCommon.h"
#include "TypeCodeKind.h"

typedef struct TypeCodeHeader TypeCodeHeader;


typedef struct TypeObject TypeObject;

namespace DDS {

class TypeCode;

#ifdef _ZRDDS_INCLUDE_TYPECODE
class DCPSDLL TypeCode
{
public:
	virtual ~TypeCode() {}

    /**
     * @fn  virtual TCTypeKind getKind() const = 0;
     *
     * @brief   ��ȡTypeCode��ʾ������.
     *
     * @author  Hzy
     * @date    2016/7/5
     *
     * @return  TC�����͡�
     */

    virtual TCTypeKind getKind() const = 0;

    /**
     * @fn  virtual ZR_BOOLEAN compare(const TypeCode* typeCode2) const = 0;
     *
     * @brief   �Ƚ�����TypeCode�Ƿ�ָ���ʾͬһ���ṹ.
     *
     * @author  Hzy
     * @date    2016/7/5
     *
     * @param   typeCode2   �ڶ���TypeCode��
     *
     * @return  true��ʾ��ȣ�false��ʾ����ȡ�
     */

    virtual ZR_BOOLEAN compare(const TypeCode* typeCode2) const = 0;

    /**
     * @fn  virtual const ZR_INT8* getName() const = 0;
     *
     * @brief   ��ȡTypeCode�����ƣ�ֻ֧��union/struct/enum���͡�
     *
     * @author  Hzy
     * @date    2016/7/5
     *
     * @return  NULL��ʾʧ�ܣ������ʾ���ơ�
     */

    virtual const ZR_INT8* getName() const = 0;

    /**
     * @fn  virtual ZR_INT32 getMemberCount() const = 0;
     *
     * @brief   ��ȡTypeCode��ʾ�����ͳ�Ա������ֻ֧��union/struct/enum���͡�
     *
     * @author  Hzy
     * @date    2016/7/6
     *
     * @return  С��0��ʾʧ�ܣ�����Ϊ��Чֵ.
     */

    virtual ZR_INT32 getMemberCount() const = 0;

    /**
     * @fn  virtual const ZR_INT8* getMemberName(ZR_UINT32 index) const = 0;
     *
     * @brief   ��ȡָ���±��Ա������.
     *
     * @author  Hzy
     * @date    2016/7/6
     *
     * @param   index   Ŀ���Ա�±ꡣ
     *
     * @return  NULL��ʾʧ�ܣ�����Ϊ��Ч�ĳ�Ա����ָ�롣
     */

    virtual const ZR_INT8* getMemberName(ZR_UINT32 index) const = 0;

    /**
     * @fn  virtual ZR_INT32 getIndexByName(const ZR_INT8* name) const = 0;
     *
     * @brief   ͨ����Ա���ƻ�ȡ�±��0��ʼ.
     *
     * @author  Hzy
     * @date    2016/7/6
     *
     * @param   name    ��Ա���ơ�
     *
     * @return  С�����ʾʧ�ܣ�����Ϊ��Ч���±ꡣ
     */

    virtual ZR_INT32 getIndexByName(const ZR_INT8* name) const = 0;

    /**
     * @fn  virtual TypeCode* getMemberType(ZR_UINT32 index) const = 0;
     *
     * @brief   ��ȡָ���±��Ա��TypeCode.
     *
     * @author  Hzy
     * @date    2016/7/6
     *
     * @param   index   ��ʾ�±ꡣ
     *
     * @return  NULL��ʾʧ�ܣ������ʾ�ɹ���
     */

    virtual TypeCode* getMemberType(ZR_UINT32 index) const = 0;

    /**
     * @fn  virtual ZR_INT32 getLabelCount(ZR_UINT32 index) const = 0;
     *
     * @brief   ��ȡUnion����ָ���ĳ�Ա��label��������Ч���� - 1.
     *
     * @author  Hzy
     * @date    2016/7/6
     *
     * @param   index   ָ���±ꡣ
     *
     * @return  A ZR_INT32.
     */

    virtual ZR_INT32 getLabelCount(ZR_UINT32 index) const = 0;

    /**
     * @fn  virtual ZR_INT32 getLabel( ZR_UINT32 memberIdx, ZR_UINT32 labelIdx, TypeCodeExceptionCode* expCode) const = 0;
     *
     * @brief   ��ȡUnion��Ա��label.
     *
     * @author  Hzy
     * @date    2016/7/6
     *
     * @param   memberIdx       ��Ա�±ꡣ
     * @param   labelIdx        ��ǩ�±ꡣ
     * @param [in,out]  expCode �����Ƿ���Ч��������Ϊ������Ч��Ҫ������Чֵ��
     *
     * @return  ���expCode��Ч���򷵻�ֵΪlabel������÷���ֵ��Ч��
     */

    virtual ZR_INT32 getLabel(
        ZR_UINT32 memberIdx,
        ZR_UINT32 labelIdx,
        TypeCodeExceptionCode* expCode) const = 0;

    /**
     * @fn  virtual ZR_INT32 getDefaultIndex() const = 0;
     *
     * @brief   ��ȡUnion���͵�Ĭ���±�.
     *
     * @author  Hzy
     * @date    2016/7/6
     *
     * @return  -1��ʾʧ�ܣ�����Ϊ��Ч���±ꡣ
     */

    virtual ZR_INT32 getDefaultIndex() const = 0;

    /**
     * @fn  virtual ZR_INT32 getEnumVal( ZR_UINT32 memberIdx, TypeCodeExceptionCode* expCode) const = 0;
     *
     * @brief   ��ȡö��ֵ��ֵ��
     *
     * @author  Hzy
     * @date    2016/7/6
     *
     * @param   memberIdx       ��Ա�±ꡣ
     * @param [in,out]  expCode �����Ƿ���Ч��������Ϊ������Ч��Ҫ������Чֵ��
     *
     * @return  ���expCode��Ч���򷵻�ֵΪö�ٵ�ֵ������÷���ֵ��Ч��
     */

    virtual ZR_INT32 getEnumVal(
        ZR_UINT32 memberIdx,
        TypeCodeExceptionCode* expCode) const = 0;

    /**
     * @fn  virtual const ZR_INT8* TypeCode::getEnumString(const TypeCode* self, ZR_UINT32 memberIdx, TypeCodeExceptionCode* expCode) const = 0;
     *
     * @brief   ��ȡö�ٳ�Ա��Ӧ���ַ�����
     *
     * @author  Hzy
     * @date    2018/3/16
     *
     * @param   enumVal       ö��ֵ��
     * @param [in,out]  expCode ���expCode��Ч���򷵻�ֵΪö�ٵ�ֵ������÷���ֵ��Ч��
     *
     * @return  NULL��ʾʧ�ܣ������ʾö���ַ���ֵ��
     */

    virtual const ZR_INT8* getEnumString(
        ZR_UINT32 enumVal,
        TypeCodeExceptionCode* expCode) const = 0;

    /**
     * @fn  virtual ZR_BOOLEAN isMemberKey( ZR_UINT32 index, TypeCodeExceptionCode* expCode) const = 0;
     *
     * @brief   ��ȡָ���ṹ���Ա�Ƿ���key��.
     *
     * @author  Hzy
     * @date    2016/7/6
     *
     * @param   index           ָ���Ա�±ꡣ
     * @param [in,out]  expCode �����Ƿ���Ч��������Ϊ������Ч��Ҫ������Чֵ��
     *
     * @return  ���expCode��Ч���򷵻�ֵΪʱ����key�򣬷���÷���ֵ��Ч��
     */

    virtual ZR_BOOLEAN isMemberKey(
        ZR_UINT32 index,
        TypeCodeExceptionCode* expCode) const = 0;

    /**
     * @fn  virtual ZR_INT32 getArrayDimensionCount() const = 0;
     *
     * @brief   ��ȡ�������͵�ά�ȡ�
     *
     * @author  Hzy
     * @date    2016/7/6
     *
     * @return  С��0��ʾ��Ч,�����ʾά�ȡ�
     */

    virtual ZR_INT32 getArrayDimensionCount() const = 0;

    /**
     * @fn  virtual ZR_INT32 getArrayDimension(ZR_UINT32 index) const = 0;
     *
     * @brief   ��ȡָ���±�ά�ȵ�ά��.
     *
     * @author  Hzy
     * @date    2016/7/6
     *
     * @param   index   ָ��ά�ȡ�
     *
     * @return  С�����ʾʧ�ܣ�����Ϊ��Ч��ά����
     */

    virtual ZR_INT32 getArrayDimension(ZR_UINT32 index) const = 0;

    /**
     * @fn  virtual ZR_INT32 getMaxLength() const = 0;
     *
     * @brief   ��ȡ������󳤶ȣ�֧��string�Լ�sequence��
     *
     * @author  Hzy
     * @date    2018/2/6
     *
     * @return  -1��ʾʧ�ܣ�����0��ʾ��󳤶ȡ�
     */

    virtual ZR_INT32 getMaxLength() const = 0;

    /**
     * @fn  virtual const TypeCode* getBaseType() const = 0;
     *
     * @brief   ��ȡTypeCode���ṹ����������VALUE_TYPE.
     *
     * @author  Hzy
     * @date    2016/12/13
     *
     * @return  NULL��ʾ��ȡʧ�ܣ�����ִ�и��ṹ���ࡣ
     */

    virtual const TypeCode* getBaseType() const = 0;

    /**
     * @fn  virtual const TypeCode* getElementType() const = 0;
     *
     * @brief   ��ȡԪ�����ͣ�������sequence�Լ�array���͡�
     *
     * @author  Hzy
     * @date    2016/12/13
     *
     * @return  NULL��ʾʧ�ܣ�����ָ��Ԫ��.
     */

    virtual const TypeCode* getElementType() const = 0;

    /**
     * @fn virtual ZR_INT32 TypeCode::addMemberToEnum( ZR_UINT32 index, const ZR_INT8* name, ZR_UINT32 value) = 0;
     *
     * @brief   ��ö��������ӳ�Ա.
     *
     * @author  Hzy
     * @date    2016/7/6
     *
     * @param   index   ָ����ӵ�λ�ã����ڵ�ǰ��Ա�����������β����
     * @param   name    ��Ա���ơ�
     * @param   value   ��ӵĳ�Աֵ��
     *
     * @return  ����0��ʾ��Ӻ�ö�ٳ�Ա������С��0��ʾʧ��.
     */

    virtual ZR_INT32 addMemberToEnum(
        ZR_UINT32 index,
        const ZR_INT8* name,
        ZR_UINT32 value) = 0;

    /**
     * @fn virtual ZR_INT32 TypeCode::addMemberToUnion( ZR_UINT32 index, const ZR_INT8* name, ZR_UINT32 labelCount, ZR_UINT32* labels, const TypeCode* tc) = 0;
     *
     * @brief   ������������ӳ�Ա.
     *
     * @author  Hzy
     * @date    2016/7/6
     *
     * @param   index           ָ����ӵ�λ�ã����ڵ�ǰ��Ա�����������β����
     * @param   name            ��Ա�����ơ�
     * @param   labelCount      �ó�Ա��ǩ������
     * @param [in,out]  labels  �ó�Ա�ı�ǩ���顣
     * @param   tc              �ó�Ա�����͡�
     *
     * @return  ������Ӻ����ϳ�Ա������С��0��ʾʧ�ܡ�
     */

    virtual ZR_INT32 addMemberToUnion(ZR_UINT32 index, const ZR_INT8* name, ZR_UINT32 labelCount, ZR_UINT32* labels, const TypeCode* tc) = 0;

    /**
     * @fn virtual ZR_INT32 TypeCode::addMemberToStruct( ZR_UINT32 index, const ZR_INT8* name, const TypeCode* tc, ZR_BOOLEAN isKey) = 0;
     *
     * @brief   ��ṹ��������ӳ�Ա.
     *
     * @author  Hzy
     * @date    2016/7/6
     *
     * @param   index           ָ����ӵ�λ�ã����ڵ�ǰ��Ա�����������β����
     * @param   memberId        ָ���ó�Ա��Id, -1��ʾ���±�һ�¡�
     * @param   name            ��Ա�����ơ�
     * @param   tc              ��Ա���͡�
     * @param   isKey           �ó�Ա�Ƿ���key��
     * @param   isOption        �ó�Ա�Ƿ��ǿ�ѡ�ġ�
     *
     * @return  ������Ӻ�ṹ���Ա������С��0��ʾʧ�ܡ�
     */

    virtual ZR_INT32 addMemberToStruct(ZR_UINT32 index,
        ZR_UINT32 memberId,
        const ZR_INT8* name,
        const TypeCode* tc,
        ZR_BOOLEAN isKey,
        ZR_BOOLEAN isOption) = 0;

    /**
     * @fn  virtual ZR_INT32 TypeCode::addMemberToValueType(ZR_UINT32 index, ZR_UINT32 memberId, const ZR_INT8* name, const TypeCodeHeader* tc, ZR_BOOLEAN isKey, ZR_BOOLEAN isOption);
     *
     * @brief   ��ValueType������ӳ�Ա.
     *
     * @author  Rainnus
     * @date    2016/10/21
     *
     * @param   index           ָ����ӵ�λ�ã����ڵ�ǰ��Ա�����������β����
     * @param   memberId        ָ���ó�Ա��Id, -1��ʾ���±�һ�¡�
     * @param   name            ��Ա�����ơ�
     * @param   tc              ��Ա���͡�
     * @param   isKey           �ó�Ա�Ƿ���key��
     * @param   isOption        �ó�Ա�Ƿ��ǿ�ѡ�ġ�
     *
     * @return  ������Ӻ�ValueType��Ա������С��0��ʾʧ�ܡ�
     */

    virtual ZR_INT32 addMemberToValueType(ZR_UINT32 index, ZR_UINT32 memberId,
        const ZR_INT8* name,
        const TypeCode* tc,
        ZR_BOOLEAN isKey,
        ZR_BOOLEAN isOption) = 0;

    /**
     * @fn virtual ZR_INT32 TypeCode::printIDL() = 0;
     *
     * @brief   ��ӡָ����TypeCode.
     *
     * @author  Hzy
     * @date    2016/7/6
     *
     * @return  С�����ʾ��ӡ����0��ʾ��ӡ�ɹ���
     */

    virtual ZR_INT32 printIDL() const = 0;

    /**
     * @fn  virtual ZR_INT8* TypeCode::getPrintableString() = 0;
     *
     * @brief   ��ȡ�ȼ۵�IDL�ļ����ݵĻ��������˷��������سɹ�����������releasePrintableString�����ͷſռ䡣
     *
     * @author  Hzy
     * @date    2016/12/13
     *
     * @return  NULL��ȡʧ�ܣ�����ָ�����ݡ�
     */

    virtual ZR_INT8* getPrintableString() const = 0;

    /**
     * @fn  virtual void TypeCode::releasePrintableString(ZR_INT8* buffer) = 0;
     *
     * @brief   �ͷ���TypeCodeGetTypePrintableString�ײ㴴���Ŀռ䡣
     *
     * @author  Hzy
     * @date    2016/12/13
     *
     * @param [in,out]  buffer  ָ����TypeCodeGetTypePrintableString���صĿռ䡣
     */

    virtual void releasePrintableString(ZR_INT8* buffer) const = 0;

    /**
     * @fn  virtual TypeCodeHeader* TypeCode::getImpl() = 0;
     *
     * @brief   ��ȡ�ײ�ʵ����
     *
     * @author  Hzy
     * @date    2016/10/18
     *
     * @return  �����ĵײ�ʵ�֡�
     */

    virtual TypeCodeHeader* getImpl() = 0;

    /**
     * @fn virtual ZR_BOOLEAN TypeCodeFactory::hasKey() = 0;
     *
     * @brief �ж������Ƿ����key�򣬽���struct type��value type��Ч���������;�����false
     *
     * @author Tim
     * @date 17/11/16
     *
     * @return A ZR_BOOLEAN
     */
    virtual ZR_BOOLEAN hasKey() const = 0;
};

class DCPSDLL TypeCodeFactory
{
public:
    virtual ~TypeCodeFactory(){}
    /**
     * @fn  static TypeCodeFactory& TypeCodeFactory::getInstance();
     *
     * @brief   ��ȡTypeCodeFactory�ĵ���.
     *
     * @author  Hzy
     * @date    2016/7/6
     *
     * @return  NULL��ʾʧ�ܣ�����ɹ���
     */

    static TypeCodeFactory& getInstance();

    /**
     * @fn  static void TypeCodeFactory::finalize();
     *
     * @brief   ����ȫ��TypeCode������
     *
     * @author  Hzy
     * @date    2016/7/6
     */

    static void finalize();

    /**
     * @fn virtual TypeCode* TypeCodeFactory::getPrimitiveTC(TCTypeKind kind) = 0;
     *
     * @brief   ��ȡ�����������͵�TypeCode.
     *
     * @author  Hzy
     * @date    2016/7/6
     *
     * @param   kind    ָ�������������͡�
     *
     * @return  NULL��ʾʧ�ܣ�����Ϊ��Ч��TypeCode��
     */

    virtual TypeCode* getPrimitiveTC(TCTypeKind kind) = 0;

    /**
     * @fn virtual TypeCode* TypeCodeFactory::createStructTC(const ZR_INT8* name) = 0;
     *
     * @brief   �����ṹ��TypeCode.
     *
     * @author  Hzy
     * @date    2016/7/6
     *
     * @param   name    �ṹ������ơ�
     * @param   kind    �ýṹ���extensibility���ԡ�
     *
     * @return  NULL��ʾʧ�ܣ�����Ϊ��Ч��TypeCode��
     */

    virtual TypeCode* createStructTC(const ZR_INT8* name,
        ExtensibilityKind kind) = 0;

    /**
     * @fn  TypeCode* TypeCodeFactory::createValueTypeTC( TypeCodeFactory* self, const ZR_INT8* name, TypeCodeModifierKind modifierKind, ExtensibilityKind kind, const TypeCode*baseTC);
     *
     * @brief   Type code factory create value type tc.
     *
     * @author  Rainnus
     * @date    2016/10/21
     *
     * @param   name            valueType���ơ�
     * @param   modifierKind    modifier�����͡�
     * @param   kind            extensibility���͡�
     * @param   baseTC          �̳е����͡�
     *
     * @return  NULL��ʾʧ�ܣ�����Ϊ��Ч��TypeCode��
     */

    virtual TypeCode* createValueTypeTC(
        const ZR_INT8* name, 
        TypeCodeModifierKind modifierKind, 
        ExtensibilityKind kind, 
        const TypeCode* baseTC) = 0;
    /**
     * @fn  virtual TypeCode* TypeCodeFactory::wrapperTypeCode(TypeCodeHeader* cTypeCode);
     *
     * @brief   ��C�汾��TypCodeheader��װ��C++����
     *
     * @author  Hzy
     * @date    2016/10/18
     *
     * @param [in,out]  cTypeCode   �ײ�ṹ��
     *
     * @return  ��װ�Ľṹ��
     */

    virtual TypeCode* wrapperTypeCode(TypeCodeHeader* cTypeCode) = 0;

    /**
     * @fn virtual TypeCode* TypeCodeFactory::createEnumTC(const ZR_INT8* name) = 0;
     *
     * @brief   ����ö������TypeCode.
     *
     * @author  Hzy
     * @date    2016/7/6
     *
     * @param   name    ö�����͵����ơ�
     * @param   bitBound        λ���С��
     * @param   kind            Extenbility����ֵ��
     *
     * @return  NULL��ʾʧ�ܣ�����Ϊ��Ч��TypeCode��
     */

    virtual TypeCode* createEnumTC(const ZR_INT8* name,
        ZR_UINT32 bitBound,
        ExtensibilityKind kind) = 0;

    /**
     * @fn virtual TypeCode* TypeCodeFactory::createUnionTC(const ZR_INT8* name, const TypeCode* switchTC, ZR_UINT32 defaultIdx) = 0;
     *
     * @brief   ������������TypeCode.
     *
     * @author  Hzy
     * @date    2016/7/6
     *
     * @param   name        �������͵����ơ�
     * @param   switchTC    ������TC��
     * @param   defaultIdx  Ĭ�ϵĳ�Ա�±ꡣ
     *
     * @return  NULL��ʾʧ�ܣ�����Ϊ��Ч��TypeCode��
     */

    virtual TypeCode* createUnionTC(const ZR_INT8* name, const TypeCode* switchTC, ZR_UINT32 defaultIdx) = 0;

    /**
     * @fn virtual TypeCode* TypeCodeFactory::createStringTC(const ZR_UINT32 length) = 0;
     *
     * @brief   ����String����TypeCode.
     *
     * @author  Hzy
     * @date    2016/7/6
     *
     * @param   length  string�ĳ��ȡ�
     *
     * @return  NULL��ʾʧ�ܣ�����Ϊ��Ч��TypeCode��
     */

    virtual TypeCode* createStringTC(const ZR_UINT32 length) = 0;

    /**
     * @fn virtual TypeCode* TypeCodeFactory::createSequenceTC(const ZR_UINT32 length, const TypeCode* tc) = 0;
     *
     * @brief   ����Sequence����TypeCode.
     *
     * @author  Hzy
     * @date    2016/7/6
     *
     * @param   length  Sequence�ĳ��ȡ�
     * @param   tc      Ԫ�ص�TypeCode��
     *
     * @return  NULL��ʾʧ�ܣ�����Ϊ��Ч��TypeCode��
     */

    virtual TypeCode* createSequenceTC(const ZR_UINT32 length, const TypeCode* tc) = 0;

    /**
     * @fn virtual TypeCode* TypeCodeFactory::createArrayTC(const ZR_UINT32 dimensionCount, const ZR_UINT32* dimensions, const TypeCode* tc) = 0;
     *
     * @brief   ������������TypeCode.
     *
     * @author  Hzy
     * @date    2016/7/6
     *
     * @param   dimensionCount  ����ά�ȡ�
     * @param   dimensions      ����ά�ȵ�ά����
     * @param   tc              Ԫ�ص�TypeCode��
     *
     * @return  NULL��ʾʧ�ܣ�����Ϊ��Ч��TypeCode��
     */

    virtual TypeCode* createArrayTC(const ZR_UINT32 dimensionCount, const ZR_UINT32* dimensions, const TypeCode* tc) = 0;

    /**
     * @fn virtual TypeCode* TypeCodeFactory::cloneTC(const TypeCode* tc) = 0;
     *
     * @brief   ����һ��TypeCode.
     *
     * @author  Hzy
     * @date    2016/7/6
     *
     * @param   tc  ԴTypeCode��
     *
     * @return  NULL��ʾʧ�ܣ�����Ϊ��Ч��TypeCode��
     */

    virtual TypeCode* cloneTC(const TypeCode* tc) = 0;

    /**
     * @fn virtual ZR_BOOLEAN TypeCodeFactory::deleteTC(TypeCode* tc) = 0;
     *
     * @brief   ɾ��һ��TypeCode.
     *
     * @author  Hzy
     * @date    2016/7/6
     *
     * @param [in,out]  tc  ɾ����Ŀ�ꡣ
     *
     * @return  true��ʾɾ���ɹ���false��ʾɾ��ʧ�ܡ�
     */

    virtual ZR_BOOLEAN deleteTC(TypeCode* tc) = 0;

#ifdef _ZRDDS_INCLUDE_TYPE_OBJECT
    /**
     * @fn  virtual TypeCode TypeCodeFactory::createFromTypeObject(const TypeObject* typeObject);
     *
     * @brief   ��TypeObject����ȼ۵�TypeCode.
     *
     * @author  Hzy
     * @date    2017/2/24
     *
     * @param   typeObject  ԴTypeObject��
     *
     * @return  NULL��ʾʧ�ܣ����򷵻�ת���Ľ����
     */

    virtual TypeCode* createFromTypeObject(const TypeObject* typeObject) = 0;
#endif
};

#endif // _ZRDDS_INCLUDE_TYPECODE
} // namespace DDS

#endif // TypeCode_h__
