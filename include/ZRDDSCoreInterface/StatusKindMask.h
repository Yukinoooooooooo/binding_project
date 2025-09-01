/**
 * @file:       StatusKindMask.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#if !defined(_STATUSKINDMASK_H)
#define _STATUSKINDMASK_H

#include "ZRDDSCommon.h"
#include "OsResource.h"

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @typedef DDS_ULong DDS_StatusKindMask
 *
 * @ingroup CoreStatusStruct
 *
 * @brief   #DDS_StatusKind �������ʾ��� #DDS_StatusKind ��״̬�ļ��ϡ�
 * 
 * @details  ���磺��������Ϊ0x0003������0x0003 = 0x0001 | 0x0002����������״̬���ͣ�
 *              #DDS_INCONSISTENT_TOPIC_STATUS (0x0001)���� #DDS_OFFERED_DEADLINE_MISSED_STATUS (0x0002)��
 */

typedef DDS_ULong DDS_StatusKindMask;

/**
 * @def DDS_STATUS_MASK_ALL
 *
 * @ingroup  CoreMacro
 *
 * @brief   ����������������͵� #DDS_StatusKind �ļ��ϡ�
 */

#define DDS_STATUS_MASK_ALL 0xffffffff

/**
 * @def DDS_STATUS_MASK_NONE
 *
 * @ingroup  CoreMacro
 *
 * @brief   ����������յ� #DDS_StatusKind �ļ��ϡ�
 */

#define DDS_STATUS_MASK_NONE 0

#ifdef __cplusplus
}
#endif

#endif  /*_STATUSKINDMASK_H*/
