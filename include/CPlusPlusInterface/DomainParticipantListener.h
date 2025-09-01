/**
 * @file:       DomainParticipantListener.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#if !defined(_DOMAINPARTICIPANTLISTENER_H)
#define _DOMAINPARTICIPANTLISTENER_H

#include "OsResource.h"
#include "PublisherListener.h"
#include "TopicListener.h"
#include "SubscriberListener.h"

namespace DDS {

/**
 * @class   DomainParticipantListener
 *
 * @ingroup CppListener
 *
 * @brief   ������Ϊ������߼������ĸ��ࡣ
 */

class DCPSDLL DomainParticipantListener :
    public PublisherListener,
    public TopicListener,
    public SubscriberListener
{
public:
    virtual ~DomainParticipantListener(){}

    /**
     * @fn  virtual void on_domain_received(ULong domainId)
     *
     * @brief   ����RTPXЭ��Ļص����μ�  DDS_DomainParticipantQos::domain_destination_addresses ��
     *
     * @param   domainId    �����յ� @e domainId ��������ߵ����ݡ�
     */

    virtual void on_domain_received(ULong domainId)
    {
         ZRDDS_UNUSED_PARAM(domainId);
    }
};

} // namespace DDS

#endif  //_DOMAINPARTICIPANTLISTENER_H
