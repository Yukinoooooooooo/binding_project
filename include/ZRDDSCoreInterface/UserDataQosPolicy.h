/**
 * @file:       UserDataQosPolicy.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#ifndef UserDataQosPolicy_h__
#define UserDataQosPolicy_h__

#include "OsResource.h"
#include "ZRBuiltinTypes.h"

#ifdef _ZRDDS_INCLUDE_USER_DATA_QOS

/**
 * @struct DDS_UserDataQosPolicy
 *
 * @ingroup CoreQosStruct
 *
 * @brief   ʵ��Я�����ݡ�
 *
 * @details ��QoSΪӦ���ṩ��һ���ܹ��洢������������ϡ�����д�߻����ݶ�����Ϣ�Ŀռ䡣
 *          �����Ϣ�ڷ��ֽ׶���Ӧ�ü�ʹ�����õ����⴫�ݡ����ʹ�������Ϣ���û������� 
 *          ZRDDS���˴洢�ͽ��䷢�͵�����Ӧ���ⲻ�����κβ�����һ������Ӧ�ü��ʶ�𡢼�������Ȩ�ͼ��ܡ� 
 *          ���û���������ʵ��ʱ����QoS��ֵ���ᱻ��䵽����������ߡ�����д���Լ����ݶ��ߵ����������У�
 *          ��ͨ�����÷���Э�鷢����DDS������ DDS_ParticipantBuiltinTopicData::user_data 
 *          DDS_SubscriptionBuiltinTopicData::user_data �Լ� DDS_PublicationBuiltinTopicData::user_data ��
 *          ��Ա | Ĭ��ֵ | ƥ������� | ��Ч�Լ�� | �����Լ�� | �ɱ��Լ��
 *          --- | --- | --- | --- | --- | ---
 *          #value | ����Ϊ0���ֽ����� | �� | �� | �� | �ɱ�
 *
 * @see DDS_TopicDataQosPolicy DDS_GroupDataQosPolicy ��
 */

typedef struct DDS_UserDataQosPolicy
{
    /** @brief   �ֽ����б�ʾ�û���ҪЯ�������ݡ� */
    DDS_CharSeq value;
}DDS_UserDataQosPolicy;

#endif /* _ZRDDS_INCLUDE_USER_DATA_QOS */

#endif /* UserDataQosPolicy_h__*/
