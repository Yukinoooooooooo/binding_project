/**
 * @file:       DestinationOrderQosPolicy.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#ifndef DestinationOrderQosPolicy_h__
#define DestinationOrderQosPolicy_h__

#include "OsResource.h"

#ifdef _ZRDDS_INCLUDE_DESTINATION_ORDER_QOS

/**
 * @enum DDS_DestinationOrderQosPolicyKind
 *
 * @ingroup CoreQosStruct
 *
 * @brief   ��ʶ����˳�����͡�
 */

typedef enum DDS_DestinationOrderQosPolicyKind
{
    /**  
     * @brief   �����ݶ��߽��յ���˳��洢�����ݶ��ߵ��ڲ������С�
     *
     * @ingroup CoreQosStruct
     *
     * @details Ĭ�������ѡ������͡����ݻᱻ�Խ��յ���˳���ύ�����ݶ��ߣ�����ܻᵼ�²�ͬ�����ݶ����Բ�ͬ������˳��������ݡ�
     *          ����ͬһ�������µ�����д��DW1��DW2�Լ����ݶ���DR1��DR2���໥ƥ�䣬��˳��DW1(1)��DW2(1)��DW1(2)��DW2(2)�����������ݣ�
     *          �ڸ�QoS�����£�DR1��DR2���ܵĽ���˳�������
     *          - DW1(1)��DW2(1)��DW1(2)��DW2(2)  
     *          - DW1(1)��DW2(1)��DW2(2)��DW1(2)  
     *          - DW1(1)��DW1(2)��DW2(1)��DW2(2)  
     *          - DW2(1)��DW1(1)��DW1(2)��DW2(2)  
     *          - DW2(1)��DW1(1)��DW2(2)��DW1(2)  
     *          - DW2(1)��DW2(2)��DW1(1)��DW1(2)  
     */
    DDS_BY_RECEPTION_TIMESTAMP_DESTINATIONORDER_QOS, 

    /**  
     * @brief   ���������ݵ�Դʱ���˳��洢�����ݶ��ߵ��ڲ������С�
     *
     * @ingroup CoreQosStruct
     *
     * @details ������д������Ϊ������ʱ������һ�����ݵ�ʱ������벻С��ǰһ�����������ݵ�ʱ��������򷢲����ݻ�ʧ�ܡ�
     *          �����ݶ�������Ϊ������ʱ�����ݶ���ֻ����շ���ʱ�������һ���յ������ݷ���ʱ���������ݡ�
     *          �������ݻᱻ�ܾ������ǲ���Ӱ�� DDS_SAMPLE_REJECTED_STATUS ״̬��
     *          
     *          ����ͬһ�������µ�����д��DW1��DW2�Լ����ݶ���DR1��DR2���໥ƥ�䣬����DW1��DW2ʹ��ͳһ��ʱ��ϵͳ
     *          ��˳��DW1(1)��DW2(1)��DW1(2)��DW2(2)�����������ݣ�
     *          �ڸ�QoS�����£�DR1��DR2���ܵĽ���˳�������
     *          - DW1(1)��DW2(1)��DW1(2)��DW2(2)
     *          - DW1(1)��DW2(1)��DW2(2)
     *          - DW1(1)��DW1(2)��DW2(2)
     *          - DW2(1)��DW2(2)
     *          
     *          δ�յ������������ݶ��߸���ʱ����ܾ���
     */
    DDS_BY_SOURCE_TIMESTAMP_DESTINATIONORDER_QOS
}DDS_DestinationOrderQosPolicyKind;

/**
 * @struct DDS_DestinationOrderQosPolicy
 *
 * @ingroup CoreQosStruct
 *
 * @brief   ����˳�����á�
 *
 * @details ��QoS�������ݶ����ڽ������Բ�ͬ������д�߷��͵�����ʱ�Ľ���˳��
 *          ��ͬ�����µ�����д�ߣ���ͬ�����ߡ�������ߡ��ڵ㣩��ZRDDSϵͳ��������ʱ��������·֮����ٶȵ����أ�
 *          ZRDDS�޷���֤���Զ������д�ߵ���������֮��Ľ���˳�����䷢��˳��һ�¡�������д��ֹͣ��������ʱ����ͬ
 *          ���ݶ����յ������һ�����ݿ��ܻ᲻��ͬ��
 *          ��Qos�������ڴ���Ҫ����һ���Ե�ϵͳ��ͬһ�����¶�����ݶ����յ�������˳����м�״̬���ܲ�һ�£�
 *          ���ǵ�����д��ֹͣ��������ʱ���������ݶ��߽��յ������һ��״̬������ͬ��
 *          ÿ����������������ʱ�����һ������ʱ������ɷ��Ͷ��ṩ����Ĭ��Ϊ�����ڵ��ϵͳʱ�䣩
 *          ��һ������ʱ�������������ύ�����ݶ��ߴ洢��ʱ�䣩��
 *          
 *          ��Ա | Ĭ��ֵ | ƥ������� | ��Ч�Լ�� | �����Լ�� | �ɱ��Լ��
 *          --- | --- | --- | --- | --- | ---
 *          #kind | ::DDS_BY_RECEPTION_TIMESTAMP_DESTINATIONORDER_QOS | ����д��.#kind >= ���ݶ���.#kind | �� | �� | ���ɱ�
 */

typedef struct DDS_DestinationOrderQosPolicy
{
    /** @brief   ָ������˳�����͡� */
    DDS_DestinationOrderQosPolicyKind kind;
}DDS_DestinationOrderQosPolicy;

#endif /* _ZRDDS_INCLUDE_DESTINATION_ORDER_QOS */

#endif /* DestinationOrderQosPolicy_h__*/
