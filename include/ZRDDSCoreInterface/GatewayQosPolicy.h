/**
* @file:       GatewayQosPolicy.h
*
* copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
*/

#ifndef GatewayQosPolicy_h__
#define GatewayQosPolicy_h__

#include "ZROSDefine.h"
#ifdef _ZRDDS_INCLUDE_GATEWAY
#include "OsResource.h"
#include "TransportConfigQosPolicy.h"

/**
 * @enum DDS_GatewayQosPolicyKind
 *
 * @ingroup CoreQosStruct
 *
 * @brief   ���ط������͡�
 */

typedef enum DDS_GatewayQosPolicyKind
{
    /**
     * @brief   �����������ز���ת����
     *
     * @ingroup CoreQosStruct
     *
     * @details ������ΪĬ�����͡�Ĭ������£�ʵ��֮��ͨ���鲥Data(P)����ɻ��෢�֣������շ�����ͨ����Ե㵥����
     *          ����ͬ�������鲥���������ܹ���ͨʱ�����ط������Ͳ��ô�Ĭ��ֵ���ɡ�
     */
    DDS_NO_FORWARD_GATEWAY_QOS,

    /**
     * @brief   ����Ҫ�������ؽ�Data(p)ת������֪��ͬһ����µ�����������ߡ�
     *
     * @ingroup CoreQosStruct
     *
     * @details ʵ������£����ܴ����ڲ�ͬ����֮���޷�ʹ���鲥�����ܹ�ʹ�õ�����ͨ�����绷����
     *          ��ʱ�����������в������ط��񣬲���������ߵ����ط�����������ΪDDS_SPDP_FORWARD_GATEWAY_QOS����������Э��ʵ��֮�佻��Data(P)�����ƥ�䡣
     *          �������շ��������Կɲ���Ĭ��ģʽ���Ե�Ե㵥���ķ�ʽ���С�
     */
    DDS_SPDP_FORWARD_GATEWAY_QOS,

    /**
     * @brief   ��Ҫ��������Э����ͨ�š�
     *
     * @ingroup CoreQosStruct
     *
     * @warning ������δʵ�֡�
     */
    DDS_SEDP_FORWARD_GATEWAY_QOS,

    /**
     * @brief   ��Ҫ��������ת�����е����ݣ��������������Լ��û����ݣ���
     *
     * @ingroup CoreQosStruct
     *
     * @details ʵ������£����ܴ����ڲ�ͬ����֮���޷�ʹ���鲥��Ҳ�޷�ʹ�õ�����ͨ�����绷����
     *          ��ʱ�����ڲ�ͬ�����зֱ������ط��������ط���֮����Ҫ�໥���ӣ�
     *          ����������ߵ����ط�����������ΪDDS_USER_FORWARD_GATEWAY_QOS����������Э��ʵ��֮��Ļ��෢�֡�ƥ�估�����������շ�������
     */
    DDS_USER_FORWARD_GATEWAY_QOS,

    /**
     * @brief   ��Ҫ��������ת��Ŀ�ĵ�Ϊ�������������е����ݣ��������������Լ��û����ݣ�����ת��Ŀ�ĵ�Ϊͬһ�������µ����ݡ�
     *
     * @ingroup CoreQosStruct
     *
     * @warning ������δʵ�֡�
     */
    DDS_USER_FORWARD_ONLY_GATEWAY_QOS
}DDS_GatewayQosPolicyKind;

/**
 * @struct DDS_GatewayQosPolicy
 *
 * @ingroup CoreQosStruct
 *
 * @brief   �����������ò��ԡ�
 *
 * @details ��Ĭ�ϵ�DDSͨ�Ź����У��ڵ���ڵ�֮���ͨ���鲥���෢�֣�������ɺ����������շ�������
 *          Ȼ���������绷����Ϊ���ӵ�����£�������������������������£�
 *          �޷���֤����������֧���鲥���֣�Ҳ�޷���֤���нڵ���ܹ�������ͨ��
 *          ��ˣ��ṩ�������صĹ��ܣ��������������ط����Լ�GatewayQosPolicy��
 *          ���ڽ���������绷��������ӵ��µ��޷����֡������շ����⡣
 *          ʹ�ø����ط���ʱ���������ø�QoS���⣬����Ҫ�����ط����ַ�����������QoS��pdp_destination_addresses��
 *          ͬʱ����������������QoS��domain_destination_addresses��
 *
 *          ��Ա | Ĭ��ֵ | ƥ������� | ��Ч�Լ�� | �����Լ�� | �ɱ��Լ��
 *          --- | --- | --- | --- | --- | ---
 *          #kind | ::DDS_NO_FORWARD_GATEWAY_QOS | ����д��.#kind == ���ݶ���.#kind | �� | �� | ���ɱ�
 */
typedef struct DDS_GatewayQosPolicy
{
    /** @brief   ָ�������������ʹ�õ����ط������ͣ��μ�@ref DDS_GatewayQosPolicyKind �� */
    DDS_GatewayQosPolicyKind kind;

    /**
     * @brief   ָ���м̷�������ַ�� 
     *
     * @warning ��ع���δʵ�֡�
     */
    DDS_TransportConfigQosPolicy relay_addresses;
}DDS_GatewayQosPolicy;

#endif // _ZRDDS_INCLUDE_GATEWAY

#endif /* GatewayQosPolicy_h__*/