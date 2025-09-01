/**
 * @file:       DefaultQos.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#ifndef DefaultQos_h__
#define DefaultQos_h__

#include "DomainParticipantFactoryQos.h"
#include "DomainParticipantQos.h"
#include "PublisherQos.h"
#include "SubscriberQos.h"
#include "DataWriterQos.h"
#include "DataReaderQos.h"
#include "TopicQos.h"
#include "ZRDDSCommon.h"

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @brief   ����� DDS_DomainParticipantFactoryQos ��ʾʹ��ZRDDSĬ�ϵ�QoS��
 *
 * @ingroup CoreVar
 */

DCPSDLL extern DDS_DomainParticipantFactoryQos DDS_DOMAINPARTICIPANT_FACTORY_QOS_DEFAULT;

/**
 * @brief   ����� DDS_DomainParticipantQos ��ʾʹ�ñ����ڸ�ʵ���е�Ĭ��QoS��
 *
 * @ingroup CoreVar
 */

DCPSDLL extern DDS_DomainParticipantQos DDS_DOMAINPARTICIPANT_QOS_DEFAULT;

/**
 * @brief   ����� DDS_PublisherQos ��ʾʹ�ñ����ڸ�ʵ���е�Ĭ��QoS��
 *
 * @ingroup CoreVar
 */

DCPSDLL extern DDS_PublisherQos DDS_PUBLISHER_QOS_DEFAULT;

/**
 * @brief   ����� DDS_SubscriberQos ��ʾʹ�ñ����ڸ�ʵ���е�Ĭ��QoS��
 *
 * @ingroup CoreVar
 */

DCPSDLL extern DDS_SubscriberQos DDS_SUBSCRIBER_QOS_DEFAULT;

/**
 * @brief   ����� DDS_DataWriterQos ��ʾʹ�ñ����ڸ�ʵ���е�Ĭ��QoS��
 *
 * @ingroup CoreVar
 */

DCPSDLL extern DDS_DataWriterQos DDS_DATAWRITER_QOS_DEFAULT;

/**
 * @brief   ����� DDS_DataReaderQos ��ʾʹ�ñ����ڸ�ʵ���е�Ĭ��QoS��
 *
 * @ingroup CoreVar
 */

DCPSDLL extern DDS_DataReaderQos DDS_DATAREADER_QOS_DEFAULT;

/**
 * @brief   ����� DDS_TopicQos ��ʾʹ�ñ����ڸ�ʵ���е�Ĭ��QoS��
 *
 * @ingroup CoreVar
 */

DCPSDLL extern DDS_TopicQos DDS_TOPIC_QOS_DEFAULT;

/**
 * @brief   ����� DDS_DataWriterQos ��ʾʹ������д�߹��������QoS��
 *
 * @ingroup CoreVar
 */

DCPSDLL extern DDS_DataWriterQos DDS_DATAWRITER_QOS_USE_TOPIC_QOS;

/**
 * @brief   ����� DDS_DataReaderQos ��ʾʹ�����ݶ��߹��������QoS��
 *
 * @ingroup CoreVar
 */

DCPSDLL extern DDS_DataReaderQos DDS_DATAREADER_QOS_USE_TOPIC_QOS;

/**
 * @fn  DCPSDLL void DDS_DefaultDomainParticipantFactoryQosInitial(DDS_DomainParticipantFactoryQos* self);
 *
 * @ingroup CoreBaseFunction
 *
 * @brief   ��ʼ��ָ�� DDS_DomainParticipantFactoryQos ΪDDSĬ�ϵ�ֵ��
 *
 * @pre     selfΪ��Ч��DDS_DomainParticipantFactoryQos��ָ�롣
 *
 * @param [in,out]  self    ָ��Ŀ�ꡣ
 */

DCPSDLL void DDS_DefaultDomainParticipantFactoryQosInitial(DDS_DomainParticipantFactoryQos* self);

/**
 * @fn  DCPSDLL DDS_Long DDS_DefaultDomainParticipantQosInitial(DDS_DomainParticipantQos* self);
 *
 * @ingroup CoreBaseFunction
 *
 * @brief   ��ʼ��ָ�� DDS_DomainParticipantQos ΪDDSĬ�ϵ�ֵ��
 *
 * @pre     selfΪ��Ч��DDS_DomainParticipantQos��ָ�롣
 *
 * @param [in,out]  self    ָ��Ŀ�ꡣ
 *
 * @return  0��ʾ��ʼ���ɹ��������ʾ��ʼ��ʧ�ܣ�ԭ�����Ϊ�ڴ�ռ䲻�㡣
 */

DCPSDLL DDS_Long DDS_DefaultDomainParticipantQosInitial(DDS_DomainParticipantQos* self);

/**
 * @fn  DCPSDLL void DDS_DefaultPublisherQosInitial(DDS_PublisherQos* self);
 *
 * @ingroup CoreBaseFunction
 *
 * @brief   ��ʼ��ָ�� DDS_PublisherQos ΪDDSĬ�ϵ�ֵ��
 *
 * @pre     selfΪ��Ч��DDS_PublisherQos��ָ�롣
 *
 * @param [in,out]  self    ָ��Ŀ�ꡣ
 */

DCPSDLL void DDS_DefaultPublisherQosInitial(DDS_PublisherQos* self);

/**
 * @fn  DCPSDLL void DDS_DefaultSubscriberQosInitial(DDS_SubscriberQos* self);
 *
 * @ingroup CoreBaseFunction
 *
 * @brief   ��ʼ��ָ�� DDS_PublisherQos ΪDDSĬ�ϵ�ֵ��
 *
 * @pre     selfΪ��Ч��DDS_PublisherQos��ָ�롣
 *
 * @param [in,out]  self    ָ��Ŀ�ꡣ
 */

DCPSDLL void DDS_DefaultSubscriberQosInitial(DDS_SubscriberQos* self);

/**
 * @fn  DCPSDLL void DDS_DefaultDataWriterQosInitial(DDS_DataWriterQos* self);
 *
 * @ingroup CoreBaseFunction
 *
 * @brief   ��ʼ��ָ�� DDS_PublisherQos ΪDDSĬ�ϵ�ֵ��
 *
 * @pre     selfΪ��Ч��DDS_PublisherQos��ָ�롣
 *
 * @param [in,out]  self    ָ��Ŀ�ꡣ
 */

DCPSDLL void DDS_DefaultDataWriterQosInitial(DDS_DataWriterQos* self);

/**
 * @fn  DCPSDLL void DDS_DefaultDataReaderQosInitial(DDS_DataReaderQos* self);
 *
 * @ingroup CoreBaseFunction
 *
 * @brief   ��ʼ��ָ�� DDS_PublisherQos ΪDDSĬ�ϵ�ֵ��
 *
 * @pre     selfΪ��Ч��DDS_PublisherQos��ָ�롣
 *
 * @param [in,out]  self    ָ��Ŀ�ꡣ
 */

DCPSDLL void DDS_DefaultDataReaderQosInitial(DDS_DataReaderQos* self);

/**
 * @fn  DCPSDLL void DDS_DefaultTopicQosInitial(DDS_TopicQos* self);
 *
 * @ingroup CoreBaseFunction
 *
 * @brief   ��ʼ��ָ�� DDS_PublisherQos ΪDDSĬ�ϵ�ֵ��
 *
 * @pre     selfΪ��Ч��DDS_PublisherQos��ָ�롣
 *
 * @param [in,out]  self    ָ��Ŀ�ꡣ
 */

DCPSDLL void DDS_DefaultTopicQosInitial(DDS_TopicQos* self);

/**
 * @fn  DCPSDLL void DDS_DomainParticipantFactoryQosDestroy(DDS_DomainParticipantFactoryQos* self);
 *
 * @ingroup CoreBaseFunction
 *
 * @brief   �ͷ� DDS_DomainParticipantFactoryQos �Ŀռ䡣
 *
 * @pre     selfΪ��Ч��DDS_DomainParticipantFactoryQos��ָ�롣
 *
 * @param [in,out]  self    ָ��Ŀ�ꡣ
 */

DCPSDLL void DDS_DomainParticipantFactoryQosDestroy(DDS_DomainParticipantFactoryQos* self);

/**
 * @fn  DCPSDLL void DDS_DomainParticipantQosDestroy(DDS_DomainParticipantQos* self);
 *
 * @ingroup CoreBaseFunction
 *
 * @brief   �ͷ� DDS_DomainParticipantQos �Ŀռ䡣
 *
 * @pre     selfΪ��Ч��DDS_DomainParticipantQos��ָ�롣
 *
 * @param [in,out]  self    ָ��Ŀ�ꡣ
 */

DCPSDLL void DDS_DomainParticipantQosDestroy(DDS_DomainParticipantQos* self);

/**
 * @fn  DCPSDLL void DDS_PublisherQosDestroy(DDS_PublisherQos* self);
 *
 * @ingroup CoreBaseFunction
 *
 * @brief   �ͷ� DDS_PublisherQos �Ŀռ䡣
 *
 * @pre     selfΪ��Ч��DDS_PublisherQos��ָ�롣
 *
 * @param [in,out]  self    ָ��Ŀ�ꡣ
 */

DCPSDLL void DDS_PublisherQosDestroy(DDS_PublisherQos* self);

/**
 * @fn  DCPSDLL void DDS_SubscriberQosDestroy(DDS_SubscriberQos* self);
 *
 * @ingroup CoreBaseFunction
 *
 * @brief   �ͷ� DDS_SubscriberQos �Ŀռ䡣
 *
 * @pre     selfΪ��Ч��DDS_SubscriberQos��ָ�롣
 *
 * @param [in,out]  self    ָ��Ŀ�ꡣ
 */

DCPSDLL void DDS_SubscriberQosDestroy(DDS_SubscriberQos* self);

/**
 * @fn  DCPSDLL void DDS_DataWriterQosDestroy(DDS_DataWriterQos* self);
 *
 * @ingroup CoreBaseFunction
 *
 * @brief   �ͷ� DDS_DataWriterQos �Ŀռ䡣
 *
 * @pre     selfΪ��Ч��DDS_DataWriterQos��ָ�롣
 *
 * @param [in,out]  self    ָ��Ŀ�ꡣ
 */

DCPSDLL void DDS_DataWriterQosDestroy(DDS_DataWriterQos* self);

/**
 * @fn  DCPSDLL void DDS_DataReaderQosDestroy(DDS_DataReaderQos* self);
 *
 * @ingroup CoreBaseFunction
 *
 * @brief   �ͷ� DDS_DataReaderQos �Ŀռ䡣
 *
 * @pre     selfΪ��Ч��DDS_DataReaderQos��ָ�롣
 *
 * @param [in,out]  self    ָ��Ŀ�ꡣ
 */

DCPSDLL void DDS_DataReaderQosDestroy(DDS_DataReaderQos* self);

/**
 * @fn  DCPSDLL void DDS_TopicQosDestroy(DDS_TopicQos* self);
 *
 * @ingroup CoreBaseFunction
 *
 * @brief   �ͷ� DDS_TopicQos �Ŀռ䡣
 *
 * @pre     selfΪ��Ч��DDS_TopicQos��ָ�롣
 *
 * @param [in,out]  self    ָ��Ŀ�ꡣ
 */

DCPSDLL void DDS_TopicQosDestroy(DDS_TopicQos* self);

/**
 * @fn  DCPSDLL ZR_BOOLEAN DomainParticipantFactoryQosAssign( DDS_DomainParticipantFactoryQos* self, const DDS_DomainParticipantFactoryQos* right);
 *
 * @brief   ������߹���QoS��ֵ������
 *
 * @param [in,out]  self    ��ֵĿ�Ķˡ�
 * @param   right           Դ�ˡ�
 *
 * @return  true��ʾ�ɹ���false��ʾʧ�ܡ�
 */

DCPSDLL ZR_BOOLEAN DomainParticipantFactoryQosAssign(DDS_DomainParticipantFactoryQos* self, const DDS_DomainParticipantFactoryQos* right);

/**
 * @fn  DCPSDLL ZR_BOOLEAN DomainParticipantQosAssign(DDS_DomainParticipantQos* self, const DDS_DomainParticipantQos* right);
 *
 * @brief   �������QoS��ֵ������
 *
 * @param [in,out]  self    ��ֵĿ�Ķˡ�
 * @param   right           Դ�ˡ�
 *
 * @return  true��ʾ�ɹ���false��ʾʧ�ܡ�
 */

DCPSDLL ZR_BOOLEAN DomainParticipantQosAssign(DDS_DomainParticipantQos* self, const DDS_DomainParticipantQos* right);

/**
 * @fn  DCPSDLL ZR_BOOLEAN PublisherQosAssign(DDS_PublisherQos* self, const DDS_PublisherQos* right);
 *
 * @brief   ������QoS��ֵ������
 *
 * @param [in,out]  self    ��ֵĿ�Ķˡ�
 * @param   right           Դ�ˡ�
 *
 * @return  true��ʾ�ɹ���false��ʾʧ�ܡ�
 */

DCPSDLL ZR_BOOLEAN PublisherQosAssign(DDS_PublisherQos* self, const DDS_PublisherQos* right);

/**
 * @fn  DCPSDLL ZR_BOOLEAN SubscriberQosAssign(DDS_SubscriberQos* self, const DDS_SubscriberQos* right);
 *
 * @brief   ������QoS��ֵ������
 *
 * @param [in,out]  self    ��ֵĿ�Ķˡ�
 * @param   right           Դ�ˡ�
 *
 * @return  true��ʾ�ɹ���false��ʾʧ�ܡ�
 */

DCPSDLL ZR_BOOLEAN SubscriberQosAssign(DDS_SubscriberQos* self, const DDS_SubscriberQos* right);

/**
 * @fn  DCPSDLL ZR_BOOLEAN TopicQosAssign(DDS_TopicQos* self, const DDS_TopicQos* right);
 *
 * @brief   ����QoS��ֵ������
 *
 * @param [in,out]  self    ��ֵĿ�Ķˡ�
 * @param   right           Դ�ˡ�
 *
 * @return  true��ʾ�ɹ���false��ʾʧ�ܡ�
 */

DCPSDLL ZR_BOOLEAN TopicQosAssign(DDS_TopicQos* self, const DDS_TopicQos* right);

/**
 * @fn  DCPSDLL ZR_BOOLEAN DataWriterQosAssign(DDS_DataWriterQos* self, const DDS_DataWriterQos* right);
 *
 * @brief   ����д��QoS��ֵ������
 *
 * @param [in,out]  self    ��ֵĿ�Ķˡ�
 * @param   right           Դ�ˡ�
 *
 * @return  true��ʾ�ɹ���false��ʾʧ�ܡ�
 */

DCPSDLL ZR_BOOLEAN DataWriterQosAssign(DDS_DataWriterQos* self, const DDS_DataWriterQos* right);

/**
 * @fn  DCPSDLL ZR_BOOLEAN DataReaderQosAssign(DDS_DataReaderQos* self, const DDS_DataReaderQos* right);
 *
 * @brief   ���ݶ���QoS��ֵ������
 *
 * @param [in,out]  self    ��ֵĿ�Ķˡ�
 * @param   right           Դ�ˡ�
 *
 * @return  true��ʾ�ɹ���false��ʾʧ�ܡ�
 */

DCPSDLL ZR_BOOLEAN DataReaderQosAssign(DDS_DataReaderQos* self, const DDS_DataReaderQos* right);

#ifdef __cplusplus
}
#endif

#endif /* DefaultQos_h__*/
