#ifndef Authentication_h__
#define Authentication_h__

#include "DDSBuiltinSecurityCommon.h"
#include "DomainId_t.h"
#include "DomainParticipantQos.h"
#include "AuthenticationListener.h"
/** return code */
typedef enum ValidationResult_t
{
    /**  ��֤�ɹ� */
    VALIDATION_OK,
    /**  ��֤ʧ�� */
    VALIDATION_FAILED,
    /** ��֤�����У��Ժ�����*/
    VALIDATION_PENDING_RETRY,
    /** ��Ҫ����������Ϣ */
    VALIDATION_PENDING_HANDSHAKE_REQUEST,
    /** ��֤���ڹ���״̬��DDS implementation �ȴ�BuiltinParticipantMessageReader������Ϣ */
    VALIDATION_PENDING_HANDSHAKE_MESSAGE,
    /** ��֤�ɹ�������DDS implementationӦ��ʹ��BuiltinParticipantMessageWriter������Ϣ */
    VALIDATION_OK_FINAL_MESSAGE
}ValidationResult_t;

/** ����������֤domainparticipant*/
typedef DDSSecHandle IdentityHandle;
/** ����������������Э���״̬����*/
typedef DDSSecHandle HandshakeHandle;
typedef DDSSecHandle SharedSecretHandle;

class Authentication
{

public:
    virtual ~Authentication(){};

    /**
     * @fn virtual ValidationResult_t validate_local_identity(
     *     IdentityHandle *local_identity_handle,
     *     DDS_BuiltinTopicKey_t adjusted_participant_key,
     *     const DDS_DomainId_t domain_id,
     *     const DDS_DomainParticipantQos *participant_qos,
     *     const DDS_BuiltinTopicKey_t candidate_participant_key,
     *     SecurityException *exception) = 0;
     *
     * @brief ��֤����DomainParticipant�����
     *
     * @author lin
     *
     * @param [out] local_identity_handle    ����������֤participant.
     * @param [out] adjusted_participant_key ���ɵ�participant key.
     * @param domain_id                      Domainparticipant��Domain id.
     * @param participant_qos                Domainparticipant����DomianparticipantQos.
     * @param candidate_participant_key      DDS implementation������֤domainparticipantʹ�õ�key.
     * @param [out] exception                �����쳣������.
     *
     * @return ���������ɹ���ʧ�ܵ�ֵ.
     */
    virtual ValidationResult_t validate_local_identity(
        IdentityHandle *local_identity_handle,
        DDS_BuiltinTopicKey_t adjusted_participant_key,
        const DDS_DomainId_t domain_id,
        const DDS_DomainParticipantQos *participant_qos,
        const DDS_BuiltinTopicKey_t candidate_participant_key,
        SecurityException *exception) = 0;

    /**
     * @fn virtual ValidationResult_t validate_remote_identity(
     *     IdentityHandle *remote_identity_handle,
     *     const IdentityHandle local_identity_handle,
     *     IdentityToken *remote_identity_token,
     *     const DDS_BuiltinTopicKey_t remote_participant_key,
     *     SecurityException *exception) = 0;
     *
     * @brief ��֤Զ��domainparticipant���.
     *
     * @author lin
     *
     * @param [out] remote_identity_handle   ΪԶ�˲����ߴ�����handle,���ڱ�����֤.
     * @param local_identity_handle          ������֤��ȡ��handle�����պ���validate_local_identity.
     * @param [in,out] remote_identity_token ���յ�token,����Զ�˵��õĺ���get_identity_token
     * @param remote_participant_key         ��Զ�˻�ȡ��pariticipant key.
     * @param [out] exception                �����쳣������.
     *
     * @return ���������ɹ���ʧ�ܵ�ֵ.
     */
    virtual	ValidationResult_t validate_remote_identity(
        IdentityHandle *remote_identity_handle,
        const IdentityHandle local_identity_handle,
        IdentityToken *remote_identity_token,
        const DDS_BuiltinTopicKey_t remote_participant_key,
        SecurityException *exception) = 0;

    /**
     * @fn virtual ValidationResult_t begin_handshake_request(
     *     HandshakeHandle *handshake_handle,
     *     HandshakeMessageToken *handshake_message_token,
     *     const IdentityHandle initiator_identity_handle,
     *     const IdentityHandle replier_identity_handle,
     *     const char* builtin_topic_data,
     *     ZR_UINT32 builtin_topic_data_length,
     *     SecurityException *exception) = 0;
     *
     * @brief ������������.
     *
     * @author lin
     *
     * @param [out] handshake_handle        ���������handle.
     * @param [out] handshake_message_token ������Ϣ���.
     * @param initiator_identity_handle     ����handshake��handle.
     * @param replier_identity_handle       ���ֱ����˵�handle.
     * @param builtin_topic_data            �����ߵ�����topic����.
     * @param builtin_topic_data_length     ����topic���ݳ���.
     * @param [out] exception               �����쳣������.
     *
     * @return ���������ɹ���ʧ�ܵ�ֵ.
     */
    virtual ValidationResult_t begin_handshake_request(
        HandshakeHandle *handshake_handle,
        HandshakeMessageToken *handshake_message_token,
        const IdentityHandle initiator_identity_handle,
        const IdentityHandle replier_identity_handle,
        const char* builtin_topic_data,
        ZR_UINT32 builtin_topic_data_length,
        SecurityException *exception) = 0;

    /**
     * @fn virtual ValidationResult_t begin_handshake_reply(
     *     HandshakeHandle *handshake_handle,
     *     HandshakeMessageToken *handshake_message_out,
     *     HandshakeMessageToken *handshake_message_in,
     *     const IdentityHandle initiator_identity_handle,
     *     const IdentityHandle replier_identity_handle,
     *     const char* builtin_topic_data,
     *     ZR_UINT32 builtin_topic_data_length,
     *     SecurityException *exception) = 0;
     *
     * @brief �ظ���������.
     *
     * @author lin
     *
     * @param [out] handshake_handle        ���ֵ�handle.
     * @param [out] handshake_message_out   ������handshake���.
     * @param [in,out] handshake_message_in �����handshake���(Զ�˴����token).
     * @param initiator_identity_handle     �������ֵ�handle.
     * @param replier_identity_handle       ���ֱ����˵�handle.
     * @param builtin_topic_data            �����ߵ�����topic����.
     * @param builtin_topic_data_length     ����topic���ݳ���.
     * @param [out] exception               �����쳣������.
     *
     * @return ���������ɹ���ʧ�ܵ�ֵ.
     */
    virtual ValidationResult_t begin_handshake_reply(
        HandshakeHandle *handshake_handle,
        HandshakeMessageToken *handshake_message_out,
        HandshakeMessageToken *handshake_message_in,
        const IdentityHandle initiator_identity_handle,
        const IdentityHandle replier_identity_handle,
        const char* builtin_topic_data,
        ZR_UINT32 builtin_topic_data_length,
        SecurityException *exception) = 0;

    /**
     * @fn virtual ValidationResult_t process_handshake(
     *     HandshakeMessageToken *handshake_message_out,
     *     HandshakeMessageToken *handshake_message_in,
     *     const HandshakeHandle handshake_handle, SecurityException *exception) = 0;
     *
     * @brief ����һ������.
     *
     * @author lin
     *
     * @param [out] handshake_message_out   ���ص���Ϣ.
     * @param [in,out] handshake_message_in �������Ϣ.
     * @param handshake_handle              ���ֵ�handle.
     * @param [out] exception               �����쳣������.
     *
     * @return ���������ɹ���ʧ�ܵ�ֵ.
     */
    virtual ValidationResult_t process_handshake(
        HandshakeMessageToken *handshake_message_out,
        HandshakeMessageToken *handshake_message_in,
        const HandshakeHandle handshake_handle,
        SecurityException *exception) = 0;

    /**
     * @fn virtual SharedSecretHandle get_shared_secret(
     *     const HandshakeHandle handshake_handle, SecurityException *exception) = 0;
     *
     * @brief ��ȡ��Կ.
     *
     * @author lin
     *
     * @param handshake_handle ���ֵ�handle.
     * @param [out] exception  �����쳣������.
     *
     * @return SharedSecretHandle.
     */
    virtual SharedSecretHandle get_shared_secret(
        const HandshakeHandle handshake_handle,
        SecurityException *exception) = 0;

    /**
     * @fn virtual bool get_authenticated_peer_credential_token(
     *     AuthenticatedPeerCredentialToken *peer_credential_token,
     *     const HandshakeHandle handshake_handle, SecurityException *exception) = 0;
     *
     * @brief Gets authenticated peer credential token.
     *
     * @author lin
     *
     * @param [out] peer_credential_token The peer credential token.
     * @param handshake_handle            ���ֵ�handle.
     * @param [out] exception             �����쳣������.
     *
     * @return �ɹ�����true��ʧ�ܷ���false.
     */
    virtual bool get_authenticated_peer_credential_token(
        AuthenticatedPeerCredentialToken *peer_credential_token,
        const HandshakeHandle handshake_handle,
        SecurityException *exception) = 0;

    /**
     * @fn virtual bool get_identity_token(
     *     IdentityToken *identity_token,
     *     const IdentityHandle handle,
     *     SecurityException *exception) = 0;
     *
     * @brief ��ȡIdentityToken.
     *
     * @author lin
     *
     * @param [out] identity_token ͨ��handle���ҵ���token.
     * @param handle               ��֤�ı�ʶ,���Ժ���validate_local_identity
     * @param [out] exception      �����쳣������.
     *
     * @return �ɹ�����true��ʧ�ܷ���false.
     */
    virtual bool get_identity_token(
        IdentityToken *identity_token,
        const IdentityHandle handle,
        SecurityException *exception) = 0;

    /**
     * @fn virtual bool set_permissions_credential_and_token(
     *     IdentityHandle handle,
     *     const PermissionsCredentialToken *permissions_credential_token,
     *     const PermissionsToken *permissions_token,
     *     SecurityException *exception) = 0;
     *
     * @brief Sets permissions credential and token.
     *
     * @author lin
     *
     * @param handle                       ���Ժ���valid_local_identity.
     * @param permissions_credential_token The permissions credential token.
     * @param permissions_token            The permissions token.
     * @param [out] exception              �����쳣������.
     *
     * @return �ɹ�����true��ʧ�ܷ���false.
     */
    virtual bool set_permissions_credential_and_token(
        IdentityHandle handle,
        const PermissionsCredentialToken *permissions_credential_token,
        const PermissionsToken *permissions_token,
        SecurityException *exception) = 0;

    /**
     * @fn virtual bool set_listener(
     *     AuthenticationListener *listener, SecurityException *exception) = 0;
     *
     * @brief ����һ��������.
     *
     * @author lin
     *
     * @param [in,out] listener ����Authentication����ļ�����.
     * @param [out] exception   �����쳣������.
     *
     * @return �ɹ�����true��ʧ�ܷ���false.
     */
    virtual bool set_listener(
        AuthenticationListener *listener,
        SecurityException *exception) = 0;

    /**
     * @fn virtual bool return_identity_token(
     *     IdentityToken *token, SecurityException *exception) = 0;
     *
     * @brief ����IdentityToken����
     *
     * @author lin
     *
     * @param [in,out] token  ���ٵ�IdentityToken.
     * @param [out] exception �����쳣������.
     *
     * @return �ɹ�����true��ʧ�ܷ���false.
     */
    virtual bool return_identity_token(
        IdentityToken *token,
        SecurityException *exception) = 0;

    /**
     * @fn virtual bool return_authenticated_peer_credential_token(
     *     AuthenticatedPeerCredentialToken *peer_credential_token,
     *     SecurityException *exception) = 0;
     *
     * @brief ����AuthenticatedPeerCredentialToken����
     *
     * @author lin
     *
     * @param [in,out] peer_credential_token    ���ٵ�AuthenticatedPeerCredentialToken,
     *                                          ���Ժ���get_authenticated_peer_credential_token.
     * @param [out] exception                �����쳣������.
     *
     * @return �ɹ�����true��ʧ�ܷ���false.
     */
    virtual bool return_authenticated_peer_credential_token(
        AuthenticatedPeerCredentialToken *peer_credential_token,
        SecurityException *exception) = 0;

    /**
     * @fn virtual bool return_handshake_handle(
     *     const HandshakeHandle handshake_handle, SecurityException *exception) = 0;
     *
     * @brief ����HandshakeHandle.
     *
     * @author lin
     *
     * @param handshake_handle ���ٵ�HandshakeHandle,���Ժ���begin_handshake_request����begin_handshake_reply.
     * @param [out] exception  �����쳣������.
     *
     * @return �ɹ�����true��ʧ�ܷ���false.
     */
    virtual bool return_handshake_handle(
        const HandshakeHandle handshake_handle,
        SecurityException *exception) = 0;

    /**
     * @fn virtual bool return_identity_handle(
     *     const IdentityHandle identity_handle, SecurityException *exception) = 0;
     *
     * @brief ����IdentityHandle����
     *
     * @author lin
     *
     * @param identity_handle ���ٵ�IdentityHandle,����validate_local_identity����validate_remote_identity
     * @param [out] exception �����쳣������.
     *
     * @return �ɹ�����true��ʧ�ܷ���false.
     */
    virtual bool return_identity_handle(
        const IdentityHandle identity_handle,
        SecurityException *exception) = 0;

    /**
     * @fn virtual bool return_sharedsecret_handle(
     *     const SharedSecretHandle sharedsecret_handle, SecurityException *exception) = 0;
     *
     * @brief ����SharedSecretHandle����
     *
     * @author lin
     *
     * @param sharedsecret_handle ���ٵ�SharedSecretHandle,���Ժ���get_shared_secret.
     * @param [out] exception     �����쳣������.
     *
     * @return �ɹ�����true��ʧ�ܷ���false.
     */
    virtual  bool return_sharedsecret_handle(
        const SharedSecretHandle sharedsecret_handle,
        SecurityException *exception) = 0;

   /**
    * @fn virtual bool return_handshake_token(
    *     HandshakeMessageToken *handshake_token, SecurityException *exception) = 0;
    *
    * @brief �ͷ�handshake_token
    *
    * @author lin
    *
    * @param [in,out] handshake_token ���ٵ�HandshakeMessageToken.
    * @param [in,out] exception       �����쳣������..
    *
    * @return true if it succeeds, false if it fails.
    */
   virtual bool return_handshake_token(
       HandshakeMessageToken *handshake_token,
       SecurityException *exception) = 0;

};


#endif //Authentication_h__
