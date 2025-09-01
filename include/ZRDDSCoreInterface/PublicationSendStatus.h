/**
* @file:       PublicationSendStatus.h
*
* copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
*/

#ifndef PublicationSendStatus_h__
#define PublicationSendStatus_h__

#include "InstanceHandle_t.h"

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @enum DDS_TransportKind
 *
 * @ingroup CoreBaseStructTransportKind
 *
 * @brief   ���ڱ�ʶͨ��ʹ�õĴ��䷽ʽ��
 */

typedef enum DDS_TransportKind
{
    /** @brief  ������Locator_t���͡� @ingroup CoreBaseStructTransportKind */
    DDS_TRANSPORT_KIND_RESERVED = 0,
    /** @brief  ʹ��IPv4��UDP���䷽ʽ�� @ingroup CoreBaseStructTransportKind */
    DDS_TRANSPORT_KIND_UDPv4 = 1,
    /** @brief  ʹ��IPv6��UDP���䷽ʽ�� @ingroup CoreBaseStructTransportKind */
    DDS_TRANSPORT_KIND_UDPv6 = 2,
    /** @brief   ʹ��IPv4��TCP���䷽ʽ�� @ingroup CoreBaseStructTransportKind */
    DDS_TRANSPORT_KIND_TCPv4 = 8,
    /** @brief   ʹ��IPv6��TCP���䷽ʽ�� @ingroup CoreBaseStructTransportKind */
    DDS_TRANSPORT_KIND_TCPv6 = 16,
    /** @brief  ʹ����RTPSЭ���UDP���䷽ʽ�� @ingroup CoreBaseStructTransportKind */
    DDS_TRANSPORT_KIND_UDPv4_RAW = 32,
    /** @brief  ʹ����RTPSЭ���TCP���䷽ʽ�� @ingroup CoreBaseStructTransportKind */
    DDS_TRANSPORT_KIND_TCPv4_RAW = 64,
    /** @brief   ʹ��IPv4��TCP��˴��䷽ʽ�� @ingroup CoreBaseStructTransportKind */
    DDS_TRANSPORT_KIND_TCPv4_CC = 128,
    /** @brief   ʹ��IPv4��TCP���������䷽ʽ�� @ingroup CoreBaseStructTransportKind */
    DDS_TRANSPORT_KIND_TCPv4_MC = 256,
    /** @brief   ʹ�ù����ڴ�Ĵ��䷽ʽ�� @ingroup CoreBaseStructTransportKind */
    DDS_TRANSPORT_KIND_SHMEM = 16777216,
    /** @brief   ʹ��RapidIO�Ĵ��䷽ʽ�� @ingroup CoreBaseStructTransportKind */
    DDS_TRANSPORT_KIND_RAPIDIO = 100,
    /** @brief   ʹ��PCI-E�Ĵ��䷽ʽ�� @ingroup CoreBaseStructTransportKind */
    DDS_TRANSPORT_KIND_PCIE,
#ifdef _ZRDDS_INCLUDE_DPDK_ANS
    DDS_TRANSPORT_KIND_DPDK_ANS_UDPv4,
#endif //_ZRDDS_INCLUDE_DPDK_ANS
}DDS_TransportKind;

/**
 * @enum DDS_LocatorStatusKind
 *
 * @ingroup CoreBaseStructLocatorStatusKind
 *
 * @brief   ���ڱ�ʶ��ǰ���ӵ�ͨ��״̬��
 */

typedef enum DDS_LocatorStatusKind
{
    /** @brief   ��ǰ����δʹ�á� @ingroup CoreBaseStructLocatorStatusKind */
    DDS_LOCATOR_STATUS_NOT_VALID,
    /** @brief   ��ǰ����δ�������ݡ� @ingroup CoreBaseStructLocatorStatusKind */
    DDS_LOCATOR_STATUS_WATING_SEND,
    /** @brief   ��ǰ��������ͨ�ţ��������ݡ� @ingroup CoreBaseStructLocatorStatusKind */
    DDS_LOCATOR_STATUS_SENDED,
    /** @brief   ��ǰ����ͨ���쳣�� @ingroup CoreBaseStructLocatorStatusKind */
    DDS_LOCATOR_STATUS_ERROR,
    /** @brief   ��ǰ�������������� @ingroup CoreBaseStructLocatorStatusKind */
    DDS_LOCATOR_STATUS_RECONNECTING,
}DDS_LocatorStatusKind;

/**
 * @struct DDS_PublicationSendLocator
 *
 * @ingroup CoreBaseStruct
 *
 * @brief    ����д�������ݶ���ͨ��ʹ�õ�������Ϣ��
 */

typedef struct DDS_PublicationSendLocator
{
    /** @brief   ��ǰ����ʹ�õĴ��䷽ʽ�� */
    DDS_TransportKind locator_type;
    /** @brief   ��ǰ���Ӵ������ݵ�Ŀ�ĵ�ַ�� */
    DDS_Octet locator_addr[4];
    /** @brief   ��ǰ���Ӵ������ݵ�Ŀ�Ķ˿ڡ� */
    DDS_ULong locator_port;
    /** @brief   ��ǰ���ӵ�ͨ��״̬�� */
    DDS_LocatorStatusKind locator_status;
    /** @brief   ��ǰ�������µĴ��䷵��ֵ�� */
    DDS_Long locator_return_code;
}DDS_PublicationSendLocator;

/**
 * @struct DDS_PublicationSendLocatorSeq
 *
 * @ingroup CoreBaseStruct
 *
 * @brief   ���� DDS_PublicationSendLocator ���������ͣ��μ� #DDS_USER_SEQUENCE_CPP ��
 */
DDS_SEQUENCE_CPP(DDS_PublicationSendLocatorSeq, DDS_PublicationSendLocator);

/**
 * @struct DDS_PublicationSendStatus
 *
 * @ingroup CoreBaseStruct
 *
 * @brief    ����д�ߵķ���״̬��
 */

typedef struct DDS_PublicationSendStatus
{
    /** @brief   �뵱ǰ����д��ͨ�ŵ����ݶ��ߵ�Ψһ��ʶ�� */
    DDS_InstanceHandle_t subscription_handle;
    /** @brief   ������ݶ��ߵ�����ͨ��������Ϣ�� */
    DDS_PublicationSendLocatorSeq send_locators;
}DDS_PublicationSendStatus;

/**
 * @struct DDS_PublicationSendStatusSeq
 *
 * @ingroup CoreBaseStruct
 *
 * @brief   ���� DDS_PublicationSendStatus ���������ͣ��μ� #DDS_USER_SEQUENCE_CPP ��
 */
DDS_SEQUENCE_CPP(DDS_PublicationSendStatusSeq, DDS_PublicationSendStatus);

#ifdef __cplusplus
}
#endif

#endif /* PublicationSendStatus_h__*/
