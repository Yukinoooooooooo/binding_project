/**
 * @file:       ReaderDataLifecycleQosPolicy.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#ifndef ReaderDataLifecycleQosPolicy_h__
#define ReaderDataLifecycleQosPolicy_h__

#include "OsResource.h"
#include "Duration_t.h"

/**
 * @struct DDS_ReaderDataLifecycleQosPolicy
 *
 * @ingroup CoreQosStruct
 *
 * @brief   ���ݶ�������ʵ���������������á�
 *
 * @details �����ÿ������ݶ��ߺ�ʱ����Ǵ��״̬������ʵ����ռ�Ŀռ䡣������������ݶ��߿���Ҫ��黹���е�Ϊ����ʵ���������Դ��
 *          �����е������������ߵ�ʱ�����ݶ��߻���Ϊ����ʵ��ά�������һ��������״̬�������� 
 *          DDS_SampleInfo::instance_state Ϊ #DDS_NOT_ALIVE_NO_WRITERS_INSTANCE_STATE ���� 
 *          #DDS_NOT_ALIVE_DISPOSED_INSTANCE_STATE �����û�и�QoS���ᵼ����Щ�Ǵ�������ʵ����ռ�Ŀռ�������ڵĲ��������ݶ����С�
 *          ��Ա | Ĭ��ֵ | ƥ������� | ��Ч�Լ�� | �����Լ�� | �ɱ��Լ��
 *          --- | --- | --- | --- | --- | ---
 *          #autopurge_nowriter_samples_delay | #INFINITE_DURATION | �� | �� | �� | �ɱ�
 *          #autopurge_disposed_samples_delay | #INFINITE_DURATION | �� | �� | �� | �ɱ�
 *          #purge_instance_with_not_read_samples | true | �� | �� | �� | �ɱ�
 */

typedef struct DDS_ReaderDataLifecycleQosPolicy
{
    /** @brief   ����������ʵ����״̬��� #DDS_NOT_ALIVE_NO_WRITERS_INSTANCE_STATE ʱ���ݶ���ά�ָ�����ʵ����������Ϣ�����ʱ�䳤�ȡ� */
    DDS_Duration_t autopurge_nowriter_samples_delay;
    /** @brief   ����������ʵ����״̬��� #DDS_NOT_ALIVE_DISPOSED_INSTANCE_STATE ʱ���ݶ���ά�ָ�����ʵ����������Ϣ�����ʱ�䳤�ȡ� */
    DDS_Duration_t autopurge_disposed_samples_delay;
    /**  
     *  @brief   �Ƿ��������δ������������ʵ��������ֵΪfalse�������ʱ�䳤�ȵ��ﲢ������������ʵ��ʱ�������Ȼ����δ�����������ݲ������  
     *             ֱ���û�read/take��return_loan����ͷ�ʵ���ռ䡣Ĭ��Ϊtrue��
     */
    DDS_Boolean purge_instance_with_not_read_samples;
}DDS_ReaderDataLifecycleQosPolicy;

#endif /* ReaderDataLifecycleQosPolicy_h__*/
