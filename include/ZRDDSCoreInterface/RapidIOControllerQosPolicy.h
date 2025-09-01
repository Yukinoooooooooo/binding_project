/**
 * @file:       RapidIOControllerQosPolicy.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#ifndef RapidIOControllerQosPolicy_h__
#define RapidIOControllerQosPolicy_h__

#include "OsResource.h"

#ifdef _ZRDDS_RIO

/**
 * @typedef struct DDS_RapidIOControllerQosPolicy
 *
 * @ingroup CoreQosStruct
 *
 * @brief RapidIOѡ��QoS��Ĭ��Ϊ0�����ɱ䡣
 */
typedef struct DDS_RapidIOControllerQosPolicy
{
    /** @brief ѡ�õ�RapidIO�������š� */
    DDS_Long controller_id;
}DDS_RapidIOControllerQosPolicy;

#endif /* _ZRDDS_RIO */

#endif /* RapidIOControllerQosPolicy_h__ */
