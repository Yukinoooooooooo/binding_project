/**
 * @file:       AsynchronousPublisherQosPolicy.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#ifndef AsynchronousPublisherQosPolicy_h__
#define AsynchronousPublisherQosPolicy_h__

#include "OsResource.h"
#include "ZRBuiltinTypes.h"

/**
 * @struct DDS_AsynchronousPublisherQosPolicy
 *
 * @ingroup CoreQosStruct
 *
 * @brief   ����Publisher�Ƿ�ʹ���첽�������ݻ��첽�������͵�QoS��
 *
 * @details Ĭ������£�DDS��������ʱ��ʹ���û����÷��ͽӿڵ��߳�ֱ�ӽ����ݷ��͵�����Э���У�
 *          �����ݰ��ϴ�ʱ����������û��̵߳ĳ�ʱ��������Ϊ�˱�������������������ʹ���첽���͡�
 *          �������첽����ʱ�������߻Ὺ�����̷߳������ݡ�
 *          ���û����ʹ������Ƚ϶̵�����ʱ��Ϊ�˾�������������������Խ����С���ݰ��ϲ���һ���ϴ����ݰ����ͣ����������͡�
 *          ��Ա | Ĭ��ֵ | ƥ������� | ��Ч�Լ�� | �����Լ�� | �ɱ��Լ��
 *          --- | --- | --- | --- | --- | ---
 *          #disable_asynchronous_write | false | �� | �� | DDS_PublishModeQosPolicy::kind == DDS_SYNCHRONOUS_PUBLISH_MODE_QOS | ���ɱ�
 *          #disable_asynchronous_batch | false | �� | �� | DDS_BatchQosPolicy::enable == false OR DDS_BatchQosPolicy::max_flush_delay == #INFINITE_DURATION | ���ɱ�
 *
 */

typedef struct DDS_AsynchronousPublisherQosPolicy
{
    /** @brief   �Ƿ�����첽����ģʽ�� */
    DDS_Boolean disable_asynchronous_write;
#ifdef _ZRDDS_INCLUDE_BATCH
    /** @brief   �Ƿ�����첽��������ģʽ�� */
    DDS_Boolean disable_asynchronous_batch;
#endif // _ZRDDS_INCLUDE_BATCH
}DDS_AsynchronousPublisherQosPolicy;

#endif /* AsynchronousPublisherQosPolicy_h__*/
