/**
 * @file:       Topic.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#if !defined(_TOPIC_H)
#define _TOPIC_H

#include "DomainEntity.h"
#include "TopicDescription.h"
#include "TopicListener.h"
#include "ZRDDSCppWrapper.h"

namespace DDS {

#ifdef __cplusplus
extern "C"
{
#endif

/** @brief	�������������Ϣ���ݶ��߹������������ơ�@ingroup   CoreVar */
DCPSDLL extern const Char* BUILTIN_PARTICIPANT_TOPIC_NAME;
/** @brief	��������д������Ϣ���ݶ��߹������������ơ�@ingroup   CoreVar */
DCPSDLL extern const Char* BUILTIN_PUBLICATION_TOPIC_NAME;
/** @brief	�������ݶ�����Ϣ���ݶ��߹������������ơ�@ingroup   CoreVar */
DCPSDLL extern const Char* BUILTIN_SUBSCRIPTION_TOPIC_NAME;
#if defined(_ZRDDSSECURITY)
/** @brief	��������д������Ϣ���ݶ��߹������������ơ�@ingroup   CoreVar */
DCPSDLL extern const Char* BUILTIN_PUBLICATION_SECURE_TOPIC_NAME;
/** @brief	�������ݶ�����Ϣ���ݶ��߹������������ơ�@ingroup   CoreVar */
DCPSDLL extern const Char* BUILTIN_SUBSCRIPTION_SECURE_TOPIC_NAME;
#endif // _ZRDDSSECURITY

#ifdef __cplusplus
}
#endif

/**
 * @class   Topic
 *
 * @ingroup CppTopic
 *
 * @brief   �����Ƿ�������ģ�������ݻ����ĳ���
 *          
 * @details ��������������ʶ��������������Ψһ������ͨ���������������ƶ������������ݵ����ݽṹ��
 *          ����д�������ݶ���ͨ�������������ͨ�š�
 */

class DCPSDLL Topic :
    virtual public DomainEntity,
    virtual public TopicDescription
{
public:
#ifdef _ZRXMLINTERFACE

#ifdef _ZRXMLQOSINTERFACE

    /**
     * @fn  virtual ReturnCode_t set_qos_with_profile( const Char* library_name, const Char* profile_name, const Char* qos_name) = 0;
     *
     * @brief   ��QoS�ֿ��л�ȡ����QoS���������õ�������
     *
     * @param   library_name    QoS������֣�������ΪNULL��
     * @param   profile_name    QoS���õ����֣�������ΪNULL��
     * @param   qos_name        QoS�����֣�����ΪNULL����ת��Ϊdefault�ַ�����
     *
     * @return  ��ǰ���ܵķ���ֵ���£�
     *         - #DDS_RETCODE_OK :��ʾ���óɹ���
     *         - #DDS_RETCODE_ERROR :��ʾδ֪�����µ����ô���
     */

    virtual ReturnCode_t set_qos_with_profile(
        const Char* library_name,
        const Char* profile_name,
        const Char* qos_name) = 0;

#endif // _ZRXMLQOSINTERFACE

#endif // _ZRXMLINTERFACE

    /**
     * @fn  virtual ReturnCode_t get_inconsistent_topic_status(InconsistentTopicStatus &status) = 0;
     *
     * @brief   ��ȡ����������� #DDS_INCONSISTENT_TOPIC_STATUS ״̬.
     *
     * @param [in,out]  status  ���ڲ�����ʾ��ǰ��״̬��
     *
     * @return  ��ǰ���Ƿ��� #DDS_RETCODE_OK ��ʾ��ȡ�ɹ���
     */

    virtual ReturnCode_t get_inconsistent_topic_status(InconsistentTopicStatus &status) = 0;

    /**
     * @fn  virtual ReturnCode_t set_qos(const TopicQos &qoslist) = 0;
     *
     * @brief   ��������ʵ���QoS��
     *
     * @details  ����ʹ������ֵ DDS::TOPIC_QOS_DEFAULT ��
     *
     * @param   qoslist ��ʾ�û���Ҫ���õ�QoS���á�
     *
     * @return  ��ǰ���ܵķ���ֵ��
     *          - #DDS_RETCODE_OK :��ʾ��ȡ�ɹ���
     *          - #DDS_RETCODE_BAD_PARAMETER :��ʾ @e qoslist ������Ч��QoS���ã�
     *          - #DDS_RETCODE_INCONSISTENT :��ʾ @e qoslist ���в����ݵ�QoS���ã�
     *          - #DDS_RETCODE_IMMUTABLE_POLICY :��ʾ�û������޸�ʹ�ܺ󲻿ɱ��QoS���ã�
     *          - #DDS_RETCODE_ERROR :��ʾδ����Ĵ��󣬴�����ϸ��Ϣ�������־�У�.
     */

    virtual ReturnCode_t set_qos(const TopicQos &qoslist) = 0;

    /**
     * @fn  virtual ReturnCode_t get_qos(TopicQos &qoslist) = 0;
     *
     * @brief   ��ȡ�������QoS���á�
     *
     * @param [in,out]  qoslist ���ڲ��������ڱ��������ĵ�QoS���á�
     *
     * @return  ��ǰ���ܵķ���ֵ��
     *          - #DDS_RETCODE_OK :��ʾ��ȡ�ɹ���
     *          - #DDS_RETCODE_ERROR :��ʾʧ�ܣ�ԭ�����Ϊ����QoSʱ��������
     */

    virtual ReturnCode_t get_qos(TopicQos &qoslist) = 0;

    /**
     * @fn  virtual ReturnCode_t set_listener(TopicListener *a_listener, StatusKindMask mask) = 0;
     *
     * @brief   ���ø�����ĵļ�������
     *
     * @details  ������������ԭ�м�������������ÿն����ʾ���ԭ�����õļ�������
     *
     * @param [in,out]  a_listener  Ϊ���������õļ���������
     * @param   mask                ����Ӧ�ó������Ȥ��״̬��ֻ��Ӧ�ó������Ȥ��״̬�����仯ʱ���Ż�֪ͨӦ�ó���
     *
     * @return  ��ǰ���Ƿ��� #DDS_RETCODE_OK ��ʾ���óɹ���
     */

    virtual ReturnCode_t set_listener(TopicListener *a_listener, StatusKindMask mask) = 0;

    /**
     * @fn  virtual TopicListener* get_listener() = 0;
     *
     * @brief   �÷�����ȡͨ�� #set_listener �������ߴ���ʱΪ�������õļ���������
     *
     * @return  ��ǰ���ܵķ���ֵ��
     *          - NULL��ʾδ���ü�������
     *          - �ǿձ�ʾӦ��ͨ�� #set_listener �����ڴ���ʱ���õļ���������
     */

    virtual TopicListener* get_listener() = 0;
protected:
    Topic(){}
    virtual ~Topic(){}
};

} // namespace DDS

#endif  //_TOPIC_H
