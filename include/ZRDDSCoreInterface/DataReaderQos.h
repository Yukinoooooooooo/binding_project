/**
 * @file:       DataReaderQos.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#ifndef DataReaderQos_h__
#define DataReaderQos_h__

#include "OsResource.h"
#include "DurabilityQosPolicy.h"
#include "DeadlineQosPolicy.h"
#include "LatencyBudgetQosPolicy.h"
#include "LivelinessQosPolicy.h"
#include "ReliabilityQosPolicy.h"
#include "DestinationOrderQosPolicy.h"
#include "HistoryQosPolicy.h"
#include "ResourceLimitsQosPolicy.h"
#include "UserDataQosPolicy.h"
#include "OwnershipQosPolicy.h"
#include "TimeBasedFilterQosPolicy.h"
#include "ReaderDataLifecycleQosPolicy.h"
#include "TransportConfigQosPolicy.h"
#include "TypeConsistencyEnforcementQosPolicy.h"
#include "PropertyQosPolicy.h"
#include "QualityEvaluationQosPolicy.h"

/**
 * @struct DDS_DataReaderQos
 *
 * @ingroup CoreQosStruct
 *
 * @brief   �������ݶ��ߵ�QoS���á�
 */

typedef struct DDS_DataReaderQos
{
    /** @brief   �־û����á� */
    DDS_DurabilityQosPolicy durability;
#ifdef _ZRDDS_INCLUDE_DEADLINE_QOS
    /** @brief   ��ֹʱ�����á� */
    DDS_DeadlineQosPolicy deadline;
#endif //_ZRDDS_INCLUDE_DEADLINE_QOS
#ifdef _ZRDDS_INCLUDE_LATENCY_BUDGET_QOS
    /** @brief   ��ʱ�Ż����á� */
    DDS_LatencyBudgetQosPolicy latency_budget;
#endif //_ZRDDS_INCLUDE_LATENCY_BUDGET_QOS
#ifdef _ZRDDS_INCLUDE_LIVELINESS_QOS
    /** @brief   ��μ��ƥ������д�ߵĴ�������á� */
    DDS_LivelinessQosPolicy liveliness;
#endif //_ZRDDS_INCLUDE_LIVELINESS_QOS
    /** @brief   �ɿ������á� */
    DDS_ReliabilityQosPolicy reliability;
#ifdef _ZRDDS_INCLUDE_DESTINATION_ORDER_QOS
    /** @brief   ������д�ߵ���������˳�����á� */
    DDS_DestinationOrderQosPolicy destination_order;
#endif //_ZRDDS_INCLUDE_DESTINATION_ORDER_QOS
    /** @brief   �洢�������á� */
    DDS_HistoryQosPolicy history;
    /** @brief   ��Դʹ���������á� */
    DDS_ResourceLimitsQosPolicy resource_limits;
#ifdef _ZRDDS_INCLUDE_USER_DATA_QOS
    /** @brief   Я���������á� */
    DDS_UserDataQosPolicy user_data;
#endif //_ZRDDS_INCLUDE_USER_DATA_QOS
#ifdef _ZRDDS_INCLUDE_OWNERSHIP_QOS
    /** @brief   ����ʵ������Ȩ���á� */
    DDS_OwnershipQosPolicy ownership;
#endif //_ZRDDS_INCLUDE_OWNERSHIP_QOS
#ifdef _ZRDDS_INCLUDE_TIME_BASED_FILTER_QOS
    /** @brief   �����¼��������á� */
    DDS_TimeBasedFilterQosPolicy time_based_filter;
#endif //_ZRDDS_INCLUDE_TIME_BASED_FILTER_QOS
    /** @brief   ���ݶ������������������á� */
    DDS_ReaderDataLifecycleQosPolicy reader_data_lifecycle;
    /** @brief   ���ͼ������á� */
    DDS_TypeConsistencyEnforcementQosPolicy type_compatibility;
    /** @brief   �ײ㴫��Э�����á� */
    DDS_TransportConfigQosPolicy receive_addresses;
    /** @brief   ��ʵ��������б� */
    DDS_PropertyQosPolicy property;
#ifdef _ZRDDS_INCLUDE_BREAKPOINT_RESUME
    /** @brief   �ϵ�������������ģʽ��record_data�ӿ����ʹ�� ��trueΪ����������*/
    ZR_BOOLEAN breakpoint_resume;
#endif //_ZRDDS_INCLUDE_BREAKPOINT_RESUME
#ifdef _ZRDDS_INCLUDE_QUALITY_EVALUATION
    /** @brief   ͨ�������������á� */
    DDS_QualityEvaluationQosPolicy quality_evaluation;
#endif //_ZRDDS_INCLUDE_QUALITY_EVALUATION
}DDS_DataReaderQos;

#endif /* DataReaderQos_h__*/
