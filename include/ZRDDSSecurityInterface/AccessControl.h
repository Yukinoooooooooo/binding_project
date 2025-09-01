#ifndef AccessControl_h__
#define AccessControl_h__

#include "DDSBuiltinSecurityCommon.h"
#include "DomainId_t.h"
#include "DomainParticipantQos.h"
#include "PartitionQosPolicy.h"
#include "DataReaderQos.h"
#include "DataWriterQos.h"
#include "TopicQos.h"
#include "ZRDynamicData.h"
#include "ParticipantBuiltinTopicData.h"
#include "PublicationBuiltinTopicData.h"
#include "SubscriptionBuiltinTopicData.h"
#include "DataTags.h"

namespace DDS
{
class DataWriter;
class DataReader;
} // namespace DDS

typedef DDSSecHandle PermissionsHandle;
typedef DDSSecHandle IdentityHandle;
typedef struct TopicBuiltinTopicData TopicBuiltinTopicData;
class AccessControlListener;
class Authentication;

class AccessControl
{
public:
    virtual ~AccessControl(){};
    /**
    * @fn  PermissionsHandle BuiltinAccessControl::validate_local_permissions( const AuthenticationPlugin* auth_plugin, const IdentityHandle identity, const DDS_DomainId_t domain_id, const DomainParticipantQos* participant_qos, SecurityException* exception);
    *
    * @brief   ȷ�ϱ���������ߵ�Ȩ��.
    *
    * @author  zch
    * @date    2018/1/30
    *
    * @param   auth_plugin         ��Ȩ�����ȷ��������ߵ�Ȩ��.
    * @param   identity            ����������ߵ���ݱ�ʶ��������֤�����validate_local_identity����.
    * @param   domain_id           ���.
    * @param   participant_qos     ������ߵ�QoS.
    * @param [in,out]  exception   �����쳣������.
    *
    * @return  �ɹ��򷵻�PermissionsHandle,���򷵻ؿ�.
    */

   virtual PermissionsHandle validate_local_permissions(
        Authentication* auth_plugin,
        const IdentityHandle identity,
        const DDS_DomainId_t domain_id,
        const DDS_DomainParticipantQos* participant_qos,
        SecurityException* exception)=0;

    /**
    * @fn  PermissionsHandle BuiltinAccessControl::validate_remote_permissions( const AuthenticationPlugin* auth_plugin, const IdentityHandle local_identity_handle, const IdentityHandle remote_identity_handle, const PermissionsToken* remote_permissions_token, const AuthenticatedPeerCredentialToken* remote_credential_token, SecurityException** exception);
    *
    * @brief  ȷ��Զ�������֤����������ߵ�Ȩ��.
    *
    * @author  zch
    * @date    2018/1/30
    *
    * @param   auth_plugin                 ��֤���������ȷ��Զ��������ߵ����.
    * @param   local_identity_handle       ����������ߵ���ݱ�ʶ.
    * @param   remote_identity_handle      Զ��������ߵ���ݱ�ʶ.
    * @param   remote_permissions_token    Զ��������ߵ�PermissionsToken.
    * @param   remote_credential_token     Զ��������ߵ�AuthenticatedPeerCredentialToken.
    * @param [in,out]  exception           �����쳣������.
    *
    * @return  �ɹ�����PermissionsHandle�����򷵻ؿ�.
    */

    virtual PermissionsHandle validate_remote_permissions(
        Authentication* auth_plugin,
        const IdentityHandle local_identity_handle,
        const IdentityHandle remote_identity_handle,
        const PermissionsToken* remote_permissions_token,
        const AuthenticatedPeerCredentialToken* remote_credential_token,
        SecurityException* exception)=0;

    /**
    * @fn  bool BuiltinAccessControl::check_create_participant( PermissionsHandle permissions_handle, DDS_DomainId_t domain_id, DomainParticipantQos qos, SecurityException* exception);
    *
    * @brief   ����Ƿ��д�������������������ߵ�Ȩ��.
    *
    * @author  zch
    * @date    2018/1/30
    *
    * @param   permissions_handle  ����������ߵ�Ȩ�ޱ�ʶ.
    * @param   domain_id           ���.
    * @param   qos                 ������ߵ�QoS.
    * @param   exception           �����쳣������.
    *
    * @return  �ɹ�����true�����򷵻�false.
    */

   virtual bool check_create_participant(
        const PermissionsHandle permissions_handle,
        const DDS_DomainId_t domain_id,
        const DDS_DomainParticipantQos* qos,
        SecurityException* exception)=0;

    /**
    * @fn  bool BuiltinAccessControl::check_create_datawriter( const PermissionsHandle permissions_handle, const DDS_DomainId_t domain_id, const char* topic_name, const DataWriterQos* qos, const PartitionQosPolicy* partition, const DataTag* data_tag, SecurityException* exception);
    *
    * @brief   ��֤�����Ƿ���Ȩ�޴�������Ҫ���DataWriter.
    *
    * @author  zch
    * @date    2018/1/30
    *
    * @param   permissions_handle  ����������ߵ�Ȩ�ޱ�ʶ.
    * @param   domain_id           ���.
    * @param   topic_name          ������.
    * @param   qos                 DataWriter��QoS.
    * @param   partition           DataWriter����Publisher��PartitionQosPolicy��
    * @param   data_tag            �ͱ���DataWriter��data��ƥ������ݱ�ǩ��
    * @param [in,out]  exception   �����쳣������.
    *
    * @return  �ɹ�����true�����򷵻�false.
    */

    virtual bool check_create_datawriter(
        const PermissionsHandle permissions_handle,
        const DDS_DomainId_t domain_id,
        const char* topic_name,
        const DDS_DataWriterQos* qos,
        const DDS_PartitionQosPolicy* partition,
        const DDS_DataTags* data_tag,
        SecurityException* exception)=0;

    /**
    * @fn  bool BuiltinAccessControl::check_create_datareader( const PermissionsHandle permissions_handle, const DDS_DomainId_t domain_id, const char* topic_name, const DataReaderQos* qos, const PartitionQosPolicy* partition, const DataTag* data_tag, SecurityException* exception);
    *
    * @brief   ��֤�����Ƿ�Ȩ�޴�������Ҫ���DataReader��
    *
    * @author  zch
    * @date    2018/1/30
    *
    * @param   permissions_handle  ����������ߵ�Ȩ�ޱ�ʶ��
    * @param   domain_id           ��š�
    * @param   topic_name          ��������
    * @param   qos                 DataReader��Qos.
    * @param   partition           DataReader������Subscriber��PartitionQosPolicy.
    * @param   data_tag            ����DataReader���ڶ�ȡ�����ݵı�ǩ.
    * @param [in,out]  exception   �����쳣������.
    *
    * @return  �ɹ�����true�����򷵻�false.
    */

    virtual bool check_create_datareader(
        const PermissionsHandle permissions_handle,
        const DDS_DomainId_t domain_id,
        const char* topic_name,
        const DDS_DataReaderQos* qos,
        const DDS_PartitionQosPolicy* partition,
        const DDS_DataTags* data_tag,
        SecurityException* exception)=0;

    /**
    * @fn  bool BuiltinAccessControl::check_create_topic( const PermissionsHandle permisssions_handle, const DDS_DomainId_t domain_id, const char* topic_name, const TopicQos* qos, SecurityException* exception);
    *
    * @brief   ȷ�ϱ����Ƿ��д�������������Topic��Ȩ��.
    *
    * @author  zch
    * @date    2018/1/30
    *
    * @param   permisssions_handle ����������ߵ�Ȩ�ޱ�ʶ.
    * @param   domain_id           ���.
    * @param   topic_name          ������.
    * @param   qos                 Topic��QoS.
    * @param [in,out]  exception   �����쳣������.
    *
    * @return  ����ɹ�����true����෵��false.
    */

    virtual bool check_create_topic(
        const PermissionsHandle permissions_handle,
        const DDS_DomainId_t domain_id,
        const char*  topic_name,
        const DDS_TopicQos* qos,
        SecurityException* exception)=0;

    /**
    * @fn  bool BuiltinAccessControl::check_local_datawriter_register_instance( const PermissionsHandle permissions_handle, const DataWriter* writer, const ZRDynamicData* key, SecurityException* exception);
    *
    * @brief   ��֤���ص�DataWriter�Ƿ���ע��ʵ����Ȩ��.
    *
    * @author  zch
    * @date    2018/1/30
    *
    * @param   permissions_handle  ����������ߵ�Ȩ�ޱ�ʶ.
    * @param   writer              ���ص�DataWriter.
    * @param   key                 ʵ����key.
    * @param [in,out]  exception   �����쳣������.
    *
    * @return  ����ɹ�����true�����򷵻�false.
    */

    virtual bool check_local_datawriter_register_instance(
        const PermissionsHandle permissions_handle,
        const DDS::DataWriter* writer,
        const ZRDynamicData* key,
        SecurityException* exception)=0;

    /**
    * @fn  bool BuiltinAccessControl::check_local_datawriter_dispose_instance( const PermissionsHandle* permissions_handle, const DataWriter* writer, const ZRDynamicData* key, SecurityException* exception);
    *
    * @brief   ȷ�ϱ���DataWriter�Ƿ��д���ʵ����Ȩ��.
    *
    * @author  zch
    * @date    2018/1/30
    *
    * @param   permissions_handle  ���ص�Ȩ�ޱ�ʶ.
    * @param   writer              ���ص�DataWriter.
    * @param   key                 ʵ����key.
    * @param [in,out]  exception   �����쳣������.
    *
    * @return ����ɹ�����true�����򷵻�false.
    */

    virtual bool check_local_datawriter_dispose_instance(
        const PermissionsHandle* permissions_handle,
        const DDS::DataWriter* writer,
        const ZRDynamicData* key,
        SecurityException* exception)=0;

    /**
    * @fn  bool BuiltinAccessControl::check_remote_participant( const PermissionsHandle permissions_handle, const DDS_DomainId_t domain_id, const ParticipantBuiltinTopicDataSecure* participant_data, SecurityException* exception);
    *
    * @brief   ȷ��Զ�˵���������Ƿ��������DDS Domain.
    *
    * @author  zch
    * @date    2018/1/30
    *
    * @param   permissions_handle  Զ��������ߵ�Ȩ�ޱ�ʶ.
    * @param   domain_id           ���.
    * @param   participant_data    Զ��������ߵ�ParticipantBuiltinTopicDataSecure.
    * @param [in,out]  exception   �����쳣������.
    *
    * @return  ����ɹ�����true�����򷵻�false.
    */

    virtual bool check_remote_participant(
        const PermissionsHandle permissions_handle,
        const DDS_DomainId_t domain_id,
        const DDS_ParticipantBuiltinTopicDataSecure* participant_data,
        SecurityException* exception)=0;

    /**
    * @fn  bool BuiltinAccessControl::check_remote_datawriter( const PermissionsHandle permissions_handle, const DDS_DomainId_t domain_id, const PublicationBuiltinTopicDataSecure* publication_data, SecurityException* exception);
    *
    * @brief   ���Զ�˵�DataWriter.
    *
    * @author  zch
    * @date    2018/1/30
    *
    * @param   permissions_handle  Զ��������ߵı�ʶ.
    * @param   domain_id           ���.
    * @param   publication_data    DataWriter��ص�PublicationBuiltinTopicDataSecure.
    * @param [in,out]  exception   �����쳣������.
    *
    * @return  ����ɹ�����true�����򷵻�false.
    */

    virtual bool check_remote_datawriter(
        const PermissionsHandle permissions_handle,
        const DDS_DomainId_t domain_id,
        const DDS_PublicationBuiltinTopicDataSecure* publication_data,
        SecurityException* exception)=0;

    /**
    * @fn  bool BuiltinAccessControl::check_remote_datareader( const PermissionsHandle permissions_handle, const DDS_DomainId_t domain_id, const SubscriptionBuiltinTopicDataSecure subscription_data, bool relay_only, SecurityException* exception);
    *
    * @brief   ���Զ�˵�DataReader.
    *
    * @author  zch
    * @date    2018/1/30
    *
    * @param   permissions_handle  Զ�˵�Ȩ�ޱ�ʶ.
    * @param   domain_id           ���.
    * @param   subscription_data   ��Զ��DataReader��ص�SubscriptionBuiltinTopicDataSecure.
    * @param [in,out]  relay_only  ����Զ��DataReader�Ƿ�������յ�����Ϣ��
    * @param [in,out]  exception   �����쳣������.
    *
    * @return  ����ɹ�����true�����򷵻�false.
    */

   virtual bool check_remote_datareader(
        const PermissionsHandle permissions_handle,
        const DDS_DomainId_t domain_id,
        const DDS_SubscriptionBuiltinTopicDataSecure* subscription_data,
        bool relay_only,
        SecurityException* exception)=0;

    /**
    * @fn  bool BuiltinAccessControl::check_remote_topic( const PermissionsHandle permissions_handle, const DDS_DomainId_t domain_id, const TopicBuiltinTopicData* topic_data, SecurityException* exception);
    *
    * @brief   ���Զ�˵�Topic.
    *
    * @author  zch
    * @date    2018/1/30
    *
    * @param   permissions_handle  Զ�˵�Ȩ�ޱ�ʶ.
    * @param   domain_id           ���.
    * @param   topic_data          ��Topic�������TopicBuiltInTopicData.
    * @param [in,out]  exception   �����쳣������.
    *
    * @return  �ɹ�����true�����򷵻�false.
    */

    virtual bool check_remote_topic(
        const PermissionsHandle permissions_handle,
        const DDS_DomainId_t domain_id,
        const TopicBuiltinTopicData* topic_data,
        SecurityException* exception)=0;

    /**
    * @fn  bool BuiltinAccessControl::check_local_datawriter_match( const PermissionsHandle writer_permisions_handle, const PermissionsHandle reader_permissions_handle, const PartitionQosPolicy* publisher_partition, const DataTag* writer_data_tag, const DataTag* reader_data_tag, SecurityException* exception);
    *
    * @brief   ��Ȿ��DataWriter��ƥ��.
    *
    * @author  zch
    * @date    2018/1/30
    *
    * @param   writer_permisions_handle    ��DataWriter��ص�������ߵ�Ȩ�ޱ�ʶ.
    * @param   reader_permissions_handle   ��DataReader��ص�������ߵ�Ȩ�ޱ�ʶ.
    * @param   publisher_partition         ��DataWriter��ص�Publisher��PartitionQosPolicy.
    * @param   writer_data_tag             ��DataWriter��ص�DataTags.
    * @param   reader_data_tag             ��DataReader��ص�DataTags.
    * @param [in,out]  exception           �����쳣������.
    *
    * @return  �ɹ�����true�����򷵻�false.
    */

    virtual bool check_local_datawriter_match(
        const PermissionsHandle writer_permisions_handle,
        const PermissionsHandle reader_permissions_handle,
        const DDS_PartitionQosPolicy* publisher_partition,
        const DDS_DataTags* writer_data_tag,
        const DDS_DataTags* reader_data_tag,
        SecurityException* exception)=0;

    /**
    * @fn  bool BuiltinAccessControl::check_local_datareader_match( const PermissionsHandle reader_permissions_handle, const PermissionsHandle writer_permissions_handle, const PartitionQosPolicy* subscriber_partiton, const DataTag* reader_data_tag, const DataTag* writer_data_tag, SecurityException* exception);
    *
    * @brief   ��Ȿ��DataReader��ƥ��.
    *
    * @author  zch
    * @date    2018/1/31
    *
    * @param   reader_permissions_handle   DataReader��ص�������ߵ�Ȩ�ޱ�ʶ.
    * @param   writer_permissions_handle   DataWrtier��ص�������ߵ�Ȩ�ޱ�ʶ.
    * @param   subscriber_partiton         ��DataReader��ص�Subscriber��PartitionQosPolicy.
    * @param   reader_data_tag             ��DataReader��ص�DataTags.
    * @param   writer_data_tag             ��DataWriter��ص�DataTags.
    * @param [in,out]  exception           �����쳣������.
    *
    * @return  �ɹ�����true�����򷵻�false.
    */

   virtual bool check_local_datareader_match(
        const PermissionsHandle reader_permissions_handle,
        const PermissionsHandle writer_permissions_handle,
        const DDS_PartitionQosPolicy* subscriber_partiton,
        const DDS_DataTags* reader_data_tag,
        const DDS_DataTags* writer_data_tag,
        SecurityException* exception)=0;

    /**
    * @fn  bool BuiltinAccessControl::check_remote_datawriter_register_instance( const PermissionsHandle permissions_handle, const DataReader* reader, const InstanceHandle_t* publication_handle, const ZRDynamicData* key, const InstanceHandle_t* instance_handle, SecurityException* exception);
    *
    * @brief   ���Զ��DataWriterע��ʵ����Ȩ��.
    *
    * @author  zch
    * @date    2018/1/31
    *
    * @param   permissions_handle  Զ��������ߵ�Ȩ�ޱ�ʶ.
    * @param   reader              ��Զ��DataWriter��ƥ���DataReader.
    * @param   publication_handle  Զ��DataWriter��Ψһ��ʶ.
    * @param   key                 ʵ����key����ʵ����Ҫȥƥ��ע��ʵ�������permissions.
    * @param   instance_handle     ʵ����Ψһ��ʶ.
    * @param [in,out]  exception   �����쳣������.
    *
    * @return  �ɹ�����true�����򷵻�false.
    */

   virtual bool check_remote_datawriter_register_instance(
        const PermissionsHandle permissions_handle,
        const DDS::DataReader* reader,
        const DDS_InstanceHandle_t* publication_handle,
        const ZRDynamicData* key,
        const DDS_InstanceHandle_t* instance_handle,
        SecurityException* exception)=0;

    /**
    * @fn  bool BuiltinAccessControl::check_remote_datawriter_dispose_instance( const PermissionsHandle permissions_handle, const DataReader* reader, const InstanceHandle_t* publication_handle, const ZRDynamicData* key, SecurityException* exception);
    *
    * @brief  ���Զ��DataWriter����ʵ����Ȩ��.
    *
    * @author  zch
    * @date    2018/1/31
    *
    * @param   permissions_handle  Զ��������ߵ�Ȩ�ޱ�ʶ.
    * @param   reader              ��DataWriterƥ��ı��ص�DataReader.
    * @param   publication_handle  DataWriter��Ψһ��ʶ.
    * @param   key                 ʵ����key.
    * @param [in,out]  exception   �����쳣������.
    *
    * @return  �ɹ�����true�����󷵻�false.
    */

    virtual bool check_remote_datawriter_dispose_instance(
        const PermissionsHandle permissions_handle,
        const DDS::DataReader* reader,
        const DDS_InstanceHandle_t* publication_handle,
        const ZRDynamicData* key,
        SecurityException* exception)=0;

    /**
    * @fn  PermissionsToken BuiltinAccessControl::get_permissions_token( const PermissionsHandle handle, SecurityException* exception);
    *
    * @brief  ���PermissionsToken.
    *
    * @author  zch
    * @date    2018/1/31
    *
    * @param   permissions_token   ������PermissionsToken����Ϣ.
    * @param   handle              ������ߵ�Ȩ�ޱ�ʶ.
    * @param [in,out]  exception   �����쳣������.
    *
    * @return  The permissions token.
    */

    virtual bool get_permissions_token(
        PermissionsToken* permissions_token,
        const PermissionsHandle handle,
        SecurityException* exception)=0;

    /**
    * @fn  PermissionsCredentialToken BuiltinAccessControl::get_permissions_credential_token( const PermissionsHandle handle, SecurityException* exception);
    *
    * @brief   ���PermissionsCredentialToken.
    *
    * @author  zch
    * @date    2018/1/31
    *
    * @param   permissions_credential_token              ������PermissionsCredentialToken��Ϣ.
    * @param   handle              ����������ߵ�Ȩ�ޱ�ʶ.
    * @param [in,out]  exception   �����쳣������.
    *
    * @return  The permissions credential token.
    */

    virtual bool get_permissions_credential_token(
        PermissionsCredentialToken* permissions_credential_token,
        const PermissionsHandle handle,
        SecurityException* exception)=0;

    /**
    * @fn  bool BuiltinAccessControl::set_listener( const AccessControlListener* listener, SecurityException* exception);
    *
    * @brief   ΪAccessControl������ü�����.
    *
    * @author  zch
    * @date    2018/1/31
    *
    * @param   listener            ������.
    * @param [in,out]  exception   �����쳣������.
    *
    * @return  �ɹ�����true�����򷵻�false.
    */

    virtual bool set_listener(
        AccessControlListener* listener,
        SecurityException* exception)=0;

    /**
    * @fn  bool BuiltinAccessControl::return_permissions_token( const PermissionsToken* token, SecurityException* exception);
    *
    * @brief   �黹PermissionsToken��ռ�Ŀռ�.
    *
    * @author  zch
    * @date    2018/1/31
    *
    * @param   token               ��Ҫ�黹�ռ��PermissionsToken.
    * @param [in,out]  exception   �����쳣������.
    *
    * @return  �ɹ�����true�����򷵻�false.
    */

    virtual bool return_permissions_token(
        PermissionsToken* token,
        SecurityException* exception)=0;

    /**
    * @fn  bool BuiltinAccessControl::return_permissions_credential_token( const PermissionsCredentialToken* permissions_credential_token, SecurityException* exception);
    *
    * @brief   �黹PermissionsCredentialToken��ռ�Ŀռ�.
    *
    * @author  zch
    * @date    2018/1/31
    *
    * @param   permissions_credential_token    ��Ҫ�黹�ռ��PermissionsCredentialToken.
    * @param [in,out]  exception               �����쳣������.
    *
    * @return  �ɹ�����true�����򷵻�false.
    */

   virtual bool return_permissions_credential_token(
        PermissionsCredentialToken* permissions_credential_token,
        SecurityException* exception)=0;

    /**
    * @fn  bool BuiltinAccessControl::get_participant_sec_attributes( const PermissionsHandle permissions_handle, ParticipantSecurityAttributes* attributes, SecurityException* exception);
    *
    * @brief   ���ParticipantSecurityAttributes��Ϣ.
    *
    * @author  zch
    * @date    2018/1/31
    *
    * @param   permissions_handle  ����������ߵ�Ȩ�ޱ�ʶ.
    * @param [in,out]  attributes  ����ParticipantSecurityAttributes��Ϣ.
    * @param [in,out]  exception   �����쳣������.
    *
    * @return  �ɹ�����true�����򷵻�false.
    */

   virtual bool get_participant_sec_attributes(
        const PermissionsHandle permissions_handle,
        ParticipantSecurityAttributes* attributes,
        SecurityException* exception)=0;

    /**
    * @fn  bool BuiltinAccessControl::get_datawriter_sec_attributes( const PermissionsHandle permissions_handle, const char* topic_name, const PartitionQosPolicy* partition, const DataTagQosPolicy* data_tag, EndpointSecurityAttributes* attributes, SecurityException* exception);
    *
    * @brief   ���DataWriter��EndpointSecurityAttributes��Ϣ.
    *
    * @author  zch
    * @date    2018/1/31
    *
    * @param   permissions_handle  ����������ߵ�Ȩ�ޱ�ʶ.
    * @param   topic_name          ������.
    * @param   partition           DataWriter������Publisher��PartitionQosPolicy.
    * @param   data_tag            DataWriter��DataTagQosPolicy.
    * @param [in,out]  attributes   ����EndpointSecurityAttributes��Ϣ��.
    * @param [in,out]  exception   �����쳣������.
    *
    * @return  �ɹ�����true�����򷵻�false.
    */

    virtual bool get_datawriter_sec_attributes(
        const PermissionsHandle permissions_handle,
        const char* topic_name,
        const DDS_PartitionQosPolicy* partition,
        const DDS_DataTagQosPolicy* data_tag,
        EndpointSecurityAttributes* attributes,
        SecurityException* exception)=0;

    /**
    * @fn  bool BuiltinAccessControl::get_datareader_sec_attributes( const PermissionsHandle permissions_handle, const char* topic_name, const PartitionQosPolicy* partition, const DataTagQosPolicy* data_tag, EndpointSecurityAttributes* attributes, SecurityException* exception);
    *
    * @brief   ���DataReader��EndpointSecurityAttributes.
    *
    * @author  zch
    * @date    2018/1/31
    *
    * @param   permissions_handle  ���ص�������ߵ�Ȩ�ޱ�ʶ.
    * @param   topic_name          ������.
    * @param   partition           DataReader������Subscriber��PartitionQosPolicy.
    * @param   data_tag            DataReader��DataTagQosPolicy.
    * @param [in,out]  attributes   ����EndpointSecurityAttributes��Ϣ.
    * @param [in,out]  exception   �����쳣������.
    *
    * @return  �ɹ�����true�����򷵻�false.
    */

    virtual bool get_datareader_sec_attributes(
        const PermissionsHandle permissions_handle,
        const char* topic_name,
        const DDS_PartitionQosPolicy* partition,
        const DDS_DataTagQosPolicy* data_tag,
        EndpointSecurityAttributes* attributes,
        SecurityException* exception)=0;

    /**
     * @fn  virtual bool AccessControl::return_permissions_handle( PermissionsHandle permissions_handle, SecurityException* exception)=0;
     *
     * @brief   �ͷ�handle��ռ�õĿռ�.
     *
     * @author  zch
     * @date    2018/1/31
     *
     * @param   permissions_handle  ��Ҫ�ͷſռ�PermissionsHandle.
     * @param [in,out]  exception   �����쳣������.
     *
     * @return  �ɹ�����true��ʧ�ܷ���false.
     */

    virtual bool return_permissions_handle(
        PermissionsHandle permissions_handle,
        SecurityException* exception)=0;

    /**
     * @fn  virtual bool AccessControl::return_participant_sec_attributes( ParticipantSecurityAttributes* attributes, SecurityException* exception) = 0;
     *
     * @brief    �ͷ�ParticipantSecurityAttributes��ռ�õĿռ�.
     *
     * @author  zch
     * @date    2018/5/21
     *
     * @param  attributes          ��Ҫ�ͷſռ��attributes.
     * @param [in,out]  exception  �����쳣������.
     *
     * @return  �ɹ�����true��ʧ�ܷŻ�false.
     */

    virtual bool return_participant_sec_attributes(
        ParticipantSecurityAttributes* attributes,
        SecurityException* exception) = 0;
    /**
    * @fn  virtual bool AccessControl::return_participant_sec_attributes( ParticipantSecurityAttributes* attributes, SecurityException* exception) = 0;
    *
    * @brief    �ͷ�EndpointSecurityAttributes��ռ�õĿռ�.
    *
    * @author  zch
    * @date    2018/5/21
    *
    * @param  attributes          ��Ҫ�ͷſռ��attributes.
    * @param [in,out]  exception  �����쳣������.
    *
    * @return  �ɹ�����true��ʧ�ܷŻ�false.
    */
    virtual bool return_datawriter_sec_attributes(
        EndpointSecurityAttributes* attributes,
        SecurityException* exception) = 0;
    /**
    * @fn  virtual bool AccessControl::return_participant_sec_attributes( ParticipantSecurityAttributes* attributes, SecurityException* exception) = 0;
    *
    * @brief    �ͷ�EndpointSecurityAttributes��ռ�õĿռ�.
    *
    * @author  zch
    * @date    2018/5/21
    *
    * @param  attributes          ��Ҫ�ͷſռ��attributes.
    * @param [in,out]  exception  �����쳣������.
    *
    * @return  �ɹ�����true��ʧ�ܷŻ�false.
    */
    virtual bool return_datareader_sec_attributes(
        EndpointSecurityAttributes* attributes,
        SecurityException* exception) = 0;
};

#endif // AccessControlPlugin_h__
