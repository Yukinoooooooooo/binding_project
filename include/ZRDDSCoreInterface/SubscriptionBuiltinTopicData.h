/**
 * @file:       SubscriptionBuiltinTopicData.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#ifndef SubscriptionBuiltinTopicData_h__
#define SubscriptionBuiltinTopicData_h__

#include "BuiltinTopicKey_t.h"
#include "DurabilityQosPolicy.h"
#include "DeadlineQosPolicy.h"
#include "LatencyBudgetQosPolicy.h"
#include "LivelinessQosPolicy.h"
#include "ReliabilityQosPolicy.h"
#include "OwnershipQosPolicy.h"
#include "DestinationOrderQosPolicy.h"
#include "UserDataQosPolicy.h"
#include "TimeBasedFilterQosPolicy.h"
#include "PresentationQosPolicy.h"
#include "PropertyList.h"
#include "PartitionQosPolicy.h"
#include "TopicDataQosPolicy.h"
#include "GroupDataQosPolicy.h"
#include "ZRSequence.h"
#include "ContentFilterProperty_t.h"
#include "TypeObject.h"
#include "TypeConsistencyEnforcementQosPolicy.h"
#ifdef _ZRDDSSECURITY
#include "DataTags.h"
#include "DDSBuiltinSecurityCommon.h"
#endif /* _ZRDDSSECURITY */

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @struct DDS_SubscriptionBuiltinTopicData
 *
 * @ingroup CoreBaseStruct
 *
 * @brief   �ýṹ�����ڴ洢Զ������д�ߵ���Ϣ��
 */

typedef struct DDS_SubscriptionBuiltinTopicData
{
    /** @brief   ���ݶ��ߵ�Ψһ��ʶ�� */
    DDS_BuiltinTopicKey_t key;
    /** @brief   ���ݶ�������������ߵ�Ψһ��ʶ�� */
    DDS_BuiltinTopicKey_t participant_key;
    /** @brief   ���ݶ��߹�����������������ơ� */
    DDS_Char* topic_name;
    /** @brief   ���ݶ��߹���������������������͵����ơ� */
    DDS_Char* type_name;
    /** @brief   ���ݶ��ߵ������б� */
    DDS_PropertyList property_list;
#ifdef _ZRDDS_INCLUDE_CONTENTFILTER_TOPIC
    /** @brief   ������ݶ��߹������ǻ������ݹ��˵����⣬��ó�Ա��ʾ�������ݹ��������Ϣ�� */
    DDS_ContentFilterProperty_t content_filter_property;
#endif /* _ZRDDS_INCLUDE_CONTENTFILTER_TOPIC  */
    /** @brief   �־û����á� */
    DDS_DurabilityQosPolicy durability;
#ifdef _ZRDDS_INCLUDE_DEADLINE_QOS
    /** @brief   ���ݶ��ߵĽ�ֹʱ�����á� */
    DDS_DeadlineQosPolicy deadline;
#endif /* _ZRDDS_INCLUDE_DEADLINE_QOS */
#ifdef _ZRDDS_INCLUDE_LATENCY_BUDGET_QOS
    /** @brief   ���ݶ��ߵ���ʱ�Ż����á� */
    DDS_LatencyBudgetQosPolicy latency_budget;
#endif /* _ZRDDS_INCLUDE_LATENCY_BUDGET_QOS */
#ifdef _ZRDDS_INCLUDE_LIVELINESS_QOS
    /** @brief   ���ݶ��ߵĴ�������á� */
    DDS_LivelinessQosPolicy liveliness;
#endif /* _ZRDDS_INCLUDE_LIVELINESS_QOS */
    DDS_ReliabilityQosPolicy reliability;
#ifdef _ZRDDS_INCLUDE_OWNERSHIP_QOS
    /** @brief   ���ݶ�������ʵ������Ȩ���á� */
    DDS_OwnershipQosPolicy ownership;
#endif /* _ZRDDS_INCLUDE_OWNERSHIP_QOS */
#ifdef _ZRDDS_INCLUDE_DESTINATION_ORDER_QOS
    /** @brief   ���ݶ��ߵ�����˳�����á� */
    DDS_DestinationOrderQosPolicy destination_order;
#endif /* _ZRDDS_INCLUDE_DESTINATION_ORDER_QOS */
#ifdef _ZRDDS_INCLUDE_USER_DATA_QOS
    /** @brief   ���ݶ��ߵ�Я���������á� */
    DDS_UserDataQosPolicy user_data;
#endif /* _ZRDDS_INCLUDE_USER_DATA_QOS */
#ifdef _ZRDDS_INCLUDE_TIME_BASED_FILTER_QOS
    /** @brief   ���ݶ��ߵĻ����¼����˵����á� */
    DDS_TimeBasedFilterQosPolicy time_based_filter;
#endif /* _ZRDDS_INCLUDE_TIME_BASED_FILTER_QOS */
#ifdef _ZRDDS_INCLUDE_PRESENTATION_QOS
    /** @brief   ���ݶ������������ߵ����ݱ������á� */
    DDS_PresentationQosPolicy presention; 
#endif /* _ZRDDS_INCLUDE_PRESENTATION_QOS */
    DDS_TypeConsistencyEnforcementQosPolicy type_compatibility;
#ifdef _ZRDDS_INCLUDE_PARTITION_QOS
    /** @brief   ���ݶ������������ߵķ������á� */
    DDS_PartitionQosPolicy partition;
#endif /* _ZRDDS_INCLUDE_PARTITION_QOS */
#ifdef _ZRDDS_INCLUDE_TOPIC_DATA_QOS
    /** @brief   ���ݶ��߹����������Я���������á� */
    DDS_TopicDataQosPolicy topic_data;
#endif /* _ZRDDS_INCLUDE_TOPIC_DATA_QOS */
#ifdef _ZRDDS_INCLUDE_GROUP_DATA_QOS
    /** @brief   ���ݶ������������ߵ�Я���������á� */
    DDS_GroupDataQosPolicy group_data;
#endif /* _ZRDDS_INCLUDE_GROUP_DATA_QOS */
#ifdef _ZRDDS_INCLUDE_TYPE_OBJECT
    /** @brief   ���ݶ��߹�������������������͵������� */
    TypeObject* type_object;
#endif /* _ZRDDS_INCLUDE_TYPE_OBJECT */
#ifdef _ZRDDSSECURITY
    /** @brief The data tags */
    DDS_DataTags data_tags;
    /** @brief ʵ�尲ȫ�����Ϣ */
    DDS_EndpointSecurityInfo security_info;
    /** @brief ���ֹ����Ƿ���Ҫ������ */
    DDS_Boolean protected_discovery;
#endif /* _ZRDDSSECURITY */
}DDS_SubscriptionBuiltinTopicData;

DCPSDLL void DDS_SubscriptionBuiltinTopicDataInitial(DDS_SubscriptionBuiltinTopicData* self);

DCPSDLL void DDS_SubscriptionBuiltinTopicDataDestroy(DDS_SubscriptionBuiltinTopicData* self);

DCPSDLL DDS_Long DDS_SubscriptionBuiltinTopicDataCopy(DDS_SubscriptionBuiltinTopicData* dst, const DDS_SubscriptionBuiltinTopicData* src);

/* ����sequence�ṹ*/
DDS_SEQUENCE_CPP(DDS_SubscriptionBuiltinTopicDataSeq, DDS_SubscriptionBuiltinTopicData);

#ifdef _ZRDDSSECURITY
typedef DDS_SubscriptionBuiltinTopicData DDS_SubscriptionBuiltinTopicDataSecure;
#endif /* _ZRDDSSECURITY */

#ifdef __cplusplus
}
#endif

#endif /* SubscriptionBuiltinTopicData_h__*/
