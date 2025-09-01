/**
 * @file:       TypeSupport.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#if !defined(_TYPESUPPORT_H)
#define _TYPESUPPORT_H

#include "OsResource.h"
#include "ZRDDSCommon.h"
#include "ZRDDSCppWrapper.h"
#include <stdlib.h>

namespace DDS {

class DomainParticipant;
class DataWriter;
class DataReader;

/**
 * @class   TypeSupport
 *
 * @ingroup CppTopic
 *
 * @brief   ����֧�ֽӿڣ�������ZRDDSע���û��Զ����������͡�
 *
 * @details Ӧ���Զ�����������ͱ���ʵ�ָýӿڣ�ZRDDSͨ���������Զ��������û��������͹���������֧�ֽӿڡ�
 *          Ӧ���Զ��������������Ҫ���������ע��ɹ��󣬲����������������������ZRDDSע��Ĺ�����Ҫ�Ǹ�֪ZRDDS���
 *          �������������������Լ����л��������л��Ȳ����� 
 */

class DCPSDLL TypeSupport
{
public:

    virtual ~TypeSupport(){}

    /**
     * @fn  virtual const Char* TypeSupport::get_type_name() = 0;
     *
     * @brief   ��ȡ�������ơ�
     *
     * @return  ��ȡ�����������ơ�
     */

    virtual const Char* get_type_name() = 0;

    /**
     * @fn  virtual ReturnCode_t TypeSupport::register_type( DomainParticipant *participant, const Char* type_name);
     *
     * @brief   ע���������ͣ��������ʵ�ֵĽӿڡ�
     *          
     * @details �÷����������������ע�����ͣ�ע��Ľ����ʹ��ͨ���м���ܹ������������󣨴�����ɾ������������
     *          ��ȡ�����������������л��Լ������л���������ͬһ����������¸���ͬ������֧�ֶ���ע����ͬ����������
     *          ���� #DDS_RETCODE_PRECONDITION_NOT_MET �����������֧�ֽӿڶ��ע����ͬ�Ļ��߲�ͬ���������ƣ�
     *          Ч���Ǹ���ע�ᡣ
     *
     * @param [in,out]  participant ע���Ŀ��������ߡ�
     * @param   type_name           �û�ָ����Ϊ������֧�ֶ���ע���������������ΪNULL��ͨ���м��ʹ�� #get_type_name 
     *                              �����Ľ��ע�ᣬ�����������������������Ψһ��ʶ�������������ͣ����ڴ�������ȡ�
     *
     * @return  ��ǰ���ܵķ���ֵ���£�
     *          - #DDS_RETCODE_OK :ע��ɹ���
     *          - #DDS_RETCODE_PRECONDITION_NOT_MET :������ͬ����������ע�ᣬ������֧�ֶ���ͬ��
     *          - #DDS_RETCODE_BAD_PARAMETER ��participant����Ϊ�գ�
     *          - #DDS_RETCODE_ERROR :�ڲ�δ֪����
     */

    virtual ReturnCode_t register_type(
        DomainParticipant *participant,
        const Char* type_name) = 0;

    /**
     * @fn  virtual ReturnCode_t TypeSupport::unregister_type(DomainParticipant *participant, const Char* type_name) = 0;
     *
     * @brief   ��ָ�����������ע�����͡�
     *
     * @param [in,out]  participant ָ��Ŀ��������ߡ�
     * @param   type_name           ָ��ע���������ơ�
     *
     * @return  ��ǰ���ܵķ���ֵ��
     *          - #DDS_RETCODE_OK :��ʾע���ɹ���  
     *          - #DDS_RETCODE_BAD_PARAMETER ������Ϊ�գ�  
     *          - #DDS_RETCODE_PRECONDITION_NOT_MET ��  
     *              - ����ָ�����������Ʋ����ڣ�  
     *              - ������ע���������ײ㻹����������������͹�����
     */

    virtual ReturnCode_t unregister_type(DomainParticipant *participant,
                                         const Char* type_name) = 0;
protected:

    TypeSupport(){}
};

} // namespace DDS

#endif  //_TYPESUPPORT_H
