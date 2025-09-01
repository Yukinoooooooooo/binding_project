/**
 * @file:       TimeBasedFilterQosPolicy.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#ifndef TimeBasedFilterQosPolicy_h__
#define TimeBasedFilterQosPolicy_h__

#include "OsResource.h"
#include "Duration_t.h"

#ifdef _ZRDDS_INCLUDE_TIME_BASED_FILTER_QOS

/**
 * @struct DDS_TimeBasedFilterQosPolicy
 *
 * @ingroup CoreQosStruct
 *
 * @brief   ����ʱ��������á�
 *
 * @details ʹ�����ݶ����� #minimum_separation ʱ�������洢��֪ͨ�û�ͬһ������ʵ��һ������������ע��������Ϊ����ʵ����
 *          �ù������ڶ��Ķ���ɣ������˵�����ͨ������ȷ�ʽ�ӷ����˴��䵽���Ķˣ��ù��˶����ڼ�� 
 *          DDS_ResourceLimitQosPolicy::max_samples ֮�󣬼��������Դ����֮ǰ���Ҳ�����״̬������
 *          Ӧ�ó�����
 *          - �칹�����з�����ԶԶ���ڶ��Ķ��ٶ��ٶ�ʱ�� ���Ķ����ø�QoS������������ƥ������Ĵ����ٶȡ�
 *          - ��ͬ�����ݶ������ø�QoS��ƥ������Ĵ����ٶȡ�
 *          ��Ա | Ĭ��ֵ | ƥ������� | ��Ч�Լ�� | �����Լ�� | �ɱ��Լ��
 *          --- | --- | --- | --- | --- | ---
 *          #minimum_separation | #ZERO_DURATION | �� | #minimum_separation >= #ZERO_DURATION | DDS_DeadlineQosPolicy::period >= #minimum_separation | �ɱ�
 */

typedef struct DDS_TimeBasedFilterQosPolicy
{
    /** @brief   ָ��ͬһ����ʵ����������������Сʱ������ */
    DDS_Duration_t minimum_separation;
}DDS_TimeBasedFilterQosPolicy;

#endif /* _ZRDDS_INCLUDE_TIME_BASED_FILTER_QOS */

#endif /* TimeBasedFilterQosPolicy_h__*/
