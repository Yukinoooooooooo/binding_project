/**
 * @file:       LivelinessLostStatus.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#if !defined(_LIVELINESSLOSTSTATUS_H)
#define _LIVELINESSLOSTSTATUS_H

#include "OsResource.h"

#ifdef _ZRDDS_INCLUDE_LIVELINESS_QOS

/**
 * @struct DDS_LivelinessLostStatus
 *
 * @ingroup CoreStatusStruct
 *
 * @brief   ����д�ߴ���Զ�ʧ״̬��
 *
 * @details ������д�ߵ� DDS_LivelinessQosPolicy::kind ����Ϊ 
 *          #DDS_MANUAL_BY_PARTICIPANT_LIVELINESS_QOS ���� #DDS_MANUAL_BY_TOPIC_LIVELINESS_QOS ʱ��
 *          ����д�߻����û�����Ϊ���Ƿ��ڹ涨��ʱ�������ڵ��� DataWriter::write�ȷ�������������Ĵ���ԣ�
 *          �Ƿ����� DDS_LivelinessQosPolicy �����ã������⵽����������޸�����Ĵ���Զ�ʧ״̬
 *          ����ȡ�����μ� #DDS_StatusKind ��
 */

typedef struct DDS_LivelinessLostStatus
{
    /** @brief   ��⵽����Զ�ʧ���ܴ����� */
    DDS_Long total_count;
    /** @brief   ����һ�λ�ȡ��״̬�������¼����ڼ�⵽����Զ�ʧ�Ĵ����� */
    DDS_Long total_count_change;
}DDS_LivelinessLostStatus;

#endif /* _ZRDDS_INCLUDE_LIVELINESS_QOS */

#endif  /*_LIVELINESSLOSTSTATUS_H*/
