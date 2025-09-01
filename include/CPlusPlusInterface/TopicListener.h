/**
 * @file:       TopicListener.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#if !defined(_TOPICLISTENER_H)
#define _TOPICLISTENER_H

#include "Listener.h"
#include "ZRDDSCppWrapper.h"

namespace DDS {

class Topic;

/**
 * @class   TopicListener 
 *
 * @ingroup CppListener
 *
 * @brief   ������Ϊ����������ĸ��ࡣ
 */

class DCPSDLL TopicListener : public Listener
{
public:
    virtual ~TopicListener(){}

    /**
     * @fn  virtual void TopicListener::on_inconsistent_topic(Topic *the_topic, const InconsistentTopicStatus &status)
     *
     * @brief   �ײ� #DDS_INCONSISTENT_TOPIC_STATUS ״̬�Ļص��ӿڡ�
     *
     * @param [in,out]  the_topic  �ü��������������⡣
     * @param   status          ��ǰ��״ֵ̬��
     */

    virtual void on_inconsistent_topic(Topic *the_topic, const InconsistentTopicStatus &status)
    {
        ZRDDS_UNUSED_PARAM(the_topic);
        ZRDDS_UNUSED_PARAM(status);
    }
};

} // namespace DDS

#endif  //_TOPICLISTENER_H
