#ifndef CryptoKeyExchange_h__
#define CryptoKeyExchange_h__

#include "CryCommonSource.h"

class CryptoKeyExchange
{
public:

    virtual ~CryptoKeyExchange(){};

    /**
    * @fn  bool CryptoKeyExchange::create_local_participant_crypto_tokens( ParticipantCryptoTokenSeq &local_participant_crypto_tokens, ParticipantCryptoHandle locat_participant, ParticipantCryptoHandle remote_participant, SecurityException* exception);
    *
    * @brief   ��������participant�Ľ�����Ϣ.
    *
    * @author  Lxx
    * @date    2018/1/30
    *
    * @param [out] local_participant_crypto_tokens ����Ľ�����Ϣ.
    * @param   locat_participant                   ����participant�ļ��ܾ��.
    * @param   remote_participant                  Զ��participant�ļ��ܾ��.
    * @param [out] exception                       ��������ʱ�Ĵ��󷵻�.
    *
    * @return  �����ɹ��򷵻�true��ʧ���򷵻�false.
    */

    virtual bool create_local_participant_crypto_tokens(
        ParticipantCryptoTokenSeq* local_participant_crypto_tokens,
        ParticipantCryptoHandle locat_participant,
        ParticipantCryptoHandle remote_participant,
        SecurityException* exception) = 0;

    /**
    * @fn  bool CryptoKeyExchange::set_remote_participant_crypto_tokens( ParticipantCryptoHandle local_participant_crypto, ParticipantCryptoHandle remote_participant_crypto, ParticipantCryptoTokenSeq remote_participant_tokens, SecurityException* exception);
    *
    * @brief   ���ݽ�����Ϣ����Զ��participant���ܾ������Ϣ.
    *
    * @author  Lxx
    * @date    2018/1/30
    *
    * @param   local_participant_crypto    ����participant�ļ��ܾ��.
    * @param   remote_participant_crypto   Զ��participant�ļ��ܾ��.
    * @param   remote_participant_tokens   Զ��participant�Ľ�����Ϣ.
    * @param [out] exception               ��������ʱ�Ĵ��󷵻�.
    *
    * @return  ���óɹ��򷵻�true��ʧ���򷵻�false.
    */

    virtual bool set_remote_participant_crypto_tokens(
        ParticipantCryptoHandle local_participant_crypto,
        ParticipantCryptoHandle remote_participant_crypto,
        const ParticipantCryptoTokenSeq* remote_participant_tokens,
        SecurityException* exception) = 0;

    /**
    * @fn  bool CryptoKeyExchange::create_local_datawriter_crypto_tokens( ParticipantCryptoTokenSeq &local_datawriter_crypto_tokens, DatawriterCryptoHandle local_datawriter_crypto, DatareaderCryptoHandle remote_datareader_crypto, SecurityException* exception);
    *
    * @brief   ����datawriter�Ľ�����Ϣ.
    *
    * @author  Lxx
    * @date    2018/1/30
    *
    * @param [out] local_datawriter_crypto_tokens  ����datawriter�Ľ�����Ϣ.
    * @param   local_datawriter_crypto             ����datawriter�ļ��ܾ��.
    * @param   remote_datareader_crypto            �뱾��datawriter��ƥ���Զ�˵�datareader���ܾ��.
    * @param [out] exception                       ��������ʱ�Ĵ��󷵻�.
    *
    * @return  �����ɹ��򷵻�true��ʧ���򷵻�false.
    */

    virtual bool create_local_datawriter_crypto_tokens(
        DatawriterCryptoTokenSeq* local_datawriter_crypto_tokens,
        DatawriterCryptoHandle local_datawriter_crypto,
        DatareaderCryptoHandle remote_datareader_crypto,
        SecurityException* exception) = 0;

    /**
    * @fn  bool CryptoKeyExchange::set_remote_datawriter_crypto_tokens( DatareaderCryptoHandle local_datareader_crypto, DatawriterCryptoHandle remote_datawriter_crypto, int remote_datawriter_token, SecurityException* exception);
    *
    * @brief   ����Զ��datawriter�Ľ�����Ϣ����Զ��datawriter�ļ��ܾ��.
    *
    * @author  Lxx
    * @date    2018/1/30
    *
    * @param   local_datareader_crypto     ��Զ��datawriter��ƥ��ı���datareader�ļ��ܾ��.
    * @param   remote_datawriter_crypto    Զ��datawriter�ļ��ܾ��.
    * @param   remote_datawriter_token     Զ��datawriter�Ľ�����Ϣ.
    * @param [out] exception               ��������ʱ�Ĵ��󷵻�.
    *
    * @return  ���óɹ��򷵻�true��ʧ���򷵻�false.
    */

    virtual bool set_remote_datawriter_crypto_tokens(
        DatareaderCryptoHandle local_datareader_crypto,
        DatawriterCryptoHandle remote_datawriter_crypto,
        const DatawriterCryptoTokenSeq* remote_datawriter_token,
        SecurityException* exception) = 0;

    /**
    * @fn  bool CryptoKeyExchange::create_local_datareader_crypto_tokens( ParticipantCryptoTokenSeq &local_datareader_crypto_tokens, DatareaderCryptoHandle local_datareader_crypto, DatawriterCryptoHandle remote_datawriter_crypto, SecurityException* exception);
    *
    * @brief   ����datareader�Ľ�����Ϣ.
    *
    * @author  Lxx
    * @date    2018/1/30
    *
    * @param [out]  local_datareader_crypto_tokens     dataereader�Ľ�����Ϣ.
    * @param   local_datareader_crypto                 ���ص�datareader�ļ��ܾ��.
    * @param   remote_datawriter_crypto                �뱾��datareader��ƥ���Զ��datawriter�ļ��ܾ��.
    * @param [out] exception                           ��������ʱ�Ĵ��󷵻�.
    *
    * @return  �����ɹ��򷵻�true��ʧ���򷵻�false.
    */

    virtual bool create_local_datareader_crypto_tokens(
        DatareaderCryptoTokenSeq* local_datareader_crypto_tokens,
        DatareaderCryptoHandle local_datareader_crypto,
        DatawriterCryptoHandle remote_datawriter_crypto,
        SecurityException* exception) = 0;

    /**
    * @fn  bool CryptoKeyExchange::set_remote_datareader_crypto_tokens( DatawriterCryptoHandle local_datawriter_crypto, DatareaderCryptoHandle remote_datareader_crypto, ParticipantCryptoTokenSeq remote_datareader_tokens, SecurityException* exception);
    *
    * @brief   ����Զ��datareader�Ľ�����Ϣ����Զ��datareader�ļ��ܾ��.
    *
    * @author  Lxx
    * @date    2018/1/30
    *
    * @param   local_datawriter_crypto     ��Զ��datareader��ƥ��ı���datawriter�ļ��ܾ��.
    * @param   remote_datareader_crypto    Զ��datareader�ļ��ܾ��.
    * @param   remote_datareader_tokens    Զ��datareader�Ľ�����Ϣ.
    * @param [out] exception               ��������ʱ�Ĵ��󷵻�.
    *
    * @return  ���óɹ��򷵻�true��ʧ���򷵻�false.
    */

    virtual bool set_remote_datareader_crypto_tokens(
        DatawriterCryptoHandle local_datawriter_crypto,
        DatareaderCryptoHandle remote_datareader_crypto,
        const DatareaderCryptoTokenSeq* remote_datareader_tokens,
        SecurityException* exception) = 0;

    /**
    * @fn  bool CryptoKeyExchange::return_crypto_tokens( ParticipantCryptoTokenSeq crypto_tokens, SecurityException* exception);
    *
    * @brief   �ͷŽ�����Ϣʹ�õĿռ�.
    *
    * @author  Lxx
    * @date    2018/1/30
    *
    * @param   crypto_tokens   ������Ϣ�ļ���.
    * @param [out] exception   ��������ʱ�Ĵ��󷵻�.
    *
    * @return  ִ�гɹ��򷵻�true��ʧ���򷵻�fasle.
    */

    virtual bool return_crypto_tokens(
        CryptoTokenSeq* crypto_tokens,
        SecurityException* exception) = 0;
};
#endif // CryptoKeyExchange_h__
