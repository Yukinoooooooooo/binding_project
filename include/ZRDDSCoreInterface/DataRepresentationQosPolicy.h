/**
 * @file:       DataRepresentationQosPolicy.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#ifndef DataRepresentationQosPolicy_h__
#define DataRepresentationQosPolicy_h__

#include "OsResource.h"
#include "ZRBuiltinTypes.h"

/**
 * @def DDS_XCDR_DATA_REPRESENTATION();
 *
 * @ingroup CoreMacro
 *
 * @brief   ���紫�������Ϊʹ��CDR��ʽ���л����������
 */

#define DDS_XCDR_DATA_REPRESENTATION 0x0000

/**
 * @def DDS_XML_DATA_REPRESENTATION();
 *
 * @ingroup CoreMacro
 *
 * @brief   ���紫�������Ϊʹ��XML��ʽ��ʽ���л���������
 */

#define DDS_XML_DATA_REPRESENTATION 0x0001

/**
 * @struct DDS_DataRepresentationQosPolicy
 *
 * @ingroup CoreQosStruct
 *
 * @brief   ���ݷ�װ��ʽ����QoS��
 * @details 
 *          - �����������ݣ�
 *              - ���ݷ�װ�ı�ʶ��
 *              - ����д�ߡ����ݶ�����֧�ֵķ�װ�����Լ���ƫ�õķ�װ���ͣ�  
 *              - ���ڸ����ķ�װ���࣬������д��/���ݶ���֮��ѡȡ���ʵķ�װ�����ѡ�񷽷���  
 *          - ÿ�����⡢����д�ߡ����ݶ��߶�Ӧ�ú������Qos��  
 *          - �����ṩ�������󷽵����壻  
 *          - ��ʹ��֮����ʹ�ܣ�  
 *          - ����д�߶˽����ṩһ�����ݷ�װ��ʶ����Ȼ�ṹΪһ���б������Զ����һ��Ԫ��֮������壩  
 *          - ���ݶ��߶�����һ�ֻ��߶��ַ�װ��ʽ��  
 *          - �����ԣ����ݶ��߶˰�������д�߶˵ķ�װ��ʽ;  
 *          - Ĭ��Ϊ�յ��б��ȼ���ֻ��һ��XCDRԪ��;  
 *              
 * @warning ��QoS��δʵ�֡�
 */

typedef struct DDS_DataRepresentationQosPolicy 
{
    /** @brief   ���ݷ�װ��ʶ�б� */
    DDS_ShortSeq value;
}DDS_DataRepresentationQosPolicy ;

#endif /* DataRepresentationQosPolicy_h__*/
