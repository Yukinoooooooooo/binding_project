/**
 * @file:       DiscoveryConfigQosPolicy.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#ifndef DiscoveryConfigQosPolicy_h__
#define DiscoveryConfigQosPolicy_h__

#include "OsResource.h"
#include "Duration_t.h"

/**
 * @struct DDS_DiscoveryConfigQosPolicy
 *
 * @ingroup CoreQosStruct
 *
 * @brief   ����SPDPЭ�顣
 *
 * @details 
 *          ��Ա | Ĭ��ֵ | ƥ������� | ��Ч�Լ�� | �����Լ�� | �ɱ��Լ��
 *          --- | --- | --- | --- | --- | ---
 *          #participant_liveliness_assert_period | DDS_Duration_t(30, 0) | �� | ��������Ϊ ::INFINITE_DURATION ::ZERO_DURATION ::INVALID_DURATION | #participant_liveliness_assert_period < #participant_liveliness_lease_duration | ���ɱ� 
 *          #participant_liveliness_lease_duration | DDS_Duration_t(100, 0) | �� | ��������Ϊ ::ZERO_DURATION ::INVALID_DURATION |  #participant_liveliness_assert_period < #participant_liveliness_lease_duration | ���ɱ� 
 */

typedef struct DDS_DiscoveryConfigQosPolicy
{
    /** @brief   ZRDDS�Ը�ʱ��Ϊ��������DDS�鲥�з����������������Ϣ(Data(p)) */
    DDS_Duration_t participant_liveliness_assert_period;
    /** @brief   ZRDDS��֪������������ڸ�ʱ����δ�յ������Data(p)��������Ϊ���������ʧȥ���ԡ�*/
    DDS_Duration_t participant_liveliness_lease_duration;
}DDS_DiscoveryConfigQosPolicy;

#endif /* DiscoveryConfigQosPolicy_h__*/
