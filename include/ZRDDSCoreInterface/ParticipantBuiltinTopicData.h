/**
 * @file:       ParticipantBuiltinTopicData.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#ifndef ParticipantBuiltinTopicData_h__
#define ParticipantBuiltinTopicData_h__

#include "OsResource.h"
#include "BuiltinTopicKey_t.h"
#include "UserDataQosPolicy.h"
#include "PropertyList.h"
#include "SRIOPass_t.h"
#include "ZRSequence.h"
#include "Duration_t.h"

#ifdef _ZRDDSSECURITY
#include "DDSBuiltinSecurityCommon.h"
#endif

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @struct DDS_ParticipantBuiltinTopicData
 *
 * @ingroup CoreBaseStruct
 *
 * @brief   ���ڳ�����û����ֵ�Զ�����������Ϣ��
 */

typedef struct DDS_ParticipantBuiltinTopicData
{
    /** @brief   ����Ψһ��ʶ��������ߡ� */
    DDS_BuiltinTopicKey_t key;
#ifdef _ZRDDS_INCLUDE_USER_DATA_QOS
    /** @brief   ������������õ� DDS_UserDataQosPolicy �� */
    DDS_UserDataQosPolicy user_data;
#endif /* _ZRDDS_INCLUDE_USER_DATA_QOS */
    /** @brief   ��������������ڵ�������б� */
    DDS_PropertyList property_list;
#ifdef _ZRDDS_MPORT_SRIO
    /** @brief   �����������rioͨ��������ܴ���С�� */
    DDS_ULong recv_sub_wnd_size;
#ifdef _ZRDDS_MPORT_FPGA_SRIO
    /** @brief   ��������������ڵ��srio��id�� */
    DDS_ULong srio_id;
    /** @brief   ��������������ڵ���Žӱ� */
    SRIOConfigList_t configList;
#endif // _ZRDDS_MPORT_FPGA_SRIO
#endif // _ZRDDS_MPORT_SRIO
    /** @brief   ���������������������RTPXЭ�飬�μ� DDS_DomainParticipantQos::domain_destination_addresses �� */
    DDS_ULong domain_id;
#ifdef _ZRDDSSECURITY
    /** @brief ָ����Participant���������������Ƿ������ȫ������ݡ� */
    DDS_Boolean contains_security_data;
    /** @brief The identity token */
    IdentityToken identity_token;
    /** @brief The permissions token */
    PermissionsToken permissions_token;
    /** @brief Information describing the participant security */
    ParticipantSecurityInfo security_info;
#endif
    /** @brief   ��������ߴ���ʱ�䡣 */
    DDS_Duration_t create_time;
}DDS_ParticipantBuiltinTopicData;

/**
 * @fn  DCPSDLL void DDS_ParticipantBuiltinTopicDataInitial( DDS_ParticipantBuiltinTopicData* self);
 *
 * @ingroup CoreBaseFunction
 *
 * @brief   ��ʼ�� DDS_ParticipantBuiltinTopicData ����
 *
 * @param [in,out]  self    ָ��Ŀ�ꡣ
 *
 * @pre selfΪ��Ч�� DDS_ParticipantBuiltinTopicData ����
 */

DCPSDLL void DDS_ParticipantBuiltinTopicDataInitial(
    DDS_ParticipantBuiltinTopicData* self);

/**
 * @fn  DCPSDLL void DDS_ParticipantBuiltinTopicDataDestroy( DDS_ParticipantBuiltinTopicData* self);
 *
 * @ingroup CoreBaseFunction
 *
 * @brief   ���� DDS_ParticipantBuiltinTopicData ����ռ䣬�����ͷ� DDS_ParticipantBuiltinTopicData ����ռ䡣
 *
 * @param [in,out]  self    ָ��Ŀ�ꡣ
 *
 * @pre selfΪ��Ч�� DDS_ParticipantBuiltinTopicData ����
 */

DCPSDLL void DDS_ParticipantBuiltinTopicDataDestroy(
    DDS_ParticipantBuiltinTopicData* self);

/**
 * @fn  DCPSDLL DDS_Boolean DDS_ParticipantBuiltinTopicDataCopy( DDS_ParticipantBuiltinTopicData* dst, const DDS_ParticipantBuiltinTopicData* src);
 *
 * @ingroup CoreBaseFunction
 *
 * @brief   ���� DDS_ParticipantBuiltinTopicData ����
 *
 * @param [in,out]  dst ָ��������Ŀ�Ķ���
 * @param   src         ָ������Դ����
 *
 * @return  true��ʾ�����ɹ���false��ʾ����ʧ�ܣ�ԭ�����Ϊ�ռ䲻�㡣
 *
 * @pre dst�Լ�srcΪ��Ч�� DDS_ParticipantBuiltinTopicData ����
 */

DCPSDLL DDS_Boolean DDS_ParticipantBuiltinTopicDataCopy(
    DDS_ParticipantBuiltinTopicData* dst,
    const DDS_ParticipantBuiltinTopicData* src);

/* ����sequence�ṹ*/
DDS_SEQUENCE_CPP(DDS_ParticipantBuiltinTopicDataSeq, DDS_ParticipantBuiltinTopicData);

#ifdef _ZRDDSSECURITY
typedef DDS_ParticipantBuiltinTopicData DDS_ParticipantBuiltinTopicDataSecure;
#endif /* _ZRDDSSECURITY */

#ifdef __cplusplus
}
#endif

#endif /* ParticipantBuiltinTopicData_h__*/
