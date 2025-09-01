/**
 * @file:       PublicationMatchedStatus.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#if !defined(_PUBLICATIONMATCHEDSTATUS_H)
#define _PUBLICATIONMATCHEDSTATUS_H

#include "InstanceHandle_t.h"

/**
 * @struct DDS_PublicationMatchedStatus
 *
 * @ingroup CoreStatusStruct
 *
 * @brief   ����д�߶������ݶ��ߵ�ƥ��״̬��
 *
 * @details ����д�߶��������ݶ���ƥ��ɹ����߽�������ݶ���ƥ����޸ĸ�״̬����ȡ��״̬�ķ�ʽ�μ� #DDS_StatusKind ��
 */

typedef struct DDS_PublicationMatchedStatus
{
    /** @brief   ����д�������ݶ���ƥ���ܴ����������Ѿ����ƥ������ݶ��ߣ��� */
    DDS_Long total_count;
    /** @brief   ����һ�λ�ȡ��״̬�����λ�ȡ��״̬ʱ����ƥ���ܴ����ı仯�� */
    DDS_Long total_count_change;
    /** @brief    ��ǰ����д�������ݶ���ƥ��ĸ����� */
    DDS_Long current_count;
    /** @brief   ����һ�λ�ȡ��״̬�����λ�ȡ��״̬ʱ���ڵ�ǰƥ������ı仯�� */
    DDS_Long current_count_change;
    /** @brief   ��һ�������״̬�仯��Զ�����ݶ��ߵ�Ψһ��ʶ�� */
    DDS_InstanceHandle_t last_subscription_handle;
}DDS_PublicationMatchedStatus;

#endif  /*_PUBLICATIONMATCHEDSTATUS_H*/
