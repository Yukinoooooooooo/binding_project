/**
 * @file:       LivelinessQosPolicy.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#ifndef LivelinessQosPolicy_h__
#define LivelinessQosPolicy_h__

#include "OsResource.h"
#include "Duration_t.h"

#ifdef _ZRDDS_INCLUDE_LIVELINESS_QOS

/**
 * @enum DDS_LivelinessQosPolicyKind
 *
 * @ingroup CoreQosStruct
 *
 * @brief   ָ������д����������Ե����͡�
 */

typedef enum DDS_LivelinessQosPolicyKind
{
    /**
     * @brief   ��ZRDDS�ײ��Զ���������������
     *
     * @ingroup CoreQosStruct
     *
     * @details Ĭ��Ϊ�����ͣ�ZRDDS�ڲ������Զ�����������������д�ߣ�ZRDDS�������� DDS_LivelinessQosPolicy::lease_duration 
     *          ��Ƶ���������������������������д�ߵĴ���ԣ�������������Ҳ�����ȷ����������д�ߴ���Եķ�����
     */
    DDS_AUTOMATIC_LIVELINESS_QOS,

    /**
     * @brief   ͨ����������ֶ���������������
     *
     * @ingroup CoreQosStruct
     *
     * @details ��������д�����ø����ͣ���ZRDDS�����û������� DDS_LivelinessQosPolicy::lease_duration 
     *          ������������ͬһ���������������һ������д�ߵĴ���Ի������������Ĵ���ԣ��������д��Ҳ�Ǵ��ġ�
     *          �����������û�����ͨ������ͬһ���������������һ������д�߻������������Ĵ������������������д�ߵĴ���Ե�������
     */
    DDS_MANUAL_BY_PARTICIPANT_LIVELINESS_QOS,

    /**
     * @brief   ������д���ֶ���������������
     *
     * @ingroup CoreQosStruct
     *
     * @details ֻ���û�������ȷ�ĵ�������д����������ԵĲ�����������д�߲Żᱻ��Ϊ�Ǵ��ġ�������ǿ���û���������
     *          ����д�ߵĴ���ԣ��������û�������õؿ��ƺ�ʱ�����������Ϊ����д�߱�Ϊ����Ծ�ģ����ǻ��úܲ����㡣
     */
    DDS_MANUAL_BY_TOPIC_LIVELINESS_QOS
}DDS_LivelinessQosPolicyKind;

/**
 * @struct DDS_LivelinessQosPolicy
 *
 * @ingroup CoreQosStruct
 *
 * @brief   ����д�ߴ�����������ж����á�
 *          
 * @details ��QoS�������ݶ����ж�����д���Ƿ����QoS��������Ȩ���� DDS_OwnershipQosPolicy ������ϵͳ�ȱ���
 *          - �ֶ���������д�ߴ���Եķ�����
 *              - ���� DataWriter::write ϵ�з��� DataWriter::unregister_instance ϵ�з���   
 *                  DataWriter::dispose ϵ�з�����
 *              - ���� DataWrite::assert_liveliness ������
 *          - �ֶ�����������ߴ���Եķ�����
 *              - ���� DomainParticipant::assert_liveliness ������  
 *          
 *          ��QoS��ʵ��״̬ DDS_LivelinessChangedStatus �Լ� DDS_LivelinessLostStatus ������
 *          ��Ա | Ĭ��ֵ | ƥ������� | ��Ч�Լ�� | �����Լ�� | �ɱ��Լ��
 *          --- | --- | --- | --- | --- | ---
 *          #kind | #DDS_AUTOMATIC_LIVELINESS_QOS | ����д��.#kind>=���ݶ��ߵ�.#kind  | �� | �� | ���ɱ�
 *          #lease_duration | #INFINITE_DURATION | ����д��.#lease_duration <= ���ݶ���.#lease_duration | #lease_duration > #ZERO_DURATION | �� | ���ɱ� 
 */

typedef struct DDS_LivelinessQosPolicy 
{
    /** @brief   ָ������д����������Ե����͡� */
    DDS_LivelinessQosPolicyKind kind;
    /**  
     * @brief   ʧ��ʱ�䡣 
     *
     * @details ��������д���Լ����ݶ��ߵĺ��岻ͬ��
     *          - ��������д����˵��ʱ���ʾ������ʱ���δ�������ͱ���Ϊ�ǻ���߲���
     *          - �������ݶ��ߣ���ʱ���������ʱ���ȥ���ƥ�������д�ߵĴ���ԡ�
     */
    DDS_Duration_t lease_duration;
}DDS_LivelinessQosPolicy;

#endif /* _ZRDDS_INCLUDE_LIVELINESS_QOS */

#endif /* LivelinessQosPolicy_h__*/
