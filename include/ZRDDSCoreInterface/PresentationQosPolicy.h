/**
 * @file:       PresentationQosPolicy.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#ifndef PresentationQosPolicy_h__
#define PresentationQosPolicy_h__

#include "OsResource.h"

#ifdef _ZRDDS_INCLUDE_PRESENTATION_QOS

/**
 * @enum DDS_PresentationQosPolicyAccessScopeKind
 *
 * @ingroup CoreQosStruct
 *
 * @brief   ��������չ�ֿ��������͡�
 */

typedef enum DDS_PresentationQosPolicyAccessScopeKind
{
    /** @brief  ��ΧΪ����ʵ�������庬��μ� DDS_PresentationQosPolicy @ingroup CoreQosStruct */
    DDS_INSTANCE_PRESENTATION_QOS,
    /** @brief  ��ΧΪ���⣬���庬��μ� DDS_PresentationQosPolicy @ingroup CoreQosStruct */
    DDS_TOPIC_PRESENTATION_QOS,
    /** @brief  ��ΧΪ�飬���庬��μ� DDS_PresentationQosPolicy @ingroup CoreQosStruct */
    DDS_GROUP_PRESENTATION_QOS
}DDS_PresentationQosPolicyAccessScopeKind;

/**
 * @struct DDS_PresentationQosPolicy
 *
 * @ingroup CoreQosStruct
 *
 * @brief   ����չʾ���á�
 *
 * @details ��QoS����ZRDDS���ֽ��յ������ݸ����ݶ��ߵķ�ʽ������ #coherent_access ����һ���Է��ʣ�
 *          #ordered_access ���ư�����ʣ������������ָ��û���˳��
 *          ��һ���Լ��ϡ�������ָ���뱻һ���ύ�û��������������ϣ�ֻ���ڼ��������е������������洢�����ݶ��ߺ�
 *          �û�����ͨ�� DataReader::read/take �����������ݣ������������е����ݾ���ͨ���ӿڷ��ظ��û���
 *          ���� #coherent_access = true ֻ�������ݶ��ߺ�����д������Ϊ�ɿ�ͨ��ʱ����Ч��
 *          ���ͳ���ʹ�� Publisher::begin_coherent_changes() �Լ� Publisher::end_coherent_changes()
 *          ����һ��������������������ʱ #access_scope ���ƴ����һ���Լ��ϵ����������ķ�Χ��������
 *          - #DDS_INSTANCE_PRESENTATION_QOS ������ֻ��ͬһ������д���Լ�����һ������ʵ���������ܹ������һ��һ���Լ����У�
 *          - #DDS_TOPIC_PRESENTATION_QOS ������ͬһ������д�ߵ����ݿ��Դ����һ��һ���Լ����У�
 *          
 *          ���������ָ�û�ͨ�� DataReader::read/take ����������������ʱ��ZRDDS���ؽ��ʱ������������˳��
 *          - #DDS_INSTANCE_PRESENTATION_QOS ���������ص�˳��Ϊ������ʵ����˳��
 *          - #DDS_TOPIC_PRESENTATION_QOS ���������ص�˳��Ϊ���������˳��  
 *          ���磺DW1�ֱ�������ʵ��1�Լ�����ʵ��2�µ�����������˳��Ϊ data(1,1)��data(2,1)��data(1,2)��data(2,2)��
 *          ���������ڵ�һ�����ֱ�ʾ����ʵ���ı�ʶ���ڶ������ֱ�ʾ������ʵ���µ�������ţ������ݶ��߶˵��� DataReader::read/take
 *          �Ľ�����£�
 *          - #DDS_INSTANCE_PRESENTATION_QOS ��data(1,1)��data(1,2)��data(2,1)��data(2,2)
 *          - #DDS_TOPIC_PRESENTATION_QOS ��data(1,1)��data(2,1)��data(1,2)��data(2,2)
 *          ��Ա | Ĭ��ֵ | ƥ������� | ��Ч�Լ�� | �����Լ�� | �ɱ��Լ��
 *          --- | --- | --- | --- | --- | ---
 *          #access_scope | DDS_INSTANCE_PRESENTATION_QOS | ������.#access_scope >= ���Ķ�.#access_scope | �� | �� | ���ɱ� 
 *          #coherent_access | false | ������.#coherent_access >= ���Ķ�.#coherent_access (true > false) | �� | �� | ���ɱ� 
 *          #ordered_access | false | ������.#ordered_access >= ���Ķ�.#ordered_access (true > false) | �� | �� | ���ɱ� 
 *
 * @warning ������Ϊ #DDS_GROUP_PRESENTATION_QOS ���͵�һ���Է����Լ�������ʾ���δʵ�֡�
 */

typedef struct DDS_PresentationQosPolicy
{
    /** @brief  ���Ʒ��ʵķ�Χ��#coherent_access �Լ� #ordered_access ���岻ͬ�� */
    DDS_PresentationQosPolicyAccessScopeKind access_scope;
    /** @brief ����һ���Է��ʡ� */
    DDS_Boolean coherent_access;
    /** @brief ����������ʡ� */
    DDS_Boolean ordered_access;
}DDS_PresentationQosPolicy;

#endif /* _ZRDDS_INCLUDE_PRESENTATION_QOS */

#endif /* PresentationQosPolicy_h__*/
