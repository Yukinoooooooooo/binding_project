/**
 * @file:       EntityFactoryQosPolicy.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#ifndef EntityFactoryQosPolicy_h__
#define EntityFactoryQosPolicy_h__

#include "OsResource.h"

/**
 * @struct DDS_EntityFactoryQosPolicy
 *
 * @ingroup CoreQosStruct
 *
 * @brief   ʵ�幤�����á�
 *
 * @details ����Ϊ������������ʵ���ʱ���Ƿ��Զ�ʹ���䴴����ʵ�壬ʹ�ܵ���ϸ����μ� Entity::enable ,��QoS��
 *          ���ü�����ʱ����Ϊfalse�����Ա�����©�ڴ����������֮�������������ݶ��ߵļ�����֮ǰ�����ݵ���֪ͨ��
 *          ��©��ԭ����������Զ�ʹ��ʵ�壬����ʵ�崴����ɺ󣬿����Ѿ��յ���DDS�������Ѿ����ڵ�ʵ��������Ϣ��
 *          ��ʱ��δ���ü�������DDS������Դ��������ݵ�֪ͨ�����õĲ���μ����� @ref CreateDisabledEntity.cpp 
 *          ��Ա | Ĭ��ֵ | ƥ������� | ��Ч�Լ�� | �����Լ�� | �ɱ��Լ��
 *          --- | --- | --- | --- | --- | ---
 *          #autoenable_created_entities | true | �� | �� | �� | �ɱ�
 */

typedef struct DDS_EntityFactoryQosPolicy
{
    /** @brief   �����Ƿ��Զ�ʹ����ʵ�塣 */
    DDS_Boolean autoenable_created_entities;
}DDS_EntityFactoryQosPolicy;

#endif /* EntityFactoryQosPolicy_h__ */
