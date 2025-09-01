/**
 * @file:       DataWriterMessageModeQosPolicy.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */


#ifndef DataWriterMessageModeQosPolicy_h__
#define DataWriterMessageModeQosPolicy_h__

#include "OsResource.h"

/**
 * @struct DDS_DataWriterMessageModeQosPolicy
 *
 * @ingroup CoreQosStruct
 *
 * @brief �ṩ����DataWriter��Ϣ����Ĺ��ܡ�
 *
 * @details 
 *          ��Ա | Ĭ��ֵ | ƥ������� | ��Ч�Լ�� | �����Լ�� | �ɱ��Լ��
 *          --- | --- | --- | --- | --- | ---
 *          #without_timestamp | false | �� | �� | DDS_DataWriterQos::destination_order::kind == #DDS_BY_SOURCE_TIMESTAMP_DESTINATIONORDER_QOS && ! #without_timestamp | ���ɱ�
 *          #without_inlineQos | false | �� | �� | �� | ���ɱ�
 *          #disallow_message_coalesce | false | �� | �� | �� | ���ɱ�
 *          #message_header_coalesce | false | �� | �� | �� | ���ɱ�
 *          #enable_raw_transfer | false | �� | �� | �� | ���ɱ�
 *
 */
typedef struct DDS_DataWriterMessageModeQosPolicy
{
    /** @brief DataWriter���͵����ݰ��Ƿ����ʱ����� */
    DDS_Boolean without_timestamp;
    /** @brief DataWriter���͵����ݰ��Ƿ����InlineQos��ע�⣺��ʹ�ر���InlineQos���Ի����һЩ��Ҫ��InlineQos�� */
    DDS_Boolean without_inlineQos;
    /** @brief DataWriter�Ƿ�����ϲ����ݰ���������Nack����ʱ��DataWriter�᳢�Խ����С�����ݰ��ϲ���ͬһ��������з��ͣ������������������ϲ�������ʹ�ø�QoS�رմ˹��ܡ� */
    DDS_Boolean disallow_message_coalesce;
    /** @brief DataWriter��������ʱ���Ƿ�Ԥ���ռ佫����Ϣͷ������Timestamp�����û�����д��ͬһ�黺�档��ʹ���㿽�����ͣ� DDS_ZeroCopyBytes ��ʱ��ֱ�����ø�ѡ� */
    DDS_Boolean message_header_coalesce;
#ifdef _ZRDDS_ENABLE_RAW_TRANSFER
    /** @brief ������Э�����ݴ��䣬��������ѡ��ʱ�����������ݽ����ٰ���RTPS����ͷ���Ӷ����ٹ�������ͷ�Ŀ�������ʱDataReader����ʹ��Raw��ַ���ã��� DDS_TransportConfigQosPolicy ����
     *         ��DataReader������Raw��ַ���ö�DataWriterδ���ø����ã���ʹ��DataReader���õ�Raw��ַ��Ч����DataReaderδ����������ַ�������޷������������ݡ�
     *         ͬʱ���ø�ѡ����ζ�ŷ���RTPSЭ�����ṩ�Ŀɿ����书�ܣ��������ŵ�������ɵ����ݶ�ʧ�⣬�������ٶȸ��ڽ����ٶȣ������ڽ��շ��������ݸ��ǵ����⡣ 
     */
    DDS_Boolean enable_raw_transfer;
#endif // _ZRDDS_ENABLE_RAW_TRANSFER
}DDS_DataWriterMessageModeQosPolicy;

#endif /* DataWriterMessageModeQosPolicy_h__*/
