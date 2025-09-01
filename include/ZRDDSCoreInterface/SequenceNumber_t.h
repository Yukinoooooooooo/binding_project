/**
 * @file:       SequenceNumber_t.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#ifndef SEQUENCENUMBER_H
#define SEQUENCENUMBER_H

#include "ZRDDSCommon.h"
#include "OsResource.h"

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @struct DDS_SequenceNumber_t
 *
 * @ingroup  CoreBaseStruct
 *
 * @brief   64���ص����кţ�seq_num = high * (2^32) + low.
 */

typedef struct DDS_SequenceNumber_t
{
    /** @brief ���кŵĸ�λ. */
    DDS_Long high;
    /** @brief ���кŵĵ�λ. */
    DDS_ULong low;
} DDS_SequenceNumber_t;

#ifdef __cplusplus
}
#endif

#endif
