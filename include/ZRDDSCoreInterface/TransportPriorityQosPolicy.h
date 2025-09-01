/**
 * @file:       TransportPriorityQosPolicy.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#ifndef TransportPriorityQosPolicy_h__
#define TransportPriorityQosPolicy_h__

#include "OsResource.h"
#include "ZRDDSCommon.h"

#ifdef _ZRDDS_INCLUDE_TRANSPORT_PRIORITY_QOS

/**
 * @struct DDS_TransportPriorityQosPolicy
 *
 * @ingroup CoreQosStruct
 *
 * @brief   �������ȼ����á�
 *
 * @details ���õ�ǰ�������ݵĴ������ȼ���
 *          
 * @warning ZRDDS��ǰδʵ�ָ�QoS��
 */

typedef struct DDS_TransportPriorityQosPolicy
{
    /** @brief   ���ȼ��� */
    DDS_Long value;
}DDS_TransportPriorityQosPolicy;

#endif /* _ZRDDS_INCLUDE_TRANSPORT_PRIORITY_QOS */

#endif /* TransportPriorityQosPolicy_h__*/
