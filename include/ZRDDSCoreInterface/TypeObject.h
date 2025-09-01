/**
 * @file:       TypeObject.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#ifndef TypeObject_h__
#define TypeObject_h__

#include "OsResource.h"
#include "ZRSequence.h"
#include "ZRBuiltinTypes.h"
#include "TypeCodeKind.h"

#ifdef _ZRDDS_INCLUDE_TYPE_OBJECT

#ifdef __cplusplus
extern "C"
{
#endif

typedef struct TypeObject TypeObject;

#define TypeObjectSize 64

/**
 * @fn  TypeObjectImpl* TypeObjectFactoryCloneTypeObject(const TypeObjectImpl* typeObject);
 *
 * @brief   ��ȿ���TypeObject��
 *
 * @author  Hzy
 * @date    2017/1/10
 *
 * @param   typeObject  ԭʼTypeObject��
 *
 * @return  NULL��ʾʧ�ܣ�����ָ�򿽱�������TypeObject��
 */

DCPSDLL TypeObject* TypeObjectFactoryCloneTypeObject(const TypeObject* typeObject);

/**
 * @fn  DDS_Long TypeObjectFactoryDeleteTypeObject(TypeObjectImpl* typeObject);
 *
 * @brief   ����TypeObject�Ŀռ䡣
 *
 * @author  Hzy
 * @date    2017/1/5
 *
 * @param [in,out]  typeObject  ����TypeObject�Ŀռ䡣
 *
 * @return  0��ʾ�ɹ���-1��ʾʧ�ܡ�
 */

DCPSDLL DDS_Long TypeObjectFactoryDeleteTypeObject(TypeObject* typeObject);

/**
 * @fn  DDS_Long TypeObjectAssignableFrom(const TypeObjectImpl* type1, const TypeObjectImpl* type2);
 *
 * @brief   �Ƿ�����type1 is-assignable-from type2.
 *
 * @param   type1   ����1.
 * @param   type2   ����2.
 *
 * @return  0��ʾ���㣬С��0��ʾ�����㡣
 */

DCPSDLL DDS_Long TypeObjectAssignableFrom(const TypeObject* type1, const TypeObject* type2);

/**
 * @fn  DDS_Char* GetTypeObjectPrintableString(const TypeObject* typeObject);
 *
 * @brief   ��ȡһ��TypeObject�ȼ۵�IDL�ļ�������
 *
 * @param   typeObject  ָ��Ŀ�ꡣ
 *
 * @return  NULL��ʾʧ�ܣ�����ָ���ļ�����,��Ҫ����ReleaseTypeObjectPrintableString����������ڴ�й©��
 */

DCPSDLL DDS_Char* GetTypeObjectPrintableString(const TypeObject* typeObject);

/**
 * @fn  DCPSDLL void ReleaseTypeObjectPrintableString(DDS_Char* buffer);
 *
 * @brief   �������û��Ŀռ䡣
 *
 * @param [in,out]  buffer  GetTypeObjectPrintableString���صĿռ䡣
 */

DCPSDLL void ReleaseTypeObjectPrintableString(DDS_Char* buffer);

#ifdef _ZRDDS_INCLUDE_TYPECODE

/**
 * @fn  TypeObject TypeObjectFactoryCreateFromTypeCode(TypeObjectImpl* typeObject, struct TypeCodeImpl* typeCode);
 *
 * @brief   ��TypeCode�����ȼ۵�TypeObject��
 *
 * @param [in,out]  typeCode    ԴTypeCode��
 *
 * @return  NULL��ʾת��ʧ�ܣ������ʾת�������
 */

DCPSDLL TypeObject* TypeObjectFactoryCreateFromTypeCode(struct TypeCodeHeader* typeCode);

/**
 * @fn  DCPSDLL TypeCodeHeader* TypeObjectToTypeCode(const TypeObject* typeObject);
 *
 * @brief   ��TypeObjectת��ΪTypeCode.
 *
 * @param   typeObject  ָ��Ŀ�ꡣ
 *
 * @return  NULL��ʾʧ�ܣ������ʾת�������
 */

DCPSDLL TypeCodeHeader* TypeObjectToTypeCode(const TypeObject* typeObject);

#endif /*_ZRDDS_INCLUDE_TYPECODE */

#ifdef __cplusplus
}
#endif

#endif /* _ZRDDS_INCLUDE_TYPE_OBJECT */

#endif /* TypeObject_h__*/
