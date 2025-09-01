/**
 * @file:       TypeCodeKind.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#ifndef TypeCodeKind_h__
#define TypeCodeKind_h__

#include "OsResource.h"

#ifdef __cplusplus
extern "C"
{
#endif

typedef struct TypeCodeHeader TypeCodeHeader;

/**
 * @typedef enum TCTypeKind
 *
 * @brief   ���ֽ�ö�����ͣ����е�һ���ֽڵ���λ��ʶ����1ΪС�˱��룬2Ϊ��˱��룬�����ͱ�ʾ�����������͵�TypeCode
 */

typedef enum TCTypeKind
{
    /** @brief  ��Чֵ */
    DDS_TK_NULL = 0,
    /** @brief  ������������short */
    DDS_TK_SHORT,
    /** @brief  ������������int */
    DDS_TK_INT,
    /** @brief  ������������ushort */
    DDS_TK_USHORT,
    /** @brief  ������������uint */
    DDS_TK_UINT,
    /** @brief  ������������float */
    DDS_TK_FLOAT,
    /** @brief  ������������double */
    DDS_TK_DOUBLE,
    /** @brief  ������������boolean */
    DDS_TK_BOOLEAN,
    /** @brief  ������������char */
    DDS_TK_CHAR,
    /** @brief  ������������uchar */
    DDS_TK_UCHAR,
    /** @brief  struct����*/
    DDS_TK_STRUCT,
    /** @brief  union ����*/
    DDS_TK_UNION,
    /** @brief  enum����*/
    DDS_TK_ENUM,
    /** @brief  ��������string */
    DDS_TK_STRING,
    /** @brief  ��������sequence */
    DDS_TK_SEQUENCE,
    /** @brief  ������������array */
    DDS_TK_ARRAY,
    /** @brief  ������������(��֧��) */
    DDS_TK_ALIAS,
    /** @brief  ������������longlong */
    DDS_TK_LONGLONG,
    /** @brief  ������������ulonglong */
    DDS_TK_ULONGLONG,
    /** @brief  �̳е�struct���� */
    DDS_TK_VALUETYPE = 22,
    /** @brief  ��ʼδֵ֪ */
    DDS_TK_UNKNOWN = -1
}TCTypeKind;

/**
 * @typedef enum TypeCodeExceptionCode
 *
 * @brief   ö���͵�TypeCodeException�������洢TypeCodeģ�����͵ķ���ֵ.
 */

typedef enum TypeCodeExceptionCode
{
    TC_EC_OK,
    TC_EC_ERROR
}TypeCodeExceptionCode;


typedef enum TypeCodeModifierKind
{
    DDS_MODIFIER_NONE
}TypeCodeModifierKind;

/**
 * @typedef enum ExtensibilityKind
 *
 * @brief   ��ʾ�����͵Ķ�̬���͡�
 */

typedef enum ExtensibilityKind
{
    /** @brief  ��ʾ������Ҫ�����ں�����ӳ�Ա�� */
    DDS_EXTENSIBLE_EXTENSIBILITY,
    /** @brief  ��ʾ�����Ѿ�ȷ�����Ժ󲻴�����չ�� */
    DDS_FINAL_EXTENSIBILITY,
    /** @brief  ��ʾ��������Ҫ�������ӡ�ɾ��������λ�õ����͡� */
    DDS_MUTABLE_EXTENSIBILITY
}ExtensibilityKind;

#ifdef __cplusplus
}
#endif

#endif /* TypeCodeKind_h__*/
