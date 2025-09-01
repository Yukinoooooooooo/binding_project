/**
 * @file:       TopicDataQosPolicy.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#ifndef TopicDataQosPolicy_h__
#define TopicDataQosPolicy_h__

#include "OsResource.h"
#include "ZRBuiltinTypes.h"

#ifdef _ZRDDS_INCLUDE_TOPIC_DATA_QOS

/**
 * @struct DDS_TopicDataQosPolicy
 *
 * @ingroup CoreQosStruct
 *
 * @brief   ����Я���������á�
 *          
 * @details ��QoS����������ʵ���ϣ����û��������ݶ��߻�������д��ʱ����QoS��ֵ���ᱻ��䵽��������д���Լ����ݶ��ߵ����������У�
 *          ��ͨ�����÷���Э�鷢����DDS������ DDS_SubscriptionBuiltinTopicData::topic_data �Լ�
 *          DDS_PublicationBuiltinTopicData::topic_data ��
 *          ��Ա | Ĭ��ֵ | ƥ������� | ��Ч�Լ�� | �����Լ�� | �ɱ��Լ��
 *          --- | --- | --- | --- | --- | ---
 *          #value | ����Ϊ0���ֽ����� | �� | �� | �� | �ɱ�
 *
 * @see DDS_UserDataQosPolicy DDS_GroupDataQosPolicy ��
 */

typedef struct DDS_TopicDataQosPolicy
{
    /** @brief   �ֽ����б�ʾ�û���ҪЯ�������ݡ� */
    DDS_CharSeq value;
}DDS_TopicDataQosPolicy;

#endif /* _ZRDDS_INCLUDE_TOPIC_DATA_QOS */

#endif /* TopicDataQosPolicy_h__*/
