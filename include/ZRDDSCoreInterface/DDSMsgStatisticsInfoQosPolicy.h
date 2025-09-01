/**
 * @file:       DDSMsgStatisticsInfoQosPolicy.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#ifndef DDSMsgStatisticsInfoQosPolicy_h__
#define DDSMsgStatisticsInfoQosPolicy_h__

#include "OsResource.h"
#include "Duration_t.h"

#ifdef _ZRDDS_INCLUDE_MSGSTATISTICSINFO_QOS

/**
 * @struct DDS_MsgStatisticsInfoQosPolicy
 *
 * @ingroup CoreQosStruct
 *
 * @brief   ʵ�屨��ͳ����Ϣ�������á�
 *
 * @details Ϊ�˸��õص���DDSϵͳ��DDSϵͳ�ṩ��ȷ��ʵ��ı����Լ��û��������͡�����������ͳ�ƣ�
 *          �ù�����Ҫ��DDS�����������ʹ�á�
 *          ��Ա | Ĭ��ֵ | ƥ������� | ��Ч�Լ�� | �����Լ�� | �ɱ��Լ��
 *          --- | --- | --- | --- | --- | ---
 *          #enable | false | �� | �� | �� | �ɱ�
 *          #send_period | DDS_Duration_t(1, 0) | �� | �� | �� | �ɱ�
 */

typedef struct DDS_MsgStatisticsInfoQosPolicy 
{
    /** @brief   �����Ƿ�ʹ�ܱ���ͳ�ƹ��ܡ�*/
    DDS_Boolean enable;
    /** @brief   ����ͳ�ƽ���ķ������ڡ� */
    DDS_Duration_t send_period;
}DDS_MsgStatisticsInfoQosPolicy;

#endif /* _ZRDDS_INCLUDE_MSGSTATISTICSINFO_QOS */

#endif /* DDSMsgStatisticsInfoQosPolicy_h__ */
