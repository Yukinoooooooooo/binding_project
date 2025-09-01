/**
 * @file:       ResourceLimitsQosPolicy.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#ifndef ResourceLimitsQosPolicy_h__
#define ResourceLimitsQosPolicy_h__

#include "OsResource.h"
#include "ZRDDSCommon.h"

/**
 * @struct DDS_ResourceLimitsQosPolicy
 *
 * @ingroup CoreQosStruct
 *
 * @brief   ��Դ�������á�
 *
 * @details ���� DDS_HistoryQosPolicy::kind == #DDS_KEEP_ALL_HISTORY_QOS ��ʵ��� Qos ������ʵ���ڲ���
 *          ����д�ߡ����ݶ��ߣ����ڴ洢���ݵ���Դʹ��������û�и����ƣ���ZRDDS���ܻᵼ���ڴ������������
 *          �����ڴ治���ϵͳ�쳣��
 *           ��Ա | Ĭ��ֵ | ƥ������� | ��Ч�Լ�� | �����Լ�� | �ɱ��Լ��
 *          --- | --- | --- | --- | --- | ---
 *          #max_samples | #LENGTH_UNLIMITED | �� | #max_samples > 0 | #max_samples >= #max_samples_per_instance | ���ɱ�
 *          #max_instances | #LENGTH_UNLIMITED | �� | #max_instances > 0 | �� | ���ɱ�
 *          #max_samples_per_instance | #LENGTH_UNLIMITED | �� | #max_samples_per_instance > 0 | DDS_HistoryQosPolicy::depth <= #max_samples_per_instance < #max_samples | ���ɱ�
 *          #initial_samples | 1 | �� | #initial_samples >= 0 | �� | ���ɱ�
 */

typedef struct DDS_ResourceLimitsQosPolicy
{
    /**   
     * @brief   ��������ʵ���´洢��������������������� 
     *
     * @details �����ݶ��߶ˣ��յ��ײ�����������󣬽����ȼ��ײ�洢���������������Ƿ�ﵽ��ֵ�����δ�ﵽ���򽫱���
     *          �����ݶ��ߵĴ��洢�������ڻ�δ��������˳���Լ�������Դ���Ƶļ�飬������֪ͨ�û�����ȡ�����ݣ�������������д��
     *          �������������յ������洢�����������Ѿ��ﵽ��ֵ����ȡ���� DDS_ReliabilityQosPolicy::kind �Լ� 
     *          DDS_HistoryQosPolicy::kind �����ã��ײ㽫��ȡ��ͬ����Ϊ��
     *          -# #DDS_RELIABLE_RELIABILITY_QOS && #DDS_KEEP_ALL_HISTORY_QOS   
     *              - �������ܾ��� #DDS_REJECTED_BY_SAMPLES_LIMIT �����һ���������д�߶����·��͸�������ȡ��������д�ߵ�QoS���ã����������տ������±������Լ�  
     *                  ��֪ͨ�Ѿ�������д�߶˱��Ƴ������¸�������ʧ��
     *          -# #DDS_RELIABLE_RELIABILITY_QOS && #DDS_KEEP_LAST_HISTORY_QOS 
     *              - ���ݶ���������ʵ����Ψһ��ʶ��С˳����������õĿռ䣬ֻҪ����δ���û�����ȥ��DataReader::read/takeϵ�з�����
     *                  �����������������������ʧ�ܣ���ܾ��������� #DDS_REJECTED_BY_SAMPLES_LIMIT ����
     *          -# #DDS_BEST_EFFORT_RELIABILITY_QOS ����һ�������ͬ�Ĵ���ʽ��
     */
    DDS_Long max_samples;

    /**   
     * @brief   ��������ʵ������������� 
     *
     * @details �����ݶ��߶ˣ��ڴ洢���洢������������ʱ�������ȼ��ײ�洢����������ʵ���ĸ����Ƿ�ﵽ��ֵ���Ҵ��洢
     *          �������Ƿ����µ�����ʵ�����������������������������δ�ﵽ�����ƣ�������һ�������������������������
     *          ���ݶ��߽����������Ѿ����ڵ�����ʵ��������ʵ�������������
     *          - ����ʵ����״̬Ϊ #DDS_NOT_ALIVE_NO_WRITERS_INSTANCE_STATE ��  
     *          - ����ʵ���µ�������������Ϊ0��
     *          
     *          �����������ʵ��ʧ�ܣ������ڸ����ƣ����ݶ��߽�֪ͨ�û����������ܾ��� #DDS_REJECTED_BY_INSTANCE_LIMIT ���Լ���ʧ���Ҹ���������ͨ���ش���á�
     *          
     * @note    �������� #max_samples_per_instance ����ʱ�Ĵ���ʽ���ȴ�������ʵ���ռ�ʱ�ٴ洢��֪ͨ�û���
     *          ��ԭ�����ڣ�#max_samples_per_instance ���ƿ��������ݶ��߲�������������磺���� DataReader::take 
     *          ����������� #max_instances �����ƣ�����������д�߶˷���״̬���Ļ�����ĳ������ʵ���йص�����д�߱�Ϊ
     *          �Ǵ��״̬�����������ͬ�Ĵ���ʽ�����ڵ��� #max_samples ֮�󣬻ᵼ��״̬���ı��ܾ�������Զ�޷�������ơ�
     */
    DDS_Long max_instances;

    /**   
     * @brief   ��������ʵ���´洢���������������
     *
     * @details ��ֵֻ���� DDS_HistoryQosPolicy::kind == #DDS_KEEP_ALL_HISTORY_QOS ʱ��Ч�������ֵ�����ó�
     *          DDS_HistoryQosPolicy::depth ��ֵ�� ȡ����DDS_HistoryQosPolicy::kind �����ã��ײ㽫��ȡ��ͬ����Ϊ��
     *          -# #DDS_RELIABLE_RELIABILITY_QOS && #DDS_KEEP_ALL_HISTORY_QOS
     *              - �������ܾ��� #DDS_REJECTED_BY_SAMPLES_PER_INSTANCE_LIMIT �����������ݴ洢�ڴ��洢�����ȴ���һ�εĳ��Դ洢��֪ͨ�û���
     *          -# #DDS_RELIABLE_RELIABILITY_QOS && #DDS_KEEP_LAST_HISTORY_QOS
     *              - ���ݶ��߶˽�����������õĿռ䣬�����������������������ʵ���µ��������������δ����ɹ�����
     *                  ��������Χ�����е�����ʵ����������ʵ����Ψһ��ʶ��С˳�򣩣�ֻҪ����δ���û�����ȥ��
     *                  DataReader::read/takeϵ�з��������������������������������ʧ�����ȡ����һ����ͬ�Ĵ����߼���
     */
    DDS_Long max_samples_per_instance;

    /**   
     * @brief   �������е���������������
     *
     * @details �����ݶ��߶�ʹ�ã�Ϊ�Ż��������ܣ�ZRDDS�ײ�ά�������أ������ظ��Ĵ�����ɾ���������ó�Ա���������������ٵĸ������ڹ黹
     *          ��������ʱ�������������������ڸ�ֵʱ������������ռ�ռ佫�黹������ϵͳ����������������黹���������С�
     */
    DDS_Long initial_samples;
    /** @brief   �����ֶΡ� */
    DDS_Long max_prealloc_sample_size;
}DDS_ResourceLimitsQosPolicy;

#endif /* ResourceLimitsQosPolicy_h__*/
