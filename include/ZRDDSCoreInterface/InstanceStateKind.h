/**
 * @file:       InstanceStateKind.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#ifndef InstanceStateKind_h__
#define InstanceStateKind_h__

/**
 * @enum    DDS_InstanceStateKind
 *          
 * @ingroup CoreBaseStruct
 *
 * @brief   ��ö�ٱ����оٳ�һϵ�е�ʵ��״̬���� DDS_InstanceStateMask ���ʹ�á�
 *          
 * @details ʵ��״̬�����ݶ���Ϊ�����е�ÿ��ʵ��������һ��״̬��Ϣ��ÿ��������������״̬���μ�
 *          DDS_SampleInfo::instance_state ����״̬��Ϣ������ʵ�����������ڷ����仯���ı䡣
 */
typedef enum DDS_InstanceStateKind
{
    /**
     * @brief   ��״̬��ʾ������������ʵ�����ڴ��״̬��
     *
     * @ingroup CoreBaseStruct
     *          
     * @details �����ݶ��߽��յ��˸�����ʵ����������������������������ʵ����ת��Ϊ��״̬����֪ͨ�û���
     *          ���������������ͣ�
     *          - �����������ݵ���������Ϊ����������  
     *          - �������������ݵ���������Ϊ״̬���������У�  
     *              - �� DataWriter::unregister_instance ����ע��״̬������  
     *              - �� DataWriter::dispose ��������״̬������
     */
    DDS_ALIVE_INSTANCE_STATE = 0x0001 << 0,

    /** @brief  ��״̬��ʾ������������ʵ�����ڱ�����״̬��  
     *
     * @ingroup CoreBaseStruct
     *
     * @details �����ݶ��߽��յ�������״̬����ʱ��
     *          - ���ԭ��Ϊ ::DDS_ALIVE_INSTANCE_STATE ״̬��������������ʵ����ת��Ϊ��״̬����֪ͨ�û���  
     *              �û�ͨ�� DataReader::read/take �������Ի�ȡ���¼���
     *          - ���ԭ��Ϊ ::DDS_NOT_ALIVE_DISPOSED_INSTANCE_STATE ״̬��������������ʵ����ת��Ϊ��״̬����֪ͨ�û���  
     *          - ���ԭ��Ϊ ::DDS_NOT_ALIVE_NO_WRITERS_INSTANCE_STATE ״̬��������������ʵ��״̬����ı䣬��֪ͨ�û���  
     */
    DDS_NOT_ALIVE_DISPOSED_INSTANCE_STATE = 0x0001 << 1,

    /** @brief  ��״̬��ʾ������������ʵ�����ڱ�ע��״̬��  
     *
     * @ingroup CoreBaseStruct
     *
     * @details �����ݶ��߽��յ���ע��״̬����ʱ��
     *          - ���ԭ��Ϊ ::DDS_ALIVE_INSTANCE_STATE ���Ҵ�����д��Ϊ���һ���������ʵ������������д�ߣ�  
     *              ��״̬��������������ʵ����ת��Ϊ��״̬����֪ͨ�û��� ����������д���������ʵ���������򲻸ı�״̬��
     *              ����д��������ʵ��������ָ������ʵ��������������ʵ���µ��������ݣ�����������������״̬������ 
     *          - ���ԭ��Ϊ ::DDS_NOT_ALIVE_DISPOSED_INSTANCE_STATE ״̬��������������ʵ��״̬����ı䣬��֪ͨ�û���  
     *          - ���ԭ��Ϊ ::DDS_NOT_ALIVE_NO_WRITERS_INSTANCE_STATE ״̬��������������ʵ��״̬����ı䣬��֪ͨ�û���  
     */
    DDS_NOT_ALIVE_NO_WRITERS_INSTANCE_STATE = 0x0001 << 2
}DDS_InstanceStateKind;

#endif /* InstanceStateKind_h__*/
