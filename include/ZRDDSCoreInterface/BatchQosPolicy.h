/**
 * @file:       BatchQosPolicy.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#ifndef BatchQosPolicy_h__
#define BatchQosPolicy_h__

#include "OsResource.h"
#include "Duration_t.h"

/**
 * @struct DDS_BatchQosPolicy
 *
 * @ingroup CoreQosStruct
 *
 * @brief   �����������á�
 *
 * @details ���û����ʹ������Ƚ϶̵�����ʱ��Ϊ�˾�������������������Խ����С���ݰ��ϲ���һ���ϴ����ݰ����ͣ����������͡�
 *          ��Ա | Ĭ��ֵ | ƥ������� | ��Ч�Լ�� | �����Լ�� | �ɱ��Լ��
 *          --- | --- | --- | --- | --- | ---
 *          #enable | false | �� | �� | �� | ���ɱ�
 *          #max_data_bytes | 1024 | �� | DDS_BatchQosPolicy::max_data_bytes > 0 | �� | ���ɱ�
 *          #max_meta_data_bytes | #LENGTH_UNLIMITED | �� | �� | �� | ���ɱ�
 *          #max_samples | #LENGTH_UNLIMITED | �� | DDS_BatchQosPolicy::max_samples > 0 | �� | ���ɱ�
 *          #max_flush_delay | #INFINITE_DURATION | �� | �� | !#enable OR #max_flush_delay == #INFINITE_DURATION OR !DDS_AsynchronousPublisherQosPolicy::disable_asynchronous_batch | ���ɱ�
 *          #source_timestamp_resolution | #INFINITE_DURATION | �� | �� | �� | ���ɱ�
 *          #thread_safe_write | false | �� | �� | �� | ���ɱ�
 *
 */

typedef struct DDS_BatchQosPolicy
{
    /** @brief   �Ƿ�ʹ���������͡� */
    DDS_Boolean enable;
    /** @brief   ��������ʱ��������ۼƳ��ȣ������������ȴﵽ��ֵʱ�ᴥ��ˢ�¡� */
    DDS_Long max_data_bytes;
    /** @brief   ��δʹ�� */
    DDS_Long max_meta_data_bytes;
    /** @brief   ������������������������������������ﵽ��ֵʱ�ᴥ��ˢ�¡� */
    DDS_Long max_samples;
    /** @brief   ������ӳ٣�ÿ���ﵽ��ʱ��ʱ�ᴥ��ˢ�£�����������ʽˢ��ʱ��������ˢ��ʱ�䡣 */
    DDS_Duration_t max_flush_delay;
    /** @brief   �����������͵�Դʱ����ֱ��ʣ����������͵����ݰ�ʱ�����ǰһ�����ֵ�ʱ���С�ڸ�ֵʱ�����ݰ������ٰ���������ʱ��������������������ʱ����� */
    DDS_Duration_t source_timestamp_resolution;
    /** @brief   ��δʹ�á� */
    DDS_Boolean thread_safe_write;
}DDS_BatchQosPolicy;

#endif /* BatchQosPolicy_h__*/
