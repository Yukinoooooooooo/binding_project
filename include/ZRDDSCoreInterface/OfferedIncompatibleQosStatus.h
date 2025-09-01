/**
 * @file:       OfferedIncompatibleQosStatus.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#if !defined(_OFFEREDINCOMPATIBLEQOSSTATUS_H)
#define _OFFEREDINCOMPATIBLEQOSSTATUS_H

#include "OsResource.h"
#include "QosPolicyId_t.h"
#include "QosPolicyCount.h"

/**
 * @struct DDS_OfferedIncompatibleQosStatus
 *
 * @ingroup CoreStatusStruct
 *
 * @brief   ����д�߶�QoS��ƥ��״̬��
 *  
 * @details ����д������ͼ��Զ�˵����ݶ���ƥ��ʱ��⵽�������ṩ��QoS��Զ�˵����ݶ��߲�����ʱ��ı䱾״̬��
 *          ZRDDS��QoS�ļ����Լ��μ�ÿ��QoS����ϸ�������û���ȡ��״̬�ķ�ʽ�μ� #DDS_StatusKind ��
 */

typedef struct DDS_OfferedIncompatibleQosStatus
{
    /** @brief   ����д�߼�⵽���ݶ���QoS�����ݵ��ܴ����� */
    DDS_Long total_count;
    /** @brief   �Դ���һ�λ�ȡ��״̬��ʼ�����λ�ȡ��״̬ʱ��������д�߼�⵽���ݶ���QoS�����ݵĴ����� */
    DDS_Long total_count_change;
    /** @brief   ���һ������ƥ��QoS״̬��QoS��ʶ�� */
    DDS_QosPolicyId_t last_policy_id;
    /** @brief   ����ÿ�����͵�Qos���ͷֱ�ͳ�����𲻼���QoS���ܴ����� */
    DDS_QosPolicyCountSeq policies;
}DDS_OfferedIncompatibleQosStatus;

#endif  /*_OFFEREDINCOMPATIBLEQOSSTATUS_H*/
