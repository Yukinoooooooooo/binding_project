/**
 * @file:       ReturnCode_t.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#if !defined(_RETURNCODE_T_H)
#define _RETURNCODE_T_H

/**
 * @enum    DDS_ReturnCode_t
 *
 * @ingroup CoreBaseStruct
 * 
 * @brief   ZRDDS�ӿڵķ���ֵ���͡�
 */

typedef enum DDS_ReturnCode_t
{
    /** @brief ִ�гɹ��� @ingroup CoreBaseStruct */
    DDS_RETCODE_OK = 0,
    /** @brief ִ�г��� @ingroup CoreBaseStruct  */
    DDS_RETCODE_ERROR = 1,
    /** @brief ��֧�ֲ����� @ingroup CoreBaseStruct  */
    DDS_RETCODE_UNSUPPORTED = 2,
    /** @brief ����ȷ�Ĳ����� @ingroup CoreBaseStruct  */
    DDS_RETCODE_BAD_PARAMETER = 3,
    /** @brief ���ò�����ǰ������δ���㡣 @ingroup CoreBaseStruct  */
    DDS_RETCODE_PRECONDITION_NOT_MET = 4,
    /** @brief ��Դ������ @ingroup CoreBaseStruct  */
    DDS_RETCODE_OUT_OF_RESOURCES = 5,
    /** @brief ʵ��δʹ�ܣ����ܽ��иò����� @ingroup CoreBaseStruct  */
    DDS_RETCODE_NOT_ENABLED = 6,
    /** @brief ��ͼ�޸�ʹ�ܺ����޸ĵ�Qos�� @ingroup CoreBaseStruct */
    DDS_RETCODE_IMMUTABLE_POLICY = 7,
    /** @brief ��һ�µ�Qos�� @ingroup CoreBaseStruct  */
    DDS_RETCODE_INCONSISTENT = 8,
    /** @brief ��ͼɾ���Ѿ���ɾ����ʵ�塣 @ingroup CoreBaseStruct  */
    DDS_RETCODE_ALREADY_DELETED = 9,
    /** @brief ������ʱ�� @ingroup CoreBaseStruct  */
    DDS_RETCODE_TIMEOUT = 10,
    /** @brief �ڶ����ݵ�ʱ��û����Ч�����ݡ� @ingroup CoreBaseStruct  */
    DDS_RETCODE_NO_DATA = 11,
    /** @brief �Ƿ��Ĳ����� @ingroup CoreBaseStruct  */
    DDS_RETCODE_ILLEGAL_OPERATION = 12,
    /** @brief ������ȫԭ�򱻾ܾ��� @ingroup CoreBaseStruct  */
    DDS_RETCODE_NOT_ALLOWED_BY_SEC = 13
}DDS_ReturnCode_t;

#endif  /*_RETURNCODE_T_H*/
