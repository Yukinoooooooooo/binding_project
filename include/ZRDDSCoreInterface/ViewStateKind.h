/**
 * @file:       ViewStateKind.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#ifndef ViewStateKind_h__
#define ViewStateKind_h__

/**
 * @typedef enum DDS_ViewStateKind
 *
 * @ingroup  CoreBaseStruct
 *
 * @brief   ��ö�ٱ����оٳ�������ʵ������ͼ״̬���� DDS_ViewStateMask ���ʹ�á�
 *
 * @details  ��ͼ״̬�����ݶ���Ϊ���������е�ÿ������ʵ��������һ��״̬��Ϣ��ͨ�� DDS_SampleInfo::view_state 
 *           ���ظ��û�����״̬��Ϣ���������ݶ��߶Ը�����ʵ���������Լ���ʵ�����������ڱ仯���ı䡣
 */

typedef enum DDS_ViewStateKind
{
    /**
     * @brief   ��״̬��ʾ���ݶ�����δ���ʹ�������ʵ���µ������������������ʵ�����������֣���NOT_ALIVE״̬���±�ΪALIVE״̬����
     *
     * @ingroup CoreBaseStruct
     */
    DDS_NEW_VIEW_STATE = 0x0001 << 0,
    /**   
     * @brief   ��״̬��ʾ���ݶ��߷��ʹ���ʵ�������ݣ��Ҵ�ʵ��δ�������֣��� 
     *
     * @ingroup CoreBaseStruct
     */
     DDS_NOT_NEW_VIEW_STATE = 0x0001 << 1
}DDS_ViewStateKind;

#endif /* ViewStateKind_h__*/
