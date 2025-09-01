/**
 * @file:       Condition.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#if !defined(_CONDITION_H)
#define _CONDITION_H

#include "ZRDDSCommon.h"
#include "ZRSequence.h"
#include "ZRDDSCppWrapper.h"

namespace DDS {

class Entity;
class GuardConditionCPlusPlusImpl;

/**
 * @class   Condition 
 *
 * @ingroup CppInfrastruct
 *
 * @brief   ZRDDS�������Ļ��ࡣ
 *
 * @details ZRDDS���ṩ����-�ȴ�ģ��ʹ���û�����ʹ��ͬ���ȴ���ģʽ��ȡZRDDS�ײ�����ݣ�@ref waitset-introduction ������Ϊ���������Ļ��ࡣ
 */

class DCPSDLL Condition
{
public:

    /**
     * @fn  virtual Boolean Condition::get_trigger_value() = 0;
     *
     * @brief   ��ȡ��ǰ�Ĵ���״̬��
     *
     * @return  true��ʾ��������false��ʾ��������δ��������
     */

    virtual Boolean get_trigger_value() = 0;

    /**
     * @fn  virtual Condition::~Condition()
     *
     * @brief   ����������
     */

    virtual ~Condition(){}
};

/**
 * @class   StatusCondition 
 *
 * @ingroup CppInfrastruct
 *
 * @brief   ʵ��״̬���������������ڻ�ȡʵ��״̬�ı䡣
 *
 * @details ���������ڵȴ�ʵ���м�ͨ��״̬�仯����ZRDDS���û�����ʵ��ʱ���Զ�������ʵ������ĸ�״̬���û�ͨ���ӿ�
 *          DDS::Entity::get_statusconditon() ������ȡ�ײ����á�
 */

class DCPSDLL StatusCondition : public Condition
{
public:

    /**
     * @fn  virtual ReturnCode_t StatusCondition::set_enabled_statuses(const StatusKindMask &mask) = 0;
     *
     * @brief   ������ķ�ʽ�����û����ĵ�״̬��
     *
     * @param   mask    ���롣
     *
     * @return  ��ǰ���Ƿ��� #DDS_RETCODE_OK ��
     */

    virtual ReturnCode_t set_enabled_statuses(const StatusKindMask &mask) = 0;

    /**
     * @fn  virtual StatusKindMask StatusCondition::get_enabled_statuses() = 0;
     *
     * @brief   ��ȡǰһ���û�ͨ�� #set_enabled_statuses �������õĹ��ĵ�״̬��
     *
     * @return  ���뷽ʽ���ص�ǰ״̬������������״̬���ϡ�
     */

    virtual StatusKindMask get_enabled_statuses() = 0;

    /**
     * @fn  virtual Entity* StatusCondition::get_entity() = 0;
     *
     * @brief   ��ȡ״̬����������ʵ�塣
     *
     * @return  NULL��ʾʧ�ܣ�����ָ�������ʵ��Ļ��࣬�û�ͨ��dynamic_castת��Ϊ�����ʵ�����͡�
     */

    virtual Entity* get_entity() = 0;
};

#ifdef _ZRDDS_INCLUDE_GUARD_CONDITION

/**
 * @class   GuardCondition 
 *
 * @ingroup CppInfrastruct
 *
 * @brief   �������������ֶ����Ƶȴ�������
 *
 * @details ������Ҫ�����ֶ����Ƶȴ����� DDS::WaitSet::wait ��������������������������������ȫ���û�ͨ�� new/delete ���ơ�
 */

class DCPSDLL GuardCondition : public Condition
{
public:

    /**
     * @fn  GuardCondition::GuardCondition();
     *
     * @brief   Ĭ�Ϲ��촦�ڷǴ���״̬�ļ���������
     */

    GuardCondition();

    /**
     * @fn  GuardCondition::~GuardCondition();
     *
     * @brief   ����������
     */

    ~GuardCondition();

    /**
     * @fn  virtual ReturnCode_t GuardCondition::set_trigger_value(Boolean value);
     *
     * @brief   �ֶ����ü����Ĵ���״̬��
     *
     * @param   value   true��ʾ����Ϊ����״̬��false��ʾ����Ϊ�Ǵ���״̬��
     *
     * @return  ���Ƿ��� #DDS_RETCODE_OK ��
     */

    virtual ReturnCode_t set_trigger_value(Boolean value);

    /**
     * @fn  virtual Boolean GuardCondition::get_trigger_value();
     *
     * @brief   ʵ�ָ���ĳ��󷽷���
     *
     * @return  true��ʾ��������false��ʾ��������δ��������
     */

    virtual Boolean get_trigger_value();

public:
    /** @brief   ������ʵ�ֶ��� */
    GuardConditionCPlusPlusImpl* m_impl;
};
#endif // _ZRDDS_INCLUDE_GUARD_CONDITION

/**
 * @typedef Condition* ConditionPtr
 *
 * @ingroup CppInfrastruct
 *
 * @brief   ���� DDS::Condition ָ��ı�����
 */

typedef Condition* ConditionPtr;

/**
 * @struct ConditionSeq 
 *
 * @ingroup CppInfrastruct
 *
 * @brief   ���� DDS::ConditionPtr ���������ͣ��μ� #DDS_USER_SEQUENCE_CPP ��
 */

typedef struct ConditionSeq ConditionSeq;
DDS_SEQUENCE_CPP(ConditionSeq, ConditionPtr);

} // namespace DDS

#endif  //_CONDITION_H
