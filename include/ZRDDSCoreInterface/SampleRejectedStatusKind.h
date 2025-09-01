/**
 * @file:       SampleRejectedStatusKind.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#if !defined(_SAMPLEREJECTEDSTATUSKIND_H)
#define _SAMPLEREJECTEDSTATUSKIND_H

/**
 * @enum DDS_SampleRejectedStatusKind
 *
 * @ingroup CoreBaseStruct
 *
 * @brief   ���ڱ�ʶ�����������ܾ���ԭ�����͡�
 */

typedef enum DDS_SampleRejectedStatusKind
{
    /** @brief   ��������δ���ܾ��� @ingroup CoreBaseStruct */
    DDS_NOT_REJECTED,
    /** @brief   ������������ DDS_ResourceLimitsQosPolicy::max_instances ԭ�򱻾ܾ��� @ingroup CoreBaseStruct */
    DDS_REJECTED_BY_INSTANCE_LIMIT,
    /** @brief   ������������ DDS_ResourceLimitsQosPolicy::max_samples ԭ�򱻾ܾ��� @ingroup CoreBaseStruct */
    DDS_REJECTED_BY_SAMPLES_LIMIT,
    /** @brief   ������������ DDS_ResourceLimitsQosPolicy::max_samples_per_instance ԭ�򱻾ܾ��� @ingroup CoreBaseStruct */
    DDS_REJECTED_BY_SAMPLES_PER_INSTANCE_LIMIT
}DDS_SampleRejectedStatusKind;

#endif  /*_SAMPLEREJECTEDSTATUSKIND_H*/
