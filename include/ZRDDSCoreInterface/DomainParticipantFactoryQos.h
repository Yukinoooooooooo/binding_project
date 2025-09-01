/**
 * @file:       DomainParticipantFactoryQos.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#ifndef DomainParticipantFactoryQos_h__
#define DomainParticipantFactoryQos_h__

#include "OsResource.h"
#include "EntityFactoryQosPolicy.h"
#include "DDSLogQosPolicy.h"
#include "RapidIOConfigQosPolicy.h"
#include "QosProfileQosPolicy.h"
#ifdef _ZRDDS_INCLUDE_ENABLE_SYSTEM_CONFIGURE
#include "PropertyQosPolicy.h"
#endif // _ZRDDS_INCLUDE_ENABLE_SYSTEM_CONFIGURE

/**
 * @struct DDS_DomainParticipantFactoryQos
 *
 * @ingroup CoreQosStruct
 *
 * @brief   ����������߹�����QoS��
 */

typedef struct DDS_DomainParticipantFactoryQos
{
    /** @brief   ʵ�幤�����á� */
    DDS_EntityFactoryQosPolicy entity_factory;
    /** @brief   ��־ϵͳ���á� */
    DDS_LogQosPolicy dds_log;
    /**   
     * @brief   ������ֵʹ��DMA����memcpy���������洢�ռ䡣
     *
     * @note    ���ڻ����ƽ̨��ʹ�á�
     */
    DDS_ULong min_dma_copy_size;
#ifdef _ZRDDS_RIO
    /** @brief   RapidIO���á� */
    DDS_RapidIOConfigQosPolicy rapidio_config;
#endif /* _ZRDDS_RIO */
#ifdef _ZRXMLINTERFACE
#ifdef _ZRXMLQOSINTERFACE
    /** @brief   QoS�����ļ�·�����á� */
    DDS_QosProfileQosPolicy qos_profile;
#endif // _ZRXMLQOSINTERFACE
#endif /* _ZRXMLINTERFACE */
#ifdef _ZRDDS_INCLUDE_ENABLE_SYSTEM_CONFIGURE
    DDS_PropertyQosPolicy property;
#endif /* _ZRDDS_INCLUDE_ENABLE_SYSTEM_CONFIGURE */
}DDS_DomainParticipantFactoryQos;

#endif /* DomainParticipantFactoryQos_h__*/
