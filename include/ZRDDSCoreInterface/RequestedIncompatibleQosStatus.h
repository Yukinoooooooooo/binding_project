/**
 * @file:       RequestedIncompatibleQosStatus.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#if !defined(_REQUESTEDINCOMPATIBLEQOSSTATUS_H)
#define _REQUESTEDINCOMPATIBLEQOSSTATUS_H

#include "OsResource.h"
#include "QosPolicyId_t.h"
#include "QosPolicyCount.h"

/**
 * @struct DDS_RequestedIncompatibleQosStatus
 *
 * @ingroup CoreStatusStruct
 *
 * @brief   ���ݶ��߶�QoS��ƥ��״̬��
 *
 * @details ���ݶ�������ͼ��Զ�˵�����д��ƥ��ʱ��⵽�������������QoS��Զ�˵�����д�߲�����ʱ��ı䱾״̬��
 *          ZRDDS��QoS�ļ����Լ��μ�ÿ��QoS����ϸ�������û���ȡ��״̬�ķ�ʽ�μ� #DDS_StatusKind ��
 */

typedef struct DDS_RequestedIncompatibleQosStatus
{
    /** @brief   ���ݶ��߼�⵽����д��QoS�����ݵ��ܴ����� */
    DDS_Long total_count;
    /** @brief   �Դ���һ�λ�ȡ��״̬��ʼ�����λ�ȡ��״̬ʱ��������д�߼�⵽���ݶ���QoS�����ݵĴ����� */
    DDS_Long total_count_change;
    /** @brief   ���һ������ƥ��QoS״̬��QoS��ʶ�� */
    DDS_QosPolicyId_t last_policy_id;
    /** @brief   ����ÿ�����͵�Qos���ͷֱ�ͳ�����𲻼���QoS���ܴ����� */
    DDS_QosPolicyCountSeq policies;
}DDS_RequestedIncompatibleQosStatus;

#endif  /*_REQUESTEDINCOMPATIBLEQOSSTATUS_H*/
