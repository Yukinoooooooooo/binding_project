/**
 * @file:       PublicationBuiltinTopicData.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#ifndef PublicationBuiltinTopicData_h__
#define PublicationBuiltinTopicData_h__

#include "BuiltinTopicKey_t.h"
#include "DurabilityQosPolicy.h"
#include "DurabilityServiceQosPolicy.h"
#include "DeadlineQosPolicy.h"
#include "LatencyBudgetQosPolicy.h"
#include "LivelinessQosPolicy.h"
#include "ReliabilityQosPolicy.h"
#include "LifespanQosPolicy.h"
#include "UserDataQosPolicy.h"
#include "OwnershipQosPolicy.h"
#include "OwnershipStrengthQosPolicy.h"
#include "DestinationOrderQosPolicy.h"
#include "PresentationQosPolicy.h"
#include "PropertyList.h"
#include "PartitionQosPolicy.h"
#include "TopicDataQosPolicy.h"
#include "GroupDataQosPolicy.h"
#include "ZRSequence.h"
#include "TypeObject.h"
#ifdef _ZRDDSSECURITY
#include "DataTags.h"
#include "DDSBuiltinSecurityCommon.h"
#endif /* _ZRDDSSECURITY */

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @struct DDS_PublicationBuiltinTopicData
 *
 * @ingroup CoreBaseStruct
 *
 * @brief   �ýṹ�����ڴ洢Զ������д�ߵ���Ϣ��
 */

typedef struct DDS_PublicationBuiltinTopicData
{
    /** @brief   ����д�ߵ�Ψһ��ʶ�� */
    DDS_BuiltinTopicKey_t key;
    /** @brief   ����д������������ߵ�Ψһ��ʶ�� */
    DDS_BuiltinTopicKey_t participant_key;
    /** @brief   ����д�߹�����������������ơ� */
    DDS_Char* topic_name;
    /** @brief   ����д�߹���������������������͵����ơ� */
    DDS_Char* type_name;
    /** @brief   ����д�ߵĳ־û����á� */
    DDS_DurabilityQosPolicy durability;
    /** @brief   ����д�ߵĳ־û���Դ���á� */
    DDS_DurabilityServiceQosPolicy durability_service;
    /** @brief   ����д�ߵ������б� */
    DDS_PropertyList property_list;
#ifdef _ZRDDS_INCLUDE_DEADLINE_QOS
    /** @brief   ����д�ߵĽ�ֹʱ�����á� */
    DDS_DeadlineQosPolicy deadline;
#endif /* _ZRDDS_INCLUDE_DEADLINE_QOS */
#ifdef _ZRDDS_INCLUDE_LATENCY_BUDGET_QOS
    /** @brief   ����д�ߵ���ʱ�Ż����á� */
    DDS_LatencyBudgetQosPolicy latency_budget;
#endif /* _ZRDDS_INCLUDE_LATENCY_BUDGET_QOS */
#ifdef _ZRDDS_INCLUDE_LIVELINESS_QOS
    /** @brief   ����д�ߵĴ�������á� */
    DDS_LivelinessQosPolicy liveliness;
#endif /* _ZRDDS_INCLUDE_LIVELINESS_QOS */
    /** @brief   ����д�߿ɿ��Ե����á� */
    DDS_ReliabilityQosPolicy reliability;
#ifdef _ZRDDS_INCLUDE_LIFESPAN_QOS
    /** @brief   ����д��������Ч�ڵ����á� */
    DDS_LifespanQosPolicy lifespan;
#endif /* _ZRDDS_INCLUDE_LIFESPAN_QOS */
#ifdef _ZRDDS_INCLUDE_USER_DATA_QOS
    /** @brief   ����д�ߵ�Я���������á� */
    DDS_UserDataQosPolicy user_data;
#endif /* _ZRDDS_INCLUDE_USER_DATA_QOS */
#ifdef _ZRDDS_INCLUDE_OWNERSHIP_QOS
    /** @brief   ����д������ʵ������Ȩ���á� */
    DDS_OwnershipQosPolicy ownership;
    /** @brief   ����д������ʵ������ȨȨֵ���á� */
    DDS_OwnershipStrengthQosPolicy ownership_strength;
#endif /* _ZRDDS_INCLUDE_OWNERSHIP_QOS */
#ifdef _ZRDDS_INCLUDE_DESTINATION_ORDER_QOS
    /** @brief   ����д�ߵ�����˳�����á� */
    DDS_DestinationOrderQosPolicy destination_order;
#endif /* _ZRDDS_INCLUDE_DESTINATION_ORDER_QOS */
#ifdef _ZRDDS_INCLUDE_PRESENTATION_QOS
    /** @brief   ����д�����������ߵ����ݱ������á� */
    DDS_PresentationQosPolicy presention;
#endif /* _ZRDDS_INCLUDE_PRESENTATION_QOS */
#ifdef _ZRDDS_INCLUDE_PARTITION_QOS
    /** @brief   ����д�����������ߵķ������á� */
    DDS_PartitionQosPolicy partition;
#endif /* _ZRDDS_INCLUDE_PARTITION_QOS */
#ifdef _ZRDDS_INCLUDE_TOPIC_DATA_QOS
    /** @brief   ����д�߹����������Я���������á� */
    DDS_TopicDataQosPolicy topic_data;
#endif /* _ZRDDS_INCLUDE_TOPIC_DATA_QOS */
#ifdef _ZRDDS_INCLUDE_GROUP_DATA_QOS
    /** @brief   ����д�����������ߵ�Я���������á� */
    DDS_GroupDataQosPolicy group_data;
#endif /* _ZRDDS_INCLUDE_GROUP_DATA_QOS */
#ifdef _ZRDDS_INCLUDE_TYPE_OBJECT
    /** @brief   ����д�߹�������������������͵������� */
    TypeObject* type_object;
#endif
#ifdef _ZRDDSSECURITY
    /** @brief The data tags */
    DDS_DataTags data_tags;
    /** @brief ʵ�尲ȫ�����Ϣ */
    DDS_EndpointSecurityInfo security_info;
    /** @brief ���ֹ����Ƿ���Ҫ������ */
    DDS_Boolean protected_discovery;
#endif /* _ZRDDSSECURITY */
}DDS_PublicationBuiltinTopicData;

DCPSDLL void DDS_PublicationBuiltinTopicDataInitial(DDS_PublicationBuiltinTopicData* self);

DCPSDLL void DDS_PublicationBuiltinTopicDataDestroy(DDS_PublicationBuiltinTopicData* self);

DCPSDLL DDS_Long DDS_PublicationBuiltinTopicDataCopy(DDS_PublicationBuiltinTopicData* dst, 
    const DDS_PublicationBuiltinTopicData* src);

/* ����sequence�ṹ*/
DDS_SEQUENCE_CPP(DDS_PublicationBuiltinTopicDataSeq, DDS_PublicationBuiltinTopicData);

#ifdef _ZRDDSSECURITY
typedef DDS_PublicationBuiltinTopicData DDS_PublicationBuiltinTopicDataSecure;
#endif /* _ZRDDSSECURITY */

#ifdef __cplusplus
}
#endif

#endif /* PublicationBuiltinTopicData_h__*/
