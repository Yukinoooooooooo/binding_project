#ifndef CryptoKeyFactory_h__
#define CryptoKeyFactory_h__


#include "CryCommonSource.h"

class CryptoKeyFactory
{
public:
    virtual ~CryptoKeyFactory(){};
    /**
    * @fn  ParticipantCryptoHandle CryptoKeyFactory::register_local_participant( IdentityHandle participant_identity, PermissionsHandle participant_permissions, PropertySeq participant_properties, SecurityException* exception);
    *
    * @brief   ע��һ�����ص�participant���ܾ��.
    *
    * @author  Lxx
    * @date    2018/1/30
    *
    * @param   participant_identity    participant�ı�ʶ.
    * @param   participant_permissions participant�������Ϣ.
    * @param   participant_properties  participant�Ĺ�������.
    * @param [out] exception           ��������ʱ�Ĵ��󷵻�ֵ.
    *
    * @return  ����ע���Participant�ļ��ܾ��.
    */

    virtual ParticipantCryptoHandle register_local_participant(
        IdentityHandle  participant_identity,
        PermissionsHandle participant_permissions,
        const DDS_PropertySeq* participant_properties,
        SecurityException* exception) = 0;

    /**
    * @fn  ParticipantCryptoHandle CryptoKeyFactory::register_matched_remote_participant( ParticipantCryptoHandle remote_participant_identity, ParticipantCryptoHandle local_participant_crypto_handle, ShareSecret sharesecret, PermissionsHandle remote_participant_permissions, SecurityException* exception);
    *
    * @brief   ΪԶ�˵�participantע��һ�����ܾ��.
    *
    * @author  Lxx
    * @date    2018/1/30
    *
    * @param   remote_participant_identity     Զ��participant�ı�ʶ.
    * @param   local_participant_crypto_handle ��Զ��participant��ƥ��ı���participant�ļ��ܾ��.
    * @param   sharesecret                     ������Կ.
    * @param   remote_participant_permissions  Զ��participant�������Ϣ.
    * @param [out] exception                   ��������ʱ�Ĵ��󷵻�ֵ.
    *
    * @return  ����ע���Զ��Participant�ļ��ܾ��.
    */

    virtual ParticipantCryptoHandle register_matched_remote_participant(
        IdentityHandle remote_participant_identity,
        ParticipantCryptoHandle local_participant_crypto_handle,
        SharedSecretHandle sharesecret,
        PermissionsHandle remote_participant_permissions,
        SecurityException* exception) = 0;

    /**
    * @fn  DatareaderCryptoHandle CryptoKeyFactory::register_local_datareader( ParticipantCryptoHandle participant_crypto, PropertySeq datareader_properties, SecurityException* exception);
    *
    * @brief   ע��һ�����ص�datareader�ļ��ܾ��.
    *
    * @author  Lxx
    * @date    2018/1/30
    *
    * @param   participant_crypto      datareader����participant�ļ��ܾ��.
    * @param   datareader_properties   datareader�Ĺ�����Ϣ.
    * @param [out] exception           ��������ʱ�Ĵ��󷵻�ֵ.
    *
    * @return  ����ע���datareader�ļ��ܾ��.
    */

    virtual DatareaderCryptoHandle register_local_datareader(
        ParticipantCryptoHandle participant_crypto,
        const DDS_PropertySeq* datareader_properties,
        SecurityException* exception) = 0;

    /**
    * @fn  DatawriterCryptoHandle CryptoKeyFactory::register_local_datawriter( ParticipantCryptoHandle participant_crypto, PropertySeq datawriter_properties, SecurityException* exception);
    *
    * @brief   ע��һ�����ص�datawriter�ļ��ܾ��.
    *
    * @author  Lxx
    * @date    2018/1/30
    *
    * @param   participant_crypto      datawriter����participant�ļ��ܾ��.
    * @param   datawriter_properties   datawriter�Ĺ�����Ϣ.
    * @param [out] exception           ��������ʱ�Ĵ��󷵻�ֵ.
    *
    * @return  ����ע���datawriter�ļ��ܾ��.
    */

    virtual DatawriterCryptoHandle register_local_datawriter(
        ParticipantCryptoHandle participant_crypto,
        const DDS_PropertySeq* datawriter_properties,
        SecurityException* exception) = 0;

    /**
    * @fn  DatareaderCryptoHandle CryptoKeyFactory::register_matched_remote_datareader( DatawriterCryptoHandle local_datawriter_crypto_handle, ParticipantCryptoHandle remote_participant_crypto, ShareSecret shared_secret, bool relay_only, SecurityException* exception);
    *
    * @brief   ΪԶ�˵�datareaderע��һ�����ܾ��.
    *
    * @author  Lxx
    * @date    2018/1/30
    *
    * @param   local_datawriter_crypto_handle  ��Զ����reader��ƥ��ı���writer�ļ��ܾ��.
    * @param   remote_participant_crypto       Զ��participant�ļ��ܾ��.
    * @param   shared_secret                   ������Կ.
    * @param   relay_only                      �Ƿ�ֻ����ת��.
    * @param [out] exception                   ��������ʱ�Ĵ��󷵻�ֵ.
    *
    * @return  ����ע���datareader�ļ��ܾ��.
    */

    virtual DatareaderCryptoHandle register_matched_remote_datareader(
        DatawriterCryptoHandle local_datawriter_crypto_handle,
        ParticipantCryptoHandle remote_participant_crypto,
        SharedSecretHandle shared_secret,
        bool relay_only,
        SecurityException* exception) = 0;

    /**
    * @fn  DatawriterCryptoHandle CryptoKeyFactory::regiser_matched_remote_datawriter( DatawriterCryptoHandle local_datareader_crypto_handle, ParticipantCryptoHandle remote_participant_crypto, ShareSecret shared_secret, bool relay_only, SecurityException* exception);
    *
    * @brief   ΪԶ�˵�datawriterע��һ�����ܾ��.
    *
    * @author  Lxx
    * @date    2018/1/30
    *
    * @param   local_datareader_crypto_handle  ��Զ��writer��ƥ��ı���reader�ļ��ܾ��.
    * @param   remote_participant_crypto       Զ��participant�ļ��ܾ��.
    * @param   shared_secret                   ������Կ.
    * @param [out] exception                   ��������ʱ�Ĵ��󷵻�ֵ.
    *
    * @return  ����ע���datawriter�ļ��ܾ��.
    */

    virtual DatawriterCryptoHandle register_matched_remote_datawriter(
        DatareaderCryptoHandle local_datareader_crypto_handle,
        ParticipantCryptoHandle remote_participant_crypto,
        SharedSecretHandle shared_secret,
        SecurityException* exception) = 0;

    /**
    * @fn  bool CryptoKeyFactory::unregister_participant( ParticipantCryptoHandle participant_crypto_handle, SecurityException* exception);
    *
    * @brief   ����participant�ļ��ܾ��.
    *
    * @author  Lxx
    * @date    2018/1/30
    *
    * @param   participant_crypto_handle   ����Ҫ���ٵ�participant���.
    * @param [out] exception               ��������ʱ�Ĵ��󷵻�.
    *
    * @return  ���ٳɹ��򷵻�true��ʧ���򷵻�false.
    */

    virtual bool unregister_participant(
        ParticipantCryptoHandle participant_crypto_handle,
        SecurityException* exception) = 0;

    /**
    * @fn  bool CryptoKeyFactory::unregister_datawriter( DatawriterCryptoHandle datawriter_crypto_handle, SecurityException* exception);
    *
    * @brief   ����datawriter�ļ��ܾ��.
    *
    * @author  Lxx
    * @date    2018/1/30
    *
    * @param   datawriter_crypto_handle    ����Ҫ���ٵ�datawriter���.
    * @param [out] exception               ��������ʱ�Ĵ��󷵻�.
    *
    * @return  ���ٳɹ��򷵻�true��ʧ���򷵻�false.
    */

    virtual bool unregister_datawriter(
        DatawriterCryptoHandle datawriter_crypto_handle,
        SecurityException* exception) = 0;

    /**
    * @fn  bool CryptoKeyFactory::unregister_datareader( DatareaderCryptoHandle datareader_crypto_handle, SecurityException* exception);
    *
    * @brief   ����datareader�ļ��ܾ��.
    *
    * @author  Lxx
    * @date    2018/1/30
    *
    * @param   datareader_crypto_handle    ����Ҫ���ٵ�datareader���.
    * @param [out] exception               ��������ʱ�Ĵ��󷵻�.
    *
    * @return  ���ٳɹ��򷵻�true��ʧ���򷵻�false.
    */

    virtual bool unregister_datareader(
        DatareaderCryptoHandle datareader_crypto_handle,
        SecurityException* exception) = 0;


};

#endif // CryptoKeyFactory_h__
