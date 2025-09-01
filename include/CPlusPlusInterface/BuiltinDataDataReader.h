/**
 * @file:       BuiltinDataDataReader.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#ifndef BuiltinDataDataReader_h__
#define BuiltinDataDataReader_h__

#include "ZRDDSDataReader.h"
#include "ZRDDSCppWrapper.h"

namespace DDS {

/**
 * @struct DDS::ParticipantBuiltinTopicDataSeq
 *
 * @ingroup CppDiscoveryTypes
 *
 * @brief   ���������������� DDS::ParticipantBuiltinTopicData �����С�
 */
typedef struct DDS_ParticipantBuiltinTopicDataSeq ParticipantBuiltinTopicDataSeq;

/**  
 * @class DDS::ParticipantBuiltinTopicDataDataReader
 *
 * @ingroup CppDiscoveryTypes
 *
 * @brief ���������������� DDS::ParticipantBuiltinTopicData ���������ݶ���
 *  
 * @details ���ڴ�ZRDDS�л�ȡ������������������ݼ���״̬�������� DDS::ZRDDSDataReader ��ģ��ʵ������ģ�����Ϊ�� 
 *          DDS::ParticipantBuiltinTopicData DDS::ParticipantBuiltinTopicDataSeq ���÷��μ� 
 *          DDS::DomainParticipant::get_builtin_subscriber ��
 */
typedef DCPSDLL ZRDDSDataReader<ParticipantBuiltinTopicData, ParticipantBuiltinTopicDataSeq> ParticipantBuiltinTopicDataDataReader;

/**
 * @struct DDS::PublicationBuiltinTopicDataSeq
 *
 * @ingroup CppDiscoveryTypes
 *
 * @brief   ���������������� DDS::PublicationBuiltinTopicData �����С�
 */
typedef struct DDS_PublicationBuiltinTopicDataSeq PublicationBuiltinTopicDataSeq;

/**  
 * @class DDS::PublicationBuiltinTopicDataDataReader
 *
 * @ingroup CppDiscoveryTypes
 *
 * @brief ���������������� DDS::PublicationBuiltinTopicData ���������ݶ���
 *  
 * @details ���ڴ�ZRDDS�л�ȡ���÷������������ݣ������� DDS::ZRDDSDataReader ��ģ��ʵ������ģ�����Ϊ��
 *          DDS::PublicationBuiltinTopicData DDS::PublicationBuiltinTopicDataSeq ���÷��μ�
 *          DDS::DomainParticipant::get_builtin_subscriber ��
 */
typedef DCPSDLL ZRDDSDataReader<PublicationBuiltinTopicData, PublicationBuiltinTopicDataSeq> PublicationBuiltinTopicDataDataReader;

/**
 * @struct DDS::SubscriptionBuiltinTopicDataSeq
 *
 * @ingroup CppDiscoveryTypes
 *
 * @brief   ���������������� DDS::SubscriptionBuiltinTopicData �����С�
 */
typedef struct DDS_SubscriptionBuiltinTopicDataSeq SubscriptionBuiltinTopicDataSeq;

/**  
 * @class DDS::SubscriptionBuiltinTopicDataDataReader
 *
 * @ingroup CppDiscoveryTypes
 *
 * @brief ���������������� DDS::SubscriptionBuiltinTopicData ���������ݶ���
 *  
 * @details ���ڴ�ZRDDS�л�ȡ���ö��Ķ��������ݣ������� DDS::ZRDDSDataReader ��ģ��ʵ������ģ�����Ϊ��
 *          DDS::SubscriptionBuiltinTopicData DDS::SubscriptionBuiltinTopicDataSeq ���÷��μ�
 *          DDS::DomainParticipant::get_builtin_subscriber ��
 */
typedef DCPSDLL ZRDDSDataReader<SubscriptionBuiltinTopicData, SubscriptionBuiltinTopicDataSeq> SubscriptionBuiltinTopicDataDataReader;

#ifdef _ZRDDS_INCLUDE_TOPIC_BUILTIN_TOPIC_DATA

/**
 * @struct DDS::TopicBuiltinTopicDataSeq
 *
 * @ingroup CppDiscoveryTypes
 *
 * @brief   ���������������� DDS::TopicBuiltinTopicDataSeq �����С�
 */
typedef struct DDS_TopicBuiltinTopicDataSeq TopicBuiltinTopicDataSeq;

/**  
 * @class DDS::TopicBuiltinTopicDataDataReader
 *
 * @ingroup CppDiscoveryTypes
 *
 * @brief ���������������� DDS::TopicBuiltinTopicData ���������ݶ���
 *  
 * @details ���ڴ�ZRDDS�л�ȡ���ö��Ķ��������ݣ������� DDS::ZRDDSDataReader ��ģ��ʵ������ģ�����Ϊ��
 *          DDS::TopicBuiltinTopicData DDS::TopicBuiltinTopicDataSeq ���÷��μ�
 *          DDS::DomainParticipant::get_builtin_subscriber ��
 */
typedef DCPSDLL ZRDDSDataReader<TopicBuiltinTopicData, TopicBuiltinTopicDataSeq> TopicBuiltinTopicDataDataReader;

#endif // _ZRDDS_INCLUDE_TOPIC_BUILTIN_TOPIC_DATA

#if defined(_ZRDDSSECURITY)
/**
* @struct DDS::PublicationBuiltinTopicDataSecureSeq
*
* @ingroup CppDiscoveryTypes
*
* @brief   ���������������� DDS::PublicationBuiltinTopicDataSecure �����С�
*/

/**
* @class DDS::PublicationBuiltinTopicDataSecureDataReader
*
* @ingroup CppDiscoveryTypes
*
* @brief ���������������� DDS::PublicationBuiltinTopicDataSecure ���������ݶ���
*
* @details ���ڴ�ZRDDS�л�ȡ���÷������������ݣ������� DDS::ZRDDSDataReader ��ģ��ʵ������ģ�����Ϊ��
*          DDS::PublicationBuiltinTopicDataSecure DDS::PublicationBuiltinTopicDataSecureSeq ���÷��μ�
*          DDS::DomainParticipant::get_builtin_subscriber ��
*/

typedef struct DDS_PublicationBuiltinTopicDataSeq PublicationBuiltinTopicDataSecureSeq;
typedef DCPSDLL ZRDDSDataReader<PublicationBuiltinTopicDataSecure, PublicationBuiltinTopicDataSecureSeq>
    PublicationBuiltinTopicDataSecureDataReader;

/**
* @struct DDS::SubscriptionBuiltinTopicDataSecureSeq
*
* @ingroup CppDiscoveryTypes
*
* @brief   ���������������� DDS::SubscriptionBuiltinTopicDataSecure �����С�
*/

/**
* @class DDS::SubscriptionBuiltinTopicDataSecureDataReader
*
* @ingroup CppDiscoveryTypes
*
* @brief ���������������� DDS::SubscriptionBuiltinTopicDataSecure ���������ݶ���
*
* @details ���ڴ�ZRDDS�л�ȡ���ö��Ķ��������ݣ������� DDS::ZRDDSDataReader ��ģ��ʵ������ģ�����Ϊ��
*          DDS::SubscriptionBuiltinTopicDataSecure DDS::SubscriptionBuiltinTopicDataSecureSeq ���÷��μ�
*          DDS::DomainParticipant::get_builtin_subscriber ��
*/

typedef struct DDS_SubscriptionBuiltinTopicDataSeq SubscriptionBuiltinTopicDataSecureSeq;
typedef DCPSDLL ZRDDSDataReader<SubscriptionBuiltinTopicDataSecure, SubscriptionBuiltinTopicDataSecureSeq>
    SubscriptionBuiltinTopicDataSecureDataReader;

#endif // _ZRDDSSECURITY

} // namespace DDS

#endif // BuiltinDataDataReader_h__
