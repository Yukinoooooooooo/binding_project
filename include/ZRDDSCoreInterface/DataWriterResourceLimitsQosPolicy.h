/**
 * @file:       DataWriterResourceLimitsQosPolicy.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#ifndef DataWriterResourceLimitsQosPolicy_h__
#define DataWriterResourceLimitsQosPolicy_h__

#include "OsResource.h"

/**
 * @enum DDS_DataWriterResourceLimitsInstanceReplacementKind
 *
 * @ingroup CoreQosStruct
 *
 * @brief ��������д��ʵ���滻���ԡ�
 */
typedef enum DDS_DataWriterResourceLimitsInstanceReplacementKind
{
    /** @brief  ֻ�滻��ע����ʵ���� @ingroup CoreQosStruct */
    DDS_UNREGISTERED_INSTANCE_REPLACEMENT,
    /** @brief  ֻ�滻����ʵ���� @ingroup CoreQosStruct */
    DDS_ALIVE_INSTANCE_REPLACEMENT,
    /** @brief  ֻ�滻�����ٵ�ʵ���� @ingroup CoreQosStruct */
    DDS_DISPOSED_INSTANCE_REPLACEMENT,
    /** @brief  �����滻����ʵ���������������滻��ע����ʵ���� @ingroup CoreQosStruct */
    DDS_ALIVE_THEN_DISPOSED_INSTANCE_REPLACEMENT,
    /** @brief  �����滻�����ٵ�ʵ���������������滻����ʵ���� @ingroup CoreQosStruct */
    DDS_DISPOSED_THEN_ALIVE_INSTANCE_REPLACEMENT,
    /** @brief  �滻��������ע����ʵ���� @ingroup CoreQosStruct */
    DDS_ALIVE_OR_DISPOSED_INSTANCE_REPLACEMENT
}DDS_DataWriterResourceLimitsInstanceReplacementKind;

/**
 * @struct DDS_DataWriterResourceLimitsQosPolicy
 *
 * @ingroup CoreQosStruct
 *
 * @brief ����д����Դ����QoS���á�
 *
 * @details 
 *          ��Ա | Ĭ��ֵ | ƥ������� | ��Ч�Լ�� | �����Լ�� | �ɱ��Լ��
 *          --- | --- | --- | --- | --- | ---
 *          #initial_concurrent_blocking_threads | 1 | �� | #initial_concurrent_blocking_threads >= 0 | �� | ���ɱ�
 *          #max_concurrent_blocking_threads | #LENGTH_UNLIMITED | �� | #max_concurrent_blocking_threads >= #initial_concurrent_blocking_threads | �� | ���ɱ�
 *          #instance_replacement | #DDS_UNREGISTERED_INSTANCE_REPLACEMENT | �� | �� | �� | ���ɱ�
 *          #replace_empty_instances | false | �� | �� | �� | ���ɱ�
 *          #autoregister_instances | true | �� | �� | �� | ���ɱ�
 *          #max_batches | #LENGTH_UNLIMITED | �� | #max_batches > 0 | �� | ���ɱ�
 *
 */
typedef struct DDS_DataWriterResourceLimitsQosPolicy
{
    /** @brief ���õ�����д�������ﵽ����ʱ��ͬʱ�ȴ����̳߳�ʼ������������Ҫ�ȴ����߳�ռ��һ����Դ����QoS���ó�ʼ�������Դ���� */
    DDS_Long initial_concurrent_blocking_threads;
    /** @brief ���õ�����д�������ﵽ����ʱ��ͬʱ�ȴ����߳���������� */
    DDS_Long max_concurrent_blocking_threads;
    /** @brief ��������д��ʵ���滻���ԡ� */
    DDS_DataWriterResourceLimitsInstanceReplacementKind instance_replacement;
    /** @brief ���õ���Ҫ�滻ʵ��ʱ�Ƿ��滻��ʵ������δ������������ʵ���� */
    DDS_Boolean replace_empty_instances;
    /** @brief ���÷�������ʱ���Ƿ��Զ�ע��δע���ʵ�� */
    DDS_Boolean autoregister_instances;
    /** @brief ������������������Batch����������� */
    DDS_Long max_batches;
}DDS_DataWriterResourceLimitsQosPolicy;

#endif /* DataWriterResourceLimitsQosPolicy_h__*/
