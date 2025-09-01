/**
 * @file:       QualityEvaluationQosPolicy.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#ifndef QualityEvaluationQosPolicy_h__
#define QualityEvaluationQosPolicy_h__

#include "OsResource.h"
#include "Duration_t.h"
#include "InstanceHandle_t.h"
#include "ZRBuiltinTypes.h"

/**
 * @struct DDS_RTPS_MESSAGE_KIND
 *
 * @ingroup CoreQosStruct
 *
 * @brief   RTPS����ͳ���е�����Ϣ���͡�
 * 
 */
typedef enum DDS_RTPS_MESSAGE_KIND
{
    RTPS_MSG_ACKNACK = 0,
    RTPS_MSG_NACK,
    RTPS_MSG_GAP,
    RTPS_MSG_INFO_TS,
    RTPS_MSG_HEARTBEAT,
    RTPS_MSG_INFO_SRC,
    RTPS_MSG_INFO_REPLY_IP4,
    RTPS_MSG_INFO_DST,
    RTPS_MSG_INFO_REPLY,
    RTPS_MSG_NACK_FRAG,
    RTPS_MSG_HEARTBEAT_FRAG,
    RTPS_MSG_DATA,
    RTPS_MSG_RESEND_DATA,
    RTPS_MSG_DATA_FRAG,
    RTPS_MSG_RESEND_DATA_FRAG,
    RTPS_MSG_ACKNACK_BATCH,
    RTPS_MSG_DATA_BATCH,
    RTPS_MSG_RESEND_DATA_BATCH,
    RTPS_MSG_HEARTBEAT_BATCH,
    RTPS_MSG_UNKNOWN_SUBMSGKIND,
    RTPS_MSG_UNKNOWN_WRITER_DATA,
    RTPS_MSG_DUPLICATE_DATA,
    RTPS_MSG_MAX_SAMPLES_LIMITS_DATA,
    RTPS_MSG_MAX_INSTANCES_LIMITS_DATA,
    RTPS_MSG_MAX_SAMPLES_PER_INSTANCE_LIMITS_DATA,
    RTPS_MSG_FILTERED_DATA,
    RTPS_MSG_EARLY_TS_DATA,
    RTPS_DELIVERED_DATA,
    RTPS_MSG_NO_OWNERSHIP_DATA,
    RTPS_MSG_INVALID
}DDS_RTPS_MESSAGE_KIND;

#ifdef _ZRDDS_INCLUDE_QUALITY_EVALUATION

#define DDS_QUALITY_EVAL_LATENCY_RESERVED_NUM 16

/**
 * @struct DDS_LinkQualityEvaluationInfo
 *
 * @ingroup CoreQosStruct
 *
 * @brief   ����ͨ������������������������������ͣ�Ϊ֧����չ��������Ϊ MUTABLE ���͡�
 * 
 */
typedef struct DDS_LinkQualityEvaluationInfo
{
    /** @brief   �ṹ�汾��Ϣ�� */
    DDS_ULong version;
    /** @brief   ���ӵķ��Ͷˣ�ͨ��Ϊ����д�ߵ�Ψһ��ʶ�� */
    DDS_Octet writer_id[16];
    /** @brief   ���ӵĽ��նˣ�ͨ��Ϊ���ݶ��ߵ�Ψһ��ʶ�� */
    DDS_Octet reader_id[16];
    /** @brief   �����ӷ��͵�rtps����Ϣ�ۻ�ͳ�ơ� */
    DDS_ULongLong rtps_smsg_recv_count[30];
    /** @brief   �����Ӵ�������������ۻ�ͳ�ơ� */
    DDS_ULongLong sample_count;
    /** @brief   �����Ӵ���������ۻ���С����λΪ�ֽڡ� */
    DDS_ULongLong sample_size;
    /** 
     *  @brief   ����һ�η����������ݺ��ӳ�ͳ����Ϣ����λΪus��
     *  
     *  @details    ǰ16Ԫ��Ԥ������ǰ�ֱ�Ϊ����������С�����ƽ����
     *              �����Ԫ��Ϊ������һ���������ݺ�ǰn���������ӳ����ݣ�n��DDS_QualityEvaluationQosPolicy::max_samples���ơ� 
     */
    DDS_LongSeq latency_infos;
}DDS_LinkQualityEvaluationInfo;

/**
 * @struct DDS_QualityEvaluationQosPolicy
 *
 * @ingroup CoreQosStruct
 *
 * @brief   ����ͨ����������QoS���ԡ�
 * 
 * @details ����ͨ����������QoS��DDS��ʹ��������������µ����� DDS_BuiltinQualityEvaluationTopic ����
 *          �������� DDS_QualityEvaluationInfo ���������� @period Ϊ���ڷ�������ǰ�����ݶ��߶˽���ͳ�ơ�
 */
typedef struct DDS_QualityEvaluationQosPolicy
{
    /** @brief   ͳ����Ϣ�������ڣ�Ĭ��Ϊ DDS_DURATION_INFINITE_SEC ��ʾ������ͳ�ơ� */
    DDS_Duration_t period;
    /** @brief   �ϲ����͵ĸ�����Ĭ��Ϊ-1��ʾ�������������ݺϲ����͡� */
    DDS_Long batch;
    /** @brief   �Ƿ�������õ�NTP��ʱ����ʱ�ӡ� */
    DDS_Boolean adjust_time;
    /** @brief   DDS_QualityEvaluationInfo::latency_infos Ԥ����ĳ��ȣ������ڽ�������ʱ��̬����ռ䣬Ĭ��Ϊ1024�� */
    DDS_ULong initial_samples;
    /** @brief   ͳ�������ڣ�ͳ�Ƶ��������������Ĭ��Ϊ1024�� */
    DDS_ULong max_samples;
}DDS_QualityEvaluationQosPolicy;

#endif /* _ZRDDS_INCLUDE_QUALITY_EVALUATION */

#endif /* QualityEvaluationQosPolicy_h__*/
