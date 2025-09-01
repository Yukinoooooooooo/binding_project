/**
 * @file:       PublishModeQosPolicy.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#ifndef PublishModeQosPolicy_h__
#define PublishModeQosPolicy_h__

/**
 * @enum DDS_PublishModeQosPolicyKind
 *
 * @ingroup CoreQosStruct
 * 
 * @brief ��������д�ߵķ���ģʽ���͡�
 */
typedef enum DDS_PublishModeQosPolicyKind
{
    /** @brief  ͬ������ģʽ�� @ingroup CoreQosStruct */
    DDS_SYNCHRONOUS_PUBLISH_MODE_QOS,
    /** @brief  �첽����ģʽ�� @ingroup CoreQosStruct */
    DDS_ASYNCHRONOUS_PUBLISH_MODE_QOS
}DDS_PublishModeQosPolicyKind;

/**
 * @struct DDS_PublishModeQosPolicy
 *
 * @ingroup CoreQosStruct
 *
 * @brief ����д�߷���ģʽ���á�
 *
 * @details 
 *          ��Ա | Ĭ��ֵ | ƥ������� | ��Ч�Լ�� | �����Լ�� | �ɱ��Լ��
 *          --- | --- | --- | --- | --- | ---
 *          #kind | #DDS_SYNCHRONOUS_PUBLISH_MODE_QOS | �� | �� | �� | ���ɱ�
 *
 */
typedef struct DDS_PublishModeQosPolicy
{
    /** @brief ����д�ߵķ���ģʽ���͡� */
    DDS_PublishModeQosPolicyKind kind;
}DDS_PublishModeQosPolicy;

#endif /* PublishModeQosPolicy_h__*/
