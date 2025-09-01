/**
 * @file:       OwnershipQosPolicy.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#ifndef OwnershipQosPolicy_h__
#define OwnershipQosPolicy_h__

#include "OsResource.h"

#ifdef _ZRDDS_INCLUDE_OWNERSHIP_QOS

/**
 * @enum DDS_OwnershipQosPolicyKind
 *
 * @ingroup CoreQosStruct 
 *
 * @brief   ָ������ʵ������Ȩ���͡�
 */

typedef enum DDS_OwnershipQosPolicyKind
{
    /**
     * @brief   ��������Ȩ���͡�
     *
     * @ingroup CoreQosStruct
     * 
     * @details Ĭ��Ϊ�����ͣ�����������д��ȥ����ͬһ������ʵ���������ݶ��߻�֪ͨ�û�����ƥ������д�߷��������ݡ�
     */
    DDS_SHARED_OWNERSHIP_QOS,

    /**
     * @brief   ��ռ����Ȩ���͡�
     *
     * @ingroup CoreQosStruct
     * 
     * @details ����Ϊ�����ͱ�ʾÿ������ʵ��ֻ�ܱ�ӵ�и�����ʵ������Ȩ������д���޸ģ������ݶ��߽���֪ͨ�û�������д�߷��������ݡ�
     *          �����ݶ��߶�����ʵ��������Ȩ����������������������д�ߣ�
     *          1. DDS_OwnershipStrengthQosPolicy::value ��������д�ߣ�  
     *          2. ����д�߱��봦�ڴ��״̬ DDS_LivelinessQosPolicy ��  
     *          3. ����д��δΥ�� DDS_DeadlineQosPolicy ��  
     *          4. ���ݶ����յ�������д�ߵ����ݣ�
     *          
     *          ���¼�������ᵼ������Ȩ�ı仯��
     *          - ϵͳ�о��и��� DDS_OwnershipStrengthQosPolicy::value ֵ������д�߷����˸�����ʵ���µ����ݣ�  
     *          - ӵ�и�����ʵ��������д�ߵ� DDS_OwnershipStrengthQosPolicy::value ֵ�ı��Ҳ���Ϊ���  
     *          - ӵ�и�����ʵ��������д�ߵĴ���Է����˱仯 DDS_LivelinessQosPolicy ��
     *              - ��alive��Ϊnot_aliveʱ��������д��ʧȥ��ӵ��Ȩ��
     *              - ��not_alive��Ϊaliveʱ���������·��������ݣ�������д�����»�ȡӵ��Ȩ��
     *          - ӵ�и�����ʵ��������д��Υ���� DDS_DeadlineQosPolicy ��Լ����  
     *              - ��Υ���˽�ֹʱ��Լ��ʱ��������д��ʧȥӵ��Ȩ��
     */
    DDS_EXCLUSIVE_OWNERSHIP_QOS
}DDS_OwnershipQosPolicyKind;

/**
 * @struct DDS_OwnershipQosPolicy
 *
 * @ingroup CoreQosStruct
 *
 * @brief   ����ʵ������Ȩ���á�
 *
 * @details �����Ƿ�����������д��ȥ����ͬһ������ʵ������@ref DDS_OwnershipStrengthQosPolicy 
 *          �����ڹ�����������ڵ��ϵͳ�������ȱ��ݴ�
 *          ��Ա | Ĭ��ֵ | ƥ������� | ��Ч�Լ�� | �����Լ�� | �ɱ��Լ��
 *          --- | --- | --- | --- | --- | ---
 *          #kind | #DDS_SHARED_OWNERSHIP_QOS | ����д��.#kind == ���ݶ���.#kind | �� | �� | ���ɱ�
 */

typedef struct DDS_OwnershipQosPolicy 
{
    /** @brief   ָ������ʵ��������Ȩ���͡� */
    DDS_OwnershipQosPolicyKind kind;
}DDS_OwnershipQosPolicy;

#endif /* _ZRDDS_INCLUDE_OWNERSHIP_QOS */

#endif /* OwnershipQosPolicy_h__*/
