/**
 * @file:       SRIOPass_t.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#ifndef SRIOPass_H
#define SRIOPass_H

#include "OsResource.h"
#ifdef _ZRDDS_MPORT_FPGA_SRIO
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#ifdef _LINUX
#include <sys/file.h>
#include <unistd.h>
#include <dirent.h>
#endif

typedef struct MessageBlock MessageBlock;

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @ingroup	BaseTypeģ��
 * @struct  SRIOPass_t
 *
 * @brief	��ʹ��SRIO��ʽ���п���䴫��ʱ��SRIOPass_t��ʾһ������ͨ���������գ����ǵ�ǰ�ڵ�����ڻ����FPGA�ڵ�֮�������ͨ��
 *
 * @author	Wby
 * @date	2021/6/21
 */

typedef struct SRIOPass_t
{
    /** @brief   FCͨ����Ψһ��ʶ��key. */
    ZR_UINT32 num;
    /** @brief   FCͨ���ı�ʶ. */
    ZR_UINT32 fc_msg_id;
    /** @brief	   Զ��FC��id. */
    ZR_UINT32 fc_remote_id;
    /** @brief	   SRIO�ķ��ͽڵ�id. */
    ZR_UINT32 srio_src_id;
    /** @brief   SRIO�Ľ��սڵ�id. */
    ZR_UINT32 srio_dst_id;
    /** @brief   ������Ϣ. */
    ZR_UINT32 db;
    /** @brief	   SRIO���յ�ַ. */
    ZR_UINT64 srio_addr;
    /** @brief   ͨ��ʹ��״̬. */
    ZR_BOOLEAN enable;
    /** @brief	   ͨ��ʹ��״̬��δʹ��Ϊ0����ʹ��Ϊ����id. */
    ZR_UINT32 used;
}SRIOPass_t;

/**
* @fn  ZR_BOOLEAN SRIOPassIsEqual(SRIOPass_t* left, SRIOPass_t* right);
*
* @brief   �Ƚ�SRIOPass��
*
* @author  Wby
* @date    2022/8/11
*
* @param   left    ��Ϊ�Ƚϵ�ǰһ��SRIOPass��
* @param   right    ��Ϊ�Ƚϵĺ�һ��SRIOPass��
*
* @return  true��ʾ��ͬ��false��ʾ����ͬ��
*/

ZR_BOOLEAN SRIOPassIsEqual(SRIOPass_t* left, SRIOPass_t* right);

/**
* @fn  ZR_INT32 SRIOPassCopy(SRIOPass_t* src, SRIOPass_t* dst);
*
* @brief   ����SRIOPass��
*
* @author  Wby
* @date    2022/8/11
*
* @param   src    ������ԴSRIOPass��
* @param   [in,out]   dst    ����Ŀ��SRIOPass��
*
* @return  0��ʾ�ɹ���С��0��ʾʧ�ܡ�
*/

ZR_INT32 SRIOPassCopy(SRIOPass_t* src, SRIOPass_t* dst);

/**
 * @fn  ZR_INT32 SRIOPassFromString(SRIOPass_t* self, const ZR_INT8* strformat);
 *
 * @brief   ���ַ����͹���SRIOPass��
 *
 * @author  Wby
 * @date    2021/6/21
 *
 * @param [in,out]  self    ת�������
 * @param   strformat       ������ַ�����
 *
 * @return  0��ʾ�ɹ���С��0��ʾʧ�ܡ�
 */

ZR_INT32 SRIOPassFromString(SRIOPass_t* self, const ZR_INT8* strformat);

/**
 * @fn  ZR_BOOLEAN SRIOPassSerialize(const SRIOPass_t* pass, MessageBlock* dst, ZR_BOOLEAN littleEndian);
 *
 * @brief   ���л�SRIOPass��
 *
 * @author  Wby
 * @date    2021/6/21
 *
 * @param   pass            ��Ҫ���л���SRIOPass��
 * @param [in,out]  dst     Ŀ�껺������
 * @param   littleEndian    Ҫ�����
 *
 * @return  true��ʾ�ɹ���false��ʾʧ�ܡ�
 */

ZR_BOOLEAN SRIOPassSerialize(const SRIOPass_t* pass, MessageBlock* dst, ZR_BOOLEAN littleEndian);

/**
 * @fn  ZR_BOOLEAN SRIOPassDeserialize(SRIOPass_t* addr, MessageBlock* src, ZR_BOOLEAN littleEndian);
 *
 * @brief   �����л�SRIOPass��
 *
 * @author  Wby
 * @date    2021/6/21
 *
 * @param   pass            �����л��Ľ����
 * @param [in,out]  dst     Դ��������
 * @param   littleEndian    Ҫ�����
 *
 * @return  true��ʾ�ɹ���false��ʾʧ�ܡ�
 */

ZR_BOOLEAN SRIOPassDeserialize(SRIOPass_t* addr, MessageBlock* src, ZR_BOOLEAN littleEndian);

/**
 * @fn  ZR_INT8* SRIOPassListToString(const SRIOPass_t* SRIOPass);
 *
 * @brief   ת���ɿɴ�ӡ���ַ��������ڵ��ԡ�
 *
 * @author  Wby
 * @date    2021/6/21
 *
 * @param   SRIOPass ָ��Ŀ�ꡣ
 *
 * @return  �����ַ�����
 */

ZR_INT8* SRIOPassToString(const SRIOPass_t* SRIOPass);
ZR_INT8* SRIOPassToString2(const SRIOPass_t* SRIOPass);

/**
 * @def BUFFERED_SRIOPASS_NUM
 *
 * @brief   SRIOPassList����󻺴��SRIOPass������
 *
 * @author  Wby
 * @date    2021/6/21
 */

#define BUFFERED_SRIOPASS_NUM 32

/**
 * @typedef struct SRIOPassList_t
 *
 * @brief   ��SRIOPassList_t���ڱ���һ��������������/��ͨ����Ӧ��SRIOPass��
 */

typedef struct SRIOPassList_t
{
    /** @brief   �б���SRIOPass������*/
    ZR_UINT32 m_size;
    /** @brief   �б��������顣*/
    SRIOPass_t m_buffer[BUFFERED_SRIOPASS_NUM];
    /** @brief   ������������ʱ���������Ŀռ䡣*/
    SRIOPass_t* m_values;
}SRIOPassList_t;

/**
 * @fn  SRIOPass_t* SRIOPassListFind(SRIOPassList_t* self, ZR_UINT32 msg_id);
 *
 * @brief   ��ȡָ���Զ�fc�˿ں�ͨ���ŵ�SRIOPass��
 *
 * @author  Wby
 * @date    2021/6/25
 *
 * @param [in,out]  self    ָ��Ŀ�ꡣ
 * @param   remote_fc_id           ָ���Զ�fc�˿ڡ�
 * @param   msg_id           ָ��ͨ���š�
 *
 * @return  NULL��ʾ��ȡʧ�ܣ����򷵻�Ԫ�ء�
 */

SRIOPass_t* SRIOPassListFind(SRIOPassList_t* self, ZR_UINT32 remote_fc_id, ZR_UINT32 msg_id);

/**
 * @fn  const ZR_INT8* SRIOPassListToString(const SRIOPassList_t* SRIOPassList);
 *
 * @brief   ת��Ϊһ���ɴ�ӡ���ַ��������ڵ��������
 *
 * @author  Wby
 * @date    2021/6/21
 *
 * @param   SRIOPassList ָ��Ŀ�ꡣ
 *
 * @return  "Empty"Ϊ�գ�����Ϊn�У�ÿһ�д���һ��SRIOPass��
 */

ZR_INT8* SRIOPassListToString(const SRIOPassList_t* SRIOPassList);

/**
 * @fn  void SRIOPassListInitial(SRIOPassList_t* self);
 *
 * @brief   ��ʼ���յ��б�
 *
 * @author  Wby
 * @date    2021/6/21
 *
 * @param [in,out]  self    If non-null, the self.
 */

void SRIOPassListInitial(SRIOPassList_t* self);

/**
 * @fn  ZR_UINT32 SRIOPassListInsertSRIOPass(SRIOPassList_t* self, const SRIOPass_t* pass);
 *
 * @brief   ����һ��SRIOPass�����б�
 *
 * @author  Wby
 * @date    2021/6/21
 *
 * @param [in,out]  self    ͨ���б�
 * @param   addr            ��Ҫ�����ͨ����
 *
 * @return  �ɹ�����0��С�����ʾʧ�ܡ�
 */

ZR_INT32 SRIOPassListInsertSRIOPass(SRIOPassList_t* self, const SRIOPass_t* pass);

/**
 * @fn  ZR_INT32 SRIOPassListCopy(SRIOPassList_t* self, const SRIOPassList_t* right);
 *
 * @brief   ����SRIOPassList��
 *
 * @author  Wby
 * @date    2021/6/21
 *
 * @param [in,out]  self    ָ��Ŀ�ꡣ
 * @param   right           ����������Դ��
 *
 * @return  0��ʾ�ɹ���С��0��ʾʧ�ܡ�
 */

ZR_INT32 SRIOPassListCopy(SRIOPassList_t* self, const SRIOPassList_t* right);

/**
 * @fn  ZR_UINT32 SRIOPassListClear(SRIOPassList_t* self);
 *
 * @brief   ����б����ͷſռ䣬������SRIOPassListʱʹ�ã����������ڴ�й©��
 *
 * @author  Wby
 * @date    2021/6/21
 *
 * @param [in,out]  self    ��Ҫ��յ��б�
 *
 * @return  �ɹ�����0�����򷵻�С��0.
 */

ZR_UINT32 SRIOPassListClear(SRIOPassList_t* self);

/**
 * @fn  ZR_UINT32 SRIOPassListGetSize(const SRIOPassList_t* self);
 *
 * @brief   ��ȡͨ���б����л���С��
 *
 * @author  Wby
 * @date    2021/6/21
 *
 * @param   self    ͨ���б�
 *
 * @return  0��ʾʧ�ܣ�������ʾ���л������С��
 */

ZR_UINT32 SRIOPassListGetSize(const SRIOPassList_t* self);

/**
 * @fn  SRIOPass_t* SRIOPassListAt(SRIOPassList_t* self, ZR_UINT32 index);
 *
 * @brief   ��ȡָ���±��SRIOPass��
 *
 * @author  Wby
 * @date    2021/6/21
 *
 * @param   self    ָ��ͨ���б�
 * @param   index   ָ���±ꡣ
 *
 * @return  NULL��ʾ��ȡʧ�ܣ����򷵻�Ԫ�ء�
 */

SRIOPass_t* SRIOPassListAt(SRIOPassList_t* self, ZR_UINT32 index);

/**
 * @fn  const SRIOPass_t* SRIOPassListConstAt(SRIOPassList_t* self, ZR_UINT32 index);
 *
 * @brief   const�汾���±������
 *
 * @author  Wby
 * @date    2021/6/21
 *
 * @param [in,out]  self    ָ��Ŀ�ꡣ
 * @param   index   ָ���±ꡣ
 *
 * @return  NULL��ʾ��ȡʧ�ܣ����򷵻�Ԫ�ء�
 */

const SRIOPass_t* SRIOPassListConstAt(const SRIOPassList_t* self, ZR_UINT32 index);

/**
 * @fn  ZR_BOOLEAN SRIOPassListSerialize(const SRIOPassList_t* self, MessageBlock* dst, ZR_BOOLEAN littleEndian);
 *
 * @brief   ���л�SRIOPassList��
 *
 * @author  Wby
 * @date    2021/6/21
 *
 * @param   self            ��Ҫ���л���SRIOPassList��
 * @param [in,out]  dst     Ŀ�껺������
 * @param   littleEndian    �Ƿ�ʹ�ö���
 *
 * @return  true��ʾ�ɹ���false��ʾʧ�ܡ�
 */

ZR_BOOLEAN SRIOPassListSerialize(const SRIOPassList_t* self, MessageBlock* dst, ZR_BOOLEAN littleEndian);

/**
 * @fn  ZR_BOOLEAN SRIOPassListDeserialize(SRIOPassList_t* self, MessageBlock* src, ZR_BOOLEAN littleEndian);
 *
 * @brief   �����л�SRIOPassList��
 *
 * @author  Wby
 * @date    2021/6/21
 *
 * @param [in,out]  self    �����л������
 * @param [in,out]  src     Դ��������
 * @param   littleEndian    �Ƿ�ʹ�ö���
 *
 * @return  true��ʾ�ɹ���false��ʾʧ�ܡ�
 */

ZR_BOOLEAN SRIOPassListDeserialize(SRIOPassList_t* self, MessageBlock* src, ZR_BOOLEAN littleEndian);

/**
 * @typedef struct SRIOConfig_t
 *
 * @brief   ��SRIOConfig_t���ڱ���һ��������������/��ͨ����Ӧ��SRIOPass��
 */

typedef struct SRIOConfig_t
{
    /** @brief   ��������������ڵ����ڻ���Ŀ����FC��id��Ψһ��ʶ�� */
    DDS_ULong fc_no;
    // TODO
    DDS_ULong temp;
    /** @brief   ��������������ڵ����ڻ���Ŀ����FC��id�� */
    DDS_ULong fc_id;
    /** @brief   ��������������ڵ����ڻ�������п���䷢��ͨ���б� */
    SRIOPassList_t srio_send_list;
    /** @brief   ��������������ڵ����ڻ�������п�������ͨ���б� */
    SRIOPassList_t srio_recv_list;
}SRIOConfig_t;

/**
 * @fn  ZR_BOOLEAN SRIOConfigSerialize(const SRIOConfig_t* self, MessageBlock* dst, ZR_BOOLEAN littleEndian);
 *
 * @brief   ���л�SRIOConfig_t��
 *
 * @author  Wby
 * @date    2021/9/30
 *
 * @param   self            ��Ҫ���л���SRIOConfig_t��
 * @param [in,out]  dst     Ŀ�껺������
 * @param   littleEndian    �Ƿ�ʹ�ö���
 *
 * @return  true��ʾ�ɹ���false��ʾʧ�ܡ�
 */

ZR_BOOLEAN SRIOConfigSerialize(const SRIOConfig_t* self, MessageBlock* dst, ZR_BOOLEAN littleEndian);

/**
 * @fn  ZR_BOOLEAN SRIOConfigDeserialize(SRIOConfig_t* self, MessageBlock* src, ZR_BOOLEAN littleEndian);
 *
 * @brief   �����л�SRIOConfig_t��
 *
 * @author  Wby
 * @date    2021/9/30
 *
 * @param [in,out]  self    �����л������
 * @param [in,out]  src     Դ��������
 * @param   littleEndian    �Ƿ�ʹ�ö���
 *
 * @return  true��ʾ�ɹ���false��ʾʧ�ܡ�
 */

ZR_BOOLEAN SRIOConfigDeserialize(SRIOConfig_t* self, MessageBlock* src, ZR_BOOLEAN littleEndian);
   
/**
 * @fn  void SRIOConfigInitial(SRIOConfig_t* self);
 *
 * @brief   ��ʼ���յ��Ž�·�ɡ�
 *
 * @author  Wby
 * @date    2021/9/30
 *
 * @param [in,out]  self    If non-null, the self.
 */

void SRIOConfigInitial(SRIOConfig_t* self);

/**
 * @fn  ZR_UINT32 SRIOConfigClear(SRIOConfig_t* self);
 *
 * @brief   ����Žӣ����ͷſռ䣬������SRIOConfigʱʹ�ã����������ڴ�й©��
 *
 * @author  Wby
 * @date    2021/9/30
 *
 * @param [in,out]  self    ��Ҫ��յ��Žӡ�
 *
 * @return  �ɹ�����0�����򷵻�С��0.
 */

ZR_UINT32 SRIOConfigClear(SRIOConfig_t* self);

/**
 * @fn  ZR_INT32 SRIOConfigCopy(SRIOConfig_t* self, const SRIOConfig_t* right);
 *
 * @brief   ����SRIOConfig_t��
 *
 * @author  Wby
 * @date    2021/9/30
 *
 * @param [in,out]  self    ָ��Ŀ�ꡣ
 * @param   right           ����������Դ��
 *
 * @return  0��ʾ�ɹ���С��0��ʾʧ�ܡ�
 */

ZR_INT32 SRIOConfigCopy(SRIOConfig_t* self, const SRIOConfig_t* right);

/**
 * @fn  ZR_UINT32 SRIOConfigGetSize(const SRIOConfig_t* self);
 *
 * @brief   ��ȡ�Ž����л���С��
 *
 * @author  Wby
 * @date    2021/9/30
 *
 * @param   self    �Žӡ�
 *
 * @return  0��ʾʧ�ܣ�������ʾ���л������С��
 */

ZR_UINT32 SRIOConfigGetSize(const SRIOConfig_t* self);

/**
 * @fn  const ZR_INT8* SRIOConfigToString(const SRIOConfig_t* SRIOConfig);
 *
 * @brief   ת��Ϊһ���ɴ�ӡ���ַ��������ڵ��������
 *
 * @author  Wby
 * @date    2021/10/9
 *
 * @param   SRIOConfig ָ��Ŀ�ꡣ
 *
 * @return  "Empty"Ϊ�գ�����Ϊn�飬ÿ��ֳ����δ���һ��SRIOConfig��
 */

ZR_INT8* SRIOConfigToString(const SRIOConfig_t* SRIOConfig);

#define BUFFERED_SRIOCONFIG_NUM 2

/**
 * @typedef struct SRIOPassList_t
 *
 * @brief   ��SRIOPassList_t���ڱ���һ��������������/��ͨ����Ӧ��SRIOPass��
 */

typedef struct SRIOConfigList_t
{
    /** @brief   �б���SRIOConfig������*/
    ZR_UINT32 m_size;
    /** @brief   �б��������顣*/
    SRIOConfig_t m_buffer[BUFFERED_SRIOCONFIG_NUM];
    /** @brief   ������������ʱ���������Ŀռ䡣*/
    SRIOConfig_t* m_values;
}SRIOConfigList_t;

/**
* @fn  ZR_BOOLEAN SRIOConfigListFromXML(SRIOConfigList_t* self, const ZR_INT8* xmlPath, FILE* passFile, const ZR_UINT32 cabNo, const ZR_UINT32 chassisNo);
*
* @brief   ����XML��ʽ�����ñ����ݲ�������SRIOConfigList_t��
*
* @author  Wby
* @date    2021/12/1
*
* @param  [in,out] self            ��Ҫ�����SRIOConfigList_t��
* @param   xmlPath         ���ñ��·����
* @param   passFile         ͨ��ʹ��״̬�ļ���
* @param   cabNo         ����š�
* @param   chassisNo         ����š�
*
* @return  true��ʾ�ɹ���false��ʾʧ�ܡ�
*/

ZR_BOOLEAN SRIOConfigListFromXML(SRIOConfigList_t* self, const ZR_INT8* xmlPath, FILE* passFile, const ZR_UINT32 cabNo, const ZR_UINT32 chassisNo);

/**
 * @fn  ZR_BOOLEAN SRIOConfigListSerialize(const SRIOConfigList_t* self, MessageBlock* dst, ZR_BOOLEAN littleEndian);
 *
 * @brief   ���л�SRIOConfigList_t��
 *
 * @author  Wby
 * @date    2021/9/30
 *
 * @param   self            ��Ҫ���л���SRIOConfigList_t��
 * @param [in,out]  dst     Ŀ�껺������
 * @param   littleEndian    �Ƿ�ʹ�ö���
 *
 * @return  true��ʾ�ɹ���false��ʾʧ�ܡ�
 */

ZR_BOOLEAN SRIOConfigListSerialize(const SRIOConfigList_t* self, MessageBlock* dst, ZR_BOOLEAN littleEndian);

/**
 * @fn  ZR_BOOLEAN SRIOConfigListDeserialize(SRIOConfigList_t* self, MessageBlock* src, ZR_BOOLEAN littleEndian);
 *
 * @brief   �����л�SRIOConfigList��
 *
 * @author  Wby
 * @date    2021/9/30
 *
 * @param [in,out]  self    �����л������
 * @param [in,out]  src     Դ��������
 * @param   littleEndian    �Ƿ�ʹ�ö���
 *
 * @return  true��ʾ�ɹ���false��ʾʧ�ܡ�
 */

ZR_BOOLEAN SRIOConfigListDeserialize(SRIOConfigList_t* self, MessageBlock* src, ZR_BOOLEAN littleEndian);

/**
 * @fn  ZR_UINT32 SRIOConfigListInsertSRIOConfig(SRIOConfigList_t* self, const SRIOConfig_t* pass);
 *
 * @brief   ����һ��SRIOPass�����б�
 *
 * @author  Wby
 * @date    2021/6/21
 *
 * @param [in,out]  self    ͨ���б�
 * @param   addr            ��Ҫ�����ͨ����
 *
 * @return  �ɹ�����0��С�����ʾʧ�ܡ�
 */

ZR_INT32 SRIOConfigListInsertSRIOConfig(SRIOConfigList_t* self, const SRIOConfig_t* config);

/**
 * @fn  void SRIOConfigListInitial(SRIOConfigList_t* self);
 *
 * @brief   ��ʼ���յ��Ž�·�ɱ�
 *
 * @author  Wby
 * @date    2021/9/30
 *
 * @param [in,out]  self    If non-null, the self.
 */

void SRIOConfigListInitial(SRIOConfigList_t* self);

/**
 * @fn  ZR_UINT32 SRIOConfigListClear(SRIOConfigList_t* self);
 *
 * @brief   ����Žӱ����ͷſռ䣬������SRIOConfigListʱʹ�ã����������ڴ�й©��
 *
 * @author  Wby
 * @date    2021/9/30
 *
 * @param [in,out]  self    ��Ҫ��յ��Žӱ�
 *
 * @return  �ɹ�����0�����򷵻�С��0.
 */

ZR_UINT32 SRIOConfigListClear(SRIOConfigList_t* self);

/**
 * @fn  ZR_INT32 SRIOConfigListCopy(SRIOConfigList_t* self, const SRIOConfigList_t* right);
 *
 * @brief   ����SRIOConfigList_t��
 *
 * @author  Wby
 * @date    2021/9/30
 *
 * @param [in,out]  self    ָ��Ŀ�ꡣ
 * @param   right           ����������Դ��
 *
 * @return  0��ʾ�ɹ���С��0��ʾʧ�ܡ�
 */

ZR_INT32 SRIOConfigListCopy(SRIOConfigList_t* self, const SRIOConfigList_t* right);

/**
 * @fn  ZR_UINT32 SRIOConfigListGetSize(const SRIOConfigList_t* self);
 *
 * @brief   ��ȡ�Žӱ����л���С��
 *
 * @author  Wby
 * @date    2021/9/30
 *
 * @param   self    �Žӱ�
 *
 * @return  0��ʾʧ�ܣ�������ʾ���л������С��
 */

ZR_UINT32 SRIOConfigListGetSize(const SRIOConfigList_t* self);

/**
 * @fn  SRIOConfig_t* SRIOConfigListAt(SRIOConfigList_t* self, ZR_UINT32 index);
 *
 * @brief   ��ȡָ���±��SRIOConfig��
 *
 * @author  Wby
 * @date    2021/9/30
 *
 * @param   self    ָ���Žӱ�
 * @param   index   ָ���±ꡣ
 *
 * @return  NULL��ʾ��ȡʧ�ܣ����򷵻�Ԫ�ء�
 */

SRIOConfig_t* SRIOConfigListAt(SRIOConfigList_t* self, ZR_UINT32 index);

/**
 * @fn  const SRIOConfig_t* SRIOConfigListConstAt(SRIOConfigList_t* self, ZR_UINT32 index);
 *
 * @brief   const�汾���±������
 *
 * @author  Wby
 * @date    2021/9/30
 *
 * @param [in,out]  self    ָ��Ŀ�ꡣ
 * @param   index   ָ���±ꡣ
 *
 * @return  NULL��ʾ��ȡʧ�ܣ����򷵻�Ԫ�ء�
 */

const SRIOConfig_t* SRIOConfigListConstAt(const SRIOConfigList_t* self, ZR_UINT32 index);

/**
 * @fn  SRIOPass_t* SRIOConfigListFindPass(SRIOConfigList_t* self, ZR_UINT32 fc_NO, ZR_UINT32 msg_id);
 *
 * @brief   ��ȡָ������fc�˿ڡ��Զ�fc�˿ں�ͨ���ŵ�SRIOPass��
 *
 * @author  Wby
 * @date    2021/10/8
 *
 * @param [in,out]  self    ָ��Ŀ�ꡣ
 * @param   local_fc_id           ָ������fc�˿ڡ�
 * @param   remote_fc_id           ָ���Զ�fc�˿ڡ�
 * @param   msg_id           ָ��ͨ���š�
 *
 * @return  NULL��ʾ��ȡʧ�ܣ����򷵻�Ԫ�ء�
 */

SRIOPass_t* SRIOConfigListFindPass(SRIOConfigList_t* self, ZR_UINT32 local_fc_id, ZR_UINT32 remote_fc_id, ZR_UINT32 msg_id, ZR_BOOLEAN isSend);

/**
 * @fn  const ZR_INT8* SRIOConfigListToString(const SRIOConfigList_t* SRIOConfigList);
 *
 * @brief   ת��Ϊһ���ɴ�ӡ���ַ��������ڵ��������
 *
 * @author  Wby
 * @date    2021/10/9
 *
 * @param   SRIOConfigList ָ��Ŀ�ꡣ
 *
 * @return  "Empty"Ϊ�գ�����Ϊn�飬ÿ��ֳ����δ���һ��SRIOConfig��
 */

ZR_INT8* SRIOConfigListToString(const SRIOConfigList_t* SRIOConfigList);

#ifdef __cplusplus
}
#endif
#endif // _ZRDDS_MPORT_FPGA_SRIO
#endif