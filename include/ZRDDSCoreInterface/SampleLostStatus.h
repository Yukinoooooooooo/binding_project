/**
 * @file:       SampleLostStatus.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#if !defined(_SAMPLELOSTSTATUS_H)
#define _SAMPLELOSTSTATUS_H

#include "OsResource.h"
#include "SequenceNumber_t.h"
#include "InstanceHandle_t.h"

/**
 * @struct DDS_SampleLostStatus
 *
 * @ingroup CoreStatusStruct
 *
 * @brief   ������ʧ״̬��
 *
 * @details �����ݶ��߼�⵽����������ʧʱ�޸Ĵ�״̬����ɸ�״̬�Ŀ��ܵ�ԭ�����£���ȡ��״̬�ķ�ʽ�μ� @ref #DDS_StatusKind ��
 *          - �� DDS_RelialibityQosPolicy::kind == DDS_BEST_EFFORT_RELIABILITY �����£�  
 *              - �ײ㴫��Э������򽫵����Ӻ��������������ʧ��  
 *              - ���� DDS_ResourceLimitQosPolicy::max_instances �����ƣ�
 *              - ���� DDS_ResourceLimitQosPolicy::max_samples_per_instance �����ƣ�
 *          - �� DDS_RelialibityQosPolicy::kind == DDS_RELIABLE_RELIABILITY �����£�
 *              - �������ش�ʱ��ԭ�����Ϊ�ײ�Ĵ���Э�鶪������������Դ�������ݶ�������������������������Ѿ�������д��ɾ����QoS���ã���
 *              - ���� DDS_ResourceLimitQosPolicy::max_instances �����ƣ�
 *              - ���� DDS_ResourceLimitQosPolicy::max_samples_per_instance �����ƣ�
 *              - �����ݶ���ʹ�ܺ���֮ƥ�������д���Ѿ�������ɵ����ݣ�
 */

typedef struct DDS_SampleLostStatus
{
    /** @brief   �����ݶ����ۼ���������ʵ����ʧ�����������ĸ����� */
    DDS_Long total_count;
    /** @brief   ����һ�λ�ȡ��״̬�����λ�ȡ��״̬ʱ���ڣ����ݶ��߼�⵽������������ʧ�����ݸ����� */
    DDS_Long total_count_change;
    /** @brief   ��ʧ��������Դ��Ϣ�� */
    DDS_InstanceHandle_t writer_handle;
    /** @brief   ��ʧ���������к���Ϣ��[start_seq, end_seq]������������Ϊ��ʧ��*/
    DDS_SequenceNumber_t start_seq;
    /** @brief   ��ʧ���������к���Ϣ��[start_seq, end_seq]������������Ϊ��ʧ��*/
    DDS_SequenceNumber_t end_seq;
}DDS_SampleLostStatus;

#endif  /*_SAMPLELOSTSTATUS_H*/
