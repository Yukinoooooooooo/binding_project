/**
 * @file:       DDSSecurityPluginQosPolicy.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#ifndef DDSSecurityPluginQosPolicy_h__
#define DDSSecurityPluginQosPolicy_h__

#include "ZROSDefine.h"
#ifdef _ZRDDSSECURITY

#include "OsResource.h"
#include "ZRBuiltinTypes.h"

/**
 * @enum DDS_SecurityPluginType
 *
 * @ingroup  CoreQosStruct
 *
 * @brief   ���尲ȫ��������͡�
 */

typedef enum DDS_SecurityPluginType
{
    DDSSECURITY_EMPTY = 0,
    DDSSECURITY_AUTHENTICATION = 1,
    DDSSECURITY_ACCESSCONTROL = 2,
    DDSSECURITY_CRYPTOGRAPHIC = 4,
}DDS_SecurityPluginType;

typedef DDS_SecurityPluginType DDS_DDSSecurityPluginType;

/**
 * @typedef struct DDS_SecurityPlugin
 *
 * @ingroup  CoreQosStruct
 *
 * @brief   ����һ��DDS��ȫ����Ľṹ.
 */

typedef struct DDS_SecurityPlugin
{
    /** @brief ��������ƣ�������������������øò�� */
    DDS_CharSeq ref_name;
    /** @brief �����·���� */
    DDS_CharSeq lib_path;
    /** @brief ������а����Ĳ�����ͣ�ʹ�� DDS_SecurityPluginType �����趨 */
    DDS_ULong types;
}DDS_SecurityPlugin;

typedef DDS_SecurityPlugin DDS_DDSSecurityPlugin;

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

DDS_SEQUENCE_CPP(DDS_SecurityPluginSeq, DDS_SecurityPlugin);

typedef DDS_SecurityPluginSeq DDS_DDSSecurityPluginSeq;

#ifdef __cplusplus
}
#endif /* __cplusplus */

/**
 * @struct DDS_SecurityPluginQosPolicy
 *
 * @ingroup CoreQosStruct
 *
 * @brief ����DDS��ȫ������ϵ�QoS�������������һ��DDS��ȫ�����Ȼ��ͨ�����ֽ������֡�
 */

typedef struct DDS_SecurityPluginQosPolicy
{
    /** @brief   �û��Զ��尲ȫ����б���������Ψһ��ʶ�� */
    DDS_SecurityPluginSeq security_plugins;
}DDS_SecurityPluginQosPolicy;

#endif /* _ZRDDSSECURITY */

#endif /* DDSSecurityPluginQosPolicy_h__ */
