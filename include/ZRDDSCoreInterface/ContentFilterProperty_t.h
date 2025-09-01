/**
 * @file:       ContentFilterProperty_t.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#ifndef ContentFilterProperty_t_h__
#define ContentFilterProperty_t_h__

#include "OsResource.h"
#include "ZRBuiltinTypes.h"

#ifdef _ZRDDS_INCLUDE_CONTENTFILTER_TOPIC

/**
 * @struct DDS_ContentFilterProperty_t
 *
 * @ingroup CoreBaseStruct
 *
 * @brief   ��װ�� DDS_SubscriptionBuiltinTopicData �еĻ������ݹ��˵��������ԡ�
 */

typedef struct DDS_ContentFilterProperty_t{
    /** @brief    �������ݹ������������(ContentFilterTopic������)�� */
    DDS_Char* contentFilteredTopicName;
    /** @brief    ���������ͨ��������ƣ�Topic�����ƣ��� */
    DDS_Char* relatedTopicName;
    /** @brief    �������ͣ���ǰZRDDS��֧��"DDSSQL"�� */
    DDS_Char* filterClassName;
    /** @brief    ���˱��ʽ���ڴ����������ݹ��˵�����ʱ�û�ָ���Ĳ����� */
    DDS_Char* filterExpression;
    /** @brief    ���˲������ڴ����������ݹ��˵�����ʱ�û�ָ���Ĳ����� */
    DDS_StringSeq expressionParameters;
} DDS_ContentFilterProperty_t;

#endif /* _ZRDDS_INCLUDE_CONTENTFILTER_TOPIC */

#endif /* ContentFilterProperty_t_h__*/
