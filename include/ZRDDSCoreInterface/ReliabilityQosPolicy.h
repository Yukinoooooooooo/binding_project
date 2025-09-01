/**
 * @file:       ReliabilityQosPolicy.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#ifndef ReliabilityQosPolicy_h__
#define ReliabilityQosPolicy_h__

#include "OsResource.h"
#include "Duration_t.h"

/**
 * @typedef enum DDS_ReliabilityQosPolicyKind
 *
 * @ingroup CoreQosStruct
 *
 * @brief �ɿ����������͡�
 */
typedef enum DDS_ReliabilityQosPolicyKind
{
    /** @brief ������Ϊ���á� @ingroup CoreQosStruct */
    DDS_BEST_EFFORT_RELIABILITY_QOS = 1,
    /** @brief �ɿ����á� @ingroup CoreQosStruct */
    DDS_RELIABLE_RELIABILITY_QOS = 2
}DDS_ReliabilityQosPolicyKind;

/**
 * @struct DDS_ReliabilityQosPolicy
 *
 * @ingroup CoreQosStruct
 *
 * @brief �ɿ������á�
 *
 * @details ��ʹ��DDS�������ݴ���ʱ�����������ԭ��������ݶ�ʧ����ǿɿ����紫��ȣ���DDS����ͨ���ɿ��������������ݴ���ɿ��ԡ�
 *          ��Ա | Ĭ��ֵ | ƥ������� | ��Ч�Լ�� | �����Լ�� | �ɱ��Լ��
 *          --- | --- | --- | --- | --- | ---
 *          #kind | ����д��Ĭ��Ϊ #DDS_RELIABLE_RELIABILITY_QOS ���ݶ���Ĭ��Ϊ #DDS_BEST_EFFORT_RELIABILITY_QOS | ����д��.#kind >= ���ݶ���.#kind  | �� | �� | ���ɱ�
 *          #max_blocking_time | Duration_t{ 0, 100000000 } | �� | �� | �� | ���ɱ�
 *
 */
typedef struct DDS_ReliabilityQosPolicy
{
    /** @brief �ɿ����������͡� */
    DDS_ReliabilityQosPolicyKind kind;
    /** @brief �ɿ�ͨ���£�����д������Դ�������������ʱ�������ʱ���� */
    DDS_Duration_t max_blocking_time;
}DDS_ReliabilityQosPolicy;

#endif /* ReliabilityQosPolicy_h__*/
