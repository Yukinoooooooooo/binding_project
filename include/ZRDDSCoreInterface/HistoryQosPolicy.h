/**
 * @file:       HistoryQosPolicy.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#ifndef HistoryQosPolicy_h__
#define HistoryQosPolicy_h__

#include "OsResource.h"

/**
 * @enum DDS_HistoryQosPolicyKind
 *
 * @ingroup CoreQosStruct 
 *
 * @brief   �������ݱ������͡�
 */

typedef enum DDS_HistoryQosPolicyKind
{
    /**
     * @brief   �������������������͡�
     *
     * @ingroup CoreQosStruct
     *
     * @details ������ΪĬ�����͡���������£�ZRDDS�᳢��Ϊÿ��ʵ���������µ��������������������ﵽ DDS_HistoryQosPolicy::depth ����ʱ��
     *          ZRDDS �������µ�����������ɵ���������ʵ������Ϊ������ʱ�����ܱ�֤���ԵĿɿ���
     *          
     *          ����Ϊ�����͵�����д�ߵĿɿ��Ա������£�
     *          - ��������һ������ʵ�������������� �ﵽ depth ֵ��������ʵ�����µ��������滻�����и�ʵ������ɵ�������  
     *          - ��ʱ��������ǵ���������δ��ƥ������ݶ��߽��գ�����������������ʧ�����ݶ��ߵ�������ʧ״̬�ᱻ����  
     *              ��DataReaderListener::on_sample_lost �Լ� DataReader::get_sample_lost_status��ȡ״̬����
     *          
     *          ����Ϊ�����͵����ݶ��ߵĿɿ��Ա������£�
     *          - ��������һ������ʵ�������������� �ﵽ depth ֵ��������ʵ�����µ��������滻�����и�ʵ������ɵ�������  
     *          - ��ʱ������滻������δ���û�ͨ�� DataReader::read/takeϵ�з�������ʱ���û����ᶪʧ���滻������
     */
    DDS_KEEP_LAST_HISTORY_QOS,

    /**
     * @brief   ���Ա������������������͡�
     *
     * @ingroup CoreQosStruct
     *
     * @details ����������ʹ�á����ԡ�һ������Ϊʵ�ʱ�������������� DDS_ResourceLimitsQosPolicy ��������Ϊ�ñ�������
     *          �������ڴ���Դ�ľ�������Ϊ������ʱ�� DDS_HistoryQosPolicy::depth ��Ա��Ч��
     *          
     *          ����Ϊ�����͵�����д�ߵĿɿ��Ա������£�
     *          - ��������һ������ʵ�������������� �ﵽ DDS_ResourceLimitsQosPolicy::max_samples_per_instance ֵ ��  
     *          - �����ɵ����������Ѿ����������ݶ��߽���ʱ������ʵ�����µ��������滻��ʵ���ڷ��Ͷ�������ɵ�������   
     *          - ���ʵ������ɵ�����û�б��������ݶ��߽���ʱ������д��һ��������ʵ���µ��������� DataWriter::write   
     *              ���������������ʱ���� DDS_ReliabilityQosPolicy::max_blocking_time ��������
     *
     *          ����Ϊ�����͵����ݶ��ߵĿɿ��Ա������£�
     *          - ��������һ������ʵ�������������� �ﵽ DDS_ResourceLimitsQosPolicy::max_samples_per_instanceֵ ��  
     *          - ���µ��������������ܾ�����ʱ���ݶ��ߵ������ܾ�״̬�ᱻ����
     *              �� DataReaderListener::on_sample_reject �Լ� DataReader::get_sample_reject_status ��ȡ״̬����
     *              ��ʱ��Ҫ�û�ͨ��DataReader::take ϵ�з����ڳ��洢�洢�ռ䣬ʹ���µ������ܹ��ύ���û���
     *              ע���ʱ������ɶ�������Ϊ���ܾ���������ͨ���ش��Ȼ������³����ύ���û���
     */
    DDS_KEEP_ALL_HISTORY_QOS
}DDS_HistoryQosPolicyKind;

/**
 * @struct DDS_HistoryQosPolicy
 *
 * @ingroup CoreQosStruct
 *
 * @brief   ��ʷ��������ʵ���������á�
 *
 * @details ��QoS��������������д���Լ����ݶ����ڱ��ش洢����ʷ������������QoS������ÿһ������ʵ����
 *          ��Ա | Ĭ��ֵ | ƥ������� | ��Ч�Լ�� | �����Լ�� | �ɱ��Լ��
 *          --- | --- | --- | --- | --- | ---
 *          #kind | ::DDS_KEEP_LAST_HISTORY_QOS | �� | �� | �� | ���ɱ�
 *          #depth | 1 | �� | #depth > 0 | #depth <= DDS_ResourceLimitsQosPolicy::max_samples_per_instance | ���ɱ�
 *          
 * @see DDS_ReliabilityQosPolicy DDS_ResourceLimitsQosPolicy 
 */

typedef struct DDS_HistoryQosPolicy 
{
    /** @brief   ����ʵ�����������������á� */
    DDS_HistoryQosPolicyKind kind;
    /** @brief   �� #kind == ::DDS_KEEP_LAST_HISTORY_QOS ����ʵ�����е���󳤶ȡ� */
    DDS_Long depth;
}DDS_HistoryQosPolicy;

#endif /* HistoryQosPolicy_h__*/
