/**
 * @file:       DataReaderListener.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#if !defined(_DATAREADERLISTENER_H)
#define _DATAREADERLISTENER_H

#include "Listener.h"
#include "ZRDDSCppWrapper.h"
#include <stdio.h>

namespace DDS {
    
class DataReader;

/**
 * @class   DataReaderListener
 *
 * @ingroup CppListener
 *
 * @brief   ������Ϊ���ݶ��߼������ĸ��ࡣ
 *
 */

class DCPSDLL DataReaderListener : public Listener
{
public:
    virtual ~DataReaderListener(){}
#ifdef _ZRDDS_INCLUDE_DEADLINE_QOS

    /**
     * @fn  virtual void DataReaderListener::on_requested_deadline_missed(DataReader* reader, const RequestedDeadlineMissedStatus& status)
     *
     * @brief   �ײ� #DDS_REQUESTED_DEADLINE_MISSED_STATUS ״̬�Ļص��ӿڡ�
     *
     * @param [in,out]  reader  �ü��������������ݶ��ߡ�
     * @param   status          ��ǰ��״ֵ̬��
     */

    virtual void on_requested_deadline_missed(DataReader* reader, const RequestedDeadlineMissedStatus& status)
    {
        ZRDDS_UNUSED_PARAM(reader);
        ZRDDS_UNUSED_PARAM(status);
    }
#endif //_ZRDDS_INCLUDE_DEADLINE_QOS

    /**
     * @fn  virtual void DataReaderListener::on_data_available(DataReader *reader)
     *
     * @brief   ���µ������洢�����ݶ��ߵײ�ʱ�ص���
     *
     * @details �ûص��������µ��������������ݣ��û���Ҫͨ�� @ref read-take ϵ�з�������Ҫ���ȡ�������������ݡ�
     *
     * @param [in,out]  reader  �ü��������������ݶ��ߡ�
     */

    virtual void on_data_available(DataReader *reader)
    {
        ZRDDS_UNUSED_PARAM(reader);
    }

    /**
     * @fn  virtual void DataReaderListener::on_data_arrived(DataReader *reader, void* sample, const SampleInfo& info)
     *
     * @brief   ֱ��֪ͨ���ݵ��������best-effort�Ȳ���Ҫ���ݶ��߻������ݵĳ�����
     *
     * @param [in,out]  reader  �ü��������������ݶ��ߡ�
     * @param [in,out]  sample  �������ݡ�
     * @param   info            ������������Ϣ��
     */

    virtual void on_data_arrived(DataReader *reader, void* sample, const SampleInfo& info)
    {
        ZRDDS_UNUSED_PARAM(reader);
        ZRDDS_UNUSED_PARAM(sample);
        ZRDDS_UNUSED_PARAM(info);
    }

    /**
     * @fn  virtual void DataReaderListener::on_sample_rejected(DataReader *reader, const SampleRejectedStatus &status)
     *
     * @brief   �ײ� #DDS_SAMPLE_REJECTED_STATUS ״̬�Ļص��ӿڡ�
     *
     * @param [in,out]  reader  �ü��������������ݶ��ߡ�
     * @param   status          ��ǰ��״ֵ̬��
     */

    virtual void on_sample_rejected(DataReader *reader, const SampleRejectedStatus &status)
    {
        ZRDDS_UNUSED_PARAM(reader);
        ZRDDS_UNUSED_PARAM(status);
    }
#ifdef _ZRDDS_INCLUDE_LIVELINESS_QOS

    /**
     * @fn  virtual void DataReaderListener::on_liveliness_changed(DataReader *reader, const LivelinessChangedStatus &status)
     *
     * @brief   �ײ� #DDS_LIVELINESS_LOST_STATUS ״̬�Ļص��ӿڡ�
     *
     * @param [in,out]  reader  �ü��������������ݶ��ߡ�
     * @param   status          ��ǰ��״ֵ̬��
     */

    virtual void on_liveliness_changed(DataReader *reader, const LivelinessChangedStatus &status)
    {
        ZRDDS_UNUSED_PARAM(reader);
        ZRDDS_UNUSED_PARAM(status);
    }
#endif //_ZRDDS_INCLUDE_LIVELINESS_QOS

    /**
     * @fn  virtual void DataReaderListener::on_requested_incompatible_qos(DataReader *reader, const RequestedIncompatibleQosStatus &status)
     *
     * @brief   �ײ� #DDS_REQUESTED_INCOMPATIBLE_QOS_STATUS ״̬�Ļص��ӿڡ�
     *
     * @param [in,out]  reader  �ü��������������ݶ��ߡ�
     * @param   status          ��ǰ��״ֵ̬��
     */

    virtual void on_requested_incompatible_qos(DataReader *reader, const RequestedIncompatibleQosStatus &status)
    {
        ZRDDS_UNUSED_PARAM(reader);
        ZRDDS_UNUSED_PARAM(status);
    }

    /**
     * @fn  virtual void DataReaderListener::on_subscription_matched(DataReader *reader, const SubscriptionMatchedStatus &status)
     *
     * @brief   �ײ� #DDS_SUBSCRIPTION_MATCHED_STATUS ״̬�Ļص��ӿڡ�
     *
     * @param [in,out]  reader  �ü��������������ݶ��ߡ�
     * @param   status          ��ǰ��״ֵ̬��
     */

    virtual void on_subscription_matched(DataReader *reader, const SubscriptionMatchedStatus &status)
    {
        ZRDDS_UNUSED_PARAM(reader);
        ZRDDS_UNUSED_PARAM(status);
    }

    /**
     * @fn  virtual void DataReaderListener::on_sample_lost(DataReader *reader, const SampleLostStatus &status)
     *
     * @brief   �ײ� #DDS_SAMPLE_LOST_STATUS ״̬�Ļص��ӿڡ�
     *
     * @param [in,out]  reader  �ü��������������ݶ��ߡ�
     * @param   status          ��ǰ��״ֵ̬��
     */

    virtual void on_sample_lost(DataReader *reader, const SampleLostStatus &status)
    {
        ZRDDS_UNUSED_PARAM(reader);
        ZRDDS_UNUSED_PARAM(status);
    }
};

/**
 * @class   SimpleDataReaderListener
 *
 * @ingroup CppListener
 *
 * @brief   �����ݶ��߼��������࣬���ڼ��û�ȡ���������ݵĹ��̡�
 *
 * @tparam  T           ��������������������͡�
 * @tparam  TSeq        ������������������������С�
 * @tparam  TDataReader �����������õ������ݶ������͡�
 */

template<typename T, typename TSeq, typename TDataReader>
class SimpleDataReaderListener : public DataReaderListener
{
public:

    /**
     * @fn  virtual void SimpleDataReaderListener::on_data_available(DataReader *reader)
     *
     * @brief   �ײ������ݵ���ʱ������ȡ�������̣����ײ㵽�������ȫ��ȡ�������Դ˵��� on_process_sample ������
     *
     * @param [in,out]  reader  �����ݵ�������ݶ���ָ�롣
     */

    virtual void on_data_available(DataReader *reader)
    {
        TSeq data_values;
        SampleInfoSeq sample_infos;
        /* ת��Ϊ���Ͱ�ȫ�ӿ� */
        TDataReader* typedReader = (TDataReader*)reader;
        ReturnCode_t retCode = typedReader->take(data_values, sample_infos,
            LENGTH_UNLIMITED, ANY_SAMPLE_STATE, ANY_VIEW_STATE, ANY_INSTANCE_STATE);
        if (RETCODE_OK != retCode)
        {
            printf("take failed(%d).\n", retCode);
            return;
        }
        /* �������� */
        for (ZR_UINT32 i = 0; i < sample_infos._length; i++)
        {
            SampleInfo& info = sample_infos[i];
            /* �ж��Ƿ�Ϊ��Ч�ĸ������� */
            if (!info.valid_data)
            {
                continue;
            }
            T& sample = data_values[i];
            this->on_process_sample(reader, sample, info);
        }
        typedReader->return_loan(data_values, sample_infos);
    }

    /**
     * @fn  virtual void SimpleDataReaderListener::on_process_sample(DataReader* reader, const T& sample, const SampleInfo& info)
     *
     * @brief   ��������������������ʱ���ã�Ĭ����Ϊʱ��ӡһ����䣬�û�Ӧ��д���Ǹú�����
     *
     * @param [in,out]  reader  ������Ч�����ݶ���ָ�롣
     * @param   sample          ����������
     * @param   info            ��������������Ϣ��
     */

    virtual void on_process_sample(DataReader* reader, const T& sample, const SampleInfo& info)
    {
        ZRDDS_UNUSED_PARAM(reader);
        ZRDDS_UNUSED_PARAM(sample);
        ZRDDS_UNUSED_PARAM(info);
        printf("data received on reader(%p)\n", reader);
    }
};

} // namespace DDS

#endif  //_DATAREADERLISTENER_H
