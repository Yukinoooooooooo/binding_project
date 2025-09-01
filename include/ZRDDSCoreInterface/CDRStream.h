/**
 * @file:       CDRStream.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#ifndef CDRStream_h__
#define CDRStream_h__

#include "OsResource.h"
#include "ZRDDSCommon.h"

typedef struct MessageBlock MessageBlock;
typedef struct CDRSerializer CDRSerializer;
typedef struct CDRDeserializer CDRDeserializer;

#define PID_LIST_END 0x3f02

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus*/

/**
 * @fn  DCPSDLL CDRSerializer* CDRSerializerInitialWBuf(ZR_INT8* buffer, ZR_UINT32 length, ZR_BOOLEAN littleEndian);
 *
 * @ingroup CoreBaseFunction
 *
 * @brief   �û��ṩԭʼ���洴��һ�����л�����ʹ�øýӿڱ������ ::CDRSerializerDestoryBuffer ������Դ��
 *
 * @param [in,out]  buffer  �û��ṩ�Ŀռ䡣
 * @param   length          �û��ṩ�Ŀռ䳤�ȡ�
 * @param   littleEndian    �Ƿ�ʹ��С�����л���true��ʾС�ˣ�false��ʾ��ˡ�
 *
 * @return  NULL��ʾ����ʧ�ܣ�����ָ���´��������л�����
 */

DCPSDLL CDRSerializer* CDRSerializerInitialWBuf(ZR_INT8* buffer, ZR_UINT32 length, ZR_BOOLEAN littleEndian);

/**
 * @fn  DCPSDLL CDRDeserializer* CDRDeserializerInitialWBuf(ZR_INT8* buffer, ZR_UINT32 length, ZR_BOOLEAN littleEndian);
 *
 * @ingroup CoreBaseFunction
 *
 * @brief   �û��ṩԭʼ���洴��һ�������л�����ʹ�øýӿڱ������ ::CDRDeserializerDestoryBuffer ������Դ��
 *
 * @param [in,out]  buffer  �û��ṩ�Ŀռ䡣
 * @param   length          �û��ṩ�Ŀռ䳤�ȡ�
 * @param   littleEndian    �Ƿ�ʹ��С�����л���true��ʾС�ˣ�false��ʾ��ˡ�
 *
 * @return  NULL��ʾʧ�ܣ����򷵻��´����ķ����л�����
 */

DCPSDLL CDRDeserializer* CDRDeserializerInitialWBuf(ZR_INT8* buffer, ZR_UINT32 length, ZR_BOOLEAN littleEndian);

/**
 * @fn  DCPSDLL ZR_UINT32 CDRSerializerGetBufferSpace(CDRSerializer* self);
 *
 * @ingroup CoreBaseFunction
 *
 * @brief   ��ȡָ�����л�����ʣ�µĻ�������С��
 *
 * @param [in,out]  self    ָ��Ŀ�ꡣ
 *
 * @return  ������������ʣ��ռ��С��
 */

DCPSDLL ZR_UINT32 CDRSerializerGetBufferSpace(CDRSerializer* self);

/**
 * @fn  DCPSDLL ZR_UINT32 CDRDeserializerGetBufferLength(CDRDeserializer* self);
 *
 * @ingroup CoreBaseFunction
 *
 * @brief   ��ȡ�����л��������Ļ�������ʣ�����ݳ��ȡ�
 *
 * @param [in,out]  self    ָ��Ŀ�ꡣ
 *
 * @return  �����Ļ�����ʣ�����ݳ��ȡ�
 */

DCPSDLL ZR_UINT32 CDRDeserializerGetBufferLength(CDRDeserializer* self);

/**
 * @fn  DCPSDLL void CDRSerializerDestoryBuffer(CDRSerializer* self);
 *
 * @ingroup CoreBaseFunction
 *
 * @brief   ������ ::CDRSerializerInitialWBuf �������ڲ��ռ䡣
 *
 * @param [in,out]  self    ָ��Ŀ�ꡣ
 */

DCPSDLL void CDRSerializerDestoryBuffer(CDRSerializer* self);

/**
 * @fn  DCPSDLL void CDRDeserializerDestoryBuffer(CDRDeserializer* self);
 *
 * @ingroup CoreBaseFunction
 *
 * @brief   ������ ::CDRDeserializerInitialWBuf �ڲ��ռ䡣
 *
 * @param [in,out]  self    ָ��Ŀ�ꡣ
 */

DCPSDLL void CDRDeserializerDestoryBuffer(CDRDeserializer* self);

/**
 * @fn  void CDRSerializerInitial(CDRSerializer* self, MessageBlock* tgaMsgBlock, ZR_BOOLEAN littleEndian);
 *
 * @ingroup CoreBaseFunction
 *
 * @brief   ��ʼ��һ��CDR���л�����
 *
 * @param [in,out]  self        ��Ҫ��ʼ����Ŀ�ꡣ
 * @param [in,out]  tgaMsgBlock ������Ŀ�껺�档
 * @param   littleEndian        ʹ�õı��뷽ʽ��true��ʾС�ˣ�false��ʾ��ˡ�
 */

DCPSDLL void CDRSerializerInitial(CDRSerializer* self, MessageBlock* tgaMsgBlock, ZR_BOOLEAN littleEndian);

/**
 * @fn  ZR_BOOLEAN CDRSerializerPutString(CDRSerializer* self, const ZR_INT8* value, const ZR_UINT32 length);
 *
 * @ingroup CoreBaseFunction
 *
 * @brief   ���л��ַ�����
 *
 * @param [in,out]  self    Ŀ�����л�����
 * @param   value           ���л�Ŀ��ֵ��
 * @param   length          ���л�Ŀ��ֵ���ȣ���Ҫ������β����
 *
 * @return  true��ʾ�ɹ���false��ʾʧ�ܡ�
 */

DCPSDLL ZR_BOOLEAN CDRSerializerPutString(CDRSerializer* self, const ZR_INT8* value, const ZR_UINT32 length);

/**
 * @fn  ZR_BOOLEAN CDRSerializerPutUntype(CDRSerializer* self, const ZR_UINT8* val, ZR_UINT32 typeSize);
 *
 * @ingroup CoreBaseFunction
 *
 * @brief   ���л������������͡�
 *
 * @param [in,out]  self    ָ��Ŀ�����л�����
 * @param   val             ��Ҫ���л���ֵ��ַ��
 * @param   typeSize        ��Ҫ���л���ֵ�ĳ��ȡ�
 *
 * @return  true��ʾ�ɹ���false��ʾʧ�ܡ�
 */

DCPSDLL ZR_BOOLEAN CDRSerializerPutUntype(CDRSerializer* self, const ZR_UINT8* val, ZR_UINT32 typeSize);

/**
 * @fn  DCPSDLL ZR_UINT32 CDRSerializerGetUntypeSize(ZR_UINT32 typeSize, ZR_UINT32 currentAlignment);
 *
 * @ingroup CoreBaseFunction
 *
 * @brief   ��ָ�����������£�ָ����С�������������л����ȡ�
 *
 * @param   typeSize            ָ�����ͳ��ȡ�
 * @param   currentAlignment    ��ǰ�Ķ���ƫ������
 *
 * @return  �����˶�������л���С��
 */

DCPSDLL ZR_UINT32 CDRSerializerGetUntypeSize(ZR_UINT32 typeSize, ZR_UINT32 currentAlignment);

/**
 * @fn  DCPSDLL ZR_UINT32 CDRSerializerGetUntypeArraySize(ZR_UINT32 typeSize, ZR_UINT32 arraySize, ZR_UINT32 currentAlignment);
 *
 * @ingroup CoreBaseFunction
 *
 * @brief   ��ȡ�����������л����ȵĽӿڡ�
 *
 * @param   typeSize            ָ�����ͳ��ȡ�
 * @param   arraySize           ָ�������ģ��
 * @param   currentAlignment    ��ǰ�����ƫ������
 *
 * @return  �����˶�������л���С��
 */

DCPSDLL ZR_UINT32 CDRSerializerGetUntypeArraySize(ZR_UINT32 typeSize, ZR_UINT32 arraySize, ZR_UINT32 currentAlignment);

/**
 * @fn  DCPSDLL ZR_UINT32 CDRSerializerGetStringSize(ZR_UINT32 length, ZR_UINT32 currentAlignment);
 *
 * @ingroup CoreBaseFunction
 *
 * @brief   ��ȡ���л�string��������ĳ��ȡ�
 *
 * @param   length              �ַ�������(����\0)��
 * @param   currentAlignment    ��ǰ�����ƫ������
 *
 * @return  �����˶�������л���С��
 */

DCPSDLL ZR_UINT32 CDRSerializerGetStringSize(ZR_UINT32 length, ZR_UINT32 currentAlignment);

/**
 * @fn  ZR_BOOLEAN CDRSerializerPutUntypeArray(CDRSerializer* self, const ZR_UINT8* arrayVal, ZR_UINT32 arraySize, ZR_UINT32 typeSize);
 *
 * @ingroup CoreBaseFunction
 *
 * @brief   ���л������������顣
 *
 * @param [in,out]  self    ָ��Ŀ�����л�����
 * @param   arrayVal        ��Ҫ���л��������׵�ַ��
 * @param   arraySize       ��Ҫ���л��������ģ��
 * @param   typeSize        ��Ҫ���л�������Ԫ�صĳ��ȡ�
 *
 * @return  true��ʾ�ɹ���false��ʾʧ�ܡ�
 */

DCPSDLL ZR_BOOLEAN CDRSerializerPutUntypeArray(CDRSerializer* self, const ZR_UINT8* arrayVal, ZR_UINT32 arraySize, ZR_UINT32 typeSize);

/**
 * @fn DCPSDLL ZR_BOOLEAN CDRSerializerNoSerializingMode(CDRSerializer* self);
 *
 * @brief �Ƿ����������л�ģʽ����ģʽ�ɵ���������
 *
 * @param [in] self If non-null, the self
 *
 * @return A ZR_BOOLEAN
 */

DCPSDLL ZR_BOOLEAN CDRSerializerNoSerializingMode(CDRSerializer* self);

/**
 * @fn DCPSDLL ZR_BOOLEAN CDRSerializerSetNoSerializingMode(CDRSerializer* self, ZR_BOOLEAN noSerializingMode);
 *
 * @brief �����Ƿ����������л�ģʽ����ģʽ�ɵ���������
 *
 * @param [in] self     If non-null, the self
 * @param noSerializingMode The no serializing mode
 *
 * @return A ZR_BOOLEAN
 */

DCPSDLL void CDRSerializerSetNoSerializingMode(CDRSerializer* self, ZR_BOOLEAN noSerializingMode);

/**
 * @fn DCPSDLL ZR_BOOLEAN CDRSerializerIsLittleEndian(CDRSerializer* self);
 *
 * @brief ��ȡ��ǰCDRSerializer���õĶ���TRUE��ʾС�ˣ�FALSE��ʾ���
 *
 * @param [in] self If non-null, the self
 *
 * @return TRUE��ʾС�ˣ�FALSE��ʾ���
 */
DCPSDLL ZR_BOOLEAN CDRSerializerIsLittleEndian(CDRSerializer* self);

/**
 * @fn  void CDRDeserializerInitial(CDRDeserializer* self, MessageBlock* srcMsg, ZR_BOOLEAN useLittleEndian);
 *
 * @ingroup CoreBaseFunction
 *
 * @brief   ��ʼ��һ��CDR�����л�����
 *
 * @param [in,out]  self    ��ʼ��Ŀ�ꡣ
 * @param [in,out]  srcMsg  ָ�������л�Դ��ַ��
 * @param   useLittleEndian ָ�����뷽ʽ��
 */

DCPSDLL void CDRDeserializerInitial(CDRDeserializer* self, MessageBlock* srcMsg, ZR_BOOLEAN useLittleEndian);

/**
 * @fn  ZR_BOOLEAN CDRDeserializerGetString(CDRDeserializer* self, ZR_INT8* value, ZR_UINT32* length);
 *
 * @ingroup CoreBaseFunction
 *
 * @brief   �ӻ������л�ȡ�ַ�����
 *
 * @param [in,out]  self    ָ�������л�����
 * @param [in,out]  value   �����л�����ַ����׵�ַ��
 * @param [in,out]  length  �����л�����ַ������ȡ�
 *
 * @return  0��ʾ�ɹ���С��0��ʾʧ�ܡ�
 */

DCPSDLL ZR_BOOLEAN CDRDeserializerGetString(CDRDeserializer* self, ZR_INT8* value, ZR_UINT32* length);

/**
 * @fn  ZR_BOOLEAN CDRDeserializerGetUntype(CDRDeserializer* self, ZR_UINT8* value, ZR_UINT32 typeSize);
 *
 * @ingroup CoreBaseFunction
 *
 * @brief   �ӻ������л�ȡ�����������͡�
 *
 * @param [in,out]  self    ָ��Ŀ�귴���л�����
 * @param [in,out]  value   �����л�����洢��ַ��
 * @param   typeSize        ָ�������л����ͳ��ȡ�
 *
 * @return  0��ʾ�ɹ���С��0��ʾʧ�ܡ�
 */

DCPSDLL ZR_BOOLEAN CDRDeserializerGetUntype(CDRDeserializer* self, ZR_UINT8* value, ZR_UINT32 typeSize);

/**
 * @fn  DCPSDLL ZR_INT8* CDRDeserializerLoanContiguousByte(CDRDeserializer* self, ZR_UINT32 length);
 *
 * @ingroup CoreBaseFunction
 *
 * @brief   �ӻ������л�ȡ�ַ�������������
 *
 * @param [in,out]  self    ָ�������л�����
 * @param   length          �����л�����ַ������ȡ�
 *
 * @return  NULL��ʾʧ�ܣ�����ָ��ͷָ�롣
 */

DCPSDLL ZR_INT8* CDRDeserializerLoanContiguousByte(CDRDeserializer* self, ZR_UINT32 length);

/**
 * @fn  ZR_BOOLEAN CDRDeserializerGetUntypeArray(CDRDeserializer* self, ZR_UINT8* value, ZR_UINT32* arraySize, ZR_UINT32 typeSize);
 *
 * @ingroup CoreBaseFunction
 *
 * @brief   �ӻ������л�ȡ���������������顣
 *
 * @param [in,out]  self    ָ��Ŀ�귴���л�����
 * @param [in,out]  value   �����л�����洢��ַ��
 * @param   arraySize   �û�ָ�������л�������鳤�ȡ�
 * @param   typeSize        ָ�������л����ͳ��ȡ�
 *
 * @return  0��ʾ�ɹ���С��0��ʾʧ�ܡ�
 */

DCPSDLL ZR_BOOLEAN CDRDeserializerGetUntypeArray(CDRDeserializer* self, ZR_UINT8* value, ZR_UINT32 arraySize, ZR_UINT32 typeSize);

/**
 * @fn  DCPSDLL ZR_BOOLEAN CDRDeserializerAheadLength(CDRDeserializer* self, ZR_UINT32 beginIndex, ZR_UINT32 length);
 *
 * @ingroup CoreBaseFunction
 *
 * @brief   ����ָ�������ַ���
 *
 * @param [in,out]  self    ָ��Ŀ�귴���л�����
 * @param   beginIndex      ��ʼλ�á�
 * @param   length          ��Ҫ�����ĳ��ȡ�
 *
 * @return  0��ʾ�ɹ���С��0��ʾʧ�ܡ�
 */

DCPSDLL ZR_BOOLEAN CDRDeserializerAheadLength(CDRDeserializer* self, ZR_UINT32 beginIndex, ZR_UINT32 length);

/**
 * @fn DCPSDLL ZR_BOOLEAN CDRDeserializerIsLittleEndian(CDRDeserializer* self);
 *
 * @brief ��ȡ��ǰCDRDeserializer���õĶ���TRUE��ʾС�ˣ�FALSE��ʾ���
 *
 * @param [in] self If non-null, the self
 *
 * @return TRUE��ʾС�ˣ�FALSE��ʾ���
 */
DCPSDLL ZR_BOOLEAN CDRDeserializerIsLittleEndian(CDRDeserializer* self);

/**
 * @fn  DCPSDLL ZR_INT8* ParameterHeaderSerialize(CDRSerializer* cdr, ZR_BOOLEAN useExtended, ZR_BOOLEAN mustUnderstand, ZR_UINT32 memberId);
 *
 * @ingroup CoreBaseFunction
 *
 * @brief   ���л�����ͷ��������չCDR.
 *
 * @param [in,out]  cdr     ָ�����л�����
 * @param   useExtended     �Ƿ�ʹ��PID_EXTENDED.
 * @param   mustUnderstand  �Ƿ�������ò�����
 * @param   memberId        ������Ӧ�ĳ�Ա��memberId.
 *
 * @return  NULL��ʾʧ�ܣ������ʾ����ĳ��ȵĵ�ַ��
 */

DCPSDLL ZR_INT8* ParameterHeaderSerialize(CDRSerializer* cdr, ZR_BOOLEAN useExtended, ZR_BOOLEAN mustUnderstand, ZR_UINT32 memberId);

/**
 * @fn  void ParameterLenSerialize( CDRSerializer* cdr, ZR_INT8* lenAddr, ZR_UINT32 length, ZR_UINT16 lengthSize, ZR_BOOLEAN littleEndian);
 *
 * @ingroup CoreBaseFunction
 *
 * @brief   ����Parameter�ĳ��ȡ�
 *
 * @param [in,out]  cdr     ָ�����л�����
 * @param [in,out]  lenAddr �������ȵĵ�ַ��
 * @param   length          ��Ҫ��Ĳ������ȡ�
 * @param   lengthSize      �������ȵ��ֽ�����
 *
 * @return  0��ʾ�ɹ���С��0��ʾʧ�ܡ�
 */

DCPSDLL void ParameterLenSerialize(
    CDRSerializer* cdr,
    ZR_INT8* lenAddr,
    ZR_UINT32 length,
    ZR_UINT16 lengthSize);

/**
 * @fn  DCPSDLL ZR_INT32 ParameterHeaderDeserialize( CDRDeserializer* cdr, ZR_UINT32* memberId, ZR_UINT32* length, ZR_BOOLEAN* useExtend, ZR_BOOLEAN* mustUnderstand);
 *
 * @ingroup CoreBaseFunction
 *
 * @brief   �����л�����ͷ��
 *
 * @param [in,out]  cdr             ָ�������л�����
 * @param [in,out]  memberId        �����л�������memberId��
 * @param [in,out]  length          �����л�������length��
 * @param [in,out]  useExtend       �����л������Ƿ�ʹ�õ�PID_EXTENDED.
 * @param [in,out]  mustUnderstand  �����л������Ƿ�������ó�Ա��
 *
 * @return  0��ʾ�ɹ���С��0��ʾʧ�ܡ�
 */

DCPSDLL ZR_INT32 ParameterHeaderDeserialize(
    CDRDeserializer* cdr,
    ZR_UINT32* memberId,
    ZR_UINT32* length,
    ZR_BOOLEAN* useExtend,
    ZR_BOOLEAN* mustUnderstand);

/**
 * @fn  DCPSDLL ZR_INT32 CDRSerializeGetKeyHash(CDRSerializer* cdr, ZR_UINT8* keyHash, ZR_BOOLEAN needMd5);
 *
 * @ingroup CoreBaseFunction
 *
 * @brief   ��ȡ������md5hashֵ��
 *
 * @param [in,out]  cdr     ָ��Ŀ�ꡣ
 * @param [in,out]  keyHash ��ȡ�Ľ����
 * @param   needMd5         �Ƿ���Ҫ��MD5��
 *
 * @return  0��ʾ�ɹ���С��0��ʾʧ�ܡ�
 */

DCPSDLL ZR_INT32 CDRSerializeGetKeyHash(CDRSerializer* cdr, ZR_UINT8* keyHash, ZR_BOOLEAN needMd5);

/**
 * @fn  DCPSDLL void CDRDeserializerPushState(CDRDeserializer* cdr);
 *
 * @ingroup CoreBaseFunction
 *
 * @brief   ���淴���л�����״̬��
 *
 * @param [in,out]  cdr ָ�������л�����
 */

DCPSDLL void CDRDeserializerPushState(CDRDeserializer* cdr);

/**
 * @fn  DCPSDLL void CDRDeserializerPopState(CDRDeserializer* cdr);
 *
 * @ingroup CoreBaseFunction
 *
 * @brief   ���¼��ط����л�����״̬��
 *
 * @param [in,out]  cdr ָ�������л�����
 */

DCPSDLL void CDRDeserializerPopState(CDRDeserializer* cdr);

/**
 * @fn  DCPSDLL void CDRSerializerAheadWrPtr(CDRSerializer* self, ZR_UINT32 length);
 *
 * @brief   �ֶ�����CDR���л�����дָ�롣
 *
 * @param [in,out]  self    ָ��Ŀ�ꡣ
 * @param   length          ��������
 */

DCPSDLL void CDRSerializerAheadWrPtr(CDRSerializer* self, ZR_UINT32 length);

#ifdef _ZRDDS_INCLUDE_SPARE_TYPE
void* CDRDeserializerGetLastSample(CDRDeserializer* self);

void CDRDeserializerSetLastSample(CDRDeserializer* self, void* lastSample);

void* CDRSerializerGetLastSample(CDRSerializer* self);

void CDRSerializerSetLastSample(CDRSerializer* self, void* lastSample);
#endif //_ZRDDS_INCLUDE_SPARE_TYPE

#ifdef __cplusplus
}
#endif /* __cplusplus*/

#endif /* CDRStream_h__*/
