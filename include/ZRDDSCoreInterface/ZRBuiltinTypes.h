/**
 * @file:       ZRBuiltinTypes.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#ifndef ZRBuiltinTypes_H_
#define ZRBuiltinTypes_H_

#include "OsResource.h"
#include "ZRSequence.h"
#include "InstanceHandle_t.h"
#include "CDRStream.h"
#include "ZRBuiltinTypes.h"
#include "ZRMemPool.h"
#include "TypeCodeKind.h"

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @struct DDS_BooleanSeq
 *
 * @ingroup CoreBuiltinTypes
 *
 * @brief   ���������������� DDS_Boolean �����У��μ�@ref CoreSeqStruct ��
 */

DDS_SEQUENCE_CPP(DDS_BooleanSeq, DDS_Boolean);

/**
 * @struct DDS_OctetSeq
 *
 * @ingroup CoreBuiltinTypes
 *
 * @brief   ���������������� DDS_Octet �����У��μ�@ref CoreSeqStruct ��
 *
 * @details ZRDDSΪ�Ż����ݴ������ܣ����������������У���ͨ�����������ɵ�֧�ֺ���NoSerializingSupported�����ķ���ֵ�жϣ���
 *          ����ȡ�ֶ����洢�ķ�ʽ����ʱ���ݲ��ٴ洢��_discontiguous_buffer�Լ�_discontiguous_buffer�У�
 *          ���洢��_fixedFragments(_fragmentNum<=64)����_variousFragments (_fragmentNum>64)�У�
 *          ���е�һ�ֶεĳ���Ϊ_firstFragSize�����һ���ֶεĳ���Ϊ_lastFragSize������ֶεĳ���Ϊ_fragmentSize��
 *          �ֶδ洢����Ϊ��
 *          - sequence��������ΪDDS_OctetSeq����DDS_CharSeq���ͣ�
 *          - sequence���ͳ�ԱΪ����������ݹ����������͵����һ����Ա��
 *          - �����һ����Ա�⣬��Ϊ����������Ķ����������ͣ�
 *          - ͨ��Э�����UDP�������ڴ桢RapidIO��
 *          ����������4������ʱ�����Ͷ�Ϊ�Ż����ܣ���ʱ���������û�����ָ�룬�ʶ���ÿ�η�������֮ǰ��
 *          ��Ӧ����ensure_length����֤�ռ�����¸�ֵ��
 */

DDS_SEQUENCE_CPP(DDS_OctetSeq, DDS_Octet);

/**
 * @struct DDS_CharSeq
 *
 * @ingroup CoreBuiltinTypes
 *
 * @brief   ���������������� DDS_Char �����У��μ�@ref CoreSeqStruct ��
 *
 * @details �μ� DDS_OctetSeq
 */

DDS_SEQUENCE_CPP(DDS_CharSeq, DDS_Char);

/**
 * @struct DDS_ShortSeq
 *
 * @ingroup CoreBuiltinTypes
 *
 * @brief   ���������������� DDS_Short �����У��μ�@ref CoreSeqStruct ��
 */

DDS_SEQUENCE_CPP(DDS_ShortSeq, DDS_Short);

/**
 * @struct DDS_UShortSeq
 *
 * @ingroup CoreBuiltinTypes
 *
 * @brief   ���������������� DDS_UShort �����У��μ�@ref CoreSeqStruct ��
 */

DDS_SEQUENCE_CPP(DDS_UShortSeq, DDS_UShort);

/**
 * @struct DDS_LongSeq
 *
 * @ingroup CoreBuiltinTypes
 *
 * @brief   ���������������� DDS_Long �����У��μ�@ref CoreSeqStruct ��
 */

DDS_SEQUENCE_CPP(DDS_LongSeq, DDS_Long);

/**
 * @struct DDS_ULongSeq
 *
 * @ingroup CoreBuiltinTypes
 *
 * @brief   ���������������� DDS_ULong �����У��μ�@ref CoreSeqStruct ��
 */

DDS_SEQUENCE_CPP(DDS_ULongSeq, DDS_ULong);

/**
 * @struct DDS_LongLongSeq
 *
 * @ingroup CoreBuiltinTypes
 *
 * @brief   ���������������� DDS_LongLong �����У��μ�@ref CoreSeqStruct ��
 */

DDS_SEQUENCE_CPP(DDS_LongLongSeq, DDS_LongLong);

/**
 * @struct DDS_ULongLongSeq
 *
 * @ingroup CoreBuiltinTypes
 *
 * @brief   ���������������� DDS_ULongLong �����У��μ�@ref CoreSeqStruct ��
 */

DDS_SEQUENCE_CPP(DDS_ULongLongSeq, DDS_ULongLong);

/**
 * @struct DDS_FloatSeq
 *
 * @ingroup CoreBuiltinTypes
 *
 * @brief   ���������������� DDS_Float �����У��μ�@ref CoreSeqStruct ��
 */

DDS_SEQUENCE_CPP(DDS_FloatSeq, DDS_Float);

/**
 * @struct DDS_DoubleSeq
 *
 * @ingroup CoreBuiltinTypes
 *
 * @brief   ���������������� DDS_Double �����У��μ�@ref CoreSeqStruct ��
 */

DDS_SEQUENCE_CPP(DDS_DoubleSeq, DDS_Double);

/**
 * @typedef DDS_Char* DDS_String
 *
 * @ingroup CoreBuiltinTypes
 *
 * @brief   ���������ַ����������͡�
 */

typedef DDS_Char* DDS_String;

/**
 * @struct DDS_StringSeq
 *
 * @ingroup CoreBuiltinTypes
 *
 * @brief   ���������������� DDS_Char* �����У��μ�@ref CoreSeqStruct ��
 */

DDS_SEQUENCE_CPP(DDS_StringSeq, DDS_Char*);

/**
 * ��������Ϊ����601����ʹ�á�
 */
#ifdef _ZRDDS_INCLUDE_601_TYPE

/**
 * @typedef DDS_OctetSeq DDS_UINT8Seq
 *
 * @ingroup CoreBuiltinTypes
 *
 * @brief   DDS_OctetSeq �ı�����
 */

typedef DDS_OctetSeq DDS_UINT8Seq;
#define DDS_UINT8Seq_is_initialized DDS_OctetSeq_is_initialized
#define DDS_UINT8Seq_set DDS_OctetSeq_set
#define DDS_UINT8Seq_initialize DDS_OctetSeq_initialize
#define DDS_UINT8Seq_new DDS_OctetSeq_new
#define DDS_UINT8Seq_get_maximum DDS_OctetSeq_get_maximum
#define DDS_UINT8Seq_set_maximum DDS_OctetSeq_set_maximum
#define DDS_UINT8Seq_get_length DDS_OctetSeq_get_length
#define DDS_UINT8Seq_set_length DDS_OctetSeq_set_length
#define DDS_UINT8Seq_ensure_length DDS_OctetSeq_ensure_length
#define DDS_UINT8Seq_get_reference DDS_OctetSeq_get_reference
#define DDS_UINT8Seq_append DDS_OctetSeq_append
#define DDS_UINT8Seq_copy_no_alloc DDS_OctetSeq_copy_no_alloc
#define DDS_UINT8Seq_copy DDS_OctetSeq_copy
#define DDS_UINT8Seq_compare DDS_OctetSeq_compare
#define DDS_UINT8Seq_from_array DDS_OctetSeq_from_array
#define DDS_UINT8Seq_to_array DDS_OctetSeq_to_array
#define DDS_UINT8Seq_loan_contiguous DDS_OctetSeq_loan_contiguous
#define DDS_UINT8Seq_loan_discontiguous DDS_OctetSeq_loan_discontiguous
#define DDS_UINT8Seq_unloan DDS_OctetSeq_unloan
#define DDS_UINT8Seq_get_contiguous_buffer DDS_OctetSeq_get_contiguous_buffer
#define DDS_UINT8Seq_get_discontiguous_buffer DDS_OctetSeq_get_discontiguous_buffer
#define DDS_UINT8Seq_get_reader_and_data_ptr DDS_OctetSeq_get_reader_and_data_ptr
#define DDS_UINT8Seq_set_reader_and_data_ptr DDS_OctetSeq_set_reader_and_data_ptr
#define DDS_UINT8Seq_has_ownership DDS_OctetSeq_has_ownership
#define DDS_UINT8Seq_clear DDS_OctetSeq_clear
#define DDS_UINT8Seq_finalize DDS_OctetSeq_finalize
#define DDS_UINT8Seq_initialize_ex DDS_OctetSeq_initialize_ex

/**
 * @typedef DDS_CharSeq DDS_INT8Seq
 *
 * @ingroup CoreBuiltinTypes
 *
 * @brief   DDS_CharSeq �ı�����
 */

typedef DDS_CharSeq DDS_INT8Seq;
#define DDS_INT8Seq_is_initialized DDS_CharSeq_is_initialized
#define DDS_INT8Seq_set DDS_CharSeq_set
#define DDS_INT8Seq_initialize DDS_CharSeq_initialize
#define DDS_INT8Seq_new DDS_CharSeq_new
#define DDS_INT8Seq_get_maximum DDS_CharSeq_get_maximum
#define DDS_INT8Seq_set_maximum DDS_CharSeq_set_maximum
#define DDS_INT8Seq_get_length DDS_CharSeq_get_length
#define DDS_INT8Seq_set_length DDS_CharSeq_set_length
#define DDS_INT8Seq_ensure_length DDS_CharSeq_ensure_length
#define DDS_INT8Seq_get_reference DDS_CharSeq_get_reference
#define DDS_INT8Seq_append DDS_CharSeq_append
#define DDS_INT8Seq_copy_no_alloc DDS_CharSeq_copy_no_alloc
#define DDS_INT8Seq_copy DDS_CharSeq_copy
#define DDS_INT8Seq_compare DDS_CharSeq_compare
#define DDS_INT8Seq_from_array DDS_CharSeq_from_array
#define DDS_INT8Seq_to_array DDS_CharSeq_to_array
#define DDS_INT8Seq_loan_contiguous DDS_CharSeq_loan_contiguous
#define DDS_INT8Seq_loan_discontiguous DDS_CharSeq_loan_discontiguous
#define DDS_INT8Seq_unloan DDS_CharSeq_unloan
#define DDS_INT8Seq_get_contiguous_buffer DDS_CharSeq_get_contiguous_buffer
#define DDS_INT8Seq_get_discontiguous_buffer DDS_CharSeq_get_discontiguous_buffer
#define DDS_INT8Seq_get_reader_and_data_ptr DDS_CharSeq_get_reader_and_data_ptr
#define DDS_INT8Seq_set_reader_and_data_ptr DDS_CharSeq_set_reader_and_data_ptr
#define DDS_INT8Seq_has_ownership DDS_CharSeq_has_ownership
#define DDS_INT8Seq_clear DDS_CharSeq_clear
#define DDS_INT8Seq_finalize DDS_CharSeq_finalize
#define DDS_INT8Seq_initialize_ex DDS_CharSeq_initialize_ex

/**
 * @typedef DDS_BooleanSeq DDS_BOOLEANSeq
 *
 * @ingroup CoreBuiltinTypes
 *
 * @brief   DDS_BooleanSeq �ı�����
 */

typedef DDS_BooleanSeq DDS_BOOLEANSeq;
#define DDS_BOOLEANSeq_is_initialized DDS_BooleanSeq_is_initialized
#define DDS_BOOLEANSeq_set DDS_BooleanSeq_set
#define DDS_BOOLEANSeq_initialize DDS_BooleanSeq_initialize
#define DDS_BOOLEANSeq_new DDS_BooleanSeq_new
#define DDS_BOOLEANSeq_get_maximum DDS_BooleanSeq_get_maximum
#define DDS_BOOLEANSeq_set_maximum DDS_BooleanSeq_set_maximum
#define DDS_BOOLEANSeq_get_length DDS_BooleanSeq_get_length
#define DDS_BOOLEANSeq_set_length DDS_BooleanSeq_set_length
#define DDS_BOOLEANSeq_ensure_length DDS_BooleanSeq_ensure_length
#define DDS_BOOLEANSeq_get_reference DDS_BooleanSeq_get_reference
#define DDS_BOOLEANSeq_append DDS_BooleanSeq_append
#define DDS_BOOLEANSeq_copy_no_alloc DDS_BooleanSeq_copy_no_alloc
#define DDS_BOOLEANSeq_copy DDS_BooleanSeq_copy
#define DDS_BOOLEANSeq_compare DDS_BooleanSeq_compare
#define DDS_BOOLEANSeq_from_array DDS_BooleanSeq_from_array
#define DDS_BOOLEANSeq_to_array DDS_BooleanSeq_to_array
#define DDS_BOOLEANSeq_loan_contiguous DDS_BooleanSeq_loan_contiguous
#define DDS_BOOLEANSeq_loan_discontiguous DDS_BooleanSeq_loan_discontiguous
#define DDS_BOOLEANSeq_unloan DDS_BooleanSeq_unloan
#define DDS_BOOLEANSeq_get_contiguous_buffer DDS_BooleanSeq_get_contiguous_buffer
#define DDS_BOOLEANSeq_get_discontiguous_buffer DDS_BooleanSeq_get_discontiguous_buffer
#define DDS_BOOLEANSeq_get_reader_and_data_ptr DDS_BooleanSeq_get_reader_and_data_ptr
#define DDS_BOOLEANSeq_set_reader_and_data_ptr DDS_BooleanSeq_set_reader_and_data_ptr
#define DDS_BOOLEANSeq_has_ownership DDS_BooleanSeq_has_ownership
#define DDS_BOOLEANSeq_clear DDS_BooleanSeq_clear
#define DDS_BOOLEANSeq_finalize DDS_BooleanSeq_finalize
#define DDS_BOOLEANSeq_initialize_ex DDS_BooleanSeq_initialize_ex

/**
 * @typedef DDS_ShortSeq DDS_INT16Seq
 *
 * @ingroup CoreBuiltinTypes
 *
 * @brief   DDS_ShortSeq �ı�����
 */

typedef DDS_ShortSeq DDS_INT16Seq;
#define DDS_INT16Seq_is_initialized DDS_ShortSeq_is_initialized
#define DDS_INT16Seq_set DDS_ShortSeq_set
#define DDS_INT16Seq_initialize DDS_ShortSeq_initialize
#define DDS_INT16Seq_new DDS_ShortSeq_new
#define DDS_INT16Seq_get_maximum DDS_ShortSeq_get_maximum
#define DDS_INT16Seq_set_maximum DDS_ShortSeq_set_maximum
#define DDS_INT16Seq_get_length DDS_ShortSeq_get_length
#define DDS_INT16Seq_set_length DDS_ShortSeq_set_length
#define DDS_INT16Seq_ensure_length DDS_ShortSeq_ensure_length
#define DDS_INT16Seq_get_reference DDS_ShortSeq_get_reference
#define DDS_INT16Seq_append DDS_ShortSeq_append
#define DDS_INT16Seq_copy_no_alloc DDS_ShortSeq_copy_no_alloc
#define DDS_INT16Seq_copy DDS_ShortSeq_copy
#define DDS_INT16Seq_compare DDS_ShortSeq_compare
#define DDS_INT16Seq_from_array DDS_ShortSeq_from_array
#define DDS_INT16Seq_to_array DDS_ShortSeq_to_array
#define DDS_INT16Seq_loan_contiguous DDS_ShortSeq_loan_contiguous
#define DDS_INT16Seq_loan_discontiguous DDS_ShortSeq_loan_discontiguous
#define DDS_INT16Seq_unloan DDS_ShortSeq_unloan
#define DDS_INT16Seq_get_contiguous_buffer DDS_ShortSeq_get_contiguous_buffer
#define DDS_INT16Seq_get_discontiguous_buffer DDS_ShortSeq_get_discontiguous_buffer
#define DDS_INT16Seq_get_reader_and_data_ptr DDS_ShortSeq_get_reader_and_data_ptr
#define DDS_INT16Seq_set_reader_and_data_ptr DDS_ShortSeq_set_reader_and_data_ptr
#define DDS_INT16Seq_has_ownership DDS_ShortSeq_has_ownership
#define DDS_INT16Seq_clear DDS_ShortSeq_clear
#define DDS_INT16Seq_finalize DDS_ShortSeq_finalize
#define DDS_INT16Seq_initialize_ex DDS_ShortSeq_initialize_ex

/**
 * @typedef DDS_UShortSeq DDS_UINT16Seq
 *
 * @ingroup CoreBuiltinTypes
 *
 * @brief   DDS_UShortSeq �ı�����
 */

typedef DDS_UShortSeq DDS_UINT16Seq;
#define DDS_UINT16Seq_is_initialized DDS_UShortSeq_is_initialized
#define DDS_UINT16Seq_set DDS_UShortSeq_set
#define DDS_UINT16Seq_initialize DDS_UShortSeq_initialize
#define DDS_UINT16Seq_new DDS_UShortSeq_new
#define DDS_UINT16Seq_get_maximum DDS_UShortSeq_get_maximum
#define DDS_UINT16Seq_set_maximum DDS_UShortSeq_set_maximum
#define DDS_UINT16Seq_get_length DDS_UShortSeq_get_length
#define DDS_UINT16Seq_set_length DDS_UShortSeq_set_length
#define DDS_UINT16Seq_ensure_length DDS_UShortSeq_ensure_length
#define DDS_UINT16Seq_get_reference DDS_UShortSeq_get_reference
#define DDS_UINT16Seq_append DDS_UShortSeq_append
#define DDS_UINT16Seq_copy_no_alloc DDS_UShortSeq_copy_no_alloc
#define DDS_UINT16Seq_copy DDS_UShortSeq_copy
#define DDS_UINT16Seq_compare DDS_UShortSeq_compare
#define DDS_UINT16Seq_from_array DDS_UShortSeq_from_array
#define DDS_UINT16Seq_to_array DDS_UShortSeq_to_array
#define DDS_UINT16Seq_loan_contiguous DDS_UShortSeq_loan_contiguous
#define DDS_UINT16Seq_loan_discontiguous DDS_UShortSeq_loan_discontiguous
#define DDS_UINT16Seq_unloan DDS_UShortSeq_unloan
#define DDS_UINT16Seq_get_contiguous_buffer DDS_UShortSeq_get_contiguous_buffer
#define DDS_UINT16Seq_get_discontiguous_buffer DDS_UShortSeq_get_discontiguous_buffer
#define DDS_UINT16Seq_get_reader_and_data_ptr DDS_UShortSeq_get_reader_and_data_ptr
#define DDS_UINT16Seq_set_reader_and_data_ptr DDS_UShortSeq_set_reader_and_data_ptr
#define DDS_UINT16Seq_has_ownership DDS_UShortSeq_has_ownership
#define DDS_UINT16Seq_clear DDS_UShortSeq_clear
#define DDS_UINT16Seq_finalize DDS_UShortSeq_finalize
#define DDS_UINT16Seq_initialize_ex DDS_UShortSeq_initialize_ex

/**
 * @typedef DDS_LongSeq DDS_INT32Seq
 *
 * @ingroup CoreBuiltinTypes
 *
 * @brief   DDS_LongSeq �ı�����
 */

typedef DDS_LongSeq DDS_INT32Seq;
#define DDS_INT32Seq_is_initialized DDS_LongSeq_is_initialized
#define DDS_INT32Seq_set DDS_LongSeq_set
#define DDS_INT32Seq_initialize DDS_LongSeq_initialize
#define DDS_INT32Seq_new DDS_LongSeq_new
#define DDS_INT32Seq_get_maximum DDS_LongSeq_get_maximum
#define DDS_INT32Seq_set_maximum DDS_LongSeq_set_maximum
#define DDS_INT32Seq_get_length DDS_LongSeq_get_length
#define DDS_INT32Seq_set_length DDS_LongSeq_set_length
#define DDS_INT32Seq_ensure_length DDS_LongSeq_ensure_length
#define DDS_INT32Seq_get_reference DDS_LongSeq_get_reference
#define DDS_INT32Seq_append DDS_LongSeq_append
#define DDS_INT32Seq_copy_no_alloc DDS_LongSeq_copy_no_alloc
#define DDS_INT32Seq_copy DDS_LongSeq_copy
#define DDS_INT32Seq_compare DDS_LongSeq_compare
#define DDS_INT32Seq_from_array DDS_LongSeq_from_array
#define DDS_INT32Seq_to_array DDS_LongSeq_to_array
#define DDS_INT32Seq_loan_contiguous DDS_LongSeq_loan_contiguous
#define DDS_INT32Seq_loan_discontiguous DDS_LongSeq_loan_discontiguous
#define DDS_INT32Seq_unloan DDS_LongSeq_unloan
#define DDS_INT32Seq_get_contiguous_buffer DDS_LongSeq_get_contiguous_buffer
#define DDS_INT32Seq_get_discontiguous_buffer DDS_LongSeq_get_discontiguous_buffer
#define DDS_INT32Seq_get_reader_and_data_ptr DDS_LongSeq_get_reader_and_data_ptr
#define DDS_INT32Seq_set_reader_and_data_ptr DDS_LongSeq_set_reader_and_data_ptr
#define DDS_INT32Seq_has_ownership DDS_LongSeq_has_ownership
#define DDS_INT32Seq_clear DDS_LongSeq_clear
#define DDS_INT32Seq_finalize DDS_LongSeq_finalize
#define DDS_INT32Seq_initialize_ex DDS_LongSeq_initialize_ex

/**
 * @typedef DDS_ULongSeq DDS_UINT32Seq
 *
 * @ingroup CoreBuiltinTypes
 *
 * @brief   DDS_ULongSeq �ı�����
 */

typedef DDS_ULongSeq DDS_UINT32Seq;
#define DDS_UINT32Seq_is_initialized DDS_ULongSeq_is_initialized
#define DDS_UINT32Seq_set DDS_ULongSeq_set
#define DDS_UINT32Seq_initialize DDS_ULongSeq_initialize
#define DDS_UINT32Seq_new DDS_ULongSeq_new
#define DDS_UINT32Seq_get_maximum DDS_ULongSeq_get_maximum
#define DDS_UINT32Seq_set_maximum DDS_ULongSeq_set_maximum
#define DDS_UINT32Seq_get_length DDS_ULongSeq_get_length
#define DDS_UINT32Seq_set_length DDS_ULongSeq_set_length
#define DDS_UINT32Seq_ensure_length DDS_ULongSeq_ensure_length
#define DDS_UINT32Seq_get_reference DDS_ULongSeq_get_reference
#define DDS_UINT32Seq_append DDS_ULongSeq_append
#define DDS_UINT32Seq_copy_no_alloc DDS_ULongSeq_copy_no_alloc
#define DDS_UINT32Seq_copy DDS_ULongSeq_copy
#define DDS_UINT32Seq_compare DDS_ULongSeq_compare
#define DDS_UINT32Seq_from_array DDS_ULongSeq_from_array
#define DDS_UINT32Seq_to_array DDS_ULongSeq_to_array
#define DDS_UINT32Seq_loan_contiguous DDS_ULongSeq_loan_contiguous
#define DDS_UINT32Seq_loan_discontiguous DDS_ULongSeq_loan_discontiguous
#define DDS_UINT32Seq_unloan DDS_ULongSeq_unloan
#define DDS_UINT32Seq_get_contiguous_buffer DDS_ULongSeq_get_contiguous_buffer
#define DDS_UINT32Seq_get_discontiguous_buffer DDS_ULongSeq_get_discontiguous_buffer
#define DDS_UINT32Seq_get_reader_and_data_ptr DDS_ULongSeq_get_reader_and_data_ptr
#define DDS_UINT32Seq_set_reader_and_data_ptr DDS_ULongSeq_set_reader_and_data_ptr
#define DDS_UINT32Seq_has_ownership DDS_ULongSeq_has_ownership
#define DDS_UINT32Seq_clear DDS_ULongSeq_clear
#define DDS_UINT32Seq_finalize DDS_ULongSeq_finalize
#define DDS_UINT32Seq_initialize_ex DDS_ULongSeq_initialize_ex

/**
 * @typedef DDS_LongLongSeq DDS_INT64Seq
 *
 * @ingroup CoreBuiltinTypes
 *
 * @brief   DDS_LongLongSeq �ı�����
 */

typedef DDS_LongLongSeq DDS_INT64Seq;
#define DDS_INT64Seq_is_initialized DDS_LongLongSeq_is_initialized
#define DDS_INT64Seq_set DDS_LongLongSeq_set
#define DDS_INT64Seq_initialize DDS_LongLongSeq_initialize
#define DDS_INT64Seq_new DDS_LongLongSeq_new
#define DDS_INT64Seq_get_maximum DDS_LongLongSeq_get_maximum
#define DDS_INT64Seq_set_maximum DDS_LongLongSeq_set_maximum
#define DDS_INT64Seq_get_length DDS_LongLongSeq_get_length
#define DDS_INT64Seq_set_length DDS_LongLongSeq_set_length
#define DDS_INT64Seq_ensure_length DDS_LongLongSeq_ensure_length
#define DDS_INT64Seq_get_reference DDS_LongLongSeq_get_reference
#define DDS_INT64Seq_append DDS_LongLongSeq_append
#define DDS_INT64Seq_copy_no_alloc DDS_LongLongSeq_copy_no_alloc
#define DDS_INT64Seq_copy DDS_LongLongSeq_copy
#define DDS_INT64Seq_compare DDS_LongLongSeq_compare
#define DDS_INT64Seq_from_array DDS_LongLongSeq_from_array
#define DDS_INT64Seq_to_array DDS_LongLongSeq_to_array
#define DDS_INT64Seq_loan_contiguous DDS_LongLongSeq_loan_contiguous
#define DDS_INT64Seq_loan_discontiguous DDS_LongLongSeq_loan_discontiguous
#define DDS_INT64Seq_unloan DDS_LongLongSeq_unloan
#define DDS_INT64Seq_get_contiguous_buffer DDS_LongLongSeq_get_contiguous_buffer
#define DDS_INT64Seq_get_discontiguous_buffer DDS_LongLongSeq_get_discontiguous_buffer
#define DDS_INT64Seq_get_reader_and_data_ptr DDS_LongLongSeq_get_reader_and_data_ptr
#define DDS_INT64Seq_set_reader_and_data_ptr DDS_LongLongSeq_set_reader_and_data_ptr
#define DDS_INT64Seq_has_ownership DDS_LongLongSeq_has_ownership
#define DDS_INT64Seq_clear DDS_LongLongSeq_clear
#define DDS_INT64Seq_finalize DDS_LongLongSeq_finalize
#define DDS_INT64Seq_initialize_ex DDS_LongLongSeq_initialize_ex

/**
 * @typedef DDS_ULongLongSeq DDS_UINT64Seq
 *
 * @ingroup CoreBuiltinTypes
 *
 * @brief   DDS_ULongLongSeq �ı�����
 */

typedef DDS_ULongLongSeq DDS_UINT64Seq;
#define DDS_UINT64Seq_is_initialized DDS_ULongLongSeq_is_initialized
#define DDS_UINT64Seq_set DDS_ULongLongSeq_set
#define DDS_UINT64Seq_initialize DDS_ULongLongSeq_initialize
#define DDS_UINT64Seq_new DDS_ULongLongSeq_new
#define DDS_UINT64Seq_get_maximum DDS_ULongLongSeq_get_maximum
#define DDS_UINT64Seq_set_maximum DDS_ULongLongSeq_set_maximum
#define DDS_UINT64Seq_get_length DDS_ULongLongSeq_get_length
#define DDS_UINT64Seq_set_length DDS_ULongLongSeq_set_length
#define DDS_UINT64Seq_ensure_length DDS_ULongLongSeq_ensure_length
#define DDS_UINT64Seq_get_reference DDS_ULongLongSeq_get_reference
#define DDS_UINT64Seq_append DDS_ULongLongSeq_append
#define DDS_UINT64Seq_copy_no_alloc DDS_ULongLongSeq_copy_no_alloc
#define DDS_UINT64Seq_copy DDS_ULongLongSeq_copy
#define DDS_UINT64Seq_compare DDS_ULongLongSeq_compare
#define DDS_UINT64Seq_from_array DDS_ULongLongSeq_from_array
#define DDS_UINT64Seq_to_array DDS_ULongLongSeq_to_array
#define DDS_UINT64Seq_loan_contiguous DDS_ULongLongSeq_loan_contiguous
#define DDS_UINT64Seq_loan_discontiguous DDS_ULongLongSeq_loan_discontiguous
#define DDS_UINT64Seq_unloan DDS_ULongLongSeq_unloan
#define DDS_UINT64Seq_get_contiguous_buffer DDS_ULongLongSeq_get_contiguous_buffer
#define DDS_UINT64Seq_get_discontiguous_buffer DDS_ULongLongSeq_get_discontiguous_buffer
#define DDS_UINT64Seq_get_reader_and_data_ptr DDS_ULongLongSeq_get_reader_and_data_ptr
#define DDS_UINT64Seq_set_reader_and_data_ptr DDS_ULongLongSeq_set_reader_and_data_ptr
#define DDS_UINT64Seq_has_ownership DDS_ULongLongSeq_has_ownership
#define DDS_UINT64Seq_clear DDS_ULongLongSeq_clear
#define DDS_UINT64Seq_finalize DDS_ULongLongSeq_finalize
#define DDS_UINT64Seq_initialize_ex DDS_ULongLongSeq_initialize_ex

/**
 * @typedef DDS_FloatSeq DDS_FLOAT32Seq
 *
 * @ingroup CoreBuiltinTypes
 *
 * @brief   DDS_FloatSeq �ı�����
 */

typedef DDS_FloatSeq DDS_FLOAT32Seq;
#define DDS_FLOAT32Seq_is_initialized DDS_FloatSeq_is_initialized
#define DDS_FLOAT32Seq_set DDS_FloatSeq_set
#define DDS_FLOAT32Seq_initialize DDS_FloatSeq_initialize
#define DDS_FLOAT32Seq_new DDS_FloatSeq_new
#define DDS_FLOAT32Seq_get_maximum DDS_FloatSeq_get_maximum
#define DDS_FLOAT32Seq_set_maximum DDS_FloatSeq_set_maximum
#define DDS_FLOAT32Seq_get_length DDS_FloatSeq_get_length
#define DDS_FLOAT32Seq_set_length DDS_FloatSeq_set_length
#define DDS_FLOAT32Seq_ensure_length DDS_FloatSeq_ensure_length
#define DDS_FLOAT32Seq_get_reference DDS_FloatSeq_get_reference
#define DDS_FLOAT32Seq_append DDS_FloatSeq_append
#define DDS_FLOAT32Seq_copy_no_alloc DDS_FloatSeq_copy_no_alloc
#define DDS_FLOAT32Seq_copy DDS_FloatSeq_copy
#define DDS_FLOAT32Seq_compare DDS_FloatSeq_compare
#define DDS_FLOAT32Seq_from_array DDS_FloatSeq_from_array
#define DDS_FLOAT32Seq_to_array DDS_FloatSeq_to_array
#define DDS_FLOAT32Seq_loan_contiguous DDS_FloatSeq_loan_contiguous
#define DDS_FLOAT32Seq_loan_discontiguous DDS_FloatSeq_loan_discontiguous
#define DDS_FLOAT32Seq_unloan DDS_FloatSeq_unloan
#define DDS_FLOAT32Seq_get_contiguous_buffer DDS_FloatSeq_get_contiguous_buffer
#define DDS_FLOAT32Seq_get_discontiguous_buffer DDS_FloatSeq_get_discontiguous_buffer
#define DDS_FLOAT32Seq_get_reader_and_data_ptr DDS_FloatSeq_get_reader_and_data_ptr
#define DDS_FLOAT32Seq_set_reader_and_data_ptr DDS_FloatSeq_set_reader_and_data_ptr
#define DDS_FLOAT32Seq_has_ownership DDS_FloatSeq_has_ownership
#define DDS_FLOAT32Seq_clear DDS_FloatSeq_clear
#define DDS_FLOAT32Seq_finalize DDS_FloatSeq_finalize
#define DDS_FLOAT32Seq_initialize_ex DDS_FloatSeq_initialize_ex

/**
 * @typedef DDS_DoubleSeq DDS_DOUBLE64Seq
 *
 * @ingroup CoreBuiltinTypes
 *
 * @brief   DDS_DoubleSeq �ı�����
 */

typedef DDS_DoubleSeq DDS_DOUBLE64Seq;
#define DDS_DOUBLE64Seq_is_initialized DDS_DoubleSeq_is_initialized
#define DDS_DOUBLE64Seq_set DDS_DoubleSeq_set
#define DDS_DOUBLE64Seq_initialize DDS_DoubleSeq_initialize
#define DDS_DOUBLE64Seq_new DDS_DoubleSeq_new
#define DDS_DOUBLE64Seq_get_maximum DDS_DoubleSeq_get_maximum
#define DDS_DOUBLE64Seq_set_maximum DDS_DoubleSeq_set_maximum
#define DDS_DOUBLE64Seq_get_length DDS_DoubleSeq_get_length
#define DDS_DOUBLE64Seq_set_length DDS_DoubleSeq_set_length
#define DDS_DOUBLE64Seq_ensure_length DDS_DoubleSeq_ensure_length
#define DDS_DOUBLE64Seq_get_reference DDS_DoubleSeq_get_reference
#define DDS_DOUBLE64Seq_append DDS_DoubleSeq_append
#define DDS_DOUBLE64Seq_copy_no_alloc DDS_DoubleSeq_copy_no_alloc
#define DDS_DOUBLE64Seq_copy DDS_DoubleSeq_copy
#define DDS_DOUBLE64Seq_compare DDS_DoubleSeq_compare
#define DDS_DOUBLE64Seq_from_array DDS_DoubleSeq_from_array
#define DDS_DOUBLE64Seq_to_array DDS_DoubleSeq_to_array
#define DDS_DOUBLE64Seq_loan_contiguous DDS_DoubleSeq_loan_contiguous
#define DDS_DOUBLE64Seq_loan_discontiguous DDS_DoubleSeq_loan_discontiguous
#define DDS_DOUBLE64Seq_unloan DDS_DoubleSeq_unloan
#define DDS_DOUBLE64Seq_get_contiguous_buffer DDS_DoubleSeq_get_contiguous_buffer
#define DDS_DOUBLE64Seq_get_discontiguous_buffer DDS_DoubleSeq_get_discontiguous_buffer
#define DDS_DOUBLE64Seq_get_reader_and_data_ptr DDS_DoubleSeq_get_reader_and_data_ptr
#define DDS_DOUBLE64Seq_set_reader_and_data_ptr DDS_DoubleSeq_set_reader_and_data_ptr
#define DDS_DOUBLE64Seq_has_ownership DDS_DoubleSeq_has_ownership
#define DDS_DOUBLE64Seq_clear DDS_DoubleSeq_clear
#define DDS_DOUBLE64Seq_finalize DDS_DoubleSeq_finalize
#define DDS_DOUBLE64Seq_initialize_ex DDS_DoubleSeq_initialize_ex

#endif //_ZRDDS_INCLUDE_601_TYPE


/* �û�ʹ�ýӿ� */

DCPSDLL ZR_BOOLEAN DDS_StringInnerCopyEx(
    DDS_String* dst,
    const DDS_Char** src,
    ZRMemPool* pool);

DCPSDLL ZR_INT32 DDS_StringCompare(
    const DDS_Char * const *first,
    const DDS_Char * const *second);

DCPSDLL ZR_BOOLEAN DDS_StringInitialize(
    DDS_String* self);

DCPSDLL ZR_BOOLEAN DDS_StringInitializeEx(
    DDS_String* self,
    ZRMemPool* pool,
    ZR_BOOLEAN allocateMemory);

DCPSDLL void DDS_StringFinalize(
    DDS_String* self);

DCPSDLL void DDS_StringFinalizeEx(
    DDS_String* self,
    ZRMemPool* pool,
    ZR_BOOLEAN deletePointers);

DCPSDLL ZR_BOOLEAN DDS_StringCopySample(
    DDS_String* dst,
    const DDS_String* src);

DCPSDLL ZR_BOOLEAN DDS_StringCopyEx(
    DDS_String* dst,
    const DDS_String* src,
    ZRMemPool* pool);

DCPSDLL void DDS_StringPrintData(
    const DDS_String* sample);

DCPSDLL TypeCodeHeader* DDS_StringGetTypeCode();

/* �ײ�ʹ�ú��� */
DCPSDLL DDS_String* DDS_StringCreateSample(
    ZRMemPool* pool,
    ZR_BOOLEAN allocMutable);

DCPSDLL void DDS_StringDestroySample(
    ZRMemPool* pool,
    DDS_String* sample);

DCPSDLL ZR_UINT32 DDS_StringGetSerializedSampleMaxSize();

DCPSDLL ZR_UINT32 DDS_StringGetSerializedSampleSize(
    const DDS_String* sample,
    ZR_UINT32 currentAlignment);

DCPSDLL ZR_INT32 DDS_StringSerialize(
    const DDS_String* sample,
    CDRSerializer* cdr);

DCPSDLL ZR_INT32 DDS_StringDeserialize(
    DDS_String* sample,
    CDRDeserializer* cdr,
    ZRMemPool* pool);

DCPSDLL ZR_UINT32 DDS_StringGetSerializedKeyMaxSize();

DCPSDLL ZR_UINT32 DDS_StringGetSerializedKeySize(
    const DDS_String* sample,
    ZR_UINT32 currentAlignment);

DCPSDLL ZR_INT32 DDS_StringSerializeKey(
    const DDS_String* sample,
    CDRSerializer* cdr);

DCPSDLL ZR_INT32 DDS_StringDeserializeKey(
    DDS_String* sample,
    CDRDeserializer* cdr,
    ZRMemPool* pool);

DCPSDLL ZR_INT32 DDS_StringGetKeyHash(
    const DDS_String* sample,
    CDRSerializer* cdr,
    DDS_KeyHash_t*  result);

DCPSDLL ZR_BOOLEAN DDS_StringHasKey();

DCPSDLL TypeCodeHeader* DDS_StringGetInnerTypeCode();

#ifdef _ZRDDS_INCLUDE_ONSITE_DESERILIZE

DCPSDLL ZR_BOOLEAN DDS_StringNoSerializingSupported(
    const void* typesupport);

DCPSDLL ZR_UINT32 DDS_StringFixedHeaderLength(
    const void* typesupport);

DCPSDLL ZR_INT32 DDS_StringOnSiteDeserialize(
    CDRDeserializer* cdr,
    void* sample,
    ZR_UINT32 offset,
    ZR_UINT32 totalSize,
    ZR_INT8* payload,
    ZR_UINT32 payloadLen,
    ZR_UINT32 fixedHeaderLen);

#endif //_ZRDDS_INCLUDE_ONSITE_DESERILIZE

#ifdef _ZRDDS_INCLUDE_NO_SERIALIZE_MODE

DCPSDLL ZR_INT8* DDS_StringLoanSampleBuf(
    void* sample,
    ZR_BOOLEAN takeBuffer,
    const void* typesupport);

DCPSDLL void DDS_StringReturnSampleBuf(
    ZR_INT8* sampleBuf,
    const void* typesupport);

DCPSDLL ZR_INT32 DDS_StringLoanDeserialize(
    void* sample,
    CDRDeserializer* cdr,
    ZR_UINT32 curIndex,
    ZR_UINT32 totalNum,
    ZR_INT8* base,
    ZR_UINT32 offset,
    ZR_UINT32 space,
    ZR_UINT32 fixedHeaderLen);

#endif //_ZRDDS_INCLUDE_NO_SERIALIZE_MODE

#ifdef _ZRDDS_INCLUDE_BUILTIN_TYPES

/* �û�ʹ�ýӿ� */
DCPSDLL ZR_BOOLEAN DDS_BooleanInitialize(
    DDS_Boolean* self);

DCPSDLL ZR_BOOLEAN DDS_BooleanInitializeEx(
    DDS_Boolean* self,
    ZRMemPool* pool,
    ZR_BOOLEAN allocateMemory);

DCPSDLL void DDS_BooleanFinalize(
    DDS_Boolean* self);

DCPSDLL void DDS_BooleanFinalizeEx(
    DDS_Boolean* self,
    ZRMemPool* pool,
    ZR_BOOLEAN deletePointers);

DCPSDLL ZR_BOOLEAN DDS_BooleanCopySample(
    DDS_Boolean* dst,
    const DDS_Boolean* src);

DCPSDLL ZR_BOOLEAN DDS_BooleanCopyEx(
    DDS_Boolean* dst,
    const DDS_Boolean* src,
    ZRMemPool* pool);

DCPSDLL void DDS_BooleanPrintData(
    const DDS_Boolean* sample);

DCPSDLL TypeCodeHeader* DDS_BooleanGetTypeCode();

/* �ײ�ʹ�ú��� */
DCPSDLL DDS_Boolean* DDS_BooleanCreateSample(
    ZRMemPool* pool,
    ZR_BOOLEAN allocMutable);

DCPSDLL void DDS_BooleanDestroySample(
    ZRMemPool* pool,
    DDS_Boolean* sample);

DCPSDLL ZR_UINT32 DDS_BooleanGetSerializedSampleMaxSize();

DCPSDLL ZR_UINT32 DDS_BooleanGetSerializedSampleSize(
    const DDS_Boolean* sample,
    ZR_UINT32 currentAlignment);

DCPSDLL ZR_INT32 DDS_BooleanSerialize(
    const DDS_Boolean* sample,
    CDRSerializer* cdr);

DCPSDLL ZR_INT32 DDS_BooleanDeserialize(
    DDS_Boolean* sample,
    CDRDeserializer* cdr,
    ZRMemPool* pool);

ZR_UINT32 DDS_BooleanGetSerializedKeyMaxSize();

DCPSDLL ZR_UINT32 DDS_BooleanGetSerializedKeySize(
    const DDS_Boolean* sample,
    ZR_UINT32 currentAlignment);

DCPSDLL ZR_INT32 DDS_BooleanSerializeKey(
    const DDS_Boolean* sample,
    CDRSerializer* cdr);

DCPSDLL ZR_INT32 DDS_BooleanDeserializeKey(
    DDS_Boolean* sample,
    CDRDeserializer* cdr,
    ZRMemPool* pool);

DCPSDLL ZR_INT32 DDS_BooleanGetKeyHash(
    const DDS_Boolean* sample,
    CDRSerializer* cdr,
    DDS_KeyHash_t*  result);

DCPSDLL ZR_BOOLEAN DDS_BooleanHasKey();

DCPSDLL TypeCodeHeader* DDS_BooleanGetInnerTypeCode();

#ifdef _ZRDDS_INCLUDE_ONSITE_DESERILIZE

DCPSDLL ZR_BOOLEAN DDS_BooleanNoSerializingSupported(
    const void* typesupport);

DCPSDLL ZR_UINT32 DDS_BooleanFixedHeaderLength(
    const void* typesupport);

DCPSDLL ZR_INT32 DDS_BooleanOnSiteDeserialize(
    CDRDeserializer* cdr,
    void* sample,
    ZR_UINT32 offset,
    ZR_UINT32 totalSize,
    ZR_INT8* payload,
    ZR_UINT32 payloadLen,
    ZR_UINT32 fixedHeaderLen);

#endif //_ZRDDS_INCLUDE_ONSITE_DESERILIZE

#ifdef _ZRDDS_INCLUDE_NO_SERIALIZE_MODE

DCPSDLL ZR_INT8* DDS_BooleanLoanSampleBuf(
    void* sample,
    ZR_BOOLEAN takeBuffer,
    const void* typesupport);

DCPSDLL void DDS_BooleanReturnSampleBuf(
    ZR_INT8* sampleBuf,
    const void* typesupport);

DCPSDLL ZR_INT32 DDS_BooleanLoanDeserialize(
    void* sample,
    CDRDeserializer* cdr,
    ZR_UINT32 curIndex,
    ZR_UINT32 totalNum,
    ZR_INT8* base,
    ZR_UINT32 offset,
    ZR_UINT32 space,
    ZR_UINT32 fixedHeaderLen);

#endif //_ZRDDS_INCLUDE_NO_SERIALIZE_MODE

/* �û�ʹ�ýӿ� */
DCPSDLL ZR_BOOLEAN DDS_OctetInitialize(
    DDS_Octet* self);

DCPSDLL ZR_BOOLEAN DDS_OctetInitializeEx(
    DDS_Octet* self,
    ZRMemPool* pool,
    ZR_BOOLEAN allocateMemory);

DCPSDLL void DDS_OctetFinalize(
    DDS_Octet* self);

DCPSDLL void DDS_OctetFinalizeEx(
    DDS_Octet* self,
    ZRMemPool* pool,
    ZR_BOOLEAN deletePointers);

DCPSDLL ZR_BOOLEAN DDS_OctetCopySample(
    DDS_Octet* dst,
    const DDS_Octet* src);

DCPSDLL ZR_BOOLEAN DDS_OctetCopyEx(
    DDS_Octet* dst,
    const DDS_Octet* src,
    ZRMemPool* pool);

DCPSDLL void DDS_OctetPrintData(
    const DDS_Octet* sample);

DCPSDLL TypeCodeHeader* DDS_OctetGetTypeCode();

/* �ײ�ʹ�ú��� */
DCPSDLL DDS_Octet* DDS_OctetCreateSample(
    ZRMemPool* pool,
    ZR_BOOLEAN allocMutable);

DCPSDLL void DDS_OctetDestroySample(
    ZRMemPool* pool,
    DDS_Octet* sample);

DCPSDLL ZR_UINT32 DDS_OctetGetSerializedSampleMaxSize();

DCPSDLL ZR_UINT32 DDS_OctetGetSerializedSampleSize(
    const DDS_Octet* sample,
    ZR_UINT32 currentAlignment);

DCPSDLL ZR_INT32 DDS_OctetSerialize(
    const DDS_Octet* sample,
    CDRSerializer* cdr);

DCPSDLL ZR_INT32 DDS_OctetDeserialize(
    DDS_Octet* sample,
    CDRDeserializer* cdr,
    ZRMemPool* pool);

DCPSDLL ZR_UINT32 DDS_OctetGetSerializedKeyMaxSize();

DCPSDLL ZR_UINT32 DDS_OctetGetSerializedKeySize(
    const DDS_Octet* sample,
    ZR_UINT32 currentAlignment);

DCPSDLL ZR_INT32 DDS_OctetSerializeKey(
    const DDS_Octet* sample,
    CDRSerializer* cdr);

DCPSDLL ZR_INT32 DDS_OctetDeserializeKey(
    DDS_Octet* sample,
    CDRDeserializer* cdr,
    ZRMemPool* pool);

DCPSDLL ZR_INT32 DDS_OctetGetKeyHash(
    const DDS_Octet* sample,
    CDRSerializer* cdr,
    DDS_KeyHash_t*  result);

DCPSDLL ZR_BOOLEAN DDS_OctetHasKey();

DCPSDLL TypeCodeHeader* DDS_OctetGetInnerTypeCode();

#ifdef _ZRDDS_INCLUDE_ONSITE_DESERILIZE

DCPSDLL ZR_BOOLEAN DDS_OctetNoSerializingSupported(
    const void* typesupport);

DCPSDLL ZR_UINT32 DDS_OctetFixedHeaderLength(
    const void* typesupport);

DCPSDLL ZR_INT32 DDS_OctetOnSiteDeserialize(
    CDRDeserializer* cdr,
    void* sample,
    ZR_UINT32 offset,
    ZR_UINT32 totalSize,
    ZR_INT8* payload,
    ZR_UINT32 payloadLen,
    ZR_UINT32 fixedHeaderLen);

#endif //_ZRDDS_INCLUDE_ONSITE_DESERILIZE

#ifdef _ZRDDS_INCLUDE_NO_SERIALIZE_MODE

DCPSDLL ZR_INT8* DDS_OctetLoanSampleBuf(
    void* sample,
    ZR_BOOLEAN takeBuffer,
    const void* typesupport);

DCPSDLL void DDS_OctetReturnSampleBuf(
    ZR_INT8* sampleBuf,
    const void* typesupport);

DCPSDLL ZR_INT32 DDS_OctetLoanDeserialize(
    void* sample,
    CDRDeserializer* cdr,
    ZR_UINT32 curIndex,
    ZR_UINT32 totalNum,
    ZR_INT8* base,
    ZR_UINT32 offset,
    ZR_UINT32 space,
    ZR_UINT32 fixedHeaderLen);

#endif //_ZRDDS_INCLUDE_NO_SERIALIZE_MODE

/* �û�ʹ�ýӿ� */
DCPSDLL ZR_BOOLEAN DDS_CharInitialize(
    DDS_Char* self);

DCPSDLL ZR_BOOLEAN DDS_CharInitializeEx(
    DDS_Char* self,
    ZRMemPool* pool,
    ZR_BOOLEAN allocateMemory);

DCPSDLL void DDS_CharFinalize(
    DDS_Char* self);

DCPSDLL void DDS_CharFinalizeEx(
    DDS_Char* self,
    ZRMemPool* pool,
    ZR_BOOLEAN deletePointers);

DCPSDLL ZR_BOOLEAN DDS_CharCopySample(
    DDS_Char* dst,
    const DDS_Char* src);

DCPSDLL ZR_BOOLEAN DDS_CharCopyEx(
    DDS_Char* dst,
    const DDS_Char* src,
    ZRMemPool* pool);

DCPSDLL void DDS_CharPrintData(
    const DDS_Char* sample);

DCPSDLL TypeCodeHeader* DDS_CharGetTypeCode();

/* �ײ�ʹ�ú��� */
DCPSDLL DDS_Char* DDS_CharCreateSample(
    ZRMemPool* pool,
    ZR_BOOLEAN allocMutable);

DCPSDLL void DDS_CharDestroySample(
    ZRMemPool* pool,
    DDS_Char* sample);

DCPSDLL ZR_UINT32 DDS_CharGetSerializedSampleMaxSize();

DCPSDLL ZR_UINT32 DDS_CharGetSerializedSampleSize(
    const DDS_Char* sample,
    ZR_UINT32 currentAlignment);

DCPSDLL ZR_INT32 DDS_CharSerialize(
    const DDS_Char* sample,
    CDRSerializer* cdr);

DCPSDLL ZR_INT32 DDS_CharDeserialize(
    DDS_Char* sample,
    CDRDeserializer* cdr,
    ZRMemPool* pool);

DCPSDLL ZR_UINT32 DDS_CharGetSerializedKeyMaxSize();

DCPSDLL ZR_UINT32 DDS_CharGetSerializedKeySize(
    const DDS_Char* sample,
    ZR_UINT32 currentAlignment);

DCPSDLL ZR_INT32 DDS_CharSerializeKey(
    const DDS_Char* sample,
    CDRSerializer* cdr);

DCPSDLL ZR_INT32 DDS_CharDeserializeKey(
    DDS_Char* sample,
    CDRDeserializer* cdr,
    ZRMemPool* pool);

DCPSDLL ZR_INT32 DDS_CharGetKeyHash(
    const DDS_Char* sample,
    CDRSerializer* cdr,
    DDS_KeyHash_t*  result);

DCPSDLL ZR_BOOLEAN DDS_CharHasKey();

DCPSDLL TypeCodeHeader* DDS_CharGetInnerTypeCode();

#ifdef _ZRDDS_INCLUDE_ONSITE_DESERILIZE

DCPSDLL ZR_BOOLEAN DDS_CharNoSerializingSupported(
    const void* typesupport);

DCPSDLL ZR_UINT32 DDS_CharFixedHeaderLength(
    const void* typesupport);

DCPSDLL ZR_INT32 DDS_CharOnSiteDeserialize(
    CDRDeserializer* cdr,
    void* sample,
    ZR_UINT32 offset,
    ZR_UINT32 totalSize,
    ZR_INT8* payload,
    ZR_UINT32 payloadLen,
    ZR_UINT32 fixedHeaderLen);

#endif //_ZRDDS_INCLUDE_ONSITE_DESERILIZE

#ifdef _ZRDDS_INCLUDE_NO_SERIALIZE_MODE

DCPSDLL ZR_INT8* DDS_CharLoanSampleBuf(
    void* sample,
    ZR_BOOLEAN takeBuffer,
    const void* typesupport);

DCPSDLL void DDS_CharReturnSampleBuf(
    ZR_INT8* sampleBuf,
    const void* typesupport);

DCPSDLL ZR_INT32 DDS_CharLoanDeserialize(
    void* sample,
    CDRDeserializer* cdr,
    ZR_UINT32 curIndex,
    ZR_UINT32 totalNum,
    ZR_INT8* base,
    ZR_UINT32 offset,
    ZR_UINT32 space,
    ZR_UINT32 fixedHeaderLen);

#endif //_ZRDDS_INCLUDE_NO_SERIALIZE_MODE

/* �û�ʹ�ýӿ� */
DCPSDLL ZR_BOOLEAN DDS_ShortInitialize(
    DDS_Short* self);

DCPSDLL ZR_BOOLEAN DDS_ShortInitializeEx(
    DDS_Short* self,
    ZRMemPool* pool,
    ZR_BOOLEAN allocateMemory);

DCPSDLL void DDS_ShortFinalize(
    DDS_Short* self);

DCPSDLL void DDS_ShortFinalizeEx(
    DDS_Short* self,
    ZRMemPool* pool,
    ZR_BOOLEAN deletePointers);

DCPSDLL ZR_BOOLEAN DDS_ShortCopySample(
    DDS_Short* dst,
    const DDS_Short* src);

DCPSDLL ZR_BOOLEAN DDS_ShortCopyEx(
    DDS_Short* dst,
    const DDS_Short* src,
    ZRMemPool* pool);

DCPSDLL void DDS_ShortPrintData(
    const DDS_Short* sample);

DCPSDLL TypeCodeHeader* DDS_ShortGetTypeCode();

/* �ײ�ʹ�ú��� */
DCPSDLL DDS_Short* DDS_ShortCreateSample(
    ZRMemPool* pool,
    ZR_BOOLEAN allocMutable);

DCPSDLL void DDS_ShortDestroySample(
    ZRMemPool* pool,
    DDS_Short* sample);

DCPSDLL ZR_UINT32 DDS_ShortGetSerializedSampleMaxSize();

DCPSDLL ZR_UINT32 DDS_ShortGetSerializedSampleSize(
    const DDS_Short* sample,
    ZR_UINT32 currentAlignment);

DCPSDLL ZR_INT32 DDS_ShortSerialize(
    const DDS_Short* sample,
    CDRSerializer* cdr);

DCPSDLL ZR_INT32 DDS_ShortDeserialize(
    DDS_Short* sample,
    CDRDeserializer* cdr,
    ZRMemPool* pool);

DCPSDLL ZR_UINT32 DDS_ShortGetSerializedKeyMaxSize();

DCPSDLL ZR_UINT32 DDS_ShortGetSerializedKeySize(
    const DDS_Short* sample,
    ZR_UINT32 currentAlignment);

DCPSDLL ZR_INT32 DDS_ShortSerializeKey(
    const DDS_Short* sample,
    CDRSerializer* cdr);

DCPSDLL ZR_INT32 DDS_ShortDeserializeKey(
    DDS_Short* sample,
    CDRDeserializer* cdr,
    ZRMemPool* pool);

DCPSDLL ZR_INT32 DDS_ShortGetKeyHash(
    const DDS_Short* sample,
    CDRSerializer* cdr,
    DDS_KeyHash_t*  result);

DCPSDLL ZR_BOOLEAN DDS_ShortHasKey();

DCPSDLL TypeCodeHeader* DDS_ShortGetInnerTypeCode();

#ifdef _ZRDDS_INCLUDE_ONSITE_DESERILIZE

DCPSDLL ZR_BOOLEAN DDS_ShortNoSerializingSupported(
    const void* typesupport);

DCPSDLL ZR_UINT32 DDS_ShortFixedHeaderLength(
    const void* typesupport);

DCPSDLL ZR_INT32 DDS_ShortOnSiteDeserialize(
    CDRDeserializer* cdr,
    void* sample,
    ZR_UINT32 offset,
    ZR_UINT32 totalSize,
    ZR_INT8* payload,
    ZR_UINT32 payloadLen,
    ZR_UINT32 fixedHeaderLen);

#endif //_ZRDDS_INCLUDE_ONSITE_DESERILIZE

#ifdef _ZRDDS_INCLUDE_NO_SERIALIZE_MODE

DCPSDLL ZR_INT8* DDS_ShortLoanSampleBuf(
    void* sample,
    ZR_BOOLEAN takeBuffer,
    const void* typesupport);

DCPSDLL void DDS_ShortReturnSampleBuf(
    ZR_INT8* sampleBuf,
    const void* typesupport);

DCPSDLL ZR_INT32 DDS_ShortLoanDeserialize(
    void* sample,
    CDRDeserializer* cdr,
    ZR_UINT32 curIndex,
    ZR_UINT32 totalNum,
    ZR_INT8* base,
    ZR_UINT32 offset,
    ZR_UINT32 space,
    ZR_UINT32 fixedHeaderLen);

#endif //_ZRDDS_INCLUDE_NO_SERIALIZE_MODE

/* �û�ʹ�ýӿ� */
DCPSDLL ZR_BOOLEAN DDS_UShortInitialize(
    DDS_UShort* self);

DCPSDLL ZR_BOOLEAN DDS_UShortInitializeEx(
    DDS_UShort* self,
    ZRMemPool* pool,
    ZR_BOOLEAN allocateMemory);

DCPSDLL void DDS_UShortFinalize(
    DDS_UShort* self);

DCPSDLL void DDS_UShortFinalizeEx(
    DDS_UShort* self,
    ZRMemPool* pool,
    ZR_BOOLEAN deletePointers);

DCPSDLL ZR_BOOLEAN DDS_UShortCopySample(
    DDS_UShort* dst,
    const DDS_UShort* src);

DCPSDLL ZR_BOOLEAN DDS_UShortCopyEx(
    DDS_UShort* dst,
    const DDS_UShort* src,
    ZRMemPool* pool);

DCPSDLL void DDS_UShortPrintData(
    const DDS_UShort* sample);

DCPSDLL TypeCodeHeader* DDS_UShortGetTypeCode();

/* �ײ�ʹ�ú��� */
DCPSDLL DDS_UShort* DDS_UShortCreateSample(
    ZRMemPool* pool,
    ZR_BOOLEAN allocMutable);

DCPSDLL void DDS_UShortDestroySample(
    ZRMemPool* pool,
    DDS_UShort* sample);

DCPSDLL ZR_UINT32 DDS_UShortGetSerializedSampleMaxSize();

DCPSDLL ZR_UINT32 DDS_UShortGetSerializedSampleSize(
    const DDS_UShort* sample,
    ZR_UINT32 currentAlignment);

DCPSDLL ZR_INT32 DDS_UShortSerialize(
    const DDS_UShort* sample,
    CDRSerializer* cdr);

DCPSDLL ZR_INT32 DDS_UShortDeserialize(
    DDS_UShort* sample,
    CDRDeserializer* cdr,
    ZRMemPool* pool);

DCPSDLL ZR_UINT32 DDS_UShortGetSerializedKeyMaxSize();

DCPSDLL ZR_UINT32 DDS_UShortGetSerializedKeySize(
    const DDS_UShort* sample,
    ZR_UINT32 currentAlignment);

DCPSDLL ZR_INT32 DDS_UShortSerializeKey(
    const DDS_UShort* sample,
    CDRSerializer* cdr);

DCPSDLL ZR_INT32 DDS_UShortDeserializeKey(
    DDS_UShort* sample,
    CDRDeserializer* cdr,
    ZRMemPool* pool);

DCPSDLL ZR_INT32 DDS_UShortGetKeyHash(
    const DDS_UShort* sample,
    CDRSerializer* cdr,
    DDS_KeyHash_t*  result);

DCPSDLL ZR_BOOLEAN DDS_UShortHasKey();

DCPSDLL TypeCodeHeader* DDS_UShortGetInnerTypeCode();

#ifdef _ZRDDS_INCLUDE_ONSITE_DESERILIZE

DCPSDLL ZR_BOOLEAN DDS_UShortNoSerializingSupported(
    const void* typesupport);

DCPSDLL ZR_UINT32 DDS_UShortFixedHeaderLength(
    const void* typesupport);

DCPSDLL ZR_INT32 DDS_UShortOnSiteDeserialize(
    CDRDeserializer* cdr,
    void* sample,
    ZR_UINT32 offset,
    ZR_UINT32 totalSize,
    ZR_INT8* payload,
    ZR_UINT32 payloadLen,
    ZR_UINT32 fixedHeaderLen);

#endif //_ZRDDS_INCLUDE_ONSITE_DESERILIZE

#ifdef _ZRDDS_INCLUDE_NO_SERIALIZE_MODE

DCPSDLL ZR_INT8* DDS_UShortLoanSampleBuf(
    void* sample,
    ZR_BOOLEAN takeBuffer,
    const void* typesupport);

DCPSDLL void DDS_UShortReturnSampleBuf(
    ZR_INT8* sampleBuf,
    const void* typesupport);

DCPSDLL ZR_INT32 DDS_UShortLoanDeserialize(
    void* sample,
    CDRDeserializer* cdr,
    ZR_UINT32 curIndex,
    ZR_UINT32 totalNum,
    ZR_INT8* base,
    ZR_UINT32 offset,
    ZR_UINT32 space,
    ZR_UINT32 fixedHeaderLen);

#endif //_ZRDDS_INCLUDE_NO_SERIALIZE_MODE

/* �û�ʹ�ýӿ� */
DCPSDLL ZR_BOOLEAN DDS_LongInitialize(
    DDS_Long* self);

DCPSDLL ZR_BOOLEAN DDS_LongInitializeEx(
    DDS_Long* self,
    ZRMemPool* pool,
    ZR_BOOLEAN allocateMemory);

DCPSDLL void DDS_LongFinalize(
    DDS_Long* self);

DCPSDLL void DDS_LongFinalizeEx(
    DDS_Long* self,
    ZRMemPool* pool,
    ZR_BOOLEAN deletePointers);

DCPSDLL ZR_BOOLEAN DDS_LongCopySample(
    DDS_Long* dst,
    const DDS_Long* src);

DCPSDLL ZR_BOOLEAN DDS_LongCopyEx(
    DDS_Long* dst,
    const DDS_Long* src,
    ZRMemPool* pool);

DCPSDLL void DDS_LongPrintData(
    const DDS_Long* sample);

DCPSDLL TypeCodeHeader* DDS_LongGetTypeCode();

/* �ײ�ʹ�ú��� */
DCPSDLL DDS_Long* DDS_LongCreateSample(
    ZRMemPool* pool,
    ZR_BOOLEAN allocMutable);

DCPSDLL void DDS_LongDestroySample(
    ZRMemPool* pool,
    DDS_Long* sample);

DCPSDLL ZR_UINT32 DDS_LongGetSerializedSampleMaxSize();

DCPSDLL ZR_UINT32 DDS_LongGetSerializedSampleSize(
    const DDS_Long* sample,
    ZR_UINT32 currentAlignment);

DCPSDLL ZR_INT32 DDS_LongSerialize(
    const DDS_Long* sample,
    CDRSerializer* cdr);

DCPSDLL ZR_INT32 DDS_LongDeserialize(
    DDS_Long* sample,
    CDRDeserializer* cdr,
    ZRMemPool* pool);

DCPSDLL ZR_UINT32 DDS_LongGetSerializedKeyMaxSize();

DCPSDLL ZR_UINT32 DDS_LongGetSerializedKeySize(
    const DDS_Long* sample,
    ZR_UINT32 currentAlignment);

DCPSDLL ZR_INT32 DDS_LongSerializeKey(
    const DDS_Long* sample,
    CDRSerializer* cdr);

DCPSDLL ZR_INT32 DDS_LongDeserializeKey(
    DDS_Long* sample,
    CDRDeserializer* cdr,
    ZRMemPool* pool);

DCPSDLL ZR_INT32 DDS_LongGetKeyHash(
    const DDS_Long* sample,
    CDRSerializer* cdr,
    DDS_KeyHash_t*  result);

DCPSDLL ZR_BOOLEAN DDS_LongHasKey();

DCPSDLL TypeCodeHeader* DDS_LongGetInnerTypeCode();

#ifdef _ZRDDS_INCLUDE_ONSITE_DESERILIZE

DCPSDLL ZR_BOOLEAN DDS_LongNoSerializingSupported(
    const void* typesupport);

DCPSDLL ZR_UINT32 DDS_LongFixedHeaderLength(
    const void* typesupport);

DCPSDLL ZR_INT32 DDS_LongOnSiteDeserialize(
    CDRDeserializer* cdr,
    void* sample,
    ZR_UINT32 offset,
    ZR_UINT32 totalSize,
    ZR_INT8* payload,
    ZR_UINT32 payloadLen,
    ZR_UINT32 fixedHeaderLen);

#endif //_ZRDDS_INCLUDE_ONSITE_DESERILIZE

#ifdef _ZRDDS_INCLUDE_NO_SERIALIZE_MODE

DCPSDLL ZR_INT8* DDS_LongLoanSampleBuf(
    void* sample,
    ZR_BOOLEAN takeBuffer,
    const void* typesupport);

DCPSDLL void DDS_LongReturnSampleBuf(
    ZR_INT8* sampleBuf,
    const void* typesupport);

DCPSDLL ZR_INT32 DDS_LongLoanDeserialize(
    void* sample,
    CDRDeserializer* cdr,
    ZR_UINT32 curIndex,
    ZR_UINT32 totalNum,
    ZR_INT8* base,
    ZR_UINT32 offset,
    ZR_UINT32 space,
    ZR_UINT32 fixedHeaderLen);

#endif //_ZRDDS_INCLUDE_NO_SERIALIZE_MODE

/* �û�ʹ�ýӿ� */
DCPSDLL ZR_BOOLEAN DDS_ULongInitialize(
    DDS_ULong* self);

DCPSDLL ZR_BOOLEAN DDS_ULongInitializeEx(
    DDS_ULong* self,
    ZRMemPool* pool,
    ZR_BOOLEAN allocateMemory);

DCPSDLL void DDS_ULongFinalize(
    DDS_ULong* self);

DCPSDLL void DDS_ULongFinalizeEx(
    DDS_ULong* self,
    ZRMemPool* pool,
    ZR_BOOLEAN deletePointers);

DCPSDLL ZR_BOOLEAN DDS_ULongCopySample(
    DDS_ULong* dst,
    const DDS_ULong* src);

DCPSDLL ZR_BOOLEAN DDS_ULongCopyEx(
    DDS_ULong* dst,
    const DDS_ULong* src,
    ZRMemPool* pool);

DCPSDLL void DDS_ULongPrintData(
    const DDS_ULong* sample);

DCPSDLL TypeCodeHeader* DDS_ULongGetTypeCode();

/* �ײ�ʹ�ú��� */
DCPSDLL DDS_ULong* DDS_ULongCreateSample(
    ZRMemPool* pool,
    ZR_BOOLEAN allocMutable);

DCPSDLL void DDS_ULongDestroySample(
    ZRMemPool* pool,
    DDS_ULong* sample);

DCPSDLL ZR_UINT32 DDS_ULongGetSerializedSampleMaxSize();

DCPSDLL ZR_UINT32 DDS_ULongGetSerializedSampleSize(
    const DDS_ULong* sample,
    ZR_UINT32 currentAlignment);

DCPSDLL ZR_INT32 DDS_ULongSerialize(
    const DDS_ULong* sample,
    CDRSerializer* cdr);

DCPSDLL ZR_INT32 DDS_ULongDeserialize(
    DDS_ULong* sample,
    CDRDeserializer* cdr,
    ZRMemPool* pool);

DCPSDLL ZR_UINT32 DDS_ULongGetSerializedKeyMaxSize();

DCPSDLL ZR_UINT32 DDS_ULongGetSerializedKeySize(
    const DDS_ULong* sample,
    ZR_UINT32 currentAlignment);

DCPSDLL ZR_INT32 DDS_ULongSerializeKey(
    const DDS_ULong* sample,
    CDRSerializer* cdr);

DCPSDLL ZR_INT32 DDS_ULongDeserializeKey(
    DDS_ULong* sample,
    CDRDeserializer* cdr,
    ZRMemPool* pool);

DCPSDLL ZR_INT32 DDS_ULongGetKeyHash(
    const DDS_ULong* sample,
    CDRSerializer* cdr,
    DDS_KeyHash_t*  result);

DCPSDLL ZR_BOOLEAN DDS_ULongHasKey();

DCPSDLL TypeCodeHeader* DDS_ULongGetInnerTypeCode();

#ifdef _ZRDDS_INCLUDE_ONSITE_DESERILIZE

DCPSDLL ZR_BOOLEAN DDS_ULongNoSerializingSupported(
    const void* typesupport);

DCPSDLL ZR_UINT32 DDS_ULongFixedHeaderLength(
    const void* typesupport);

DCPSDLL ZR_INT32 DDS_ULongOnSiteDeserialize(
    CDRDeserializer* cdr,
    void* sample,
    ZR_UINT32 offset,
    ZR_UINT32 totalSize,
    ZR_INT8* payload,
    ZR_UINT32 payloadLen,
    ZR_UINT32 fixedHeaderLen);

#endif //_ZRDDS_INCLUDE_ONSITE_DESERILIZE

#ifdef _ZRDDS_INCLUDE_NO_SERIALIZE_MODE

DCPSDLL ZR_INT8* DDS_ULongLoanSampleBuf(
    void* sample,
    ZR_BOOLEAN takeBuffer,
    const void* typesupport);

DCPSDLL void DDS_ULongReturnSampleBuf(
    ZR_INT8* sampleBuf,
    const void* typesupport);

DCPSDLL ZR_INT32 DDS_ULongLoanDeserialize(
    void* sample,
    CDRDeserializer* cdr,
    ZR_UINT32 curIndex,
    ZR_UINT32 totalNum,
    ZR_INT8* base,
    ZR_UINT32 offset,
    ZR_UINT32 space,
    ZR_UINT32 fixedHeaderLen);

#endif //_ZRDDS_INCLUDE_NO_SERIALIZE_MODE

/* �û�ʹ�ýӿ� */
DCPSDLL ZR_BOOLEAN DDS_LongLongInitialize(
    DDS_LongLong* self);

DCPSDLL ZR_BOOLEAN DDS_LongLongInitializeEx(
    DDS_LongLong* self,
    ZRMemPool* pool,
    ZR_BOOLEAN allocateMemory);

DCPSDLL void DDS_LongLongFinalize(
    DDS_LongLong* self);

DCPSDLL void DDS_LongLongFinalizeEx(
    DDS_LongLong* self,
    ZRMemPool* pool,
    ZR_BOOLEAN deletePointers);

DCPSDLL ZR_BOOLEAN DDS_LongLongCopySample(
    DDS_LongLong* dst,
    const DDS_LongLong* src);

DCPSDLL ZR_BOOLEAN DDS_LongLongCopyEx(
    DDS_LongLong* dst,
    const DDS_LongLong* src,
    ZRMemPool* pool);

DCPSDLL void DDS_LongLongPrintData(
    const DDS_LongLong* sample);

DCPSDLL TypeCodeHeader* DDS_LongLongGetTypeCode();

/* �ײ�ʹ�ú��� */
DCPSDLL DDS_LongLong* DDS_LongLongCreateSample(
    ZRMemPool* pool,
    ZR_BOOLEAN allocMutable);

DCPSDLL void DDS_LongLongDestroySample(
    ZRMemPool* pool,
    DDS_LongLong* sample);

DCPSDLL ZR_UINT32 DDS_LongLongGetSerializedSampleMaxSize();

DCPSDLL ZR_UINT32 DDS_LongLongGetSerializedSampleSize(
    const DDS_LongLong* sample,
    ZR_UINT32 currentAlignment);

DCPSDLL ZR_INT32 DDS_LongLongSerialize(
    const DDS_LongLong* sample,
    CDRSerializer* cdr);

DCPSDLL ZR_INT32 DDS_LongLongDeserialize(
    DDS_LongLong* sample,
    CDRDeserializer* cdr,
    ZRMemPool* pool);

DCPSDLL ZR_UINT32 DDS_LongLongGetSerializedKeyMaxSize();

DCPSDLL ZR_UINT32 DDS_LongLongGetSerializedKeySize(
    const DDS_LongLong* sample,
    ZR_UINT32 currentAlignment);

DCPSDLL ZR_INT32 DDS_LongLongSerializeKey(
    const DDS_LongLong* sample,
    CDRSerializer* cdr);

DCPSDLL ZR_INT32 DDS_LongLongDeserializeKey(
    DDS_LongLong* sample,
    CDRDeserializer* cdr,
    ZRMemPool* pool);

DCPSDLL ZR_INT32 DDS_LongLongGetKeyHash(
    const DDS_LongLong* sample,
    CDRSerializer* cdr,
    DDS_KeyHash_t*  result);

DCPSDLL ZR_BOOLEAN DDS_LongLongHasKey();

DCPSDLL TypeCodeHeader* DDS_LongLongGetInnerTypeCode();

#ifdef _ZRDDS_INCLUDE_ONSITE_DESERILIZE

DCPSDLL ZR_BOOLEAN DDS_LongLongNoSerializingSupported(
    const void* typesupport);

DCPSDLL ZR_UINT32 DDS_LongLongFixedHeaderLength(
    const void* typesupport);

DCPSDLL ZR_INT32 DDS_LongLongOnSiteDeserialize(
    CDRDeserializer* cdr,
    void* sample,
    ZR_UINT32 offset,
    ZR_UINT32 totalSize,
    ZR_INT8* payload,
    ZR_UINT32 payloadLen,
    ZR_UINT32 fixedHeaderLen);

#endif //_ZRDDS_INCLUDE_ONSITE_DESERILIZE

#ifdef _ZRDDS_INCLUDE_NO_SERIALIZE_MODE

DCPSDLL ZR_INT8* DDS_LongLongLoanSampleBuf(
    void* sample,
    ZR_BOOLEAN takeBuffer,
    const void* typesupport);

DCPSDLL void DDS_LongLongReturnSampleBuf(
    ZR_INT8* sampleBuf,
    const void* typesupport);

DCPSDLL ZR_INT32 DDS_LongLongLoanDeserialize(
    void* sample,
    CDRDeserializer* cdr,
    ZR_UINT32 curIndex,
    ZR_UINT32 totalNum,
    ZR_INT8* base,
    ZR_UINT32 offset,
    ZR_UINT32 space,
    ZR_UINT32 fixedHeaderLen);

#endif //_ZRDDS_INCLUDE_NO_SERIALIZE_MODE

/* �û�ʹ�ýӿ� */
DCPSDLL ZR_BOOLEAN DDS_ULongLongInitialize(
    DDS_ULongLong* self);

DCPSDLL ZR_BOOLEAN DDS_ULongLongInitializeEx(
    DDS_ULongLong* self,
    ZRMemPool* pool,
    ZR_BOOLEAN allocateMemory);

DCPSDLL void DDS_ULongLongFinalize(
    DDS_ULongLong* self);

DCPSDLL void DDS_ULongLongFinalizeEx(
    DDS_ULongLong* self,
    ZRMemPool* pool,
    ZR_BOOLEAN deletePointers);

DCPSDLL ZR_BOOLEAN DDS_ULongLongCopySample(
    DDS_ULongLong* dst,
    const DDS_ULongLong* src);

DCPSDLL ZR_BOOLEAN DDS_ULongLongCopyEx(
    DDS_ULongLong* dst,
    const DDS_ULongLong* src,
    ZRMemPool* pool);

DCPSDLL void DDS_ULongLongPrintData(
    const DDS_ULongLong* sample);

DCPSDLL TypeCodeHeader* DDS_ULongLongGetTypeCode();

/* �ײ�ʹ�ú��� */
DCPSDLL DDS_ULongLong* DDS_ULongLongCreateSample(
    ZRMemPool* pool,
    ZR_BOOLEAN allocMutable);

DCPSDLL void DDS_ULongLongDestroySample(
    ZRMemPool* pool,
    DDS_ULongLong* sample);

DCPSDLL ZR_UINT32 DDS_ULongLongGetSerializedSampleMaxSize();

DCPSDLL ZR_UINT32 DDS_ULongLongGetSerializedSampleSize(
    const DDS_ULongLong* sample,
    ZR_UINT32 currentAlignment);

DCPSDLL ZR_INT32 DDS_ULongLongSerialize(
    const DDS_ULongLong* sample,
    CDRSerializer* cdr);

DCPSDLL ZR_INT32 DDS_ULongLongDeserialize(
    DDS_ULongLong* sample,
    CDRDeserializer* cdr,
    ZRMemPool* pool);

DCPSDLL ZR_UINT32 DDS_ULongLongGetSerializedKeyMaxSize();

DCPSDLL ZR_UINT32 DDS_ULongLongGetSerializedKeySize(
    const DDS_ULongLong* sample,
    ZR_UINT32 currentAlignment);

DCPSDLL ZR_INT32 DDS_ULongLongSerializeKey(
    const DDS_ULongLong* sample,
    CDRSerializer* cdr);

DCPSDLL ZR_INT32 DDS_ULongLongDeserializeKey(
    DDS_ULongLong* sample,
    CDRDeserializer* cdr,
    ZRMemPool* pool);

DCPSDLL ZR_INT32 DDS_ULongLongGetKeyHash(
    const DDS_ULongLong* sample,
    CDRSerializer* cdr,
    DDS_KeyHash_t*  result);

DCPSDLL ZR_BOOLEAN DDS_ULongLongHasKey();

DCPSDLL TypeCodeHeader* DDS_ULongLongGetInnerTypeCode();

#ifdef _ZRDDS_INCLUDE_ONSITE_DESERILIZE

DCPSDLL ZR_BOOLEAN DDS_ULongLongNoSerializingSupported(
    const void* typesupport);

DCPSDLL ZR_UINT32 DDS_ULongLongFixedHeaderLength(
    const void* typesupport);

DCPSDLL ZR_INT32 DDS_ULongLongOnSiteDeserialize(
    CDRDeserializer* cdr,
    void* sample,
    ZR_UINT32 offset,
    ZR_UINT32 totalSize,
    ZR_INT8* payload,
    ZR_UINT32 payloadLen,
    ZR_UINT32 fixedHeaderLen);

#endif //_ZRDDS_INCLUDE_ONSITE_DESERILIZE

#ifdef _ZRDDS_INCLUDE_NO_SERIALIZE_MODE

DCPSDLL ZR_INT8* DDS_ULongLongLoanSampleBuf(
    void* sample,
    ZR_BOOLEAN takeBuffer,
    const void* typesupport);

DCPSDLL void DDS_ULongLongReturnSampleBuf(
    ZR_INT8* sampleBuf,
    const void* typesupport);

DCPSDLL ZR_INT32 DDS_ULongLongLoanDeserialize(
    void* sample,
    CDRDeserializer* cdr,
    ZR_UINT32 curIndex,
    ZR_UINT32 totalNum,
    ZR_INT8* base,
    ZR_UINT32 offset,
    ZR_UINT32 space,
    ZR_UINT32 fixedHeaderLen);

#endif //_ZRDDS_INCLUDE_NO_SERIALIZE_MODE

/* �û�ʹ�ýӿ� */
DCPSDLL ZR_BOOLEAN DDS_FloatInitialize(
    DDS_Float* self);

DCPSDLL ZR_BOOLEAN DDS_FloatInitializeEx(
    DDS_Float* self,
    ZRMemPool* pool,
    ZR_BOOLEAN allocateMemory);

DCPSDLL void DDS_FloatFinalize(
    DDS_Float* self);

DCPSDLL void DDS_FloatFinalizeEx(
    DDS_Float* self,
    ZRMemPool* pool,
    ZR_BOOLEAN deletePointers);

DCPSDLL ZR_BOOLEAN DDS_FloatCopySample(
    DDS_Float* dst,
    const DDS_Float* src);

DCPSDLL ZR_BOOLEAN DDS_FloatCopyEx(
    DDS_Float* dst,
    const DDS_Float* src,
    ZRMemPool* pool);

DCPSDLL void DDS_FloatPrintData(
    const DDS_Float* sample);

DCPSDLL TypeCodeHeader* DDS_FloatGetTypeCode();

/* �ײ�ʹ�ú��� */
DCPSDLL DDS_Float* DDS_FloatCreateSample(
    ZRMemPool* pool,
    ZR_BOOLEAN allocMutable);

DCPSDLL void DDS_FloatDestroySample(
    ZRMemPool* pool,
    DDS_Float* sample);

DCPSDLL ZR_UINT32 DDS_FloatGetSerializedSampleMaxSize();

DCPSDLL ZR_UINT32 DDS_FloatGetSerializedSampleSize(
    const DDS_Float* sample,
    ZR_UINT32 currentAlignment);

DCPSDLL ZR_INT32 DDS_FloatSerialize(
    const DDS_Float* sample,
    CDRSerializer* cdr);

DCPSDLL ZR_INT32 DDS_FloatDeserialize(
    DDS_Float* sample,
    CDRDeserializer* cdr,
    ZRMemPool* pool);

DCPSDLL ZR_UINT32 DDS_FloatGetSerializedKeyMaxSize();

DCPSDLL ZR_UINT32 DDS_FloatGetSerializedKeySize(
    const DDS_Float* sample,
    ZR_UINT32 currentAlignment);

DCPSDLL ZR_INT32 DDS_FloatSerializeKey(
    const DDS_Float* sample,
    CDRSerializer* cdr);

DCPSDLL ZR_INT32 DDS_FloatDeserializeKey(
    DDS_Float* sample,
    CDRDeserializer* cdr,
    ZRMemPool* pool);

DCPSDLL ZR_INT32 DDS_FloatGetKeyHash(
    const DDS_Float* sample,
    CDRSerializer* cdr,
    DDS_KeyHash_t*  result);

DCPSDLL ZR_BOOLEAN DDS_FloatHasKey();

DCPSDLL TypeCodeHeader* DDS_FloatGetInnerTypeCode();

#ifdef _ZRDDS_INCLUDE_ONSITE_DESERILIZE

DCPSDLL ZR_BOOLEAN DDS_FloatNoSerializingSupported(
    const void* typesupport);

DCPSDLL ZR_UINT32 DDS_FloatFixedHeaderLength(
    const void* typesupport);

DCPSDLL ZR_INT32 DDS_FloatOnSiteDeserialize(
    CDRDeserializer* cdr,
    void* sample,
    ZR_UINT32 offset,
    ZR_UINT32 totalSize,
    ZR_INT8* payload,
    ZR_UINT32 payloadLen,
    ZR_UINT32 fixedHeaderLen);

#endif //_ZRDDS_INCLUDE_ONSITE_DESERILIZE

#ifdef _ZRDDS_INCLUDE_NO_SERIALIZE_MODE

DCPSDLL ZR_INT8* DDS_FloatLoanSampleBuf(
    void* sample,
    ZR_BOOLEAN takeBuffer,
    const void* typesupport);

DCPSDLL void DDS_FloatReturnSampleBuf(
    ZR_INT8* sampleBuf,
    const void* typesupport);

DCPSDLL ZR_INT32 DDS_FloatLoanDeserialize(
    void* sample,
    CDRDeserializer* cdr,
    ZR_UINT32 curIndex,
    ZR_UINT32 totalNum,
    ZR_INT8* base,
    ZR_UINT32 offset,
    ZR_UINT32 space,
    ZR_UINT32 fixedHeaderLen);

#endif //_ZRDDS_INCLUDE_NO_SERIALIZE_MODE

/* �û�ʹ�ýӿ� */
DCPSDLL ZR_BOOLEAN DDS_DoubleInitialize(
    DDS_Double* self);

DCPSDLL ZR_BOOLEAN DDS_DoubleInitializeEx(
    DDS_Double* self,
    ZRMemPool* pool,
    ZR_BOOLEAN allocateMemory);

DCPSDLL void DDS_DoubleFinalize(
    DDS_Double* self);

DCPSDLL void DDS_DoubleFinalizeEx(
    DDS_Double* self,
    ZRMemPool* pool,
    ZR_BOOLEAN deletePointers);

DCPSDLL ZR_BOOLEAN DDS_DoubleCopySample(
    DDS_Double* dst,
    const DDS_Double* src);

DCPSDLL ZR_BOOLEAN DDS_DoubleCopyEx(
    DDS_Double* dst,
    const DDS_Double* src,
    ZRMemPool* pool);

DCPSDLL void DDS_DoublePrintData(
    const DDS_Double* sample);

DCPSDLL TypeCodeHeader* DDS_DoubleGetTypeCode();

/* �ײ�ʹ�ú��� */
DCPSDLL DDS_Double* DDS_DoubleCreateSample(
    ZRMemPool* pool,
    ZR_BOOLEAN allocMutable);

DCPSDLL void DDS_DoubleDestroySample(
    ZRMemPool* pool,
    DDS_Double* sample);

DCPSDLL ZR_UINT32 DDS_DoubleGetSerializedSampleMaxSize();

DCPSDLL ZR_UINT32 DDS_DoubleGetSerializedSampleSize(
    const DDS_Double* sample,
    ZR_UINT32 currentAlignment);

DCPSDLL ZR_INT32 DDS_DoubleSerialize(
    const DDS_Double* sample,
    CDRSerializer* cdr);

DCPSDLL ZR_INT32 DDS_DoubleDeserialize(
    DDS_Double* sample,
    CDRDeserializer* cdr,
    ZRMemPool* pool);

DCPSDLL ZR_UINT32 DDS_DoubleGetSerializedKeyMaxSize();

DCPSDLL ZR_UINT32 DDS_DoubleGetSerializedKeySize(
    const DDS_Double* sample,
    ZR_UINT32 currentAlignment);

DCPSDLL ZR_INT32 DDS_DoubleSerializeKey(
    const DDS_Double* sample,
    CDRSerializer* cdr);

DCPSDLL ZR_INT32 DDS_DoubleDeserializeKey(
    DDS_Double* sample,
    CDRDeserializer* cdr,
    ZRMemPool* pool);

DCPSDLL ZR_INT32 DDS_DoubleGetKeyHash(
    const DDS_Double* sample,
    CDRSerializer* cdr,
    DDS_KeyHash_t*  result);

DCPSDLL ZR_BOOLEAN DDS_DoubleHasKey();

DCPSDLL TypeCodeHeader* DDS_DoubleGetInnerTypeCode();

#ifdef _ZRDDS_INCLUDE_ONSITE_DESERILIZE

DCPSDLL ZR_BOOLEAN DDS_DoubleNoSerializingSupported(
    const void* typesupport);

DCPSDLL ZR_UINT32 DDS_DoubleFixedHeaderLength(
    const void* typesupport);

DCPSDLL ZR_INT32 DDS_DoubleOnSiteDeserialize(
    CDRDeserializer* cdr,
    void* sample,
    ZR_UINT32 offset,
    ZR_UINT32 totalSize,
    ZR_INT8* payload,
    ZR_UINT32 payloadLen,
    ZR_UINT32 fixedHeaderLen);

#endif //_ZRDDS_INCLUDE_ONSITE_DESERILIZE

#ifdef _ZRDDS_INCLUDE_NO_SERIALIZE_MODE

DCPSDLL ZR_INT8* DDS_DoubleLoanSampleBuf(
    void* sample,
    ZR_BOOLEAN takeBuffer,
    const void* typesupport);

DCPSDLL void DDS_DoubleReturnSampleBuf(
    ZR_INT8* sampleBuf,
    const void* typesupport);

DCPSDLL ZR_INT32 DDS_DoubleLoanDeserialize(
    void* sample,
    CDRDeserializer* cdr,
    ZR_UINT32 curIndex,
    ZR_UINT32 totalNum,
    ZR_INT8* base,
    ZR_UINT32 offset,
    ZR_UINT32 space,
    ZR_UINT32 fixedHeaderLen);

#endif //_ZRDDS_INCLUDE_NO_SERIALIZE_MODE

/**
 * @struct DDS_KeyedString
 *
 * @ingroup  CoreBuiltinTypes
 *
 * @brief   ZRDDS���õĴ���ֵ���ַ������ͣ���/0��β��������󳤶����ơ�
 */

typedef struct DDS_KeyedString
{
    /** @brief   �ó�ԱΪ�����͵ļ�ֵ��Ϊ����󳤶ȵ��ַ������� */
    DDS_Char* key;
    /** @brief   �ַ������ݣ���/0��β���� */
    DDS_Char* value;
} DDS_KeyedString; 

/**
 * @struct DDS_KeyedStringSeq
 *
 * @ingroup CoreBuiltinTypes
 *
 * @brief   ���������������� DDS_KeyedString �����У��μ�@ref CoreSeqStruct ��
 */

DDS_SEQUENCE_CPP(DDS_KeyedStringSeq, DDS_KeyedString);

/* �û�ʹ�ýӿ� */
DCPSDLL ZR_BOOLEAN DDS_KeyedStringInitialize(
    DDS_KeyedString* self);

DCPSDLL ZR_BOOLEAN DDS_KeyedStringInitializeEx(
    DDS_KeyedString* self,
    ZRMemPool* pool,
    ZR_BOOLEAN allocateMemory);

DCPSDLL void DDS_KeyedStringFinalize(
    DDS_KeyedString* self);

DCPSDLL void DDS_KeyedStringFinalizeEx(
    DDS_KeyedString* self,
    ZRMemPool* pool,
    ZR_BOOLEAN deletePointers);

DCPSDLL ZR_BOOLEAN DDS_KeyedStringCopySample(
    DDS_KeyedString* dst,
    const DDS_KeyedString* src);

DCPSDLL ZR_BOOLEAN DDS_KeyedStringCopyEx(
    DDS_KeyedString* dst,
    const DDS_KeyedString* src,
    ZRMemPool* pool);

DCPSDLL void DDS_KeyedStringPrintData(
    const DDS_KeyedString* sample);

DCPSDLL TypeCodeHeader* DDS_KeyedStringGetTypeCode();

/* �ײ�ʹ�ú��� */
DCPSDLL DDS_KeyedString* DDS_KeyedStringCreateSample(
    ZRMemPool* pool,
    ZR_BOOLEAN allocMutable);

DCPSDLL void DDS_KeyedStringDestroySample(
    ZRMemPool* pool,
    DDS_KeyedString* sample);

DCPSDLL ZR_UINT32 DDS_KeyedStringGetSerializedSampleMaxSize();

DCPSDLL ZR_UINT32 DDS_KeyedStringGetSerializedSampleSize(
    const DDS_KeyedString* sample,
    ZR_UINT32 currentAlignment);

DCPSDLL ZR_INT32 DDS_KeyedStringSerialize(
    const DDS_KeyedString* sample,
    CDRSerializer* cdr);

DCPSDLL ZR_INT32 DDS_KeyedStringDeserialize(
    DDS_KeyedString* sample,
    CDRDeserializer* cdr,
    ZRMemPool* pool);

DCPSDLL ZR_UINT32 DDS_KeyedStringGetSerializedKeyMaxSize();

DCPSDLL ZR_UINT32 DDS_KeyedStringGetSerializedKeySize(
    const DDS_KeyedString* sample,
    ZR_UINT32 currentAlignment);

DCPSDLL ZR_INT32 DDS_KeyedStringSerializeKey(
    const DDS_KeyedString* sample,
    CDRSerializer* cdr);

DCPSDLL ZR_INT32 DDS_KeyedStringDeserializeKey(
    DDS_KeyedString* sample,
    CDRDeserializer* cdr,
    ZRMemPool* pool);

DCPSDLL ZR_INT32 DDS_KeyedStringGetKeyHash(
    const DDS_KeyedString* sample,
    CDRSerializer* cdr,
    DDS_KeyHash_t*  result);

DCPSDLL ZR_BOOLEAN DDS_KeyedStringHasKey();

DCPSDLL TypeCodeHeader* DDS_KeyedStringGetInnerTypeCode();

#ifdef _ZRDDS_INCLUDE_ONSITE_DESERILIZE

DCPSDLL ZR_BOOLEAN DDS_KeyedStringNoSerializingSupported(
    const void* typesupport);

DCPSDLL ZR_UINT32 DDS_KeyedStringFixedHeaderLength(
    const void* typesupport);

DCPSDLL ZR_INT32 DDS_KeyedStringOnSiteDeserialize(
    CDRDeserializer* cdr,
    void* sample,
    ZR_UINT32 offset,
    ZR_UINT32 totalSize,
    ZR_INT8* payload,
    ZR_UINT32 payloadLen,
    ZR_UINT32 fixedHeaderLen);

#endif //_ZRDDS_INCLUDE_ONSITE_DESERILIZE

#ifdef _ZRDDS_INCLUDE_NO_SERIALIZE_MODE

DCPSDLL ZR_INT8* DDS_KeyedStringLoanSampleBuf(
    void* sample,
    ZR_BOOLEAN takeBuffer,
    const void* typesupport);

DCPSDLL void DDS_KeyedStringReturnSampleBuf(
    ZR_INT8* sampleBuf,
    const void* typesupport);

DCPSDLL ZR_INT32 DDS_KeyedStringLoanDeserialize(
    void* sample,
    CDRDeserializer* cdr,
    ZR_UINT32 curIndex,
    ZR_UINT32 totalNum,
    ZR_INT8* base,
    ZR_UINT32 offset,
    ZR_UINT32 space,
    ZR_UINT32 fixedHeaderLen);

#endif //_ZRDDS_INCLUDE_NO_SERIALIZE_MODE

/**
 * @struct DDS_Bytes
 *
 * @ingroup  CoreBuiltinTypes
 *
 * @brief   Ϊ�����û�ֱ�Ӵ��仺�����������ͣ�ZRDDS�ṩ���õĻ��������ͣ����������ַ������͵���Ҫ����Ϊ�����������к���/0��
 *          - ��׼�ӿ�ͨ�����´���γ�ʼ�����������ͣ�
 *          ```c
 *          DDS_Bytes sample;
 *          DDS_OctetSeq_initialize(&sample.value);
 *          // ����û��ռ䣬����bufferΪ��������lengthΪ����������
 *          DDS_OctetSeq_loan_contiguous(&sample.value, buffer, length, length);
 *          ```
 *          ```cpp
 *          Bytes sample;
 *          // ����û��ռ䣬����bufferΪ��������lengthΪ����������
 *          sample.loan_contiguous(&sample.value, buffer, length, length);
 *          ```
 *          - �򻯽ӿ�ͨ�����ýӿ� BytesWrapper / DDS_BytesWrapper
 */

typedef struct DDS_Bytes
{
    /** @brief   ���Ͻ�Ļ����������Ͳμ� FooSeq �� */
    DDS_OctetSeq value;
} DDS_Bytes; 

/**
 * @struct DDS_BytesSeq
 *
 * @ingroup CoreBuiltinTypes
 *
 * @brief   ���������������� DDS_Bytes �����У��μ�@ref CoreSeqStruct ��
 */

DDS_SEQUENCE_CPP(DDS_BytesSeq, DDS_Bytes);

/* �û�ʹ�ýӿ� */
DCPSDLL ZR_BOOLEAN DDS_BytesInitialize(
    DDS_Bytes* self);

DCPSDLL ZR_BOOLEAN DDS_BytesInitializeEx(
    DDS_Bytes* self,
    ZRMemPool* pool,
    ZR_BOOLEAN allocateMemory);

DCPSDLL void DDS_BytesFinalize(
    DDS_Bytes* self);

DCPSDLL void DDS_BytesFinalizeEx(
    DDS_Bytes* self,
    ZRMemPool* pool,
    ZR_BOOLEAN deletePointers);

DCPSDLL ZR_BOOLEAN DDS_BytesCopySample(
    DDS_Bytes* dst,
    const DDS_Bytes* src);

DCPSDLL ZR_BOOLEAN DDS_BytesCopyEx(
    DDS_Bytes* dst,
    const DDS_Bytes* src,
    ZRMemPool* pool);

DCPSDLL void DDS_BytesPrintData(
    const DDS_Bytes* sample);

DCPSDLL TypeCodeHeader* DDS_BytesGetTypeCode();

/* �ײ�ʹ�ú��� */
DCPSDLL DDS_Bytes* DDS_BytesCreateSample(
    ZRMemPool* pool,
    ZR_BOOLEAN allocMutable);

DCPSDLL void DDS_BytesDestroySample(
    ZRMemPool* pool,
    DDS_Bytes* sample);

DCPSDLL ZR_UINT32 DDS_BytesGetSerializedSampleMaxSize();

DCPSDLL ZR_UINT32 DDS_BytesGetSerializedSampleSize(
    const DDS_Bytes* sample,
    ZR_UINT32 currentAlignment);

DCPSDLL ZR_INT32 DDS_BytesSerialize(
    const DDS_Bytes* sample,
    CDRSerializer* cdr);

DCPSDLL ZR_INT32 DDS_BytesDeserialize(
    DDS_Bytes* sample,
    CDRDeserializer* cdr,
    ZRMemPool* pool);

DCPSDLL ZR_UINT32 DDS_BytesGetSerializedKeyMaxSize();

DCPSDLL ZR_UINT32 DDS_BytesGetSerializedKeySize(
    const DDS_Bytes* sample,
    ZR_UINT32 currentAlignment);

DCPSDLL ZR_INT32 DDS_BytesSerializeKey(
    const DDS_Bytes* sample,
    CDRSerializer* cdr);

DCPSDLL ZR_INT32 DDS_BytesDeserializeKey(
    DDS_Bytes* sample,
    CDRDeserializer* cdr,
    ZRMemPool* pool);

DCPSDLL ZR_INT32 DDS_BytesGetKeyHash(
    const DDS_Bytes* sample,
    CDRSerializer* cdr,
    DDS_KeyHash_t*  result);

DCPSDLL ZR_BOOLEAN DDS_BytesHasKey();

DCPSDLL TypeCodeHeader* DDS_BytesGetInnerTypeCode();

#ifdef _ZRDDS_INCLUDE_ONSITE_DESERILIZE

DCPSDLL ZR_BOOLEAN DDS_BytesNoSerializingSupported(
    const void* typesupport);

DCPSDLL ZR_UINT32 DDS_BytesFixedHeaderLength(
    const void* typesupport);

DCPSDLL ZR_INT32 DDS_BytesOnSiteDeserialize(
    CDRDeserializer* cdr,
    void* sample,
    ZR_UINT32 offset,
    ZR_UINT32 totalSize,
    ZR_INT8* payload,
    ZR_UINT32 payloadLen,
    ZR_UINT32 fixedHeaderLen);

#endif //_ZRDDS_INCLUDE_ONSITE_DESERILIZE

#ifdef _ZRDDS_INCLUDE_NO_SERIALIZE_MODE

DCPSDLL ZR_INT8* DDS_BytesLoanSampleBuf(
    void* sample,
    ZR_BOOLEAN takeBuffer,
    const void* typesupport);

DCPSDLL void DDS_BytesReturnSampleBuf(
    ZR_INT8* sampleBuf,
    const void* typesupport);

DCPSDLL ZR_INT32 DDS_BytesLoanDeserialize(
    void* sample,
    CDRDeserializer* cdr,
    ZR_UINT32 curIndex,
    ZR_UINT32 totalNum,
    ZR_INT8* base,
    ZR_UINT32 offset,
    ZR_UINT32 space,
    ZR_UINT32 fixedHeaderLen);

#endif //_ZRDDS_INCLUDE_NO_SERIALIZE_MODE

/**
 * @struct DDS_KeyedBytes
 *
 * @ingroup  CoreBuiltinTypes
 *
 * @brief   ZRDDS���õĴ�����Ļ��������ͣ���������������ַ������͵���Ҫ����Ϊ�����������к���/0��
 */

typedef struct DDS_KeyedBytes
{
    /** @brief   �ó�ԱΪ�����͵ļ�ֵ��Ϊ����󳤶ȵ��ַ������� */
    DDS_Char* key;
    /** @brief   ���Ͻ�Ļ����������Ͳμ� FooSeq �� */
    DDS_OctetSeq value;
} DDS_KeyedBytes; 

/**
 * @struct DDS_KeyedBytesSeq
 *
 * @ingroup CoreBuiltinTypes
 *
 * @brief   ���������������� DDS_KeyedBytes �����У��μ�@ref CoreSeqStruct ��
 */

DDS_SEQUENCE_CPP(DDS_KeyedBytesSeq, DDS_KeyedBytes);

/* �û�ʹ�ýӿ� */
DCPSDLL ZR_BOOLEAN DDS_KeyedBytesInitialize(
    DDS_KeyedBytes* self);

DCPSDLL ZR_BOOLEAN DDS_KeyedBytesInitializeEx(
    DDS_KeyedBytes* self,
    ZRMemPool* pool,
    ZR_BOOLEAN allocateMemory);

DCPSDLL void DDS_KeyedBytesFinalize(
    DDS_KeyedBytes* self);

DCPSDLL void DDS_KeyedBytesFinalizeEx(
    DDS_KeyedBytes* self,
    ZRMemPool* pool,
    ZR_BOOLEAN deletePointers);

DCPSDLL ZR_BOOLEAN DDS_KeyedBytesCopySample(
    DDS_KeyedBytes* dst,
    const DDS_KeyedBytes* src);

DCPSDLL ZR_BOOLEAN DDS_KeyedBytesCopyEx(
    DDS_KeyedBytes* dst,
    const DDS_KeyedBytes* src,
    ZRMemPool* pool);

DCPSDLL void DDS_KeyedBytesPrintData(
    const DDS_KeyedBytes* sample);

DCPSDLL TypeCodeHeader* DDS_KeyedBytesGetTypeCode();

/* �ײ�ʹ�ú��� */
DCPSDLL DDS_KeyedBytes* DDS_KeyedBytesCreateSample(
    ZRMemPool* pool,
    ZR_BOOLEAN allocMutable);

DCPSDLL void DDS_KeyedBytesDestroySample(
    ZRMemPool* pool,
    DDS_KeyedBytes* sample);

DCPSDLL ZR_UINT32 DDS_KeyedBytesGetSerializedSampleMaxSize();

DCPSDLL ZR_UINT32 DDS_KeyedBytesGetSerializedSampleSize(
    const DDS_KeyedBytes* sample,
    ZR_UINT32 currentAlignment);

DCPSDLL ZR_INT32 DDS_KeyedBytesSerialize(
    const DDS_KeyedBytes* sample,
    CDRSerializer* cdr);

DCPSDLL ZR_INT32 DDS_KeyedBytesDeserialize(
    DDS_KeyedBytes* sample,
    CDRDeserializer* cdr,
    ZRMemPool* pool);

DCPSDLL ZR_UINT32 DDS_KeyedBytesGetSerializedKeyMaxSize();

DCPSDLL ZR_UINT32 DDS_KeyedBytesGetSerializedKeySize(
    const DDS_KeyedBytes* sample,
    ZR_UINT32 currentAlignment);

DCPSDLL ZR_INT32 DDS_KeyedBytesSerializeKey(
    const DDS_KeyedBytes* sample,
    CDRSerializer* cdr);

DCPSDLL ZR_INT32 DDS_KeyedBytesDeserializeKey(
    DDS_KeyedBytes* sample,
    CDRDeserializer* cdr,
    ZRMemPool* pool);

DCPSDLL ZR_INT32 DDS_KeyedBytesGetKeyHash(
    const DDS_KeyedBytes* sample,
    CDRSerializer* cdr,
    DDS_KeyHash_t*  result);

DCPSDLL ZR_BOOLEAN DDS_KeyedBytesHasKey();

DCPSDLL TypeCodeHeader* DDS_KeyedBytesGetInnerTypeCode();

#ifdef _ZRDDS_INCLUDE_ONSITE_DESERILIZE

DCPSDLL ZR_BOOLEAN DDS_KeyedBytesNoSerializingSupported(
    const void* typesupport);

DCPSDLL ZR_UINT32 DDS_KeyedBytesFixedHeaderLength(
    const void* typesupport);

DCPSDLL ZR_INT32 DDS_KeyedBytesOnSiteDeserialize(
    CDRDeserializer* cdr,
    void* sample,
    ZR_UINT32 offset,
    ZR_UINT32 totalSize,
    ZR_INT8* payload,
    ZR_UINT32 payloadLen,
    ZR_UINT32 fixedHeaderLen);

#endif //_ZRDDS_INCLUDE_ONSITE_DESERILIZE

#ifdef _ZRDDS_INCLUDE_NO_SERIALIZE_MODE

DCPSDLL ZR_INT8* DDS_KeyedBytesLoanSampleBuf(
    void* sample,
    ZR_BOOLEAN takeBuffer,
    const void* typesupport);

DCPSDLL void DDS_KeyedBytesReturnSampleBuf(
    ZR_INT8* sampleBuf,
    const void* typesupport);

DCPSDLL ZR_INT32 DDS_KeyedBytesLoanDeserialize(
    void* sample,
    CDRDeserializer* cdr,
    ZR_UINT32 curIndex,
    ZR_UINT32 totalNum,
    ZR_INT8* base,
    ZR_UINT32 offset,
    ZR_UINT32 space,
    ZR_UINT32 fixedHeaderLen);

#endif //_ZRDDS_INCLUDE_NO_SERIALIZE_MODE

/**
 * @struct DDS_ZeroCopyBytes
 *
 * @ingroup  CoreBuiltinTypes
 *
 * @brief   ZRDDS���õ��㿽���������͡�
 *          
 * @details Ϊ��֧��RTPSЭ�飬�û���ʹ�õ����ݽṹ��Ҫ�ڷ��Ͷ˱����л���RTPS���Ĳ����ͣ��ڽ��ն˱������л����û����ݲ��ύ��
 *          ��ͨ������£��û������ݴӷ��͵������գ�������Ҫ�����������ݿ��������û����ݳ��Ƚϴ��ҵײ�ͨ��Э���ٶȽϿ�ʱ��
 *          ��ο������������ɺܴ�Ӱ�졣Ϊ������ͨ�����ܣ�ZRDDS�ṩ��һ�����õ��㿽���������ͣ�
 *          �ײ㴫��ĳ���Ϊ #reservedLength + #userLength ���û���ʹ���㿽����������ʱ���ڷ���ռ�ʱ�ɰ��������ܵĳ��ȷ��䣬
 *          ����ÿ�δ���ʱӦͨ������ #userLength ��ָ��ʵ����Ҫ������������ȡ�
 *          ʹ�ø���������������������
 *          - �������� DDS_DataWriterMessageModeQosPolicy::message_header_coalesce = true���������ݴ��佫�����쳣
 *          - �û��������ݿռ�ʱԤ������512�ֽڵĿռ���ΪZRDDS����ͷ���л��Ŀռ䣬�� #reservedLength >= 512���û������ĸ����� #userBuffer ����ʼ��д��
 *          - ʹ���㿽���������ͣ���֧���첽���͡����������Լ��漰�ش���QoS�������ɿ������Լ��־û�QoS��
 *          - ʹ���㿽���������ͣ���֧�����ݷ�Ƭ��
 */

typedef struct DDS_ZeroCopyBytes
{
    /** @brief   ���������ܳ��ȡ� */
    DDS_Long totalLength; 
    /** @brief   Ϊ�ײ�Ԥ����Э��ͷ�ռ䣬ͨ��Ԥ��1024B���ϡ� */
    DDS_Long reservedLength;
    /** @brief   ���ݻ�����������Ԥ�����֡� */
    DDS_Char* value;
    /** @brief   �û����ݿռ���ʼ��ַ��ʼ��ָ�� #value + #reservedLength */
    DDS_Char* userBuffer;
    /** @brief   �û����ݿռ�ĳ��ȣ��ڷ���ǰ���ã��ײ㽫���� #userLength + #reservedLength ���ȵ����ݡ� */
    DDS_Long userLength;
} DDS_ZeroCopyBytes; 

/**
 * @struct DDS_ZeroCopyBytesSeq
 *
 * @ingroup CoreBuiltinTypes
 *
 * @brief   ���������������� DDS_ZeroCopyBytes �����У��μ�@ref CoreSeqStruct ��
 */

DDS_SEQUENCE_CPP(DDS_ZeroCopyBytesSeq, DDS_ZeroCopyBytes);

/* �û�ʹ�ýӿ� */
DCPSDLL ZR_BOOLEAN DDS_ZeroCopyBytesInitialize(
    DDS_ZeroCopyBytes* self);

DCPSDLL ZR_BOOLEAN DDS_ZeroCopyBytesInitializeEx(
    DDS_ZeroCopyBytes* self,
    ZRMemPool* pool,
    ZR_BOOLEAN allocateMemory);

DCPSDLL void DDS_ZeroCopyBytesFinalize(
    DDS_ZeroCopyBytes* self);

DCPSDLL void DDS_ZeroCopyBytesFinalizeEx(
    DDS_ZeroCopyBytes* self,
    ZRMemPool* pool,
    ZR_BOOLEAN deletePointers);

DCPSDLL ZR_BOOLEAN DDS_ZeroCopyBytesCopySample(
    DDS_ZeroCopyBytes* dst,
    const DDS_ZeroCopyBytes* src);

DCPSDLL ZR_BOOLEAN DDS_ZeroCopyBytesCopyEx(
    DDS_ZeroCopyBytes* dst,
    const DDS_ZeroCopyBytes* src,
    ZRMemPool* pool);

DCPSDLL void DDS_ZeroCopyBytesPrintData(
    const DDS_ZeroCopyBytes* sample);

DCPSDLL TypeCodeHeader* DDS_ZeroCopyBytesGetTypeCode();

/* �ײ�ʹ�ú��� */
DCPSDLL DDS_ZeroCopyBytes* DDS_ZeroCopyBytesCreateSample(
    ZRMemPool* pool,
    ZR_BOOLEAN allocMutable);

DCPSDLL void DDS_ZeroCopyBytesDestroySample(
    ZRMemPool* pool,
    DDS_ZeroCopyBytes* sample);

DCPSDLL ZR_UINT32 DDS_ZeroCopyBytesGetSerializedSampleMaxSize();

DCPSDLL ZR_UINT32 DDS_ZeroCopyBytesGetSerializedSampleSize(
    const DDS_ZeroCopyBytes* sample,
    ZR_UINT32 currentAlignment);

DCPSDLL ZR_INT32 DDS_ZeroCopyBytesSerialize(
    const DDS_ZeroCopyBytes* sample,
    CDRSerializer* cdr);

DCPSDLL ZR_INT32 DDS_ZeroCopyBytesDeserialize(
    DDS_ZeroCopyBytes* sample,
    CDRDeserializer* cdr,
    ZRMemPool* pool);

DCPSDLL ZR_UINT32 DDS_ZeroCopyBytesGetSerializedKeyMaxSize();

DCPSDLL ZR_UINT32 DDS_ZeroCopyBytesGetSerializedKeySize(
    const DDS_ZeroCopyBytes* sample,
    ZR_UINT32 currentAlignment);

DCPSDLL ZR_INT32 DDS_ZeroCopyBytesSerializeKey(
    const DDS_ZeroCopyBytes* sample,
    CDRSerializer* cdr);

DCPSDLL ZR_INT32 DDS_ZeroCopyBytesDeserializeKey(
    DDS_ZeroCopyBytes* sample,
    CDRDeserializer* cdr,
    ZRMemPool* pool);

DCPSDLL ZR_INT32 DDS_ZeroCopyBytesGetKeyHash(
    const DDS_ZeroCopyBytes* sample,
    CDRSerializer* cdr,
    DDS_KeyHash_t*  result);

DCPSDLL ZR_BOOLEAN DDS_ZeroCopyBytesHasKey();

DCPSDLL TypeCodeHeader* DDS_ZeroCopyBytesGetInnerTypeCode();

#ifdef _ZRDDS_INCLUDE_ONSITE_DESERILIZE

DCPSDLL ZR_BOOLEAN DDS_ZeroCopyBytesNoSerializingSupported(
    const void* typesupport);

DCPSDLL ZR_UINT32 DDS_ZeroCopyBytesFixedHeaderLength(
    const void* typesupport);

DCPSDLL ZR_INT32 DDS_ZeroCopyBytesOnSiteDeserialize(
    CDRDeserializer* cdr,
    void* sample,
    ZR_UINT32 offset,
    ZR_UINT32 totalSize,
    ZR_INT8* payload,
    ZR_UINT32 payloadLen,
    ZR_UINT32 fixedHeaderLen);

#endif //_ZRDDS_INCLUDE_ONSITE_DESERILIZE

#ifdef _ZRDDS_INCLUDE_NO_SERIALIZE_MODE

DCPSDLL ZR_INT8* DDS_ZeroCopyBytesLoanSampleBuf(
    void* sample,
    ZR_BOOLEAN takeBuffer,
    const void* typesupport);

DCPSDLL void DDS_ZeroCopyBytesReturnSampleBuf(
    ZR_INT8* sampleBuf,
    const void* typesupport);

DCPSDLL ZR_INT32 DDS_ZeroCopyBytesLoanDeserialize(
    void* sample,
    CDRDeserializer* cdr,
    ZR_UINT32 curIndex,
    ZR_UINT32 totalNum,
    ZR_INT8* base,
    ZR_UINT32 offset,
    ZR_UINT32 space,
    ZR_UINT32 fixedHeaderLen);

#endif //_ZRDDS_INCLUDE_NO_SERIALIZE_MODE
	
#endif //_ZRDDS_INCLUDE_BUILTIN_TYPES

#ifdef __cplusplus
}
#endif
#endif
