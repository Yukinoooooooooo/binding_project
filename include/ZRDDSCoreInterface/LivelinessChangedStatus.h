/**
 * @file:       LivelinessChangedStatus.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#if !defined(_LIVELINESSCHANGEDSTATUS_H)
#define _LIVELINESSCHANGEDSTATUS_H

#include "InstanceHandle_t.h"

#ifdef _ZRDDS_INCLUDE_LIVELINESS_QOS

/**
 * @struct DDS_LivelinessChangedStatus
 *
 * @ingroup CoreStatusStruct
 *
 * @brief   ����д�ߴ���Ա仯״̬��
 *          
 * @details ZRDDS����� DDS_LivelinessQosPolicy �������д�ߵĴ������Ϣ�������ݶ��߼�⵽��֮ƥ���
 *          ����д�ߵĴ������Ϣ�����仯ʱ����ά�����������д�ߴ���Ա仯״̬��ע�⣬��ĳ������д�߲���������ݶ���ƥ��ʱ
 *          ����ɾ�����������������д�ߵĴ���Բ���ͳ�Ƶķ�Χ�ڣ��ʶ�Ӧע����������д��ʧ���Լ���ɾ����������Ĳ��
 *          �¼� | #alive_count �仯�� | #not_alive_count �仯�� | #alive_count_change �仯�� | #not_alive_count_change �仯��
 *          --- | --- | --- | --- | ---
 *          ƥ���µ�����д�� | 1 | 0 | 1 | 0
 *          �Ѿ�ƥ�������д�ߴ�ʧ��״̬��Ϊ��� | 1 | -1 | 1 | -1
 *          ���ƥ������д�� | -1 | 0 | -1 | 0
 *          �Ѿ�ƥ�������д�ߴӴ��״̬��Ϊʧ�� | -1 | 1 | -1 | 1
 *          �û���ȡ��״̬�ķ�ʽ�μ� ::DDS_StatusKind ��
 */

typedef struct DDS_LivelinessChangedStatus
{
    /** @brief   ������ݶ���ƥ��Ĵ�������д�ߵ������� */
    DDS_Long alive_count;
    /** @brief   ������ݶ���ƥ��ķǴ�������д�ߵ������� */
    DDS_Long not_alive_count;
    /** @brief   ����һ�λ�ȡ��״̬�������¼�����������ݶ���ƥ��Ĵ�������д�߱�Ϊ���״̬��������������д�ߣ��ĸ����� */
    DDS_Long alive_count_change;
    /** @brief   ����һ�λ�ȡ��״̬�������¼�����������ݶ���ƥ��Ĵ�������д�߱�Ϊ�Ǵ��״̬�����߽��ƥ������д�ߣ��ĸ����� */
    DDS_Long not_alive_count_change;
    /** @brief   ���һ��Ӱ������ֵ������д�ߵ�Ψһ��ʶ�� */
    DDS_InstanceHandle_t last_publication_handle;
}DDS_LivelinessChangedStatus;

#endif /* _ZRDDS_INCLUDE_LIVELINESS_QOS */

#endif  /*_LIVELINESSCHANGEDSTATUS_H*/
