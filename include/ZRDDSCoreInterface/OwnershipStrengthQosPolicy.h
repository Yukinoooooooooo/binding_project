/**
 * @file:       OwnershipStrengthQosPolicy.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#ifndef OwnershipStrengthQosPolicy_h__
#define OwnershipStrengthQosPolicy_h__

#include "OsResource.h"

#ifdef _ZRDDS_INCLUDE_OWNERSHIP_QOS

/**
 * @struct DDS_OwnershipStrengthQosPolicy
 *
 * @ingroup CoreQosStruct
 *
 * @brief   ����Ȩֵ���á�
 *
 * @details ��QoS�� DDS_OwnershipQosPolicy::kind == #DDS_EXCLUSIVE_OWNERSHIP_QOS 
 *          ʱ��������д�ߵ�Ȩֵ��
 *          ��Ա | Ĭ��ֵ | ƥ������� | ��Ч�Լ�� | �����Լ�� | �ɱ��Լ��
 *          --- | --- | --- | --- | --- | ---
 *          #value | 0 | �� | #value >= 0 | �� | �ɱ� 
 */

typedef struct DDS_OwnershipStrengthQosPolicy
{
    /** @brief   ָ��Ȩֵ����ֵԽ��ȨֵԽ�ߡ� */
    DDS_Long value;
}DDS_OwnershipStrengthQosPolicy;

#endif /* _ZRDDS_INCLUDE_OWNERSHIP_QOS */

#endif /* OwnershipStrengthQosPolicy_h__*/
