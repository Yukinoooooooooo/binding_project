/**
 * @file:       OsResource.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#ifndef OSRESOURCE_H
#define OSRESOURCE_H

#include "ZROSDefine.h"
#ifdef _REWORKS
#include <stdlib.h>
#include <reworks/types.h>
#ifdef __cplusplus
using namespace std;
#endif
#endif /* _REWORKS */

#ifndef __cplusplus
/**
 * @typedef bool ZR_BOOLEAN
 *
 * @ingroup  CoreBaseStruct
 *
 * @brief   Ϊ����ƽ̨���죬�����ڽӿ���ʹ��bool���͡�
 */
typedef char ZR_BOOLEAN;
#define false 0
#define true 1
#else

/**
 * @typedef bool ZR_BOOLEAN
 *
 * @ingroup  CoreBaseStruct
 *
 * @brief   Ϊ����ƽ̨���죬�����ڽӿ���ʹ��bool���͡�
 */

typedef bool ZR_BOOLEAN;
#endif

/**
 * @typedef char ZR_INT8
 *
 * @ingroup  CoreBaseStruct
 *
 * @brief   Ϊ����ƽ̨���죬�����ڽӿ���ʹ�õ�1���ֽ����͡�
 */

typedef char ZR_INT8;

/**
 * @typedef unsigned char ZR_UINT8
 *
 * @ingroup  CoreBaseStruct
 *
 * @brief   Ϊ����ƽ̨���죬�����ڽӿ���ʹ�õ�1���ֽ��޷������͡�
 */

typedef unsigned char ZR_UINT8;

/**
 * @typedef short ZR_INT16
 *
 * @ingroup  CoreBaseStruct
 *
 * @brief   Ϊ����ƽ̨���죬�����ڽӿ���ʹ�õ�2���ֽ����͡�
 */

typedef short ZR_INT16;

/**
 * @typedef unsigned short ZR_UINT16
 *
 * @ingroup  CoreBaseStruct
 *
 * @brief   Ϊ����ƽ̨���죬�����ڽӿ���ʹ�õ�2���ֽ��޷������͡�
 */

typedef unsigned short ZR_UINT16;

/**
 * @typedef int ZR_INT32
 *
 * @ingroup  CoreBaseStruct
 *
 * @brief   Ϊ����ƽ̨���죬�����ڽӿ���ʹ�õ�4���ֽ����͡�
 */

typedef int ZR_INT32;

/**
 * @typedef unsigned int ZR_UINT32
 *
 * @ingroup  CoreBaseStruct
 *
 * @brief   Ϊ����ƽ̨���죬�����ڽӿ���ʹ�õ�4���ֽ��޷������͡�
 */

typedef unsigned int ZR_UINT32;

/**
 * @typedef long long ZR_INT64
 *
 * @ingroup  CoreBaseStruct
 *
 * @brief   Ϊ����ƽ̨���죬�����ڽӿ���ʹ�õ�8���ֽ����͡�
 */

typedef long long ZR_INT64;

/**
 * @typedef unsigned long long ZR_UINT64
 *
 * @ingroup  CoreBaseStruct
 *
 * @brief   Ϊ����ƽ̨���죬�����ڽӿ���ʹ�õ�8���ֽ��޷������͡�
 */

typedef unsigned long long ZR_UINT64;

/**
 * @typedef float ZR_FLOAT32
 *
 * @ingroup  CoreBaseStruct
 *
 * @brief   Ϊ����ƽ̨���죬�����ڽӿ���ʹ�õ�4���ֽڵ����ȸ����͡�
 */

typedef float ZR_FLOAT32;

/**
 * @typedef double ZR_DOUBLE64
 *
 * @ingroup  CoreBaseStruct
 *
 * @brief   Ϊ����ƽ̨���죬�����ڽӿ���ʹ�õ�8���ֽ�˫���ȸ����͡�
 */

typedef double ZR_DOUBLE64;

/**
 * @def MAX_USHORT_VALUE
 *
 * @ingroup CoreMacro
 *
 * @brief   2�ֽ��޷����������ֵ��
 */

#define MAX_USHORT_VALUE 0xffff

/**
 * @def MAX_SHORT_VALUE
 *
 * @ingroup CoreMacro
 *
 * @brief   2�ֽ��з����������ֵ��
 */
#define MAX_SHORT_VALUE 0x7fff

/**
 * @def MAX_UINT32_VALUE
 *
 * @ingroup CoreMacro
 *
 * @brief   4�ֽ��޷����������ֵ��
 */
#define MAX_UINT32_VALUE 0xffffffff

/**
 * @def MAX_INT32_VALUE
 *
 * @ingroup CoreMacro
 *
 * @brief   4�ֽ��з����������ֵ��
 */
#define MAX_INT32_VALUE 0x7fffffff

/**
 * @def LENGTH_UNLIMITED
 *
 * @ingroup CoreMacro
 *
 * @brief   �������޴��ڲ�ͬ�Ļ�����ȡ��ͬ��ֵ��
 */
#define LENGTH_UNLIMITED -1

/**
 * @typedef ZR_BOOLEAN DDS_Boolean
 *
 * @ingroup CoreBuiltinTypes
 *
 * @brief   ZRDDS���õ�true/false���͡�
 */

typedef ZR_BOOLEAN DDS_Boolean;


/**
 * @typedef ZR_UINT8 DDS_Octet
 *
 * @ingroup CoreBuiltinTypes
 *
 * @brief   ZRDDS���õ�1�ֽ��޷������� 
 */

typedef unsigned char DDS_Octet;

/**
 * @typedef ZR_INT8 DDS_Char
 *
 * @ingroup CoreBuiltinTypes
 *
 * @brief   ZRDDS���õ�1�ֽ����͡�
 */

typedef char DDS_Char;

/**
 * @typedef ZR_INT16 DDS_Short
 *
 * @ingroup CoreBuiltinTypes
 *
 * @brief   ZRDDS���õ�2�ֽ����͡�
 */

typedef ZR_INT16 DDS_Short;

/**
 * @typedef ZR_UINT16 DDS_UShort
 *
 * @ingroup CoreBuiltinTypes
 *
 * @brief   ZRDDS���õ�2�ֽ��޷������͡�
 */

typedef ZR_UINT16 DDS_UShort;

/**
 * @typedef ZR_INT32 DDS_Long
 *
 * @ingroup CoreBuiltinTypes
 *
 * @brief   ZRDDS���õ�4�ֽ����͡�
 */

typedef ZR_INT32 DDS_Long;

/**
 * @typedef ZR_UINT32 DDS_ULong
 *
 * @ingroup CoreBuiltinTypes
 *
 * @brief   ZRDDS���õ�4�ֽ��޷������͡�
 */

typedef ZR_UINT32 DDS_ULong;

/**
 * @typedef ZR_INT64 DDS_LongLong
 *
 * @ingroup CoreBuiltinTypes
 *
 * @brief   ZRDDS���õ�8�ֽڳ����͡�
 */

typedef ZR_INT64 DDS_LongLong;

/**
 * @typedef ZR_UINT64 DDS_ULongLong
 *
 * @ingroup CoreBuiltinTypes
 *
 * @brief   ZRDDS���õ�8�ֽ��޷��ų����͡�
 */

typedef ZR_UINT64 DDS_ULongLong;

/**
 * @typedef ZR_FLOAT32 DDS_Float
 *
 * @ingroup CoreBuiltinTypes
 *
 * @brief   ZRDDS���õ�4�ֽڵ����ȸ����͡�
 */

typedef ZR_FLOAT32 DDS_Float;

/**
 * @typedef ZR_DOUBLE64 DDS_Double
 *
 * @ingroup CoreBuiltinTypes
 *
 * @brief   ZRDDS���õ�8�ֽ�˫���ȸ����͡�
 */

typedef ZR_DOUBLE64 DDS_Double;

typedef struct ZRBuffer
{
    void* content;
    ZR_UINT32 length;
}ZRBuffer;

/**
 * ��������Ϊ����601����ʹ�á�
 */
#ifdef _ZRDDS_INCLUDE_601_TYPE

/**
 * @typedef DDS_Octet DDS_UINT8
 *
 * @ingroup CoreBuiltinTypes
 *
 * @brief   DDS_Octet �ı�����
 */

typedef DDS_Octet DDS_UINT8;

/**
 * @typedef DDS_Char DDS_INT8
 *
 * @ingroup CoreBuiltinTypes
 *
 * @brief   DDS_Char �ı�����
 */

typedef DDS_Char DDS_INT8;

/**
 * @typedef DDS_Boolean DDS_BOOLEAN
 *
 * @ingroup CoreBuiltinTypes
 *
 * @brief   DDS_Boolean �ı�����
 */

typedef DDS_Boolean DDS_BOOLEAN;

/**
 * @typedef DDS_Short DDS_INT16
 *
 * @ingroup CoreBuiltinTypes
 *
 * @brief   DDS_Short �ı�����
 */

typedef DDS_Short DDS_INT16;

/**
 * @typedef DDS_UShort DDS_UINT16
 *
 * @ingroup CoreBuiltinTypes
 *
 * @brief   DDS_UShort �ı�����
 */

typedef DDS_UShort DDS_UINT16;

/**
 * @typedef DDS_Long DDS_INT32
 *
 * @ingroup CoreBuiltinTypes
 *
 * @brief   DDS_Long �ı�����
 */

typedef DDS_Long DDS_INT32;

/**
 * @typedef DDS_ULong DDS_UINT32
 *
 * @ingroup CoreBuiltinTypes
 *
 * @brief   DDS_ULong �ı�����
 */

typedef DDS_ULong DDS_UINT32;

/**
 * @typedef DDS_Float DDS_FLOAT32
 *
 * @ingroup CoreBuiltinTypes
 *
 * @brief   DDS_Float �ı�����
 */

typedef DDS_Float DDS_FLOAT32;

/**
 * @typedef DDS_LongLong DDS_INT64
 *
 * @ingroup CoreBuiltinTypes
 *
 * @brief   DDS_LongLong �ı�����
 */

typedef DDS_LongLong DDS_INT64;

/**
 * @typedef DDS_ULongLong DDS_UINT64
 *
 * @ingroup CoreBuiltinTypes
 *
 * @brief   DDS_ULongLong �ı�����
 */

typedef DDS_ULongLong DDS_UINT64;

/**
 * @typedef DDS_Double DDS_DOUBLE64
 *
 * @ingroup CoreBuiltinTypes
 *
 * @brief   DDS_Double �ı�����
 */

typedef DDS_Double DDS_DOUBLE64;

#endif //_ZRDDS_INCLUDE_601_TYPE

#endif
