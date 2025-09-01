/**
 * @file:       ZRDDSCppWrapper.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#ifndef ZRDDSCppWrapper_h__
#define ZRDDSCppWrapper_h__

#include "AsynchronousPublisherQosPolicy.h"
#include "BatchQosPolicy.h"
#include "BuiltinTopicKey_t.h"
#include "CDRStream.h"
#include "ContentFilterProperty_t.h"
#include "DataReaderQos.h"
#include "DataRepresentationQosPolicy.h"
#include "DataWriterMessageModeQosPolicy.h"
#include "DataWriterProtocolQosPolicy.h"
#include "DataWriterQos.h"
#include "DataWriterResourceLimitsQosPolicy.h"
#include "DDSLogQosPolicy.h"
#include "DDSMsgStatisticsInfoQosPolicy.h"
#include "DeadlineQosPolicy.h"
#include "DefaultQos.h"
#include "DestinationOrderQosPolicy.h"
#include "DiscoveryConfigQosPolicy.h"
#include "DomainId_t.h"
#include "DomainParticipantFactoryQos.h"
#include "DomainParticipantQos.h"
#include "DurabilityQosPolicy.h"
#include "DurabilityServiceQosPolicy.h"
#include "Duration_t.h"
#include "EntityFactoryQosPolicy.h"
#include "GroupDataQosPolicy.h"
#include "HistoryQosPolicy.h"
#include "InconsistentTopicStatus.h"
#include "InstanceHandle_t.h"
#include "InstanceStateKind.h"
#include "InstanceStateMask.h"
#include "LatencyBudgetQosPolicy.h"
#include "LifespanQosPolicy.h"
#include "LivelinessChangedStatus.h"
#include "LivelinessLostStatus.h"
#include "LivelinessQosPolicy.h"
#include "OfferedDeadlineMissedStatus.h"
#include "OfferedIncompatibleQosStatus.h"
#include "OsResource.h"
#include "OwnershipQosPolicy.h"
#include "OwnershipStrengthQosPolicy.h"
#include "ParticipantBuiltinTopicData.h"
#include "PartitionQosPolicy.h"
#include "PresentationQosPolicy.h"
#include "PropertyList.h"
#include "PropertyQosPolicy.h"
#include "PublicationBuiltinTopicData.h"
#include "TopicBuiltinTopicData.h"
#include "PublicationMatchedStatus.h"
#include "PublicationSendStatus.h"
#include "PublisherQos.h"
#include "PublishModeQosPolicy.h"
#include "QosPolicyCount.h"
#include "QosPolicyId_t.h"
#include "RapidIOConfigQosPolicy.h"
#include "RapidIOControllerQosPolicy.h"
#include "ReaderDataLifecycleQosPolicy.h"
#include "ReceiverThreadConfigQosPolicy.h"
#include "ReliabilityQosPolicy.h"
#include "RequestedDeadlineMissedStatus.h"
#include "RequestedIncompatibleQosStatus.h"
#include "ResourceLimitsQosPolicy.h"
#include "ReturnCode_t.h"
#include "SampleInfo.h"
#include "SampleLostStatus.h"
#include "SampleRejectedStatus.h"
#include "SampleRejectedStatusKind.h"
#include "SampleStateKind.h"
#include "SampleStateMask.h"
#include "SequenceNumber_t.h"
#include "StatusKind.h"
#include "StatusKindMask.h"
#include "SubscriberQos.h"
#include "SubscriptionBuiltinTopicData.h"
#include "SubscriptionMatchedStatus.h"
#include "ThreadCoreAffinityQosPolicy.h"
#include "TimeBasedFilterQosPolicy.h"
#include "TopicDataQosPolicy.h"
#include "TopicQos.h"
#include "TransportConfigQosPolicy.h"
#include "TransportPriorityQosPolicy.h"
#include "TypeCodeKind.h"
#include "TypeConsistencyEnforcementQosPolicy.h"
#include "TypeObject.h"
#include "UserDataQosPolicy.h"
#include "ViewStateKind.h"
#include "ViewStateMask.h"
#include "WriterDataLifecycleQosPolicy.h"
#include "ZRDDSCommon.h"
#include "ZRDDSTypePlugin.h"
#include "ZRDynamicData.h"
#include "ZRMemPool.h"
#include "ZROSDefine.h"
#include "ZRBuiltinTypes.h"
#include "ZRSequence.h"
#include "ZRSleep.h"
#include "ZRUserLog.h"
#include "DDSSecurityPluginQosPolicy.h"
#ifdef _ZRDDS_INCLUDE_GATEWAY
#include "GatewayQosPolicy.h"
#endif // _ZRDDS_INCLUDE_GATEWAY

namespace DDS {

/**
 * @typedef DDS_Boolean Boolean
 *
 * @ingroup CppCoreStruct
 *
 * @brief   ZRDDS���õ�true/false���͡�
 */

typedef DDS_Boolean Boolean;

/**
 * @typedef DDS_Octet Octet
 *
 * @ingroup CppCoreStruct
 *
 * @brief   ZRDDS���õ�1�ֽ��޷������� 
 */

typedef DDS_Octet Octet;

/**
 * @typedef DDS_Char Char
 *
 * @ingroup CppCoreStruct
 *
 * @brief   ZRDDS���õ�1�ֽ����͡�
 */

typedef DDS_Char Char;

/**
 * @typedef DDS_Short Short
 *
 * @ingroup CppCoreStruct
 *
 * @brief   ZRDDS���õ�2�ֽ����͡�
 */

typedef DDS_Short Short;

/**
 * @typedef DDS_UShort UShort
 *
 * @ingroup CppCoreStruct
 *
 * @brief   ZRDDS���õ�2�ֽ��޷������͡�
 */

typedef DDS_UShort UShort;

/**
 * @typedef DDS_Long Long
 *
 * @ingroup CppCoreStruct
 *
 * @brief   ZRDDS���õ�4�ֽ����͡�
 */

typedef DDS_Long Long;

/**
 * @typedef DDS_ULong ULong
 *
 * @ingroup CppCoreStruct
 *
 * @brief   ZRDDS���õ�4�ֽ��޷������͡�
 */

typedef DDS_ULong ULong;

/**
 * @typedef DDS_LongLong LongLong
 *
 * @ingroup CppCoreStruct
 *
 * @brief   ZRDDS���õ�8�ֽڳ����͡�
 */

typedef DDS_LongLong LongLong;

/**
 * @typedef DDS_ULongLong ULongLong
 *
 * @ingroup CppCoreStruct
 *
 * @brief   ZRDDS���õ�8�ֽ��޷��ų����͡�
 */

typedef DDS_ULongLong ULongLong;

/**
 * @typedef DDS_Float Float
 *
 * @ingroup CppCoreStruct
 *
 * @brief   ZRDDS���õ�4�ֽڵ����ȸ����͡�
 */

typedef DDS_Float Float;

/**
 * @typedef DDS_Double Double
 *
 * @ingroup CppCoreStruct
 *
 * @brief   ZRDDS���õ�8�ֽ�˫���ȸ����͡�
 */

typedef DDS_Double Double;

/**
 * @typedef DDS_String String
 *
 * @ingroup CppCoreStruct
 *
 * @brief   ZRDDS���õ��ַ������͡�
 */

typedef DDS_String String;

#ifdef _ZRDDS_INCLUDE_BUILTIN_TYPES

/**
 * @typedef DDS_KeyedString KeyedString
 *
 * @ingroup CppCoreStruct
 *
 * @brief   ӳ��������� #DDS_KeyedString �ṹΪC++�ӿڡ�
 */

typedef DDS_KeyedString KeyedString;

/**
 * @typedef DDS_Bytes Bytes
 *
 * @ingroup CppCoreStruct
 *
 * @brief   ӳ��������� #DDS_Bytes �ṹΪC++�ӿڡ�
 */

typedef DDS_Bytes Bytes;

/**
 * @typedef DDS_KeyedBytes KeyedBytes
 *
 * @ingroup CppCoreStruct
 *
 * @brief   ӳ��������� #DDS_KeyedBytes �ṹΪC++�ӿڡ�
 */

typedef DDS_KeyedBytes KeyedBytes;

/**
 * @typedef DDS_ZeroCopyBytes ZeroCopyBytes
 *
 * @ingroup CppCoreStruct
 *
 * @brief   ӳ��������� #DDS_ZeroCopyBytes �ṹΪC++�ӿڡ�
 */

typedef DDS_ZeroCopyBytes ZeroCopyBytes;

#endif //_ZRDDS_INCLUDE_BUILTIN_TYPES

/**
 * @typedef DDS_BooleanSeq BooleanSeq
 *
 * @ingroup CppCoreStruct
 *
 * @brief   ӳ��������� #DDS_BooleanSeq �ṹΪC++�ӿڡ�
 */

typedef DDS_BooleanSeq BooleanSeq;

/**
 * @typedef DDS_OctetSeq DDS_Octet
 *
 * @ingroup CppCoreStruct
 *
 * @brief   ӳ��������� #DDS_OctetSeq �ṹΪC++�ӿڡ�
 */

typedef DDS_OctetSeq OctetSeq;

/**
 * @typedef DDS_CharSeq CharSeq
 *
 * @ingroup CppCoreStruct
 *
 * @brief   ӳ��������� #DDS_CharSeq �ṹΪC++�ӿڡ�
 */

typedef DDS_CharSeq CharSeq;

/**
 * @typedef DDS_ShortSeq ShortSeq
 *
 * @ingroup CppCoreStruct
 *
 * @brief   ӳ��������� #DDS_ShortSeq �ṹΪC++�ӿڡ�
 */

typedef DDS_ShortSeq ShortSeq;

/**
 * @typedef DDS_UShortSeq UShortSeq
 *
 * @ingroup CppCoreStruct
 *
 * @brief   ӳ��������� #DDS_UShortSeq �ṹΪC++�ӿڡ�
 */

typedef DDS_UShortSeq UShortSeq;

/**
 * @typedef DDS_LongSeq LongSeq
 *
 * @ingroup CppCoreStruct
 *
 * @brief   ӳ��������� #DDS_LongSeq �ṹΪC++�ӿڡ�
 */

typedef DDS_LongSeq LongSeq;

/**
 * @typedef DDS_ULongSeq ULongSeq
 *
 * @ingroup CppCoreStruct
 *
 * @brief   ӳ��������� #DDS_ULongSeq �ṹΪC++�ӿڡ�
 */

typedef DDS_ULongSeq ULongSeq;

/**
 * @typedef DDS_LongLongSeq LongLongSeq
 *
 * @ingroup CppCoreStruct
 *
 * @brief   ӳ��������� #DDS_LongLongSeq �ṹΪC++�ӿڡ�
 */

typedef DDS_LongLongSeq LongLongSeq;

/**
 * @typedef DDS_ULongLongSeq ULongLongSeq
 *
 * @ingroup CppCoreStruct
 *
 * @brief   ӳ��������� #DDS_ULongLongSeq �ṹΪC++�ӿڡ�
 */

typedef DDS_ULongLongSeq ULongLongSeq;

/**
 * @typedef DDS_FloatSeq FloatSeq
 *
 * @ingroup CppCoreStruct
 *
 * @brief   ӳ��������� #DDS_FloatSeq �ṹΪC++�ӿڡ�
 */

typedef DDS_FloatSeq FloatSeq;

/**
 * @typedef DDS_DoubleSeq DoubleSeq
 *
 * @ingroup CppCoreStruct
 *
 * @brief   ӳ��������� #DDS_DoubleSeq �ṹΪC++�ӿڡ�
 */

typedef DDS_DoubleSeq DoubleSeq;

/**
 * @typedef DDS_StringSeq StringSeq 
 *
 * @ingroup CppCoreStruct
 *
 * @brief   ӳ��������� #DDS_StringSeq �ṹΪC++�ӿڡ�
 */

typedef DDS_StringSeq StringSeq;

#ifdef _ZRDDS_INCLUDE_BUILTIN_TYPES

/**
 * @typedef DDS_KeyedStringSeq KeyedStringSeq 
 *
 * @ingroup CppCoreStruct
 *
 * @brief   ӳ��������� #DDS_KeyedStringSeq �ṹΪC++�ӿڡ�
 */

typedef DDS_KeyedStringSeq KeyedStringSeq;

/**
 * @typedef DDS_BytesSeq BytesSeq 
 *
 * @ingroup CppCoreStruct
 *
 * @brief   ӳ��������� #DDS_BytesSeq �ṹΪC++�ӿڡ�
 */

typedef DDS_BytesSeq BytesSeq;

/**
 * @typedef DDS_KeyedBytesSeq KeyedBytesSeq 
 *
 * @ingroup CppCoreStruct
 *
 * @brief   ӳ��������� #DDS_KeyedBytesSeq �ṹΪC++�ӿڡ�
 */

typedef DDS_KeyedBytesSeq KeyedBytesSeq;

/**
 * @typedef DDS_ZeroCopyBytesSeq ZeroCopyBytesSeq 
 *
 * @ingroup CppCoreStruct
 *
 * @brief   ӳ��������� #DDS_ZeroCopyBytesSeq �ṹΪC++�ӿڡ�
 */

typedef DDS_ZeroCopyBytesSeq ZeroCopyBytesSeq;

#endif //_ZRDDS_INCLUDE_BUILTIN_TYPES

/**
 * @typedef DDS_DomainId_t DomainId_t 
 *
 * @ingroup CppCoreStruct
 *
 * @brief ӳ��������� #DDS_DomainId_t �ṹΪC++�ӿڡ�
 */
typedef DDS_DomainId_t DomainId_t;

/**
 * @typedef DDS_BuiltinTopicKey_t BuiltinTopicKey_t 
 *
 * @ingroup CppCoreStruct
 *
 * @brief ӳ��������� #DDS_BuiltinTopicKey_t �ṹΪC++�ӿڡ�
 */
typedef DDS_BuiltinTopicKey_t BuiltinTopicKey_t;

/**
 * @typedef DDS_Duration_t Duration_t 
 *
 * @ingroup CppCoreStruct
 *
 * @brief ӳ��������� #DDS_Duration_t �ṹΪC++�ӿڡ�
 */
typedef DDS_Duration_t Duration_t;

/**
 * @typedef DDS_Time_t Time_t 
 *
 * @ingroup CppCoreStruct
 *
 * @brief ӳ��������� #DDS_Time_t �ṹΪC++�ӿڡ�
 */
typedef DDS_Time_t Time_t;

/** @brief ������  @ingroup   CppConstant */
DCPSDLL extern const Long DURATION_INFINITE_SEC;
/** @brief 0��  @ingroup   CppConstant */
DCPSDLL extern const Long DURATION_ZERO_SEC;
/** @brief ��������  @ingroup   CppConstant */
DCPSDLL extern const ULong DURATION_INFINITE_NSEC;
/** @brief 0����  @ingroup   CppConstant */
DCPSDLL extern const ULong DURATION_ZERO_NSEC;
/** @brief  ʱ���Ϊ0�� @ingroup   CppConstant */
DCPSDLL extern const Time_t TIME_ZERO;
/** @brief  ��Ч��ʱ��㡣 @ingroup   CppConstant */
DCPSDLL extern const Time_t TIME_INVALID;
/** @brief  ���޳���ʱ��㡣 @ingroup   CppConstant */
DCPSDLL extern const Time_t TIME_INFINITE;

/**
 * @typedef DDS_InstanceHandle_t InstanceHandle_t 
 *
 * @ingroup CppCoreStruct
 *
 * @brief ӳ��������� #DDS_InstanceHandle_t �ṹΪC++�ӿڡ�
 */
typedef DDS_InstanceHandle_t InstanceHandle_t;

/**
 * @brief   ��ʾ��Ч�� InstanceHandle_t ��
 *
 * @ingroup CppConstant
 */
DCPSDLL extern const InstanceHandle_t HANDLE_NIL_NATIVE;

/**
 * @typedef DDS_KeyHash_t KeyHash_t 
 *
 * @ingroup CppCoreStruct
 *
 * @brief ӳ��������� #DDS_KeyHash_t �ṹΪC++�ӿڡ�
 */
typedef DDS_KeyHash_t KeyHash_t;

/**
 * @typedef DDS_InstanceHandleSeq InstanceHandleSeq 
 *
 * @ingroup CppCoreStruct
 *
 * @brief ӳ��������� #DDS_InstanceHandleSeq �ṹΪC++�ӿڡ�
 */
typedef DDS_InstanceHandleSeq InstanceHandleSeq;

/**
 * @typedef DDS_PublicationSendLocator PublicationSendLocator
 *
 * @ingroup CppCoreStruct
 *
 * @brief ӳ��������� #DDS_PublicationSendLocator �ṹΪC++�ӿڡ�
 */
typedef DDS_PublicationSendLocator PublicationSendLocator;

/**
 * @typedef DDS_PublicationSendLocatorSeq PublicationSendLocatorSeq
 *
 * @ingroup CppCoreStruct
 *
 * @brief ӳ��������� #DDS_PublicationSendLocatorSeq �ṹΪC++�ӿڡ�
 */
typedef DDS_PublicationSendLocatorSeq PublicationSendLocatorSeq;

/**
 * @typedef DDS_PublicationSendStatus PublicationSendStatus
 *
 * @ingroup CppCoreStruct
 *
 * @brief ӳ��������� #DDS_PublicationSendStatus �ṹΪC++�ӿڡ�
 */
typedef DDS_PublicationSendStatus PublicationSendStatus;

/**
 * @typedef DDS_PublicationSendStatusSeq PublicationSendStatusSeq
 *
 * @ingroup CppCoreStruct
 *
 * @brief ӳ��������� #DDS_PublicationSendStatusSeq �ṹΪC++�ӿڡ�
 */
typedef DDS_PublicationSendStatusSeq PublicationSendStatusSeq;

/**
 * @typedef DDS_ReturnCode_t ReturnCode_t 
 *
 * @ingroup CppCoreStruct
 *
 * @brief ӳ��������� #DDS_ReturnCode_t �ṹΪC++�ӿڡ�
 */
typedef DDS_ReturnCode_t ReturnCode_t;

/** @brief ִ�гɹ��� @ingroup CppConstant  */
DCPSDLL extern const ReturnCode_t RETCODE_OK;
/** @brief ִ�г��� @ingroup CppConstant  */
DCPSDLL extern const ReturnCode_t RETCODE_ERROR;
/** @brief ��֧�ֲ����� @ingroup CppConstant  */
DCPSDLL extern const ReturnCode_t RETCODE_UNSUPPORTED;
/** @brief ����ȷ�Ĳ����� @ingroup CppConstant  */
DCPSDLL extern const ReturnCode_t RETCODE_BAD_PARAMETER;
/** @brief ���ò�����ǰ������δ���㡣 @ingroup CppConstant  */
DCPSDLL extern const ReturnCode_t RETCODE_PRECONDITION_NOT_MET;
/** @brief ��Դ������ @ingroup CppConstant  */
DCPSDLL extern const ReturnCode_t RETCODE_OUT_OF_RESOURCES;
/** @brief ʵ��δʹ�ܣ����ܽ��иò����� @ingroup CppConstant  */
DCPSDLL extern const ReturnCode_t RETCODE_NOT_ENABLED;
/** @brief ��ͼ�޸�ʹ�ܺ����޸ĵ�Qos�� @ingroup CppConstant  */
DCPSDLL extern const ReturnCode_t RETCODE_IMMUTABLE_POLICY;
/** @brief ��һ�µ�Qos�� @ingroup CppConstant  */
DCPSDLL extern const ReturnCode_t RETCODE_INCONSISTENT;
/** @brief ��ͼɾ���Ѿ���ɾ����ʵ�塣 @ingroup CppConstant  */
DCPSDLL extern const ReturnCode_t RETCODE_ALREADY_DELETED;
/** @brief ������ʱ�� @ingroup CppConstant  */
DCPSDLL extern const ReturnCode_t RETCODE_TIMEOUT;
/** @brief �ڶ����ݵ�ʱ��û����Ч�����ݡ� @ingroup CppConstant  */
DCPSDLL extern const ReturnCode_t RETCODE_NO_DATA;
/** @brief �Ƿ��Ĳ����� @ingroup CppConstant  */
DCPSDLL extern const ReturnCode_t RETCODE_ILLEGAL_OPERATION;
/** @brief ������ȫԭ�򱻾ܾ��� @ingroup CppConstant  */
DCPSDLL extern const ReturnCode_t RETCODE_NOT_ALLOWED_BY_SEC;

/**
 * @typedef DDS_SequenceNumber_t SequenceNumber_t 
 *
 * @ingroup CppCoreStruct
 *
 * @brief ӳ��������� #DDS_SequenceNumber_t �ṹΪC++�ӿڡ�
 */
typedef DDS_SequenceNumber_t SequenceNumber_t;

#ifdef _ZRDDS_INCLUDE_CONTENTFILTER_TOPIC
/**
 * @typedef DDS_ContentFilterProperty_t ContentFilterProperty_t 
 *
 * @ingroup CppCoreStruct
 *
 * @brief ӳ��������� #DDS_ContentFilterProperty_t �ṹΪC++�ӿڡ�
 */
typedef DDS_ContentFilterProperty_t ContentFilterProperty_t;

#endif //_ZRDDS_INCLUDE_CONTENTFILTER_TOPIC
// Qos
/**
 * @typedef DDS_AsynchronousPublisherQosPolicy AsynchronousPublisherQosPolicy 
 *
 * @ingroup CppCoreStruct
 *
 * @brief ӳ��������� #DDS_AsynchronousPublisherQosPolicy �ṹΪC++�ӿڡ�
 */
typedef DDS_AsynchronousPublisherQosPolicy AsynchronousPublisherQosPolicy;

/**
 * @typedef DDS_BatchQosPolicy BatchQosPolicy 
 *
 * @ingroup CppCoreStruct
 *
 * @brief ӳ��������� #DDS_BatchQosPolicy �ṹΪC++�ӿڡ�
 */
typedef DDS_BatchQosPolicy BatchQosPolicy;

/**
 * @typedef DDS_DataReaderQos DataReaderQos 
 *
 * @ingroup CppCoreStruct
 *
 * @brief ӳ��������� #DDS_DataReaderQos �ṹΪC++�ӿڡ�
 */
typedef DDS_DataReaderQos DataReaderQos;

/**
 * @typedef DDS_DataRepresentationQosPolicy DataRepresentationQosPolicy 
 *
 * @ingroup CppCoreStruct
 *
 * @brief ӳ��������� #DDS_DataRepresentationQosPolicy �ṹΪC++�ӿڡ�
 */
typedef DDS_DataRepresentationQosPolicy DataRepresentationQosPolicy;

/**
 * @typedef DDS_DataWriterMessageModeQosPolicy DataWriterMessageModeQosPolicy 
 *
 * @ingroup CppCoreStruct
 *
 * @brief ӳ��������� #DDS_DataWriterMessageModeQosPolicy �ṹΪC++�ӿڡ�
 */
typedef DDS_DataWriterMessageModeQosPolicy DataWriterMessageModeQosPolicy;

/**
 * @typedef DDS_RtpsReliableWriterProtocol RtpsReliableWriterProtocol 
 *
 * @ingroup CppCoreStruct
 *
 * @brief ӳ��������� #DDS_RtpsReliableWriterProtocol �ṹΪC++�ӿڡ�
 */
typedef DDS_RtpsReliableWriterProtocol RtpsReliableWriterProtocol;

/**
 * @typedef DDS_DataWriterProtocolQosPolicy DataWriterProtocolQosPolicy 
 *
 * @ingroup CppCoreStruct
 *
 * @brief ӳ��������� #DDS_DataWriterProtocolQosPolicy �ṹΪC++�ӿڡ�
 */
typedef DDS_DataWriterProtocolQosPolicy DataWriterProtocolQosPolicy;

/**
 * @typedef DDS_DataWriterQos DataWriterQos 
 *
 * @ingroup CppCoreStruct
 *
 * @brief ӳ��������� #DDS_DataWriterQos �ṹΪC++�ӿڡ�
 */
typedef DDS_DataWriterQos DataWriterQos;

/**
 * @typedef DDS_DataWriterResourceLimitsInstanceReplacementKind DataWriterResourceLimitsInstanceReplacementKind 
 *
 * @ingroup CppCoreStruct
 *
 * @brief ӳ��������� #DDS_DataWriterResourceLimitsInstanceReplacementKind �ṹΪC++�ӿڡ�
 */
typedef DDS_DataWriterResourceLimitsInstanceReplacementKind DataWriterResourceLimitsInstanceReplacementKind;

/** @brief  ֻ�滻��ע����ʵ����ӳ����ĳ��� #DDS_UNREGISTERED_INSTANCE_REPLACEMENT �� @ingroup CppConstant */
DCPSDLL extern const DataWriterResourceLimitsInstanceReplacementKind UNREGISTERED_INSTANCE_REPLACEMENT;
/** @brief  ֻ�滻����ʵ����ӳ����ĳ��� #DDS_ALIVE_INSTANCE_REPLACEMENT �� @ingroup CppConstant */
DCPSDLL extern const DataWriterResourceLimitsInstanceReplacementKind ALIVE_INSTANCE_REPLACEMENT;
/** @brief  ֻ�滻�����ٵ�ʵ����ӳ����ĳ��� #DDS_DISPOSED_INSTANCE_REPLACEMENT �� @ingroup CppConstant */
DCPSDLL extern const DataWriterResourceLimitsInstanceReplacementKind DISPOSED_INSTANCE_REPLACEMENT;
/** @brief  �����滻����ʵ���������������滻��ע����ʵ����ӳ����ĳ��� #ALIVE_THEN_DISPOSED_INSTANCE_REPLACEMENT �� @ingroup CppConstant */
DCPSDLL extern const DataWriterResourceLimitsInstanceReplacementKind ALIVE_THEN_DISPOSED_INSTANCE_REPLACEMENT;
/** @brief  �����滻�����ٵ�ʵ���������������滻����ʵ����ӳ����ĳ��� #DISPOSED_THEN_ALIVE_INSTANCE_REPLACEMENT �� @ingroup CppConstant */
DCPSDLL extern const DataWriterResourceLimitsInstanceReplacementKind DISPOSED_THEN_ALIVE_INSTANCE_REPLACEMENT;
/** @brief  �滻��������ע����ʵ����ӳ����ĳ��� #ALIVE_OR_DISPOSED_INSTANCE_REPLACEMENT �� @ingroup CppConstant */
DCPSDLL extern const DataWriterResourceLimitsInstanceReplacementKind ALIVE_OR_DISPOSED_INSTANCE_REPLACEMENT;

/**
 * @typedef DDS_DataWriterResourceLimitsQosPolicy DataWriterResourceLimitsQosPolicy 
 *
 * @ingroup CppCoreStruct
 *
 * @brief ӳ��������� #DDS_DataWriterResourceLimitsQosPolicy �ṹΪC++�ӿڡ�
 */
typedef DDS_DataWriterResourceLimitsQosPolicy DataWriterResourceLimitsQosPolicy;

/**
 * @typedef DDS_LogType LogType 
 *
 * @ingroup CppCoreStruct
 *
 * @brief ӳ��������� #DDS_LogType �ṹΪC++�ӿڡ�
 */
typedef DDS_LogType LogType;

/**
 * @typedef DDS_LogQosPolicy LogQosPolicy 
 *
 * @ingroup CppCoreStruct
 *
 * @brief ӳ��������� #DDS_LogQosPolicy �ṹΪC++�ӿڡ�
 */
typedef DDS_LogQosPolicy LogQosPolicy;

/**
 * @typedef DDS_LogBackupKind LogBackupKind 
 *
 * @ingroup CppCoreStruct
 *
 * @brief ӳ��������� #DDS_LogBackupKind �ṹΪC++�ӿڡ�
 */
typedef DDS_LogBackupKind LogBackupKind;

#ifdef _ZRDDS_INCLUDE_GATEWAY
/**
 * @typedef DDS_GatewayQosPolicyKind GatewayQosPolicyKind
 *
 * @brief   ӳ��������� #DDS_GatewayQosPolicyKind �ṹΪC++�ӿ�.
 */
typedef DDS_GatewayQosPolicyKind GatewayQosPolicyKind;

/**
 * @typedef DDS_GatewayQosPolicy GatewayQosPolicy
 *
 * @brief   ӳ��������� #DDS_GatewayQosPolicy �ṹΪC++�ӿ�.
 */
typedef DDS_GatewayQosPolicy GatewayQosPolicy;

/**
 * @brief   �����������ز���ת����
 *
 * @ingroup CppConstant
 *
 * @details  �μ����ĳ��� #DDS_NO_FORWARD_GATEWAY_QOS ��
 */
DCPSDLL extern const GatewayQosPolicyKind NO_FORWARD_GATEWAY_QOS;

/**
 * @brief   ����Ҫ�������ؽ�Data(p)ת������֪��ͬһ����µ�����������ߡ�
 *
 * @ingroup CppConstant
 *
 * @details  �μ����ĳ��� #DDS_SPDP_FORWARD_GATEWAY_QOS ��
 */
DCPSDLL extern const GatewayQosPolicyKind SPDP_FORWARD_GATEWAY_QOS;

/**
 * @brief   ��Ҫ��������Э����ͨ�š�
 *
 * @ingroup CppConstant
 *
 * @warning ������δʵ�� �μ����ĳ��� #DDS_SEDP_FORWARD_GATEWAY_QOS ��
 */
DCPSDLL extern const GatewayQosPolicyKind SEDP_FORWARD_GATEWAY_QOS;

/**
 * @brief   ��Ҫ��������ת�����е����ݣ��������������Լ��û����ݣ���
 *
 * @ingroup CppConstant
 *
 * @details  �μ����ĳ��� #DDS_USER_FORWARD_GATEWAY_QOS ��
 */
DCPSDLL extern const GatewayQosPolicyKind USER_FORWARD_GATEWAY_QOS;

/**
 * @brief   ��Ҫ��������Э����ͨ�š�
 *
 * @ingroup CppConstant
 *
 * @warning ������δʵ�� �μ����ĳ��� #DDS_USER_FORWARD_ONLY_GATEWAY_QOS ��
 */
DCPSDLL extern const GatewayQosPolicyKind USER_FORWARD_ONLY_GATEWAY_QOS;

#endif // _ZRDDS_INCLUDE_GATEWAY

/**
 * @typedef DDS_Property_t Property_t
 *
 * @brief ��չ��Property_t.
 */
typedef DDS_Property_t Property_t;

/**
 * @typedef DDS_BinaryProperty_t BinaryProperty_t
 *
 * @brief ��ֵ�ļ�ֵ�ԡ�
 */
typedef DDS_BinaryProperty_t BinaryProperty_t;

typedef DDS_PropertySeq PropertySeq;

typedef DDS_BinaryPropertySeq BinaryPropertySeq;

typedef DDS_PropertyQosPolicy PropertyQosPolicy;

typedef DDS_TypeConsistencyEnforcementQosPolicy TypeConsistencyEnforcementQosPolicy;

#ifdef _ZRDDS_INCLUDE_MSGSTATISTICSINFO_QOS
/**
 * @typedef DDS_MsgStatisticsInfoQosPolicy MsgStatisticsInfoQosPolicy 
 *
 * @ingroup CppCoreStruct
 *
 * @brief ӳ��������� #DDS_MsgStatisticsInfoQosPolicy �ṹΪC++�ӿڡ�
 */
typedef DDS_MsgStatisticsInfoQosPolicy MsgStatisticsInfoQosPolicy;

#endif //_ZRDDS_INCLUDE_MSGSTATISTICSINFO_QOS
#ifdef _ZRDDS_INCLUDE_DEADLINE_QOS
/**
 * @typedef DDS_DeadlineQosPolicy DeadlineQosPolicy 
 *
 * @ingroup CppCoreStruct
 *
 * @brief ӳ��������� #DDS_DeadlineQosPolicy �ṹΪC++�ӿڡ�
 */
typedef DDS_DeadlineQosPolicy DeadlineQosPolicy;

#endif //_ZRDDS_INCLUDE_DEADLINE_QOS
#ifdef _ZRDDS_INCLUDE_DESTINATION_ORDER_QOS
/**
 * @typedef DDS_DestinationOrderQosPolicyKind DestinationOrderQosPolicyKind 
 *
 * @ingroup CppCoreStruct
 *
 * @brief ӳ��������� #DDS_DestinationOrderQosPolicyKind �ṹΪC++�ӿڡ�
 */
typedef DDS_DestinationOrderQosPolicyKind DestinationOrderQosPolicyKind;

/**
 * @brief   �����ݶ��߽��յ���˳��洢�����ݶ��ߵ��ڲ������С�
 *
 * @ingroup CppConstant
 *
 * @details �μ����ĳ��� #DDS_BY_RECEPTION_TIMESTAMP_DESTINATIONORDER_QOS ��
 */
DCPSDLL extern const DestinationOrderQosPolicyKind BY_RECEPTION_TIMESTAMP_DESTINATIONORDER_QOS;
/**
 * @brief   ���������ݵ�Դʱ���˳��洢�����ݶ��ߵ��ڲ������С�
 *
 * @ingroup CppConstant
 *
 * @details �μ����ĳ��� #DDS_BY_SOURCE_TIMESTAMP_DESTINATIONORDER_QOS ��
 */
DCPSDLL extern const DestinationOrderQosPolicyKind BY_SOURCE_TIMESTAMP_DESTINATIONORDER_QOS;

/**
 * @typedef DDS_DestinationOrderQosPolicy DestinationOrderQosPolicy 
 *
 * @ingroup CppCoreStruct
 *
 * @brief ӳ��������� #DDS_DestinationOrderQosPolicy �ṹΪC++�ӿڡ�
 */
typedef DDS_DestinationOrderQosPolicy DestinationOrderQosPolicy;

#endif //_ZRDDS_INCLUDE_DESTINATION_ORDER_QOS
/**
 * @typedef DDS_DiscoveryConfigQosPolicy DiscoveryConfigQosPolicy 
 *
 * @ingroup CppCoreStruct
 *
 * @brief ӳ��������� #DDS_DiscoveryConfigQosPolicy �ṹΪC++�ӿڡ�
 */
typedef DDS_DiscoveryConfigQosPolicy DiscoveryConfigQosPolicy;

/**
 * @typedef DDS_DomainParticipantFactoryQos DomainParticipantFactoryQos 
 *
 * @ingroup CppCoreStruct
 *
 * @brief ӳ��������� #DDS_DomainParticipantFactoryQos �ṹΪC++�ӿڡ�
 */
typedef DDS_DomainParticipantFactoryQos DomainParticipantFactoryQos;

/**
 * @typedef DDS_DomainParticipantQos DomainParticipantQos 
 *
 * @ingroup CppCoreStruct
 *
 * @brief ӳ��������� #DDS_DomainParticipantQos �ṹΪC++�ӿڡ�
 */
typedef DDS_DomainParticipantQos DomainParticipantQos;

/**
 * @typedef DDS_DurabilityQosPolicyKind DurabilityQosPolicyKind 
 *
 * @ingroup CppCoreStruct
 *
 * @brief ӳ��������� #DDS_DurabilityQosPolicyKind �ṹΪC++�ӿڡ�
 */
typedef DDS_DurabilityQosPolicyKind DurabilityQosPolicyKind;

/**
 * @brief   �޳־û���
 *
 * @ingroup CppConstant
 *
 * @details �μ����ĳ��� #DDS_VOLATILE_DURABILITY_QOS ��
 */
DCPSDLL extern const DurabilityQosPolicyKind VOLATILE_DURABILITY_QOS;

/**
 * @brief   ��������д�����ڴ��г־û���
 *
 * @ingroup CppConstant
 *
 * @details �μ����ĳ��� #DDS_TRANSIENT_LOCAL_DURABILITY_QOS ��
 */
DCPSDLL extern const DurabilityQosPolicyKind TRANSIENT_LOCAL_DURABILITY_QOS;

/**
 * @brief   ��������д�ߣ����������ݶ��߼���DDS����ʱ�Ѿ���ɾ��������д�ߣ����ڴ��г־û���
 *
 * @ingroup CppConstant
 *
 * @details �μ����ĳ��� #DDS_TRANSIENT_DURABILITY_QOS ��
 */
DCPSDLL extern const DurabilityQosPolicyKind TRANSIENT_DURABILITY_QOS;

/**
 * @brief   ��������д�ߣ����������ݶ��߼���DDS����ʱ�Ѿ���ɾ��������д�ߣ��ڳ־û��洢���ļ������ݿ⣩�г־û���
 *
 * @ingroup CppConstant
 *
 * @details �μ����ĳ��� #DDS_PERSISTENT_DURABILITY_QOS ��
 */
DCPSDLL extern const DurabilityQosPolicyKind PERSISTENT_DURABILITY_QOS;

/**
 * @typedef DDS_DurabilityQosPolicy DurabilityQosPolicy 
 *
 * @ingroup CppCoreStruct
 *
 * @brief ӳ��������� #DDS_DurabilityQosPolicy �ṹΪC++�ӿڡ�
 */
typedef DDS_DurabilityQosPolicy DurabilityQosPolicy;

/**
 * @typedef DDS_DurabilityServiceQosPolicy DurabilityServiceQosPolicy 
 *
 * @ingroup CppCoreStruct
 *
 * @brief ӳ��������� #DDS_DurabilityServiceQosPolicy �ṹΪC++�ӿڡ�
 */
typedef DDS_DurabilityServiceQosPolicy DurabilityServiceQosPolicy;

/**
 * @typedef DDS_EntityFactoryQosPolicy EntityFactoryQosPolicy 
 *
 * @ingroup CppCoreStruct
 *
 * @brief ӳ��������� #DDS_EntityFactoryQosPolicy �ṹΪC++�ӿڡ�
 */
typedef DDS_EntityFactoryQosPolicy EntityFactoryQosPolicy;

#ifdef _ZRXMLQOSINTERFACE
/**
 * @typedef DDS_QosProfileQosPolicy QosProfileQosPolicy 
 *
 * @ingroup CppCoreStruct
 *
 * @brief ӳ��������� #DDS_QosProfileQosPolicy �ṹΪC++�ӿڡ�
 */
typedef DDS_QosProfileQosPolicy QosProfileQosPolicy;
#endif // _ZRXMLQOSINTERFACE

#ifdef _ZRDDS_INCLUDE_GROUP_DATA_QOS
/**
 * @typedef DDS_GroupDataQosPolicy GroupDataQosPolicy 
 *
 * @ingroup CppCoreStruct
 *
 * @brief ӳ��������� #DDS_GroupDataQosPolicy �ṹΪC++�ӿڡ�
 */
typedef DDS_GroupDataQosPolicy GroupDataQosPolicy;

#endif //_ZRDDS_INCLUDE_GROUP_DATA_QOS
/**
 * @typedef DDS_HistoryQosPolicyKind HistoryQosPolicyKind 
 *
 * @ingroup CppCoreStruct
 *
 * @brief ӳ��������� #DDS_HistoryQosPolicyKind �ṹΪC++�ӿڡ�
 */
typedef DDS_HistoryQosPolicyKind HistoryQosPolicyKind;

/**
 * @brief   �������������������͡�
 *
 * @ingroup CppConstant
 *
 * @details �μ����ĳ��� #DDS_KEEP_LAST_HISTORY_QOS ��
 */
DCPSDLL extern const HistoryQosPolicyKind KEEP_LAST_HISTORY_QOS;
/**
 * @brief   ���Ա������������������͡�
 *
 * @ingroup CppConstant
 *
 * @details �μ����ĳ��� #DDS_KEEP_ALL_HISTORY_QOS ��
 */
DCPSDLL extern const HistoryQosPolicyKind KEEP_ALL_HISTORY_QOS;

/**
 * @typedef DDS_HistoryQosPolicy HistoryQosPolicy 
 *
 * @ingroup CppCoreStruct
 *
 * @brief ӳ��������� #DDS_HistoryQosPolicy �ṹΪC++�ӿڡ�
 */
typedef DDS_HistoryQosPolicy HistoryQosPolicy;

#ifdef _ZRDDS_INCLUDE_LATENCY_BUDGET_QOS
/**
 * @typedef DDS_LatencyBudgetQosPolicy LatencyBudgetQosPolicy 
 *
 * @ingroup CppCoreStruct
 *
 * @brief ӳ��������� #DDS_LatencyBudgetQosPolicy �ṹΪC++�ӿڡ�
 */
typedef DDS_LatencyBudgetQosPolicy LatencyBudgetQosPolicy;

#endif //_ZRDDS_INCLUDE_LATENCY_BUDGET_QOS
#ifdef _ZRDDS_INCLUDE_LIFESPAN_QOS
/**
 * @typedef DDS_LifespanQosPolicy LifespanQosPolicy 
 *
 * @ingroup CppCoreStruct
 *
 * @brief ӳ��������� #DDS_LifespanQosPolicy �ṹΪC++�ӿڡ�
 */
typedef DDS_LifespanQosPolicy LifespanQosPolicy;

#endif // _ZRDDS_INCLUDE_LIFESPAN_QOS
#ifdef _ZRDDS_INCLUDE_LIVELINESS_QOS
/**
 * @typedef DDS_LivelinessQosPolicyKind LivelinessQosPolicyKind 
 *
 * @ingroup CppCoreStruct
 *
 * @brief ӳ��������� #DDS_LivelinessQosPolicyKind �ṹΪC++�ӿڡ�
 */
typedef DDS_LivelinessQosPolicyKind LivelinessQosPolicyKind;

/**
 * @brief   ��ZRDDS�ײ��Զ���������������
 *
 * @ingroup CppConstant
 *
 * @details �μ����ĳ��� #DDS_AUTOMATIC_LIVELINESS_QOS ��
 */
DCPSDLL extern const LivelinessQosPolicyKind AUTOMATIC_LIVELINESS_QOS;
/**
 * @brief   ͨ����������ֶ���������������
 *
 * @ingroup CppConstant
 *
 * @details �μ����ĳ��� #DDS_MANUAL_BY_PARTICIPANT_LIVELINESS_QOS ��
 */
DCPSDLL extern const LivelinessQosPolicyKind MANUAL_BY_PARTICIPANT_LIVELINESS_QOS;
/**
 * @brief   ������д���ֶ���������������
 *
 * @ingroup CppConstant
 *
 * @details �μ����ĳ��� #DDS_MANUAL_BY_TOPIC_LIVELINESS_QOS ��
 */
DCPSDLL extern const LivelinessQosPolicyKind MANUAL_BY_TOPIC_LIVELINESS_QOS;

/**
 * @typedef DDS_LivelinessQosPolicy LivelinessQosPolicy 
 *
 * @ingroup CppCoreStruct
 *
 * @brief ӳ��������� #DDS_LivelinessQosPolicy �ṹΪC++�ӿڡ�
 */
typedef DDS_LivelinessQosPolicy LivelinessQosPolicy;

#endif //_ZRDDS_INCLUDE_LIVELINESS_QOS
#ifdef _ZRDDS_INCLUDE_OWNERSHIP_QOS
/**
 * @typedef DDS_OwnershipQosPolicyKind OwnershipQosPolicyKind 
 *
 * @ingroup CppCoreStruct
 *
 * @brief ӳ��������� #DDS_OwnershipQosPolicyKind �ṹΪC++�ӿڡ�
 */
typedef DDS_OwnershipQosPolicyKind OwnershipQosPolicyKind;

/**
 * @brief   ��������Ȩ���͡�
 *
 * @ingroup CppConstant
 * 
 * @details �μ����ĳ��� #DDS_SHARED_OWNERSHIP_QOS ��
 */
DCPSDLL extern const OwnershipQosPolicyKind SHARED_OWNERSHIP_QOS;
/**
 * @brief   ��ռ����Ȩ���͡�
 *
 * @ingroup CppConstant
 * 
 * @details �μ����ĳ��� #DDS_EXCLUSIVE_OWNERSHIP_QOS ��
 */
DCPSDLL extern const OwnershipQosPolicyKind EXCLUSIVE_OWNERSHIP_QOS;

/**
 * @typedef DDS_OwnershipQosPolicy OwnershipQosPolicy 
 *
 * @ingroup CppCoreStruct
 *
 * @brief ӳ��������� #DDS_OwnershipQosPolicy �ṹΪC++�ӿڡ�
 */
typedef DDS_OwnershipQosPolicy OwnershipQosPolicy;

/**
 * @typedef DDS_OwnershipStrengthQosPolicy OwnershipStrengthQosPolicy 
 *
 * @ingroup CppCoreStruct
 *
 * @brief ӳ��������� #DDS_OwnershipStrengthQosPolicy �ṹΪC++�ӿڡ�
 */
typedef DDS_OwnershipStrengthQosPolicy OwnershipStrengthQosPolicy;

#endif //_ZRDDS_INCLUDE_OWNERSHIP_QOS
#ifdef _ZRDDS_INCLUDE_PARTITION_QOS
/**
 * @typedef DDS_PartitionQosPolicy PartitionQosPolicy 
 *
 * @ingroup CppCoreStruct
 *
 * @brief ӳ��������� #DDS_PartitionQosPolicy �ṹΪC++�ӿڡ�
 */
typedef DDS_PartitionQosPolicy PartitionQosPolicy;

#endif //_ZRDDS_INCLUDE_PARTITION_QOS
#ifdef _ZRDDS_INCLUDE_PRESENTATION_QOS
/**
 * @typedef DDS_PresentationQosPolicyAccessScopeKind PresentationQosPolicyAccessScopeKind 
 *
 * @ingroup CppCoreStruct
 *
 * @brief ӳ��������� #DDS_PresentationQosPolicyAccessScopeKind �ṹΪC++�ӿڡ�
 */
typedef DDS_PresentationQosPolicyAccessScopeKind PresentationQosPolicyAccessScopeKind;

/** @brief  ��ΧΪ����ʵ�������庬��μ� PresentationQosPolicy @ingroup CppConstant */
DCPSDLL extern const PresentationQosPolicyAccessScopeKind INSTANCE_PRESENTATION_QOS;
/** @brief  ��ΧΪ���⣬���庬��μ� PresentationQosPolicy @ingroup CppConstant */
DCPSDLL extern const PresentationQosPolicyAccessScopeKind TOPIC_PRESENTATION_QOS;
/** @brief  ��ΧΪ�飬���庬��μ� PresentationQosPolicy @ingroup CppConstant */
DCPSDLL extern const PresentationQosPolicyAccessScopeKind GROUP_PRESENTATION_QOS;

/**
 * @typedef DDS_PresentationQosPolicy PresentationQosPolicy 
 *
 * @ingroup CppCoreStruct
 *
 * @brief ӳ��������� #DDS_PresentationQosPolicy �ṹΪC++�ӿڡ�
 */
typedef DDS_PresentationQosPolicy PresentationQosPolicy;

#endif //_ZRDDS_INCLUDE_PRESENTATION_QOS
/**
 * @typedef DDS_PublisherQos PublisherQos 
 *
 * @ingroup CppCoreStruct
 *
 * @brief ӳ��������� #DDS_PublisherQos �ṹΪC++�ӿڡ�
 */
typedef DDS_PublisherQos PublisherQos;

/**
 * @typedef DDS_PublishModeQosPolicyKind PublishModeQosPolicyKind 
 *
 * @ingroup CppCoreStruct
 *
 * @brief ӳ��������� #DDS_PublishModeQosPolicyKind �ṹΪC++�ӿڡ�
 */
typedef DDS_PublishModeQosPolicyKind PublishModeQosPolicyKind;

/** @brief  ͬ������ģʽ, �μ����ĳ��� #DDS_SYNCHRONOUS_PUBLISH_MODE_QOS �� @ingroup CppConstant */
DCPSDLL extern const PublishModeQosPolicyKind SYNCHRONOUS_PUBLISH_MODE_QOS;
/** @brief  �첽����ģʽ, �μ����ĳ��� #DDS_ASYNCHRONOUS_PUBLISH_MODE_QOS �� @ingroup CppConstant */
DCPSDLL extern const PublishModeQosPolicyKind ASYNCHRONOUS_PUBLISH_MODE_QOS;

/**
 * @typedef DDS_PublishModeQosPolicy PublishModeQosPolicy 
 *
 * @ingroup CppCoreStruct
 *
 * @brief ӳ��������� #DDS_PublishModeQosPolicy �ṹΪC++�ӿڡ�
 */
typedef DDS_PublishModeQosPolicy PublishModeQosPolicy;

/**
 * @typedef DDS_QosPolicyCount QosPolicyCount 
 *
 * @ingroup CppCoreStruct
 *
 * @brief ӳ��������� #DDS_QosPolicyCount �ṹΪC++�ӿڡ�
 */
typedef DDS_QosPolicyCount QosPolicyCount;

/**
 * @typedef DDS_QosPolicyId_t QosPolicyId_t 
 *
 * @ingroup CppCoreStruct
 *
 * @brief ӳ��������� #DDS_QosPolicyId_t �ṹΪC++�ӿڡ�
 */
typedef DDS_QosPolicyId_t QosPolicyId_t;

/** @brief  ��Ч�ı�ʶ�� @ingroup CppConstant */
DCPSDLL extern const QosPolicyId_t INVALID_QOS_POLICY_ID;
/** @brief  ��ʶ UserDataQosPolicy �� @ingroup CppConstant */
DCPSDLL extern const QosPolicyId_t USERDATA_QOS_POLICY_ID;
/** @brief  ��ʶ DurabilityQosPolicy �� @ingroup CppConstant */
DCPSDLL extern const QosPolicyId_t DURABILITY_QOS_POLICY_ID;
/** @brief  ��ʶ PresentationQosPolicy �� @ingroup CppConstant */
DCPSDLL extern const QosPolicyId_t PRESENTATION_QOS_POLICY_ID;
/** @brief  ��ʶ DeadlineQosPolicy �� @ingroup CppConstant */
DCPSDLL extern const QosPolicyId_t DEADLINE_QOS_POLICY_ID;
/** @brief  ��ʶ LatencyBudgetQosPolicy �� @ingroup CppConstant */
DCPSDLL extern const QosPolicyId_t LATENCYBUDGET_QOS_POLICY_ID;
/** @brief  ��ʶ OwnershipQosPolicy �� @ingroup CppConstant */
DCPSDLL extern const QosPolicyId_t OWNERSHIP_QOS_POLICY_ID;
/** @brief  ��ʶ OwnershipStrengthQosPolicy �� @ingroup CppConstant */
DCPSDLL extern const QosPolicyId_t OWNERSHIPSTRENGTH_QOS_POLICY_ID;
/** @brief  ��ʶ LivelinessQosPolicy �� @ingroup CppConstant */
DCPSDLL extern const QosPolicyId_t LIVELINESS_QOS_POLICY_ID;
/** @brief  ��ʶ TimeBasedFilterQosPolicy �� @ingroup CppConstant */
DCPSDLL extern const QosPolicyId_t TIMEBASEDFILTER_QOS_POLICY_ID;
/** @brief  ��ʶ PartitionQosPolicy �� @ingroup CppConstant */
DCPSDLL extern const QosPolicyId_t PARTITION_QOS_POLICY_ID;
/** @brief  ��ʶ ReliabilityQosPolicy �� @ingroup CppConstant */
DCPSDLL extern const QosPolicyId_t RELIABILITY_QOS_POLICY_ID;
/** @brief  ��ʶ DestinationOrderQosPolicy �� @ingroup CppConstant */
DCPSDLL extern const QosPolicyId_t DESTINATIONORDER_QOS_POLICY_ID;
/** @brief  ��ʶ HistoryQosPolicy �� @ingroup CppConstant */
DCPSDLL extern const QosPolicyId_t HISTORY_QOS_POLICY_ID;
/** @brief  ��ʶ ResourceLimitsQosPolicy �� @ingroup CppConstant */
DCPSDLL extern const QosPolicyId_t RESOURCELIMITS_QOS_POLICY_ID;
/** @brief  ��ʶ EntityFactoryQosPolicy �� @ingroup CppConstant */
DCPSDLL extern const QosPolicyId_t ENTITYFACTORY_QOS_POLICY_ID;
/** @brief  ��ʶ WriterDataLifeCycleQosPolicy �� @ingroup CppConstant */
DCPSDLL extern const QosPolicyId_t WRITERDATALIFECYCLE_QOS_POLICY_ID;
/** @brief  ��ʶ ReaderDataLifeCycleQosPolicy �� @ingroup CppConstant */
DCPSDLL extern const QosPolicyId_t READERDATALIFECYCLE_QOS_POLICY_ID;
/** @brief  ��ʶ TopicDataQosPolicy �� @ingroup CppConstant */
DCPSDLL extern const QosPolicyId_t TOPICDATA_QOS_POLICY_ID;
/** @brief  ��ʶ GroupDataQosPolicy �� @ingroup CppConstant */
DCPSDLL extern const QosPolicyId_t GROUPDATA_QOS_POLICY_ID;
/** @brief  ��ʶ TransportPriorityQosPolicy �� @ingroup CppConstant */
DCPSDLL extern const QosPolicyId_t TRANSPORTPRIORITY_QOS_POLICY_ID;
/** @brief  ��ʶ LifespanQosPolicy �� @ingroup CppConstant */
DCPSDLL extern const QosPolicyId_t LIFESPAN_QOS_POLICY_ID;
/** @brief  ��ʶ DurabilityServiceQosPolicy �� @ingroup CppConstant */
DCPSDLL extern const QosPolicyId_t DURABILITYSERVICE_QOS_POLICY_ID;
/** @brief  ��ʶ RepresentationQosPolicy �� @ingroup CppConstant */
DCPSDLL extern const QosPolicyId_t DATA_REPRESENTATION_QOS_POLICY_ID;
/** @brief  �������͡� @ingroup CppConstant */
DCPSDLL extern const QosPolicyId_t TYPE_CONSISTENCY_ENFORCEMENT_QOS_POLICY_ID;
/** @brief  �������͡� @ingroup CppConstant */
DCPSDLL extern const QosPolicyId_t NETWORKCONFIG_QOS_POLICY_ID;
/** @brief  �������͡� @ingroup CppConstant */
DCPSDLL extern const QosPolicyId_t DISCOVERYCONFIG_QOS_POLICY_ID;

/**
 * @typedef DDS_TransportKind TransportKind 
 *
 * @ingroup CppCoreStruct
 *
 * @brief ӳ��������� #DDS_TransportKind �ṹΪC++�ӿڡ�
 */
typedef DDS_TransportKind TransportKind;

/**
 * @typedef DDS_LocatorStatusKind LocatorStatusKind 
 *
 * @ingroup CppCoreStruct
 *
 * @brief ӳ��������� #DDS_LocatorStatusKind �ṹΪC++�ӿڡ�
 */
typedef DDS_LocatorStatusKind LocatorStatusKind;

#ifdef _ZRDDS_RIO
/**
 * @typedef DDS_RapidIOConfigQosPolicy RapidIOConfigQosPolicy 
 *
 * @ingroup CppCoreStruct
 *
 * @brief ӳ��������� #DDS_RapidIOConfigQosPolicy �ṹΪC++�ӿڡ�
 */
typedef DDS_RapidIOConfigQosPolicy RapidIOConfigQosPolicy;

/**
 * @typedef DDS_RapidIOControllerQosPolicy RapidIOControllerQosPolicy 
 *
 * @ingroup CppCoreStruct
 *
 * @brief ӳ��������� #DDS_RapidIOControllerQosPolicy �ṹΪC++�ӿڡ�
 */
typedef DDS_RapidIOControllerQosPolicy RapidIOControllerQosPolicy;
#endif /* _ZRDDS_RIO */

/**
 * @typedef DDS_ReaderDataLifecycleQosPolicy ReaderDataLifecycleQosPolicy 
 *
 * @ingroup CppCoreStruct
 *
 * @brief ӳ��������� #DDS_ReaderDataLifecycleQosPolicy �ṹΪC++�ӿڡ�
 */
typedef DDS_ReaderDataLifecycleQosPolicy ReaderDataLifecycleQosPolicy;

/**
 * @typedef DDS_ReceiverThreadConfigQosPolicy ReceiverThreadConfigQosPolicy 
 *
 * @ingroup CppCoreStruct
 *
 * @brief ӳ��������� #DDS_ReceiverThreadConfigQosPolicy �ṹΪC++�ӿڡ�
 */
typedef DDS_ReceiverThreadConfigQosPolicy ReceiverThreadConfigQosPolicy;

/**
 * @typedef DDS_ReceiverThreadKind ReceiverThreadKind 
 *
 * @ingroup CppCoreStruct
 *
 * @brief ӳ��������� #DDS_ReceiverThreadKind �ṹΪC++�ӿڡ�
 */
typedef DDS_ReceiverThreadKind ReceiverThreadKind;

/**
 * @brief  ÿ���˿�һ�������̡߳�
 *
 * @ingroup CppConstant
 *
 * @details �μ����ĳ��� #DDS_THREAD_PER_PORT ��
 */
DCPSDLL extern const ReceiverThreadKind THREAD_PER_PORT;
/**
 * @brief  ÿ������һ�������̣߳����õ�һ���̣߳��û���һ���̡߳�
 *
 * @ingroup CppConstant
 *
 * @details �μ����ĳ��� #DDS_THREAD_PER_KIND ��
 */
DCPSDLL extern const ReceiverThreadKind THREAD_PER_KIND;
/**
 * @brief  ���еĶ˿ڶ�ʹ��һ���̡߳�
 *
 * @ingroup CppConstant
 *
 * @details �μ����ĳ��� #DDS_THREAD_ALL_PORTS ��
 */
DCPSDLL extern const ReceiverThreadKind THREAD_ALL_PORTS;

/**
 * @typedef DDS_ReliabilityQosPolicyKind ReliabilityQosPolicyKind 
 *
 * @ingroup CppCoreStruct
 *
 * @brief ӳ��������� #DDS_ReliabilityQosPolicyKind �ṹΪC++�ӿڡ�
 */
typedef DDS_ReliabilityQosPolicyKind ReliabilityQosPolicyKind;

/** @brief ������Ϊ���ã��μ����ĳ��� #DDS_BEST_EFFORT_RELIABILITY_QOS �� @ingroup CppConstant */
DCPSDLL extern const ReliabilityQosPolicyKind BEST_EFFORT_RELIABILITY_QOS;
/** @brief �ɿ����ã��μ����ĳ��� #DDS_BEST_EFFORT_RELIABILITY_QOS ��@ingroup CppConstant */
DCPSDLL extern const ReliabilityQosPolicyKind RELIABLE_RELIABILITY_QOS;

/**
 * @typedef DDS_ReliabilityQosPolicy ReliabilityQosPolicy 
 *
 * @ingroup CppCoreStruct
 *
 * @brief ӳ��������� #DDS_ReliabilityQosPolicy �ṹΪC++�ӿڡ�
 */
typedef DDS_ReliabilityQosPolicy ReliabilityQosPolicy;

/**
 * @typedef DDS_ResourceLimitsQosPolicy ResourceLimitsQosPolicy 
 *
 * @ingroup CppCoreStruct
 *
 * @brief ӳ��������� #DDS_ResourceLimitsQosPolicy �ṹΪC++�ӿڡ�
 */
typedef DDS_ResourceLimitsQosPolicy ResourceLimitsQosPolicy;

/**
 * @typedef DDS_SampleRejectedStatusKind SampleRejectedStatusKind 
 *
 * @ingroup CppCoreStruct
 *
 * @brief   ���ڱ�ʶ�����������ܾ���ԭ�����͡�
 */
typedef DDS_SampleRejectedStatusKind SampleRejectedStatusKind;

/** @brief   ��������δ���ܾ����μ����ĳ��� #DDS_NOT_REJECTED �� @ingroup CppConstant */
DCPSDLL extern const SampleRejectedStatusKind NOT_REJECTED;
/** @brief   ������������ ResourceLimitsQosPolicy::max_instances ԭ�򱻾ܾ����μ����ĳ��� #DDS_REJECTED_BY_INSTANCE_LIMIT ��@ingroup CppConstant */
DCPSDLL extern const SampleRejectedStatusKind REJECTED_BY_INSTANCE_LIMIT;
/** @brief   ������������ ResourceLimitsQosPolicy::max_samples ԭ�򱻾ܾ����μ����ĳ��� #DDS_REJECTED_BY_SAMPLES_LIMIT �� @ingroup CppConstant */
DCPSDLL extern const SampleRejectedStatusKind REJECTED_BY_SAMPLES_LIMIT;
/** @brief   ������������ ResourceLimitsQosPolicy::max_samples_per_instance ԭ�򱻾ܾ����μ����ĳ��� #DDS_REJECTED_BY_SAMPLES_PER_INSTANCE_LIMIT �� @ingroup CppConstant */
DCPSDLL extern const SampleRejectedStatusKind REJECTED_BY_SAMPLES_PER_INSTANCE_LIMIT;

/**
 * @typedef DDS_SubscriberQos SubscriberQos 
 *
 * @ingroup CppCoreStruct
 *
 * @brief ӳ��������� #DDS_SubscriberQos �ṹΪC++�ӿڡ�
 */
typedef DDS_SubscriberQos SubscriberQos;

/**
 * @typedef DDS_ThreadCoreAffinityQosPolicy ThreadCoreAffinityQosPolicy 
 *
 * @ingroup CppCoreStruct
 *
 * @brief ӳ��������� #DDS_ThreadCoreAffinityQosPolicy �ṹΪC++�ӿڡ�
 */
typedef DDS_ThreadCoreAffinityQosPolicy ThreadCoreAffinityQosPolicy;

#ifdef _ZRDDS_INCLUDE_TIME_BASED_FILTER_QOS
/**
 * @typedef DDS_TimeBasedFilterQosPolicy TimeBasedFilterQosPolicy 
 *
 * @ingroup CppCoreStruct
 *
 * @brief ӳ��������� #DDS_TimeBasedFilterQosPolicy �ṹΪC++�ӿڡ�
 */
typedef DDS_TimeBasedFilterQosPolicy TimeBasedFilterQosPolicy;

#endif //_ZRDDS_INCLUDE_TIME_BASED_FILTER_QOS
#ifdef _ZRDDS_INCLUDE_TOPIC_DATA_QOS
/**
 * @typedef DDS_TopicDataQosPolicy TopicDataQosPolicy 
 *
 * @ingroup CppCoreStruct
 *
 * @brief ӳ��������� #DDS_TopicDataQosPolicy �ṹΪC++�ӿڡ�
 */
typedef DDS_TopicDataQosPolicy TopicDataQosPolicy;

#endif //_ZRDDS_INCLUDE_TOPIC_DATA_QOS
/**
 * @typedef DDS_TopicQos TopicQos 
 *
 * @ingroup CppCoreStruct
 *
 * @brief ӳ��������� #DDS_TopicQos �ṹΪC++�ӿڡ�
 */
typedef DDS_TopicQos TopicQos;

/**
 * @typedef DDS_TransportConfigQosPolicy TransportConfigQosPolicy 
 *
 * @ingroup CppCoreStruct
 *
 * @brief ӳ��������� #DDS_TransportConfigQosPolicy �ṹΪC++�ӿڡ�
 */
typedef DDS_TransportConfigQosPolicy TransportConfigQosPolicy;

#ifdef _ZRDDS_INCLUDE_TRANSPORT_PRIORITY_QOS
/**
 * @typedef DDS_TransportPriorityQosPolicy TransportPriorityQosPolicy 
 *
 * @ingroup CppCoreStruct
 *
 * @brief ӳ��������� #DDS_TransportPriorityQosPolicy �ṹΪC++�ӿڡ�
 */
typedef DDS_TransportPriorityQosPolicy TransportPriorityQosPolicy;

#endif //_ZRDDS_INCLUDE_TRANSPORT_PRIORITY_QOS
#ifdef _ZRDDS_INCLUDE_USER_DATA_QOS
/**
 * @typedef DDS_UserDataQosPolicy UserDataQosPolicy 
 *
 * @ingroup CppCoreStruct
 *
 * @brief ӳ��������� #DDS_UserDataQosPolicy �ṹΪC++�ӿڡ�
 */
typedef DDS_UserDataQosPolicy UserDataQosPolicy;

#endif //_ZRDDS_INCLUDE_USER_DATA_QOS
/**
 * @typedef DDS_WriterDataLifecycleQosPolicy WriterDataLifecycleQosPolicy 
 *
 * @ingroup CppCoreStruct
 *
 * @brief ӳ��������� #DDS_WriterDataLifecycleQosPolicy �ṹΪC++�ӿڡ�
 */
typedef DDS_WriterDataLifecycleQosPolicy WriterDataLifecycleQosPolicy;

/**
 * @brief   ����� DomainParticipantFactoryQos ��ʾʹ��ZRDDSĬ�ϵ�QoS��
 *
 * @ingroup CppCoreStruct
 *          
 * @details �μ����ĳ��� #DDS_DOMAINPARTICIPANT_FACTORY_QOS_DEFAULT ��
 */

DCPSDLL extern const DDS_DomainParticipantFactoryQos& DOMAINPARTICIPANT_FACTORY_QOS_DEFAULT;

/**
 * @brief   ����� DomainParticipantQos ��ʾʹ�ñ����ڸ�ʵ���е�Ĭ��QoS��
 *
 * @ingroup CppCoreStruct
 *
 * @details �μ����ĳ��� #DDS_DOMAINPARTICIPANT_QOS_DEFAULT ��
 */

DCPSDLL extern const DDS_DomainParticipantQos& DOMAINPARTICIPANT_QOS_DEFAULT;

/**
 * @brief   ����� PublisherQos ��ʾʹ�ñ����ڸ�ʵ���е�Ĭ��QoS��
 *
 * @ingroup CppCoreStruct
 *          
 * @details �μ����ĳ��� #DDS_PUBLISHER_QOS_DEFAULT ��
 */

DCPSDLL extern const DDS_PublisherQos& PUBLISHER_QOS_DEFAULT;

/**
 * @brief   ����� SubscriberQos ��ʾʹ�ñ����ڸ�ʵ���е�Ĭ��QoS��
 *
 * @ingroup CppCoreStruct
 *
 * @details �μ����ĳ��� #DDS_SUBSCRIBER_QOS_DEFAULT ��
 */

DCPSDLL extern const DDS_SubscriberQos& SUBSCRIBER_QOS_DEFAULT;

/**
 * @brief   ����� DataWriterQos ��ʾʹ�ñ����ڸ�ʵ���е�Ĭ��QoS��
 *
 * @ingroup CppCoreStruct
 *
 * @details �μ����ĳ��� #DDS_DATAWRITER_QOS_DEFAULT ��
 */

DCPSDLL extern const DDS_DataWriterQos& DATAWRITER_QOS_DEFAULT;

/**
 * @brief   ����� DataReaderQos ��ʾʹ�ñ����ڸ�ʵ���е�Ĭ��QoS��
 *
 * @ingroup CppCoreStruct
 *
 * @details �μ����ĳ��� #DDS_DATAREADER_QOS_DEFAULT ��
 */

DCPSDLL extern const DDS_DataReaderQos& DATAREADER_QOS_DEFAULT;

/**
 * @brief   ����� TopicQos ��ʾʹ�ñ����ڸ�ʵ���е�Ĭ��QoS��
 *
 * @ingroup CppCoreStruct
 *
 * @details �μ����ĳ��� #DDS_TOPIC_QOS_DEFAULT ��
 */

DCPSDLL extern const DDS_TopicQos& TOPIC_QOS_DEFAULT;

/**
 * @brief   ����� DataWriterQos ��ʾʹ������д�߹��������QoS��
 *
 * @ingroup CppCoreStruct
 *
 * @details �μ����ĳ��� #DDS_DATAWRITER_QOS_USE_TOPIC_QOS ��
 */

DCPSDLL extern const DDS_DataWriterQos& DATAWRITER_QOS_USE_TOPIC_QOS;

/**
 * @brief   ����� DataReaderQos ��ʾʹ�����ݶ��߹��������QoS��
 *
 * @ingroup CppCoreStruct
 *
 * @details �μ����ĳ��� #DDS_DATAREADER_QOS_USE_TOPIC_QOS ��
 */

DCPSDLL extern const DDS_DataReaderQos& DATAREADER_QOS_USE_TOPIC_QOS;

#if defined(_ZRDDSSECURITY)

/**
 * @typedef DDS_DataHolder DataHolder 
 *
 * @ingroup CppCoreStruct
 *
 * @brief ӳ��������� #DDS_DataHolder �ṹΪC++�ӿڡ�
 */
typedef DDS_DataHolder DataHolder;

/**
 * @typedef DDS_DataHolderSeq DataHolderSeq 
 *
 * @ingroup CppCoreStruct
 *
 * @brief ӳ��������� #DDS_DataHolderSeq �ṹΪC++�ӿڡ�
 */
typedef DDS_DataHolderSeq DataHolderSeq;

/**
 * @typedef DDS_Tag Tag 
 *
 * @ingroup CppCoreStruct
 *
 * @brief ӳ��������� #DDS_Tag �ṹΪC++�ӿڡ�
 */
typedef DDS_Tag Tag;

/**
 * @typedef DDS_TagSeq TagSeq 
 *
 * @ingroup CppCoreStruct
 *
 * @brief ӳ��������� #DDS_TagSeq �ṹΪC++�ӿڡ�
 */
typedef DDS_TagSeq TagSeq;

/**
 * @typedef DDS_DataTags DataTags 
 *
 * @ingroup CppCoreStruct
 *
 * @brief ӳ��������� #DDS_DataTags �ṹΪC++�ӿڡ�
 */
typedef DDS_DataTags DataTags;

/**
 * @typedef DDS_DataTagQosPolicy DataTagQosPolicy 
 *
 * @ingroup CppCoreStruct
 *
 * @brief ӳ��������� #DDS_DataTagQosPolicy �ṹΪC++�ӿڡ�
 */
typedef DDS_DataTagQosPolicy DataTagQosPolicy;

/**
 * @typedef DDS_SecurityPluginType SecurityPluginType
 *
 * @ingroup CppCoreStruct
 *
 * @brief ӳ��������� #DDS_SecurityPluginType �ṹΪC++�ӿڡ�
 */
typedef DDS_SecurityPluginType SecurityPluginType;

/**
 * @typedef DDS_SecurityPlugin SecurityPlugin
 *
 * @ingroup CppCoreStruct
 *
 * @brief ӳ��������� #DDS_SecurityPlugin �ṹΪC++�ӿڡ�
 */
typedef DDS_SecurityPlugin SecurityPlugin;

/**
 * @typedef DDS_SecurityPluginSeq SecurityPluginSeq
 *
 * @ingroup CppCoreStruct
 *
 * @brief ӳ��������� #DDS_SecurityPluginSeq �ṹΪC++�ӿڡ�
 */
typedef DDS_SecurityPluginSeq SecurityPluginSeq;

/**
 * @typedef DDS_SecurityPluginQosPolicy SecurityPluginQosPolicy
 *
 * @ingroup CppCoreStruct
 *
 * @brief ӳ��������� #DDS_SecurityPluginQosPolicy �ṹΪC++�ӿڡ�
 */
typedef DDS_SecurityPluginQosPolicy SecurityPluginQosPolicy;


/**
 * @typedef DDS_EndpointSecurityInfo EndpointSecurityInfo
 *
 * @ingroup CppCoreStruct
 *
 * @brief ӳ��������� #DDS_EndpointSecurityInfo �ṹΪC++�ӿڡ�
 */
typedef DDS_EndpointSecurityInfo EndpointSecurityInfo;

#endif

/**
 * @typedef DDS_SubscriptionMatchedStatus SubscriptionMatchedStatus 
 *
 * @ingroup CppCoreStruct
 *
 * @brief ӳ��������� #DDS_SubscriptionMatchedStatus �ṹΪC++�ӿڡ�
 */
typedef DDS_SubscriptionMatchedStatus SubscriptionMatchedStatus;

/**
 * @typedef DDS_InconsistentTopicStatus InconsistentTopicStatus 
 *
 * @ingroup CppCoreStruct
 *
 * @brief ӳ��������� #DDS_InconsistentTopicStatus �ṹΪC++�ӿڡ�
 */
typedef DDS_InconsistentTopicStatus InconsistentTopicStatus;

#ifdef _ZRDDS_INCLUDE_LIVELINESS_QOS
/**
 * @typedef DDS_LivelinessChangedStatus LivelinessChangedStatus 
 *
 * @ingroup CppCoreStruct
 *
 * @brief ӳ��������� #DDS_LivelinessChangedStatus �ṹΪC++�ӿڡ�
 */
typedef DDS_LivelinessChangedStatus LivelinessChangedStatus;

/**
 * @typedef DDS_LivelinessLostStatus LivelinessLostStatus 
 *
 * @ingroup CppCoreStruct
 *
 * @brief ӳ��������� #DDS_LivelinessLostStatus �ṹΪC++�ӿڡ�
 */
typedef DDS_LivelinessLostStatus LivelinessLostStatus;

#endif //_ZRDDS_INCLUDE_LIVELINESS_QOS
#ifdef _ZRDDS_INCLUDE_DEADLINE_QOS
/**
 * @typedef DDS_OfferedDeadlineMissedStatus OfferedDeadlineMissedStatus 
 *
 * @ingroup CppCoreStruct
 *
 * @brief ӳ��������� #DDS_OfferedDeadlineMissedStatus �ṹΪC++�ӿڡ�
 */
typedef DDS_OfferedDeadlineMissedStatus OfferedDeadlineMissedStatus;

/**
 * @typedef DDS_RequestedDeadlineMissedStatus RequestedDeadlineMissedStatus 
 *
 * @ingroup CppCoreStruct
 *
 * @brief ӳ��������� #DDS_RequestedDeadlineMissedStatus �ṹΪC++�ӿڡ�
 */
typedef DDS_RequestedDeadlineMissedStatus RequestedDeadlineMissedStatus;

#endif //_ZRDDS_INCLUDE_DEADLINE_QOS
/**
 * @typedef DDS_OfferedIncompatibleQosStatus OfferedIncompatibleQosStatus 
 *
 * @ingroup CppCoreStruct
 *
 * @brief ӳ��������� #DDS_OfferedIncompatibleQosStatus �ṹΪC++�ӿڡ�
 */
typedef DDS_OfferedIncompatibleQosStatus OfferedIncompatibleQosStatus;

/**
 * @typedef DDS_PublicationMatchedStatus PublicationMatchedStatus 
 *
 * @ingroup CppCoreStruct
 *
 * @brief ӳ��������� #DDS_PublicationMatchedStatus �ṹΪC++�ӿڡ�
 */
typedef DDS_PublicationMatchedStatus PublicationMatchedStatus;

/**
 * @typedef DDS_RequestedIncompatibleQosStatus RequestedIncompatibleQosStatus 
 *
 * @ingroup CppCoreStruct
 *
 * @brief ӳ��������� #DDS_RequestedIncompatibleQosStatus �ṹΪC++�ӿڡ�
 */
typedef DDS_RequestedIncompatibleQosStatus RequestedIncompatibleQosStatus;

/**
 * @typedef DDS_QosPolicyCountSeq QosPolicyCountSeq
 *
 * @ingroup CppCoreStruct
 *
 * @brief   ӳ��������� #DDS_QosPolicyCountSeq �ṹΪC++�ӿڡ� 
 */

typedef DDS_QosPolicyCountSeq QosPolicyCountSeq;

/**
 * @typedef DDS_SampleLostStatus SampleLostStatus 
 *
 * @ingroup CppCoreStruct
 *
 * @brief ӳ��������� #DDS_SampleLostStatus �ṹΪC++�ӿڡ�
 */
typedef DDS_SampleLostStatus SampleLostStatus;

/**
 * @typedef DDS_SampleRejectedStatus SampleRejectedStatus 
 *
 * @ingroup CppCoreStruct
 *
 * @brief ӳ��������� #DDS_SampleRejectedStatus �ṹΪC++�ӿڡ�
 */
typedef DDS_SampleRejectedStatus SampleRejectedStatus;

/**
 * @typedef DDS_SampleRejectedStatusKind SampleRejectedStatusKind 
 *
 * @ingroup CppCoreStruct
 *
 * @brief ӳ��������� #DDS_SampleRejectedStatusKind �ṹΪC++�ӿڡ�
 */
typedef DDS_SampleRejectedStatusKind SampleRejectedStatusKind;

/**
 * @typedef DDS_TypeConsistencyKind TypeConsistencyKind 
 *
 * @ingroup CppCoreStruct
 *
 * @brief ӳ��������� #DDS_TypeConsistencyKind �ṹΪC++�ӿڡ�
 */
typedef DDS_TypeConsistencyKind TypeConsistencyKind;

DCPSDLL extern const TypeConsistencyKind DISALLOW_TYPE_COERCION;
DCPSDLL extern const TypeConsistencyKind ALLOW_TYPE_COERCION;

/**
 * @typedef DDS_RTPS_MESSAGE_KIND RTPS_MESSAGE_KIND 
 *
 * @ingroup CppCoreStruct
 *
 * @brief ӳ��������� #DDS_RTPS_MESSAGE_KIND �ṹΪC++�ӿڡ�
 */
typedef DDS_RTPS_MESSAGE_KIND RTPS_MESSAGE_KIND;

// data
/**
 * @typedef DDS_Property Property
 *
 * @ingroup CppCoreStruct
 *
 * @brief ӳ��������� #DDS_Property �ṹΪC++�ӿڡ�
 */
typedef DDS_Property Property;

/**
 * @typedef DDS_PropertyList PropertyList 
 *
 * @ingroup CppCoreStruct
 *
 * @brief ӳ��������� #DDS_PropertyList �ṹΪC++�ӿڡ�
 */
typedef DDS_PropertyList PropertyList;

/**
 * @typedef DDS_ParticipantBuiltinTopicData ParticipantBuiltinTopicData 
 *
 * @ingroup CppCoreStruct
 *
 * @brief ӳ��������� #DDS_ParticipantBuiltinTopicData �ṹΪC++�ӿڡ�
 */
typedef DDS_ParticipantBuiltinTopicData ParticipantBuiltinTopicData;

/**
 * @typedef DDS_PublicationBuiltinTopicData PublicationBuiltinTopicData 
 *
 * @ingroup CppCoreStruct
 *
 * @brief ӳ��������� #DDS_PublicationBuiltinTopicData �ṹΪC++�ӿڡ�
 */
typedef DDS_PublicationBuiltinTopicData PublicationBuiltinTopicData;

/**
 * @typedef DDS_SubscriptionBuiltinTopicData SubscriptionBuiltinTopicData 
 *
 * @ingroup CppCoreStruct
 *
 * @brief ӳ��������� #DDS_SubscriptionBuiltinTopicData �ṹΪC++�ӿڡ�
 */
typedef DDS_SubscriptionBuiltinTopicData SubscriptionBuiltinTopicData;

#ifdef _ZRDDS_INCLUDE_TOPIC_BUILTIN_TOPIC_DATA
/**
 * @typedef DDS_TopicBuiltinTopicData TopicBuiltinTopicData 
 *
 * @ingroup CppCoreStruct
 *
 * @brief ӳ��������� #DDS_TopicBuiltinTopicData �ṹΪC++�ӿڡ�
 */
typedef DDS_TopicBuiltinTopicData TopicBuiltinTopicData;

#endif //_ZRDDS_INCLUDE_TOPIC_BUILTIN_TOPIC_DATA

#if defined(_ZRDDSSECURITY)
/**
 * @typedef DDS_ParticipantBuiltinTopicDataSecure ParticipantBuiltinTopicDataSecure 
 *
 * @ingroup CppCoreStruct
 *
 * @brief ӳ��������� #DDS_ParticipantBuiltinTopicDataSecure �ṹΪC++�ӿڡ�
 */
typedef DDS_ParticipantBuiltinTopicDataSecure ParticipantBuiltinTopicDataSecure;

/**
 * @typedef DDS_PublicationBuiltinTopicDataSecure PublicationBuiltinTopicDataSecure 
 *
 * @ingroup CppCoreStruct
 *
 * @brief ӳ��������� #DDS_PublicationBuiltinTopicDataSecure �ṹΪC++�ӿڡ�
 */
typedef DDS_PublicationBuiltinTopicDataSecure PublicationBuiltinTopicDataSecure;

/**
 * @typedef DDS_SubscriptionBuiltinTopicDataSecure SubscriptionBuiltinTopicDataSecure 
 *
 * @ingroup CppCoreStruct
 *
 * @brief ӳ��������� #DDS_SubscriptionBuiltinTopicDataSecure �ṹΪC++�ӿڡ�
 */
typedef DDS_SubscriptionBuiltinTopicDataSecure SubscriptionBuiltinTopicDataSecure;

#endif

/**
 * @typedef DDS_InstanceStateKind InstanceStateKind 
 *
 * @ingroup CppCoreStruct
 *
 * @brief ӳ��������� #DDS_InstanceStateKind �ṹΪC++�ӿڡ�
 */
typedef DDS_InstanceStateKind InstanceStateKind;

/**
 * @typedef DDS_InstanceStateMask InstanceStateMask 
 *
 * @ingroup CppCoreStruct
 *
 * @brief ӳ��������� #DDS_InstanceStateMask �ṹΪC++�ӿڡ�
 */
typedef DDS_InstanceStateMask InstanceStateMask;

/**
 * @brief   �������ʾ�����ʵ��״̬ InstanceStateKind ��
 *
 * @ingroup CppConstant
 *
 * @details �μ����ĳ��� #DDS_ANY_INSTANCE_STATE ��
 */
DCPSDLL extern const InstanceStateMask ANY_INSTANCE_STATE;
/**
 * @brief   �������ʾ�Ǵ���ʵ��״̬ InstanceStateKind ��
 *
 * @ingroup CppConstant
 *
 * @details �μ����ĳ��� #DDS_NOT_ALIVE_INSTANCE_STATE ��
 */
DCPSDLL extern const InstanceStateMask NOT_ALIVE_INSTANCE_STATE;
/**
 * @brief   ��״̬��ʾ������������ʵ�����ڴ��״̬��
 *
 * @ingroup CppConstant
 *
 * @details �μ����ĳ��� #DDS_ALIVE_INSTANCE_STATE ��
 */
DCPSDLL extern const InstanceStateMask ALIVE_INSTANCE_STATE;
/**
 * @brief  ��״̬��ʾ������������ʵ�����ڱ�����״̬��  
 *
 * @ingroup CppConstant
 *
 * @details �μ����ĳ��� #DDS_NOT_ALIVE_DISPOSED_INSTANCE_STATE ��
 */
DCPSDLL extern const InstanceStateMask NOT_ALIVE_DISPOSED_INSTANCE_STATE;
/**
 * @brief  ��״̬��ʾ������������ʵ�����ڱ�ע��״̬��  
 *
 * @ingroup CppConstant
 *
 * @details �μ����ĳ��� #DDS_NOT_ALIVE_NO_WRITERS_INSTANCE_STATE ��
 */
DCPSDLL extern const InstanceStateMask NOT_ALIVE_NO_WRITERS_INSTANCE_STATE;

/**
 * @typedef DDS_SampleInfo SampleInfo 
 *
 * @ingroup CppCoreStruct
 *
 * @brief ӳ��������� #DDS_SampleInfo �ṹΪC++�ӿڡ�
 */
typedef DDS_SampleInfo SampleInfo;

/**
 * @typedef DDS_SampleInfoValidMember SampleInfoValidMember 
 *
 * @ingroup CppCoreStruct
 *
 * @brief ӳ��������� #DDS_SampleInfoValidMember �ṹΪC++�ӿڡ�
 */
typedef DDS_SampleInfoValidMember SampleInfoValidMember;

/**
 * @typedef DDS_SampleInfoSeq SampleInfoSeq 
 *
 * @ingroup CppCoreStruct
 *
 * @brief ӳ��������� #DDS_SampleInfoSeq �ṹΪC++�ӿڡ�
 */
typedef DDS_SampleInfoSeq SampleInfoSeq;

/**
 * @typedef DDS_StatusKind StatusKind 
 *
 * @ingroup CppCoreStruct
 *
 * @brief ӳ��������� #DDS_StatusKind �ṹΪC++�ӿڡ�
 */
typedef DDS_StatusKind StatusKind;

/** @brief QoS��ƥ��״̬�� @ingroup CppConstant */
DCPSDLL extern const StatusKind INCONSISTENT_TOPIC_STATUS;
#ifdef _ZRDDS_INCLUDE_DEADLINE_QOS
/** @brief ����д�߽�ֹʱ��δ����״̬���͡� @ingroup CppConstant */
DCPSDLL extern const StatusKind OFFERED_DEADLINE_MISSED_STATUS;
/** @brief ���ݶ��߽�ֹʱ��δ����״̬���͡� @ingroup CppConstant */
DCPSDLL extern const StatusKind REQUESTED_DEADLINE_MISSED_STATUS;
#endif /* _ZRDDS_INCLUDE_DEADLINE_QOS */
/** @brief ����д�߶�QoS��ƥ��״̬���͡� @ingroup CppConstant */
DCPSDLL extern const StatusKind OFFERED_INCOMPATIBLE_QOS_STATUS;
/** @brief ���ݶ��߶�QoS��ƥ��״̬���͡� @ingroup CppConstant */
DCPSDLL extern const StatusKind REQUESTED_INCOMPATIBLE_QOS_STATUS;
/** @brief ����������ʧ״̬���͡� @ingroup CppConstant */
DCPSDLL extern const StatusKind SAMPLE_LOST_STATUS;
/** @brief ���������ܾ�״̬���͡� @ingroup CppConstant */
DCPSDLL extern const StatusKind SAMPLE_REJECTED_STATUS;
/** @brief ���������ݵ���״̬���͡� @ingroup CppConstant */
DCPSDLL extern const StatusKind DATA_ON_READERS_STATUS;
/** @brief ���ݶ������ݵ���״̬���͡� @ingroup CppConstant */
DCPSDLL extern const StatusKind DATA_AVAILABLE_STATUS;
/** @brief ����д�ߴ����״̬��ʧ״̬�� @ingroup CppConstant */
DCPSDLL extern const StatusKind LIVELINESS_LOST_STATUS;
/** @brief ����д�ߴ���Ըı�״̬���͡� @ingroup CppConstant */
DCPSDLL extern const StatusKind LIVELINESS_CHANGED_STATUS;
/** @brief ����д��ƥ��״̬���͡� @ingroup CppConstant */
DCPSDLL extern const StatusKind PUBLICATION_MATCHED_STATUS;
/** @brief ���ݶ���ƥ��״̬���͡� @ingroup CppConstant */
DCPSDLL extern const StatusKind SUBSCRIPTION_MATCHED_STATUS;

/**
 * @typedef DDS_StatusKindMask StatusKindMask 
 *
 * @ingroup CppCoreStruct
 *
 * @brief ӳ��������� #DDS_StatusKindMask �ṹΪC++�ӿڡ�
 */
typedef DDS_StatusKindMask StatusKindMask;

/**
 * @ingroup  CppConstant
 *
 * @brief   ����������������͵� #StatusKind �ļ��ϡ�
 */
DCPSDLL extern const StatusKindMask STATUS_MASK_ALL;
/**
 * @ingroup  CppConstant
 *
 * @brief   ����������յ� #StatusKind �ļ��ϡ�
 */
DCPSDLL extern const StatusKindMask STATUS_MASK_NONE;

/**
 * @typedef DDS_SampleStateKind SampleStateKind 
 *
 * @ingroup CppCoreStruct
 *
 * @brief ӳ��������� #DDS_SampleStateKind �ṹΪC++�ӿڡ�
 */
typedef DDS_SampleStateKind SampleStateKind;

/**
 * @typedef DDS_SampleStateMask SampleStateMask 
 *
 * @ingroup CppCoreStruct
 *
 * @brief ӳ��������� #DDS_SampleStateMask �ṹΪC++�ӿڡ�
 */
typedef DDS_SampleStateMask SampleStateMask;

/**
 * @ingroup  CppConstant
 *
 * @brief   �������ʾ���������״̬��
 */
DCPSDLL extern const SampleStateMask ANY_SAMPLE_STATE;
/**
 * @brief  �����������Ѿ����û����ʹ���
 *
 * @ingroup CppConstant
 *
 * @details ��ʾ�û���ͨ�� DataReader::read ϵ�з������ʹ������������Ѿ�ͨ�� DataReader::return_loan �����黹��
 */
DCPSDLL extern const SampleStateMask READ_SAMPLE_STATE;
/**
 * @brief  �����������Ѿ����û����ʹ���
 *
 * @ingroup CppConstant
 *
 * @details ��ʾ�û�δ��ͨ�� DataReader::read ϵ�з������ʹ����������߻�δͨ�� DataReader::return_loan �����黹�ռ䡣
 */
DCPSDLL extern const SampleStateMask NOT_READ_SAMPLE_STATE;

/**
 * @typedef DDS_ViewStateKind ViewStateKind 
 *
 * @ingroup CppCoreStruct
 *
 * @brief ӳ��������� #DDS_ViewStateKind �ṹΪC++�ӿڡ�
 */
typedef DDS_ViewStateKind ViewStateKind;

/**
 * @typedef DDS_ViewStateMask ViewStateMask 
 *
 * @ingroup CppCoreStruct
 *
 * @brief ӳ��������� #DDS_ViewStateMask �ṹΪC++�ӿڡ�
 */
typedef DDS_ViewStateMask ViewStateMask;

/**
 * @ingroup CppConstant
 *
 * @brief   ����������������͵� #ViewStateKind �ļ��ϡ�
 */
DCPSDLL extern const ViewStateMask ANY_VIEW_STATE;
/**
 * @brief   ��״̬��ʾ���ݶ�����δ���ʹ�������ʵ���µ������������������ʵ�����������֣���NOT_ALIVE״̬���±�ΪALIVE״̬����
 *
 * @ingroup CppConstant
 */
DCPSDLL extern const ViewStateMask NEW_VIEW_STATE;
/**
 * @brief   ��״̬��ʾ���ݶ��߷��ʹ���ʵ�������ݣ��Ҵ�ʵ��δ�������֣��� 
 *
 * @ingroup CppConstant
 */
DCPSDLL extern const ViewStateMask NOT_NEW_VIEW_STATE;

#ifdef _ZRDDS_INCLUDE_QUALITY_EVALUATION

/**
 * @typedef DDS_LinkQualityEvaluationInfo LinkQualityEvaluationInfo 
 *
 * @ingroup CppCoreStruct
 *
 * @brief ӳ��������� #DDS_LinkQualityEvaluationInfo �ṹΪC++�ӿڡ�
 */
typedef DDS_LinkQualityEvaluationInfo LinkQualityEvaluationInfo;


/**
 * @typedef DDS_QualityEvaluationQosPolicy QualityEvaluationQosPolicy 
 *
 * @ingroup CppCoreStruct
 *
 * @brief ӳ��������� #DDS_QualityEvaluationQosPolicy �ṹΪC++�ӿڡ�
 */
typedef DDS_QualityEvaluationQosPolicy QualityEvaluationQosPolicy;

#endif // _ZRDDS_INCLUDE_QUALITY_EVALUATION

/**
 * ��������Ϊ����601����ʹ�á�
 */
#ifdef _ZRDDS_INCLUDE_601_TYPE

/**
 * @typedef DDS_UINT8 UINT8
 *
 * @ingroup  CppCoreStruct
 *
 * @brief   ӳ��������� #DDS_UINT8 �ṹΪC++�ӿڡ�
 */

typedef DDS_UINT8 UINT8;

/**
 * @typedef DDS_INT8 INT8
 *
 * @ingroup  CppCoreStruct
 *
 * @brief   ӳ��������� #DDS_INT8 �ṹΪC++�ӿڡ�
 */

typedef DDS_INT8 INT8;

/**
 * @typedef DDS_BOOLEAN BOOLEAN
 *
 * @ingroup  CppCoreStruct
 *
 * @brief   ӳ��������� #DDS_BOOLEAN �ṹΪC++�ӿڡ�
 */

typedef DDS_BOOLEAN BOOLEAN;

/**
 * @typedef DDS_INT16 INT16
 *
 * @ingroup  CppCoreStruct
 *
 * @brief   ӳ��������� #DDS_INT16 �ṹΪC++�ӿڡ�
 */

typedef DDS_INT16 INT16;

/**
 * @typedef DDS_UINT16 UINT16
 *
 * @ingroup  CppCoreStruct
 *
 * @brief   ӳ��������� #DDS_UINT16 �ṹΪC++�ӿڡ�
 */

typedef DDS_UINT16 UINT16;

/**
 * @typedef DDS_INT32 INT32
 *
 * @ingroup  CppCoreStruct
 *
 * @brief   ӳ��������� #DDS_INT32 �ṹΪC++�ӿڡ�
 */

typedef DDS_INT32 INT32;

/**
 * @typedef DDS_UINT32 UINT32
 *
 * @ingroup  CppCoreStruct
 *
 * @brief   ӳ��������� #DDS_UINT32 �ṹΪC++�ӿڡ�
 */

typedef DDS_UINT32 UINT32;

/**
 * @typedef DDS_FLOAT32 FLOAT32
 *
 * @ingroup  CppCoreStruct
 *
 * @brief   ӳ��������� #DDS_FLOAT32 �ṹΪC++�ӿڡ�
 */

typedef DDS_FLOAT32 FLOAT32;

/**
 * @typedef DDS_INT64 INT64
 *
 * @ingroup  CppCoreStruct
 *
 * @brief   ӳ��������� #DDS_INT64 �ṹΪC++�ӿڡ�
 */

typedef DDS_INT64 INT64;

/**
 * @typedef DDS_UINT64 UINT64
 *
 * @ingroup  CppCoreStruct
 *
 * @brief   ӳ��������� #DDS_UINT64 �ṹΪC++�ӿڡ�
 */

typedef DDS_UINT64 UINT64;

/**
 * @typedef DDS_DOUBLE64 DOUBLE64
 *
 * @ingroup  CppCoreStruct
 *
 * @brief   ӳ��������� #DDS_DOUBLE64 �ṹΪC++�ӿڡ�
 */

typedef DDS_DOUBLE64 DOUBLE64;

/**
 * @typedef DDS_UINT8Seq UINT8Seq
 *
 * @ingroup  CppCoreStruct
 *
 * @brief   ӳ��������� #DDS_UINT8Seq �ṹΪC++�ӿڡ�
 */

typedef DDS_UINT8Seq UINT8Seq;

/**
 * @typedef DDS_INT8Seq INT8Seq
 *
 * @ingroup  CppCoreStruct
 *
 * @brief   ӳ��������� #DDS_INT8Seq �ṹΪC++�ӿڡ�
 */

typedef DDS_INT8Seq INT8Seq;

/**
 * @typedef DDS_BOOLEANSeq BOOLEANSeq
 *
 * @ingroup  CppCoreStruct
 *
 * @brief   ӳ��������� #DDS_BOOLEANSeq �ṹΪC++�ӿڡ�
 */

typedef DDS_BOOLEANSeq BOOLEANSeq;

/**
 * @typedef DDS_INT16Seq INT16Seq
 *
 * @ingroup  CppCoreStruct
 *
 * @brief   ӳ��������� #DDS_INT16Seq �ṹΪC++�ӿڡ�
 */

typedef DDS_INT16Seq INT16Seq;

/**
 * @typedef DDS_UINT16Seq UINT16Seq
 *
 * @ingroup  CppCoreStruct
 *
 * @brief   ӳ��������� #DDS_UINT16Seq �ṹΪC++�ӿڡ�
 */

typedef DDS_UINT16Seq UINT16Seq;

/**
 * @typedef DDS_INT32Seq INT32Seq
 *
 * @ingroup  CppCoreStruct
 *
 * @brief   ӳ��������� #DDS_INT32Seq �ṹΪC++�ӿڡ�
 */

typedef DDS_INT32Seq INT32Seq;

/**
 * @typedef DDS_UINT32Seq UINT32Seq
 *
 * @ingroup  CppCoreStruct
 *
 * @brief   ӳ��������� #DDS_UINT32Seq �ṹΪC++�ӿڡ�
 */

typedef DDS_UINT32Seq UINT32Seq;

/**
 * @typedef DDS_FLOAT32Seq FLOAT32Seq
 *
 * @ingroup  CppCoreStruct
 *
 * @brief   ӳ��������� #DDS_FLOAT32Seq �ṹΪC++�ӿڡ�
 */

typedef DDS_FLOAT32Seq FLOAT32Seq;

/**
 * @typedef DDS_INT64Seq INT64Seq
 *
 * @ingroup  CppCoreStruct
 *
 * @brief   ӳ��������� #DDS_INT64Seq �ṹΪC++�ӿڡ�
 */

typedef DDS_INT64Seq INT64Seq;

/**
 * @typedef DDS_UINT64Seq UINT64Seq
 *
 * @ingroup  CppCoreStruct
 *
 * @brief   ӳ��������� #DDS_UINT64Seq �ṹΪC++�ӿڡ�
 */

typedef DDS_UINT64Seq UINT64Seq;

/**
 * @typedef DDS_DOUBLE64Seq DOUBLE64Seq
 *
 * @ingroup  CppCoreStruct
 *
 * @brief   ӳ��������� #DDS_DOUBLE64Seq �ṹΪC++�ӿڡ�
 */

typedef DDS_DOUBLE64Seq DOUBLE64Seq;

#define DDS_BEST_EFFORT DDS_BEST_EFFORT_RELIABILITY_QOS
#define DDS_RELIABLE DDS_RELIABLE_RELIABILITY_QOS
#define DDS_BY_RECEPTION_TIMESTAMP DDS_BY_RECEPTION_TIMESTAMP_DESTINATIONORDER_QOS
#define DDS_BY_SOURCE_TIMESTAMP DDS_BY_SOURCE_TIMESTAMP_DESTINATIONORDER_QOS
#define DDS_TRANSIENT_LOCAL DDS_TRANSIENT_LOCAL_DURABILITY_QOS
#define DDS_VOLATILE DDS_VOLATILE_DURABILITY_QOS
#define DDS_KEEP_LAST DDS_KEEP_LAST_HISTORY_QOS
#define DDS_KEEP_ALL DDS_KEEP_ALL_HISTORY_QOS
#define DDS_SHARED DDS_SHARED_OWNERSHIP_QOS
#define DDS_EXCLUSIVE DDS_EXCLUSIVE_OWNERSHIP_QOS
#define DDS_RETCODE_INCONSISTENT_POLICY DDS_RETCODE_INCONSISTENT

#define DDS_DEFAULT_PARTICIPANT_QOS DDS_DOMAINPARTICIPANT_QOS_DEFAULT
#define DDS_DEFAULT_TOPIC_QOS DDS_TOPIC_QOS_DEFAULT
#define DDS_DEFAULT_PUBLISHER_QOS DDS_PUBLISHER_QOS_DEFAULT
#define DDS_DEFAULT_SUBSCRIBER_QOS DDS_SUBSCRIBER_QOS_DEFAULT
#define DDS_DEFAULT_DATAWRITER_QOS DDS_DATAWRITER_QOS_DEFAULT
#define DDS_DEFAULT_DATAREADER_QOS DDS_DATAREADER_QOS_DEFAULT

#define DDS_INCONSISTENT_TOPIC DDS_INCONSISTENT_TOPIC_STATUS
#define DDS_DATA_ON_READERS DDS_DATA_ON_READERS_STATUS
#define DDS_DATA_AVAILABLE DDS_DATA_AVAILABLE_STATUS
#define DDS_SAMPLE_REJECTED DDS_SAMPLE_REJECTED_STATUS
#define DDS_SAMPLE_LOST DDS_SAMPLE_LOST_STATUS
#define DDS_LIVELINESS_CHANGED DDS_LIVELINESS_CHANGED_STATUS
#define DDS_LIVELINESS_LOST DDS_LIVELINESS_LOST_STATUS
#define DDS_REQUESTED_DEADLINE_MISSED DDS_REQUESTED_DEADLINE_MISSED_STATUS 
#define DDS_REQUESTED_INCOMPATIBLE_QOS DDS_REQUESTED_INCOMPATIBLE_QOS_STATUS
#define DDS_PUBLICATION_MATCHED DDS_PUBLICATION_MATCHED_STATUS
#define DDS_SUBSCRIPTION_MATCHED DDS_SUBSCRIPTION_MATCHED_STATUS
#define DDS_OFFERED_DEADLINE_MISSED DDS_OFFERED_DEADLINE_MISSED_STATUS
#define DDS_OFFERED_INCOMPATIBLE_QOS DDS_OFFERED_INCOMPATIBLE_QOS_STATUS

#define BEST_EFFORT BEST_EFFORT_RELIABILITY_QOS
#define RELIABLE RELIABLE_RELIABILITY_QOS
#define BY_RECEPTION_TIMESTAMP BY_RECEPTION_TIMESTAMP_DESTINATIONORDER_QOS
#define BY_SOURCE_TIMESTAMP BY_SOURCE_TIMESTAMP_DESTINATIONORDER_QOS
#define TRANSIENT_LOCAL TRANSIENT_LOCAL_DURABILITY_QOS
#define VOLATILE VOLATILE_DURABILITY_QOS
#define KEEP_LAST KEEP_LAST_HISTORY_QOS
#define KEEP_ALL KEEP_ALL_HISTORY_QOS
#define SHARED SHARED_OWNERSHIP_QOS
#define EXCLUSIVE EXCLUSIVE_OWNERSHIP_QOS
#define RETCODE_INCONSISTENT_POLICY RETCODE_INCONSISTENT

#define DEFAULT_PARTICIPANT_QOS DOMAINPARTICIPANT_QOS_DEFAULT
#define DEFAULT_TOPIC_QOS TOPIC_QOS_DEFAULT
#define DEFAULT_PUBLISHER_QOS PUBLISHER_QOS_DEFAULT
#define DEFAULT_SUBSCRIBER_QOS SUBSCRIBER_QOS_DEFAULT
#define DEFAULT_DATAWRITER_QOS DATAWRITER_QOS_DEFAULT
#define DEFAULT_DATAREADER_QOS DATAREADER_QOS_DEFAULT

#define INCONSISTENT_TOPIC INCONSISTENT_TOPIC_STATUS
#define DATA_ON_READERS DATA_ON_READERS_STATUS
#define DATA_AVAILABLE DATA_AVAILABLE_STATUS
#define SAMPLE_REJECTED SAMPLE_REJECTED_STATUS
#define SAMPLE_LOST SAMPLE_LOST_STATUS
#define LIVELINESS_CHANGED LIVELINESS_CHANGED_STATUS
#define LIVELINESS_LOST LIVELINESS_LOST_STATUS
#define REQUESTED_DEADLINE_MISSED REQUESTED_DEADLINE_MISSED_STATUS 
#define REQUESTED_INCOMPATIBLE_QOS REQUESTED_INCOMPATIBLE_QOS_STATUS
#define PUBLICATION_MATCHED PUBLICATION_MATCHED_STATUS
#define SUBSCRIPTION_MATCHED SUBSCRIPTION_MATCHED_STATUS
#define OFFERED_DEADLINE_MISSED OFFERED_DEADLINE_MISSED_STATUS
#define OFFERED_INCOMPATIBLE_QOS OFFERED_INCOMPATIBLE_QOS_STATUS

#endif //_ZRDDS_INCLUDE_601_TYPE
}

#endif // ZRDDSCppWrapper_h__
