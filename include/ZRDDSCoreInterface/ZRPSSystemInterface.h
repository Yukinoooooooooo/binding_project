/**
 * @file:       ZRPSSystemInterface.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#if !defined(ZRPSSYSTEMZR_INT32ERFACE_H)
#define ZRPSSYSTEMZR_INT32ERFACE_H

#include "OsResource.h"
#include "ZRDDSCommon.h"

#ifdef _ZRDDS_INCLUDE_PSINTERFACE

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @typedef void(*ZRPSCALLBACKFUN)( const DDS_Char* topicName, const DDS_Long topicNo, void* buffer, DDS_Long len)
 *
 * @ingroup CoreBaseFunction   
 *
 * @brief   ���Ķ˻ص��������������£� 
 *          - topicName: ����������������   
 *          - topicNo: �������������   
 *          - buffer: ���յ�����������   
 *          - len: ���յ������ݳ��ȡ�
 */

typedef void(*ZRPSCALLBACKFUN)(
    const DDS_Char* topicName,
    const DDS_Long topicNo,
    void* buffer,
    DDS_Long len);

/**
 * @typedef void(*ZRPSBUILTINCALLBACKFUN)( const DDS_Char* topicName, DDS_Long entityState, DDS_Long entityKind, const DDS_Char* entityId)
 *
 * @ingroup CoreBaseFunction   
 *
 * @brief   ���ֻص��������������£�
 *          - topicName: ���������������ƣ�����ʾΪNULLʱ��ʾ���ֵ�Ϊ������ߣ�
 *          - entityState: ��ʵ���״̬��1��ʾ���ߣ�0��ʾ���ߣ�
 *          - entityKind: ʵ�������a:  
 *              - 0��ʾ������ߣ�  
 *              - 1��ʾ����д�ߣ�  
 *              - 2��ʾ�����ߣ�  
 *          - entityId: ��ʵ���Ψһ��ʶ���ַ�����
 */

typedef void(*ZRPSBUILTINCALLBACKFUN)(
    const DDS_Char* topicName,
    DDS_Long entityState,
    DDS_Long entityKind,
    const DDS_Char* entityId);

/**
 * @fn  DCPSDLL const DDS_Char* ZRPSInterface_GetEntityId( const DDS_Char* topicName, DDS_Long entityKind);
 *
 * @ingroup CoreBaseFunction   
 *
 * @brief   ��ȡָ������������������д�߻������ݶ��ߵĽӿڡ�
 *
 * @param   topicName   ��������.
 * @param   entityKind  1��ʾ����д�ߣ�2��ʾ���ݶ��ߡ�
 *
 * @return  NULL��ʾ����ʧ�ܣ����򷵻ض�Ӧ��Ψһ��ʶ���ַ�����
 */

DCPSDLL const DDS_Char* ZRPSInterface_GetEntityId(
    const DDS_Char* topicName,
    DDS_Long entityKind);

/**
 * @fn  DCPSDLL void ZRPSInterface_Init(DDS_ULong domain_id);
 *
 * @ingroup CoreBaseFunction   
 *
 * @brief   ��ʼ���ӿڣ���ʹ�øýӿ�֮ǰ���á�
 *
 * @param   domain_id   ������
 */

DCPSDLL void ZRPSInterface_Init(DDS_ULong domain_id);

/**
 * @fn  DCPSDLL void ZRPSInterface_SetBuiltinCallBack( ZRPSBUILTINCALLBACKFUN callback);
 *
 * @ingroup CoreBaseFunction   
 *
 * @brief   ע�ᷢ�ֽӿ�.
 *
 * @param   callback    ���ֽӿں���.
 */

DCPSDLL void ZRPSInterface_SetBuiltinCallBack(
    ZRPSBUILTINCALLBACKFUN callback);

/**
 * @fn  DCPSDLL DDS_Long ZRPSInterface_Publish( const DDS_Char* topicName);
 *
 * @ingroup CoreBaseFunction   
 *
 * @brief   ���м��ע����ĳ��������صķ����ߡ�
 *
 * @param   topicName   �÷����߹�������������
 *
 * @return  �м�����ص�����š�
 */

DCPSDLL DDS_Long ZRPSInterface_Publish(
    const DDS_Char* topicName);

/**
 * @fn  DCPSDLL DDS_Long ZRPSInterface_Publish_WConfig( const DDS_Char* topicName, DDS_Boolean strongReliable);
 *
 * @ingroup CoreBaseFunction   
 *
 * @brief   ���м��ע����ĳ��������صķ����ߣ���Я���ɿ������á�
 *
 * @param   topicName   �÷����߹�������������
 * @param   strongReliable  �Ƿ�߱�ǿ�ɿ����á�
 *
 * @return  �м�����ص�����š�
 */

DCPSDLL DDS_Long ZRPSInterface_Publish_WConfig(
    const DDS_Char* topicName,
    DDS_Boolean strongReliable);

/**
 * @fn  DCPSDLL DDS_Long ZRPSInterface_UnPublish( const DDS_Long topicNo);
 *
 * @ingroup CoreBaseFunction   
 *
 * @brief   ���м��ע��ĳ������ķ����ߡ�
 *
 * @param   topicNo ��÷����߹���������š�
 *
 * @return  �ɹ�����0�����򷵻�-1��
 */

DCPSDLL DDS_Long ZRPSInterface_UnPublish(
    const DDS_Long topicNo);

/**
 * @fn  DCPSDLL DDS_Long ZRPSInterface_SendData( void* buffer, DDS_Long len, const DDS_Long topicNo);
 *
 * @ingroup  CoreBaseFunction
 *
 * @brief   �����߷�����Ϣ��
 *
 * @param [in,out]  buffer  �������ݡ�
 * @param   len             ���ݳ��ȡ�
 * @param   topicNo         �������ݹ���������š�
 *
 * @return  �ɹ�����0�����򷵻�-1��
 */

DCPSDLL DDS_Long ZRPSInterface_SendData(
    void* buffer, 
    DDS_Long len,
    const DDS_Long topicNo);

/**
 * @fn  DCPSDLL DDS_Long ZRPSInterface_Subscribe( const DDS_Char* topicName, ZRPSCALLBACKFUN callBackFun, DDS_Boolean reliable = true);
 *
 * @ingroup CoreBaseFunction   
 *
 * @brief   ���м��ע����ĳ��������صĶ����ߡ�
 *
 * @param   topicName   �ö����߹�������������
 * @param   callBackFun �����߽��ջص�������
 * @param   reliable    �������Ƿ���Ҫ�ɿ������ܵ��·�������������Ĭ��Ϊ�ɿ���
 *
 * @return  �м�����ص�����š�
 */

DCPSDLL DDS_Long ZRPSInterface_Subscribe(
    const DDS_Char* topicName,
    ZRPSCALLBACKFUN callBackFun, 
    DDS_Boolean reliable
#ifdef __cplusplus
    = true
#endif
    );

/**
 * @fn  DCPSDLL DDS_Long ZRPSInterface_UnSubscribe( DDS_Long topicNo);
 *
 * @ingroup CoreBaseFunction   
 *
 * @brief   ���м��ע��ĳ������Ķ����ߡ�
 *
 * @param   topicNo ��ö����߹���������š�
 *
 * @return  �ɹ�����0�����򷵻�-1��
 */

DCPSDLL DDS_Long ZRPSInterface_UnSubscribe(
    DDS_Long topicNo);

/**
 * @fn  DCPSDLL void ZRPSInterface_Destory();
 *
 * @ingroup CoreBaseFunction   
 *
 * @brief   ע���ӿڣ�����ʹ��ZRPSSystemInterface�ӿ�ʱ�������ͷ���Դ��
 */

DCPSDLL void ZRPSInterface_Destory();

#ifdef __cplusplus
}
#endif

#endif /*_ZRDDS_INCLUDE_PSINTERFACE*/

#endif
