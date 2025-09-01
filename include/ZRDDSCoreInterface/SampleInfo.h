/**
 * @file:       SampleInfo.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#ifndef SampleInfo_h__
#define SampleInfo_h__

#include "SampleStateKind.h"
#include "ViewStateKind.h"
#include "InstanceStateKind.h"
#include "Duration_t.h"
#include "InstanceHandle_t.h"
#include "ZRSequence.h"
#include "SequenceNumber_t.h"

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @struct DDS_SampleInfo
 *
 * @ingroup CoreBaseStruct
 *
 * @brief   ���ݶ���Ϊÿһ�����յ�������ά����������Ϣ��
 * 
 * @details ����Ϣ����ʹ�� DataReader::read/take ��ȡ����ʱ��ȡ������������һͬ�ṩ���û���
 */

typedef struct DDS_SampleInfo
{
    /** @brief  ���ݹ���������״̬��*/
    DDS_SampleStateKind sample_state;
    /** @brief  ���ݹ�������ͼ״̬�� */
    DDS_ViewStateKind view_state;
    /** @brief  ���ݹ�����ʵ��״̬�� */
    DDS_InstanceStateKind instance_state;
    /** @brief  ���ݵ�Դʱ����� */
    DDS_Time_t source_timestamp;
    /** @brief  �����ڷ����˵����кš� */
    DDS_SequenceNumber_t write_sequence_number;
    /** @brief  ��������������ʵ����Ψһ��ʶ�� */
    DDS_InstanceHandle_t instance_handle;
    /** @brief  ���ʹ����ݵ�����д�ߵ�Ψһ��ʶ�� */
    DDS_InstanceHandle_t publication_handle;
    /** @brief  ��������������ʵ��״̬�� #DDS_NOT_ALIVE_DISPOSED_INSTANCE_STATE ��� #DDS_ALIVE_INSTANCE_STATE �Ĵ����� */
    DDS_ULong disposed_generation_count;
    /** @brief  ��������������ʵ��״̬�� #DDS_NOT_ALIVE_NO_WRITERS_INSTANCE_STATE ��� #DDS_ALIVE_INSTANCE_STATE �Ĵ����� */
    DDS_ULong no_writers_generation_count;
    /**
     * @brief   �� DataReader::read/take ϵ�з������ص������е�ͬһʵ���������У������ݺ�������ݵĸ�����
     */
    DDS_ULong sample_rank;
    /**
     * @brief   �� DataReader::read/take ϵ�з������ص������е�ͬһʵ���������У�
     *          ���µ����ݣ�MRSIC��������ݵĴ�����generation���
     */
    DDS_ULong generation_rank;
    /**
     * @brief   ��ͬһʵ�������ݣ�����Ҫ����ͬһ�������У��У�
     *          ���µ����ݣ�MRS��������ݵĴ�����generation���
     */
    DDS_ULong absolute_generation_rank;
    /**   
     * @brief   ��ֵΪtrue��ʾΪ��������������������Ϣ��Ӧ������������Ч�� 
     *
     * @warning �û��ڱ���������������ʱ��ʹ����������֮ǰ����Ҫ�ж� valid_data == true ��
     */
    DDS_Boolean valid_data;
    /** @brief  ��������Locator�� */
    void *recive_locator;
    /** @brief  ���ն��кš� */
    DDS_ULong recive_order;
    DDS_Boolean is_batch_end;
}DDS_SampleInfo;

/**
 * @struct DDS_SampleInfoValidMember
 *
 * @brief   ���ڱ�ʾ DDS_SampleInfo �еĳ�Ա�Ƿ���Ч������XML�ӿ��С�
 */

typedef struct DDS_SampleInfoValidMember
{
    DDS_Boolean source_timestamp;
    DDS_Boolean valid_data;
    DDS_Boolean instance_handle;
    DDS_Boolean instance_state;
    DDS_Boolean sample_state;
    DDS_Boolean view_state;
}DDS_SampleInfoValidMember;

/**
 * @struct DDS_SampleInfoSeq 
 *
 * @ingroup CoreBaseStruct
 *
 * @brief   ���� DDS_SampleInfoSeq ���������ͣ��μ� #DDS_USER_SEQUENCE_CPP ��
 */

DDS_SEQUENCE_CPP(DDS_SampleInfoSeq, DDS_SampleInfo);

#ifdef __cplusplus
}
#endif

#endif /* SampleInfo_h__*/
