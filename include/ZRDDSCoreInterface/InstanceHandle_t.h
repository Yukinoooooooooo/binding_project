/**
 * @file:       InstanceHandle_t.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#ifndef DDS_InstanceHandle_t_h__
#define DDS_InstanceHandle_t_h__

#include "OsResource.h"
#include "ZRSequence.h"

/**
 * @struct DDS_InstanceHandle_t
 *
 * @ingroup CoreBaseStruct
 *          
 * @brief   ������ʾһ��ʵ�����һ������ʵ����
 *
 * @details  - Ψһ��ʶ������ߡ�����д�ߡ����ݶ��ߵ�ʵ�壻
 *           - Ψһ��ʶ����ʵ������ֵ��ͬ����������16�ֽڵ�����ȡ���ڼ�ֵCDR���л��Ľ��������16�ֽڲ��㣬����16�ֽ���ȡ���л������MD5��.
 */

typedef struct DCPSDLL DDS_InstanceHandle_t
{
    /**   
     * @brief   16�ֽ�Ψһ��ʶʵ�塣
     * 
     * @details ���У�
     *          - [0-3]�ֽڱ�ʶʵ�������ڵ�IP��
     *          - [4-7]�ֽڱ�ʶʵ����������(����)ID��
     *          - [8-11]�ֽڱ�ʶʵ�������������ID(�������ID�ڽ����ڴ�1��ʼ����)��  
     *          - [12-14]�ֽڱ�ʶʵ��ID��  
     *          - 15�ֽڱ�ʶʵ�����ͣ�  
     *              - ��2λ��ʶʵ�����ࣺ  
     *                  - 0x00���û��Զ���ʵ�壻  
     *                  - 0x11��DDS����ʵ�壻  
     *                  - 0x01�������Զ���ʵ�壻  
     *              - ��6λ��ʶʵ�����ͣ�  
     *                  - 0x02��ʾʵ��Ϊ����Key������д�ߣ�  
     *                  - 0x03��ʾʵ��Ϊ��Key������д�ߣ�
     *                  - 0x07��ʾʵ��Ϊ����Key�����ݶ��ߣ�  
     *                  - 0x04��ʾʵ��Ϊ��Key������д���ߣ�
     */
    DDS_Octet value[16];
    /** 
     * @brief   �ó�ԱΪtrueʱ��ʾvalueֵ��Ч�������DDS_InstanceHandle_t��Ч��
     * 
     * @note    ��ʹ��value֮ǰӦ�ж�valid�Ƿ�Ϊtrue��
     */
    DDS_Boolean valid;
#ifdef _ZRDDSCPPINTERFACE

    /**
     * @fn  DDS_Boolean operator==(const DDS_InstanceHandle_t& handle) const;
     *
     * @brief   C++�ӿ������ص���ȱȽϲ��������ȽϹ���μ� ::DDS_InstanceHandle_t_Compare ��
     *
     * @param   handle  ��������
     *
     * @return  true��ʾ������ȣ��������߲��ȡ�
     */

    DDS_Boolean operator==(const DDS_InstanceHandle_t& handle) const;

    /**
     * @fn  DDS_Boolean operator<(const DDS_InstanceHandle_t& handle) const;
     *
     * @brief   C++�ӿ����صıȽϲ��������ȽϹ���μ� ::DDS_InstanceHandle_t_Compare ��
     *
     * @param   handle  ��������
     *
     * @return  true ��ʾthis < handle��false��ʾ this >= handle��
     */

    DDS_Boolean operator<(const DDS_InstanceHandle_t& handle) const;
#endif
}DDS_InstanceHandle_t;

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @fn  DCPSDLL DDS_Long DDS_InstanceHandle_t_Compare(const DDS_InstanceHandle_t* handle1, const DDS_InstanceHandle_t* handle2);
 *
 * @ingroup CoreBaseFunction
 *
 * @brief   C���� DDS_InstanceHandle_t �ȽϺ�����
 *
 * @details �ȽϹ���������Ч��DDS_InstanceHandle_t����ȣ���С��������Ч DDS_InstanceHandle_t ��
 *
 * @param   handle1 ������1��
 * @param   handle2 ������2��
 *
 * @return  0��ʾ��ȣ�1��ʾhandle1 &gt; handle2��-1��ʾhandle1 &lt; handle2��
 */

DCPSDLL DDS_Long DDS_InstanceHandle_t_Compare(const DDS_InstanceHandle_t* handle1, const DDS_InstanceHandle_t* handle2);

/**
 * @brief   ��ʾ��Ч�� DDS_InstanceHandle_t �� 
 *
 * @ingroup CoreVar
 */
DCPSDLL extern const DDS_InstanceHandle_t DDS_HANDLE_NIL_NATIVE;

/**
 * @typedef DDS_InstanceHandle_t DDS_KeyHash_t
 * 
 * @ingroup CoreBaseStruct
 *
 * @brief   DDS_KeyHash_t ��Ϊ�� DDS_InstanceHandle_t ��Ϊ����ʵ����Ψһ��ʶʱ�ı�����
 *
 * @note    �û�������ʽ��ʹ�øýṹ�塣
 */

typedef DDS_InstanceHandle_t DDS_KeyHash_t;

/**
 * @struct DDS_InstanceHandleSeq 
 *
 * @ingroup CoreBaseStruct
 *
 * @brief   ���� DDS_InstanceHandle_t ���������ͣ��μ� #DDS_USER_SEQUENCE_CPP ��
 */

DDS_SEQUENCE_CPP(DDS_InstanceHandleSeq, DDS_InstanceHandle_t);

#ifdef __cplusplus
}
#endif

#endif /* DDS_InstanceHandle_t_h__*/
