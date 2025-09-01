/**
 * @file:       DataReader.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#if !defined(_DATAREADER_H)
#define _DATAREADER_H

#include "ZRDDSCommon.h"
#include "DomainEntity.h"
#include "ReadCondition.h"
#include "QueryCondition.h"
#include "ZRSequence.h"
#include <stdlib.h>
#include "ZRDDSCppWrapper.h"
#include "DataReaderReadOrTakeParams.h"

typedef struct DataReaderImpl DataReaderImpl;
typedef struct DataReaderListenerImpl DataReaderListenerImpl;
struct ZRDynamicData;

namespace DDS {

class Subscriber;
class TopicDescription;
class DataReaderListener;

/**
 * @class   DataReader
 *          
 * @ingroup CppSubscription
 *
 * @brief   DDS��׼�е����ݶ��߽ӿڡ�
 *          
 * @details ���ݶ�����Ҫ����洢�ӷ����˻�ȡ���������Լ��ṩ�ӿڸ��ϲ�Ӧ�û�ȡ���յ������ݣ����ݶ��߽ӿ�ͬ����������ӿڣ�
 *          - �û����������޹ؽӿڣ����༴��������Щ���û������޹صĽӿڣ���Ϊ�û����͵����ݶ��ߵĸ��ࡣ
 *          - �û�����������ؽӿڣ�ͨ����ģ��ʵ�֣� DDS::ZRDDSDataReader 
 */
class DCPSDLL DataReader : public DomainEntity
{
public:

#ifdef _ZRXMLINTERFACE

#ifdef _ZRXMLENTITYINTERFACE
    /**
     * @fn virtual ReturnCode_t DataReader::sample_to_xml_string( ZRDynamicData* data, const Char*& result);
     *
     * @brief ��DynamicDataת����XML��XML��ʽΪdata
     *
     * @param [in] data       �û������DynamicData�������봴��Reader��Topic����������ƥ��
     * @param [in,out] result ���ɵ�XML
     *
     * @return A ReturnCode_t
     */
    virtual ReturnCode_t sample_to_xml_string(
        ZRDynamicData* data,
        const Char*& result);

    /**
     * @fn virtual ReturnCode_t DataReader::read_sample_info_to_xml_string( SampleInfo* sample_info, SampleInfoValidMember* valid_sample_info_member, const Char*& result);
     *
     * @brief ��SampleInfoת����XML��XML��ʽΪread_sample_info
     *
     * @param [in] sample_info              �û������SampleInfo
     * @param [in] valid_sample_info_member ָ�������sample_info����Щ��Ա����Ч��
     * @param [in,out] result               ���ɵ�XML
     *
     * @return The sample information to XML string
     */
    virtual ReturnCode_t read_sample_info_to_xml_string(
        SampleInfo* sample_info,
        SampleInfoValidMember* valid_sample_info_member,
        const Char*& result);

    /**
     * @fn virtual ReturnCode_t DataReader::to_xml(const Char*& result, Boolean containedQos = true);
     *
     * @brief ��Readerת����XML��XML��ʽΪdata_reader
     *
     * @param [in,out] result ���ɵĽ��
     * @param containedQos    �����Ƿ����QoS
     *
     * @return result as a ReturnCode_t
     */
    virtual ReturnCode_t to_xml(const Char*& result, Boolean containedQos = true);

    /**
     * @fn virtual const Char* DataReader::get_entity_name();
     *
     * @brief ��ȡEntity������
     *
     * @return null if it fails, else the entity name
     */
    virtual const Char* get_entity_name();

    virtual Entity* get_factory();

#ifdef _ZRDDS_INCLUDE_READ_CONDITION
    virtual ReadCondition* create_named_readcondition(
        const Char* name,
        const SampleStateMask &sample_mask,
        const ViewStateMask &view_mask,
        const InstanceStateMask &instance_mask);

    virtual ReadCondition* get_named_read_condition(const Char* name);

    virtual ReturnCode_t delete_named_readcondition(const Char* name);

#ifdef _ZRDDS_INCLUDE_QUERY_CONDITION
    virtual QueryCondition* create_named_querycondition(
        const Char* name,
        const SampleStateMask &sample_mask,
        const ViewStateMask &view_mask,
        const InstanceStateMask &instance_mask,
        const Char* query_expression,
        const StringSeq &query_parameters);
#endif //_ZRDDS_INCLUDE_QUERY_CONDITION

#endif //_ZRDDS_INCLUDE_READ_CONDITION

#endif // _ZRXMLENTITYINTERFACE

#ifdef _ZRXMLQOSINTERFACE

    /**
     * @fn virtual ReturnCode_t DataReader::set_qos_with_profile( const Char* library_name, const Char* profile_name, const Char* qos_name);
     *
     * @brief ��QoS�ֿ��ȡQoS���ò����õ����ݶ���
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
        const Char* qos_name);

#endif // _ZRXMLQOSINTERFACE

#endif // _ZRXMLINTERFACE

    virtual ~DataReader(){}
#ifdef _ZRDDS_INCLUDE_READ_CONDITION

    /**
     * @fn  virtual ReadCondition* DataReader::create_readcondition( const SampleStateMask &sample_mask, const ViewStateMask &view_mask, const InstanceStateMask &instance_mask);
     *
     * @brief   ����һ��������ݶ��߰󶨵Ķ�ȡ������
     *
     * @param   sample_mask     ����ָ������״̬���ϵ����롣
     * @param   view_mask       ����ָ����ͼ״̬���ϵ����롣
     * @param   instance_mask   �û�ָ������ʵ��״̬�������롣
     *
     * @return  �����ɹ����ض�ȡ�����Ķ���ָ�룬���򷵻ؿգ�ʧ�ܵ�ԭ�����Ϊ�����ڴ�ʧ�ܡ�
     */

    virtual ReadCondition* create_readcondition(
        const SampleStateMask &sample_mask,
        const ViewStateMask &view_mask,
        const InstanceStateMask &instance_mask);

#ifdef _ZRDDS_INCLUDE_QUERY_CONDITION

    /**
     * @fn  virtual QueryCondition* DataReader::create_querycondition( const SampleStateMask &sample_mask, const ViewStateMask &view_mask, const InstanceStateMask &instance_mask, const Char* query_expression, const StringSeq &query_parameters);
     *
     * @brief   ����һ���󶨵��ö������ϵĲ�ѯ������
     *
     * @param   sample_mask         ����״̬���롣
     * @param   view_mask           ��ͼ״̬���롣
     * @param   instance_mask       ʵ��״̬���롣
     * @param   query_expression    ��ѯ���ʽ��
     * @param   query_parameters    ��ѯ�Ĳ�����
     *
     * @return  �����ɹ����صõ� DDS::QueryCondition �����򷵻ؿա�
     *          
     *          @warning ��δʵ�֡�.
     */

    virtual QueryCondition* create_querycondition(
        const SampleStateMask &sample_mask,
        const ViewStateMask &view_mask,
        const InstanceStateMask &instance_mask,
        const Char* query_expression,
        const StringSeq &query_parameters);

#endif //_ZRDDS_INCLUDE_QUERY_CONDITION

    /**
     * @fn  virtual ReturnCode_t DataReader::delete_readcondition(ReadCondition *a_condition);
     *
     * @brief   ɾ��ָ���Ķ�ȡ������
     *
     * @param   a_condition ָ����ȡ������
     *
     * @details ɾ����ȡ����ʱ���������������˵ȴ������У����Զ��ӵȴ�������ɾ����������
     *
     * @return  ���ܷ��ص�ֵ���£�
     *          - #DDS_RETCODE_OK ��ʾɾ���ɹ���
     *          - #DDS_RETCODE_ERROR ��ʾɾ��ʧ�ܣ�ʧ�ܵ�ԭ�����Ϊ��
     *              - @e a_condition ������Ч�� DDS::ReadCondition ���󣬰���NULL��
     *              - @e a_condition �����ɸ����ݶ��ߴ�����
     */
    virtual ReturnCode_t delete_readcondition(ReadCondition *a_condition);

    /**
     * @fn  virtual ReturnCode_t DataReader::delete_contained_entities();
     *
     * @brief   ɾ�������ݶ��ߴ��������ж�ȡ����(������ѯ����)��ɾ����ȡ����ʱ�����Զ������м���ĵȴ�������ɾ����������
     *
     * @return  ��ǰ���Ƿ��� #DDS_RETCODE_OK ��ʾɾ���ɹ���
     */

    virtual ReturnCode_t delete_contained_entities();
#endif //_ZRDDS_INCLUDE_READ_CONDITION

    /**
     * @fn  virtual ReturnCode_t DataReader::wait_for_historical_data(const Duration_t &max_wait);
     *
     * @brief   �ȴ���ʷ���ݡ�
     *
     * @details �������ݶ��ߵĳ־û��������� > DDS_VOLATILE_DURABILITY_QOS ʱ���������ݶ�����Ҫ�����ڸ����ݶ���
     *          ��������ǰ����֮ƥ�������д���Ѿ����͵���ʷ���ݣ����ô˺����Եȴ���ʷ���ݽ�����ɻ��߳�ʱ��
     *
     * @param   max_wait    ��ĵȴ�ʱ�䡣
     *
     * @return  ���ܷ��ص�ֵ���£�
     *          - #DDS_RETCODE_OK :��ʾ���е���ʷ���ݾ��ѽ�����ɣ����߲���Ҫ������ʷ���ݣ�
     *          - #DDS_RETCODE_NOT_ENABLED :��ʾ�����ݶ�����δʹ�ܣ�
     *          - #DDS_RETCODE_TIMEOUT :��ʾ�� @e max_wait ʱ����δ�����ʷ���ݵĽ��ա�
     */
    virtual ReturnCode_t wait_for_historical_data(const Duration_t &max_wait);

#ifdef _ZRDDS_INCLUDE_LIVELINESS_QOS

    /**
     * @fn  virtual ReturnCode_t DataReader::get_liveliness_changed_status( LivelinessChangedStatus &status);
     *
     * @brief   ��ȡ�����ݶ��߹����� #DDS_LIVELINESS_CHANGED_STATUS ״̬��
     *
     * @param [in,out]  status  ���ڲ�����ʾ��ǰ��״̬��
     *
     * @return  ��ǰ���Ƿ��� #DDS_RETCODE_OK ��ʾ��ȡ�ɹ���
     */

    virtual ReturnCode_t get_liveliness_changed_status(
        LivelinessChangedStatus &status);
#endif //_ZRDDS_INCLUDE_LIVELINESS_QOS

#ifdef _ZRDDS_INCLUDE_DEADLINE_QOS

    /**
     * @fn  virtual ReturnCode_t DataReader::get_requested_deadline_missed_status( RequestedDeadlineMissedStatus &status);
     *
     * @brief   ��ȡ�����ݶ��߹����� #DDS_REQUESTED_DEADLINE_MISSED_STATUS ״̬��
     *
     * @param [in,out]  status  ���ڲ�����ʾ��ǰ��״̬��
     *
     * @return  ��ǰ���Ƿ��� #DDS_RETCODE_OK ��ʾ��ȡ�ɹ���
     */

    virtual ReturnCode_t get_requested_deadline_missed_status(
        RequestedDeadlineMissedStatus &status);

#endif //_ZRDDS_INCLUDE_DEADLINE_QOS

    /**
     * @fn  virtual ReturnCode_t DataReader::get_requested_incompatible_qos_status( RequestedIncompatibleQosStatus &status);
     *
     * @brief   ��ȡ�����ݶ��߹����� #DDS_REQUESTED_INCOMPATIBLE_QOS_STATUS ״̬��
     *
     * @param [in,out]  status  ���ڲ�����ʾ��ǰ��״̬��
     *
     * @return  ��ǰ���Ƿ��� #DDS_RETCODE_OK ��ʾ��ȡ�ɹ���
     */

    virtual ReturnCode_t get_requested_incompatible_qos_status(
        RequestedIncompatibleQosStatus &status);

    /**
     * @fn  virtual ReturnCode_t DataReader::get_sample_lost_status(SampleLostStatus &status);
     *
     * @brief   ��ȡ�����ݶ��߹����� #DDS_SAMPLE_LOST_STATUS ״̬��
     *
     * @param [in,out]  status  ���ڲ�����ʾ��ǰ��״̬��
     *
     * @return  ��ǰ���Ƿ��� #DDS_RETCODE_OK ��ʾ��ȡ�ɹ���
     */

    virtual ReturnCode_t get_sample_lost_status(SampleLostStatus &status);

    /**
     * @fn  virtual ReturnCode_t DataReader::get_sample_rejected_status( SampleRejectedStatus &status);
     *
     * @brief   ��ȡ�����ݶ��߹����� #DDS_SAMPLE_REJECTED_STATUS ״̬��
     *
     * @param [in,out]  status  ���ڲ�����ʾ��ǰ��״̬��
     *
     * @return  ��ǰ���Ƿ��� #DDS_RETCODE_OK ��ʾ��ȡ�ɹ���
     */

    virtual ReturnCode_t get_sample_rejected_status(
        SampleRejectedStatus &status);

    /**
     * @fn  virtual ReturnCode_t DataReader::get_subscription_matched_status( SubscriptionMatchedStatus &status);
     *
     * @brief   ��ȡ�����ݶ��߹����� #DDS_SUBSCRIPTION_MATCHED_STATUS ״̬��
     *
     * @param [in,out]  status  ���ڲ�����ʾ��ǰ��״̬��
     *
     * @return  ��ǰ���Ƿ��� #DDS_RETCODE_OK ��ʾ��ȡ�ɹ���
     */

    virtual ReturnCode_t get_subscription_matched_status(
        SubscriptionMatchedStatus &status);

    /**
     * @fn  virtual TopicDescription* DataReader::get_topicdescription();
     *
     * @brief   ��ȡ�����ݶ��������������⡣
     *
     * @return  �������ݶ��߿��Թ������¼������⣬�ʶ�����ֵΪ����ĸ�������û�ͨ����̬ת��ת��Ϊ�����������
     *          1. ������������ DDS::Topic ;
     *          2. �������ݹ��˵��������� DDS::ContentFilteredTopic ;
     */

    virtual TopicDescription* get_topicdescription();

    /**
     * @fn  virtual Subscriber* DataReader::get_subscriber();
     *
     * @brief   ��ȡ�����ݶ��������Ķ����߶���
     *
     * @return  �����ݶ������������߶���ָ�롣
     */

    virtual Subscriber* get_subscriber();

    /**
     * @fn  virtual ReturnCode_t DataReader::get_matched_publication_data( PublicationBuiltinTopicData &publication_data, const InstanceHandle_t &publication_handle);
     *
     * @brief   �÷�����ѯָ����ʶ������д�ߵ��������ݡ�
     *
     * @param [in,out]  publication_data    ���ڲ��������ڱ���ͨ���м���洢���������ݣ�
     * @param   publication_handle          ����д�ߵ�Ψһ��ʶ���ɴ����·�ʽ��ȡ��
     *                                      - ���������ݶ��������л�ȡ��
     *                                      - #get_matched_publications �з�����
     *                                      - Զ������д�ߵ� DDS::DataWriter::get_instance_handle ��ȡ��
     *
     * @return  ��ǰ���ܵķ���ֵ��
     *          - #DDS_RETCODE_OK :��ʾ��ȡ�ɹ���
     *          - #DDS_RETCODE_NOT_ENABLED :��ʾ�����ݶ�����δʹ�ܣ�
     *          - #DDS_RETCODE_BAD_PARAMETER :����� @e publication_handle δ������ݶ���ƥ�䣻
     *          - #DDS_RETCODE_ERROR :��ʾ�ڿ������ڲ���ʱ��������
     */

    virtual ReturnCode_t get_matched_publication_data(
        PublicationBuiltinTopicData &publication_data,
        const InstanceHandle_t &publication_handle);

    /**
     * @fn  virtual ReturnCode_t DataReader::get_matched_publications( InstanceHandleSeq &publication_handles);
     *
     * @brief   ��ѯ�Ѿ�ƥ���Զ������д�ߵı�ʶ�б�
     *
     * @details ���ص��б��в�����ͨ������ DomainParticipant::ignore_participant ��
     *          DomainParticipant::ignore_publication ���Ե����ݶ��ߣ������������ @e publication_handles
     *          ����󳤶�С����Ҫ���صĽ��ʱ���ײ㽫�� @e publication_handles �������ݡ�
     *
     * @param [in,out]  publication_handles ���ڲ��������ڱ�������д�ߵı�ʶ��
     *
     * @return  ��ǰ���ܵķ���ֵ��
     *          - #DDS_RETCODE_OK :��ʾ��ȡ�ɹ���
     *          - #DDS_RETCODE_NOT_ENABLED :��ʾ�����ݶ�����δʹ�ܣ�
     *          - #DDS_RETCODE_OUT_OF_RESOURCES :��ʾ�����ڴ�ʧ�ܡ�
     */

    virtual ReturnCode_t get_matched_publications(
        InstanceHandleSeq &publication_handles);

    /**
     * @fn  virtual ReturnCode_t DataReader::set_qos(const DataReaderQos &qoslist);
     *
     * @brief   �÷�������Ϊ���ݶ������õ�QoS��
     *
     * @param   qoslist ��ʾ�û���Ҫ���õ�QoS���á�
     *
     * @details ����ʹ������ֵ DDS::DATAREADER_QOS_DEFAULT �Լ� DDS::DATAREADER_QOS_USE_TOPIC_QOS ��
     *
     * @return  ��ǰ���ܵķ���ֵ��
     *          - #DDS_RETCODE_OK :��ʾ��ȡ�ɹ���
     *          - #DDS_RETCODE_BAD_PARAMETER :��ʾ @e qoslist ������Ч��QoS���ã�
     *          - #DDS_RETCODE_INCONSISTENT :��ʾ @e qoslist ���в����ݵ�QoS���ã�
     *          - #DDS_RETCODE_IMMUTABLE_POLICY :��ʾ�û������޸�ʹ�ܺ󲻿ɱ��QoS���ã�
     *          - #DDS_RETCODE_ERROR :��ʾδ����Ĵ��󣬴�����ϸ��Ϣ�������־�У�
     */
    virtual ReturnCode_t set_qos(const DataReaderQos &qoslist);

    /**
     * @fn  virtual ReturnCode_t DataReader::get_qos(DataReaderQos &qoslist);
     *
     * @brief   ��ȡ�����ݶ��ߵ�QoS���á�
     *
     * @param [in,out]  qoslist ���ڲ��������ڱ�������ݶ��ߵ�QoS���á�
     *
     * @return  ��ǰ���ܵķ���ֵ��
     *          - #DDS_RETCODE_OK :��ʾ��ȡ�ɹ���
     *          - #DDS_RETCODE_ERROR :��ʾʧ�ܣ�ԭ�����Ϊ����QoSʱ��������
     */

    virtual ReturnCode_t get_qos(DataReaderQos &qoslist);

    /**
     * @fn  virtual ReturnCode_t DataReader::set_listener( DataReaderListener *a_listener, const StatusKindMask &mask);
     *
     * @brief   ���ø����ݶ��ߵļ�������
     *
     * @details  ������������ԭ�м�������������ÿն����ʾ���ԭ�����õļ�������
     *
     * @param [in,out]  a_listener  Ϊ�����ݶ������õļ���������
     * @param   mask                ����Ӧ�ó������Ȥ��״̬��ֻ��Ӧ�ó������Ȥ��״̬�����仯ʱ���Ż�֪ͨӦ�ó���
     *
     * @return  ��ǰ���Ƿ��� #DDS_RETCODE_OK ��ʾ���óɹ���
     */

    virtual ReturnCode_t set_listener(
        DataReaderListener *a_listener,
        const StatusKindMask &mask);

    /**
     * @fn  virtual DataReaderListener* DataReader::get_listener();
     *
     * @brief   �÷�����ȡͨ�� #set_listener �������ߴ���ʱΪ���ݶ������õļ���������
     *
     * @return  ��ǰ���ܵķ���ֵ��
     *          - NULL��ʾδ���ü�������
     *          - �ǿձ�ʾӦ��ͨ�� #set_listener �����ڴ���ʱ���õļ���������
     */

    virtual DataReaderListener* get_listener();

    /**
     * @fn  virtual StatusCondition* DataReader::get_statuscondition();
     *
     * @brief   ʵ�ָ��� DDS::Entity �ķ��������ظ����ݶ��߹�����״̬������
     *
     * @return  �ײ��Զ�������״̬������
     */

    virtual StatusCondition* get_statuscondition();

    /**
     * @fn  virtual StatusKindMask DataReader::get_status_changes();
     *
     * @brief   ʵ�ָ��� DDS::Entity �ķ�������ȡ��ʵ�����һ�λ�ȡ����״̬���״̬�仯��
     *
     * @return  ����״̬�ĸı����롣
     */
    virtual StatusKindMask get_status_changes();

    /**
     * @fn  InstanceHandle_t DataReader::get_instance_handle();
     *
     * @brief   ʵ�ָ��� DDS::Entity �ķ�������ȡ�����ݶ��ߵ�Ψһ��ʶ��
     *
     * @return  ���ݶ��ߵ�Ψһ��ʶ��
     */
    virtual InstanceHandle_t get_instance_handle();

    /**
     * @fn  virtual ReturnCode_t DataReader::enable();
     *
     * @brief   �ֶ�ʹ�ܸ����ݶ��ߣ��μ�@ref entity-enable ��
     *
     * @return  ��ǰ���ܵķ���ֵ��
     *          - #DDS_RETCODE_OK ����ʾ��ȡ�ɹ���
     *          - #DDS_RETCODE_PRECONDITION_NOT_MET ����ʾ�����Ķ�������δʹ�ܡ�
     */

    virtual ReturnCode_t enable();

    /**
     * @fn  virtual ReturnCode_t DataReader::get_data_instance(InstanceHandleSeq &data_seq,
     *      SampleStateMask sampleMask,
     *      ViewStateMask viewMask,
     *      InstanceStateMask  instanceMask);
     *
     * @brief   ��ѯ��������������ʵ����ʶ��
     *
     * @param [in,out]  data_seq    ���ڲ��������ڴ洢��������������ʵ����
     * @param   sampleMask          �������롣
     * @param   viewMask            view���롣
     * @param   instanceMask        ʵ��״̬���롣
     *
     * @return  ��ǰ���ܵķ���ֵ��
     *          - #DDS_RETCODE_OK ����ʾ��ȡ�ɹ���
     *          - #DDS_RETCODE_OUT_OF_RESOURCES ����ʾ�����ڴ�ʧ�ܡ�
     */
    virtual ReturnCode_t get_data_instance(
        InstanceHandleSeq& data_seq,
        SampleStateMask sampleMask,
        ViewStateMask viewMask,
        InstanceStateMask instanceMask);

    virtual DataReader* get_impl();

    virtual ReturnCode_t read_or_take_untype(DataReaderReadOrTakeParams& result);

    virtual ReturnCode_t read_or_take_next_sample_untype(
        Char* dataValue,
        SampleInfo* sampleInfo,
        Boolean isTake);

    virtual ReturnCode_t return_loan_untype(
        void** dataSeqBuffer,
        Long dataSeqMaxLen,
        SampleInfoSeq* sampleInfos);

    virtual ReturnCode_t return_recv_buffer_untype(
        SampleInfo* sampleInfo);

    virtual ReturnCode_t loan_recv_buffer_untype(
        SampleInfo* sampleInfo);

#ifdef _ZRDDS_INCLUDE_BREAKPOINT_RESUME
    /**
    * @fn  ReturnCode_t DataReader::record_data();
    *
    * @brief   ��ʹ�ô˽ӿ�ʱ,���ݶ��߻Ὣ�Ѵ����������к��Լ���ض�д��Guid��¼������Ŀ¼�µ�zrdds.customer.xml�ļ���
    *          �����ݶ����������ߺ��������ߣ�����ȡzrdds.customer.xml�ļ�����������֪ͨ����д�ߴ�����¼��δ�������ݴ���ʼ�ش�
    *          ʹ�ô˽ӿ�ʱ��ע�⣺
    *             a)���ݶ���������д�ߵ�Guid���ܸı䣬����zrdds.customer.xml�ļ���¼һ��(��ͨ��ָ��ʵ��IDʵ��)  
    *             b)�����öϵ��ش� breakpoint_resume = true
    *
    * @param [in]  sample_infos  ���ݵ���Ϣ��
    * 
    * @param [in]  finish  �����Ƿ�ȫ��������ɣ�
    *        true��ʾ���ݸ�������ȫ��������ɣ���ɾ���Ѿ���¼���û��������кţ�
    *        false��ʾ����δȫ�����ѣ�����Ϊ�û������������кš�
    *
    * @return  ���ݶ��ߵ�Ψһ��ʶ��
    */
    virtual ReturnCode_t record_data(
        SampleInfoSeq &sample_infos,
        ZR_BOOLEAN finish);
#endif//_ZRDDS_INCLUDE_BREAKPOINT_RESUME

    virtual ReturnCode_t get_key_value_untype(
        void* keyHolder,
        const InstanceHandle_t* handle);

    virtual InstanceHandle_t lookup_instance_untype(
        const void* instance);

protected:

    DataReader(DataReader* impl);

protected:
    DataReader* m_cppImpl;
};

typedef DataReader* DataReaderPtr;

// ����DataReaderPtrSeq��
DDS_SEQUENCE_CPP(DataReaderSeq, DataReaderPtr);

} // namespace DDS

#endif  //_DATAREADER_H
