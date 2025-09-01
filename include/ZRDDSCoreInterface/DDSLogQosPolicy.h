/**
 * @file:       DDSLogQosPolicy.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#ifndef DDSLogQosPolicy_h__
#define DDSLogQosPolicy_h__

#include "OsResource.h"
#include "ZRBuiltinTypes.h"

/**
 * @typedef enum DDS_LogBackupKind
 *
 * @ingroup CoreQosStruct
 *
 * @brief   ������־�ļ��ı��ݲ��ԡ�
 */

typedef enum DDS_LogBackupKind
{
    /** @brief  Ĭ��ģʽ����ʹ����־���ݹ��ܡ�ÿ������Ӧ�ã���������ԭ����־�� @ingroup CoreQosStruct */
    DDS_LOG_BACKUP_NOTUSED_QOS,
    /** @brief  ͬ������ģʽ������ͬ����־ʱ����ԭ�е���־���ݵ���־���Ŀ¼/��־�ļ���-ʱ����� */
    DDS_LOG_BACKUP_EXIST_FILE,
    /**
    * @brief   ��ǰ��־�ļ��ﵽһ����С�󽫽��б��ݣ������´�����־�ļ���
    *          ѡ�ø�ģʽ����־�ļ������ƽ�Ϊ����־�ļ�����_����ʱ��.ddslog����
    *          @ingroup CoreQosStruct
    */
    DDS_LOG_BACKUP_FILE_SIZE_QOS,
    /**
    * @brief   ÿ��һ��ʱ��󽫽��б��ݣ������´�����־�ļ���
    *          ѡ�ø�ģʽ����־�ļ������ƽ�Ϊ����־�ļ�����_����ʱ��.ddslog����
    *          @ingroup CoreQosStruct
    */
    DDS_LOG_BACKUP_TIME_INTERVAL_QOS,
}DDS_LogBackupKind;

/**
 * @struct DDS_LogQosPolicy
 *
 * @ingroup CoreQosStruct
 *
 * @brief   DDS����־ϵͳ����QoS��
 *
 * @details DDS��־ϵͳ����������־�Լ�����DDS����������ķֲ�ʽ��־������ϵͳ��
 *          - ͨ�����ñ�����־��ϵͳ��DDS����־���������̨������DDS����ͬһĿ¼�µ���־�ļ�������Ϊ:����(����)����.ddslog���� 
 *          - ͨ�����÷ֲ�ʽ����ϵͳ��DDSͨ���������������д�߽���־������ȥ��  
 *              DDS�������������յ�����־��Ϣ�������û�չʾ��
 *          ��Ա | Ĭ��ֵ | ƥ������� | ��Ч�Լ�� | �����Լ�� | �ɱ��Լ��
 *          --- | --- | --- | --- | --- | ---
 *          #console_mask | 0xffff | �� | �� | �� | ���ɱ�
 *          #file_mask | 0xffff | �� | �� | �� | ���ɱ�
 *          #local_level_mask | 0xffff | �� | �� | �� | ���ɱ�
 *          #enable_distributed_log | false | �� | �� | �� | ���ɱ�
 *          #distributed_log_writer_domain_id | 0 | �� | �� | �� | ���ɱ�
 *          #distributed_log_level_mask | 0xffff | �� | �� | �� | ���ɱ�
 *          #file_dir | NULL | �� | �� | �� | ���ɱ�
 *          #file_name | NULL | �� | �� | �� | ���ɱ�
 *          #file_backup_kind | #DDS_LOG_BACKUP_NOTUSED_QOS | �� | �� | �� | ���ɱ�
 *          #file_backup_param | 0 | �� | �� | �� | ���ɱ�
 */

typedef struct DDS_LogQosPolicy
{
    /** @brief   ������־����̨��������������룬Ϊ ::DDS_LogType ö��ֵ��λ��Ľ���� */
    DDS_ULong console_mask;
    /** @brief   ������־��־�ļ���������������룬Ϊ ::DDS_LogType ö��ֵ��λ��Ľ���� */
    DDS_ULong file_mask;
    /**
     * @brief   ������־�������롣 
     * 
     * @note    �ó�Ա�ѱ��������� #console_mask �Լ� #file_mask ���档
     */
    DDS_ULong local_level_mask;
    /** @brief   �����Ƿ�ʹ�ֲܷ�ʽ��־�� */
    DDS_Boolean enable_distributed_log;
	/** @brief   �ֲ�ʽ��־ʹ�ܽ�����־�� */
    DDS_Boolean enable_distributed_log_finished;
    /** @brief   ���Ʒֲ�ʽ��־���������� */
    DDS_Long distributed_log_writer_domain_id;
    /** @brief   ���Ʒֲ�ʽ��־����Ϊ ::DDS_LogType ö��ֵ��λ��Ľ���� */
    DDS_Long distributed_log_level_mask;
    /** @brief   ָ��������־�ļ�������ļ�·�����������ΪNULL����ʹ��Ĭ��·������ǰ����Ŀ¼���� */
    DDS_CharSeq file_dir;
    /** @brief   ָ��������־�ļ�������ļ������������ΪNULL����ʹ��Ĭ�����ƣ���������.ddslog���� */
    DDS_CharSeq file_name;
    /** @brief   ָ��������־�ļ��ı���ģʽ�� */
    DDS_LogBackupKind file_backup_kind;
    /**
     * @brief   ������־�ļ�������ز�����
     *          ��file_backup_kind������ΪDDS_LOG_BACKUP_NOTUSED_QOSʱ���ò�����Ч��
     *          ��file_backup_kind������ΪDDS_LOG_BACKUP_FILE_SIZE_QOSʱ���ò���Ϊ��־�ļ���С���ޣ�KB����
     *          ��file_backup_kind������ΪDDS_LOG_BACKUP_TIME_INTERVAL_QOSʱ���ò���Ϊʱ������s����
     */
    DDS_Long file_backup_param;

}DDS_LogQosPolicy;

#endif /* DDSLogQosPolicy_h__*/
