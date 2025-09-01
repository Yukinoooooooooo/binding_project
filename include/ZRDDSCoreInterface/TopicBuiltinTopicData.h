/**
 * @file:       TopicBuiltinTopicData.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#ifndef TopicBuiltinTopicData_h__
#define TopicBuiltinTopicData_h__

#include "BuiltinTopicKey_t.h"
#include "DurabilityQosPolicy.h"
#include "DurabilityServiceQosPolicy.h"
#include "DeadlineQosPolicy.h"
#include "LatencyBudgetQosPolicy.h"
#include "LivelinessQosPolicy.h"
#include "ReliabilityQosPolicy.h"
#include "LifespanQosPolicy.h"
#include "TransportPriorityQosPolicy.h"
#include "OwnershipQosPolicy.h"
#include "DestinationOrderQosPolicy.h"
#include "UserDataQosPolicy.h"
#include "TimeBasedFilterQosPolicy.h"
#include "PresentationQosPolicy.h"
#include "PartitionQosPolicy.h"
#include "TopicDataQosPolicy.h"
#include "GroupDataQosPolicy.h"
#include "ZRSequence.h"
#include "ContentFilterProperty_t.h"
#include "TypeObject.h"
#include "ResourceLimitsQosPolicy.h"

#ifdef _ZRDDS_INCLUDE_TOPIC_BUILTIN_TOPIC_DATA

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @struct DDS_TopicBuiltinTopicData
 *
 * @ingroup CoreBaseStruct
 *
 * @brief   �ýṹ�����ڴ洢���ֵ�Զ��������Ϣ��
 */

typedef struct DDS_TopicBuiltinTopicData
{
    /** @brief   �����Ψһ��ʶ�� */
    DDS_BuiltinTopicKey_t key;
    /** @brief   �������ơ� */
    DDS_Char* topic_name;
    /** @brief   ����������������͵����ơ� */
    DDS_Char* type_name;
    /** @brief   �־û����á� */
    DDS_DurabilityQosPolicy durability;
    /** @brief   �־û���ʷ�������á� */
    DDS_DurabilityServiceQosPolicy durability_service;
#ifdef _ZRDDS_INCLUDE_DEADLINE_QOS
    /** @brief   ����Ľ�ֹʱ�����á� */
    DDS_DeadlineQosPolicy deadline;
#endif /* _ZRDDS_INCLUDE_DEADLINE_QOS */
#ifdef _ZRDDS_INCLUDE_LATENCY_BUDGET_QOS
    /** @brief   �������ʱ�Ż����á� */
    DDS_LatencyBudgetQosPolicy latency_budget;
#endif /* _ZRDDS_INCLUDE_LATENCY_BUDGET_QOS */
#ifdef _ZRDDS_INCLUDE_LIVELINESS_QOS
    /** @brief   ����Ĵ�������á� */
    DDS_LivelinessQosPolicy liveliness;
#endif /* _ZRDDS_INCLUDE_LIVELINESS_QOS */
    DDS_ReliabilityQosPolicy reliability;
#ifdef _ZRDDS_INCLUDE_TRANSPORT_PRIORITY_QOS
    /** @brief   ��������Ĵ������ȼ����á� */
    DDS_TransportPriorityQosPolicy transport_priority;
#endif /*_ZRDDS_INCLUDE_TRANSPORT_PRIORITY_QOS */
#ifdef _ZRDDS_INCLUDE_LIFESPAN_QOS
    /** @brief   ����������Ч�ڵ����á� */
    DDS_LifespanQosPolicy lifespan;
#endif /* _ZRDDS_INCLUDE_LIFESPAN_QOS */
#ifdef _ZRDDS_INCLUDE_OWNERSHIP_QOS
    /** @brief   ��������ʵ������Ȩ���á� */
    DDS_OwnershipQosPolicy ownership;
#endif /* _ZRDDS_INCLUDE_OWNERSHIP_QOS */
#ifdef _ZRDDS_INCLUDE_DESTINATION_ORDER_QOS
    /** @brief   ���������˳�����á� */
    DDS_DestinationOrderQosPolicy destination_order;
#endif /* _ZRDDS_INCLUDE_DESTINATION_ORDER_QOS */
#ifdef _ZRDDS_INCLUDE_TOPIC_DATA_QOS
    /** @brief   ��������������Я���������á� */
    DDS_TopicDataQosPolicy topic_data;
#endif /* _ZRDDS_INCLUDE_TOPIC_DATA_QOS */
    /** @brief   ��ʷ���ݶ������á� */
    DDS_HistoryQosPolicy history;
    /** @brief   ��Դ�������á� */
    DDS_ResourceLimitsQosPolicy resource_limits;
#ifdef _ZRDDS_INCLUDE_TYPE_OBJECT
    /** @brief   �����������������������͵������� */
    TypeObject* type_object;
#endif /* _ZRDDS_INCLUDE_TYPE_OBJECT */
}DDS_TopicBuiltinTopicData;

DCPSDLL extern void DDS_TopicBuiltinTopicDataInitial(
    DDS_TopicBuiltinTopicData* self);

DCPSDLL extern void DDS_TopicBuiltinTopicDataDestroy(
    DDS_TopicBuiltinTopicData* self);

DCPSDLL extern DDS_Long DDS_TopicBuiltinTopicDataCopy(
    DDS_TopicBuiltinTopicData* dst, 
    const DDS_TopicBuiltinTopicData* src);

/* ����sequence�ṹ*/
DDS_SEQUENCE_CPP(DDS_TopicBuiltinTopicDataSeq, DDS_TopicBuiltinTopicData);

#ifdef __cplusplus
}
#endif
#else
typedef struct DDS_TopicBuiltinTopicData DDS_TopicBuiltinTopicData;
#endif /* _ZRDDS_INCLUDE_TOPIC_BUILTIN_TOPIC_DATA */

#endif /* TopicBuiltinTopicData_h__ */
