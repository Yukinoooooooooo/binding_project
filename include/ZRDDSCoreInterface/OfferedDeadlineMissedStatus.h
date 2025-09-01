/**
 * @file:       OfferedDeadlineMissedStatus.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#if !defined(_OFFEREDDEADLINEMISSEDSTATUS_H)
#define _OFFEREDDEADLINEMISSEDSTATUS_H

#include "InstanceHandle_t.h"

#ifdef _ZRDDS_INCLUDE_DEADLINE_QOS

/**
 * @struct DDS_OfferedDeadlineMissedStatus
 * 
 * @ingroup CoreStatusStruct
 *
 * @brief   ����д�߶˽�ֹʱ��δ����״̬��
 *
 * @details ��״̬�ڷ����˼�⵽��ֹʱ��δ����ʱ�� DDS_DeadlineQosPolicy ������д���޸ĸ�״̬
 *          ����ȡ��״̬�ķ����μ� #DDS_StatusKind ��
 */

typedef struct DDS_OfferedDeadlineMissedStatus
{
    /** @brief   ��⵽Υ����ֹʱ����ܴ����� */
    DDS_Long total_count;
    /** @brief   ����һ�λ�ȡ��״̬�����λ�ȡ��ʱ����ڣ�Υ����ֹʱ��Ĵ����� */
    DDS_Long total_count_change;
    /** @brief   ���һ�μ�⵽Υ����ֹʱ�������ʵ���ı�ʶ�� */
    DDS_InstanceHandle_t last_instance_handle;
}DDS_OfferedDeadlineMissedStatus;
#endif /* _ZRDDS_INCLUDE_DEADLINE_QOS */

#endif  /*_OFFEREDDEADLINEMISSEDSTATUS_H*/
