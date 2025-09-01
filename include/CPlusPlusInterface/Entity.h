/**
 * @file:       Entity.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#if !defined(_ENTITY_H)
#define _ENTITY_H

#include "ZRDDSCommon.h"
#include "ZRBuiltinTypes.h"
#include "ZRDDSCppWrapper.h"

namespace DDS {

class StatusCondition;

/**
 * @class   Entity
 *
 * @ingroup CppInfrastruct
 *
 * @brief   ʵ�壨@ref entity-introduction) ��Ϊ����ʵ�壨����������ߡ����⡢�����ߡ������ߡ����ݶ��ߡ�����д�ߣ��Ļ��࣬����ʵ��Ļ��������Լ�������
 */

class DCPSDLL Entity
{
public:
    virtual ~Entity();

    /**
     * @fn  virtual StatusCondition* Entity::get_statuscondition() = 0;
     *
     * @brief   ���ظ�ʵ�������״̬������
     *
     * @return  �ײ��Զ�������״̬������
     */

    virtual StatusCondition* get_statuscondition() = 0;

    /**
     * @fn  virtual StatusKindMask Entity::get_status_changes() = 0;
     *
     * @brief   ��ȡ��ʵ�����һ�λ�ȡ����״̬���״̬�仯��
     *
     * @return  ����״̬�ĸı����롣
     */

    virtual StatusKindMask get_status_changes() = 0;

    /**
     * @fn  virtual ReturnCode_t Entity::enable() = 0;
     *
     * @brief   �ֶ�ʹ�ܸ�ʵ�壬�μ�@ref entity-enable ��
     *
     * @return  ��ǰ���ܵķ���ֵ��
     *          - #DDS_RETCODE_OK ����ʾ��ȡ�ɹ���
     *          - #DDS_RETCODE_PRECONDITION_NOT_MET ����ʾ�����ĸ�ʵ����δʹ�ܡ�
     */

    virtual ReturnCode_t enable() = 0;

    /**
     * @fn  virtual InstanceHandle_t Entity::get_instance_handle() = 0;
     *
     * @brief   ��ȡ��ʵ���Ψһ��ʶ��
     *
     * @return  ʵ��Ψһ��ʶ��
     */

    virtual InstanceHandle_t get_instance_handle() = 0;
#ifdef _ZRXMLINTERFACE

#ifdef _ZRXMLENTITYINTERFACE

    /**
     * @fn  virtual const Char* Entity::get_entity_name() = 0;
     *
     * @brief   ��ȡʵ������ơ�
     *
     * @return  NULL��ʾ��ȡʧ�ܣ�����Ϊʵ������ơ�
     */

    virtual const Char* get_entity_name() = 0;

    /**
     * @fn  virtual Entity* Entity::get_factory() = 0;
     *
     * @brief   ��ȡ��ʵ��Ĺ���ʵ�塣
     *
     * @return  ��ʵ��ĸ�����ʵ�塣
     */

    virtual Entity* get_factory() = 0;

    /**
     * @fn virtual ReturnCode_t Entity::to_xml(const Char*& result, Boolean containedQos = true) = 0;
     *
     * @brief ��ʵ��ת��ΪXML�ı�
     *
     * @param [in,out] result ת���õ���XML�ı���
     * @param containedQos    ת����XML���Ƿ���Ҫ����ʵ���QoS��
     *
     * @return ��ǰ���ܵķ���ֵ��
     *          - #DDS_RETCODE_OK ����ʾת���ɹ���
     *          - #DDS_RETCODE_ERROR ����ʾת��ʧ�ܡ�
     */
    virtual ReturnCode_t to_xml(const Char*& result, Boolean containedQos = true) = 0;

#endif // _ZRXMLENTITYINTERFACE

#endif // _ZRXMLINTERFACE
protected:
    // ���캯��
    Entity();
    StatusCondition* m_statusCondition;
};

} // namespace DDS

#endif  //_ENTITY_H
