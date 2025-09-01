/**
 * @file:       RequestedDeadlineMissedStatus.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#if !defined(_REQUESTEDDEADLINEMISSEDSTATUS_H)
#define _REQUESTEDDEADLINEMISSEDSTATUS_H

#include "InstanceHandle_t.h"

#ifdef _ZRDDS_INCLUDE_DEADLINE_QOS
/**
 * @struct DDS_RequestedDeadlineMissedStatus
 *
 * @ingroup CoreStatusStruct
 *
 * @brief   ���ݶ��߶˽�ֹʱ��δ����״̬��
 *         
 * @details ��״̬�����ݶ��߼�⵽����ʵ���Ľ�ֹʱ������δ����ʱ�� DDS_DeadlineQosPolicy �����ݶ����޸ĸ�״̬��
 *          ��ȡ��״̬�ķ����μ� #DDS_StatusKind ��
 */

typedef struct DDS_RequestedDeadlineMissedStatus
{
    /** @brief   ��⵽Υ����ֹʱ����ܴ����� */
    DDS_Long total_count;
    /** @brief   ����һ�λ�ȡ��״̬�����λ�ȡ��ʱ����ڣ�Υ����ֹʱ��Ĵ����� */
    DDS_Long total_count_change;
    /** @brief   ���һ�μ�⵽Υ����ֹʱ�������ʵ���ı�ʶ�� */
    DDS_InstanceHandle_t last_instance_handle;
}DDS_RequestedDeadlineMissedStatus;

#endif /* _ZRDDS_INCLUDE_DEADLINE_QOS */

#endif  /*_REQUESTEDDEADLINEMISSEDSTATUS_H*/
