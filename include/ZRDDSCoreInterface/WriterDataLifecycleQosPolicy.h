/**
 * @file:       WriterDataLifecycleQosPolicy.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#ifndef WriterDataLifecycleQosPolicy_h__
#define WriterDataLifecycleQosPolicy_h__

#include "OsResource.h"
#include "Duration_t.h"

/**
 * @struct DDS_WriterDataLifecycleQosPolicy
 *
 * @ingroup CoreQosStruct
 *
 * @brief ����д�����������������á�
 *
 * @details 
 *          ��Ա | Ĭ��ֵ | ƥ������� | ��Ч�Լ�� | �����Լ�� | �ɱ��Լ��
 *          --- | --- | --- | --- | --- | ---
 *          #autodispose_unregistered_instances | true | �� | �� | �� | ���ɱ�
 *          #autopurge_unregistered_instance_delay | #DDS_TIME_INFINITE | �� | �� | �� | ���ɱ�
 *          #autopurge_disposed_instance_delay | #DDS_TIME_INFINITE | �� | �� | �� | ���ɱ�
 *
 */
typedef struct DDS_WriterDataLifecycleQosPolicy
{
    /** @brief �����Ƿ��Զ������Ѿ�ע����ʵ���� */
    DDS_Boolean autodispose_unregistered_instances;
    /** @brief ������ע��ʵ��������Դ���ӳ�ʱ�䡣 */
    DDS_Duration_t autopurge_unregistered_instance_delay;
    /** @brief ����������ʵ��������Դ���ӳ�ʱ�䡣 */
    DDS_Duration_t autopurge_disposed_instance_delay;
}DDS_WriterDataLifecycleQosPolicy;

#endif /* WriterDataLifecycleQosPolicy_h__*/
