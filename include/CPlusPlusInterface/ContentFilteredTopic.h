/**
 * @file:       ContentFilteredTopic.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#if !defined(_CONTENTFILTEREDTOPIC_H)
#define _CONTENTFILTEREDTOPIC_H

#include "ZRDDSCommon.h"
#include "DomainEntity.h"
#include "TopicDescription.h"
#include "ZRBuiltinTypes.h"
#include "ZRDDSCppWrapper.h"

namespace DDS {

class DomainParticipant;
class Topic;

/**
 * @class   ContentFilteredTopic
 *
 * @ingroup  CppTopic
 *
 * @brief   ����������ݹ��˵����⡣
 *
 * @details  �������ݵĹ��������Ǹ����ӵ�������󣬱������Ķ˲���Ҫ�����µ��������ݣ���ֻ��������һ�����������ݡ�
 *           �������ݹ��˵���������������ƶ��Ķ���Ҫ��������������Լ����������ڷ��͵��������������˹��ˣ���
 *           ͨ�����˱��ʽ�Լ����˲�������ʾ���Ķ���Ҫ�����ݡ����˱��ʽ��SQL����е�WHERE�����ƣ�
 *           �����˲������ṩֵ�����˱��ʽ�еĲ�����ʹ��%n��ʾ�����ṩ�Ĺ��˲����ĸ���������˱��ʽ��Ҫ��Ĳ���һ�¡�
 *           ���˱��ʽ�Լ����˲������﷨�μ� @ref expression-grammer ��
 *
 *           ע�⣺ ZRDDS�ð汾�Ĺ����ڶ��Ķ�Ӧ�ã��ʶ��������ݹ��˵����ⲻ���������������������ӽ��ն˵ĸ��أ�ÿ������
 *           ����ҪӦ���û����õĹ��˹��򣩡�
 */

class DCPSDLL ContentFilteredTopic :
    public TopicDescription
{
public:

    /**
     * @fn  virtual Topic* ContentFilteredTopic::get_related_topic() = 0;
     *
     * @brief   ��ȡ�û������ݹ�������Ļ������⣬��ʹ�� DomainParticipant::create_contentfilertopic ����ʱָ����
     *
     * @return  ָ��û������ݹ��˵���������Ļ������⡣
     */

    virtual Topic* get_related_topic() = 0;

    /**
     * @fn  virtual ReturnCode_t ContentFilteredTopic::get_expression_parameters(StringSeq &exp_paras) = 0;
     *
     * @brief   �÷�����ȡ�����Ĺ��˲������ڴ����������ݹ��˵�����ʱ�������ͨ�� #set_expression_parameters �������á�
     *
     * @param [in,out]  exp_paras   ���ڲ��������ڱ���ͨ���м��ά���Ĺ��˲�����
     *
     * @return  ���µĿ��ܷ���ֵ��
     *          - #DDS_RETCODE_OK :��ʾ�ɹ��� 
     *          - #DDS_RETCODE_ERROR :δ֪�Ĵ����ʾʧ�ܣ����翽������ʧ�ܡ�
     */

    virtual ReturnCode_t get_expression_parameters(StringSeq &exp_paras) = 0;

    /**
     * @fn  virtual ReturnCode_t ContentFilteredTopic::set_expression_parameters(const StringSeq &exp_paras) = 0;
     *
     * @brief   �÷��������������ù��˲�����
     *
     * @param   exp_paras   ָ���µĹ��˲�����
     *
     * @return  ���µĿ��ܷ���ֵ��
     *          - #DDS_RETCODE_OK :��ʾ�ɹ���
     *          - #DDS_RETCODE_BAD_PARAMETER :��ʾ���˲�������������������˱��ʽ��ƥ�䣻  
     *          - #DDS_RETCODE_ERROR :δ֪�Ĵ����ʾʧ�ܣ����翽������ʧ�ܡ�
     */

    virtual ReturnCode_t set_expression_parameters(const StringSeq &exp_paras) = 0;

    /**
     * @fn  virtual Char* ContentFilteredTopic::get_filter_expression() const = 0;
     *
     * @brief   ��ȡ��ǰ�������ݹ��˵���������Ĺ��˱��ʽ��
     *
     * @return  ���˱��ʽ�ַ�����
     */

    virtual Char* get_filter_expression() const = 0;
protected:
    virtual ~ContentFilteredTopic(){}
};

} // namespace DDS

#endif  //_CONTENTFILTEREDTOPIC_H
