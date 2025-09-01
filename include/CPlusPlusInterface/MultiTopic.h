/**
 * @file:       MultiTopic.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#if !defined(_MULTITOPIC_H)
#define _MULTITOPIC_H

#include "TopicDescription.h"
#include "ZRBuiltinTypes.h"

namespace DDS {
    
class DomainParticipant;
/**
 * @class   MultiTopic
 *
 * @ingroup CppTopic
 *
 * @brief   �ϲ����ն�����⡣
 *
 * @details ָ��һ�������߿��Խ�����ͬһ���ʹ����Ķ�����⣬������ͨ��ָ���ķ�ʽ���й��˺���������
 *          ���˺����ŵı��ʽ��ʽ������SQL��䡣��ϸ���﷨�����DDS�淶��
 *
 * @warning ZRDDS��ǰδʵ�ָù��ܡ�
 */

class DCPSDLL MultiTopic :
    public TopicDescription
{
public:
    virtual ReturnCode_t get_expression_parameters(StringSeq &exp_paras) = 0;
    virtual ReturnCode_t set_expression_parameters(const StringSeq &exp_paras) = 0;
protected:
    virtual ~MultiTopic() {}
};

} // namespace DDS

#endif  //_MULTITOPIC_H
