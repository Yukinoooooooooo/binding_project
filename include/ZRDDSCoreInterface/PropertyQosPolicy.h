/**
 * @file:       PropertyQosPolicy.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#ifndef PropertyQosPolicy_h__
#define PropertyQosPolicy_h__

#include "OsResource.h"
#include "ZRDDSCommon.h"
#include "ZRSequence.h"
#include "ZRBuiltinTypes.h"

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

/**
 * @typedef struct DDS_Property_t
 *
 * @brief   ��չ��DDS_Property_t.
 */

typedef struct DDS_Property_t
{
    /** @brief   ���ƣ��ɳ����Լ�Լ���� */
    DDS_Char* name;
    /** @brief   ���ƶ�Ӧ��ֵ�� */
    DDS_Char* value;
    /** @brief   �Ƿ���Ҫ���ݸ��Զˡ� */
    DDS_Boolean propagate;
    /** @brief   �����ڴ�ռ��Ƿ����ڲ����䣬true����DDS�ڲ������ڴ�ռ䣬��������û������ڴ�ռ䡣 */
    DDS_Boolean owned;
}DDS_Property_t;

DDS_SEQUENCE_CPP(DDS_PropertySeq, DDS_Property_t);

/**
 * @struct  DDS_BinaryProperty_t
 *
 * @brief   ��ֵ�ļ�ֵ�ԡ�
 *
 * @author  Hzy
 * @date    2018/1/30
 */

typedef struct DDS_BinaryProperty_t
{
    /** @brief   ���ƣ��ɳ����Լ�Լ���� */
    DDS_Char* name;
    /** @brief   ���ƶ�Ӧ��ֵ�� */
    DDS_OctetSeq value;
    /** @brief   �Ƿ���Ҫ���ݸ��Զˡ� */
    DDS_Boolean propagate;
    /** @brief   �����ڴ�ռ��Ƿ����ڲ����䣬true����DDS�ڲ������ڴ�ռ䣬��������û������ڴ�ռ䡣 */
    DDS_Boolean owned;
}DDS_BinaryProperty_t;

DDS_SEQUENCE_CPP(DDS_BinaryPropertySeq, DDS_BinaryProperty_t);

/**
 * @struct DDS_PropertyQosPolicy
 *
 * @ingroup CoreQosStruct
 *
 * @brief   �������á�
 *
 * @details 
 *          ��Ա | Ĭ��ֵ | ƥ������� | ��Ч�Լ�� | �����Լ�� | �ɱ��Լ��
 *          --- | --- | --- | --- | --- | ---
 *          #value | �� | �� | �� | �� | ���ɱ�
 *          #binary_value | �� | �� | �� | �� | ���ɱ�
 *
 */
typedef struct DDS_PropertyQosPolicy 
{
    /** @brief   �ַ���ֵ�� */
    DDS_PropertySeq value;
    /** @brief   ������ֵ�� */
    DDS_BinaryPropertySeq binary_value;
}DDS_PropertyQosPolicy;

/**
 * @fn  DDS_Boolean DDS_PropertyQos_AppendProperty(DDS_PropertyQosPolicy * propertyQos, const DDS_Char* name, const DDS_Char* value, DDS_Boolean propagate);
 *
 * @brief   ��PropertyQos�������ַ���ֵ���Լ�ֵ��.
 *
 * @param [in,out]  propertyQos ָ��PropertyQos����.
 * @param   name                �ַ���ֵ��������.
 * @param   value               �ַ���ֵ����ֵ.
 * @param   propagate           �Ƿ���Ҫ���ݸ��Զ�.
 *
 * @return  A DDS_Boolean.      ���ɹ�������true�����򷵻�false.
 */

DCPSDLL DDS_Boolean DDS_PropertyQos_AppendProperty(DDS_PropertyQosPolicy * propertyQos,
    const DDS_Char* name,
    const DDS_Char* value,
    DDS_Boolean propagate);

/**
 * @fn  DDS_Boolean DDS_PropertyQos_AppendBinaryProperty(DDS_PropertyQosPolicy * propertyQos, const DDS_Char* name, const DDS_OctetSeq* value, DDS_Boolean propagate);
 *
 * @brief   ��PropertyQos�����ӻ�����ֵ���Լ�ֵ��.
 *
 * @param [in,out]  propertyQos ָ��PropertyQos����.
 * @param   name                ������ֵ��������.
 * @param   value               ������ֵ����ֵ.
 * @param   propagate           �Ƿ���Ҫ���ݸ��Զ�.
 *
 * @return  A DDS_Boolean.      ���ɹ�������true�����򷵻�false.
 */

DCPSDLL DDS_Boolean DDS_PropertyQos_AppendBinaryProperty(DDS_PropertyQosPolicy * propertyQos,
    const DDS_Char* name,
    const DDS_OctetSeq* value,
    DDS_Boolean propagate);

/**
 * @fn  DDS_Boolean DDS_PropertyQos_RemoveProperty(DDS_PropertyQosPolicy * propertyQos, const DDS_Char* name);
 *
 * @brief   ��PropertyQos���Ƴ�ָ�����Ƶ��ַ���ֵ����.���ô˺������Ὣ����ͬ�������Ƴ�.
 *
 * @param [in,out]  propertyQos ָ��PropertyQos����.
 * @param   name                ��Ҫ�Ƴ�����������.
 *
 * @return  A DDS_Boolean.      ���ɹ�������true�����򷵻�false.
 */

DCPSDLL DDS_Boolean DDS_PropertyQos_RemoveProperty(DDS_PropertyQosPolicy * propertyQos,
    const DDS_Char* name);

/**
 * @fn  DDS_Boolean DDS_PropertyQos_RemoveBinaryProperty(DDS_PropertyQosPolicy * propertyQos, const DDS_Char* name);
 *
 * @brief   ��PropertyQos���Ƴ�ָ�����ƵĻ�����ֵ����.���ô˺������Ὣ����ͬ�������Ƴ�.
 *
 * @param [in,out]  propertyQos ָ��PropertyQos����.
 * @param   name                ��Ҫ�Ƴ�����������.
 *
 * @return  A DDS_Boolean.      ���ɹ�������true�����򷵻�false.
 */

DCPSDLL DDS_Boolean DDS_PropertyQos_RemoveBinaryProperty(DDS_PropertyQosPolicy * propertyQos,
    const DDS_Char* name);

#ifdef _ZRDDS_INCLUDE_DATA_COMPRESSION

/**
* @fn  int CompressionFunc(const char* src, char* dst, int src_size, int dst_size);
*
* @brief   CompressionFunc.
*
* @param   src         ԭ����
* @param   src_size    ԭʼ���ݴ�С
* @param   [in,out]dst �洢ѹ��������.
* @param   dst_size    �洢ѹ�������ݵĿռ��С.
*
* @return   ����0��ʾʧ�ܣ����򷵻�����.
*/
typedef int(*CompressionFunc)(
    const char* src,
    char* dst,
    int src_size,
    int dst_size);

/**
* @fn  int DeCompressionFunc(const char* src, char* dst, int compressed_size, int dst_capacity);
*
* @brief   DeCompressionFunc.
*
* @param   src             ��Ҫ��ѹ������.
* @param   [in,out] dst    �洢��ѹ�����ݵ�λ��.
* @param   compressed_size ��Ҫ��ѹ�����ݴ�С.
* @param   dst_capacity    �洢��ѹ�����ݵĿռ��С.
*
* @return  ��ѹ�ɹ�����ѹ��ǰ���ݴ�С�����dst�ռ䲻���������ݴ����루������.
*/

typedef int(*DeCompressionFunc)(
    const char* src,
    char* dst,
    int compressed_size,
    int dst_capacity);

/**
* @fn  ZR_INT32 SetDataWriterCompression(DDS_PropertyQosPolicy* property, ZR_INT8* dll_name, void* get_name_func, void* compression_func);
*
* @brief   ��������д��ѹ��.
*
* @param [in,out]  property            ����д�ߵ�PropertyQosPolicy.
* @param [in]      dll_name            ʹ�õ�DLL���֣���̬�����̬�����֣���̬������NULL��ʹ��Ĭ��ֵ��NULL��.
* @param [in]      conpression_name    ʹ�õ�ѹ���㷨���ƣ�ʹ��Ĭ�Ϻ�����NULL��.
* @param [in]      compression_func    ѹ����������̬�������������̬���������ַ��ʹ��Ĭ�Ϻ�����NULL��.
*
* @return  �ɹ�����0��ʧ�ܷ���-1.
*/

DCPSDLL ZR_INT32 SetDataWriterCompression(DDS_PropertyQosPolicy* property, ZR_INT8* dll_name, ZR_INT8* compression_name, void* compression_func);

/**
* @fn  ZR_INT32 SetDataReaderCompression(DDS_PropertyQosPolicy* property, ZR_INT8* dll_name, void* get_name_func, void* decompression_func);
*
* @brief   �������ݶ���ѹ��.
*
* @param [in,out]  property              ���ݶ��ߵ�PropertyQosPolicy.
* @param [in]      dll_name              ʹ�õ�DLL���֣���̬�����̬�����֣���̬������NULL��ʹ��Ĭ��ֵ��NULL��.
* @param [in]      conpression_name      ʹ�õ�ѹ���㷨���ƣ�ʹ��Ĭ�Ϻ�����NULL��.
* @param [in]      decompression_func    ��ѹ��������̬�������������̬���������ַ��ʹ��Ĭ�Ϻ�����NULL��.
*
* @return  �ɹ�����0��ʧ�ܷ���-1.
*/

DCPSDLL ZR_INT32 SetDataReaderCompression(DDS_PropertyQosPolicy* property, ZR_INT8* dll_name, ZR_INT8* compression_name, void* decompression_func);

#endif // _ZRDDS_INCLUDE_DATA_COMPRESSION


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* PropertyQosPolicy_h__ */
