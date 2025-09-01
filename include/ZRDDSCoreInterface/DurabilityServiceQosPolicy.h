/**
 * @file:       DurabilityServiceQosPolicy.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#ifndef DurabilityServiceQosPolicy_h__
#define DurabilityServiceQosPolicy_h__

#include "OsResource.h"
#include "Duration_t.h"
#include "HistoryQosPolicy.h"

/**
 * @struct DDS_DurabilityServiceQosPolicy
 *
 * @ingroup CoreQosStruct
 *
 * @brief   ��ʷ������Դ���á�
 *
 * @details �� #DDS_DurabilityQosPolicyKind ȡֵΪ ::DDS_TRANSIENT_DURABILITY_QOS
 *          ::DDS_PERSISTENT_DURABILITY_QOS ʱ����ʱ����д����Ҫ�������ʷ���ݵ�ʱ����Ҫ��������д��������������ڣ�
 *          ������д�߱�ɾ��ʱ����ʷ��������Ҫ���棬��ʱ��Ҫһ������ĳ־û�������Ϊ������д�߱�����ʷ���ݣ���QoS�����Ƹó־û�
 *          ����Ϊ������д�߱������ʷ���ݵ���Դ���ơ�
 *          ��Ա | Ĭ��ֵ | ƥ������� | ��Ч�Լ�� | �����Լ�� | �ɱ��Լ��
 *          --- | --- | --- | --- | --- | ---
 *          #service_cleanup_delay | ::ZERO_DURATION | �� | �� | �� | ���ɱ�
 *          #history_kind | ::DDS_KEEP_LAST_HISTORY_QOS | �� | �� | �� | ���ɱ�
 *          #history_depth | 1 | �� | #history_depth > 0 | �� | ���ɱ�
 *          #max_samples | #LENGTH_UNLIMITED | �� | #max_samples > 0 | �� | ���ɱ�
 *          #max_instances | #LENGTH_UNLIMITED | �� | #max_instances > 0 | �� | ���ɱ�
 *          #max_samples_per_instance | #LENGTH_UNLIMITED | �� | #max_samples_per_instance > 0 | �� | ���ɱ�
 *          
 */

typedef struct DDS_DurabilityServiceQosPolicy
{
    /**  
     * @brief   ���ƺ�ʱɾ���־û������б��������ʵ������Ϣ�� 
     *
     * @details ����������������ʱɾ����
     *          1. ����ʵ������ʾ��dispose����instance_state=NOT_ALIVE_DISPOSED��  
     *          2. ����NOT_ALIVE_DISPOSED״̬ʱ��û�л��ŵ�DataWriter��д�������ʵ���������������µ�WriterҪôע���˸�����ʵ����Ҫô���ٴ�  
     *          3. �ڼ�⵽ǰ������������������ #service_cleanup_delay ʱ�䡣
     */
    DDS_Duration_t service_cleanup_delay;
    /** @brief   Ϊÿ������ʵ���������ݵ����͡� */
    DDS_HistoryQosPolicyKind history_kind;
    /** @brief   �� #history_kind == ::DDS_KEEP_LAST_HISTORY_QOS ʱ��Ϊÿ������ʵ���������µ� #history_depth ������������*/
    DDS_Long history_depth;
    /** @brief   �� #history_kind == ::DDS_KEEP_ALL_HISTORY_QOS ʱ��Ϊ�����Ᵽ��������������޸����� */
    DDS_Long max_samples;
    /** @brief   �� #history_kind == ::DDS_KEEP_ALL_HISTORY_QOS ʱ��Ϊ�������±��������ʵ�����޸����� */
    DDS_Long max_instances;
    /** @brief   �� #history_kind == ::DDS_KEEP_ALL_HISTORY_QOS ʱ��Ϊ��������ÿ������ʵ����������������������ޡ� */
    DDS_Long max_samples_per_instance;
}DDS_DurabilityServiceQosPolicy;

#endif /* DurabilityServiceQosPolicy_h__*/
