/**
 * @file:       QosPolicyId_t.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#ifndef QosPolicyId_t_h__
#define QosPolicyId_t_h__

#include "ZRDDSCommon.h"

/**
 * @enum DDS_QosPolicyId_t
 *
 * @ingroup CoreQosStruct
 *
 * @brief   ö��ֵ��ʶQoS�����͡�
 */

typedef enum DDS_QosPolicyId_t
{
    /** @brief  ��Ч�ı�ʶ�� @ingroup CoreQosStruct */
    DDS_INVALID_QOS_POLICY_ID = 0,
    /** @brief  ��ʶ DDS_UserDataQosPolicy �� @ingroup CoreQosStruct */
    DDS_USERDATA_QOS_POLICY_ID = 1,
    /** @brief  ��ʶ DDS_DurabilityQosPolicy �� @ingroup CoreQosStruct */
    DDS_DURABILITY_QOS_POLICY_ID = 2,
    /** @brief  ��ʶ DDS_PresentationQosPolicy �� @ingroup CoreQosStruct */
    DDS_PRESENTATION_QOS_POLICY_ID = 3,
    /** @brief  ��ʶ DDS_DeadlineQosPolicy �� @ingroup CoreQosStruct */
    DDS_DEADLINE_QOS_POLICY_ID = 4,
    /** @brief  ��ʶ DDS_LatencyBudgetQosPolicy �� @ingroup CoreQosStruct */
    DDS_LATENCYBUDGET_QOS_POLICY_ID = 5,
    /** @brief  ��ʶ DDS_OwnershipQosPolicy �� @ingroup CoreQosStruct */
    DDS_OWNERSHIP_QOS_POLICY_ID = 6,
    /** @brief  ��ʶ DDS_OwnershipStrengthQosPolicy �� @ingroup CoreQosStruct */
    DDS_OWNERSHIPSTRENGTH_QOS_POLICY_ID = 7,
    /** @brief  ��ʶ DDS_LivelinessQosPolicy �� @ingroup CoreQosStruct */
    DDS_LIVELINESS_QOS_POLICY_ID = 8,
    /** @brief  ��ʶ DDS_TimeBasedFilterQosPolicy �� @ingroup CoreQosStruct */
    DDS_TIMEBASEDFILTER_QOS_POLICY_ID = 9,
    /** @brief  ��ʶ DDS_PartitionQosPolicy �� @ingroup CoreQosStruct */
    DDS_PARTITION_QOS_POLICY_ID = 10,
    /** @brief  ��ʶ DDS_ReliabilityQosPolicy �� @ingroup CoreQosStruct */
    DDS_RELIABILITY_QOS_POLICY_ID = 11,
    /** @brief  ��ʶ DDS_DestinationOrderQosPolicy �� @ingroup CoreQosStruct */
    DDS_DESTINATIONORDER_QOS_POLICY_ID = 12,
    /** @brief  ��ʶ DDS_HistoryQosPolicy �� @ingroup CoreQosStruct */
    DDS_HISTORY_QOS_POLICY_ID = 13,
    /** @brief  ��ʶ DDS_ResourceLimitsQosPolicy �� @ingroup CoreQosStruct */
    DDS_RESOURCELIMITS_QOS_POLICY_ID = 14,
    /** @brief  ��ʶ DDS_EntityFactoryQosPolicy �� @ingroup CoreQosStruct */
    DDS_ENTITYFACTORY_QOS_POLICY_ID = 15,
    /** @brief  ��ʶ DDS_WriterDataLifeCycleQosPolicy �� @ingroup CoreQosStruct */
    DDS_WRITERDATALIFECYCLE_QOS_POLICY_ID = 16,
    /** @brief  ��ʶ DDS_ReaderDataLifeCycleQosPolicy �� @ingroup CoreQosStruct */
    DDS_READERDATALIFECYCLE_QOS_POLICY_ID = 17,
    /** @brief  ��ʶ DDS_TopicDataQosPolicy �� @ingroup CoreQosStruct */
    DDS_TOPICDATA_QOS_POLICY_ID = 18,
    /** @brief  ��ʶ DDS_GroupDataQosPolicy �� @ingroup CoreQosStruct */
    DDS_GROUPDATA_QOS_POLICY_ID = 19,
    /** @brief  ��ʶ DDS_TransportPriorityQosPolicy �� @ingroup CoreQosStruct */
    DDS_TRANSPORTPRIORITY_QOS_POLICY_ID = 20,
    /** @brief  ��ʶ DDS_LifespanQosPolicy �� @ingroup CoreQosStruct */
    DDS_LIFESPAN_QOS_POLICY_ID = 21,
    /** @brief  ��ʶ DDS_DurabilityServiceQosPolicy �� @ingroup CoreQosStruct */
    DDS_DURABILITYSERVICE_QOS_POLICY_ID = 22,
    /** @brief  ��ʶ DDS_RepresentationQosPolicy �� @ingroup CoreQosStruct */
    DDS_DATA_REPRESENTATION_QOS_POLICY_ID = 23,
    /** @brief  �������͡� @ingroup CoreQosStruct */
    DDS_TYPE_CONSISTENCY_ENFORCEMENT_QOS_POLICY_ID = 24,
    /** @brief  �������͡� @ingroup CoreQosStruct */
    DDS_NETWORKCONFIG_QOS_POLICY_ID = 50,
    /** @brief  �������͡� @ingroup CoreQosStruct */
    DDS_DISCOVERYCONFIG_QOS_POLICY_ID = 51
}DDS_QosPolicyId_t;

#endif /* QosPolicyId_t_h__*/
