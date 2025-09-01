/**
 * @file:       PropertyList.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#ifndef PropertyList_h__
#define PropertyList_h__

#include "OsResource.h"
#include "ZRDDSCommon.h"

/**
 * @typedef struct DDS_Property
 *
 * @ingroup CoreBaseStruct
 *
 * @brief   <����-ֵ>��ֵ�ԣ������ڷ��ֽ׶δ洢�ڵ���Ϣ��
 * 
 * @details �ֽ׶�֧�ֵ�������:
 *          - "dds.sys_info.hostname": ��ʾDDS����������������
 *          - "dds.sys_info.username": ��ʾ����DDS������û�
 *          - "dds.sys_info.process_id": ��ʾDDS����Ľ���ID
 *          - "dds.sys_info.host_ip": ��ʾDDS������������IP
 *          - "dds.sys_info.executable_filepath": ��ʾDDS����Ŀ�ִ�г�������·��
 */

typedef struct DDS_Property
{
    /** @brief   ���ƣ��ɳ����Լ�Լ���� */
    DDS_Char* name;
    /** @brief   ���ƶ�Ӧ��ֵ�� */
    DDS_Char* value;
}DDS_Property;

#define BUFFERED_PROPERTY_NUM 16

/**
 * @struct DDS_PropertyList
 *
 * @ingroup CoreBaseStruct
 *
 * @brief   <����-ֵ>��ֵ���б��װ��
 */

typedef struct DCPSDLL DDS_PropertyList
{
    /** @brief   �б���Property������*/
    DDS_ULong size;
    /** @brief   �б��������顣*/
    DDS_Property buffer[BUFFERED_PROPERTY_NUM];
    /** @brief   ������������ʱ���������Ŀռ䡣*/
    DDS_Property* values;
#ifdef _ZRDDSCPPINTERFACE
    DDS_PropertyList();
#endif
}DDS_PropertyList;

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @fn  DCPSDLL DDS_Long DDS_PropertyInitial(DDS_Property* self, const DDS_Char* name, const DDS_Char* value);
 *
 * @ingroup CoreBaseFunction
 *
 * @brief   ��ʼ�����Լ�ֵ�ԣ�����ռ䡣
 *
 * @param [in,out]  self    ָ��Ŀ�ꡣ
 * @param   name            ���ơ�
 * @param   value           ֵ��
 *
 * @return  0��ʾ�ɹ���-1��ʾʧ�ܡ�
 */

DCPSDLL DDS_Long DDS_PropertyInitial(DDS_Property* self, const DDS_Char* name, const DDS_Char* value);

/**
 * @fn  DCPSDLL DDS_Long DDS_PropertyClear(DDS_Property* self);
 *
 * @ingroup CoreBaseFunction
 *
 * @brief   �����ֵ�Կռ䡣
 *
 * @param [in,out]  self    ָ��Ŀ�ꡣ
 *
 * @return  ���Ƿ���0��ʾ�ɹ���
 */

DCPSDLL DDS_Long DDS_PropertyClear(DDS_Property* self);

/**
 * @fn  DCPSDLL void DDS_PropertyListInitial(DDS_PropertyList* self);
 *
 * @ingroup CoreBaseFunction
 *
 * @brief   ��ʼ��һ���յ��б�
 *
 * @param [in,out]  self    ָ��Ŀ�ꡣ
 */

DCPSDLL void DDS_PropertyListInitial(DDS_PropertyList* self);

/**
 * @fn  DCPSDLL DDS_Long DDS_PropertyListInsert(DDS_PropertyList* self, const DDS_Char* name, const DDS_Char* value, DDS_Property* newPro);
 *
 * @ingroup CoreBaseFunction
 *
 * @brief   ����ָ��������Property���б��С�
 *
 * @param [in,out]  self    ָ������Ŀ�ꡣ
 * @param   name            Property�ַ����͵����ƣ���NULL��β��
 * @param   value           Property�������͵�ֵ�����Բ���NULL��β��
 * @param [in,out]  newPro  �µ�Property�Ŀռ䣬Ϊ��ʱʹ��name/valueָ����
 *
 * @return  0��ʾ�ɹ���С��0��ʾʧ�ܡ�
 */

DCPSDLL DDS_Long DDS_PropertyListInsert(DDS_PropertyList* self,
    const DDS_Char* name,
    const DDS_Char* value,
    DDS_Property* newPro);

/**
 * @fn  DCPSDLL DDS_Long DDS_PropertyListCopy(DDS_PropertyList* self, const DDS_PropertyList* right);
 *
 * @ingroup CoreBaseFunction
 *
 * @brief   ����PropertyList��
 *
 * @param [in,out]  self    ָ��Ŀ��,�����ԭ�е����ݡ�
 * @param   right           ָ������Դ��
 *
 * @return  0��ʾ�ɹ���С��0��ʾʧ�ܡ�
 */

DCPSDLL DDS_Long DDS_PropertyListCopy(DDS_PropertyList* self,
    const DDS_PropertyList* right);

/**
 * @fn  DCPSDLL DDS_Property* DDS_PropertyListGet(DDS_PropertyList* self, const char* name);;
 *
 * @ingroup CoreBaseFunction
 *
 * @brief   ����Property��
 *
 * @param [in,out]  self    ָ��Ŀ�ꡣ
 * @param   name            ��Ҫ���ҵ���������
 *
 * @return  �ɹ����ز��ҵ�Property�����򷵻�NULL��
 */

DCPSDLL DDS_Property* DDS_PropertyListGet(DDS_PropertyList* self,
    const char* name);

/**
 * @fn  DCPSDLL DDS_Long DDS_PropertyListClear(DDS_PropertyList* self);
 *
 * @ingroup CoreBaseFunction
 *
 * @brief   ����б����տռ䡣
 *
 * @param [in,out]  self    ָ��Ŀ�ꡣ
 *
 * @return  0��ʾ�ɹ���С��0��ʾʧ�ܡ�
 */

DCPSDLL DDS_Long DDS_PropertyListClear(DDS_PropertyList* self);

/**
 * @fn  DCPSDLL DDS_Property* DDS_PropertyListAt(DDS_PropertyList* self, DDS_ULong index);
 *
 * @ingroup CoreBaseFunction
 *
 * @brief   �±����������
 *
 * @param [in,out]  self    ָ��Ŀ�ꡣ
 * @param   index           ָ���±ꡣ
 *
 * @return  NULL��ʾ������Χ������Ϊ��Ч�������б�
 */

DCPSDLL DDS_Property* DDS_PropertyListAt(DDS_PropertyList* self, DDS_ULong index);

#ifdef __cplusplus
}
#endif

#endif /* PropertyList_h__*/
