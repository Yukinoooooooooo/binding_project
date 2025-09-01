/**
 * @file:       SubscriptionMatchedStatus.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#if !defined(_SUBSCRIPTIONMATCHEDSTATUS_H)
#define _SUBSCRIPTIONMATCHEDSTATUS_H

#include "OsResource.h" 
#include "InstanceHandle_t.h"

/**
 * @struct DDS_SubscriptionMatchedStatus
 *
 * @ingroup CoreStatusStruct
 *
 * @brief   ���ݶ��߶�������д�ߵ�ƥ��״̬��
 *
 * @details ���ݶ��߶���������д��ƥ��ɹ����߽��������д��ƥ����޸ĸ�״̬����ȡ��״̬�ķ�ʽ�μ� #DDS_StatusKind ��
 */

typedef struct DDS_SubscriptionMatchedStatus
{
    /** @brief   ���ݶ���������д��ƥ���ܴ����������Ѿ����ƥ�������д�ߣ��� */
    DDS_Long total_count;
    /** @brief   ����һ�λ�ȡ��״̬�����λ�ȡ��״̬ʱ����ƥ���ܴ����ı仯�� */
    DDS_Long total_count_change;
    /** @brief    ��ǰ���ݶ���������д��ƥ��ĸ����� */
    DDS_Long current_count;
    /** @brief   ����һ�λ�ȡ��״̬�����λ�ȡ��״̬ʱ���ڵ�ǰƥ������ı仯�� */
    DDS_Long current_count_change;
    /** @brief   ��һ�������״̬�仯��Զ������д�ߵ�Ψһ��ʶ�� */
    DDS_InstanceHandle_t last_publication_handle;
}DDS_SubscriptionMatchedStatus;

#endif  /*_SUBSCRIPTIONMATCHEDSTATUS_H*/
