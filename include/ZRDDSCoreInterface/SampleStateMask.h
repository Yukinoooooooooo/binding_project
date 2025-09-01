/**
 * @file:       SampleStateMask.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#ifndef SampleStateMask_h__
#define SampleStateMask_h__

#include "OsResource.h"

/**
 * @typedef DDS_ULong DDS_SampleStateMask
 *
 * @ingroup  CoreBaseStruct
 *
 * @brief   ::DDS_SampleStateKind �������ʾ��� ::DDS_SampleStateKind ��״̬��
 */

typedef DDS_ULong DDS_SampleStateMask;

/**
 * @def DDS_ANY_SAMPLE_STATE
 *
 * @ingroup  CoreMacro
 *
 * @brief   �������ʾ���������״̬��
 */

#define  DDS_ANY_SAMPLE_STATE 0xffffffff

#endif /* SampleStateMask_h__*/
