/**
 * @file:       QosProfileQosPolicy.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#ifndef QosProfileQosPolicy_h__
#define QosProfileQosPolicy_h__

#include "ZROSDefine.h"
#include "ZRBuiltinTypes.h"

#ifdef _ZRXMLINTERFACE

#ifdef _ZRXMLQOSINTERFACE

/**
 * @struct DDS_QosProfileQosPolicy
 *
 * @ingroup CoreQosStruct
 *
 * @brief   ������Qos�����ļ��йص������
 */
typedef struct DDS_QosProfileQosPolicy
{
    /**   
     * @brief   QoS�����ļ�����·���б�
     * 
     * @details DDS���� #profile_paths ���õ�·���г��Զ�ȡQos�����ļ�, Ĭ��Ϊ���ַ������С�
     *          ÿ��Ԫ�ش���һ����Ի��߾���·���� 
     */
    DDS_StringSeq profile_paths;
}DDS_QosProfileQosPolicy;

#endif /* _ZRXMLQOSINTERFACE */

#endif /* _ZRXMLINTERFACE */

#endif /* QosProfileQosPolicy_h__ */
