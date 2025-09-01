/**
 * @file:       GroupDataQosPolicy.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#ifndef GroupDataQosPolicy_h__
#define GroupDataQosPolicy_h__

#include "OsResource.h"
#include "ZRBuiltinTypes.h"

#ifdef _ZRDDS_INCLUDE_GROUP_DATA_QOS

/**
 * @struct DDS_GroupDataQosPolicy
 *
 * @ingroup CoreQosStruct
 *
 * @brief   ��Я�����ݡ�
 *
 * @details ��QoS�����ڷ������Լ�������ʵ���ϣ����û����������߻��߶�����ʱ����QoS��ֵ���ᱻ��䵽��������д���Լ����ݶ��ߵ����������У�
 *          ��ͨ�����÷���Э�鷢����DDS������ DDS_SubscriptionBuiltinTopicData::group_data �Լ� 
 *          DDS_PublicationBuiltinTopicData::group_data ��
 *          ��Ա | Ĭ��ֵ | ƥ������� | ��Ч�Լ�� | �����Լ�� | �ɱ��Լ��
 *          --- | --- | --- | --- | --- | ---
 *          #value | ����Ϊ0���ֽ����� | �� | �� | �� | �ɱ�
 *          
 * @see DDS_UserDataQosPolicy DDS_TopicDataQosPolicy ��
 */

typedef struct DDS_GroupDataQosPolicy
{
    /** @brief   �ֽ����б�ʾ�û���ҪЯ�������ݡ� */
    DDS_CharSeq value;
}DDS_GroupDataQosPolicy;

#endif /* _ZRDDS_INCLUDE_GROUP_DATA_QOS */

#endif /* GroupDataQosPolicy_h__*/
