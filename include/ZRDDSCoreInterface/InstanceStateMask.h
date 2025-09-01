/**
 * @file:       InstanceStateMask.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#ifndef InstanceStateMask_h__
#define InstanceStateMask_h__

#include "OsResource.h"

/**
 * @typedef DDS_ULong DDS_InstanceStateMask
 *
 * @ingroup CoreBaseStruct
 *          
 * @brief   ::DDS_InstanceStateKind �������ʾ��� ::DDS_InstanceStateKind ��״̬��
 */
typedef DDS_ULong DDS_InstanceStateMask;

/**
 * @brief   �������ʾ�����ʵ��״̬ ::DDS_InstanceStateKind ��
 *
 * @ingroup CoreMacro
 */
#define DDS_ANY_INSTANCE_STATE 0xffffffff

/**
 * @brief   �������ʾ�Ǵ���ʵ��״̬ ::DDS_InstanceStateKind ��
 *
 * @ingroup CoreMacro
 */
#define  DDS_NOT_ALIVE_INSTANCE_STATE 0x00000006

#endif /* InstanceStateMask_h__*/
