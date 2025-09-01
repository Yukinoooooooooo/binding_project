/**
 * @file:       DomainParticipantQos.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#ifndef DomainParticipantQos_h__
#define DomainParticipantQos_h__

#include "UserDataQosPolicy.h"
#include "EntityFactoryQosPolicy.h"
#include "ReceiverThreadConfigQosPolicy.h"
#include "TransportConfigQosPolicy.h"
#include "ThreadCoreAffinityQosPolicy.h"
#include "DiscoveryConfigQosPolicy.h"
#include "DDSMsgStatisticsInfoQosPolicy.h"
#include "RapidIOControllerQosPolicy.h"
#include "PropertyQosPolicy.h"
#ifdef _ZRDDS_INCLUDE_GATEWAY
#include "GatewayQosPolicy.h"
#endif // _ZRDDS_INCLUDE_GATEWAY

/**
 * @struct DDS_DomainParticipantQos
 *
 * @ingroup CoreQosStruct
 *
 * @brief   ����������ߵ�QoS���á�
 */

typedef struct DDS_DomainParticipantQos
{
#ifdef _ZRDDS_INCLUDE_USER_DATA_QOS
    /** @brief   �������Я����Ϣ���á� */
    DDS_UserDataQosPolicy user_data;
#endif //_ZRDDS_INCLUDE_USER_DATA_QOS
    /** @brief   ʵ�幤�����á� */
    DDS_EntityFactoryQosPolicy entity_factory;
    /** @brief   �����߳��������á�  */
    DDS_ReceiverThreadConfigQosPolicy receiver_thread_config;
    /**   
     * @brief   RTPX���ĵ�Ŀ�ĵ�ַ���á� 
     *
     * @details ����ZRDDS�ڲ�ͬ����ж˿ڸ��룬������Ҫ������ʱ��ȡDDSϵͳ�е����п��ܵ������Ϣ��Ӧ�ó������磺�����Ӧ�ã�
     *          ��Ҫ�������ָ��룬ZRDDSʹ��RTPX������ɸù��ܣ�ZRDDS���ⷢ���������������Ϣʱ��ͬʱ�� #domain_destination_addresses
     *          ��ַ�б��з���RTPX���ģ����ն��յ�RTPX����ʱ������� DDS::DomainParticipantListener::on_domain_received 
     *          ����֪ͨ�û���ĳ�����µ����ݵ��Ĭ��Ϊudpv4://239.255.0.1//7400��
     *          ���鲥��ַΪ239.255.0.1���˿�ͨ��RTPSЭ����㡣 
     */
    DDS_TransportConfigQosPolicy domain_destination_addresses;
    /**   
     * @brief   RTPX���ĵļ�����ַ�� 
     *          
     * @details һ������Ӧ�����øõ�ַ����̬����DDSϵͳ�еĲ�ͬ��Ĭ��Ϊudpv4://239.255.0.1//7400��
     *          ���鲥��ַΪ239.255.0.1���˿�ͨ��RTPSЭ����㡣 
     */
    DDS_TransportConfigQosPolicy domain_receive_addresses;
    /** @brief  SPDPЭ���Դ��ַ�б�
    *
    * @details Ĭ��Ϊudpv4://default//0�������е�ַ�����鲥���˿���ϵͳ�Զ����䡣
    */
    DDS_TransportConfigQosPolicy pdp_send_addresses;
    /** @brief  SPDPЭ���Ŀ�ĵ�ַ�б�  
     * 
     * @details Ĭ��Ϊudpv4://239.255.0.1//0�����鲥��ַΪ239.255.0.1���˿�ͨ��RTPSЭ����㡣 
     */
    DDS_TransportConfigQosPolicy pdp_destination_addresses;
    /**   
     * @brief   SPDPЭ��ļ�����ַ�б�
     *  
     * @details Ĭ��Ϊudpv4://239.255.0.1//0�����鲥��ַΪ239.255.0.1���˿�ͨ��RTPSЭ����㡣 
     */
    DDS_TransportConfigQosPolicy pdp_receive_addresses;
    /**   
     * @brief   ���÷���Э��SEDPʹ�õĵ�ַ�����б�
     *          
     * @details Ĭ��Ϊudpv4://default//0����������ַ���˿�ͨ��RTPSЭ����㡣 
     */
    DDS_TransportConfigQosPolicy metatraffic_receive_addresses;
    /**   
     * @brief   �û�����ʹ�õĵ�ַ�����б�
     *           
     * @details Ĭ��Ϊudpv4://default//0����������ַ���˿�ͨ��RTPSЭ����㡣 
     */
    DDS_TransportConfigQosPolicy usertraffic_receive_addresses;
    /** @brief   DDS�߳�/�������������á� */
    DDS_ThreadCoreAffinityQosPolicy thread_core_affinity;
    /** @brief   SPDP�������á� */
    DDS_DiscoveryConfigQosPolicy discovery_config;
#ifdef _ZRDDS_INCLUDE_MSGSTATISTICSINFO_QOS
    /** @brief   ���ñ���ͳ����Ϣ�� */
    DDS_MsgStatisticsInfoQosPolicy message_staticstics_info_config;
#endif //_ZRDDS_INCLUDE_MSGSTATISTICSINFO_QOS
    /**   
     * @brief   ����RTPS���ĵĶ���true��ʾС�ˣ�Ĭ�ϣ���false��ʾ��ˡ� 
     * 
     * @note    �����ڴ�˻��������ó�false�����ṩ���л��Լ������л������ܣ����ɱ䡣 
     */
    DDS_Boolean rtps_message_little_endian;
#ifdef _ZRDDS_RIO
    /** @brief The rapidio controller */
    DDS_RapidIOControllerQosPolicy rapidio_controller;
#endif /* _ZRDDS_RIO */
    /** @brief   ��ʵ��������б� */
    DDS_PropertyQosPolicy property;
#ifdef _ZRDDS_INCLUDE_GATEWAY
    /** @brief   ��·�ɷ�������á� */
    DDS_GatewayQosPolicy gateway;
#endif // _ZRDDS_INCLUDE_GATEWAY
}DDS_DomainParticipantQos;

#endif /* DomainParticipantQos_h__*/
