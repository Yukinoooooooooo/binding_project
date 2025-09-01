/**
 * @file:       SubscriberListener.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#if !defined(_SUBSCRIBERLISTENER_H)
#define _SUBSCRIBERLISTENER_H

#include "DataReaderListener.h"

namespace DDS {

class Subscriber;
class DataReader;

/**
 * @class   SubscriberListener
 *
 * @ingroup CppListener
 *
 * @brief   ������Ϊ�����߼������ĸ��ࡣ
 */

class DCPSDLL SubscriberListener : public DataReaderListener
{
public:
    virtual ~SubscriberListener(){}

    /**
     * @fn  virtual void SubscriberListener::on_data_on_readers(Subscriber *the_subscriber)
     *
     * @brief   �ص� #DDS_DATA_ON_READERS_STATUS ״̬��
     *
     * @details �������ߵ���ʵ�����ݶ����������ݴﵽʱ�������߽����ڴ�״̬����������������״̬��
     *          - �����߼��������õĹ��ĵ�״̬���� #DDS_DATA_ON_READERS_STATUS ��  
     *          - �û����� DDS::Subscriber::notify_datareaders ������  
     *          - �û��ɹ����� DDS::SubscriberListener::on_data_available ������  
     *          - �û����ø�����������������ݶ��ߵ� @ref read-take ϵ�з�����
     *
     * @param [in,out]  the_subscriber  �ü����������Ķ����ߡ�
     */

    virtual void on_data_on_readers(Subscriber *the_subscriber)
    {
        ZRDDS_UNUSED_PARAM(the_subscriber);
    }
};

} // namespace DDS

#endif  //_SUBSCRIBERLISTENER_H
