/**
 * @file:       ThreadCoreAffinityQosPolicy.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#ifndef ThreadCoreAffinityQosPolicy_h__
#define ThreadCoreAffinityQosPolicy_h__

#include "OsResource.h"
#include "Duration_t.h"
#include "ZRBuiltinTypes.h"

/**
 * @struct DDS_ThreadCoreAffinityQosPolicy
 *
 * @ingroup CoreQosStruct
 *
 * @brief   �߳����������á�
 *
 * @details ��QoS�������� ZRDDS �ڲ��̵߳�CPU�����ԣ��ڶ��ƽ̨��ͨ����QoS�����߳���������ЩCPU���ϣ�������λ����
 *          ����ʽ���ø��߳��ܹ����е�CPU���ı�ţ�����0x01�ĵ�0�ֽ�Ϊ1����ʾ���߳̿���������0��CPU���ϣ�0xffff�ĵ�16λ
 *          Ϊ1����ʾ���߳̿���������0-15��CPU���ϡ�
 *          һ��������ߵ��̰߳���:
 *          - ���ɸ������̣߳� ������ DDS_ReceiverThreadConfigQosPolicy ���ã�  
 *          - һ����ʱ���߳�  
 *          - ���ɸ��첽�����̣߳���������ʹ���첽����ķ����ߵĸ��� DDS_PublishModeQosPolicy 
 *           ��Ա | Ĭ��ֵ | ƥ������� | ��Ч�Լ�� | �����Լ�� | �ɱ��Լ��
 *          --- | --- | --- | --- | --- | ---
 *          #receive_thread_default_affinity_mask | #MAX_UINT32_VALUE | �� | �� | �� | ���ɱ�
 *          #user_data_receive_thread_affinity_mask | #MAX_UINT32_VALUE | �� | �� | �� | ���ɱ�
 *          #builtin_data_receive_thread_affinity_mask | #MAX_UINT32_VALUE | �� | �� | �� | ���ɱ�
 *          #timer_thread_affinity_mask | #MAX_UINT32_VALUE | �� | �� | �� | ���ɱ�
 *          #async_send_thread_affinity_mask | #MAX_UINT32_VALUE | �� | �� | �� | ���ɱ�
 */

typedef struct DDS_ThreadCoreAffinityQosPolicy
{
    /** @brief   �����߳�Ĭ��ʹ�õ�����ֵ�� */
    DDS_ULong receive_thread_default_affinity_mask;
    /** @brief   �û����ݽ����߳�ʹ�õ�����ֵ�� */
    DDS_ULong user_data_receive_thread_affinity_mask;
    /** @brief   �������ݽ����߳�ʹ�õ�����ֵ�� */
    DDS_ULong builtin_data_receive_thread_affinity_mask;
    /** @brief   ��ʱ���߳�ʹ�õ�����ֵ�� */
    DDS_ULong timer_thread_affinity_mask;
    /** @brief   �첽�����߳�ʹ�õ�����ֵ�� */
    DDS_ULong async_send_thread_affinity_mask;
    /** @brief   ������PER_PORTʱ���ײ���ܻᴴ��������ڽ���TCP�����̣߳���ʱ�������к����ΰ��̡߳� */
    DDS_ULongSeq tcp_receive_thread_affinity_masks;
    /* @brief   Ĭ�������ֵΪfalse��TCP�����̰߳������к����ΰ�tcp_receive_thread_affinity_masks�����õĺˣ�
     *          tcp_receive_thread_affinity_masks�����õ�ֵȫ���󶨺���������̲߳����а�ˡ�  
     *          ������Ϊtrue������£������߳�ѭ����tcp_receive_thread_affinity_masks�����õ�ֵ*/
    ZR_BOOLEAN tcp_receive_thread_repeat_use_affinity_masks;
}DDS_ThreadCoreAffinityQosPolicy;

#endif /* ThreadCoreAffinityQosPolicy_h__*/
