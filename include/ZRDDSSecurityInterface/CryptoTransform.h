#ifndef CryptoKeyTransform_h__
#define CryptoKeyTransform_h__

#include "CryCommonSource.h"

class  CryptoTransform
{
public:

    virtual ~CryptoTransform(){};

    /**
    * @fn  bool CryptoTransform::encode_serialized_payload( ZR_INT8* encoded_buffer, ZR_INT32* encoded_buffer_length, ZR_INT8* extra_inline_qos, ZR_INT32* extra_inlien_qos_num, const ZR_INT8* plain_buffer, ZR_INT32 plain_buffer_length, DatawriterCryptoHandle sending_datawriter_crypto, SecurityException* exception);
    *
    * @brief   ʹ����Կ��payload�������Ľ��м��ܻ�ǩ��
    *
    * @author  Lxx
    * @date    2018/1/30
    *
    * @param [out] encoded_buffer          ����֮�������.
    * @param [out] extra_inline_qos        ���ܲ����Ķ�����Ϣ
    * @param   plain_buffer                ��Ҫ���ܵ����Ļ����׵�ַ.
    * @param   plain_buffer_count          ��Ҫ���ܵ����Ļ�������.
    * @param   sending_datawriter_crypto   ���Ͷ�datawriter����Կ.
    * @param [out] exception               ����ִ��ʧ��ʱ�Ĵ�����Ϣ.
    *
    * @return  �ɹ��򷵻�true�� ʧ�ܷ���false.
    */

    virtual bool encode_serialized_payload(
        ZRBuffer* encoded_buffer,
        ZRBuffer* extra_inline_qos,
        const ZRBuffer* plain_buffer,
        ZR_INT32 plain_buffer_count,
        DatawriterCryptoHandle sending_datawriter_crypto,
        SecurityException* exception) = 0;

    /**
    * @fn  bool CryptoTransform::encode_datawriter_submessage( ZR_INT8* encode_rtps_submessage, ZR_INT32* encode_rtps_submessage_length, const ZR_INT8* plain_rtps_submessage, ZR_INT32 plain_rtps_submessage_length, DatawriterCryptoHandle sending_datawriter_crypto, const DatareaderCryptoHandle* receiving_datareader_crypto_list, ZR_INT32 receiving_datareader_crypto_num, SecurityException* exception);
    *
    * @brief   ʹ����Կ��datawriter��submessage���м��ܻ�ǩ��

    *
    * @author  Lxx
    * @date    2018/1/30
    *
    * @param [out] encode_rtps_submessage          ���ܺ������.
    * @param   plain_rtps_submessage               ��Ҫ���ܵ����Ļ���.
    * @param   plain_rtps_submessage_count         ��Ҫ���ܵ����Ļ�������.
    * @param   sending_datawriter_crypto           ���Ͷ�datawriter����Կ.
    * @param   receiving_datareader_crypto_list    ���ܶ�datareader����Կ�б�.
    * @param   receiving_datareader_crypto_num     ���ܶ��б�Ԫ�ص�����.
    * @param [out] exception                       ����ִ��ʧ��ʱ�Ĵ�����Ϣ.
    *
    * @return  �ɹ��򷵻�true�� ʧ�ܷ���false.
    */

    virtual bool encode_datawriter_submessage(
        ZRBuffer* encoded_rtps_submessage,
        const ZRBuffer* plain_rtps_submessage,
        ZR_INT32 plain_rtps_submessage_count,
        DatawriterCryptoHandle sending_datawriter_crypto,
        const DatareaderCryptoHandle* receiving_datareader_crypto_list,
        ZR_INT32 receiving_datareader_crypto_num,
        SecurityException* exception) = 0;

    /**
    * @fn  bool CryptoTransform::encode_datareader_submessage( ZR_INT8* encoded_rtps_submessage, ZR_INT32* encode_rtps_submessage_length, const ZR_INT8* plain_rtps_submessage, ZR_INT32 plain_rtps_suibmessage_length, DatareaderCryptoHandle sending_datareader_crypto, const DatawriterCryptoHandle* receiving_datawriter_crypto_list, ZR_INT32 receiving_datawriter_crypto_list_num, SecurityException* exception);
    *
    * @brief   ����datareader����Կ��datareader��submessage��Ϣ���м��ܻ���ǩ��
    *
    * @author  Lxx
    * @date    2018/1/30
    *
    * @param [out] encoded_rtps_submessage             ����֮�������.
    * @param   plain_rtps_submessage                   ��Ҫ���ܵ����Ļ���.
    * @param   plain_rtps_suibmessage_count            ��Ҫ���ܵ����Ļ�������.
    * @param   sending_datareader_crypto               ���Ͷ�datareader����Կ.
    * @param   receiving_datawriter_crypto_list        ���ն˵�datawriter��Կ�б�.
    * @param   receiving_datawriter_crypto_list_num    ���ն��б�Ԫ�ص�����.
    * @param [out] exception                           ����ִ��ʧ��ʱ�Ĵ�����Ϣ.
    *
    * @return  �ɹ��򷵻�true�� ʧ�ܷ���false.
    */

    virtual bool encode_datareader_submessage(
        ZRBuffer* encoded_rtps_submessage,
        const ZRBuffer* plain_rtps_submessage,
        ZR_INT32 plain_rtps_submessage_count,
        DatareaderCryptoHandle sending_datareader_crypto,
        const DatawriterCryptoHandle* receiving_datawriter_crypto_list,
        ZR_INT32 receiving_datawriter_crypto_list_num,
        SecurityException* exception) = 0;

    /**
    * @fn  bool CryptoTransform::encode_rtps_message( ZR_INT8* encoded_rtps_message, ZR_INT32* encoded_rtps_message_length, const ZR_INT8* plain_rtps_message, ZR_INT32 plain_rtps_message_length, ParticipantCryptoHandle sending_crypto, const ParticipantCryptoHandle* receiving_crypto_list, ZR_INT32 receiving_crypto_list_num, SecurityException* exception);
    *
    * @brief   ʹ��participant����Կ��rtps��message���м��ܻ���ǩ��
    *
    * @author  Lxx
    * @date    2018/1/30
    *
    * @param [out] encoded_rtps_message        ���ܺ������.
    * @param   plain_rtps_message              ����ǰ�����Ļ���.
    * @param   plain_rtps_message_count        ����ǰ���ĵĻ�������.
    * @param   sending_crypto                  ���Ͷ�participant����Կ.
    * @param   receiving_crypto_list           ���ն˵�participant��Կ�б�.
    * @param   receiving_crypto_list_num       ���ն��б�Ԫ�ص�����.
    * @param [out] exception                   ����ִ��ʧ��ʱ�Ĵ�����Ϣ.
    *
    * @return  �ɹ��򷵻�true�� ʧ�ܷ���false.
    */

    virtual bool encode_rtps_message(
        ZRBuffer* encoded_rtps_message,
        const ZRBuffer* plain_rtps_message,
        ZR_INT32 plain_rtps_message_count,
        ParticipantCryptoHandle sending_crypto,
        const ParticipantCryptoHandle* receiving_crypto_list,
        ZR_INT32 receiving_crypto_list_num,
        SecurityException* exception) = 0;

    /**
    * @fn  bool CryptoTransform::decode_rtps_message( ZR_INT8* plain_buffer, ZR_INT32* plain_buffer_length, const ZR_INT8* encoded_buffer, ZR_INT32 encoded_buffer_length, ParticipantCryptoHandle receiving_crypto, ParticipantCryptoHandle sending_crypto, SecurityException* exception);
    *
    * @brief   ʹ��Զ��participant����Կ��Զ�˵����Ľ��н��ܻ�����֤ǩ��
    *
    * @author  Lxx
    * @date    2018/1/30
    *
    * @param [out] plain_buffer        ����֮�������.
    * @param   encoded_buffer          ��Ҫ���ܵ����Ļ���.
    * @param   encoded_buffer_count    ��Ҫ���ܵ����Ļ�������.
    * @param   receiving_crypto        ���ն˵���Կ.
    * @param   sending_crypto          ���Ͷ˵���Կ.
    * @param [out] exception           ����ִ��ʧ��ʱ�Ĵ�����Ϣ.
    *
    * @return  �ɹ��򷵻�true�� ʧ�ܷ���false.
    */

    virtual bool decode_rtps_message(
        ZRBuffer* plain_buffer,
        const ZRBuffer* encoded_buffer,
        ZR_INT32 encoded_buffer_count,
        ParticipantCryptoHandle receiving_crypto,
        ParticipantCryptoHandle sending_crypto,
        SecurityException* exception) = 0;

    /**
    * @fn  bool CryptoTransform::preprocess_secure_submsg( DatawriterCryptoHandle datawriter_crypto, DatareaderCryptoHandle datareader_crypto, DDS_SecureSujmessageCategorty_t* secure_submessage_category, const ZR_INT8* encoded_rtps_submessage, ZR_INT32 encoded_rtps_submessage_length, ParticipantCryptoHandle receiving_crypto, ParticipantCryptoHandle sending_crypto, SecurityException* exception);
    *
    * @brief   ΪsubmessageѰ����֮��ƥ���datawriter��Կ��datareader��Կ
    *
    * @author  Lxx
    * @date    2018/1/30
    *
    * @param [out] datawriter_crypto           datawriter����Կ.
    * @param [out] datareader_crypto           datareader����Կ.
    * @param [out] secure_submessage_category  submessage����Ϣ���.
    * @param   encoded_rtps_submessage         submessage�����Ļ���.
    * @param   encoded_rtps_submessage_count   ���Ļ�������.
    * @param   receiving_crypto                ���ն�participant����Կ.
    * @param   sending_crypto                  ���Ͷ�participant����Կ.
    * @param [out] exception                   ����ִ��ʧ��ʱ�Ĵ�����Ϣ.
    *
    * @return  �ɹ��򷵻�true�� ʧ�ܷ���false.
    */

    virtual bool preprocess_secure_submsg(
        DatawriterCryptoHandle* datawriter_crypto,
        DatareaderCryptoHandle* datareader_crypto,
        DDS_SecureSubmessageCategory_t* secure_submessage_category,
        const ZRBuffer* encoded_rtps_submessage,
        ZR_INT32 encoded_rtps_submessage_count,
        ParticipantCryptoHandle receiving_crypto,
        ParticipantCryptoHandle sending_crypto,
        SecurityException* exception) = 0;

    /**
    * @fn  bool CryptoTransform::decode_datawriter_submessage( ZR_INT8* plain_rtps_submessage, ZR_INT32* plain_rtps_submessage_length, const ZR_INT8* encoded_rtps_submessage, ZR_INT32 encoded_rtps_submessage_length, DatareaderCryptoHandle receiving_datareader_crypto, DatawriterCryptoHandle sending_datawriter_crypto, SecurityException* exception);
    *
    * @brief   ʹ��Զ��datawriter����Կ��datawriter��submessage���н��ܻ���ǩ����֤
    *
    * @author  Lxx
    * @date    2018/1/30
    *
    * @param [out] plain_rtps_submessage           ����֮�������.
    * @param   encoded_rtps_submessage             ��Ҫ���ܵ����Ļ���.
    * @param   encoded_rtps_submessage_count       ��Ҫ���ܵ����Ļ�������.
    * @param   receiving_datareader_crypto         ���ն�datareader��Կ.
    * @param   sending_datawriter_crypto           ���Ͷ�datawriter��Կ.
    * @param [out] exception                       ����ִ��ʧ��ʱ�Ĵ�����Ϣ.
    *
    * @return  �ɹ��򷵻�true�� ʧ�ܷ���false.
    */

    virtual bool decode_datawriter_submessage(
        ZRBuffer* plain_rtps_submessage,
        const ZRBuffer* encoded_rtps_submessage,
        ZR_INT32 encoded_rtps_submessage_count,
        DatareaderCryptoHandle receiving_datareader_crypto,
        DatawriterCryptoHandle sending_datawriter_crypto,
        SecurityException* exception) = 0;

    /**
    * @fn  bool CryptoTransform::decode_datareader_submessage( ZR_INT8* plain_rtps_submessage, ZR_INT32* plain_rtps_submessage_length, const ZR_INT8* encoded_rtps_submessage, ZR_INT32 encoded_rtps_submessage_length, DatawriterCryptoHandle receiving_datawriter_crypto, DatareaderCryptoHandle sending_datareader_crypto, SecurityException* exception);
    *
    * @brief   ʹ��Զ��datareader����Կ��datareader��submessage��Ϣ�������Ľ��ܻ���ǩ����֤.
    *
    * @author  Lxx
    * @date    2018/1/30
    *
    * @param [out] plain_rtps_submessage           ����֮�������.
    * @param   encoded_rtps_submessage             ��Ҫ���ܵ����Ļ���.
    * @param   encoded_rtps_submessage_count       ��Ҫ���ܵ����Ļ�������.
    * @param   receiving_datawriter_crypto         ���ն�datawriter����Կ.
    * @param   sending_datareader_crypto           ���Ͷ�datareader����Կ.
    * @param [out] exception                       ����ִ��ʧ��ʱ�Ĵ�����Ϣ.
    *
    * @return  �ɹ��򷵻�true�� ʧ�ܷ���false.
    */

    virtual bool decode_datareader_submessage(
        ZRBuffer* plain_rtps_submessage,
        const ZRBuffer* encoded_rtps_submessage,
        ZR_INT32 encoded_rtps_submessage_count,
        DatawriterCryptoHandle receiving_datawriter_crypto,
        DatareaderCryptoHandle sending_datareader_crypto,
        SecurityException* exception) = 0;

    /**
    * @fn  bool CryptoTransform::decode_serialized_payload( ZR_INT8* plain_buffer, ZR_INT32* plain_buffer_length, const ZR_INT8* encode_buffer, ZR_INT32 encode_buffer_length, const ZR_INT8* inline_qos, ZR_INT32 inline_qos_num, DatareaderCryptoHandle receiving_datareader_crypto, DatawriterCryptoHandle sending_datawriter_crypto, SecurityException* exception);
    *
    * @brief   ʹ����Կ��datareader��submessage��Ϣ�������Ľ��ܻ���ǩ����֤.
    *
    * @author  Lxx
    * @date    2018/1/30
    *
    * @param [out] plain_buffer            ���ܺ������.
    * @param   encode_buffer               ��Ҫ���ܵ����Ļ���.
    * @param   encode_buffer_count         ��Ҫ�������Ļ�������.
    * @param   inline_qos                  ������Ϣ
    * @param   inline_qos_count            ������Ϣ��������.
    * @param   receiving_datareader_crypto ��ȡ�˵���Կ.
    * @param   sending_datawriter_crypto   д��˵���Կ.
    * @param [out] exception               ����ִ��ʧ��ʱ�Ĵ�����Ϣ.
    *
    * @return  �ɹ��򷵻�true�� ʧ�ܷ���false.
    */

    virtual bool decode_serialized_payload(
        ZRBuffer* plain_buffer,
        const ZRBuffer* encoded_buffer,
        ZR_INT32 encoded_buffer_count,
        const ZRBuffer* inline_qos,
        ZR_INT32 inline_qos_count,
        DatareaderCryptoHandle receiving_datareader_crypto,
        DatawriterCryptoHandle sending_datawriter_crypto,
        SecurityException* exception) = 0;

    /**
    * @fn virtual bool CryptoTransform::get_payload_encode_attributes( DatawriterCryptoHandle datawriter_crypto, CryptoPayloadEncodeAttributes* payload_encode_attributes) = 0;
    *
    * @brief ��ȡ�����ݸ��ؽ��м��ܵ��������
    *
    * @author Tim
    * @date 18/3/29
    *
    * @param datawriter_crypto                  datawriter����Կ
    * @param [in,out] payload_encode_attributes �����ݸ��ؽ��м��ܵ��������
    *
    * @return �ɹ��򷵻�true�� ʧ�ܷ���false.
    */
    virtual bool get_payload_encode_attributes(
        DatawriterCryptoHandle datawriter_crypto,
        CryptoPayloadEncodeAttributes* payload_encode_attributes) = 0;

    /**
    * @fn virtual bool CryptoTransform::get_datawriter_submessage_encode_attributes( DatawriterCryptoHandle sending_datawriter_crypto, CryptoWriterSubmessageAttributes* writer_submessage_encode_attributes) = 0;
    *
    * @brief ��ȡ��DataWriter����Ϣ���м��ܵ��������
    *
    * @author Tim
    * @date 18/3/29
    *
    * @param sending_datawriter_crypto                    datawriter����Կ
    * @param [in,out] writer_submessage_encode_attributes  ��DataWriter����Ϣ���м��ܵ��������
    *
    * @return �ɹ��򷵻�true�� ʧ�ܷ���false.
    */
    virtual bool get_datawriter_submessage_encode_attributes(
        DatawriterCryptoHandle sending_datawriter_crypto,
        CryptoWriterSubmessageAttributes* writer_submessage_encode_attributes) = 0;

    /**
    * @fn virtual bool CryptoTransform::get_datareader_submessage_encode_attributes( DatareaderCryptoHandle datareader_crypto, CryptoReaderSubmessageAttributes* reader_submessage_encode_attributes) = 0;
    *
    * @brief ��ȡ��DataReader����Ϣ���м��ܵ��������
    *
    * @author Tim
    * @date 18/3/29
    *
    * @param datareader_crypto                            datareader����Կ
    * @param [in,out] reader_submessage_encode_attributes  ��ȡ��DataReader����Ϣ���м��ܵ��������
    *
    * @return �ɹ��򷵻�true�� ʧ�ܷ���false.
    */
    virtual bool get_datareader_submessage_encode_attributes(
        DatareaderCryptoHandle datareader_crypto,
        CryptoReaderSubmessageAttributes* reader_submessage_encode_attributes) = 0;

    /**
    * @fn virtual bool CryptoTransform::get_rtps_message_encode_attributes( ParticipantCryptoHandle participant_crypto, CryptoRtpsMessageAttributes* rtps_message_encode_attributes) = 0;
    *
    * @brief ��ȡ��RTPS��Ϣ���м��ܵ��������
    *
    * @author Tim
    * @date 18/3/29
    *
    * @param participant_crypto                      participant����Կ
    * @param [in,out] rtps_message_encode_attributes   ��ȡ��RTPS��Ϣ���м��ܵ��������
    *
    * @return �ɹ��򷵻�true�� ʧ�ܷ���false.
    */
    virtual bool get_rtps_message_encode_attributes(
        ParticipantCryptoHandle participant_crypto,
        CryptoRtpsMessageAttributes* rtps_message_encode_attributes) = 0;
};
#endif // CryptoKeyTransform_h__
