/**
 * @file:       ZRMemPool.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#ifndef ZRMemPool_h__
#define ZRMemPool_h__

#include "OsResource.h"
#include "ZRDDSCommon.h"

#ifdef __cplusplus
extern "C"
{
#endif

typedef struct ZRMemPool ZRMemPool;

#ifdef _MEMORY_USE_TRACK_

#define ZRMalloc(_MEM_POOL_, _SIZE_) ZRMallocWCallInfo(_MEM_POOL_, _SIZE_, __FILE__, __FUNCTION__, __LINE__)

DCPSDLL extern void* ZRMallocWCallInfo(struct ZRMemPool* pool, DDS_ULong size, const char* fileName, const char* funcName, size_t line);

#else

/**
 * @fn  DCPSDLL extern void* ZRMalloc(ZRMemPool* pool, DDS_ULong size);
 *
 * @ingroup CoreBaseFunction   
 *
 * @brief   ���ڴ���з���ָ�����ȵĿռ䡣
 *
 * @param [in,out]  pool    ָ���ڴ�ء�
 * @param   size            ָ����С��
 *
 * @return  NULL��ʾ����ʧ�ܣ�����ָ�����ɹ��Ŀռ䡣
 */

DCPSDLL extern void* ZRMalloc(ZRMemPool* pool, DDS_ULong size);

#endif /* _MEMORY_USE_TRACK_ */

/**
 * @fn  DCPSDLL extern void ZRDealloc(ZRMemPool* pool, void* mem);
 *
 * @ingroup CoreBaseFunction   
 *
 * @brief   ���ڴ�����ͷ�ָ���Ŀռ䡣
 *
 * @param [in,out]  pool    ָ���ڴ�ء�
 * @param [in,out]  mem     ָ����Ҫ�ͷŵĿռ䡣
 */

DCPSDLL extern void ZRDealloc(ZRMemPool* pool, void* mem);

/**
 * @fn  DCPSDLL void ZRInitialGlobalMemPool();
 *
 * @ingroup CoreBaseFunction   
 *
 * @brief   ��ʼ��ȫ���ڴ�ռ䡣
 */

DCPSDLL void ZRInitialGlobalMemPool();

/**
 * @fn  DCPSDLL void ZRFinalizeGlobalMemPool();
 *
 * @ingroup CoreBaseFunction   
 *
 * @brief   ����ȫ�����ݿռ䡣
 */

DCPSDLL void ZRFinalizeGlobalMemPool();

#ifdef __cplusplus
}
#endif

#endif /* ZRMemPool_h__*/
