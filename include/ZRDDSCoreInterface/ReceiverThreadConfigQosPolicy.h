/**
 * @file:       ReceiverThreadConfigQosPolicy.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#ifndef ReceiverThreadConfig_h__
#define ReceiverThreadConfig_h__

/**
 * @enum DDS_ReceiverThreadKind
 *
 * @ingroup CoreQosStruct
 *
 * @brief   ������������½����̲߳��ԡ�
 *
 * @details �����߳�����ZRDDS��Э��ջ�������ݲ����������̴߳�Э��ջ��ȡ��ԭʼ���ݺ���Ҫ��ԭʼ���ݽ��з����л��ͷַ���
 *          ��Э��ջ�л�ȡ�������ݰ������÷��ֱ��ĺ��û������ݱ��ģ�����ʹ�ò�ͬ�Ķ˿ڣ�Ϊ����DDS��������Ӱ���û����ݱ��ĵĴ���
 *          ZRDDS���ø�QoS���û��ṩ���ý����߳�ģ�͵��������ڵ�������£�ZRDDS��������¼���˿ڣ�
 *          1. ���������鲥���ݰ���  
 *          2. �����ڲ��������ݰ���  
 *          3. �����û��������ݰ���
 */

typedef enum DDS_ReceiverThreadKind
{
    /**   
     * @brief  ÿ���˿�һ�������̡߳� 
     *
     * @ingroup CoreQosStruct
     *          
     * @details Ĭ�����ͣ�������������õ�ÿ���˿ھ�ʹ�õ������̼߳���������Ĭ�������Ϊ �ܽ����߳��� = �û���ЧIP���� * 3��
     */
    DDS_THREAD_PER_PORT,

    /**   
     * @brief  ÿ������һ�������̣߳����õ�һ���̣߳��û���һ���̡߳�
     *
     * @ingroup CoreQosStruct
     *          
     * @details ������������õ�ÿ��˿�ʹ�õ������̼߳���������Ĭ������� �ܽ����߳��� = 2��
     */
    DDS_THREAD_PER_KIND,

    /**   
     * @brief  ���еĶ˿ڶ�ʹ��һ���̡߳� 
     *
     * @ingroup CoreQosStruct
     *          
     * @details ������������õ����ж˿�ʹ�õ������̼߳���������Ĭ������� �ܽ����߳��� = 1��
     */
    DDS_THREAD_ALL_PORTS 
}DDS_ReceiverThreadKind;

/**
 * @struct DDS_ReceiverThreadConfigQosPolicy
 *
 * @ingroup CoreQosStruct
 *
 * @brief   ������ߵĽ����߳����á�
 *
 * @details ��QoS��������������ߵĽ����̣߳�receive_buffer_lengthĬ��Ϊ0����ʾ���ջ�������С��ʹ��Э�������Ƭ��Сȷ��������0ʱ���ɸó�Ա��������Э���µĽ��ջ�������С��
 *          ��Ա | Ĭ��ֵ | ƥ������� | ��Ч�Լ�� | �����Լ�� | �ɱ��Լ��
 *          --- | --- | --- | --- | --- | ---
 *          #kind | DDS_THREAD_ALL_PORTS | �� | �� | �� | ���ɱ�
 *          #receive_buffer_length | 0 | �� | �� | �� | ���ɱ�
 */

typedef struct DDS_ReceiverThreadConfigQosPolicy
{
    /** @brief   �����̵߳����͡� */
    DDS_ReceiverThreadKind kind;
    /** @brief   ���ý��ջ������� */
    DDS_Long receive_buffer_length;
#ifdef _LINUX
    /** @brief   �Ƿ�ѡ��select��·����ģʽ������Ϊfalse����ʹ��epollģʽ�� */
    DDS_Boolean use_select;
#endif // _LINUX
}DDS_ReceiverThreadConfigQosPolicy;

#endif /* ReceiverThreadConfig_h__ */
