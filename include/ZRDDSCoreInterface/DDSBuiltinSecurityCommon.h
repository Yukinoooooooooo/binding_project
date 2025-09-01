/**
 * @file:       DDSBuiltinSecurityCommon.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#ifndef DDSBuiltinSecurityCommon_h__
#define DDSBuiltinSecurityCommon_h__

#include "ZROSDefine.h"
#ifdef _ZRDDSSECURITY

#include "OsResource.h"
#include "ZRSequence.h"
#include "ZRBuiltinTypes.h"
#include "PropertyQosPolicy.h"
#include "BuiltinTopicKey_t.h"
#include "InstanceHandle_t.h"
#include "Duration_t.h"

struct MessageBlock;

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

typedef struct ZRDDSSecurityPluginInstance
{
    void* authentication;
    void* access_control;
    void* crypto_key_factory;
    void* crypto_key_exchange;
    void* crypto_transform;
    DDS_Time_t retry_time;
    DDS_Time_t max_wait_time;
    DDS_ULong max_retry_number;
}ZRDDSSecurityPluginInstance;

typedef DDS_Boolean(*GetSecurityPlugInstance)(ZRDDSSecurityPluginInstance*);
typedef void(*FinalizeSecurityPlugInstance)();

typedef void* DDSSecHandle;

extern DCPSDLL const DDSSecHandle DDS_SEC_NIL_HANDLE;

extern DCPSDLL DDS_Char* DDS_GMCLASSID_SECURITY_AUTH_HANDSHAKE;
extern DCPSDLL DDS_Char* DDS_GMCLASSID_SECURITY_PARTICIPANT_CRYPTO_TOKENS;
extern DCPSDLL DDS_Char* DDS_GMCLASSID_SECURITY_DATAWRITER_CRYPTO_TOKENS;
extern DCPSDLL DDS_Char* DDS_GMCLASSID_SECURITY_DATAREADER_CRYPTO_TOKENS;

/**
 * @typedef DDS_Long SecurityExceptionCode
 *
 * @brief   ��ʾ��ȫ����쳣���롣
 */

typedef DDS_Long SecurityExceptionCode;

/**
 * @struct  SecurityException
 *
 * @brief   ��ʾ��ȫ����쳣��Ϣ��
 */

struct SecurityException
{
    /** @brief   �쳣���롣 */
    SecurityExceptionCode code;
    /** @brief   �쳣���롣 */
    DDS_Long minor_code;
    /** @brief   �쳣��Ϣ�� */
    DDS_Char message[256];
};

/**
 * @struct  DDS_DataHolder
 *
 * @brief   �����洢һ���Ե����ݣ������������������洢��ͬ�������ʽ�����ݣ���Ϊ�������͵���ɲ��֣�����Token��GenericMessageData
 *
 * @author  Hzy
 */

typedef struct DDS_DataHolder
{
    /** @brief   ����ΪToken����ʱ�������ʾToken���ͣ�dds.sec.Ϊ�����ַ���,ʵ�ֳ���ʹ������������ */
    DDS_Char* class_id;
    /** @brief   �������á� */
    DDS_PropertySeq properties;
    /** @brief   �������á� */
    DDS_BinaryPropertySeq binary_properties;
} DDS_DataHolder;

typedef DDS_ULong ParticipantSecurityAttributesMask;
typedef DDS_ULong DDS_PluginParticipantSecurityAttributesMask;

typedef struct ParticipantSecurityInfo
{
    ParticipantSecurityAttributesMask  participant_security_atributes;
    DDS_PluginParticipantSecurityAttributesMask plugin_participant_security_attributes;
}ParticipantSecurityInfo;

extern const ParticipantSecurityInfo PARTICIPANT_SECURITY_ATTRIBUTES_INFO_DEFAULT;
#define PARTICIPANT_SECURITY_ATTRIBUTES_FLAG_IS_VALID (0x1 << 31)
#define PARTICIPANT_SECURITY_ATTRIBUTES_FLAG_IS_RTPS_PROTECTED (0x00000001 << 0)
#define PARTICIPANT_SECURITY_ATTRIBUTES_FLAG_IS_DISCOVERY_PROTECTED (0x00000001 << 1)
#define PARTICIPANT_SECURITY_ATTRIBUTES_FLAG_IS_LIVELINESS_PROTECTED (0x00000001 << 2)

typedef DDS_ULong EndpointSecurityAttributesMask;
typedef DDS_ULong DDS_PluginEndpointSecurityAttributesMask;

typedef struct DDS_EndpointSecurityInfo
{
    EndpointSecurityAttributesMask endpoint_security_attributes;
    DDS_PluginEndpointSecurityAttributesMask plugin_endpoint_security_attributes;
}DDS_EndpointSecurityInfo;

extern const DDS_EndpointSecurityInfo ENDPOINT_SECURITY_ATTRIBUTES_INFO_DEFAULT;
#define ENDPOINT_SECURITY_ATTRIBUTES_FLAG_IS_VALID (0x1 << 31)
#define ENDPOINT_SECURITY_ATTRIBUTES_FLAG_IS_READ_PROTECTED (0x00000001 << 0)
#define ENDPOINT_SECURITY_ATTRIBUTES_FLAG_IS_WRITE_PROTECTED (0x00000001 << 1)
#define ENDPOINT_SECURITY_ATTRIBUTES_FLAG_IS_DISCOVERY_PROTECTED (0x00000001 << 2)
#define ENDPOINT_SECURITY_ATTRIBUTES_FLAG_IS_SUBMESSAGE_PROTECTED (0x00000001 << 3)
#define ENDPOINT_SECURITY_ATTRIBUTES_FLAG_IS_PAYLOAD_PROTECTED (0x00000001 << 4)
#define ENDPOINT_SECURITY_ATTRIBUTES_FLAG_IS_KEY_PROTECTED (0x00000001 << 5)
#define ENDPOINT_SECURITY_ATTRIBUTES_FLAG_IS_LIVELINESS_PROTECTED (0x00000001 << 6)

/**
 * @typedef struct ParticipantSecurityAttributes
 *
 * @brief   DomainParticipant��صİ�ȫ����.
 */
typedef struct ParticipantSecurityAttributes
{
    /** @brief   �Ƿ�������δ��֤��ݵ�DomainParticipantƥ�� */
    DDS_Boolean allow_unauthenticated_participants;
    /** @brief   ����DomainParticipantƥ���Ƿ���ҪAccessControl�������Ȩ */
    DDS_Boolean is_access_protected;
    /** @brief   ����RTPS Message�Ƿ���Ҫ��CryptoTransform��encode_rtps_message��������ת��. */
    DDS_Boolean is_rtps_protected;
    /** @brief   ������Ϣ�Ƿ���Ҫ������. */
    DDS_Boolean is_discovery_protected;
    /** @brief   Liveliness��Ϣ�Ƿ���Ҫ������. */
    DDS_Boolean is_liveliness_protected;
    /** @brief   ΪCryptoKeyFactory��register_local_participant�����еĲ���participant_properties���ӵ�����. */
    DDS_PropertySeq ac_participant_properties;
    /** @brief The plugin participant attributes */
    DDS_PluginParticipantSecurityAttributesMask plugin_participant_attributes;
}ParticipantSecurityAttributes;

/**
 * @typedef struct TopicSecurityAttributes
 *
 * @brief ������ذ�ȫ����.
 */
typedef struct TopicSecurityAttributes
{
    /** @brief   �Ƿ���Ҫʹ�÷��ʿ��Ʋ���Ա���Reader������Զ��Readerƥ����м�� */
    DDS_Boolean is_read_protected;
    /** @brief   �Ƿ���Ҫʹ�÷��ʿ��Ʋ���Ա���Writer������Զ��Writerƥ����м�� */
    DDS_Boolean is_write_protected;
    /** @brief   ��ʵ��ķ�����Ϣ����ʱ����ʹ�ð�ȫ���ڽ���topics����ʹ�ó����topics. */
    DDS_Boolean is_discovery_protected;
    /** @brief   Liveliness��Ϣ�Ƿ���Ҫ������. */
    DDS_Boolean is_liveliness_protected;
}TopicSecurityAttributes;

/**
 * @typedef struct EndpointSecurityAttributes
 *
 * @brief   ʵ����صİ�ȫ����.
 */
typedef struct EndpointSecurityAttributes
{
    /* **�� TopicSecurityAttributes �̳е����� */
    /** @brief   �Ƿ���Ҫʹ�÷��ʿ��Ʋ���Ա���Reader������Զ��Readerƥ����м�� */
    DDS_Boolean is_read_protected;
    /** @brief   �Ƿ���Ҫʹ�÷��ʿ��Ʋ���Ա���Writer������Զ��Writerƥ����м�� */
    DDS_Boolean is_write_protected;
    /** @brief   ��ʵ��ķ�����Ϣ����ʱ����ʹ�ð�ȫ���ڽ���topics����ʹ�ó����topics. */
    DDS_Boolean is_discovery_protected;
    /** @brief   Liveliness��Ϣ�Ƿ���Ҫ������. */
    DDS_Boolean is_liveliness_protected;
    /* **�̳��� TopicSecurityAttributes �����Խ��� */

    /** @brief   �Ƿ���Ҫ������Ϣ���б���. */
    DDS_Boolean is_submessage_protected;
    /** @brief   �Ƿ���Ҫ�����ݸ��ؽ��б���. */
    DDS_Boolean is_payload_protected;
    /** @brief   �Ƿ���Ҫʹ�ð�ȫ�����������ʵ�����. */
    DDS_Boolean is_key_protected;
    /** @brief   ���ӵ�����. */
    DDS_PropertySeq ac_endpoint_properties;
    /** @brief The plugin endpoint attributes */
    DDS_PluginEndpointSecurityAttributesMask plugin_endpoint_attributes;
}EndpointSecurityAttributes;

typedef struct CryptoPayloadEncodeAttributes
{
    DDS_ULong headerFixLength;
    DDS_ULong encodeDataLengthPercentage;
    DDS_ULong tailFixLength;
}CryptoPayloadEncodeAttributes;

typedef struct CryptoWriterSubmessageAttributes
{
    DDS_ULong headerFixLength;
    DDS_ULong headerMutableLengthPerReader;
    DDS_ULong encodeDataLengthPercentage;
    DDS_ULong tailFixLength;
    DDS_ULong tailMutableLengthPerReader;
}CryptoWriterSubmessageAttributes;

typedef struct CryptoReaderSubmessageAttributes
{
    DDS_ULong headerFixLength;
    DDS_ULong headerMutableLengthPerWriter;
    DDS_ULong encodeDataLengthPercentage;
    DDS_ULong tailFixLength;
    DDS_ULong tailMutableLengthPerWriter;
}CryptoReaderSubmessageAttributes;

typedef struct CryptoRtpsMessageAttributes
{
    DDS_ULong headerFixLength;
    DDS_ULong headerMutableLengthPerParticipant;
    DDS_ULong encodeDataLengthPercentage;
    DDS_ULong tailFixLength;
    DDS_ULong tailMutableLengthPerParticipant;
}CryptoRtpsMessageAttributes;

DDS_SEQUENCE_CPP(DDS_DataHolderSeq, DDS_DataHolder);

typedef DDS_DataHolder Credential;
typedef Credential IdentityCredential;
typedef Credential PermissionsCredential;

typedef DDS_DataHolder Token;

typedef Token HandshakeMessageToken;
typedef Token IdentityToken;
typedef Token PermissionsToken;
typedef Token AuthenticatedPeerCredentialToken;
typedef Token PermissionsCredentialToken;

typedef Token CryptoToken;
typedef Token ParticipantCryptoToken;
typedef Token DatawriterCryptoToken;
typedef Token DatareaderCryptoToken;

typedef DDS_DataHolderSeq HandshakeMessageTokenSeq;
typedef DDS_DataHolderSeq CryptoTokenSeq;
typedef DDS_DataHolderSeq ParticipantCryptoTokenSeq;
typedef DDS_DataHolderSeq DatawriterCryptoTokenSeq;
typedef DDS_DataHolderSeq DatareaderCryptoTokenSeq;

DCPSDLL DDS_Long DDS_DataHolderInitialize(
    DDS_DataHolder* sample,
    void* memPool,
    DDS_Boolean allocMem);

DCPSDLL DDS_Long DDS_DataHolderFinalize(
    DDS_DataHolder* sample,
    void* memPool,
    DDS_Boolean allocMem);

DCPSDLL DDS_Long DDS_DataHolderCopy(
    DDS_DataHolder* dst,
    const DDS_DataHolder* src,
    void* mempool);

DCPSDLL DDS_ULong DDS_DataHolderGetSize(
    const DDS_DataHolder* sample);

DCPSDLL DDS_Long DDS_DataHolderSerialize(
    const DDS_DataHolder* sample,
    struct MessageBlock *dst,
    DDS_Boolean littleEndian);

DCPSDLL DDS_Long DDS_DataHolderDeserialize(
    DDS_DataHolder* sample,
    struct MessageBlock *src,
    DDS_Boolean littleEndian);

DCPSDLL DDS_ULong DDS_DataHolderSeqGetSize(
    const DDS_DataHolderSeq* sample);

DCPSDLL DDS_Long DDS_DataHolderSeqSerialize(
    const DDS_DataHolderSeq* sample,
    struct MessageBlock *dst,
    DDS_Boolean littleEndian);

DCPSDLL DDS_Long DDS_DataHolderSeqDeserialize(
    DDS_DataHolderSeq* sample,
    struct MessageBlock *src,
    DDS_Boolean littleEndian);

DCPSDLL ParticipantSecurityAttributesMask ParticipantSecurityAttributesToMask(ParticipantSecurityAttributes* secAttr);

DCPSDLL EndpointSecurityAttributesMask TopicSecurityAttributesToMask(TopicSecurityAttributes* secAttr);

DCPSDLL EndpointSecurityAttributesMask EndpointSecurityAttributesToMask(EndpointSecurityAttributes* secAttr);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _ZRDDSSECURITY */

#endif /* DDSBuiltinSecurityCommon_h__ */
