/**
 * @file:       DeadlineQosPolicy.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#ifndef DeadlineQosPolicy_h__
#define DeadlineQosPolicy_h__

#include "OsResource.h"
#include "Duration_t.h"

#ifdef _ZRDDS_INCLUDE_DEADLINE_QOS

/**
 * @struct DDS_DeadlineQosPolicy
 *
 * @ingroup CoreQosStruct 
 *
 * @brief   ��ֹʱ�����á�
 * 
 * @details ��Qos������ϣ�������Եķ���һ��������ÿ��ʵ��������ʱʹ�á�
 *          - �ڷ����ˣ����û�������У�ÿ������ʵ���� #period ʱ�������ٱ�����һ�Σ�ͨ�����ø�QoS��  
 *            �����ʵ�������з����˲������Ҫ��DDS����֪ͨ�û��� DDS_OfferedDeadlineMissedStatus ����
 *            �û��������ʵ����������Ʋ�������쳣��
 *          - �ڶ��Ķˣ����û�������У�ÿ������ʵ���� #period ʱ���ڶ����յ�һ�����ݣ�ͨ�����ø�QoS��  
 *            �����ʵ�������ж��Ķ˲������Ҫ��DDS����֪ͨ�û��� DDS_RequestedDeadlineMissedStatus ����
 *            �û��������ʵ����������Ʋ�������쳣��
 *          ��Ա | Ĭ��ֵ | ƥ������� | ��Ч�Լ�� | �����Լ�� | �ɱ��Լ��
 *          --- | --- | --- | --- | --- | ---
 *          #period | #INFINITE_DURATION | ����д��.#period <= ���ݶ���.#period | �� | #period >= DDS_TimeBasedFilterQosPolicy::minimum_separation | �ɱ�
 */

typedef struct DDS_DeadlineQosPolicy 
{
    /** @brief   ÿ��ʵ�����ݵ���С�������ڡ� */
    DDS_Duration_t period;
} DDS_DeadlineQosPolicy;

#endif /* _ZRDDS_INCLUDE_DEADLINE_QOS */

#endif /* DeadlineQosPolicy_h__*/
