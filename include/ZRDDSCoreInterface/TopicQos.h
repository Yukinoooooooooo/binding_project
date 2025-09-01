/**
 * @file:       TopicQos.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#ifndef TopicQos_h__
#define TopicQos_h__

#include "TopicDataQosPolicy.h"
#include "DurabilityQosPolicy.h"
#include "DurabilityServiceQosPolicy.h"
#include "DeadlineQosPolicy.h"
#include "LatencyBudgetQosPolicy.h"
#include "LivelinessQosPolicy.h"
#include "ReliabilityQosPolicy.h"
#include "DestinationOrderQosPolicy.h"
#include "HistoryQosPolicy.h"
#include "ResourceLimitsQosPolicy.h"
#include "TransportPriorityQosPolicy.h"
#include "LifespanQosPolicy.h"
#include "OwnershipQosPolicy.h"

/**
 * @struct DDS_TopicQos
 *
 * @ingroup CoreQosStruct
 *
 * @brief   ����ʵ���QoS���á�
 *
 * @details ����ʵ���QoSΪ����д���Լ����ݶ��ߵ�QoS���õļ���+ #topic_data ���ã�����ʵ���QoS����ͨ������������
 *          �����ʹ�ã�
 *          - ���ڹ�������д���Լ����ݶ���QoS���ã��μ� DDS::Subscriber::copy_from_topic_qos �Լ�  
 *          - �ڹ���������������ʱ��ʹ�� #topic_data Я���������ݡ�
 */

typedef struct DDS_TopicQos
{
#ifdef _ZRDDS_INCLUDE_TOPIC_DATA_QOS
    /** @brief   ����Я���������á� */
    DDS_TopicDataQosPolicy topic_data;
#endif /* _ZRDDS_INCLUDE_TOPIC_DATA_QOS */
    DDS_DurabilityQosPolicy durability;
    /** @brief �־û���ʷ�������á� */
    DDS_DurabilityServiceQosPolicy durability_service;
#ifdef _ZRDDS_INCLUDE_DEADLINE_QOS
    /** @brief   ��ֹʱ�����á� */
    DDS_DeadlineQosPolicy deadline;
#endif /* _ZRDDS_INCLUDE_DEADLINE_QOS */
#ifdef _ZRDDS_INCLUDE_LATENCY_BUDGET_QOS
    /** @brief   ��ʱ�Ż����á� */
    DDS_LatencyBudgetQosPolicy latency_budget;
#endif /* _ZRDDS_INCLUDE_LATENCY_BUDGET_QOS */
#ifdef _ZRDDS_INCLUDE_LIVELINESS_QOS
    /** @brief   ��μ��ƥ������д�ߵĴ�������á� */
    DDS_LivelinessQosPolicy liveliness;
#endif /* _ZRDDS_INCLUDE_LIVELINESS_QOS */
    DDS_ReliabilityQosPolicy reliability;
#ifdef _ZRDDS_INCLUDE_DESTINATION_ORDER_QOS
    /** @brief   ������д�ߵ���������˳�����á� */
    DDS_DestinationOrderQosPolicy destination_order;
#endif /* _ZRDDS_INCLUDE_DESTINATION_ORDER_QOS */
    DDS_HistoryQosPolicy history;
    /** @brief   ��Դʹ���������á� */
    DDS_ResourceLimitsQosPolicy resource_limits;
#ifdef _ZRDDS_INCLUDE_TRANSPORT_PRIORITY_QOS
    /** @brief �������ȼ����ã���δʹ�á� */
    DDS_TransportPriorityQosPolicy transport_priority;
#endif /* _ZRDDS_INCLUDE_TRANSPORT_PRIORITY_QOS */
#ifdef _ZRDDS_INCLUDE_LIFESPAN_QOS
    /** @brief ������Ч�����á� */
    DDS_LifespanQosPolicy lifespan;
#endif /* _ZRDDS_INCLUDE_LIFESPAN_QOS */
#ifdef _ZRDDS_INCLUDE_OWNERSHIP_QOS
    /** @brief   ����ʵ������Ȩ���á� */
    DDS_OwnershipQosPolicy ownership;
#endif /* _ZRDDS_INCLUDE_OWNERSHIP_QOS */
}DDS_TopicQos;

#endif /* TopicQos_h__*/
