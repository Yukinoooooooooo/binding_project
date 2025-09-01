/**
 * @file:       StatusKind.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#if !defined(_STATUSKIND_H)
#define _STATUSKIND_H

#include "ZROSDefine.h"

/**
 * @enum    DDS_StatusKind
 *
 * @ingroup CoreStatusStruct
 *
 * @brief   λ����ʵ��״̬���͡�
 *
 * @details Ϊ��ȡZRDDS�ײ��ͨ��״̬�Լ��ض����¼���ZRDDSʵ�壨����д�ߡ����ݶ��ߡ�����ȣ�����ά��һϵ��״̬��֪ͨ�ϲ��û���
 *          ״̬�ķ��༰������Ľӿ����£�
 *          ״̬ | ������ʵ�� | �������ӿ� | ��ѯ�ӿ� | ������QoS
 *          --- | --- | --- | --- | ---
 *          #DDS_INCONSISTENT_TOPIC_STATUS | ���� | DDS::TopicListener::on_inconsistent_topic | DDS::Topic::get_inconsistent_topic_status | ��
 *          #DDS_OFFERED_DEADLINE_MISSED_STATUS | ����д�� | DDS::DataWriterListener::on_offered_deadline_missed | DDS::DataWriter::get_offered_deadline_missed_status | DDS_DeadlineQosPolicy
 *          #DDS_OFFERED_INCOMPATIBLE_QOS_STATUS | ����д�� | DDS::DataWriterListener::on_offered_incompatible_qos | DDS::DataWriter::get_offered_incompatible_qos_status | ��
 *          #DDS_LIVELINESS_LOST_STATUS | ����д�� | DDS::DataWriterListener::on_liveliness_lost | DDS::DataWriter::get_liveliness_lost_status | DDS_LivelinessQosPolicy
 *          #DDS_PUBLICATION_MATCHED_STATUS | ����д�� | DDS::DataWriterListener::on_publication_matched | DDS::DataWriter::get_publication_matched_status | ��
 *          #DDS_REQUESTED_DEADLINE_MISSED_STATUS | ���ݶ��� | DDS::DataReaderListener::on_requested_deadline_missed | DDS::DataReader::get_requested_deadline_missed_status | DDS_DeadlineQosPolicy
 *          #DDS_REQUESTED_INCOMPATIBLE_QOS_STATUS | ���ݶ��� | DDS::DataReaderListener::on_requested_incompatible_qos | DDS::DataReader::get_requested_incompatible_qos_status | ��
 *          #DDS_SAMPLE_LOST_STATUS | ���ݶ��� | DDS::DataReaderListener::on_sample_lost | DDS::DataReader::get_sample_lost_status | DDS_HistoryQosPolicy DDS_ResourceLimitsQosPolicy
 *          #DDS_SAMPLE_REJECTED_STATUS | ���ݶ��� | DDS::DataReaderListener::on_sample_rejected | DDS::DataReader::get_sample_rejected_status | DDS_HistoryQosPolicy DDS_ResourceLimitsQosPolicy
 *          #DDS_LIVELINESS_CHANGED_STATUS | ���ݶ��� | DDS::DataReaderListener::on_liveliness_changed | DDS::DataReader::get_liveliness_changed_status | DDS_LivelinessQosPolicy
 *          #DDS_SUBSCRIPTION_MATCHED_STATUS | ���ݶ��� | DDS::DataReaderListener::on_subscription_matched | DDS::DataReader::get_subscription_matched_status | ��
 *
 *          ��ȡ���ݶ��ߵķ�����״̬���� #DDS_DATA_AVAILABLE_STATUS ���ķ�ʽ���£�
 *          1. �û�ͨ�����ݶ��߼�������������Ҫ��ȡ��״̬��������������״̬��ZRDDS�ڼ�⵽��״̬�仯ʱ��ͨ������������Ӧ�����ص��û���
 *          2. �û�ͨ�������������ݶ��ߵ���Ӧ������ѯ��״̬��
 *          3. ͬ���ȴ���״̬��
 *              -# �û����� DDS::DataReader::get_status_condition ��ȡ������ DDS::StatusCondition ��
 *              -# ���� DDS::StatusCondition::set_enabled_statuses (��Ҫ��ȡ��״̬������)�������ù��ĸ�״̬��
 *              -# ���� DDS::WaitSet::attach_condition ����������a�л�ȡ���� DDS::StatusCondition ���ӵ�һ��
 *               DDS::WaitSet �����ϣ������� DDS::WaitSet::wait ���������ȴ���״̬�ķ���;
 *              -# ZRDDS�ڼ�⵽��״̬�仯ʱ���⿪ DDS::WaitSet::wait ������������ʱ�û�ͨ������2��ȡ��״̬��
 *
 *          ��ȡ����д�ߵ�״̬�ķ�ʽ���£�
 *          1. �û�ͨ������д�߼�������������Ҫ��ȡ��״̬��������������״̬��ZRDDS�ڼ�⵽��״̬�仯ʱ��ͨ������������Ӧ�����ص��û���
 *          2. �û�ͨ��������������д�ߵ���Ӧ������ѯ��״̬��
 *          3. ͬ���ȴ���״̬��
 *              -# �û����� DDS::DataWriter::get_status_condition ��ȡ������ DDS::StatusCondition ��
 *              -# ���� DDS::StatusCondition::set_enabled_statuses (��Ҫ��ȡ��״̬������)�������ù��ĸ�״̬��
 *              -# ���� DDS::WaitSet::attach_condition ����������a�л�ȡ���� DDS::StatusCondition ���ӵ�һ��
 *               DDS::WaitSet �����ϣ������� DDS::WaitSet::wait ���������ȴ���״̬�ķ���;
 *              -# ZRDDS�ڼ�⵽��״̬�仯ʱ���⿪ DDS::WaitSet::wait ������������ʱ�û�ͨ������2��ȡ��״̬��
 */

typedef enum DDS_StatusKind
{
    /** @brief ���ⲻƥ��״̬�� @ingroup CoreStatusStruct */
    DDS_INCONSISTENT_TOPIC_STATUS = 0x0001 << 0,
#ifdef _ZRDDS_INCLUDE_DEADLINE_QOS
    /** @brief ����д�߽�ֹʱ��δ����״̬���͡� @ingroup CoreStatusStruct */
    DDS_OFFERED_DEADLINE_MISSED_STATUS = 0x0001 << 1,
    /** @brief ���ݶ��߽�ֹʱ��δ����״̬���͡� @ingroup CoreStatusStruct */
    DDS_REQUESTED_DEADLINE_MISSED_STATUS = 0x0001 << 2,
#endif /* _ZRDDS_INCLUDE_DEADLINE_QOS */
    /** @brief ����д�߶�QoS��ƥ��״̬���͡� @ingroup CoreStatusStruct */
    DDS_OFFERED_INCOMPATIBLE_QOS_STATUS = 0x0001 << 5,
    /** @brief ���ݶ��߶�QoS��ƥ��״̬���͡� @ingroup CoreStatusStruct */
    DDS_REQUESTED_INCOMPATIBLE_QOS_STATUS = 0x0001 << 6,
    /** @brief ����������ʧ״̬���͡� @ingroup CoreStatusStruct */
    DDS_SAMPLE_LOST_STATUS = 0x0001 << 7,
    /** @brief ���������ܾ�״̬���͡� @ingroup CoreStatusStruct */
    DDS_SAMPLE_REJECTED_STATUS = 0x0001 << 8,
    /** @brief ���������ݵ���״̬���͡� @ingroup CoreStatusStruct */
    DDS_DATA_ON_READERS_STATUS = 0x0001 << 9,
    /** @brief ���ݶ������ݵ���״̬���͡� @ingroup CoreStatusStruct */
    DDS_DATA_AVAILABLE_STATUS = 0x0001 << 10,
    /** @brief ����д�ߴ����״̬��ʧ״̬�� @ingroup CoreStatusStruct */
    DDS_LIVELINESS_LOST_STATUS = 0x0001 << 11,
    /** @brief ����д�ߴ���Ըı�״̬���͡� @ingroup CoreStatusStruct */
    DDS_LIVELINESS_CHANGED_STATUS = 0x0001 << 12,
    /** @brief ����д��ƥ��״̬���͡� @ingroup CoreStatusStruct */
    DDS_PUBLICATION_MATCHED_STATUS = 0x0001 << 13,
    /** @brief ���ݶ���ƥ��״̬���͡� @ingroup CoreStatusStruct */
    DDS_SUBSCRIPTION_MATCHED_STATUS = 0x0001 << 14
}DDS_StatusKind;

#endif  /* _STATUSKIND_H*/
