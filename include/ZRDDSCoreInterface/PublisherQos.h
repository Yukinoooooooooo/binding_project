/**
 * @file:       PublisherQos.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#ifndef PublisherQos_h__
#define PublisherQos_h__

#include "PresentationQosPolicy.h"
#include "PartitionQosPolicy.h"
#include "GroupDataQosPolicy.h"
#include "EntityFactoryQosPolicy.h"
#include "AsynchronousPublisherQosPolicy.h"
#include "TransportConfigQosPolicy.h"

/**
 * @struct DDS_PublisherQos
 *
 * @ingroup CoreQosStruct
 *
 * @brief ������QoS����
 */
typedef struct DDS_PublisherQos
{
#ifdef _ZRDDS_INCLUDE_PRESENTATION_QOS
    /** @brief ����չʾ���á� */
    DDS_PresentationQosPolicy presentation;
#endif /* _ZRDDS_INCLUDE_PRESENTATION_QOS */
#ifdef _ZRDDS_INCLUDE_PARTITION_QOS
    /** @brief ����QoS���á� */
    DDS_PartitionQosPolicy partition;
#endif /* _ZRDDS_INCLUDE_PARTITION_QOS */
#ifdef _ZRDDS_INCLUDE_GROUP_DATA_QOS
    /** @brief ��Я�����ݡ� */
    DDS_GroupDataQosPolicy group_data;
#endif /* _ZRDDS_INCLUDE_GROUP_DATA_QOS */
    /** @brief ʵ�幤�����á� */
    DDS_EntityFactoryQosPolicy entity_factory;
    /* ��չQoS */
    /** @brief ����Publisher�Ƿ�ʹ���첽�������ݻ��첽�������͵�QoS�� */
    DDS_AsynchronousPublisherQosPolicy asynchronous_publisher;
#ifdef _ZRDDS_PORT_LIMIT
    /*ָ���û���������ʹ�õĶ˿ں͵�ַ*/
    DDS_TransportConfigQosPolicy send_addresses;
    /* �Ƿ�ʹ�õ��˿ڣ�ֱ�Ӹ���dp�Ķ˿ں͵�ַ */
    ZR_BOOLEAN single_port;
#endif /*_ZRDDS_PORT_LIMIT*/
}DDS_PublisherQos;

#endif /* PublisherQos_h__*/
