/**
 * @file:       DurabilityQosPolicy.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#ifndef DurabilityQosPolicy_h__
#define DurabilityQosPolicy_h__

#include "OsResource.h"

/**
 * @enum DDS_DurabilityQosPolicyKind
 *
 * @ingroup CoreQosStruct
 *
 * @brief   ���ݳ־û����͡�
 */

typedef enum DDS_DurabilityQosPolicyKind
{
    /**
     * @brief   �޳־û���
     *
     * @ingroup CoreQosStruct
     *
     * @details ������ΪĬ�����ͣ�����д������Ϊ�����ͱ�ʾ������д�߲��洢�Ѿ�������ɣ���ǰƥ������ݶ��߶��յ���������������
     *          ���ݶ�������Ϊ�����ͱ�ʾ�����ڸ����ݶ��߼���DDS����֮ǰ������д�߷�����ɵ���ʷ���ݲ�����Ȥ��
     */
    DDS_VOLATILE_DURABILITY_QOS,

    /**
     * @brief   ��������д�����ڴ��г־û���
     *
     * @ingroup CoreQosStruct
     *
     * @details ����д������Ϊ�����ͱ�ʾ������д�߽����ڴ��д洢�Ѿ�������ɣ���ǰƥ������ݶ��߶��յ�����
     *          �洢����������Դ�������ÿ��� DDS_ResourceLimitsQosPolicy ��������д��ɾ��ʱ����Щ��ʷ����Ҳ�ᱻͬʱɾ����
     *          ���ݶ�������Ϊ�����ͱ�ʾ�����ڸ����ݶ��߼���DDS����֮ǰ�Ҵ�ʱ�Դ�������д�߷�����ɵ���ʷ���ݸ���Ȥ��
     */
    DDS_TRANSIENT_LOCAL_DURABILITY_QOS,

    /**
     * @brief   ��������д�ߣ����������ݶ��߼���DDS����ʱ�Ѿ���ɾ��������д�ߣ����ڴ��г־û���
     *
     * @ingroup CoreQosStruct
     *
     * @warning ������δʵ�֡�
     */
    DDS_TRANSIENT_DURABILITY_QOS,

    /**
     * @brief   ��������д�ߣ����������ݶ��߼���DDS����ʱ�Ѿ���ɾ��������д�ߣ��ڳ־û��洢���ļ������ݿ⣩�г־û���
     *
     * @ingroup CoreQosStruct
     *
     * @warning ������δʵ�֡�
     */
    DDS_PERSISTENT_DURABILITY_QOS
}DDS_DurabilityQosPolicyKind;

/**
 * @struct DDS_DurabilityQosPolicy
 *
 * @ingroup CoreQosStruct
 *
 * @brief   ʵ�����ݳ־û����á�
 *
 * @details ��DDSͨ��ģ���У�����д�ߺ����ݶ���֮������ӹ�ϵ������������в�����ƥ������ݶ��ߣ�
 *          ����д��Ҳ���Է������ݡ������ݶ��߼���DDS������ǰ����֮ƥ�������д�߿����Ѿ�������һ��������������
 *          ���ݶ��߿��ܶ���Щ����ʱ�����޷����յ������ݸ���Ȥ����������£�����ͨ�����ø�QoS��
 *          ʹ�����ݶ��߿����ڼ���DDS����ͨ��ʱ��������ʹ��ʱ����ȡƥ�������д����ǰ���͵ġ���ʷ���ݡ���
 *          ��QoS���Կ������ݶ����Ƿ��ȡ��Ӧƥ�������д�߷��͵ġ���ʷ���ݡ��Լ����ݵ���Դ��
 *          ���ݶ��߿���ͨ�����ø�QoS����ȡ��Ӧƥ�������д����ǰ���͡���ʷ���ݡ���
 *          �ڻ�ȡ��Ӧƥ�������д�ߵġ���ʷ���ݡ��Ļ����ϣ����ݶ���Ҳ����ͨ�����ø�QoS��ѡ���ȡ����Դ��������
 *          - ���ݶ���ֻ��ȡ��ǰ��Ȼ��������д�߷��͵ġ���ʷ���ݡ���  
 *          - ���ݶ��߻�ȡ���Ͷ���������д�ߣ������Ѿ���ɾ��������д�ߣ����͵ġ���ʷ���ݡ���  
 *
 *          ��Ա | Ĭ��ֵ | ƥ������� | ��Ч�Լ�� | �����Լ�� | �ɱ��Լ��
 *          --- | --- | --- | --- | --- | ---
 *          #kind | ::DDS_VOLATILE_DURABILITY_QOS | ����д��.#kind >= ���ݶ���.#kind | �� | �� | ���ɱ�
 */

typedef struct DDS_DurabilityQosPolicy
{
    /** @brief   ָ���־û����ͣ��μ�@ref DDS_DurabilityQosPolicyKind �� */
    DDS_DurabilityQosPolicyKind kind;
}DDS_DurabilityQosPolicy;

#endif /* DurabilityQosPolicy_h__*/
