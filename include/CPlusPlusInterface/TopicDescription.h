/**
 * @file:       TopicDescription.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#if !defined(_TOPICDESCRIPTION_H)
#define _TOPICDESCRIPTION_H

#include "ZRDDSCommon.h"
#include "OsResource.h"

namespace DDS {

class DomainParticipant;

/**
 * @class	TopicDescription
 *
 * @ingroup	CppTopic
 *
 * @brief	��������Ļ���������Ϣ��
 *
 * @details	��������ص���Ϣ����������һ���Ѵ��ڵ��������ͣ��������������� DDS::TypeSupport ����������
 * 			���������Լ������������� DDS::DomainParticipant ����Щ������Ϣ�����ڸ���Ķ����в���ͨ������Ķ����ȡ��
 */

class DCPSDLL TopicDescription
{
public:

    /**
     * @fn  virtual DomainParticipant* TopicDescription::get_participant() = 0;
     *
     * @brief   ��ȡ����������������������ߡ�
     *
     * @return  ���ظ�����������������߶���
     */

    virtual DomainParticipant* get_participant() = 0;

    /**
     * @fn  virtual const Char* TopicDescription::get_type_name() = 0;
     *
     * @brief   ��ȡ�������������������������������ע������ơ�
     *
     * @return  �������͵����ơ�
     */

    virtual const Char* get_type_name() = 0;

    /**
     * @fn  virtual const Char* TopicDescription::get_name() = 0;
     *
     * @brief   ��ȡ����������ơ�
     *
     * @return  �������ơ�
     */

    virtual const Char* get_name() = 0;
protected:

    TopicDescription(){}

    virtual ~TopicDescription(){}
};

} // namespace DDS

#endif  //_TOPICDESCRIPTION_H
