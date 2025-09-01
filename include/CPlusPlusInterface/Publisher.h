/**
 * @file:       Publisher.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#ifndef Publisher_h__
#define Publisher_h__

#include "DomainEntity.h"
#include "ZRSequence.h"
#include "ZRBuiltinTypes.h"
#include "ZRDDSCppWrapper.h"

struct PublisherImpl;

namespace DDS {

class DataWriter;
class Topic;
class DataWriterListener;
class PublisherListener;
class DomainParticipant;
class TypeSupport;


/**
 * @class   Publisher
 *
 * @ingroup  CppPublication
 *
 * @brief   ZRDDS�ṩ�ķ����߽ӿڣ�Ӧ�ô��������߱�ʾ��������ָ���������ṩ���ݣ�
 *
 * @details ��������Ҫ������¼������ܣ�
 *          - ʵ�幦�ܣ�  
 *          - ��Ϊ����д�ߵĹ�����  
 *          - ͳһ��������д�ߵ������������ͣ�
 */
class Publisher : public DomainEntity
{
public:
#ifdef _ZRXMLINTERFACE

#ifdef _ZRXMLENTITYINTERFACE

    /**
     * @fn virtual DataWriter* Publisher::lookup_datawriter_by_name( const Char* name)=0;
     *
     * @brief �����־�ȷ����DataWriter
     *
     * @author Tim
     * @date 17/11/2
     *
     * @param name �����ҵ�����д�����ơ�
     *
     * @return  ���ܵķ���ֵ���£�
     *           - NULLδ���ҵ�����д�ߣ�
     *           - �鵽�����׸�����д�ߡ�
     */
    virtual DataWriter* lookup_datawriter_by_name(
        const Char* name) = 0;

    /**
     * @fn virtual ReturnCode_t Publisher::lookup_named_datawriters( const Char* pattern, StringSeq& writer_names) = 0;
     *
     * @brief �������Ʒ���pattern�޶�������д������
     *
     * @param pattern               ����ģʽ������֧��*��?��*�������������������ַ���?�������ⵥ���ַ�
     * @param [in,out] writer_names ���ҵõ�����д�������б�
     *
     * @return   ���ܵķ���ֵ���£�
     *           - #DDS_RETCODE_BAD_PARAMETER �������ڴ���
     *           - #DDS_RETCODE_OK ���óɹ���
     */
    virtual ReturnCode_t lookup_named_datawriters(
        const Char* pattern, StringSeq& writer_names) = 0;

    /**
     * @fn virtual DataWriter* Publisher::create_datawriter_from_xml_string( const Char* xml_content) = 0;
     *
     * @brief ��XML����һ������д�ߣ�XML���ڵ�Ϊdata_writer
     *
     * @param xml_content XML�ַ���
     *
     * @return  ���ܵķ���ֵ���£�
     *           - NULL��������д��ʧ�ܣ�
     *           - ����������д�ߡ�
     */
    virtual DataWriter* create_datawriter_from_xml_string(
        const Char* xml_content) = 0;

#endif // _ZRXMLENTITYINTERFACE

#ifdef _ZRXMLQOSINTERFACE

    /**
     * @fn virtual ReturnCode_t Publisher::set_default_datawriter_qos_with_profile( const Char* library_name, const Char* profile_name, const Char* qos_name)=0;
     *
     * @brief ��QoS�ֿ��л�ȡ����д��QoS��������ΪĬ������д��QoS
     *
     * @param library_name QoS������֣�������ΪNULL��
     * @param profile_name QoS���õ����֣�������ΪNULL��
     * @param qos_name     QoS�����֣�����ΪNULL����ת��Ϊdefault�ַ�����
     *
     * @return ��ǰ���ܵķ���ֵ���£�
     *         - #DDS_RETCODE_OK :��ʾ���óɹ���
     *         - #DDS_RETCODE_ERROR :��ʾδ֪�����µ����ô���
     */
    virtual ReturnCode_t set_default_datawriter_qos_with_profile(
        const Char* library_name,
        const Char* profile_name,
        const Char* qos_name) = 0;

    /**
     * @fn virtual ReturnCode_t Publisher::set_qos_with_profile( const Char* library_name, const Char* profile_name, const Char* qos_name)=0;
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
     * @fn virtual DataWriter* Publisher::create_datawriter_with_qos_profile( Topic *topic, const Char* library_name, const Char* profile_name, const Char* qos_name, DataWriterListener *dw_listener, StatusKindMask mask) = 0;
     *
     * @brief ��QoS�ֿ��л�ȡ����д��QoS�����䴴������д��
     *
     * @param [in] topic        ����д�߹���������
     * @param library_name      QoS������֣�������ΪNULL��
     * @param profile_name      QoS���õ����֣�������ΪNULL��
     * @param qos_name          QoS�����֣�����ΪNULL����ת��Ϊdefault�ַ�����
     * @param [in] dw_listener  �û��ṩ�ļ���������
     * @param mask              ״̬���룬ָ����Ҫ�������������״̬
     *
     * @return  ���ܵķ���ֵ���£�
     *           - NULL��������д��ʧ�ܣ�
     *           - ����������д�ߡ�
     */
    virtual DataWriter* create_datawriter_with_qos_profile(
        Topic *topic,
        const Char* library_name,
        const Char* profile_name,
        const Char* qos_name,
        DataWriterListener *dw_listener,
        StatusKindMask mask) = 0;

    /**
     * @fn  virtual DataWriter* Publisher::create_datawriter_with_topic_and_qos_profile( const Char* topicName, TypeSupport* typeSupport, const Char* library_name, const Char* profile_name, const Char* qos_name, DataWriterListener *dw_listener, StatusKindMask mask) = 0;
     *
     * @brief   ����ָ���������Ƶ�����д�ߣ����������ƹ���������δ����ʱ�����Զ������� ���������Ѿ����������ⴴ������д�ߡ�
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

#endif // _ZRXMLQOSINTERFACE

#endif // _ZRXMLINTERFACE

    /**
    * @fn   virtual DataWriter* Publisher::create_datawriter( Topic *the_topic, const DataWriterQos &qoslist, DataWriterListener *a_listener, const StatusKindMask &mask) = 0;
    *
    * @brief    ����DataWriter��
    *
    * @param    the_topic       ���ڹ���DataWriter��Topicʵ��ָ�롣
    * @param    qoslist         DataWriter��QoS���á�
    * @param    a_listener      ��Ҫ��װ��DataWriter��Listener��
    * @param    mask            ״̬���룬ָ����Ҫ��Listener�����״̬��
    *
    * @return  ���ܵķ���ֵ���£�
    *           - NULL��������д��ʧ�ܣ�
    *           - ����������д�ߡ�
    */

    virtual DataWriter* create_datawriter(
        Topic *the_topic,
        const DataWriterQos &qoslist,
        DataWriterListener *a_listener,
        const StatusKindMask &mask) = 0;

    /**
    * @fn   virtual ReturnCode_t Publisher::delete_datawriter(DataWriter *a_writer) = 0;
    *
    * @brief    ɾ��һ������д�ߡ�
    *
    * @param    a_writer    ��Ҫ��ɾ��������д�ߡ�
    *
    * @return   ���ܵķ���ֵ���£�
    *           - #DDS_RETCODE_BAD_PARAMETER ����Ĳ�������
    *           - #DDS_RETCODE_PRECONDITION_NOT_MET ���������д������
    *           - #DDS_RETCODE_ERROR δ�������
    *           - #DDS_RETCODE_OK ɾ���ɹ���
    */

    virtual ReturnCode_t delete_datawriter(DataWriter *a_writer) = 0;

    /**
    * @fn   virtual DataWriter* Publisher::lookup_datawriter( const Char* topic_name) = 0;
    *
    * @brief    �������������Ҷ�Ӧ������д�ߡ�
    *
    * @param    topic_name  ����������д��������������ơ�
    *
    * @return   ���ܵķ���ֵ���£�
    *           - NULLδ���ҵ�����д�ߣ�
    *           - �鵽�����׸�����д�ߡ�
    */

    virtual DataWriter* lookup_datawriter(
        const Char* topic_name) = 0;

    /**
    * @fn   virtual ReturnCode_t Publisher::suspend_publications() = 0;
    *
    * @brief    �������ݷ�����
    *
    * @details  �����ݷ���������֮�󣬸÷����ߴ�������������д�߷��������ݶ����ٱ�������
    *           ֱ��������ȫȡ��֮��Ż�����������ݡ�
    *           �ú������Ա���ε��ã�����ȡ������Ҳ��Ҫ���ʹ�ã��༴����ú�������ε���֮�󣬱���ȡ����ͬ�����������¿�ʼ�������ݡ�
    *
    * @return   ���ܵķ���ֵ���£�
    *           - #DDS_RETCODE_NOT_ENABLED �÷�����δ��ʹ�ܣ�
    *           - #DDS_RETCODE_OK �����ɹ���
    */

    virtual ReturnCode_t suspend_publications() = 0;

    /**
    * @fn   virtual ReturnCode_t Publisher::resume_publications() = 0;
    *
    * @brief    �ָ����ݷ������� #suspend_publications ���ʹ�á�
    *
    * @return   ���ܵķ���ֵ���£�
    *           - #DDS_RETCODE_NOT_ENABLED �÷�����δ��ʹ�ܣ�
    *           - #DDS_RETCODE_PRECONDITION_NOT_MET �÷�����δ���ù� #suspend_publications ��
    *           - #DDS_RETCODE_OK �����ɹ���
    */

    virtual ReturnCode_t resume_publications() = 0;

#ifdef _ZRDDS_INCLUDE_PRESENTATION_QOS
    /**
    * @fn   virtual ReturnCode_t Publisher::begin_coherent_changes() = 0;
    *
    * @brief    ��ʼ���С����������޸ġ�
    *
    * @details  ��������д�������ķ����ߵ�QoS #DDS_PresentationQosPolicy::coherent_access == true��ʹ�ô˺�����ʼ���С�ԭ�ӡ�������
    *           �ڸú�������֮��ֱ�� #end_coherent_changes ������֮ǰ�������������ݻᱻ���ն�һ���Է��ʵ���
    *           �༴�� #end_coherent_changes ������֮ǰ�������ύ�����ݶ��ڽ��ն���˵���ǲ��ɷ��ʵġ�
    *           ���� #end_coherent_changes ����֮�󣬽��ն˻��յ�һ�����ݡ�
    *
    * @return	���ܵķ���ֵ���£�
    *           - #DDS_RETCODE_NOT_ENABLED ������δʹ�ܣ�
    *           - #DDS_RETCODE_ERROR δ�������
    */

    virtual ReturnCode_t begin_coherent_changes() = 0;

    /**
    * @fn   virtual ReturnCode_t Publisher::end_coherent_changes() = 0;
    *
    * @brief    ���������������޸ģ�ʹ���ն˿��Է����޸ĵ�ֵ�������� #begin_coherent_changes ����֮����á�
    *
    * @return   ���ܵķ���ֵ���£�
    *           - #DDS_RETCODE_NOT_ENABLED ������δʹ�ܡ�
    *           - #DDS_RETCODE_PRECONDITION_NOT_MET ������δ���ù� #begin_coherent_changes ��
    *           - #DDS_RETCODE_ERROR δ�������
    */

    virtual ReturnCode_t end_coherent_changes() = 0;

#endif //_ZRDDS_INCLUDE_PRESENTATION_QOS

    /**
    * @fn   virtual ReturnCode_t Publisher::wait_for_acknowledgments(const Duration_t &max_wait) = 0;
    *
    * @brief    �������øú������߳�ֱ���÷����ߴ���������д�߷��͵��������ݶ������ն�����Ӧ���߳�ʱ��
    *
    * @param    max_wait    �ú����������ʱ�䡣
    *
    * @return   ���ܵķ���ֵ���£�
    *           - #DDS_RETCODE_NOT_ENABLED ������δʹ�ܡ�
    *           - #DDS_RETCODE_TIMEOUT �ȴ���ʱ��
    *           - #DDS_RETCODE_ERROR δ�������
    */

    virtual ReturnCode_t wait_for_acknowledgments(const Duration_t &max_wait) = 0;

    /**
    * @fn   virtual DomainParticipant* Publisher::get_participant() = 0;
    *
    * @brief    ��ȡ�����÷����ߵ�������ߡ�
    *
    * @return   ���ܵķ���ֵ���£�
    *           - ������Publisher��DomainParticipant��
    */

    virtual DomainParticipant* get_participant() = 0;

    /**
    * @fn   virtual ReturnCode_t Publisher::delete_contained_entities() = 0;
    *
    * @brief    ɾ��Publisher������������DataWriter��
    *
    * @return   ���ܵķ���ֵ���£�
    *           - #DDS_RETCODE_ERROR δ�������
    *           - #DDS_RETCODE_OK ɾ���ɹ���
    */

    virtual ReturnCode_t delete_contained_entities() = 0;

    /**
    * @fn   virtual ReturnCode_t Publisher::set_default_datawriter_qos(const DataWriterQos &qoslist) = 0;
    *
    * @brief    ��������д�ߵ�Ĭ��QoS��
    *
    * @details  ����������д��ʱ����ʹ�� DDS::DATAWRITER_QOS_DEFAULT ֵ��ΪDataWriterQoS���롣
    *           ����û�ʹ���� DDS::DATAWRITER_QOS_DEFAULT �������QoS���ý��ɸú�������ʱ�����QoS������
    *
    * @param    qoslist ��Ҫ���õ�����д��QoS�����ʹ��DEFAULT_DATAWRITER_QOS��Ϊ�������øú��������õ�Ĭ��QoS�������á�
    *
    * @return   �μ� #DDS::DataWriter::set_qos ��
    */

    virtual ReturnCode_t set_default_datawriter_qos(const DataWriterQos &qoslist) = 0;

    /**
    * @fn   virtual ReturnCode_t Publisher::get_default_datawriter_qos(DataWriterQos &qoslist) = 0;
    *
    * @brief    ��ȡ�� #set_default_datawriter_qos ���õ�DataWriterQos��
    *
    * @param [in,out]   qoslist ��ȡ��������д��QoS
    *
    * @return   ���ܵķ���ֵ���£�
    *           - #DDS_RETCODE_ERROR δ�������
    *           - #DDS_RETCODE_OK ��ȡ�ɹ���
    */

    virtual ReturnCode_t get_default_datawriter_qos(DataWriterQos &qoslist) = 0;

    /**
    * @fn   virtual ReturnCode_t Publisher::copy_from_topic_qos(DataWriterQos &a_datawriter_qos, const TopicQos &a_topic_qos) = 0;
    *
    * @brief    ʹ��TopicQos�еĶ�Ӧ�ֵDataWriterQos��
    *
    * @param    a_topic_qos                 ����QoS����Ϊ����������Դ��
    * @param [in,out]   a_datawriter_qos    ����д��QoS�����濽�������
    *
    * @return   ���ܵķ���ֵ���£�
    *           - #DDS_RETCODE_ERROR δ�������
    *           - #DDS_RETCODE_OK ���óɹ���
    */

    virtual ReturnCode_t copy_from_topic_qos(
        DataWriterQos &a_datawriter_qos, 
        const TopicQos &a_topic_qos) = 0;

    /**
    * @fn   virtual ReturnCode_t Publisher::set_qos(const PublisherQos &qoslist) = 0;
    *
    * @brief    ���÷�����QoS��
    *
    * @param    qoslist �����õķ�����QoS������ʹ�� DDS::PUBLISHER_QOS_DEFAULT ��Ϊ������ʹ������������б����Ĭ�Ϸ�����QoS
    *
    * @return   ���ܵķ���ֵ���£�
    *           - #DDS_RETCODE_IMMUTABLE_POLICY ������ʹ�ܺ��޸ĵ�QoS��
    *           - #DDS_RETCODE_INCONSISTENT QoS���ڳ�ͻ��
    *           - #DDS_RETCODE_BAD_PARAMETER QoS���ڲ��Ϸ���ֵ��
    *           - #DDS_RETCODE_ERROR δ�������
    *           - #DDS_RETCODE_OK ���óɹ���
    */

    virtual ReturnCode_t set_qos(const PublisherQos &qoslist) = 0;

    /**
    * @fn   virtual ReturnCode_t Publisher::get_qos(PublisherQos &qoslist) = 0;
    *
    * @brief    ��ȡ������QoS��
    *
    * @param [in,out]   qoslist �����ȡ���ķ�����QoSֵ��
    *
    * @return   ���ܵķ���ֵ���£�
    *           - #DDS_RETCODE_OK ��ȡ�ɹ���
    *           - #DDS_RETCODE_ERROR δ�������
    */

    virtual ReturnCode_t get_qos(PublisherQos &qoslist) = 0;

    /**
    * @fn   virtual ReturnCode_t Publisher::set_listener(PublisherListener *a_listener, const StatusKindMask &mask) = 0;
    *
    * @brief    ���÷����ߵļ�������
    *
    * @details  �����µļ���������ʹԭ�еļ��������ͷţ��û���Ҫ�Լ��������������ķ�����ͷš�
    *
    * @param    a_listener  �û��ṩ�ļ��������󣬿��Դ���NULL���������
    * @param    mask        ״̬���룬ָ����Ҫ�������������״̬��
    *
    * @return   ���ܵķ���ֵ���£�
    *           - #DDS_RETCODE_OK ���óɹ���
    */

    virtual ReturnCode_t set_listener(
        PublisherListener *a_listener, 
        const StatusKindMask &mask) = 0;

    /**
    * @fn   virtual PublisherListener* Publisher::get_listener() = 0;
    *
    * @brief    ��ȡ�����ߵ�ǰ�ļ�������
    *
    * @return   ���ܵķ���ֵ���£�
    *           - NULL��ʾδ���ü�������
    *           - �ǿձ�ʾӦ��ͨ�� #set_listener �����ڴ���ʱ���õļ���������
    */

    virtual PublisherListener* get_listener() = 0;

protected:
    virtual ~Publisher() {}
};

typedef Publisher* PublisherPtr;
// ����PublisherSeq��
DDS_SEQUENCE_CPP(PublisherSeq, PublisherPtr);

} // namespace DDS

#endif // Publisher_h__
