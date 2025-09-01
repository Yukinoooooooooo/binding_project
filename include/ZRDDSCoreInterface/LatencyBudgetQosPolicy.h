/**
 * @file:       LatencyBudgetQosPolicy.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#ifndef LatencyBudgetQosPolicy_h__
#define LatencyBudgetQosPolicy_h__

#include "OsResource.h"
#include "Duration_t.h"

#ifdef _ZRDDS_INCLUDE_LATENCY_BUDGET_QOS

/**
 * @struct DDS_LatencyBudgetQosPolicy
 *
 * @ingroup CoreQosStruct
 *
 * @brief   ��ʱ�Ż����á�
 *
 * @details �������ɽ��ܵ������ӳ٣������ն�Ӧ�ñ�֪ͨ��ʱ��-�����˷��������ݵ�ʱ�䡣ֻ��һ����ZRDDS�ײ����ʾ��
 *          �����Ż����������磬������ #duration С����·���������ȼ���ߡ�
 *          ��Ա | Ĭ��ֵ | ƥ������� | ��Ч�Լ�� | �����Լ�� | �ɱ��Լ��
 *          --- | --- | --- | --- | --- | ---
 *          #duration | ::ZERO_DURATION | ����д��.#duration &lt;= ���ݶ���.#duration | #duration &gt;= #ZERO_DURATION | �� | �ɱ�
 *
 * @warning ZRDDS��δʵ�ָ�QoS�����ø�QoS��Ч������Ը�QoS���м�顣
 */

typedef struct DDS_LatencyBudgetQosPolicy
{
    /** @brief   �������ɽ��ܵ������ӳ١� */
    DDS_Duration_t duration;
}DDS_LatencyBudgetQosPolicy;

#endif //_ZRDDS_INCLUDE_LATENCY_BUDGET_QOS

#endif /* LatencyBudgetQosPolicy_h__*/
