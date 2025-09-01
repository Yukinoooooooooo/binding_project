/**
 * @file:       DomainParticipant.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#if !defined(_DOMAINPARTICIPANT_H)
#define _DOMAINPARTICIPANT_H

#include "Entity.h"
#include "Publisher.h"
#include "Subscriber.h"
#include "ContentFilteredTopic.h"
#include "MultiTopic.h"
#include "DomainParticipantListener.h"
#include "ZRDDSCppWrapper.h"
#include "TypeSupport.h"

namespace DDS {

/**
 * @class   DomainParticipant
 *
 * @ingroup CppDomain
 *
 * @brief   ��������������ʵ�塣
 *      
 * @details ���������Ҫ�ṩ���½ӿڹ��ܣ�
 *          - ʵ�幦�ܣ�  
 *          - ��Ϊ����ʵ�幤����  
 *              - ��Ϊ������ʵ�幤����  
 *              - ��Ϊ������ʵ�幤����  
 *              - ��Ϊ����ʵ�幤����
 *          - ����ʵ�����  
 *          - ͨ�Ź���  
 *          - ����Ϣ��ѯ��  
 *          - ����Թ���
 */

class DCPSDLL DomainParticipant : public Entity
{
public:

#ifdef _ZRXMLINTERFACE

#ifdef _ZRXMLENTITYINTERFACE

    /**
     * @fn virtual Subscriber* DomainParticipant::lookup_subscriber_by_name( const Char* name)=0;
     *
     * @brief �����־�ȷ����Subscriber
     *
     * @param name The name
     *
     * @return null if it fails, else a Subscriber*
     */
    virtual Subscriber* lookup_subscriber_by_name(
        const Char* name) = 0;

    /**
     * @fn virtual Publisher* DomainParticipant::lookup_publisher_by_name( const Char* name)=0;
     *
     * @brief �����־�ȷ����Publisher
     *
     * @param name The name
     *
     * @return null if it fails, else a Publisher*
     */
    virtual Publisher* lookup_publisher_by_name(
        const Char* name) = 0;

    /**
     * @fn virtual Topic* DomainParticipant::lookup_topic_by_name( const Char* name) = 0;
     *
     * @brief �����־�ȷ����Topic
     *
     * @param name The name
     *
     * @return null if it fails, else a Topic*
     */
    virtual Topic* lookup_topic_by_name(
        const Char* name) = 0;

    /**
     * @fn virtual ReturnCode_t DomainParticipant::register_type_from_type_library( const Char* type_name, const Char* registered_name) = 0;
     *
     * @brief ��TypeLibraryע�����͡�
     *
     * @param type_name       ���Ϳ��е��������ơ�
     * @param registered_name ���ͱ�ע������ƣ����������ڴ�������ʱ�������͡�
     *
     * @return  ��ǰ���ܵķ���ֵ��
     *          - #DDS_RETCODE_OK :��ʾע��ɹ���
     *          - #DDS_RETCODE_BAD_PARAMETER :��ʾ�������ڴ�����ȱʧ������
     *          - #DDS_RETCODE_ERROR :��ʾ���ʧ�ܡ�
     */
    virtual ReturnCode_t register_type_from_type_library(
        const Char* type_name,
        const Char* registered_name) = 0;

    /**
     * @fn virtual ReturnCode_t DomainParticipant::unregister_type_from_type_library( const Char* registered_name) = 0;
     *
     * @brief ע��ָ�����������͡�
     *
     * @param registered_name ��ע�����͵����ƣ���Ӧע��ʱ�����ơ�
     *
     * @return  ��ǰ���ܵķ���ֵ��
     *          - #DDS_RETCODE_OK :��ʾע��ɹ���
     *          - #DDS_RETCODE_PRECONDITION_NOT_MET :ָ������δע�᣻
     *          - #DDS_RETCODE_ERROR :��ʾ���ʧ�ܡ�
     */
    virtual ReturnCode_t unregister_type_from_type_library(
        const Char* registered_name) = 0;

    /**
     * @fn virtual ReturnCode_t DomainParticipant::register_type_from_xml_string( const Char* xml_content) = 0;
     *
     * @brief ��XML�ַ���ע�����͡�
     *
     * @details �˴�ֻ��ָ���������ö����ܶ������ͣ������õ����ͱ����Ѿ����������Ϳ���
     *
     * @param xml_content ��XML�ַ�����ʾ�����͡�
     *
     * @return  ��ǰ���ܵķ���ֵ��
     *          - #DDS_RETCODE_OK :��ʾע��ɹ���
     *          - #DDS_RETCODE_BAD_PARAMETER :��ʾ�������ڴ�����ȱʧ������
     *          - #DDS_RETCODE_ERROR :��ʾע��ʧ�ܣ�����Ϊָ�������Ͳ����ڡ�
     */
    virtual ReturnCode_t register_type_from_xml_string(
        const Char* xml_content) = 0;

    /**
     * @fn virtual ReturnCode_t DomainParticipant::lookup_named_publishers( const Char* pattern, StringSeq& publisher_names) = 0;
     *
     * @brief �������Ʒ���pattern�޶��ķ����ߡ�
     *
     * @param pattern                  ����ģʽ������֧��*��?��*�������������������ַ���?�������ⵥ���ַ�
     * @param [in,out] publisher_names ���ҵõ��ķ����������б�
     *
     * @return ��ǰ���ܵķ���ֵ��
     *          - #DDS_RETCODE_OK :��ʾ���ҳɹ���
     *          - #DDS_RETCODE_BAD_PARAMETER :��ʾ�������ڴ�����ȱʧ������
     *          - #DDS_RETCODE_ERROR :��ʾ����ʧ�ܡ�
     */
    virtual ReturnCode_t lookup_named_publishers(
        const Char* pattern, StringSeq& publisher_names) = 0;

    /**
     * @fn virtual ReturnCode_t DomainParticipant::lookup_named_subscribers( const Char* pattern, StringSeq& subscriber_names) = 0;
     *
     * @brief �������Ʒ���pattern�޶��Ķ����ߡ�
     *
     * @param pattern                   ����ģʽ������֧��*��?��*�������������������ַ���?�������ⵥ���ַ�
     * @param [in,out] subscriber_names ���ҵõ��Ķ����������б�
     *
     * @return ��ǰ���ܵķ���ֵ��
     *          - #DDS_RETCODE_OK :��ʾ���ҳɹ���
     *          - #DDS_RETCODE_BAD_PARAMETER :��ʾ�������ڴ�����ȱʧ������
     *          - #DDS_RETCODE_ERROR :��ʾ����ʧ�ܡ�
     */
    virtual ReturnCode_t lookup_named_subscribers(
        const Char* pattern, StringSeq& subscriber_names) = 0;

    /**
     * @fn virtual ReturnCode_t DomainParticipant::lookup_named_topics( const Char* pattern, StringSeq& topic_names) = 0;
     *
     * @brief �������Ʒ���pattern�޶������⡣
     *
     * @param pattern              ����ģʽ������֧��*��?��*�������������������ַ���?�������ⵥ���ַ�
     * @param [in,out] topic_names ���ҵõ������������б�
     *
     * @return  ��ǰ���ܵķ���ֵ��
     *          - #DDS_RETCODE_OK :��ʾ���ҳɹ���
     *          - #DDS_RETCODE_BAD_PARAMETER :��ʾ�������ڴ�����ȱʧ������
     *          - #DDS_RETCODE_ERROR :��ʾ����ʧ�ܡ�
     */
    virtual ReturnCode_t lookup_named_topics(
        const Char* pattern, StringSeq& topic_names) = 0;

    /**
     * @fn virtual Publisher* DomainParticipant::create_publisher_from_xml_string( const Char* xml_content) = 0;
     *
     * @brief ��XML�ַ������������ߡ�
     *
     * @details ���е�DataWriterQos��UserData��PublisherQos��GroupData����֧��ʹ��String��ʽ��Sequence��ʽ����
     *          - String��ʽΪ���ַ���ֱ����Ϊvalue�ڵ��text
     *          - Sequence��ʽΪ��value����Sequenceʹ�ã���������sequenceMaxLength���ԣ�������ÿ��Ԫ����Ϊitemд��
     *
     * @param xml_content ��XML�ַ�����ʾ�ķ����ߡ�
     *
     * @return �����ɹ�ָ�򴴽��ɹ��ķ�����ʵ����󣬷��򷵻�NULL��ʧ�ܵ�ԭ�����Ϊ��
     *          - ����ռ�ʧ�ܻ��߳�ʼ����Դʧ�ܣ�����Ĵ�����Ϣ�μ���־��
     *          - QoS����Чֵ���ߺ��в�һ�µ�QoS��
     */
    virtual Publisher* create_publisher_from_xml_string(
        const Char* xml_content) = 0;

    /**
     * @fn virtual Subscriber* DomainParticipant::create_subscriber_from_xml_string( const Char* xml_content) = 0;
     *
     * @brief ��XML�ַ������������ߡ�
     *
     * @details ���е�DataReaderQos��UserData��SubscriberQos��GroupData����֧��ʹ��String��ʽ��Sequence��ʽ����
     *          - String��ʽΪ���ַ���ֱ����Ϊvalue�ڵ��text
     *          - Sequence��ʽΪ��value����Sequenceʹ�ã���������sequenceMaxLength���ԣ�������ÿ��Ԫ����Ϊitemд��
     *
     * @param xml_content ��XML�ַ�����ʾ�Ķ����ߡ�
     *
     * @return �����ɹ�ָ�򴴽��ɹ��Ķ�����ʵ����󣬷��򷵻�NULL��ʧ�ܵ�ԭ�����Ϊ��
     *          - ����ռ�ʧ�ܻ��߳�ʼ����Դʧ�ܣ�����Ĵ�����Ϣ�μ���־��
     *          - QoS����Чֵ���ߺ��в�һ�µ�QoS��
     */
    virtual Subscriber* create_subscriber_from_xml_string(
        const Char* xml_content) = 0;

    /**
     * @fn virtual Topic* DomainParticipant::create_topic_from_xml_string( const Char* xml_content) = 0;
     *
     * @brief ��XML�ַ����������⡣
     *
     * @details ���е� #TopicQos::topic_data ����֧��ʹ��String��ʽ��Sequence��ʽ����
     *          - String��ʽΪ���ַ���ֱ����Ϊvalue�ڵ��text
     *          - Sequence��ʽΪ��value����Sequenceʹ�ã���������sequenceMaxLength���ԣ�������ÿ��Ԫ����Ϊitemд��
     *
     * @param xml_content ��XML�ַ�����ʾ�����⡣
     *
     * @return �����ɹ�ָ�򴴽��ɹ��Ķ�����ʵ����󣬷��򷵻�NULL��ʧ�ܵ�ԭ�����Ϊ��
     *          - ����ռ�ʧ�ܻ��߳�ʼ����Դʧ�ܣ�����Ĵ�����Ϣ�μ���־��
     *          - QoS����Чֵ���ߺ��в�һ�µ�QoS��
     */
    virtual Topic* create_topic_from_xml_string(
        const Char* xml_content) = 0;
#endif // _ZRXMLENTITYINTERFACE

#ifdef _ZRXMLQOSINTERFACE
    /**
     * @fn virtual ReturnCode_t DomainParticipant::set_qos_with_profile( const Char* library_name, const Char* profile_name, const Char* qos_name)=0;
     *
     * @brief ��QoS�ֿ��ȡQoS���ò����õ��������
     *
     * @param library_name QoS������֣�������ΪNULL��
     * @param profile_name QoS���õ����֣�������ΪNULL��
     * @param qos_name     QoS�����֣�����ΪNULL����ת��Ϊdefault�ַ�����
     *
     * @return ��ǰ���ܵķ���ֵ���£�
     *         - #DDS_RETCODE_OK :��ʾ���óɹ���
     *         - #DDS_RETCODE_ERROR :��ʾδ֪�����µ����ô���
     */
    virtual ReturnCode_t set_qos_with_profile(
        const Char* library_name,
        const Char* profile_name,
        const Char* qos_name) = 0;

    /**
     * @fn virtual ReturnCode_t DomainParticipant::set_default_topic_qos_with_profile( const Char* library_name, const Char* profile_name, const Char* qos_name)=0;
     *
     * @brief ��QoS�ֿ��ȡ����QoS��������ΪĬ������QoS
     *
     * @param library_name QoS������֣�������ΪNULL��
     * @param profile_name QoS���õ����֣�������ΪNULL��
     * @param qos_name     QoS�����֣�����ΪNULL����ת��Ϊdefault�ַ�����
     *
     * @return ��ǰ���ܵķ���ֵ���£�
     *         - #DDS_RETCODE_OK :��ʾ���óɹ���
     *         - #DDS_RETCODE_ERROR :��ʾδ֪�����µ����ô���
     */
    virtual ReturnCode_t set_default_topic_qos_with_profile(
        const Char* library_name,
        const Char* profile_name,
        const Char* qos_name) = 0;

    /**
     * @fn virtual ReturnCode_t DomainParticipant::set_default_publisher_qos_with_profile( const Char* library_name, const Char* profile_name, const Char* qos_name)=0;
     *
     * @brief ��QoS�ֿ��ȡ������QoS��������ΪĬ�Ϸ�����QoS
     *
     * @param library_name QoS������֣�������ΪNULL��
     * @param profile_name QoS���õ����֣�������ΪNULL��
     * @param qos_name     QoS�����֣�����ΪNULL����ת��Ϊdefault�ַ�����
     *
     * @return ��ǰ���ܵķ���ֵ���£�
     *         - #DDS_RETCODE_OK :��ʾ���óɹ���
     *         - #DDS_RETCODE_ERROR :��ʾδ֪�����µ����ô���
     */
    virtual ReturnCode_t set_default_publisher_qos_with_profile(
        const Char* library_name,
        const Char* profile_name,
        const Char* qos_name) = 0;

    /**
     * @fn virtual ReturnCode_t DomainParticipant::set_default_subscriber_qos_with_profile( const Char* library_name, const Char* profile_name, const Char* qos_name)=0;
     *
     * @brief ��QoS�ֿ��ȡ������QoS��������ΪĬ�϶�����QoS
     *
     * @param library_name QoS������֣�������ΪNULL��
     * @param profile_name QoS���õ����֣�������ΪNULL��
     * @param qos_name     QoS�����֣�����ΪNULL����ת��Ϊdefault�ַ�����
     *
     * @return ��ǰ���ܵķ���ֵ���£�
     *         - #DDS_RETCODE_OK :��ʾ���óɹ���
     *         - #DDS_RETCODE_ERROR :��ʾδ֪�����µ����ô���
     */
    virtual ReturnCode_t set_default_subscriber_qos_with_profile(
        const Char* library_name,
        const Char* profile_name,
        const Char* qos_name) = 0;

    /**
     * @fn virtual Publisher* DomainParticipant::create_publisher_with_qos_profile( const Char* library_name, const Char* profile_name, const Char* qos_name, PublisherListener* listener, StatusKindMask mask) = 0;
     *
     * @brief ��QoS�ֿ��л�ȡ������QoS�����䴴�������ߡ�
     *
     * @param library_name  QoS������֣�������ΪNULL��
     * @param profile_name  QoS���õ����֣�������ΪNULL��
     * @param qos_name      QoS�����֣�����ΪNULL����ת��Ϊdefault�ַ�����
     * @param [in] listener Ϊ�÷��������õļ�������
     * @param mask          ����Ӧ�ó������Ȥ��״̬��ֻ��Ӧ�ó������Ȥ��״̬�����仯ʱ���Ż�֪ͨӦ�ó���
     *
     * @return �����ɹ�ָ�򴴽��ɹ��ķ�����ʵ����󣬷��򷵻�NULL��ʧ�ܵ�ԭ�����Ϊ��
     *          - ����ռ�ʧ�ܻ��߳�ʼ����Դʧ�ܣ�����Ĵ�����Ϣ�μ���־��
     *          - δ�ҵ�ָ����QoS�ȡ�
     */
    virtual Publisher* create_publisher_with_qos_profile(
        const Char* library_name,
        const Char* profile_name,
        const Char* qos_name,
        PublisherListener* listener,
        StatusKindMask mask) = 0;

    /**
     * @fn virtual Subscriber* DomainParticipant::create_subscriber_with_qos_profile( const Char* library_name, const Char* profile_name, const Char* qos_name, SubscriberListener* listener, StatusKindMask mask) = 0;
     *
     * @brief ��QoS�ֿ��л�ȡ������QoS�����䴴��������
     *
     * @param library_name  QoS������֣�������ΪNULL��
     * @param profile_name  QoS���õ����֣�������ΪNULL��
     * @param qos_name      QoS�����֣�����ΪNULL����ת��Ϊdefault�ַ�����
     * @param [in] listener Ϊ�ö��������õļ�������
     * @param mask          ����Ӧ�ó������Ȥ��״̬��ֻ��Ӧ�ó������Ȥ��״̬�����仯ʱ���Ż�֪ͨӦ�ó���
     *
     * @return �����ɹ�ָ�򴴽��ɹ��Ķ�����ʵ����󣬷��򷵻�NULL��ʧ�ܵ�ԭ�����Ϊ��
     *          - ����ռ�ʧ�ܻ��߳�ʼ����Դʧ�ܣ�����Ĵ�����Ϣ�μ���־��
     *          - δ�ҵ�ָ����QoS�ȡ�
     */
    virtual Subscriber* create_subscriber_with_qos_profile(
        const Char* library_name,
        const Char* profile_name,
        const Char* qos_name,
        SubscriberListener* listener,
        StatusKindMask mask) = 0;

    /**
     * @fn virtual Topic* DomainParticipant::create_topic_with_qos_profile( const Char* topic_name, const Char* type_name, const Char* library_name, const Char* profile_name, const Char* qos_name, TopicListener* listener, StatusKindMask mask) = 0;
     *
     * @brief ��QoS�ֿ��л�ȡ����QoS�����䴴�����⡣
     *
     * @param topic_name    ��������ơ�
     * @param type_name     �������������ơ�
     * @param library_name  QoS������֣�������ΪNULL��
     * @param profile_name  QoS���õ����֣�������ΪNULL��
     * @param qos_name      QoS�����֣�����ΪNULL����ת��Ϊdefault�ַ�����
     * @param [in] listener Ϊ���������õļ�������
     * @param mask          ����Ӧ�ó������Ȥ��״̬��ֻ��Ӧ�ó������Ȥ��״̬�����仯ʱ���Ż�֪ͨӦ�ó���
     *
     * @return �����ɹ�ָ�򴴽��ɹ�������ʵ����󣬷��򷵻�NULL��ʧ�ܵ�ԭ�����Ϊ��
     *          - ����ռ�ʧ�ܻ��߳�ʼ����Դʧ�ܣ�����Ĵ�����Ϣ�μ���־��
     *          - δ�ҵ�ָ����QoS�ȡ�
     */
    virtual Topic* create_topic_with_qos_profile(
        const Char* topic_name,
        const Char* type_name,
        const Char* library_name,
        const Char* profile_name,
        const Char* qos_name,
        TopicListener* listener,
        StatusKindMask mask) = 0;

#ifdef _ZRDDS_INCLUDE_AUTO_CREATED_PUB_SUB

    /**
     * @fn  virtual DataWriter* DomainParticipant::create_datawriter_with_topic_and_qos_profile( const Char* topicName, TypeSupport* typeSupport, const Char* library_name, const Char* profile_name, const Char* qos_name, DataWriterListener *dw_listener, StatusKindMask mask) = 0;
     *
     * @brief   �����Զ��������û������ߣ�����ָ���������Ƶ�����д�ߣ����������ƹ���������δ����ʱ�����Զ�������
     *          ���������Ѿ����������ⴴ������д�ߣ����øú����ȼ��� get_auto_created_publisher()->create_datawriter_with_topic_and_qos_profile ��
     *
     * @param   topicName           ����д�߹������������ơ�
     * @param [in,out]  typeSupport ����д�߹������������͵�����֧�ֵ����������㿽�����ͣ� ZeroCopyBytesTypeSupport::get_instance() ��
     * @param   library_name        QoS������֣�������ΪNULL��
     * @param   profile_name        QoS���õ����֣�������ΪNULL��
     * @param   qos_name            QoS�����֣�����ΪNULL����ת��Ϊdefault�ַ�����
     * @param [in,out]  dw_listener ����д�ߵļ�������
     * @param   mask                ���������롣
     *
     * @return  NULL��ʾʧ�ܣ����򷵻�����д��ָ�롣
     */

    virtual DataWriter* create_datawriter_with_topic_and_qos_profile(
        const Char* topicName,
        TypeSupport* typeSupport,
        const Char* library_name,
        const Char* profile_name,
        const Char* qos_name,
        DataWriterListener *dw_listener,
        StatusKindMask mask) = 0;

    /**
     * @fn  virtual DataReader* DomainParticipant::create_datareader_with_topic_and_qos_profile( const Char* topicName, TypeSupport* typeSupport, const Char* library_name, const Char* profile_name, const Char* qos_name, DataReaderListener *dr_listener, StatusKindMask mask) = 0;
     *
     * @brief   �����Զ��������û������ߣ�����ָ���������Ƶ����ݶ��ߣ����������ƹ���������δ����ʱ��
     *          ���Զ����������������Ѿ����������ⴴ�����ݶ��ߡ����øú����ȼ��� get_auto_created_subscriber()->create_datareader_with_topic_and_qos_profile ��
     *
     * @param   topicName           ���ݶ��߹������������ơ�
     * @param [in,out]  typeSupport ���ݶ��߹������������͵�����֧�ֵ����������㿽�����ͣ� ZeroCopyBytesTypeSupport::get_instance() ��
     * @param   library_name        QoS������֣�������ΪNULL��
     * @param   profile_name        QoS���õ����֣�������ΪNULL��
     * @param   qos_name            QoS�����֣�����ΪNULL����ת��Ϊdefault�ַ�����
     * @param [in,out]  dr_listener ���ݶ��ߵļ�������
     * @param   mask                ���������롣
     *
     * @return  NULL��ʾʧ�ܣ����򷵻����ݶ���ָ�롣
     */

    virtual DataReader* create_datareader_with_topic_and_qos_profile(
        const Char* topicName,
        TypeSupport* typeSupport,
        const Char* library_name,
        const Char* profile_name,
        const Char* qos_name,
        DataReaderListener *dr_listener,
        StatusKindMask mask) = 0;

#endif //_ZRDDS_INCLUDE_AUTO_CREATED_PUB_SUB

#endif // _ZRXMLQOSINTERFACE

#endif // _ZRXMLINTERFACE

#ifdef _ZRDDS_INCLUDE_AUTO_CREATED_PUB_SUB

    /**
     * @fn  virtual Publisher* DomainParticipant::get_auto_created_publisher() = 0;
     *
     * @brief   Ϊ���û�������������ߴ���ʱ��ʹ��Ĭ��QoS�Զ������û�ʹ�õķ����ߣ��ýӿ�Ϊ��ȡ���Զ������ķ����ߡ�
     *
     * @return  �ɹ������Զ������ķ�����ָ�룬ʧ�ܷ���NULL��
     */

    virtual Publisher* get_auto_created_publisher() = 0;

    /**
     * @fn  virtual Subscriber* DomainParticipant::get_auto_created_subscriber() = 0;
     *
     * @brief   Ϊ���û�������������ߴ���ʱ��ʹ��Ĭ��QoS�Զ������û�ʹ�õĶ����ߣ��ýӿ�Ϊ��ȡ���Զ������Ķ����ߣ�
     *          �Զ������Ķ����������ö����߲�ͬ�����ö��������ڹ������õ�Readerʵ�壬���ڷ��ֹ��̡�
     *
     * @return  �ɹ������Զ������Ķ�����ָ�룬ʧ�ܷ���NULL��
     */

    virtual Subscriber* get_auto_created_subscriber() = 0;

#endif //_ZRDDS_INCLUDE_AUTO_CREATED_PUB_SUB
    /**
     * @fn  virtual Subscriber* DomainParticipant::get_builtin_subscriber() = 0;
     *
     * @brief   ��ȡ�û�ʵ�巢�ֵ����ö����ߡ�
     *          
     * @details ����ʵ����ָ����DDS�м���ڲ����ݽ�����������Ϣ���������Ϣ�������⡢����д���Լ����ݶ��ߡ�
     *          Ϊ���ܹ���ȡ��������Ϣ������������ṩ�����ڲ������ߵĽӿڣ��û���ͨ�������ö����ߵĹ��ܻ�ȡ��Ҫ�ķ�����Ϣ��
     *          ����ʵ������������Զ���������ͨ���ýӿ���� DDS::Subscriber::lookup_datareader �ӿڻ�ȡ���õ�
     *          ���ݶ��ߣ�ʹ�����õ����ݶ��߳����������������û��Զ������ݶ��߲�֮ͬ�⣬�����������û��Զ������ݶ���һ�¡�
     *          �ṩ���û�ʹ�õ��������ݶ��߼���������������Ƽ���������������Ͳμ��±�
     *          �������ݶ��� | �������� | ��������
     *          --- | --- | ---
     *          DDS::ParticipantBuiltinTopicDataDataReader | #BUILTIN_PARTICIPANT_TOPIC_NAME | DDS_ParticipantBuiltinTopicData
     *          DDS::PublicationBuiltinTopicDataDataReader | #BUILTIN_PUBLICATION_TOPIC_NAME | DDS_PublicationBuiltinTopicData
     *          DDS::SubscriptionBuiltinTopicDataDataReader | #BUILTIN_SUBSCRIPTION_TOPIC_NAME | DDS_SubscriptionBuiltinTopicData
     *          ��ȡ��������ʵ�岻Ӧ��ɾ�����������ϵͳ�쳣������ʹ�õ����Ӳμ� @ref SetBuiltinListenerExample.cpp ��
     *
     * @return  ���ö����ߵ�ָ�룬ZRDDS��ʵ���У�ֻҪ�������δ��ɾ������ô����ֵһ����Ч��
     */

    virtual Subscriber* get_builtin_subscriber() = 0;

    /**
     * @fn  virtual ReturnCode_t DomainParticipant::get_discovered_participants(InstanceHandleSeq &discoved_handleList) = 0;
     *
     * @brief   ��ȡ��������߷��ֵ�Զ�̣��߼��ϣ�Ҳ�п�����ͬһ���ڵ㣬������ͬһ��Ӧ�ó����У�������ߵı�ʶ�б�
     *
     * @details ��ZRDDS�У����������ʹ�ܺ󣬻�ͨ������Э���Զ���֪ͬһ�����µ�������ߣ�����֮������ǰʵ�����Ϣ��
     *          �Խ�������/���Ĺ�ϵ��������߷���Զ��������ߵ�����������
     *          - ������ͬһ�����ڣ�  
     *          - δ���� #ignore_participant �ֶ�����Զ��������ߣ�
     *          
     *          �û�����ͨ�����ַ�ʽ��ȡ��ǰ��������Ѿ����ֵ��������������Ϣ��
     *          - ͬ����ʽ���û�����Ҫ����Ϣʱ�����²����ȡ��    
     *              - �û����ñ��ӿڻ�ȡ���ֵ�������߱�ʶ��  
     *              - ���� #get_discovered_participant_data ͨ����һ���л�ȡ�ı�ʶ�鿴Զ��������ߵ���ϸ��Ϣ��
     *          - �첽�ص���ʽ  
     *              - ͨ�������������ݶ��ߣ� DDS::ParticipantBuiltinTopicDataDataReader ���ļ�������  
     *              - �ڼ������л�ȡ����Զ��������ߵ���ϸ��Ϣ��
     *          ͬ����ʽ�ŵ����ڱȽϼ򵥣�ȱ�����ڲ�ͬ��ʱ�Ļ�ȡ���µ�״̬������˵��Ҫ��ȡ��ʱ��״̬�Ĵ��۽ϸߣ�
     *          ͨ����Ƶ�ʵ���ѯ����
     *          �첽�ص���ʽ��ʹ����Ը��ӣ����ܹ���ʱ�Ļ�ȡ���µķ���״̬��
     *
     * @param [in,out]  discoved_handleList ���ڲ��������ڴ洢�ѷ��ֵ�������߱�ʶ�����û��ṩ�Ŀռ䲻��ʱ��
     *                  �ײ㽫���Զ����н������ݡ�
     *
     * @return  ��ǰ���ܵķ���ֵ��
     *          - #DDS_RETCODE_OK :��ʾ��ȡ�ɹ���  
     *          - #DDS_RETCODE_NOT_ENABLED :��ǰ�������δʹ�ܣ�
     *          - #DDS_RETCODE_ERROR :��ȡʧ�ܣ�����ʧ�ܣ�
     *
     * @see get_discovered_participant_data
     */

    virtual ReturnCode_t get_discovered_participants(InstanceHandleSeq &discoved_handleList) = 0;

    /**
     * @fn  virtual ReturnCode_t DomainParticipant::get_discovered_participant_data( ParticipantBuiltinTopicData &a_pd, const InstanceHandle_t& a_handle) = 0;
     *
     * @brief   �÷�����ѯָ����ʶ��������ߵ���ϸ��Ϣ��
     *
     * @param [in,out]  a_pd    ���ڲ��������ڴ洢��ȡ������ϸ��Ϣ��
     * @param   a_handle        ָ��������ߵ�Ψһ��ʶ���ñ�ʶ���Դ����¼����ط���ȡ��
     *                          - #get_discovered_participants   
     *                          - �������ݶ����ж�ȡ�������������������е� DDS_ParticipantBuiltinTopicData::_key   
     *                              ���� DDS_SampleInfo::instance_handle
     *                          - Զ��������ߵ� #get_instance_handle �����Ľ����
     *
     * @return  - #DDS_RETCODE_OK :��ʾ���ڲ����е���ϸ��Ϣ��Ч������ȡ�ɹ���
     *          - #DDS_RETCODE_NOT_ENABLED :���������δʹ�ܣ�
     *          - #DDS_RETCODE_PRECONDITION_NOT_MET :�ṩ�ı�ʶ��Ч��  
     *          - #DDS_RETCODE_ERROR :��ʾ��ȡʧ�ܣ����翽����������ʧ�ܣ�
     *
     * @see get_discovered_participants
     */

    virtual ReturnCode_t get_discovered_participant_data(
        ParticipantBuiltinTopicData &a_pd, 
        const InstanceHandle_t& a_handle) = 0;

    /**
     * @fn  virtual DomainId_t DomainParticipant::get_domain_id() = 0;
     *
     * @brief   ��ȡ�����������������
     *
     * @return  �������������ֵ��
     */

    virtual DomainId_t get_domain_id() = 0;

    /**
     * @fn  virtual DomainParticipantListener* DomainParticipant::get_listener() = 0;
     *
     * @brief   �÷�����ȡͨ�� #set_listener �������ߴ���ʱΪ����������õļ���������
     *
     * @return  ��ǰ���ܵķ���ֵ��
     *          - NULL��ʾδ���ü�������
     *          - �ǿձ�ʾӦ��ͨ�� #set_listener �����ڴ���ʱ���õļ���������
     */

    virtual DomainParticipantListener* get_listener() = 0;

    /**
     * @fn  virtual ReturnCode_t DomainParticipant::get_qos(DomainParticipantQos &qoslist) = 0;
     *
     * @brief   ��ȡ��������ߵ�QoS���á�
     *
     * @param [in,out]  qoslist ���ڲ��������ڱ���������ߵ�QoS���á�
     *
     * @return  ��ǰ���ܵķ���ֵ��
     *          - #DDS_RETCODE_OK :��ʾ��ȡ�ɹ���
     *          - #DDS_RETCODE_ERROR :��ʾʧ�ܣ�ԭ�����Ϊ����QoSʱ��������
     */

    virtual ReturnCode_t get_qos(DomainParticipantQos &qoslist) = 0;

    /**
     * @fn  virtual ReturnCode_t DomainParticipant::ignore_participant(const InstanceHandle_t &handle) = 0;
     *
     * @brief   �÷������ں���ָ����������ߣ�����ͬδ���ָ�������ߣ����Ը���������µ����ж��ġ�������Ϣ��
     *
     * @details ͨ�Ź����ܵĳ���ʹ�ó���Ϊ���ʿ��ƣ���ͨ�����������ϸ��Ϣ�жϸ�������߻�������д�ߡ����ݶ����Ƿ�߱�
     *          ��Ӧ��Ȩ�ޣ����磺�������Я���������Ƿ�����Ҫ�󣩣�����Ѿ�������ָ��������ߣ��򽫽⿪���������ߵ�ƥ�䡣
     *
     * @param   handle  �û���ʶԶ�˵�������ߣ���Դ�μ� #get_discovered_participant_data ��
     *
     * @return  �Ƿ���Գɹ���
     */

    virtual ReturnCode_t ignore_participant(const InstanceHandle_t &handle) = 0;

    /**
     * @fn  virtual ReturnCode_t DomainParticipant::set_listener( DomainParticipantListener *a_listener, const StatusKindMask &mask) = 0;
     *
     * @brief   ���ø�������ߵļ�������
     *
     * @details  ������������ԭ�м�������������ÿն����ʾ���ԭ�����õļ�������
     *
     * @param [in,out]  a_listener  Ϊ������������õļ���������
     * @param   mask                ����Ӧ�ó������Ȥ��״̬��ֻ��Ӧ�ó������Ȥ��״̬�����仯ʱ���Ż�֪ͨӦ�ó���
     *
     * @return  ��ǰ���Ƿ��� #DDS_RETCODE_OK ��ʾ���óɹ���
     */

    virtual ReturnCode_t set_listener(
        DomainParticipantListener *a_listener,
        const StatusKindMask &mask) = 0;

    /**
     * @fn  virtual ReturnCode_t DomainParticipant::set_qos(const DomainParticipantQos& qoslist) = 0;
     *
     * @brief   �÷�������Ϊ����������õ�QoS��
     *
     * @param   qoslist ��ʾ�û���Ҫ���õ�QoS���á�
     *
     * @details ����ʹ������ֵ DDS::DOMAINPARTICIPANT_QOS_DEFAULT ��ʾʹ�ô洢��������߹����е�QoS���á�
     *
     * @return  ��ǰ���ܵķ���ֵ��
     *          - #DDS_RETCODE_OK :��ʾ��ȡ�ɹ���
     *          - #DDS_RETCODE_BAD_PARAMETER :��ʾ @e qoslist ������Ч��QoS���ã�
     *          - #DDS_RETCODE_INCONSISTENT :��ʾ @e qoslist ���в����ݵ�QoS���ã�
     *          - #DDS_RETCODE_IMMUTABLE_POLICY :��ʾ�û������޸�ʹ�ܺ󲻿ɱ��QoS���ã�
     *          - #DDS_RETCODE_ERROR :��ʾδ����Ĵ��󣬴�����ϸ��Ϣ�������־�У�
     */

    virtual ReturnCode_t set_qos(const DomainParticipantQos& qoslist) = 0;

    /**
     * @fn  virtual Publisher* DomainParticipant::create_publisher( const PublisherQos &qoslist, PublisherListener *a_listener, const StatusKindMask &mask) = 0;
     *
     * @brief   �÷�������������´���һ����������ʵ�壬������QoS�Լ�������������Ӧ����Ҫ������ڷ������ݡ�
     *
     * @param   qoslist             ��ʾΪ�÷��������õ�QoS��#PUBLISHER_QOS_DEFAULT ����ʹ�ø���������б����Ĭ�ϵ�QoS��
     * @param [in,out]  a_listener  Ϊ�÷��������õļ�������
     * @param   mask                ����Ӧ�ó������Ȥ��״̬��ֻ��Ӧ�ó������Ȥ��״̬�����仯ʱ���Ż�֪ͨӦ�ó���
     *
     * @return  �����ɹ�ָ�򴴽��ɹ��ķ�����ʵ����󣬷��򷵻�NULL��ʧ�ܵ�ԭ�����Ϊ��
     *          - ����ռ�ʧ�ܻ��߳�ʼ����Դʧ�ܣ�����Ĵ�����Ϣ�μ���־��
     *          - @e qoslist ������Чֵ���ߺ��в�һ�µ�QoS��
     */

    virtual Publisher* create_publisher(
        const PublisherQos &qoslist,
        PublisherListener *a_listener,
        const StatusKindMask &mask) = 0;

    /**
     * @fn  virtual ReturnCode_t DomainParticipant::delete_publisher(Publisher *a_pub) = 0;
     *
     * @brief   ɾ��ָ���ķ�����ʵ�塣
     *
     * @param [in,out]  a_pub   ָ���ķ����ߡ�
     *
     * @return  ��ǰ���ܵķ���ֵ��
     *          - #DDS_RETCODE_BAD_PARAMETER :��ʾ����Ĳ�����Ч������Ч�ķ�����ָ�룻 
     *              - ��Ч�ķ�����ָ�룬���ǲ����ڸ�������ߴ��������ġ�
     *          - #DDS_RETCODE_PRECONDITION_NOT_MET :  
     *              - ��ʾ�÷����߲�����ɾ����������������ʵ������д��δɾ����  
     *              - ����ķ����߲��ɸ�������ߴ�����
     *          - #DDS_RETCODE_OK ����ʾɾ���ɹ���  
     *          - #DDS_RETCODE_ERROR ��δ����Ĵ�����ϸ��Ϣ�μ���־��
     */

    virtual ReturnCode_t delete_publisher(Publisher *a_pub) = 0;

    /**
     * @fn  virtual ReturnCode_t DomainParticipant::get_publishers( PublisherSeq &publisherList) = 0;
     *
     * @brief   ��ȡ��ǰδ��ɾ�����ɸ�������ߴ����ķ������б�
     *
     * @param [in,out]  publisherList   ���ڲ�����������䷢����ʵ�����
     *
     * @return  ��ǰ���ܵķ���ֵ���£�
     *          - #DDS_RETCODE_OK :���ڲ�����Ч����ʾ��ȡ�ɹ���  
     *          - #DDS_RETCODE_OUT_OF_RESOURCES ����ʾ�û��ṩ�Ŀռ䲻��������ʧ�ܣ�
     */

    virtual ReturnCode_t get_publishers(
        PublisherSeq &publisherList) = 0;

    /**
     * @fn  virtual Subscriber* DomainParticipant::create_subscriber( const SubscriberQos &qoslist, SubscriberListener *a_listener, const StatusKindMask &mask) = 0;
     *
     * @brief   �÷�������������´���һ����������ʵ�壬������QoS�Լ�������������Ӧ����Ҫ������ڶ������ݡ�
     *
     * @param   qoslist             ��ʾΪ�ö��������õ�QoS��#SUBSCRIBER_QOS_DEFAULT ����ʹ�ø���������б����Ĭ�ϵ�QoS��
     * @param [in,out]  a_listener  Ϊ�ö��������õļ�������
     * @param   mask                ����Ӧ�ó������Ȥ��״̬��ֻ��Ӧ�ó������Ȥ��״̬�����仯ʱ���Ż�֪ͨӦ�ó���
     *
     * @return  �����ɹ�ָ�򴴽��ɹ��Ķ�����ʵ����󣬷��򷵻�NULL��ʧ�ܵ�ԭ�����Ϊ��
     *          - ����ռ�ʧ�ܻ��߳�ʼ����Դʧ�ܣ�����Ĵ�����Ϣ�μ���־��
     *          - @e qoslist ������Чֵ���ߺ��в�һ�µ�QoS��
     */

    virtual Subscriber* create_subscriber(
        const SubscriberQos &qoslist,
        SubscriberListener *a_listener,
        const StatusKindMask &mask) = 0;

    /**
     * @fn  virtual ReturnCode_t DomainParticipant::delete_subscriber(Subscriber *a_sub) = 0;
     *
     * @brief   ɾ��ָ���Ķ�����ʵ�塣
     *
     * @param [in,out]  a_sub   ָ���Ķ����ߡ�
     *
     * @return  ��ǰ���ܵķ���ֵ��
     *          - #DDS_RETCODE_BAD_PARAMETER :��ʾ����Ĳ�����Ч������Ч�ķ�����ָ�룻
     *              - ��Ч�Ķ�����ָ�룬���ǲ����ڸ�������ߴ��������ġ�
     *          - #DDS_RETCODE_PRECONDITION_NOT_MET :
     *              - ��ʾ�ö����߲�����ɾ����������������ʵ�����ݶ���δɾ����
     *              - ����Ķ����߲��ɸ�������ߴ�����
     *          - #DDS_RETCODE_OK ����ʾɾ���ɹ���
     *          - #DDS_RETCODE_ERROR ��δ����Ĵ�����ϸ��Ϣ�μ���־��
     */

    virtual ReturnCode_t delete_subscriber(Subscriber *a_sub) = 0;

    /**
     * @fn  virtual ReturnCode_t DomainParticipant::get_subscribers( SubscriberSeq &subscriberList) = 0;
     *
     * @brief   ��ȡ��ǰδ��ɾ�����ɸ�������ߴ����Ķ������б�
     *
     * @param [in,out]  subscriberList   ���ڲ�����������䶩����ʵ�����
     *
     * @return  ��ǰ���ܵķ���ֵ���£�
     *          - #DDS_RETCODE_OK :���ڲ�����Ч����ʾ��ȡ�ɹ���
     *          - #DDS_RETCODE_OUT_OF_RESOURCES ����ʾ�û��ṩ�Ŀռ䲻��������ʧ�ܣ�
     */

    virtual ReturnCode_t get_subscribers(
        SubscriberSeq &subscriberList) = 0;

    /**
     * @fn  virtual Topic* DomainParticipant::create_topic( const Char* topic_name, const Char* type_name, const TopicQos &qoslist, TopicListener *a_listener, const StatusKindMask &mask) = 0;
     *
     * @brief   �÷�������������´���һ��������ʵ�壬����������Ψһ�����ơ��������������͡�QoS�Լ������������ڳ������ڵ����ݡ�
     *
     * @param   topic_name          �´�������������ƣ���֤�������������Ψһ��
     * @param   type_name           �´�����������������͵����ƣ����������Ʊ���������������ע����������ƣ�
     *                              ע������ע��������Լ����ͱ�������ƣ���ע��ķ���Ϊʹ�ñ��������ɵ�֧�ֽӿ� 
     *                              DDS::FooTypeSupport::get_instance().register_type ��
     * @param   qoslist             �´����������QoS���á�
     * @param [in,out]  a_listener  ������Ϣ�ص��ӿڡ�
     * @param   mask                �ص���Ϣ�������롣
     *
     * @return  �����ɹ���ָ�򴴽��ɹ���������󣬷��򷵻�NULL��ԭ��������£�
     *          - ����ռ�ʧ�ܣ�  
     *          - ����Ĳ����Ƿ��� @e topic_name == NULL @e type_name == NULL����  
     *          - �����QoS������Чֵ����QoS�к��в�һ�µ����ã�  
     *          - ����Ĳ���δע�᣻  
     *          - �����������������ͬ�����������⣻  
     *          - δ���������ϸ�μ���־��
     */

    virtual Topic* create_topic(
        const Char* topic_name,
        const Char* type_name,
        const TopicQos &qoslist,
        TopicListener *a_listener,
        const StatusKindMask &mask) = 0;

    /**
     * @fn  virtual Topic* DomainParticipant::create_topic_w_type_support( const Char* topic_name, TypeSupport* type_support, const TopicQos &qoslist, TopicListener *a_listener, const StatusKindMask &mask) = 0;
     *
     * @brief   �÷����� create_topic ��ͬ���ڴ�������֮ǰ������Ĭ�ϵ��������Զ�ע����������͡�
     *
     * @param   topic_name              �´�������������ƣ���֤�������������Ψһ��
     * @param [in,out]  type_support    �´���������������������͵�����֧�ֵ����������㿽�����ͣ� ZeroCopyBytesTypeSupport::get_instance() ��
     * @param   qoslist                 �´����������QoS���á�
     * @param [in,out]  a_listener      ������Ϣ�ص��ӿڡ�
     * @param   mask                    �ص���Ϣ�������롣
     *
     * @return  �����ɹ���ָ�򴴽��ɹ���������󣬷��򷵻�NULL��ԭ��������£�
     *          - ����ռ�ʧ�ܣ�  
     *          - ����Ĳ����Ƿ��� @e topic_name == NULL @e type_support == NULL����  
     *          - �����QoS������Чֵ����QoS�к��в�һ�µ����ã�  
     *          - ����Ĳ���δע�᣻  
     *          - �����������������ͬ�����������⣻  
     *          - δ���������ϸ�μ���־��
     */

    virtual Topic* create_topic_w_type_support(
        const Char* topic_name,
        TypeSupport* type_support,
        const TopicQos &qoslist,
        TopicListener *a_listener,
        const StatusKindMask &mask) = 0;
    /**
     * @fn  virtual ReturnCode_t DomainParticipant::delete_topic(Topic *a_topic) = 0;
     *
     * @brief   ɾ��ָ�����⡣
     *          
     * @details �ڵ��ø÷���֮ǰ��Ҫ��֤�����������������ʵ�壨����д�ߡ����ݶ��ߡ������ڹ��˵����⣩���Ѿ���ɾ����
     *          �������������ô���Ϊ0�Σ��û�ͨ�� #find_topic ������������������ô�����
     *          ��������������������᷵�ش��� #DDS_RETCODE_PRECONDITION_NOT_MET ��
     *
     * @param [in,out]  a_topic ָ�����������
     *
     * @return  ��ǰ���ܵķ���ֵ���£�
     *          - #DDS_RETCODE_OK :��ʾɾ���ɹ���  
     *          - #DDS_RETCODE_BAD_PARAMETER :@e a_topic ������Ч���������
     *          - #DDS_RETCODE_PRECONDITION_NOT_MET   
     *              - ��ʾָ�����ⲻ���ɸ�������ߴ����ģ�  
     *              - ������ɾ��������  
     */

    virtual ReturnCode_t delete_topic(Topic *a_topic) = 0;

    /**
     * @fn  virtual Topic* DomainParticipant::find_topic(const Char* topic_name, const Duration_t& timeout) = 0;
     *
     * @brief   �������������������ұ������⡣
     *          
     * @details �����������������Ѿ����ڣ���ֱ�ӷ��أ�����ȴ���ֱ����ʱ�����������������ⱻ������ע����ҳɹ�ʱ��
     *          �����Ӳ��ҳɹ����������������Ӧ���� #delete_topic ɾ����������
     *
     * @param   topic_name  �������ơ�
     * @param   timeout     ��ȴ�ʱ�䡣
     *
     * @return  ��ǰ���ܵķ���ֵ��
     *          - NULL��ʾ����ʧ�ܣ�ָ����ʱ����û���������������⡣   
     *          - ��NULL��ʾ���ҵ�������������ָ�����
     */

    virtual Topic* find_topic(const Char* topic_name, const Duration_t& timeout) = 0;

    /**
     * @fn  virtual TopicDescription* DomainParticipant::lookup_topicdescription(const Char* name) = 0;
     *
     * @brief   �����������ֲ��ұ��ش��������⣬���������Լ��������ݹ��˵����⡣
     *
     * @param   name    ָ����Ҫ���ҵ��������ơ�
     *
     * @return  ��ǰ���ܵķ���ֵ��
     *          - NULL��ʾ����ʧ�ܣ�������δ����ָ�������������⡣
     *          - ��NULL��ʾ���ҵ������������ĸ���ָ�롣
     */

    virtual TopicDescription* lookup_topicdescription(const Char* name) = 0;

    /**
     * @fn  virtual ReturnCode_t DomainParticipant::ignore_topic(const InstanceHandle_t &handle) = 0;
     *
     * @brief   ����ָ����ʶ��ʾ��������������ж���/������
     *          
     * @details ���������ݶ����Լ�����д�ߣ��������жԸ�����Ķ��Ļ��߷�����ƥ�䣬����Ѿ�ƥ������Ͽ������Ե�����д���Լ����ݶ���ƥ�䡣
     *
     * @param   handle  ��ʶָ�������⡣
     *
     * @return  ��ǰ���ܵķ���ֵ��
     *          - #DDS_RETCODE_NOT_ENABLED :��ʾδʹ�ܡ�
     *          - #DDS_RETCODE_ERROR :��ʾ���Դ���  
     *          - #DDS_RETCODE_OK :��ʾ���Գɹ���
     *
     * @warning ZRDDS��ǰδʵ�ָýӿڡ�
     */

    virtual ReturnCode_t ignore_topic(const InstanceHandle_t &handle) = 0;

    /**
     * @fn  virtual ReturnCode_t DomainParticipant::ignore_publication(const InstanceHandle_t &handle) = 0;
     *
     * @brief   ����ָ������д�ߣ������뱾�����ݶ���ƥ�䡣
     *          
     * @details ���Է����Ƕ��ڱ��ص����ݶ�����˵�ģ��ڸ÷���������֮�󣬸���������µ��������ݶ��߾������յ����Ը�����д�ߵ����ݣ�
     *          ͨ���������ǣ����� DDS::DataReader::get_matched_publications ����ȡ�Ѿ���Ե�Զ������д�ߵ�
     *          Ψһ��ʶ����ͨ�����ü�������ȡԶ������д�ߵ�Ψһ��ʶ���ٵ��øú��������ú��ԡ�
     *
     * @param   handle  ��ʶ��Ҫ�����Ե�����д�ߡ�
     *
     * @return  ��ǰ���ܵķ���ֵ��
     *          - #DDS_RETCODE_OK :��ʾ���Գɹ�������@e handle ָ��������д�߲����ڵ������
     *          - #DDS_RETCODE_BAD_PARAMETER :@e handle ������Ч������д�߱�ʶ��
     *          - #DDS_RETCODE_NOT_ENABLED :��ʾ���������δʹ�ܡ�
     *          - #DDS_RETCODE_ERROR :δ���������ϸ�μ���־��Ϣ��
     */

    virtual ReturnCode_t ignore_publication(const InstanceHandle_t &handle) = 0;

    /**
     * @fn  virtual ReturnCode_t DomainParticipant::ignore_subscription(const InstanceHandle_t &handle) = 0;
     *
     * @brief   ����ָ�����ݶ��ߣ������뱾������д��ƥ�䡣
     *
     * @details ���Զ����Ƕ��ڱ��ص�����д����˵�ģ��ڸ÷���������֮�󣬸���������µ���������д�߾�����������ݶ��߷������ݣ�
     *          ͨ���������ǣ����� DDS::DataWriter::get_matched_subscriptions ����ȡ�Ѿ���Ե�Զ�����ݶ��ߵ�
     *          Ψһ��ʶ����ͨ�����ü�������ȡԶ�����ݶ��ߵ�Ψһ��ʶ���ٵ��øú��������ú��ԡ�
     *
     * @param   handle  ��ʶ��Ҫ�����Ե����ݶ��ߡ�
     *
     * @return  ��ǰ���ܵķ���ֵ��
     *          - #DDS_RETCODE_OK :��ʾ���Գɹ�������@e handle ָ�������ݶ��߲����ڵ������
     *          - #DDS_RETCODE_BAD_PARAMETER :@e handle ������Ч�����ݶ��߱�ʶ��
     *          - #DDS_RETCODE_NOT_ENABLED :��ʾ���������δʹ�ܡ�
     *          - #DDS_RETCODE_ERROR :δ���������ϸ�μ���־��Ϣ��
     */

    virtual ReturnCode_t ignore_subscription(const InstanceHandle_t &handle) = 0;

    /**
     * @fn  virtual ReturnCode_t DomainParticipant::delete_contained_entities() = 0;
     *
     * @brief   �÷���ɾ��������ߴ���������ʵ�塣
     *          
     * @details ���������ߡ������ߡ����⡢�������ݹ��˵����⡣���Ҷ���ʵ����еݹ���� delete_contained_entities 
     *          ���������յ�ɾ����ʵ���������д�ߡ����ݶ��ߡ���ȡ�����ȣ�ɾ����ʵ�岻��������ʵ�塣
     *          �÷�����ȡ������Ϊ�Ĳ���ɾ����������ɾ��������ʵ�����ɾ��������в�����ɾ��������ʵ�壬�򷵻��ض��Ĵ����롣
     *
     * @return  ��ǰ���ܵķ���ֵ��
     *          - #DDS_RETCODE_OK :��ʾɾ���ɹ���
     *          - #DDS_RETCODE_PRECONDITION_NOT_MET :��ʾ�в���ʵ�岻����ɾ����������ɾ������ʵ�壻
     *          - #DDS_RETCODE_ERROR :��ʾδ���������ϸ�μ���־��
     */

    virtual ReturnCode_t delete_contained_entities() = 0;

    /**
     * @fn  virtual bool DomainParticipant::contains_entity(const InstanceHandle_t &a_handle) = 0;
     *
     * @brief   �÷������ڲ���ʵ���Ƿ���������ߵ���ʵ�塣
     *          
     * @details �÷�����ݹ���ԣ����ɲ��Ե�ʵ����������ߡ������ߡ����⡢���ݶ��ߡ�����д�ߡ�
     *
     * @param   a_handle    ��Ҫ���Ե�ʵ���ʶ��
     *
     * @return  true��ʾ���ڸ�������ߵ���ʵ�壬false��ʾ�����ڡ�
     */

    virtual bool contains_entity(const InstanceHandle_t &a_handle) = 0;

    /**
     * @fn  virtual ReturnCode_t DomainParticipant::set_default_subscriber_qos(const SubscriberQos &qoslist) = 0;
     *
     * @brief   �÷�������Ϊ�����߱����Ĭ��QoS���á�
     *
     * @details Ĭ�ϵ�QoS�ڴ����µĶ�����ʱָ��QoS����Ϊ DDS::SUBSCRIBER_QOS_DEFAULT ʱʹ�õ�QoS���ã�
     *          ʹ�������ֵ DDS::SUBSCRIBER_QOS_DEFAULT ������QoS�еĸ������õ�����ΪĬ��ֵ��
     *
     * @param   qoslist ָ��QoS���á�
     *
     * @return  ��ǰ���ܵķ���ֵ��
     *          - #DDS_RETCODE_OK :��ʾ���óɹ���
     *          - #DDS_RETCODE_BAD_PARAMETER :��ʾ@e qoslistΪ�գ�����@e qoslist ������Чֵ��
     *          - #DDS_RETCODE_INCONSISTENT :��ʾ@e qoslist �о��в����ݵ����ã�
     *          - #DDS_RETCODE_ERROR :��ʾʧ�ܣ����縴��QoSʱ��������
     */

    virtual ReturnCode_t set_default_subscriber_qos(const SubscriberQos &qoslist) = 0;

    /**
     * @fn  virtual ReturnCode_t DomainParticipant::set_default_publisher_qos(const PublisherQos &qoslist) = 0;
     *
     * @brief   �÷�������Ϊ�����߱����Ĭ��QoS���á�
     *
     * @details Ĭ�ϵ�QoS�ڴ����µĶ�����ʱָ��QoS����Ϊ DDS::PUBLISHER_QOS_DEFAULT ʱʹ�õ�QoS���ã�
     *          ʹ�������ֵ DDS::PUBLISHER_QOS_DEFAULT ������QoS�еĸ������õ�����ΪĬ��ֵ��
     *
     * @param   qoslist ָ��QoS���á�
     *
     * @return  ��ǰ���ܵķ���ֵ��
     *          - #DDS_RETCODE_OK :��ʾ���óɹ���
     *          - #DDS_RETCODE_BAD_PARAMETER :��ʾ@e qoslistΪ�գ�����@e qoslist ������Чֵ��
     *          - #DDS_RETCODE_INCONSISTENT :��ʾ@e qoslist �о��в����ݵ����ã�
     *          - #DDS_RETCODE_ERROR :��ʾʧ�ܣ����縴��QoSʱ��������
     */

    virtual ReturnCode_t set_default_publisher_qos(const PublisherQos &qoslist) = 0;

    /**
     * @fn  virtual ReturnCode_t DomainParticipant::set_default_topic_qos(const TopicQos &qoslist) = 0;
     *
     * @brief   �÷�������Ϊ���Ᵽ���Ĭ��QoS���á�
     *
     * @details Ĭ�ϵ�QoS�ڴ����µ�����ʱָ��QoS����Ϊ DDS::TOPIC_QOS_DEFAULT ʱʹ�õ�QoS���ã�
     *          ʹ�������ֵ DDS::TOPIC_QOS_DEFAULT ����QoS�еĸ������õ�����ΪĬ��ֵ��
     *
     * @param   qoslist ָ��QoS���á�
     *
     * @return  ��ǰ���ܵķ���ֵ��
     *          - #DDS_RETCODE_OK :��ʾ���óɹ���
     *          - #DDS_RETCODE_BAD_PARAMETER :��ʾ@e qoslistΪ�գ�����@e qoslist ������Чֵ��
     *          - #DDS_RETCODE_INCONSISTENT :��ʾ@e qoslist �о��в����ݵ����ã�
     *          - #DDS_RETCODE_ERROR :��ʾʧ�ܣ����縴��QoSʱ��������
     */

    virtual ReturnCode_t set_default_topic_qos(const TopicQos &qoslist) = 0;

    /**
     * @fn  virtual ReturnCode_t DomainParticipant::get_default_subscriber_qos(SubscriberQos &qoslist) = 0;
     *
     * @brief   �÷�����ȡΪ�����߱����Ĭ��QoS���á�
     *
     * @param [in,out]  qoslist ���ڲ�����ʾ��ȡ�Ľ��.
     *
     * @return  ��ǰ�ķ���ֵ���ͣ�
     *          - #DDS_RETCODE_OK :��ʾ���óɹ���
     *          - #DDS_RETCODE_ERROR :��ʾʧ�ܣ����縴��QoSʱ��������
     */

    virtual ReturnCode_t get_default_subscriber_qos(SubscriberQos &qoslist) = 0;

    /**
     * @fn  virtual ReturnCode_t DomainParticipant::get_default_publisher_qos(PublisherQos &qoslist) = 0;
     *
     * @brief   �÷�����ȡΪ�����߱����Ĭ��QoS���á�
     *
     * @param [in,out]  qoslist ���ڲ�����ʾ��ȡ�Ľ��.
     *
     * @return  ��ǰ�ķ���ֵ���ͣ�
     *          - #DDS_RETCODE_OK :��ʾ���óɹ���
     *          - #DDS_RETCODE_ERROR :��ʾʧ�ܣ����縴��QoSʱ��������
     */

    virtual ReturnCode_t get_default_publisher_qos(PublisherQos &qoslist) = 0;

    /**
     * @fn  virtual ReturnCode_t DomainParticipant::get_default_topic_qos(TopicQos &qoslist) = 0;
     *
     * @brief   �÷�����ȡΪ���Ᵽ���Ĭ��QoS���á�
     *
     * @param [in,out]  qoslist ���ڲ�����ʾ��ȡ�Ľ��.
     *
     * @return  ��ǰ�ķ���ֵ���ͣ�
     *          - #DDS_RETCODE_OK :��ʾ���óɹ���
     *          - #DDS_RETCODE_ERROR :��ʾʧ�ܣ����縴��QoSʱ��������
     */

    virtual ReturnCode_t get_default_topic_qos(TopicQos &qoslist) = 0;    

#ifdef _ZRDDS_INCLUDE_CONTENTFILTER_TOPIC

    /**
     * @fn  virtual ContentFilteredTopic* DomainParticipant::create_contentfilteredtopic( const Char* name, const Topic *related_topic, const Char* filter_exp, const StringSeq& exp_para) = 0;
     *
     * @brief   �����������ݹ��˵����⡣
     *
     * @param   name            �������ݹ��˵��������ƣ����������Ʋ���ͨ���������ݴ��ݵ�Զ�̣����ڱ���ʹ�ã�name
     *                          Ӧ�ñ�֤�����������Ψһ��������ͨ��������ƣ���
     * @param   related_topic   �����Ļ������⡣
     * @param   filter_exp      ���˱��ʽ���﷨����μ� @ref expression-grammer ��
     * @param   exp_para        ���˲���������˱��ʽ���ʹ�á�
     *
     * @return  ��NULL��ʾ�����ɹ���NULL��ʾ����ʧ�ܣ�ʧ�ܵ�ԭ�����Ϊ��
     *          - �����Ѵ���ͬ�������⣻  
     *          - �����Ļ������ⲻ���ڣ�  
     *          - ���˱��ʽ���߹��˲������Ϸ���
     *          - �����ڴ�ʧ�ܡ�
     */

    virtual ContentFilteredTopic* create_contentfilteredtopic(
        const Char* name,
        const Topic *related_topic,
        const Char* filter_exp,
        const StringSeq& exp_para) = 0;

    /**
     * @fn  virtual ReturnCode_t DomainParticipant::delete_contentfilteredtopic( ContentFilteredTopic *a_topic) = 0;
     *
     * @brief   ɾ��ָ���������ݹ��˵����⡣
     *
     * @param [in,out]  a_topic ָ��Ŀ�ꡣ
     *
     * @return  ��ǰ���ܵķ���ֵ��
     *          - #DDS_RETCODE_OK ��ɾ���ɹ���
     *          - #DDS_RETCODE_BAD_PARAMETER ��������Ч���߲����ɸ�������ߴ�����
     *          - #DDS_RETCODE_PRECONDITION_NOT_MET ��������ɾ�����������������������������ݶ�����δɾ����
     *          - #DDS_RETCODE_ERROR ��ɾ��������ϸ�μ���־��
     */

    virtual ReturnCode_t delete_contentfilteredtopic(
        ContentFilteredTopic *a_topic) = 0;

#endif // _ZRDDS_INCLUDE_CONTENTFILTER_TOPIC

    /**
     * @fn  virtual MultiTopic* DomainParticipant::create_multitopic( const Char* name, const Char* type_name, const Char* sub_exp, const Char** exp_para) = 0;
     *
     * @brief   �����ϲ����⡣
     *
     * @param   name        �������ơ�
     * @param   type_name   �������ơ�
     * @param   sub_exp     ���ı��ʽ��
     * @param   exp_para    ��ʾʽ������
     *
     * @return  ��ǰ���Ƿ���NULL��
     *  
     * @warning ��ǰδʵ�� DDS::MultiTopic ��
     */

    virtual MultiTopic* create_multitopic(
        const Char* name,
        const Char* type_name,
        const Char* sub_exp,
        const Char** exp_para) = 0;

    /**
     * @fn  virtual ReturnCode_t DomainParticipant::delete_multitopic(MultiTopic *a_topic) = 0;
     *
     * @brief   ɾ���ϲ����⡣
     *
     * @param [in,out]  a_topic ָ��Ŀ�ꡣ
     *
     * @return  ��ǰ���Ƿ��� #DDS_RETCODE_ERROR ��
     *  
     * @warning ��ǰδʵ�� DDS::MultiTopic ��
     */

    virtual ReturnCode_t delete_multitopic(MultiTopic *a_topic) = 0;

    /**
     * @fn  virtual ReturnCode_t DomainParticipant::get_discovered_topics(InstanceHandleSeq &discoved_handleList) = 0;
     *
     * @brief   ��ȡ�Ѿ���������û�б����Ե���������ı�ʶ��
     *
     * @param [in,out]  discoved_handleList ��ȡ�Ľ���б�
     *
     * @return  ��ǰ���Ƿ��� #DDS_RETCODE_UNSUPPORTED ��
     *  
     * @warning ��ǰδʵ�֡�
     */

    virtual ReturnCode_t get_discovered_topics(InstanceHandleSeq &discoved_handleList) = 0;

#ifdef _ZRDDS_INCLUDE_TOPIC_BUILTIN_TOPIC_DATA
    /**
     * @fn  virtual ReturnCode_t DomainParticipant::get_discovered_topic_data( TopicBuiltinTopicData &data, const InstanceHandle_t& a_handle) = 0;
     *
     * @brief   ��ȡ�Ѿ���������û�б����Ե��������ϸ��Ϣ
     *
     * @param [in,out]  data    ��ȡ������ϸ��Ϣ��
     * @param   a_handle        ��ʶ��Ҫ���ͻ�ȡ�����⡣
     *
     * @return  ��ǰ���Ƿ��� #DDS_RETCODE_UNSUPPORTED 
     *          
     * @warning ��ǰδʵ�֡�
     */

    virtual ReturnCode_t get_discovered_topic_data(
        TopicBuiltinTopicData &data,
        const InstanceHandle_t& a_handle) = 0;
#endif //_ZRDDS_INCLUDE_TOPIC_BUILTIN_TOPIC_DATA

    /**
     * @fn  virtual ReturnCode_t DomainParticipant::get_current_time(Time_t &cur_time) = 0;
     *
     * @brief   ��ȡZRDDS�ڲ�ʹ�õ�ʱ��ϵͳ�ĵ�ǰʱ�����
     *
     * @param [in,out]  cur_time    ���ڲ�������ǰ��ʱ�����
     *
     * @return  ��ǰ���Ƿ��� #DDS_RETCODE_OK ��
     */

    virtual ReturnCode_t get_current_time(Time_t &cur_time) = 0;

#ifdef _ZRDDS_INCLUDE_LIVELINESS_QOS

    /**
     * @fn  virtual ReturnCode_t DomainParticipant::assert_liveliness() = 0;
     *
     * @brief   �÷��������ֶ�����������ߵĴ���ԣ�������Բ�������Ϊ #DDS_MANUAL_BY_PARTICIPANT_LIVELINESS_QOS ʱ���á�
     *
     * @return  ��ǰ���ܵķ���ֵ��
     *          - #DDS_RETCODE_OK :��ʾ��������Գɹ���
     *          - #DDS_RETCODE_NOT_ENABLED :��ʾ���������δʹ�ܡ�
     *          - #DDS_RETCODE_ERROR :�ڲ�δ���������ϸ�μ���־��
     */

    virtual ReturnCode_t assert_liveliness() = 0;
#endif //_ZRDDS_INCLUDE_LIVELINESS_QOS

    virtual ReturnCode_t register_type(
        const Char* type_name,
        ZRDDSTypePlugin* type_plugin) = 0;

    virtual ReturnCode_t unregister_type(const Char* type_name) = 0;

protected:

    /**
     * @brief   ����ģʽ����ʵ�壬˽�еĹ��캯����ֹ�û��Լ�������
     */

    DomainParticipant(){}

    virtual ~DomainParticipant(){}
};

} // namespace DDS

#endif  //_DOMAINPARTICIPANT_H
