/**
 * @file:       LifespanQosPolicy.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#ifndef LifespanQosPolicy_h__
#define LifespanQosPolicy_h__

#include "OsResource.h"
#include "Duration_t.h"

#ifdef _ZRDDS_INCLUDE_LIFESPAN_QOS

/**
 * @struct DDS_LifespanQosPolicy
 *
 * @ingroup CoreQosStruct
 *
 * @brief   ������Ч�����á�
 *
 * @details ��QoS������������д��ָ�������������ݵ���Ч�ڣ���������Ч�ڵ����������������ݶ�����ʷ���ݶ������Ƴ���
 *          ����ʱ�� = #duration + ����������Դʱ������ɵײ��ȡϵͳʱ������� DataWriter::write_w_timestamp �ṩ����
 *          ʹ�ø�QoS�ķ������Լ����ն�Ҫ��ʱ����Ч��ͬ�������δͬ�����ҵײ���Լ�⵽�����ݶ���ʹ�ý��յ���ʱ���������Դʱ������������ʱ�䡣
 *          ��Qos�������ڿ������ݶ��������洢�����д洢���������������� DDS_HistoryQosPolicy::kind == 
 *          #DDS_KEEP_ALL_HISTORY_QOS �� ���ڸ�QoS�����Ƴ�����Ч�ڵ����ݻ��ǻᱻ����ɾ���
 *          �����ݶ��ߵײ���洢��������д����� #duration ʱ�������������
 *          ��QoS������д��ʹ�ܺ�ɱ䣬�ı�֮�����Ч�ڽ������ڸı�󷢲�������������Ӱ���QoS�ı�֮ǰ���ݶ������յ������������� 
 *          ��Ա | Ĭ��ֵ | ƥ������� | ��Ч�Լ�� | �����Լ�� | �ɱ��Լ��
 *          --- | --- | --- | --- | --- | ---
 *          #duration | #INFINITE_DURATION | �� | #duration > #ZERO_DURATION | �� | �ɱ�
 */

typedef struct DDS_LifespanQosPolicy 
{
    /** @brief   ָ������д�ߵ�������Ч�ڡ� */
    DDS_Duration_t duration;
}DDS_LifespanQosPolicy;

#endif /* _ZRDDS_INCLUDE_LIFESPAN_QOS */

#endif /* LifespanQosPolicy_h__*/
