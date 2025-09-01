/**
 * @file:       TypeConsistencyEnforcementQosPolicy.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#ifndef TypeConsistencyEnforcementQosPolicy_h__
#define TypeConsistencyEnforcementQosPolicy_h__

/**
 * @enum DDS_TypeConsistencyKind
 *
 * @ingroup CoreQosStruct
 *
 * @brief   ������ݵ����ͣ����ڴ�Ԥ�ȶ���Ĳ�����ѡȡ��
 */

typedef enum DDS_TypeConsistencyKind 
{
    /**  @brief ����д�������ݶ��߱���֧����ͬ���������͡� @ingroup CoreQosStruct */
    DDS_DISALLOW_TYPE_COERCION,
    /**  @brief ֻ��Ҫ�������ݶ��ߵ����� >= ����д�ߵ����ͼ��ɡ� @ingroup CoreQosStruct */
    DDS_ALLOW_TYPE_COERCION
}DDS_TypeConsistencyKind;

/**
 * @struct  DDS_TypeConsistencyEnforcementQosPolicy
 *
 * @ingroup CoreQosStruct
 *
 * @brief   ���������������ͼ��ݹ������á�
 *   
 * @details ��Ա | Ĭ��ֵ | ƥ������� | ��Ч�Լ�� | �����Լ�� | �ɱ��Լ��
 *          --- | --- | --- | --- | --- | ---
 *          #kind | #DDS_ALLOW_TYPE_COERCION | �� | �� | �� | ���ɱ� 
 *          ע�⣬Ĭ�ϵ�ֵ��Ϊ #DDS_ALLOW_TYPE_COERCION ,Ȼ������Զ�˵ķ�����Ϣ��û�и���Ϣ������ΪԶ��Ϊ #DDS_DISALLOW_TYPE_COERCION ���͡�
 *
 * @warning ��QoS��δʵ�֡�
 */

typedef struct DDS_TypeConsistencyEnforcementQosPolicy 
{
    /** @brief   ָ���������͡� */
    DDS_TypeConsistencyKind kind;
}DDS_TypeConsistencyEnforcementQosPolicy;

#endif /* TypeConsistencyEnforcementQosPolicy_h__*/
