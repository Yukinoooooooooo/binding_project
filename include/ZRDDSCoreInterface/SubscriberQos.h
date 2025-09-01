/**
 * @file:       SubscriberQos.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#ifndef SubscriberQos_h__
#define SubscriberQos_h__

#include "PresentationQosPolicy.h"
#include "PartitionQosPolicy.h"
#include "GroupDataQosPolicy.h"
#include "EntityFactoryQosPolicy.h"

/**
 * @struct DDS_SubscriberQos
 *
 * @ingroup CoreQosStruct
 *
 * @brief   ���嶩���ߵ�QoS���á�
 */

typedef struct DDS_SubscriberQos
{
#ifdef _ZRDDS_INCLUDE_PRESENTATION_QOS
    /** @brief   �����ߵ�����չʾ���á� */
    DDS_PresentationQosPolicy presentation;
#endif /* _ZRDDS_INCLUDE_PRESENTATION_QOS */
#ifdef _ZRDDS_INCLUDE_PARTITION_QOS
    /** @brief   �����ߵķ������á� */
    DDS_PartitionQosPolicy partition;
#endif /* _ZRDDS_INCLUDE_PARTITION_QOS */
#ifdef _ZRDDS_INCLUDE_GROUP_DATA_QOS
    /** @brief   �����ߵ���Я���������á� */
    DDS_GroupDataQosPolicy group_data;
#endif /* _ZRDDS_INCLUDE_GROUP_DATA_QOS */
    /** @brief   �����ߵ�ʵ�幤�����á� */
    DDS_EntityFactoryQosPolicy entity_factory;
}DDS_SubscriberQos;

#endif /* SubscriberQos_h__*/
