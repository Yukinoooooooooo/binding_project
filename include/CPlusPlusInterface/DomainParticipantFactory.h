/**
 * @file:       DomainParticipantFactory.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#if !defined(_DOMAINPARTICIPANTFACTORY_H)
#define _DOMAINPARTICIPANTFACTORY_H

#include "ZRDDSCppWrapper.h" 

struct ZRDynamicData;
struct TypeCodeHeader;

namespace DDS {

class DomainListener;
class DomainParticipantListener;
class DomainParticipant;
class Entity;

/**
 * @class   DomainParticipantFactory
 *
 * @ingroup CppDomain
 *
 * @brief   ������߹����ӿڵĺ��Ĺ��������Ǵ����Լ������������ʵ�壬����Ϊ�������ʵ��Ĺ�����������߹�����һ�������ࡣ
 */

class DCPSDLL DomainParticipantFactory
{
public:
#ifdef _ZRXMLINTERFACE

#ifdef _ZRXMLENTITYINTERFACE

    /**
     * @fn virtual DomainParticipant* DomainParticipantFactory::lookup_participant_by_name( const Char* name)=0;
     *
     * @brief �����־�ȷ����Participant
     *
     * @param name Participant�����֣��������ʱ��ApplicationΪ��Ԫ�ش������������б������Application���֣���ʽΪ/<ApplicationName>/<ParticipantName>
     *
     * @return null if it fails, else a DomainParticipant*
     */
    virtual DomainParticipant* lookup_participant_by_name(
        const Char* name) = 0;

    /**
     * @fn virtual Entity* DomainParticipantFactory::lookup_entity_by_name( const Char* name)=0;
     *
     * @brief �����־�ȷ����ʵ��
     *
     * @param name ʵ������
     *
     * @return null if it fails, else an Entity*
     */
    virtual Entity* lookup_entity_by_name(
        const Char* name) = 0;

    /**
     * @fn virtual ReturnCode_t DomainParticipantFactory::add_to_type_library_from_xml_string(const Char* xml_content) = 0;
     *
     * @brief ��XML������������ӵ����Ϳ�
     *
     * @param xml_content ��typesΪ����Ԫ�ص�XML�ַ���
     *
     * @return  ��ǰ���ܵķ���ֵ���£�
     *          - #DDS_RETCODE_OK :��ʾ��ӳɹ���
     *          - #DDS_RETCODE_BAD_PARAMETER :��ʾ�������ڴ�����ȱʧ������
     *          - #DDS_RETCODE_ERROR :��ʾ���ʧ�ܡ�
     */
    virtual ReturnCode_t add_to_type_library_from_xml_string(
        const Char* xml_content) = 0;

    /**
     * @fn virtual ZRDynamicData* DomainParticipantFactory::gen_dynamic_data(const Char* type_name, const Char* xml_content) = 0;
     *
     * @brief ��XML����DynamicData
     *
     * @param type_name   ��TypeLibrary��ӹ���������
     * @param xml_content ��XML������Data
     *
     * @return  ��ǰ���ܵķ���ֵ���£�
     *          - �ǿձ������ɳɹ���
     *          - NULL��������ʧ�ܡ�
     */
    virtual ZRDynamicData* gen_dynamic_data(
        const Char* type_name,
        const Char* xml_content) = 0;

    /**
     * @fn virtual ReturnCode_t DomainParticipantFactory::lookup_named_participants( const Char* pattern, StringSeq& participant_names) = 0;
     *
     * @brief �������Ʒ���pattern�޶���������ߡ�
     *
     * @param pattern                    ����ģʽ������֧��*��?��*�������������������ַ���?�������ⵥ���ַ�
     * @param [in,out] participant_names ���ҵõ���Participant�����б�
     *
     * @return ��ǰ���ܵķ���ֵ���£�
     *         - #DDS_RETCODE_OK :��ʾ���ҳɹ���
     *         - #DDS_RETCODE_BAD_PARAMETER :��ʾ�������ڴ�����ȱʧ������
     *         - #DDS_RETCODE_ERROR :��ʾ����ʧ�ܡ�
     */
    virtual ReturnCode_t lookup_named_participants(
        const Char* pattern,
        StringSeq& participant_names) = 0;

    /**
     * @fn virtual TypeCodeHeader* DomainParticipantFactory::lookup_type_by_name(const Char* name) = 0;
     *
     * @brief �����ֲ���һ������
     *
     * @param name ���͵����ƣ�Ƕ������ͨ����::���ָ���
     *
     * @return ���ҵõ������Ͷ�Ӧ�� #TypeCodeHeader
     */
    virtual TypeCodeHeader* lookup_type_by_name(const Char* name) = 0;

    /**
     * @fn virtual ReturnCode_t DomainParticipantFactory::lookup_named_types(const Char* pattern, Long reference_depth, StringSeq& type_names) = 0;
     *
     * @brief �����Ϳ��в������ַ���pattern������
     *
     * @param pattern             ����ģʽ������֧��*��?��*�������������������ַ���?�������ⵥ���ַ�
     * @param reference_depth     ��ʱ���ã�������-1
     * @param [in,out] type_names ���ҵõ����������б�
     *
     * @return ��ǰ���ܵķ���ֵ���£�
     *         - #DDS_RETCODE_OK :��ʾ���ҳɹ���
     *         - #DDS_RETCODE_ERROR :��ʾ����ʧ�ܡ�
     */
    virtual ReturnCode_t lookup_named_types(
        const Char* pattern,
        Long reference_depth,
        StringSeq& type_names) = 0;

    /**
     * @fn virtual ReturnCode_t DomainParticipantFactory::type_to_xml( const Char* type_name, const Char*& result) = 0;
     *
     * @brief ��ָ�����Ƶ�����ת��ΪXML
     *
     * @param type_name       ���Ϳ��е��������ƣ�Ƕ������ͨ����::���ָ���
     * @param [in,out] result ���ڱ���ת�������
     *
     * @return ��ǰ���ܵķ���ֵ���£�
     *         - #DDS_RETCODE_OK :��ʾת���ɹ���
     *         - #DDS_RETCODE_ERROR :��ʾת��ʧ�ܡ�
     */
    virtual ReturnCode_t type_to_xml(
        const Char* type_name,
        const Char*& result) = 0;

    /**
     * @fn virtual DomainParticipant* DomainParticipantFactory::create_participant_from_xml_string( const Char* xml_content) = 0;
     *
     * @brief ��XML����Participant��XML��ʽΪdomain_participant
     *
     * @param xml_content ��XML�ı���ʾ��������ߡ�
     *
     * @return  ��ǰ���ܵķ���ֵ���£�
     *          - �ǿձ�ʾ����������߳ɹ���
     *          - NULL��ʾ����ʧ�ܡ�
     */
    virtual DomainParticipant* create_participant_from_xml_string(
        const Char* xml_content) = 0;

    static DomainParticipantFactory* new_instance(const DomainParticipantFactoryQos &qoslist);
    static ReturnCode_t delete_instance(DomainParticipantFactory* factory);

#endif // _ZRXMLENTITYINTERFACE

#ifdef _ZRXMLQOSINTERFACE

    /**
     * @fn  DomainParticipantFactory* DomainParticipantFactory::get_instance_w_profile(const Char* qosFilePath, const Char* libName, const Char* profileName, const Char* qosName);
     *
     * @brief   ��ָ��������ʼ��DDS������߹�����
     *
     * @param   qosFilePath qos�����ļ�·������ΪNULLʱ����Ĭ��ʹ������Ŀ¼�� ZRDDS_QOS_PROFILES.xml �ļ���
     * @param   libName     Qos�����ƣ�������ΪNULL��
     * @param   profileName Qos�������ƣ�������ΪNULL��
     * @param   qosName     Qos���ƣ�����Ϊ�գ���ת��Ϊdefault�ַ�����
     *
     * @return  NULL��ʾʧ�ܣ����򷵻ص���ָ�롣
     */

    static DomainParticipantFactory* get_instance_w_profile(const Char* qosFilePath, const Char* libName, const Char* profileName, const Char* qosName);

    /**
     * @fn virtual ReturnCode_t DomainParticipantFactory::reload_qos_profiles() = 0;
     *
     * @brief ����QosProfileQosPolicy���й�QoS���õ����ã��������¼���QoS���õ����У���DomainParticipantFactory��ʼ��ʱ��ʽ���ã�
     *          �쳣�����߼���
     *          - �����õ�·��������ʱ�����Ը�������ʾ�û�������RETCODE_OK
     *          - �����õ�XML���ڲ��ɺ��ԵĴ���ʱ��XML��ʽ����ȣ�,��ʾ�û���������RETCODE_ERROR
     *        ���е�UserData��GroupData��TopicData����֧��ʹ��String��ʽ��Sequence��ʽ����
     *          - String��ʽΪ���ַ���ֱ����Ϊvalue�ڵ��text
     *          - Sequence��ʽΪ��value����Sequenceʹ�ã���������sequenceMaxLength���ԣ�������ÿ��Ԫ����Ϊelementд��
     *
     * @return ��ǰ���ܵķ���ֵ���£�
     *         - #DDS_RETCODE_OK :��ʾ���óɹ������õ�·�������ڣ�
     *         - #DDS_RETCODE_BAD_PARAMETER ����ʾ��������ȷ���µ����QoS�����
     *         - #DDS_RETCODE_ERROR :��ʾXML���ڴ�����QoS�����ʧ�ܣ�
     */
    virtual ReturnCode_t reload_qos_profiles() = 0;

    /**
     * @fn virtual void DomainParticipantFactory::unload_qos_profiles()=0;
     *
     * @brief ж�����е�QoS����
     */
    virtual void unload_qos_profiles() = 0;

    /**
     * @fn virtual ReturnCode_t DomainParticipantFactory::set_qos_with_profile( const Char* library_name, const Char* profile_name, const Char* qos_name) = 0;
     *
     * @brief ��QoS�ֿ��ȡQoS���ò����õ�������߹���
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
     * @fn virtual ReturnCode_t DomainParticipantFactory::set_default_participant_qos_with_profile( const Char* library_name, const Char* profile_name, const Char* qos_name) = 0;
     *
     * @brief ��QoS�ֿ��ȡ�������QoS��������ΪĬ���������QoS
     *
     * @param library_name QoS������֣�������ΪNULL��
     * @param profile_name QoS���õ����֣�������ΪNULL��
     * @param qos_name     QoS�����֣�����ΪNULL����ת��Ϊdefault�ַ�����
     *
     * @return ��ǰ���ܵķ���ֵ���£�
     *         - #DDS_RETCODE_OK :��ʾ���óɹ���
     *         - #DDS_RETCODE_ERROR :��ʾδ֪�����µ����ô���
     */
    virtual ReturnCode_t set_default_participant_qos_with_profile(
        const Char* library_name,
        const Char* profile_name,
        const Char* qos_name) = 0;

    /**
     * @fn  virtual ReturnCode_t DomainParticipantFactory::get_participant_factory_qos_from_profile( DomainParticipantFactoryQos& qos, const Char* library_name, const Char* profile_name, const Char* qos_name) = 0;
     *
     * @brief   ��QoS�ֿ��ȡ������߹���QoS������
     *
     * @param [in,out]  qos     ��ȡ����QoS
     * @param   library_name    QoS������֣�������ΪNULL��
     * @param   profile_name    QoS���õ����֣�������ΪNULL��
     * @param   qos_name        QoS�����֣�����ΪNULL����ת��Ϊdefault�ַ�����
     *
     * @return  ��ǰ���ܵķ���ֵ���£�
     *          - #DDS_RETCODE_OK :��ʾ���óɹ���
     *          - #DDS_RETCODE_ERROR :��ʾδ֪�����µ����ô���
     */

    virtual ReturnCode_t get_participant_factory_qos_from_profile(
        DomainParticipantFactoryQos& qos,
        const Char* library_name,
        const Char* profile_name,
        const Char* qos_name) = 0;

    /**
     * @fn virtual ReturnCode_t DomainParticipantFactory::get_participant_qos_from_profile( DomainParticipantQos& qos, const Char* library_name, const Char* profile_name, const Char* qos_name)=0;
     *
     * @brief ��QoS�ֿ��ȡ�������QoS������
     *
     * @param [in,out] qos ��ȡ����QoS
     * @param library_name QoS������֣�������ΪNULL��
     * @param profile_name QoS���õ����֣�������ΪNULL��
     * @param qos_name     QoS�����֣�����ΪNULL����ת��Ϊdefault�ַ�����
     *
     * @return ��ǰ���ܵķ���ֵ���£�
     *         - #DDS_RETCODE_OK :��ʾ���óɹ���
     *         - #DDS_RETCODE_ERROR :��ʾδ֪�����µ����ô���
     */
    virtual ReturnCode_t get_participant_qos_from_profile(
        DomainParticipantQos& qos,
        const Char* library_name,
        const Char* profile_name,
        const Char* qos_name) = 0;

    /**
     * @fn virtual ReturnCode_t DomainParticipantFactory::get_publisher_qos_from_profile( PublisherQos& qos, const Char* library_name, const Char* profile_name, const Char* qos_name)=0;
     *
     * @brief ��QoS�ֿ��ȡ������QoS������
     *
     * @param [in,out] qos ��ȡ����QoS
     * @param library_name QoS������֣�������ΪNULL��
     * @param profile_name QoS���õ����֣�������ΪNULL��
     * @param qos_name     QoS�����֣�����ΪNULL����ת��Ϊdefault�ַ�����
     *
     * @return ��ǰ���ܵķ���ֵ���£�
     *         - #DDS_RETCODE_OK :��ʾ���óɹ���
     *         - #DDS_RETCODE_ERROR :��ʾδ֪�����µ����ô���
     */
    virtual ReturnCode_t get_publisher_qos_from_profile(
        PublisherQos& qos,
        const Char* library_name,
        const Char* profile_name,
        const Char* qos_name) = 0;

    /**
     * @fn virtual ReturnCode_t DomainParticipantFactory::get_subscriber_qos_from_profile( SubscriberQos& qos, const Char* library_name, const Char* profile_name, const Char* qos_name)=0;
     *
     * @brief ��QoS�ֿ��ȡ������QoS������
     *
     * @param [in,out] qos ��ȡ����QoS
     * @param library_name QoS������֣�������ΪNULL��
     * @param profile_name QoS���õ����֣�������ΪNULL��
     * @param qos_name     QoS�����֣�����ΪNULL����ת��Ϊdefault�ַ�����
     *
     * @return ��ǰ���ܵķ���ֵ���£�
     *         - #DDS_RETCODE_OK :��ʾ���óɹ���
     *         - #DDS_RETCODE_ERROR :��ʾδ֪�����µ����ô���
     */
    virtual ReturnCode_t get_subscriber_qos_from_profile(
        SubscriberQos& qos,
        const Char* library_name,
        const Char* profile_name,
        const Char* qos_name) = 0;

    /**
     * @fn virtual ReturnCode_t DomainParticipantFactory::get_topic_qos_from_profile( TopicQos& qos, const Char* library_name, const Char* profile_name, const Char* qos_name)=0;
     *
     * @brief ��QoS�ֿ��ȡ����QoS������
     *
     * @param [in,out] qos ��ȡ����QoS
     * @param library_name QoS������֣�������ΪNULL��
     * @param profile_name QoS���õ����֣�������ΪNULL��
     * @param qos_name     QoS�����֣�����ΪNULL����ת��Ϊdefault�ַ�����
     *
     * @return ��ǰ���ܵķ���ֵ���£�
     *         - #DDS_RETCODE_OK :��ʾ���óɹ���
     *         - #DDS_RETCODE_ERROR :��ʾδ֪�����µ����ô���
     */
    virtual ReturnCode_t get_topic_qos_from_profile(
        TopicQos& qos,
        const Char* library_name,
        const Char* profile_name,
        const Char* qos_name) = 0;

    /**
     * @fn virtual ReturnCode_t DomainParticipantFactory::get_datawriter_qos_from_profile( DataWriterQos& qos, const Char* library_name, const Char* profile_name, const Char* qos_name)=0;
     *
     * @brief ��QoS�ֿ��ȡ����д��QoS������
     *
     * @param [in,out] qos ��ȡ����QoS
     * @param library_name QoS������֣�������ΪNULL��
     * @param profile_name QoS���õ����֣�������ΪNULL��
     * @param qos_name     QoS�����֣�����ΪNULL����ת��Ϊdefault�ַ�����
     *
     * @return ��ǰ���ܵķ���ֵ���£�
     *         - #DDS_RETCODE_OK :��ʾ���óɹ���
     *         - #DDS_RETCODE_ERROR :��ʾδ֪�����µ����ô���
     */
    virtual ReturnCode_t get_datawriter_qos_from_profile(
        DataWriterQos& qos,
        const Char* library_name,
        const Char* profile_name,
        const Char* qos_name) = 0;

    /**
     * @fn virtual ReturnCode_t DomainParticipantFactory::get_datareader_qos_from_profile( DataReaderQos& qos, const Char* library_name, const Char* profile_name, const Char* qos_name)=0;
     *
     * @brief ��QoS�ֿ��ȡ���ݶ���QoS������
     *
     * @param [in,out] qos ��ȡ����QoS
     * @param library_name QoS������֣�������ΪNULL��
     * @param profile_name QoS���õ����֣�������ΪNULL��
     * @param qos_name     QoS�����֣�����ΪNULL����ת��Ϊdefault�ַ�����
     *
     * @return ��ǰ���ܵķ���ֵ���£�
     *         - #DDS_RETCODE_OK :��ʾ���óɹ���
     *         - #DDS_RETCODE_ERROR :��ʾδ֪�����µ����ô���
     */
    virtual ReturnCode_t get_datareader_qos_from_profile(
        DataReaderQos& qos,
        const Char* library_name,
        const Char* profile_name,
        const Char* qos_name) = 0;

    /**
     * @fn virtual DomainParticipant* DomainParticipantFactory::create_participant_with_qos_profile( const DomainId_t domainId, const Char* library_name, const Char* profile_name, const Char* qos_name, DomainParticipantListener* listener, StatusKindMask mask) = 0;
     *
     * @brief ��QoS�ֿ��ȡQoS���ò����䴴���������
     *
     * @param domainId      ��Id
     * @param library_name  QoS������֣�������ΪNULL��
     * @param profile_name  QoS���õ����֣�������ΪNULL��
     * @param qos_name      QoS�����֣�����ΪNULL����ת��Ϊdefault�ַ�����
     * @param [in] listener Ϊ������������õļ�������
     * @param mask          ����Ӧ�ó������Ȥ��״̬��ֻ��Ӧ�ó������Ȥ��״̬�����仯ʱ���Ż�֪ͨӦ�ó���
     *
     * @return  ��ǰ���ܵķ���ֵ���£�
     *          - �ǿձ�ʾ����������߳ɹ���
     *          - NULL��ʾ����ʧ�ܡ�
     */
    virtual DomainParticipant* create_participant_with_qos_profile(
        const DomainId_t domainId,
        const Char* library_name,
        const Char* profile_name,
        const Char* qos_name,
        DomainParticipantListener* listener,
        StatusKindMask mask) = 0;

    /**
     * @fn virtual ReturnCode_t DomainParticipantFactory::add_qos_library(const Char* xml_representation) = 0;
     *
     * @brief ���һ��QoS��
     *
     * @param xml_representation ��XML�ַ�����ʾ��QoS�⡣
     *
     * @return ��ǰ���ܵķ���ֵ���£�
     *         - #DDS_RETCODE_OK :��ʾ��ӳɹ���
     *         - #DDS_RETCODE_BAD_PARAMETER :��ʾ�������ڴ�����ȱʧ������
     *         - #DDS_RETCODE_ERROR :��ʾ���ʧ�ܡ�
     */
    virtual ReturnCode_t add_qos_library(const Char* xml_representation) = 0;

    /**
     * @fn virtual ReturnCode_t DomainParticipantFactory::remove_qos_library(const Char* qos_library_name) = 0;
     *
     * @brief ɾ��һ��QoS��
     *
     * @param qos_library_name ��Ҫ���Ƴ���QoS�������
     *
     * @return ��ǰ���ܵķ���ֵ���£�
     *         - #DDS_RETCODE_OK :��ʾ�Ƴ��ɹ���
     *         - #DDS_RETCODE_BAD_PARAMETER :��ʾ�������ڴ�����ȱʧ������
     *         - #DDS_RETCODE_ERROR :��ʾ�Ƴ�ʧ�ܡ�
     */
    virtual ReturnCode_t remove_qos_library(const Char* qos_library_name) = 0;

    /**
     * @fn virtual ReturnCode_t DomainParticipantFactory::add_qos_profile(const Char* qos_library_name, const Char* xml_representation) = 0;
     *
     * @brief ��ָ��QoS�������һ��QoS����
     *
     * @param qos_library_name   ��Ҫ���QoS���õ�QoS�⡣
     * @param xml_representation ��XML��ʾ��QoS�������ݡ�
     *
     * @return ��ǰ���ܵķ���ֵ���£�
     *         - #DDS_RETCODE_OK :��ʾ��ӳɹ���
     *         - #DDS_RETCODE_BAD_PARAMETER :��ʾ�������ڴ�����ȱʧ������
     *         - #DDS_RETCODE_ERROR :��ʾ���ʧ�ܡ�
     */
    virtual ReturnCode_t add_qos_profile(
        const Char* qos_library_name,
        const Char* xml_representation) = 0;

    /**
     * @fn virtual ReturnCode_t DomainParticipantFactory::remove_qos_profile(const Char* qos_library_name, const Char* qos_profile_name) = 0;
     *
     * @brief ��ָ��QoS�����Ƴ�һ��QoS����
     *
     * @param qos_library_name QoS������ơ�
     * @param qos_profile_name QoS���õ����ơ�
     *
     * @return ��ǰ���ܵķ���ֵ���£�
     *         - #DDS_RETCODE_OK :��ʾ�Ƴ��ɹ���
     *         - #DDS_RETCODE_BAD_PARAMETER :��ʾ�������ڴ�����ȱʧ������
     *         - #DDS_RETCODE_ERROR :��ʾ�Ƴ�ʧ�ܡ�
     */
    virtual ReturnCode_t remove_qos_profile(
        const Char* qos_library_name,
        const Char* qos_profile_name) = 0;

    /**
     * @fn virtual ReturnCode_t DomainParticipantFactory::qos_library_to_xml(const Char* qos_library_name, const Char*& result) = 0;
     *
     * @brief ��QoS��ת��ΪXML
     *
     * @param qos_library_name QoS������ơ�
     * @param [in,out] result  ת���õ��Ľ����
     *
     * @return ��ǰ���ܵķ���ֵ���£�
     *         - #DDS_RETCODE_OK :��ʾת���ɹ���
     *         - #DDS_RETCODE_ERROR :��ʾת��ʧ�ܡ�
     */
    virtual ReturnCode_t qos_library_to_xml(
        const Char* qos_library_name,
        const Char*& result) = 0;

    /**
     * @fn virtual ReturnCode_t DomainParticipantFactory::qos_profile_to_xml(const Char* qos_library_name, const Char* qos_profile_name, const Char*& result) = 0;
     *
     * @brief ��һ��QoS����ת��ΪXML
     *
     * @param qos_library_name QoS������ơ�
     * @param qos_profile_name QoS���õ����ơ�
     * @param [in,out] result  ת���õ��Ľ����
     *
     * @return ��ǰ���ܵķ���ֵ���£�
     *         - #DDS_RETCODE_OK :��ʾת���ɹ���
     *         - #DDS_RETCODE_ERROR :��ʾת��ʧ�ܡ�
     */
    virtual ReturnCode_t qos_profile_to_xml(
        const Char* qos_library_name,
        const Char* qos_profile_name,
        const Char*& result) = 0;

    /**
     * @fn virtual ReturnCode_t DomainParticipantFactory::lookup_qos_libraries( const Char* pattern, StringSeq& qos_library_names) = 0;
     *
     * @brief �������Ʒ���pattern�޶���QoS��
     *
     * @param pattern                    ����ģʽ������֧��*��?��*�������������������ַ���?�������ⵥ���ַ���
     * @param [in,out] qos_library_names ���ҵõ���QoS�������б�
     *
     * @return ��ǰ���ܵķ���ֵ���£�
     *         - #DDS_RETCODE_OK :��ʾ���ҳɹ���
     *         - #DDS_RETCODE_BAD_PARAMETER :��ʾ�������ڴ�����ȱʧ������
     *         - #DDS_RETCODE_ERROR :��ʾ����ʧ�ܡ�
     */
    virtual ReturnCode_t lookup_qos_libraries(
        const Char* pattern,
        StringSeq& qos_library_names) = 0;

    /**
     * @fn virtual ReturnCode_t DomainParticipantFactory::lookup_qos_profiles( const Char* qos_library_name, const Char* pattern, StringSeq& qos_profile_names) = 0;
     *
     * @brief ��ָ��QoS���в������ַ���pattern��QoS����
     *
     * @param qos_library_name           QoS������֣�������ΪNULL��
     * @param pattern                    ����ģʽ������֧��*��?��*�������������������ַ���?�������ⵥ���ַ�
     * @param [in,out] qos_profile_names ���ҵõ���QoS���������б�
     *
     * @return ��ǰ���ܵķ���ֵ���£�
     *         - #DDS_RETCODE_OK :��ʾ���ҳɹ���
     *         - #DDS_RETCODE_BAD_PARAMETER :��ʾ�������ڴ�����ȱʧ������
     *         - #DDS_RETCODE_ERROR :��ʾ����ʧ�ܡ�
     */
    virtual ReturnCode_t lookup_qos_profiles(
        const Char* qos_library_name,
        const Char* pattern,
        StringSeq& qos_profile_names) = 0;

#endif // _ZRXMLQOSINTERFACE

#endif // _ZRXMLINTERFACE

    /**
     * @fn  virtual DomainParticipant* DomainParticipantFactory::create_participant( const DomainId_t &domainId, const DomainParticipantQos &qoslist, DomainParticipantListener *a_listener, const StatusKindMask &mask) = 0;
     *
     * @brief   ����һ���µ��������ʵ�壬������QoS�Լ���������������ߵĴ�������Ӧ�ó���������@e domainId ָ�������н���ͨ�š�
     *
     * @param   domainId            ������Ҫ�������ţ�ȡֵ��ΧΪ[0-232]��
     * @param   qoslist             ��ʾΪ������������õ�QoS��#DOMAINPARTICIPANT_QOS_DEFAULT ����ʹ��������߹����б����Ĭ�ϵ�QoS��
     * @param [in,out]  a_listener  Ϊ������������õļ�������
     * @param   mask                ����Ӧ�ó������Ȥ��״̬��ֻ��Ӧ�ó������Ȥ��״̬�����仯ʱ���Ż�֪ͨӦ�ó���
     *
     * @return  �����ɹ�ָ�򴴽��ɹ����������ʵ����󣬷��򷵻�NULL��ʧ�ܵ�ԭ�����Ϊ��
     *          - ����ռ�ʧ�ܻ��߳�ʼ����Դʧ�ܣ�����Ĵ�����Ϣ�μ���־��  
     *          - @e qoslist ������Чֵ���ߺ��в�һ�µ�QoS��
     */

    virtual DomainParticipant* create_participant(
        const DomainId_t &domainId,
        const DomainParticipantQos &qoslist,
        DomainParticipantListener *a_listener,
        const StatusKindMask &mask) = 0;

    /**
     * @fn  virtual ReturnCode_t DomainParticipantFactory::delete_participant(DomainParticipant *a_dp) = 0;
     *
     * @brief   �÷���ɾ��ָ����������ߡ��ڵ��ø÷���֮ǰ��Ҫ��֤��������ߵ�������ʵ�嶼�Ѿ���ɾ�������򽫻᷵�ش���
     *
     * @param [in,out]  a_dp    ָ����Ҫɾ�����������ʵ�塣
     *
     * @return  ���ܵķ���ֵ���£�
     *          - #DDS_RETCODE_OK :��ʾɾ���ɹ���  
     *          - #DDS_RETCODE_BAD_PARAMETER :�û��ṩ�Ĳ���������Ч��������߶��󣬰���NULLֵ��  
     *          - #DDS_RETCODE_PRECONDITION_NOT_MET :ָ����������߲�����ɾ����������������ʵ��δɾ����  
     *          - #DDS_RETCODE_ERROR :ָ����������߲����ɹ���������
     */

    virtual ReturnCode_t delete_participant(DomainParticipant *a_dp) = 0;

    /**
     * @fn  static DomainParticipantFactory* DomainParticipantFactory::get_instance();
     *
     * @brief   ��ȡ������߹����������� #TheParticipantFactory ��Ϊ�ú����ļ�д��
     *
     * @return  ��ǰ���ܵķ���ֵ��
     *          - NULL��ʾ������������ʧ�ܣ����ܵ�ԭ��  
     *              - ��ʼ����Դʧ�ܣ���ϸ�μ���־��  
     *              - Mac����ʱ����֤ʧ�ܣ�
     *          - ��ȡ�ɹ��ĵ�������ָ�룻   
     *
     * @note    �÷����̲߳���ȫ������߳�ͬʱ����ʵ������ȫ����ȡʵ����ȫ��
     */

    static DomainParticipantFactory* get_instance();

    /**
     * @fn  static DomainParticipantFactory* get_instance_w_qos(const DomainParticipantFactoryQos &qoslist);
     *
     * @brief   ʹ��ָ����DomainParticipantFactoryQos����ȡ������߹����ĵ�������.
     *
     * @param   qoslist ָ����DomainParticipantFactoryQos.
     *
     * @return  ��ǰ���ܵķ���ֵ��
     *          - NULL��ʾ������������ʧ�ܣ����ܵ�ԭ��
     *              - ��ʼ����Դʧ�ܣ���ϸ�μ���־��
     *              - Mac����ʱ����֤ʧ�ܣ�
     *          - ��ȡ�ɹ��ĵ�������ָ�룻
     *          
     * @note    �÷����̲߳���ȫ������߳�ͬʱ����ʵ������ȫ����ȡʵ����ȫ��.
     */

    static DomainParticipantFactory* get_instance_w_qos(const DomainParticipantFactoryQos &qoslist);

    /**
     * @fn  static ReturnCode_t DomainParticipantFactory::finalize_instance();
     *
     * @brief   �����������÷���ͬ�����̲߳���ȫ�ģ�����߳�ͬʱ���øú��������ܻ�����⡣
     *
     * @return  ��ǰ���ܵķ���ֵ��
     *          - #DDS_RETCODE_OK :��ʾ�����ɹ���
     *          - #DDS_RETCODE_PRECONDITION_NOT_MET :�ɸ�������߹����������������δɾ���ꣻ
     */

    static ReturnCode_t finalize_instance();

    /**
     * @fn  virtual ReturnCode_t DomainParticipantFactory::delete_contained_entities() = 0;
     *
     * @brief   ɾ�����е�������߼�����ʵ�壬�ú���������ɾ����������ɾ����������ʵ�塣
     *
     * @return  ���ܵķ���ֵ���£�
     *          - #DDS_RETCODE_OK :��ʾɾ���ɹ���
     *          - #DDS_RETCODE_PRECONDITION_NOT_MET :ĳЩ������߲�����ɾ����������������ʵ��δɾ����
     *          - #DDS_RETCODE_ERROR :ָ����������߲����ɹ���������
     */

    virtual ReturnCode_t delete_contained_entities() = 0;

    /**
     * @fn  virtual DomainParticipant* DomainParticipantFactory::lookup_participant(const DomainId_t &domainId) = 0;
     *
     * @brief   �÷�����ָ����@e domainId �²���������ߣ�����ж��������ߣ��򷵻�����һ����
     *
     * @param   domainId    ��Ҫ���ҵ���
     *
     * @return  ��ǰ���ܵķ���ֵ��
     *          - NULL��ʾ����ʧ�ܣ��������ڸ����µ�ǰû��������ߣ�  
     *          - �ǿձ�ʾ���ҵĽ�������صĽ��Ϊ�������������ָ����С��������ߡ�
     */

    virtual DomainParticipant* lookup_participant(const DomainId_t &domainId) = 0;

    /**
     * @fn  virtual ReturnCode_t DomainParticipantFactory::set_default_participant_qos(const DomainParticipantQos &qoslist) = 0;
     *
     * @brief   �÷������øù���Ϊ������߱����Ĭ��QoS���á�
     *          
     * @details Ĭ�ϵ�QoS�ڴ����µ��������ʱָ��QoS����Ϊ DDS::DOMAINPARTICIPANT_QOS_DEFAULT ʱʹ�õ�QoS���ã�
     *          ʹ�������ֵ DDS::DOMAINPARTICIPANT_QOS_DEFAULT �������QoS�еĸ������õ�����ΪĬ��ֵ��
     *
     * @param   qoslist ָ��QoS���á�
     *
     * @return  ��ǰ���ܵķ���ֵ��
     *          - #DDS_RETCODE_OK :��ʾ���óɹ���  
     *          - #DDS_RETCODE_BAD_PARAMETER :��ʾ@e qoslistΪ�գ�����@e qoslist ������Чֵ��   
     *          - #DDS_RETCODE_INCONSISTENT :��ʾ@e qoslist �о��в����ݵ����ã�   
     *          - #DDS_RETCODE_ERROR :��ʾʧ�ܣ����縴��QoSʱ��������
     */

    virtual ReturnCode_t set_default_participant_qos(const DomainParticipantQos &qoslist) = 0;

    /**
     * @fn  virtual ReturnCode_t DomainParticipantFactory::get_default_participant_qos(DomainParticipantQos &qoslist) = 0;
     *
     * @brief   �÷�����ȡ�ù���Ϊ������߱����Ĭ��QoS���á�
     *
     * @param [in,out]  qoslist ���ڲ�����ʾ��ȡ�Ľ��.
     *
     * @return  ��ǰ�ķ���ֵ���ͣ�
     *          - #DDS_RETCODE_OK :��ʾ���óɹ���  
     *          - #DDS_RETCODE_ERROR :��ʾʧ�ܣ����縴��QoSʱ��������
     */

    virtual ReturnCode_t get_default_participant_qos(DomainParticipantQos &qoslist) = 0;

    /**
     * @fn  virtual ReturnCode_t DomainParticipantFactory::set_qos(const DomainParticipantFactoryQos &qoslist) = 0;
     *
     * @brief   �÷�������������߹��������QoS�������ֵ DDS::DOMAINPARTICIPANT_FACTORY_QOS_DEFAULT ��ʾ����ΪĬ��ֵ��
     *
     * @param   qoslist ָ��Ŀ��QoS��
     *
     * @return  ��ǰ���ܵķ���ֵ��
     *          - #DDS_RETCODE_OK :��ʾ���óɹ���  
     *          - #DDS_RETCODE_BAD_PARAMETER :��ʾ@e qoslistΪ�գ�����@e qoslist ������Чֵ��   
     *          - #DDS_RETCODE_INCONSISTENT :��ʾ@e qoslist �о��в����ݵ����ã�   
     *          - #DDS_RETCODE_ERROR :��ʾʧ�ܣ����縴��QoSʱ��������
     */

    virtual ReturnCode_t set_qos(const DomainParticipantFactoryQos &qoslist) = 0;

    /**
     * @fn  virtual ReturnCode_t DomainParticipantFactory::get_qos(DomainParticipantFactoryQos &qoslist) = 0;
     *
     * @brief   �÷�����ȡΪ������߹������õ�QoS��
     *          
     * @details ������ø÷���֮ǰδ���ù� #set_qos ���򷵻�ϵͳĬ�ϵ�QoS���ã����򷵻� #set_qos �Ľ����
     *
     * @param [in,out]  qoslist ���ڲ������洢��ȡ�Ľ����
     *
     * @return  ��ǰ�ķ���ֵ���ͣ�
     *          - #DDS_RETCODE_OK :��ʾ���óɹ���  
     *          - #DDS_RETCODE_ERROR :��ʾʧ�ܣ����縴��QoSʱ��������
     */

    virtual ReturnCode_t get_qos(DomainParticipantFactoryQos &qoslist) = 0;

#ifdef _ZRDDSSECURITY

    /**
     * @fn virtual ReturnCode_t DomainParticipantFactory::load_security_plugin( const Char* plugin_name, const Char* file_name, const Char* retrieve_instance_func_name, const Char* finalize_instance_func_name) = 0;
     *
     * @brief ���ذ�ȫ���
     *
     * @details - ��Windows��Linux�ں�ϵͳ�У���ȫ����Զ�̬�����ʽ�ṩ��Windows��.dll��Linux��.so����
     *          ����������ʱͨ�����øú������ء�
     *          - ��VxWorks��ReWorks�У���ȫ����Կ��������ʽ�ṩ��.a���������ڿ���Ӧ��ʱһͬ���뵽Ӧ���У�  
     *          ������Ҫʹ�ð�ȫ���֮ǰ���øú�������ʱ�ĵ��� @e file_name �����������á�
     *          ע�⣺����ReWorks�Ļ�����������ReDe�ڱ���ʱδ��ֱ�����õķ��Ż��ڱ�������б�ɾ����
     *          �����Ҫ��ʹ�ð�ȫ�����Ӧ���з���һ���������ں����е��ð�ȫ�����ȡʵ����ɾ��ʵ���ĺ�����
     *          �����������������������Ż���
     *
     * @param plugin_name                 Ϊ��ǰ���صİ�ȫ�����������ƣ������ڴ����������ʱ���ð�ȫ�����
     * @param file_name                   ��ȫ������ļ����ƣ���Windows���Ƕ�̬���ӿ⣨dll����Linux���Ƕ�̬�⣨so����VxWorks��ReWorks�д˲����������á�
     * @param retrieve_instance_func_name ��ȫ����л�ȡʵ���ĺ������ƣ���Ҫ�ο���ȫ�����ʹ���ֲ��֪��
     * @param finalize_instance_func_name ��ȫ�����ɾ��ʵ���ĺ������ƣ���Ҫ�ο���ȫ�����ʹ���ֲ��֪��
     *
     * @return ��ǰ���ܵķ���ֵ��
     *          - #DDS_RETCODE_OK :��ʾ���سɹ���
     *          - #DDS_RETCODE_ERROR :��ʾ����ʧ�ܣ�ʧ�ܵ�ԭ�����������ļ������ڡ������ļ�ʧ�ܡ���ȡ��ȫ����еĺ���ʧ�ܡ���ȡʵ��ʧ�ܣ��������ʱ��־��Ϣ��
     */
    virtual ReturnCode_t load_security_plugin(
        const Char* plugin_name,
        const Char* file_name,
        const Char* retrieve_instance_func_name,
        const Char* finalize_instance_func_name) = 0;
#endif // _ZRDDSSECURITY
protected:

    virtual ~DomainParticipantFactory();
};

/**
 * @def TheParticipantFactory
 *
 * @ingroup CppDomain
 *
 * @brief   �ú���Ϊ DDS::DomainParticipantFactory::get_instance ����д��
 */

#define TheParticipantFactory DomainParticipantFactory::get_instance()

} // namespace DDS

#endif  //_DOMAINPARTICIPANTFACTORY_H
