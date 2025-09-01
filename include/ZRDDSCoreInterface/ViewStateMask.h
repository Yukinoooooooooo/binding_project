/**
 * @file:       ViewStateMask.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#ifndef ViewStateMask_h__
#define ViewStateMask_h__

#include "OsResource.h"

/**
 * @typedef DDS_ULong DDS_ViewStateMask
 *
 * @ingroup CoreBaseStruct
 *
 * @brief   #DDS_ViewStateKind �������ʾ��� #DDS_ViewStateKind ��״̬�ļ��ϡ�
 */

typedef DDS_ULong DDS_ViewStateMask;

/**
 * @def DDS_ANY_VIEW_STATE
 *
 * @ingroup CoreMacro
 *
 * @brief   ����������������͵� #DDS_ViewStateKind �ļ��ϡ�
 */

#define DDS_ANY_VIEW_STATE 0xffffffff

#endif /* ViewStateMask_h__*/
