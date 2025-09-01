/**
 * @file:       Subscriber.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#if !defined(_SUBSCRIBER_H)
#define _SUBSCRIBER_H

#include "DomainEntity.h"
#include "ZRDDSCppWrapper.h"
#include "ZRBuiltinTypes.h"

namespace DDS {

class DataReader;
class TopicDescription;
class DataReaderListener;
class SubscriberListener;
class DomainParticipant;
class TypeSupport;
struct DataReaderSeq;

/**
 * @class   Subscriber
 *
 * @ingroup  CppSubscription
 *
 * @brief   ZRDDS�ṩ�Ķ����߽ӿڣ�Ӧ�ô��������߱�ʾ�������ָ�������ڻ�ȡ���ݣ�
 *
 * @details ��������Ҫ������¼������ܣ�
 *          - ʵ�幦�ܣ�  
 *          - ��Ϊ���ݶ��ߵĹ�����  
 *          - ͳһ�������ݶ��ߵ���������֪ͨ��
 */

class DCPSDLL Subscriber : public DomainEntity
{
public:
#ifdef _ZRXMLINTERFACE

#ifdef _ZRXMLENTITYINTERFACE

    /**
     * @fn virtual DataReader* Subscriber::lookup_datareader_by_name( const Char* name)=0;
     *
     * @brief �����־�ȷ����DataReader
     *
     * @param name The name
     *
     * @return null if it fails, else a DataReader*
    */
    virtual DataReader* lookup_datareader_by_name(
        const Char* name) = 0;

    /**
     * @fn virtual ReturnCode_t Subscriber::lookup_named_datareaders( const Char* pattern, StringSeq& reader_names) = 0;
     *
     * @brief �������Ʒ���pattern�޶������ݶ��ߡ�
     *
     * @param pattern               ����ģʽ������֧��*��?��*�������������������ַ���?�������ⵥ���ַ���
     * @param [in,out] reader_names ���ҵõ������ݶ��������б�
     *
     * @return  ��ǰ���ܵķ���ֵ��
     *          - #DDS_RETCODE_OK :��ʾ���ҳɹ���
     *          - #DDS_RETCODE_BAD_PARAMETER :��ʾ�������ڴ�����ȱʧ������
     *          - #DDS_RETCODE_ERROR :��ʾ����ʧ�ܡ�
     */
    virtual ReturnCode_t lookup_named_datareaders(
        const Char* pattern, StringSeq& reader_names) = 0;

    /**
     * @fn virtual DataReader* Subscriber::create_datareader_from_xml_string( const Char* xml_content) = 0;
     *
     * @brief ��XML����һ�����ݶ��ߡ�
     *
     * @param xml_content ��XML�ַ�����ʾ�����ݶ��ߡ�
     *
     * @return ��NULL��ʾ�����ɹ��������ʾʧ�ܣ�ʧ�ܵ�ԭ�����Ϊ��
     *          - �����ڴ�����δ���������ϸ�μ���־��
     */
    virtual DataReader* create_datareader_from_xml_string(
        const Char* xml_content) = 0;
		
#endif // _ZRXMLENTITYINTERFACE

#ifdef _ZRXMLQOSINTERFACE
    /**
     * @fn virtual ReturnCode_t Subscriber::set_default_datareader_qos_with_profile( const Char* library_name, const Char* profile_name, const Char* qos_name)=0;
     *
     * @brief ��QoS�ֿ��л�ȡ���ݶ���QoS����������ΪĬ��DataReaderQos
     *
     * @param library_name QoS������֣�������ΪNULL��
     * @param profile_name QoS���õ����֣�������ΪNULL��
     * @param qos_name     QoS�����֣�����ΪNULL����ת��Ϊdefault�ַ�����
     *
     * @return ��ǰ���ܵķ���ֵ���£�
     *         - #DDS_RETCODE_OK :��ʾ���óɹ���
     *         - #DDS_RETCODE_ERROR :��ʾδ֪�����µ����ô���
     */
    virtual ReturnCode_t set_default_datareader_qos_with_profile(
        const Char* library_name,
        const Char* profile_name,
        const Char* qos_name) = 0;

    /**
     * @fn virtual ReturnCode_t Subscriber::set_qos_with_profile( const Char* library_name, const Char* profile_name, const Char* qos_name)=0;
     *
     * @brief ��QoS�ֿ��л�ȡ������QoS���������õ���������
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
     * @fn virtual DataReader* Subscriber::create_datareader_with_qos_profile( TopicDescription *topic, const Char* library_name, const Char* profile_name, const Char* qos_name, DataReaderListener *dr_listener, StatusKindMask mask) = 0;
     *
     * @brief ��QoS�ֿ��л�ȡ���ݶ���QoS�����䴴�����ݶ��ߡ�
     *
     * @param [in,out] topic    ���ݶ��߹��������⡣
     * @param library_name      QoS������֡�
     * @param profile_name      QoS���õ����֡�
     * @param qos_name          QoS�����֡�
     * @param [in] dr_listener  Ϊ�ö��������õļ��������˲�������Ϊ�ա� ZRDDS����ӹܼ�����������ڴ�������û������ͷš�
     * @param   mask            ����Ӧ�ó������Ȥ��״̬��ֻ��Ӧ�ó������Ȥ��״̬�����仯ʱ���Ż�֪ͨӦ�ó���
     *
     * @return ��NULL��ʾ�����ɹ��������ʾʧ�ܣ�ʧ�ܵ�ԭ�����Ϊ��
     *          - @e a_topic ������Ч���������
     *          - @e a_topic �ĸ�ʵ����ö����߲�����һ���������ʵ�壻
     *          - @e library_name @e profile_name @e qos_name ָ����QoS�к�����Ч��QoS���ߺ��в�һ�µ�QoS���ã�
     *          - �����ڴ�����δ���������ϸ�μ���־��
     */
    virtual DataReader* create_datareader_with_qos_profile(
        TopicDescription *topic,
        const Char* library_name,
        const Char* profile_name,
        const Char* qos_name,
        DataReaderListener *dr_listener,
        StatusKindMask mask) = 0;

    /**
     * @fn  virtual DataReader* Subscriber::create_datareader_with_topic_and_qos_profile( const Char* topicName, TypeSupport* typeSupport, const Char* library_name, const Char* profile_name, const Char* qos_name, DataReaderListener *dr_listener, StatusKindMask mask) = 0;
     *
     * @brief   �����Զ��������û������ߣ�����ָ���������Ƶ����ݶ��ߣ����������ƹ���������δ����ʱ�� ���Զ����������������Ѿ����������ⴴ�����ݶ��ߡ�
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

#endif // _ZRXMLQOSINTERFACE

#endif //_ZRXMLINTERFACE

    /**
     * @fn  virtual DataReader* Subscriber::create_datareader( TopicDescription *a_topic, const DataReaderQos &qoslist, DataReaderListener *a_listener, const StatusKindMask &mask) = 0;
     *
     * @brief   �÷����ڶ������´���һ�����ݶ�����ʵ�壬�����ù��������⡢QoS�Լ���������
     *          
     * @details �û�ʹ�ø����ݶ��ߴ����ڶ�ȡ/��ȡָ���������ݣ����ص����ݶ��߶���Ϊ���ݶ��߹������û�����������ص����ݶ��ߵĸ���ָ�룬
     *          �û���Ҫ������ֵ��̬ת��Ϊ�û��������͵����ݶ��߶��󣬾������μ� @ref subscription_example.cpp ��
     *
     * @param [in,out]  a_topic     �����������������û����Թ��������Լ��������ݹ��˵����⣬
     *                              ���������������ڵ��ø÷���֮ǰ��ͬһ����������µ��� DDS::DomainParticipant::create_topic 
     *                              DDS::DomainParticipant::create_contentfilteredtopic ��������������ĸ��ࣻ
     * @param   qoslist             ��ʾΪ�����ݶ������õ�QoS�� DDS::DATAREADER_QOS_DEFAULT ����ʹ�ö������б����Ĭ�ϵ�QoS��
     * @param [in,out]  a_listener  Ϊ�ö��������õļ��������˲�������Ϊ�ա� ZRDDS����ӹܼ�����������ڴ�������û������ͷš�
     * @param   mask                ����Ӧ�ó������Ȥ��״̬��ֻ��Ӧ�ó������Ȥ��״̬�����仯ʱ���Ż�֪ͨӦ�ó���
     *
     * @return  ��NULL��ʾ�����ɹ��������ʾʧ�ܣ�ʧ�ܵ�ԭ�����Ϊ��
     *          - @e a_topic ������Ч���������
     *          - @e a_topic �ĸ�ʵ����ö����߲�����һ���������ʵ�壻  
     *          - @e qoslist �к�����Ч��QoS���ߺ��в�һ�µ�QoS���ã�  
     *          - �������ݴ����δ���������ϸ�μ���־��
     */

    virtual DataReader* create_datareader(
        TopicDescription *a_topic,
        const DataReaderQos &qoslist,
        DataReaderListener *a_listener,
        const StatusKindMask &mask) = 0;

    /**
     * @fn  virtual ReturnCode_t Subscriber::delete_datareader(DataReader *a_datareader) = 0;
     *
     * @brief   ɾ��ָ�������ݶ��ߡ�
     *
     * @param [in,out]  a_datareader    ָ����Ҫɾ�������ݶ��ߡ�
     *
     * @details ��ɾ�������ݶ���Ӧ����ɾ����������Ҫ������
     *          - ���ݶ��ߴ��������С���ʵ�塱��ȡ�����Ѿ�ȫ����ɾ����  
     *          - ͨ�������ݶ��ߵ� @ref read-take ϵ�з��������û��Ŀռ��Ѿ�ȫ�����ճɹ���  
     *
     * @return  ��ǰ���ܵķ���ֵ���£�
     *          - #DDS_RETCODE_OK ��ɾ���ɹ���
     *          - #DDS_RETCODE_BAD_PARAMETER ������ָ�������ݶ��߲�����Ч�����ݶ��߶���
     *          - #DDS_RETCODE_PRECONDITION_NOT_MET ��  
     *              - ����ָ�������ݶ��߲����ڱ���
     *              - ָ�������ݶ��߲�����ɾ��������
     */

    virtual ReturnCode_t delete_datareader(DataReader *a_datareader) = 0;

    /**
     * @fn  virtual DataReader* Subscriber::lookup_datareader(const Char* topic_name) = 0;
     *
     * @brief   �����������������ݶ��ߡ�
     *
     * @details ������ڶ���������������ݶ��ߣ��򷵻����ݶ��ߵ�ַ��С���Ǹ���
     *
     * @param   topic_name  ��ѯ����������
     *
     * @return  ���ؿձ�ʾû���������������ݶ��ߣ����򷵻���Ӧ�����ݶ��ߡ�
     */

    virtual DataReader* lookup_datareader(const Char* topic_name) = 0;

#ifdef _ZRDDS_INCLUDE_PRESENTATION_QOS

    /**
     * @fn  virtual ReturnCode_t Subscriber::begin_access() = 0;
     *
     * @brief   ���ݶ��߶˿���һ���Է��ʡ�
     *
     * @details  �˷���ֻ���ڶ����� DDS_PresentationQosPolicy::access_scope == #DDS_GROUP_PRESENTATION_QOS
     *           ʱ��Ч���÷���Ӧ�� #end_access �������ʹ�á�
     *
     * @return  ��ǰ���Ƿ��� #DDS_RETCODE_UNSUPPORTED ��
     *
     * @warning �÷���δʵ�֡�
     */

    virtual ReturnCode_t begin_access() = 0;

    /**
     * @fn  virtual ReturnCode_t Subscriber::end_access() = 0;
     *
     * @brief   �� #begin_access ������Ӧ����ʾ���ݷ��ʽ�����
     *
     * @return  ��ǰ���Ƿ��� #DDS_RETCODE_UNSUPPORTED ��
     *
     * @warning �÷���δʵ�֡�
     */

    virtual ReturnCode_t end_access() = 0;

#endif //_ZRDDS_INCLUDE_PRESENTATION_QOS

    /**
     * @fn  virtual ReturnCode_t Subscriber::get_datareaders( DataReaderSeq &datareader, const SampleStateMask &sample_states, const ViewStateMask &view_states, const InstanceStateMask &instance_states) = 0;
     *
     * @brief   ���ҵײ㺬�д����ض�״̬���������������ݶ��ߵĽ�ϡ�
     *
     * @param [in,out]  datareader  ���ڲ��������ڴ洢�������������ݶ����б�
     * @param   sample_states       ��Ҫ���������״̬������
     * @param   view_states         ��Ҫ�������ͼ״̬������
     * @param   instance_states     ��Ҫ�����ʵ��״̬������
     *
     * @details  �������õ��������� DDS_SampleStateKind ��DDS_ViewStateKind �� DDS_InstanceStateKind 
     *           ��ͨ����������ʾ״̬�ļ��ϡ����ݶ�����ֻҪ��һ����������������ݶ��߷���������
     *
     * @return  ��ǰ���ܵķ���ֵ���£�
     *          - #DDS_RETCODE_OK ����ȡ�ɹ���
     *          - #DDS_RETCODE_OUT_OF_RESOURCES ����@e datareader �ṩ�Ŀռ䲻�㣬�ҵײ�����ʧ�ܣ�  
     *          - #DDS_RETCODE_NOT_ENABLED ������������δʹ�ܣ�  
     *          - #DDS_RETCODE_ERROR ���ڲ�������ϸ�μ���־��
     */

    virtual ReturnCode_t get_datareaders(
        DataReaderSeq &datareader,
        const SampleStateMask &sample_states,
        const ViewStateMask &view_states,
        const InstanceStateMask &instance_states) = 0;

    /**
     * @fn  virtual ReturnCode_t Subscriber::notify_datareaders() = 0;
     *
     * @brief   �����������Ե������д��� #DDS_DATA_AVAILABLE_STATUS ״̬�����ݶ��߹����ļ������� 
     *          DDS::DataReaderListener::on_data_available ������
     *
     * @details �����ݶ��ߵײ����µ����ݵ���ʱ�����ᴦ�� #DDS_DATA_AVAILABLE_STATUS ״̬�����û��ص��ɹ������û�
     *          ͨ�� @ref read-take ϵ�з�����ȡ����ʱ�������״̬���÷���ͨ���� 
     *          DDS::SusbcriberListener::data_on_reader �ص�������ʹ�á�
     *
     * @return  ��ǰ���ܵķ���ֵ��
     *          - #DDS_RETCODE_OK ��֪ͨ�ɹ���
     *          - #DDS_RETCODE_NOT_ENABLED ������������δʹ�ܣ�  
     *          - #DDS_RETCODE_ERROR ���ڲ�������ϸ�μ���־��
     */

    virtual ReturnCode_t notify_datareaders() = 0;

    /**
     * @fn  virtual DomainParticipant* Subscriber::get_participant() = 0;
     *
     * @brief   ��ö����ߵĸ�ʵ��������ߡ�
     *
     * @return  ���ظö����ߵĸ�ʵ���������ߡ�
     */

    virtual DomainParticipant* get_participant() = 0;

    /**
     * @fn  virtual ReturnCode_t Subscriber::delete_contained_entities() = 0;
     *
     * @brief   �÷���ɾ���ö����ߴ���������ʵ�塣
     *
     * @details �÷��������ʵ����еݹ���� delete_contained_entities ���������յ�ɾ����ʵ��������ݶ��ߡ���ȡ�����ȣ�
     *          �÷�����ȡ������Ϊ�Ĳ���ɾ����������ɾ��������ʵ�����ɾ��������в�����ɾ��������ʵ�壬�򷵻��ض��Ĵ����롣
     *
     * @return  ��ǰ���ܵķ���ֵ��
     *          - #DDS_RETCODE_OK :��ʾɾ���ɹ���
     *          - #DDS_RETCODE_PRECONDITION_NOT_MET :��ʾ�в���ʵ�岻����ɾ����������ɾ������ʵ�壻
     *          - #DDS_RETCODE_ERROR :��ʾδ���������ϸ�μ���־��
     */

    virtual ReturnCode_t delete_contained_entities() = 0;

    /**
     * @fn  virtual ReturnCode_t Subscriber::set_default_datareader_qos( const DataReaderQos &qoslist) = 0;
     *
     * @brief   �÷�������Ϊ���ݶ��߱����Ĭ��QoS���á�
     *
     * @details Ĭ�ϵ�QoS�ڴ����µ����ݶ���ʱָ��QoS����Ϊ DDS::DATAREADER_QOS_DEFAULT ʱʹ�õ�QoS���ã�
     *          ʹ�������ֵ DDS::DATAREADER_QOS_DEFAULT ������QoS�еĸ������õ�����ΪĬ��ֵ��
     *
     * @param   qoslist ָ��QoS���á�
     *
     * @return  ��ǰ���ܵķ���ֵ��
     *          - #DDS_RETCODE_OK :��ʾ���óɹ���
     *          - #DDS_RETCODE_BAD_PARAMETER :��ʾ@e qoslistΪ�գ�����@e qoslist ������Чֵ��
     *          - #DDS_RETCODE_INCONSISTENT :��ʾ@e qoslist �о��в����ݵ����ã�
     *          - #DDS_RETCODE_ERROR :��ʾʧ�ܣ����縴��QoSʱ��������
     */

    virtual ReturnCode_t set_default_datareader_qos(
        const DataReaderQos &qoslist) = 0;

    /**
     * @fn  virtual ReturnCode_t Subscriber::get_default_datareader_qos(DataReaderQos &qoslist) = 0;
     *
     * @brief   �÷�����ȡΪ���ݶ��߱����Ĭ��QoS���á�
     *
     * @param [in,out]  qoslist ���ڲ�����ʾ��ȡ�Ľ��.
     *
     * @return  ��ǰ�ķ���ֵ���ͣ�
     *          - #DDS_RETCODE_OK :��ʾ���óɹ���
     *          - #DDS_RETCODE_ERROR :��ʾʧ�ܣ����縴��QoSʱ��������
     */

    virtual ReturnCode_t get_default_datareader_qos(DataReaderQos &qoslist) = 0;

    /**
     * @fn  virtual ReturnCode_t Subscriber::copy_from_topic_qos( DataReaderQos &a_datareader_qos, const TopicQos &a_topic_qos) = 0;
     *
     * @brief   ������QoS�й�����Ӧ�����ݶ���QoS��
     *
     * @param [in,out]  a_datareader_qos    ���ڲ�������ʾ����Ľ�����ݶ�ȡQoS���á�
     * @param   a_topic_qos                 Դ����QoS���á�
     *
     * @return  ���ر�ʾ��������ķ����룺
     *          - #DDS_RETCODE_OK ������ɹ���
     *          - #DDS_RETCODE_ERROR ���ڲ����󣬾���μ���־�ļ������ܵ�ԭ��Ϊ�����ڴ�ʧ�ܡ�
     */

    virtual ReturnCode_t copy_from_topic_qos(
        DataReaderQos &a_datareader_qos, 
        const TopicQos &a_topic_qos) = 0;

    /**
     * @fn  virtual ReturnCode_t Subscriber::set_qos(const SubscriberQos &qoslist) = 0;
     *
     * @brief   �÷�������Ϊ���������õ�QoS��
     *
     * @param   qoslist ��ʾ�û���Ҫ���õ�QoS���á�
     *
     * @details ����ʹ������ֵ DDS::SUBSCRIBER_QOS_DEFAULT ��ʾʹ�ô洢����������е�QoS���á�
     *
     * @return  ��ǰ���ܵķ���ֵ��
     *          - #DDS_RETCODE_OK :��ʾ��ȡ�ɹ���
     *          - #DDS_RETCODE_BAD_PARAMETER :��ʾ @e qoslist ������Ч��QoS���ã�
     *          - #DDS_RETCODE_INCONSISTENT :��ʾ @e qoslist ���в����ݵ�QoS���ã�
     *          - #DDS_RETCODE_IMMUTABLE_POLICY :��ʾ�û������޸�ʹ�ܺ󲻿ɱ��QoS���ã�
     *          - #DDS_RETCODE_ERROR :��ʾδ����Ĵ��󣬴�����ϸ��Ϣ�������־�У�
     */
    virtual ReturnCode_t set_qos(const SubscriberQos &qoslist) = 0;

    /**
     * @fn  virtual ReturnCode_t Subscriber::get_qos(SubscriberQos &qoslist) = 0;
     *
     * @brief   ��ȡ�ö����ߵ�QoS���á�
     *
     * @param [in,out]  qoslist ���ڲ��������ڱ��涩���ߵ�QoS���á�
     *
     * @return  ��ǰ���ܵķ���ֵ��
     *          - #DDS_RETCODE_OK :��ʾ��ȡ�ɹ���
     *          - #DDS_RETCODE_ERROR :��ʾʧ�ܣ�ԭ�����Ϊ����QoSʱ��������
     */
    virtual ReturnCode_t get_qos(SubscriberQos &qoslist) = 0;

    /**
     * @fn  virtual ReturnCode_t Subscriber::set_listener( SubscriberListener *a_listener, const StatusKindMask &mask) = 0;
     *
     * @brief   ���øö����ߵļ�������
     *
     * @details  ������������ԭ�м�������������ÿն����ʾ���ԭ�����õļ�������
     *
     * @param [in,out]  a_listener  Ϊ�ö��������õļ���������
     * @param   mask                ����Ӧ�ó������Ȥ��״̬��ֻ��Ӧ�ó������Ȥ��״̬�����仯ʱ���Ż�֪ͨӦ�ó���
     *
     * @return  ��ǰ���Ƿ��� #DDS_RETCODE_OK ��ʾ���óɹ���
     */
    virtual ReturnCode_t set_listener(
        SubscriberListener *a_listener, const StatusKindMask &mask) = 0;

    /**
     * @fn  virtual SubscriberListener* Subscriber::get_listener() = 0;
     *
     * @brief   �÷�����ȡͨ�� #set_listener �������ߴ���ʱΪ���������õļ���������
     *
     * @return  ��ǰ���ܵķ���ֵ��
     *          - NULL��ʾδ���ü�������
     *          - �ǿձ�ʾӦ��ͨ�� #set_listener �����ڴ���ʱ���õļ���������
     */
    virtual SubscriberListener* get_listener() = 0;

protected:
    virtual ~Subscriber();
};

/**
 * @typedef Subscriber* SubscriberPtr
 *
 * @ingroup CppSubscription
 *
 * @brief   ���� DDS::Subscriber ָ��ı�����
 */

typedef Subscriber* SubscriberPtr;

/**
 * @struct SubscriberSeq 
 *
 * @ingroup CppSubscription
 *
 * @brief   ���� DDS::SubscriberPtr ���������ͣ��μ� #DDS_USER_SEQUENCE_CPP ��
 */

DDS_SEQUENCE_CPP(SubscriberSeq, SubscriberPtr);

} // namespace DDS

#endif  //_SUBSCRIBER_H
