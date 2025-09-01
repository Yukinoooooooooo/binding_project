/**
 * @file:       DataWriterQos.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#ifndef DataWriterQos_h__
#define DataWriterQos_h__

#include "OsResource.h"
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
#include "UserDataQosPolicy.h"
#include "OwnershipQosPolicy.h"
#include "OwnershipStrengthQosPolicy.h"
#include "WriterDataLifecycleQosPolicy.h"
#include "BatchQosPolicy.h"
#include "PublishModeQosPolicy.h"
#include "DataWriterProtocolQosPolicy.h"
#include "DataWriterResourceLimitsQosPolicy.h"
#include "DataWriterMessageModeQosPolicy.h"
#include "ZRDDSCommon.h"
#include "TransportConfigQosPolicy.h"
#include "PropertyQosPolicy.h"

/**
 * @struct DDS_DataWriterQos
 *
 * @ingroup CoreQosStruct
 *
 * @brief ��������д�ߵ�QoS
 */
typedef struct DDS_DataWriterQos
{
    /** @brief �־û����á� */
    DDS_DurabilityQosPolicy durability;
    /** @brief �־û���ʷ�������á� */
    DDS_DurabilityServiceQosPolicy durability_service;
#ifdef _ZRDDS_INCLUDE_DEADLINE_QOS
    /** @brief ��ֹʱ�����á� */
    DDS_DeadlineQosPolicy deadline;
#endif /* _ZRDDS_INCLUDE_DEADLINE_QOS */
#ifdef _ZRDDS_INCLUDE_LATENCY_BUDGET_QOS
    /** @brief ��ʱ�Ż����á� */
    DDS_LatencyBudgetQosPolicy latency_budget;
#endif /* _ZRDDS_INCLUDE_LATENCY_BUDGET_QOS */
#ifdef _ZRDDS_INCLUDE_LIVELINESS_QOS
    /** @brief ��μ��ƥ������д�ߵĴ�������á� */
    DDS_LivelinessQosPolicy liveliness;
#endif /* _ZRDDS_INCLUDE_LIVELINESS_QOS */
    /** @brief �ɿ������á� */
    DDS_ReliabilityQosPolicy reliability;
#ifdef _ZRDDS_INCLUDE_DESTINATION_ORDER_QOS
    /** @brief ������д�ߵ���������˳�����á� */
    DDS_DestinationOrderQosPolicy destination_order;
#endif /* _ZRDDS_INCLUDE_DESTINATION_ORDER_QOS */
    /** @brief �洢�������á� */
    DDS_HistoryQosPolicy history;
    /** @brief ��Դʹ���������á� */
    DDS_ResourceLimitsQosPolicy resource_limits;
#ifdef _ZRDDS_INCLUDE_TRANSPORT_PRIORITY_QOS
    /** @brief �������ȼ����ã���δʹ�á� */
    DDS_TransportPriorityQosPolicy transport_priority;
#endif /* _ZRDDS_INCLUDE_TRANSPORT_PRIORITY_QOS */
#ifdef _ZRDDS_INCLUDE_LIFESPAN_QOS
    /** @brief ������Ч�����á� */
    DDS_LifespanQosPolicy lifespan;
#endif /* _ZRDDS_INCLUDE_LIFESPAN_QOS */
#ifdef _ZRDDS_INCLUDE_USER_DATA_QOS
    /** @brief Я���������á� */
    DDS_UserDataQosPolicy user_data;
#endif /* _ZRDDS_INCLUDE_USER_DATA_QOS */
#ifdef _ZRDDS_INCLUDE_OWNERSHIP_QOS
    /** @brief ����ʵ������Ȩ���á� */
    DDS_OwnershipQosPolicy ownership;
    /** @brief ����Ȩֵ���á� */
    DDS_OwnershipStrengthQosPolicy ownership_strength;
#endif /* _ZRDDS_INCLUDE_OWNERSHIP_QOS */
    /** @brief ����д�����������������á� */
    DDS_WriterDataLifecycleQosPolicy writer_data_lifecycle;
    
    /* ��չQoS */
#ifdef _ZRDDS_INCLUDE_BATCH
    /** @brief �����������á� */
    DDS_BatchQosPolicy batch;
#endif /* _ZRDDS_INCLUDE_BATCH */
    /** @brief ����д�߷���ģʽ���á� */
    DDS_PublishModeQosPolicy publish_mode;
    /** @brief ����д������RTPSЭ����ص���Ϊ���á� */
    DDS_DataWriterProtocolQosPolicy protocol;
    /** @brief ����д����Դ����QoS���á� */
    DDS_DataWriterResourceLimitsQosPolicy writer_resource_limits;
    /** @brief �ṩ����DataWriter��Ϣ����Ĺ��ܡ� */
    DDS_DataWriterMessageModeQosPolicy message_mode;
    /** @brief   DataWriterʹ�õĶ�����Participant�ĵ�ַ�����б� */
    DDS_TransportConfigQosPolicy receive_addresses;
    /** @brief   ��ʵ��������б� */
    DDS_PropertyQosPolicy property;
#ifdef _ZRDDS_INCLUDE_BIND_SENDADDR
    /** @brief   DataWriter�󶨵ı��ص�ַ��ֻ����һ����ַ���˿ں�Ϊ65536��ʾϵͳ��ѡ�˿� */
    DDS_TransportConfigQosPolicy send_addresses;
#endif /*_ZRDDS_INCLUDE_BIND_SENDADDR*/
}DDS_DataWriterQos;

#endif /* DataWriterQos_h__*/
