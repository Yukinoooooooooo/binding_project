/**
 * @file:       RapidIOConfigQosPolicy.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#ifndef RapidIOConfigQosPolicy_h__
#define RapidIOConfigQosPolicy_h__

#include "OsResource.h"
#include "ZRBuiltinTypes.h"

#ifdef _ZRDDS_RIO

/**
 * @struct DDS_RapidIOControllerConfig
 *
 * @ingroup CoreQosStruct
 *
 * @brief RapidIO���������á�
 */
typedef struct DDS_RapidIOControllerConfig
{
    /** @brief ��������ԵĿ������š� */
    DDS_Long rapidio_controller;
    /** @brief RapidIO�豸��ַ�� */
    DDS_ULong rapidio_address;
    /** @brief RapidIO���ջ���ӳ����������ַ�� */
    DDS_ULong receive_window_base_address;
    /** @brief RapidIO���մ���С����Ϊÿ�ο����Ĵ�С��������Ϊ4MB�� */
    DDS_Long receive_window_size;
    /** @brief �����Ӵ��ڴ�С  
     * 
     * @details Ĭ�ϵ��Ӵ��ڴ�С�����մ��ᱻ���ֳ����ɸó����Ӵ��ڣ�ÿ���Ӵ��ڱ������һ�������������RapidIOͨ�š�
     *          ��û�п��е��Ӵ���ʱ���Զ����ϴ����봰�ĵ�ַ�������������մ���С�Ĵ���
     *          ���Ͷ˿�������������ߵ�DDS_PropertyQosPolicy����֪���ն˶��ڸ�����������������Ӵ��ڴ�С��
     */
    DDS_Long receive_subwindow_size;
    /** @brief RapidIO���մ�������󿪴����������Ϊ8 */
    DDS_ULong receive_window_limit;
    /** @brief RapidIO�豸��ַ������ơ� */
    DDS_ULong rapidio_address_limit;
}DDS_RapidIOControllerConfig;

#ifdef __cplusplus
extern "C"
{
#endif

DDS_SEQUENCE_CPP(DDS_RapidIOControllerConfigSeq, DDS_RapidIOControllerConfig);

#ifdef __cplusplus
}
#endif

/**
 * @struct DDS_RapidIOConfigQosPolicy
 *
 * @ingroup CoreQosStruct
 *
 * @brief RapidIO����QoS��
 *
 * @details
 *          ��Ա | Ĭ��ֵ | ƥ������� | ��Ч�Լ�� | �����Լ�� | �ɱ��Լ��
 *          --- | --- | --- | --- | --- | ---
 *          #controllers_config | �� | �� | �� | �� | ���ɱ�
 */
typedef struct DDS_RapidIOConfigQosPolicy
{
    /** @brief RapidIO�������������С� */
    DDS_RapidIOControllerConfigSeq controllers_config;
}DDS_RapidIOConfigQosPolicy;

#endif /* _ZRDDS_RIO */

#endif /* RapidIOConfigQosPolicy_h__ */
