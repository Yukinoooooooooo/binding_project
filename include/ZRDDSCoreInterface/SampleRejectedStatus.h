/**
 * @file:       SampleRejectedStatus.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#if !defined(_SAMPLEREJECTEDSTATUS_H)
#define _SAMPLEREJECTEDSTATUS_H

#include "OsResource.h"
#include "SampleRejectedStatusKind.h"
#include "InstanceHandle_t.h"

/**
 * @struct DDS_SampleRejectedStatus
 *
 * @ingroup CoreStatusStruct
 *
 * @brief  �����������ܾ�״̬��
 *
 * @details �����ݶ��߼�⵽�����������ܾ�ʱ�޸Ĵ�״̬����ɸ�״̬�Ŀ��ܵ�ԭ�����£���ȡ��״̬�ķ�ʽ�μ� @ref #DDS_StatusKind ��
 *          - ���� DDS_ResourceLimitQosPolicy::max_samples �����ƣ�
 *          - ���� DDS_ResourceLimitQosPolicy::max_instances �����ƣ�
 *          - ���� DDS_ResourceLimitQosPolicy::max_samples_per_instance �����ƣ�
 */

typedef struct DDS_SampleRejectedStatus
{
    /** @brief   �����������ܾ����ܴ�������Ҫ�����ܸ�����ͬһ���������ܱ��ܾ���Σ���*/
    DDS_Long total_count;
    /** @brief   ����һ�λ�ȡ��״̬�����λ�ȡ��״̬ʱ���ڣ����ݶ��߼�⵽�������������ܾ��Ĵ����� */
    DDS_Long total_count_change;
    /** @brief   ���һ��������״̬�ĵ�ԭ�� */
    DDS_SampleRejectedStatusKind last_reason;
    /** @brief   ���һ��������״̬������������������ʵ����Ψһ��ʶ�� */
    DDS_InstanceHandle_t last_instance_handle;
}DDS_SampleRejectedStatus;

#endif  /*_SAMPLEREJECTEDSTATUS_H*/
