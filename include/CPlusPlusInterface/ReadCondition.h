/**
 * @file:       ReadCondition.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#if !defined(_READCONDITION_H)
#define _READCONDITION_H

#include "Condition.h"

struct ReadConditionImpl;

namespace DDS {

class ReadCondition;
#ifdef _ZRDDS_INCLUDE_READ_CONDITION

class DataReader;

/**
 * @class   ReadCondition
 *
 * @ingroup CppSubscription
 *
 * @brief   �������ZRDDS�еĶ�ȡ����@ref waitset-introduction ��
 *          
 * @details ZRDDS�����ݶ���Ϊÿ���洢������������ά������״̬��
 *          - #DDS_SampleStateKind ;  
 *          - #DDS_ViewStateKind ;  
 *          - #DDS_InstanceStateKind ;
 *          
 *          �����ȡ���� ReadCondition(sampleMask, viewMask, instanceMask)��������������ͬʱ������������������
 *          - #DDS_SampleStateKind ���� sampleMask ����ʾ��״̬�����У�
 *          - �� #DDS_ViewStateKind ���� viewMask ����ʾ��״̬�����У�
 *          - �� #DDS_InstanceStateKind ���� instanceMask ����ʾ��״̬�����У�
 *          ��ȡ��������ͬʱ��ʾ������״̬����ȡ������Ҫ�������ط�ʹ�ã�
 *          1. ��������-�ȴ�ģ��@ref waitset-introduction �У������ݶ����д��� DDS::ReadCondition ��ָ��״̬������  
 *              �������ϲ�Ϊ��ʱ����������������  
 *          2. ���� @ref read-take ϵ�з��������� sample_mask��view_mask��instance_mask��  
 *              ���������ڶ�ȡ���ݶ����д��� DDS::ReadCondition ��ָ��״̬�������������ϡ�
 */

class DCPSDLL ReadCondition : public Condition
{
public:

    /**
     * @fn  virtual DataReader* ReadCondition::get_datareader() = 0;
     *
     * @brief   ��ȡ�ö�ȡ�������������ݶ��ߡ�
     *
     * @return  ָ�򴴽��ö�ȡ���������ݶ��߶���
     */

    virtual DataReader* get_datareader() = 0;

    /**
     * @fn  virtual SampleStateMask ReadCondition::get_sample_state_mask() = 0;
     *
     * @brief   ��ȡ����ʱ���������״̬���롣
     *
     * @return  �ö�ȡ��������״̬���롣
     */

    virtual SampleStateMask get_sample_state_mask() = 0;

    /**
     * @fn  virtual ViewStateMask ReadCondition::get_view_state_mask() = 0;
     *
     * @brief   ��ȡ����ʱ�������ͼ״̬���롣
     *
     * @return  �ö�ȡ������ͼ״̬���롣
     */

    virtual ViewStateMask get_view_state_mask() = 0;

    /**
     * @fn  virtual InstanceStateMask ReadCondition::get_instance_state_mask() = 0;
     *
     * @brief   ��ȡ����ʱ�����ʵ��״̬���롣
     *
     * @return  �ö�ȡ����ʵ��״̬���롣
     */

    virtual InstanceStateMask get_instance_state_mask() = 0;
};

#endif //_ZRDDS_INCLUDE_READ_CONDITION

} // namespace DDS

#endif  //_READCONDITION_H
