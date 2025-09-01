/**
 * @file:       InconsistentTopicStatus.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#ifndef InconsistentTopicStatus_h__
#define InconsistentTopicStatus_h__

#include "OsResource.h"

/**
 * @struct DDS_InconsistentTopicStatus
 *
 * @ingroup CoreStatusStruct
 *
 * @brief   ��������ͬһ��������������ͬ�����������Ͳ�ͬ������״̬��
 *          
 * @details ZRDDSҪ����ͬһ�����о�����ͬ�������Ƶ���������ͬ���������ư󶨣�������������������д�ߺ����ݶ��߽�����ƥ�䣬
 *          �������ܽ������ݽ�����ZRDDS�ڷ���ͬһ�����о�����ͬ����������������ͬ������ʱ��ͨ�������������������д�߻�
 *          ���ݶ��ߣ�ZRDDS���ᵥ���������⣩���ᴥ�����ؾ߱�������������������ⲻһ��״̬����ȡ�����μ� ::DDS_StatusKind ��
 */

typedef struct DDS_InconsistentTopicStatus
{
    /** @brief   �Ӹ����ⴴ����ʼ���������ⲻһ��״̬���ܴ����� */
    DDS_ULong total_count;
    /** @brief   ����һ�λ�ȡ��״̬�����λ�ȡʱ����ڴ������ⲻһ��״̬�������� */
    DDS_ULong total_count_change;
}DDS_InconsistentTopicStatus;

#endif /* InconsistentTopicStatus_h__*/
