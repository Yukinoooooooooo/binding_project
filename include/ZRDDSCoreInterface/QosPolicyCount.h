/**
 * @file:       QosPolicyCount.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#ifndef QosPolicyCount_h__
#define QosPolicyCount_h__

#include "OsResource.h"
#include "ZRDDSCommon.h"
#include "QosPolicyId_t.h"
#include "ZRSequence.h"

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @struct DDS_QosPolicyCount
 *
 * @ingroup CoreBaseStruct
 *
 * @brief   QoS���ʹ���ͳ�ƣ����� DDS_OfferedIncompatibleQosStatus �Լ� 
 *          DDS_RequestedIncompatibleQosStatus ��
 */

typedef struct DDS_QosPolicyCount
{
    /** @brief   ö�����ͱ�ʾQoS���͡� */
    DDS_QosPolicyId_t last_policy_id;
    /** @brief   #last_policy_id ָ�����͵Ĵ����� */
    DDS_Long count;
}DDS_QosPolicyCount;


/**
 * @struct DDS_QosPolicyCountSeq
 *
 * @ingroup CoreBaseStruct
 *
 * @brief   ���������������� DDS_QosPolicyCount �����С�
 */
DDS_SEQUENCE_CPP(DDS_QosPolicyCountSeq, DDS_QosPolicyCount);

#ifdef __cplusplus
}
#endif

#endif /* QosPolicyCount_h__*/
