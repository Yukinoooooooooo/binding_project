/**
 * @file:       ZRSleep.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#ifndef ZRSLEEP_H
#define ZRSLEEP_H

#include "ZROSDefine.h"
#include "OsResource.h"
#include "ZRDDSCommon.h"

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @fn  void DCPSDLL ZRSleep(DDS_ULong ms);
 *
 * @ingroup CoreUtilityFunction
 *
 * @brief   ��ƽ̨��ʱ������
 *
 * @param   ms  ��ʱ�ĺ�������
 */

void DCPSDLL ZRSleep(DDS_ULong ms);

/**
 * @fn  void DCPSDLL ZRUSleep(DDS_ULong us);
 *
 * @ingroup CoreUtilityFunction
 *
 * @brief   ��ƽ̨��ʱ������
 *
 * @param   us  ��ʱ��΢������
 */

void DCPSDLL ZRUSleep(DDS_ULong us);

/**
 * @fn  void DCPSDLL ZRSyncSleep(DDS_ULong us);
 *
 * @brief   ͬ��sleep��
 *
 * @param   us  ΢�롣
 */

void DCPSDLL ZRSyncSleep(DDS_ULong us);

/**
 * @fn  void DCPSDLL ZRSyncSleep(DDS_ULong us);
 *
 * @brief   ʹ��forѭ��ͬ��sleep��
 *
 * @param   count  ѭ��������
 */

void DCPSDLL ZRForSleep(DDS_ULong count);

#ifdef __cplusplus
}
#endif

#endif
