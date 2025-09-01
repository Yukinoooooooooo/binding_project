/**
 * @file:       SampleStateKind.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#ifndef SampleStateKind_h__
#define SampleStateKind_h__

/**
 * @enum DDS_SampleStateKind
 *
 * @ingroup CoreBaseStruct
 *
 * @brief   �����ͱ�ʾ���������ı���ȡ״̬��
 *
 * @details  ������������ȡ״̬�����ݶ���Ϊ�ײ㱣�������ά����һ��״̬��Ϣ�������������Ƿ��û�ͨ�� 
 *           DataReader::read ϵ�з�����ȡ���ʳɹ��������û� ���� DataReader::return_loan �����黹��������ʱ��
 *           ���ݱ�Ϊ #DDS_READ_SAMPLE_STATE ״̬��
 */

typedef enum DDS_SampleStateKind
{
    /**
     * @brief  �����������Ѿ����û����ʹ���
     *
     * @ingroup CoreBaseStruct
     *
     * @details ��ʾ�û���ͨ�� DataReader::read ϵ�з������ʹ������������Ѿ�ͨ�� DataReader::return_loan �����黹��
     */
     
    DDS_READ_SAMPLE_STATE = 0x0001 << 0,

    /**
     * @brief  ����������δ���û����ʹ���
     *
     * @ingroup CoreBaseStruct
     *
     * @details ��ʾ�û�δ��ͨ�� DataReader::read ϵ�з������ʹ����������߻�δͨ�� DataReader::return_loan �����黹�ռ䡣
     */
    DDS_NOT_READ_SAMPLE_STATE = 0x0001 << 1
}DDS_SampleStateKind;

#endif /* SampleStateKind_h__*/
