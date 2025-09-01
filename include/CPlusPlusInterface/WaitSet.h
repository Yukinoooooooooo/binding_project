/**
 * @file:       WaitSet.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#if !defined(_WAITSET_H)
#define _WAITSET_H

#include "Condition.h"
#include "ZRDDSCppWrapper.h"

typedef struct WaitSetImpl WaitSetImpl;

#ifdef _ZRDDS_INCLUDE_WAITSET

namespace DDS {

/**
 * @class   WaitSet
 *
 * @ingroup CppInfrastructure
 *
 * @brief   �����ͳ���ȴ����� @ref waitset-introduction ��
 */

class DCPSDLL WaitSet
{
public:

    /**
     * @fn  WaitSet::WaitSet();
     *
     * @brief   Ĭ�Ϲ��캯�������켯��Ϊ�յļ��ϡ�
     */

    WaitSet();

    /**
     * @fn  WaitSet::~WaitSet();
     *
     * @brief   �������������Զ��⿪������
     */

    ~WaitSet();

    /**
     * @fn  ReturnCode_t WaitSet::attach_condition(Condition *a_condition);
     *
     * @brief   ��ָ�����������뵽�õȴ������С�
     *          
     * @details �����ӵ������Ĵ���״̬Ϊtrue������⿪������
     *
     * @param [in,out]  a_condition ָ����Ҫ��ӵ�������
     *
     * @return  ��ǰ���ܵķ���ֵ��
     *          - #DDS_RETCODE_OK :��ӳɹ���  
     *          - #DDS_RETCODE_OUT_OF_RESOURCES :�����ڴ�ʧ�ܣ�  
     *          - #DDS_RETCODE_BAD_PARAMETER :����������Ч��������
     */

	ReturnCode_t attach_condition(Condition *a_condition);

    /**
     * @fn  ReturnCode_t WaitSet::detach_condition(Condition *a_condition);
     *
     * @brief   �ӵȴ��������Ƴ�ָ����������
     *
     * @param [in,out]  a_condition ָ����Ҫɾ����������
     *
     * @return  ��ǰ���ܵķ���ֵ��
     *          - #DDS_RETCODE_OK :��ӳɹ���  
     *          - #DDS_RETCODE_PRECONDITION_NOT_MET :ָ�����������ڸõȴ������У�  
     *          - #DDS_RETCODE_BAD_PARAMETER :����������Ч��������
     */

	ReturnCode_t detach_condition(Condition *a_condition);

    /**
     * @fn  ReturnCode_t WaitSet::wait(const ConditionSeq &active_condition, const Duration_t &timeout);
     *
     * @brief   �����ȴ��ȴ������е��������ڴ���״̬��
     *          
     * @details Ӧ���̵߳ȴ�ĳЩ�����ķ��������������̣߳� �����óɹ�ʱ��@e active_condition �д�Ŵ�����������
     *          ���������̵߳ȴ�ͬһ���ȴ�������
     *
     * @param   active_condition    ���ڲ��������ڴ洢���ڴ���״̬��������
     * @param   timeout             ָ����ȴ�ʱ�䡣
     *
     * @return  ��ǰ���ܵķ���ֵ��
     *          - #DDS_RETCODE_OK :���ڲ�����Ч���������ڴ���״̬��������  
     *          - #DDS_RETCODE_PRECONDITION_NOT_MET :�ڶ���߳��ϵȴ�������    
     *          - #DDS_RETCODE_BAD_PARAMETER / #DDS_RETCODE_ERROR ���û��ṩ�Ŀռ䲻�㣬�ҵײ�����ʧ�ܣ�  
     *          - #DDS_RETCODE_TIMEOUT : ��ָ����ʱ����û���������ڴ���״̬��
     */

    ReturnCode_t wait(ConditionSeq &active_condition, const Duration_t &timeout);

    /**
     * @fn  ReturnCode_t WaitSet::get_conditions(ConditionSeq &attached_conditions);
     *
     * @brief   ��ȡ��ǰ�õȴ����������е�������
     *
     * @param [in,out]  attached_conditions ���ڲ��������ڴ洢��ǰ�����е�������
     *
     * @return  ��ǰ���ܵķ���ֵ��
     *          - #DDS_RETCODE_OK :���ڲ�����Ч���������ڴ���״̬��������  
     *          - #DDS_RETCODE_BAD_PARAMETER / #DDS_RETCODE_ERROR ���û��ṩ�Ŀռ䲻�㣬�ҵײ�����ʧ�ܣ�  
     */

    ReturnCode_t get_conditions(ConditionSeq &attached_conditions);
private:
    /** @brief   The conditions. */
    WaitSetImpl* m_cWaitSet;
};

} // namespace DDS

#endif //_ZRDDS_INCLUDE_WAITSET

#endif  //_WAITSET_H
