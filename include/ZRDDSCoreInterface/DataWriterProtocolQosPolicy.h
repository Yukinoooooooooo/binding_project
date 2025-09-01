/**
 * @file:       DataWriterProtocolQosPolicy.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#ifndef DataWriterProtocolQosPolicy_h__
#define DataWriterProtocolQosPolicy_h__

#include "OsResource.h"
#include "Duration_t.h"

/**
 * @struct DDS_RtpsReliableWriterProtocol
 *
 * @ingroup CoreQosStruct
 *
 * @brief ���ƿɿ�����д�ߵ������Ϊ��
 */
typedef struct DDS_RtpsReliableWriterProtocol
{
    /** @brief DataWriter��ʱ���������ļ���� */
    DDS_Duration_t heartbeat_period;
    /** @brief ������Ϊreliability/keep_allʱ��������δ���������������ڵȴ��ռ�ʱ���ײ㽫�Ը�ʱ�����ڷ���HB��Ϣ�� */
    DDS_Duration_t fastheartbeat_period;
    /** @brief ��δʹ�� */
    DDS_Long max_heartbeat_retries;
    /** 
     * @brief ��������д�����ݰ��а����������İ��������
     *        
     * @details ����д�����ݰ��п���ͬʱЯ����������ʹ�ø�QoSʱ��ÿ��max_samples/heartbeats_per_max_samples�����ݰ�ʱ��Я��һ����������
     *        ����max_samplesֵΪ��ǰDataWriter����󻺴�������������DDS_HistoryQosPolicy::kindΪDDS_KEEP_LAST_HISTORY_QOSʱ��ȡDDS_HistoryQosPolicy::depth��
     *        ��DDS_HistoryQosPolicy::kindΪDDS_KEEP_ALL_HISTORY_QOSʱ��ȡDDS_ResourceLimitsQosPolicy::max_samples_per_instance������ֵȡ0ʱ����ȡ1Ч����ͬ��������ȡ��ֵ�� 
     */
    DDS_Long heartbeats_per_max_samples;
}DDS_RtpsReliableWriterProtocol;

/**
 * @struct DDS_DataWriterProtocolQosPolicy
 *
 * @ingroup CoreQosStruct
 *
 * @brief ����д������RTPSЭ����ص���Ϊ���á�
 *
 * @details
 *          ��Ա | Ĭ��ֵ | ƥ������� | ��Ч�Լ�� | �����Լ�� | �ɱ��Լ��
 *          --- | --- | --- | --- | --- | ---
 *          #push_on_write | false | �� | �� | �� | ���ɱ�
 *          DDS_RtpsReliableWriterProtocol::heartbeat_period | DDS_Duration_t{3,0} | �� | �� | �� | ���ɱ�
 *          DDS_RtpsReliableWriterProtocol::fastheartbeat_period | DDS_Duration_t{0, 100 * 1000 * 1000} | �� | �� | �� | ���ɱ�
 *          DDS_RtpsReliableWriterProtocol::max_heartbeat_retries | #LENGTH_UNLIMITED | �� | �� | �� | ���ɱ�
 *          DDS_RtpsReliableWriterProtocol::heartbeats_per_max_samples | 8 | �� | DDS_RtpsReliableWriterProtocol::heartbeats_per_max_samples >= 0 | �� | ���ɱ�
 *
 */
typedef struct DDS_DataWriterProtocolQosPolicy
{
    /** @brief ��ʹ��TCP����ʱ�����ڿ������ݴ���SOCKET��TCP_NODELAYѡ�����Ϊtrueʱ���ײ㽫���ø�ѡ� */
    DDS_Boolean push_on_write;
    /** @brief ���ƿɿ�����д�ߵ������Ϊ�� */
    DDS_RtpsReliableWriterProtocol rtps_reliable_writer;
}DDS_DataWriterProtocolQosPolicy;

#endif /* DataWriterProtocolQosPolicy_h__*/
