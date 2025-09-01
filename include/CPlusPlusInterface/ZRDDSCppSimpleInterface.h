#ifndef ZRDDSCppSimpleInterface_h__
#define ZRDDSCppSimpleInterface_h__

#include "ZROSDefine.h"

#ifdef _ZRDDS_INCLUDE_SIMPLE_INTERFACE

#include "DomainParticipantFactory.h"
#include "DomainParticipant.h"
#include "ZRDDSTypeSupport.h"
#include "DataReader.h"
#include "DataWriter.h"
#include "ZRBuiltinTypesTypeSupport.h"
#include "ZRBuiltinTypesDataReader.h"
#include "ZRBuiltinTypesDataWriter.h"
#include "DataReaderListener.h"
#include "ZRSleep.h"

namespace DDS {

/**
 * @class   DDSIF DDSIF_SUSTAIN
 *
 * @brief   DDS��CPP���׽ӿڣ����еķ�����Ϊ��̬������
 */

class DCPSDLL DDSIF_SUSTAIN
{
public:

    /**
     * @fn  static DomainParticipantFactory* DDSIF_SUSTAIN::Init( const Char* qosFilePath, const Char* qosName);
     *
     * @brief   ��ָ�����ó�ʼ��DDS�м����ֻ�����������ʼ��ʱ����һ�μ��ɡ�
     *
     * @param   qosFilePath QoS�����ļ���·���������Ǿ���·����Ҳ�����ǳ�������Ŀ¼�����·����
     *                      ΪNULLʱ��Ĭ��ʹ������Ŀ¼�� ZRDDS_QOS_PROFILES.xml �����ļ���
     * @param   qosName     QoS�����ļ��й���QoS�������ƣ�DDS���� default_lib::default_profile::qosName �����QoS��ʼ��DDS�򳧣�
     *                      ����ΪNULL������ʹ�������ļ�������Ϊdefault�����á�
     *
     * @return  NULL��ʾʧ�ܣ����򷵻�DDS�򹤳�������
     */

    static DomainParticipantFactory* Init(
        const Char* qosFilePath,
        const Char* qosName);

    /**
     * @fn  static DomainParticipant* DDSIF_SUSTAIN::CreateDP( const DomainId_t domainId, const Char* qos_name);
     *
     * @brief   DDS����������ߣ���ָ�������QoS�������ƣ�ͬһ����ſ����ж��������ߣ�
     *          ��ҪΪʹ�ò�ͬ�ײ㴫��Э������ⴴ����ͬ��������ߣ���ͨ��SRIO��UDP��TCP��������߸�һ����
     *
     * @param   domainId    ָ����ţ���ŷ�Χ0-232.
     * @param   qos_name    ָ��QoS�����ļ����������QoS�������ƣ�����ΪNULL������ʹ�������ļ�������Ϊdefault�����á�
     *
     * @return  NULL��ʾʧ�ܣ����򷵻�������ߵ�ָ�룬��ָ�����ں��������������Լ������ߡ�
     */

    static DomainParticipant* CreateDP(
        const DomainId_t domainId,
        const Char* qos_name);

    /**
     * @fn  static DataWriter* DDSIF_SUSTAIN::PubTopic( DomainParticipant* self, const Char* topicName, TypeSupport* typeSupport, const Char* qos_name, DataWriterListener* dwListener);
     *
     * @brief   �������⣬ָ��������ߡ�����������������QoS���������Լ���������
     *
     * @param [in,out]  self        ָ��������ߡ�
     * @param   topicName           �������ơ�
     * @param [in,out]  typeSupport ����֧�ֶ���ָ���������������ͣ�����Ϊ�� &amp;��������+TypeSupport::get_instance,
     *                              ���Ϊ�㿽�������������� &amp;ZeroCopyBytesTypeSupport::get_instance�� ���÷��㿽������
     *                              &amp;BytesTypeSupport::get_instance��IDL�ļ��Զ����ɵĴ��� &amp;
     *                              ��������TypeSupport::get_instance����
     * @param   qos_name            ָ��QoS�����ļ�������д��QoS�������ƣ�����ΪNULL������ʹ�������ļ�������Ϊdefault�����á�
     * @param [in,out]  dwListener  �����ߵļ�������������չ����NULL���ɡ�
     *
     * @return  NULL��ʾʧ�ܣ����򷵻�����д��ָ�루����Ψһ��ʶ�����õķ����ߣ���
     */

    static DataWriter* PubTopic(
        DomainParticipant* self,
        const Char* topicName,
        TypeSupport* typeSupport,
        const Char* qos_name,
        DataWriterListener* dwListener);

    /**
     * @fn  static ReturnCode_t DDSIF_SUSTAIN::UnPubTopic(DataWriter* writer);
     *
     * @brief   ָ������д��ָ��ȡ��������
     *
     * @param [in,out]  writer  ָ������д��ָ�롣
     *
     * @return  #RETCODE_OK ��ʾȡ���ɹ���������ʾʧ�ܣ�
     */

    static ReturnCode_t UnPubTopic(DataWriter* writer);

    /**
     * @fn  static ReturnCode_t DDSIF_SUSTAIN::UnPubTopicWTopicName(DomainId_t domainId, const Char* topicName);
     *
     * @brief   ͨ�����Լ���������ȡ��������������ڴ��ڶ����������ͬ�ķ����߽�ɾ������ͬ�����ⷢ���� 
     *          �ýӿڽ���ָ���������ҽ���һ���������������ʹ�ã�
     *
     * @param   domainId    ָ����š�
     * @param   topicName   ָ���������ơ�
     *
     * @return  #RETCODE_OK ��ʾȡ���ɹ���������ʾʧ�ܣ�
     */

    static ReturnCode_t UnPubTopicWTopicName(DomainId_t domainId, const Char* topicName);

    /**
     * @fn  static DataReader* DDSIF_SUSTAIN::SubTopic( DomainParticipant* self, const Char* topicName, TypeSupport* typeSupport, const Char* qos_name, DataReaderListener* drListener);
     *
     * @brief   �������⣬ָ��������ߡ����������������Լ�QoS�������ơ�
     *
     * @param [in,out]  self        ָ��������ߡ�
     * @param   topicName           �������ơ�
     * @param [in,out]  typeSupport ����֧�ֶ���ָ���������������ͣ�����Ϊ�� &amp;��������+TypeSupport::get_instance,
     *                              ���Ϊ�㿽�������������� &amp;ZeroCopyBytesTypeSupport::get_instance�� ���÷��㿽������
     *                              &amp;BytesTypeSupport::get_instance��IDL�ļ��Զ����ɵĴ��� &amp;
     *                              ��������TypeSupport::get_instance����
     * @param   qos_name            ָ��QoS�����ļ�������д��QoS�������ƣ�����ΪNULL������ʹ�������ļ�������Ϊdefault�����á�
     * @param [in,out]  drListener  �����ߵļ�������������չ����NULL���ɡ�
     *
     * @return  NULL��ʾʧ�ܣ����򷵻����ݶ���ָ�루����Ψһ��ʶ�����õĶ����ߣ���
     */

    static DataReader* SubTopic(
        DomainParticipant* self,
        const Char* topicName,
        TypeSupport* typeSupport,
        const Char* qos_name,
        DataReaderListener* drListener);

    /**
     * @fn  static ReturnCode_t DDSIF_SUSTAIN::UnSubTopic(DataReader* reader);
     *
     * @brief   ָ�����ݶ���ָ��ȡ�����ġ�
     *
     * @param [in,out]  reader  ָ�����ݶ���ָ�롣
     *
     * @return  #RETCODE_OK ��ʾȡ���ɹ���������ʾʧ�ܣ�
     */

    static ReturnCode_t UnSubTopic(DataReader* reader);

    /**
     * @fn  static ReturnCode_t DDSIF_SUSTAIN::UnSubTopicWTopicName(DomainId_t domainId, const Char* topicName);
     *
     * @brief   ͨ�����Լ���������ȡ�����ģ�������ڴ��ڶ����������ͬ�Ķ����߽�ɾ������ͬ�����ⶩ�ġ� 
     *          �ýӿڽ���ָ���������ҽ���һ���������������ʹ�ã�
     *
     * @param   domainId    ָ����š�
     * @param   topicName   ָ���������ơ�
     *
     * @return  #RETCODE_OK ��ʾȡ���ɹ���������ʾʧ�ܣ�
     */

    static ReturnCode_t UnSubTopicWTopicName(DomainId_t domainId, const Char* topicName);

    /**
     * @fn  static ReturnCode_t DDSIF_SUSTAIN::Finalize();
     *
     * @brief   ������Դ��
     *
     * @return  RETCODE_OK��ʾ�ɹ��������ʾ������Դ����ʧ�ܡ�
     */

    static ReturnCode_t Finalize();

    /**
     * @fn  static ZeroCopyBytes* DDSIF_SUSTAIN::ZeroCopyBytesCreate(ULong maximum);
     *
     * @brief   �����㿽�����󣬲�����󳤶ȷ���ռ䡣
     *
     * @param   maximum �㿽�������ܷ��͵ĳ��ȡ�
     *
     * @return  NULL��ʾʧ�ܣ����ܵ�ԭ��Ϊ�����ڴ�ʧ�ܣ����򷵻��㿽������
     */

    static ZeroCopyBytes* ZeroCopyBytesCreate(ULong maximum);

    /**
     * @fn  static void DDSIF_SUSTAIN::ZeroCopyBytesDestroy(ZeroCopyBytes* sample);
     *
     * @brief   �� ZeroCopyBytesCreate ������Ӧ�Ļ����㿽������ռ䡣
     *
     * @param [in,out]  sample  ָ���㿽������
     */

    static void ZeroCopyBytesDestroy(ZeroCopyBytes* sample);

    /**
     * @fn  static ReturnCode_t DDSIF_SUSTAIN::ZeroCopyBytesWrite( DomainId_t domainId, Char* topicName, ZeroCopyBytes* sample);
     *
     * @brief   ��ָ��������ָ��������㿽�����ݡ�ʹ�øýӿڵ�ǰ�᣺
     *          - ָ�����������ҽ���һ��������ߣ�
     *          - ָ�����������ҽ���һ����ָ����������ķ����ߣ�
     *          - ָ���������������������Ϊ�㿽���������ͣ�
     *          ���������������������ʹ�� ZeroCopyBytesDataWriter::write �ӿ�ָ�������߷������ݡ�.
     *
     * @param   domainId            ָ����š�
     * @param [in,out]  topicName   ָ���������ơ�
     * @param [in,out]  sample      ָ�����͵����ݡ�
     *
     * @return  #RETCODE_OK ��ʾ���ͳɹ��� ������ʾʧ�ܡ�
     */

    static ReturnCode_t ZeroCopyBytesWrite(
        DomainId_t domainId,
        Char* topicName,
        ZeroCopyBytes* sample);

    /**
     * @fn  static Long DDSIF_SUSTAIN::BytesWrapper(Bytes& self, const Char* buffer, const Long length);
     *
     * @brief   �û���������װ��DDS_Bytes���ͣ����㿽���������������ͣ����ýӿڲ�����ռ䣬�����Ӧ�Ļ��պ�����.
     *
     * @param [in,out]  self    ָ����װ��Ŀ�ꡣ
     * @param   buffer          �û��ṩ�ռ䡣
     * @param   length          �ռ䳤�ȡ�
     *
     * @return  0��ʾ�ɹ��������ʾʧ�ܡ�
     */

    static Long BytesWrapper(Bytes& self, const Char* buffer, const Long length);

    /**
     * @fn  static ReturnCode_t DDSIF_SUSTAIN::BytesWrite( DomainId_t domainId, Char* topicName, const Char* content, const Long length);
     *
     * @brief   ��ָ��������ָ������ķ��㿽��Bytes���ݡ�ʹ�øýӿڵ�ǰ�᣺
     *          - ָ�����������ҽ���һ��������ߣ�
     *          - ָ�����������ҽ���һ����ָ����������ķ����ߣ�
     *          - ָ���������������������ΪBytes�������ͣ�
     *          ���������������������ʹ�� BytesDataWriter::write �ӿ�ָ�������߷������ݡ�
     *
     * @param   domainId            ָ����š�
     * @param [in,out]  topicName   ָ���������ơ�
     * @param   content             �������ݻ�������
     * @param   length              ���������ȡ�
     *
     * @return  #RETCODE_OK ��ʾ���ͳɹ��� ������ʾʧ�ܡ�
     */

    static ReturnCode_t BytesWrite(
        DomainId_t domainId,
        Char* topicName,
        const Char* content,
        const Long length);
};
class DCPSDLL DDSIF
{
public:

    /**
     * @fn  static DomainParticipantFactory* DDSIF::Init( const Char* qosFilePath, const Char* qosName);
     *
     * @brief   ��ָ�����ó�ʼ��DDS�м����ֻ�����������ʼ��ʱ����һ�μ��ɡ�
     *
     * @param   qosFilePath QoS�����ļ���·���������Ǿ���·����Ҳ�����ǳ�������Ŀ¼�����·����
     *                      ΪNULLʱ��Ĭ��ʹ������Ŀ¼�� ZRDDS_QOS_PROFILES.xml �����ļ���
     * @param   qosName     QoS�����ļ��й���QoS�������ƣ�DDS���� default_lib::default_profile::qosName �����QoS��ʼ��DDS�򳧣�
     *                      ����ΪNULL������ʹ�������ļ�������Ϊdefault�����á�
     *
     * @return  NULL��ʾʧ�ܣ����򷵻�DDS�򹤳�������
     */

    static DomainParticipantFactory* Init(
        const Char* qosFilePath,
        const Char* qosName);

    /**
     * @fn  static DomainParticipant* DDSIF::CreateDP( const DomainId_t domainId, const Char* qos_name);
     *
     * @brief   DDS����������ߣ���ָ�������QoS�������ƣ�ͬһ����ſ����ж��������ߣ�
     *          ��ҪΪʹ�ò�ͬ�ײ㴫��Э������ⴴ����ͬ��������ߣ���ͨ��SRIO��UDP��TCP��������߸�һ����
     *
     * @param   domainId    ָ����ţ���ŷ�Χ0-232.
     * @param   qos_name    ָ��QoS�����ļ����������QoS�������ƣ�����ΪNULL������ʹ�������ļ�������Ϊdefault�����á�
     *
     * @return  NULL��ʾʧ�ܣ����򷵻�������ߵ�ָ�룬��ָ�����ں��������������Լ������ߡ�
     */

    static DomainParticipant* CreateDP(
        const DomainId_t domainId,
        const Char* qos_name);

    /**
     * @fn  static DataWriter* DDSIF::PubTopic( DomainParticipant* self, const Char* topicName, TypeSupport* typeSupport, const Char* qos_name, DataWriterListener* dwListener);
     *
     * @brief   �������⣬ָ��������ߡ�����������������QoS���������Լ���������
     *
     * @param [in,out]  self        ָ��������ߡ�
     * @param   topicName           �������ơ�
     * @param [in,out]  typeSupport ����֧�ֶ���ָ���������������ͣ�����Ϊ�� &amp;��������+TypeSupport::get_instance,
     *                              ���Ϊ�㿽�������������� &amp;ZeroCopyBytesTypeSupport::get_instance�� ���÷��㿽������
     *                              &amp;BytesTypeSupport::get_instance��IDL�ļ��Զ����ɵĴ��� &amp;
     *                              ��������TypeSupport::get_instance����
     * @param   qos_name            ָ��QoS�����ļ�������д��QoS�������ƣ�����ΪNULL������ʹ�������ļ�������Ϊdefault�����á�
     * @param [in,out]  dwListener  �����ߵļ�������������չ����NULL���ɡ�
     *
     * @return  NULL��ʾʧ�ܣ����򷵻�����д��ָ�루����Ψһ��ʶ�����õķ����ߣ���
     */

    static DataWriter* PubTopic(
        DomainParticipant* self,
        const Char* topicName,
        TypeSupport* typeSupport,
        const Char* qos_name,
        DataWriterListener* dwListener);

    /**
     * @fn  static ReturnCode_t DDSIF::UnPubTopic(DataWriter* writer);
     *
     * @brief   ָ������д��ָ��ȡ��������
     *
     * @param [in,out]  writer  ָ������д��ָ�롣
     *
     * @return  #RETCODE_OK ��ʾȡ���ɹ���������ʾʧ�ܣ�
     */

    static ReturnCode_t UnPubTopic(DataWriter* writer);

    /**
     * @fn  static ReturnCode_t DDSIF::UnPubTopicWTopicName(DomainId_t domainId, const Char* topicName);
     *
     * @brief   ͨ�����Լ���������ȡ��������������ڴ��ڶ����������ͬ�ķ����߽�ɾ������ͬ�����ⷢ���� 
     *          �ýӿڽ���ָ���������ҽ���һ���������������ʹ�ã�
     *
     * @param   domainId    ָ����š�
     * @param   topicName   ָ���������ơ�
     *
     * @return  #RETCODE_OK ��ʾȡ���ɹ���������ʾʧ�ܣ�
     */

    static ReturnCode_t UnPubTopicWTopicName(DomainId_t domainId, const Char* topicName);

    /**
     * @fn  static DataReader* DDSIF::SubTopic( DomainParticipant* self, const Char* topicName, TypeSupport* typeSupport, const Char* qos_name, DataReaderListener* drListener);
     *
     * @brief   �������⣬ָ��������ߡ����������������Լ�QoS�������ơ�
     *
     * @param [in,out]  self        ָ��������ߡ�
     * @param   topicName           �������ơ�
     * @param [in,out]  typeSupport ����֧�ֶ���ָ���������������ͣ�����Ϊ�� &amp;��������+TypeSupport::get_instance,
     *                              ���Ϊ�㿽�������������� &amp;ZeroCopyBytesTypeSupport::get_instance�� ���÷��㿽������
     *                              &amp;BytesTypeSupport::get_instance��IDL�ļ��Զ����ɵĴ��� &amp;
     *                              ��������TypeSupport::get_instance����
     * @param   qos_name            ָ��QoS�����ļ�������д��QoS�������ƣ�����ΪNULL������ʹ�������ļ�������Ϊdefault�����á�
     * @param [in,out]  drListener  �����ߵļ�������������չ����NULL���ɡ�
     *
     * @return  NULL��ʾʧ�ܣ����򷵻����ݶ���ָ�루����Ψһ��ʶ�����õĶ����ߣ���
     */

    static DataReader* SubTopic(
        DomainParticipant* self,
        const Char* topicName,
        TypeSupport* typeSupport,
        const Char* qos_name,
        DataReaderListener* drListener);

    /**
     * @fn  static ReturnCode_t DDSIF::UnSubTopic(DataReader* reader);
     *
     * @brief   ָ�����ݶ���ָ��ȡ�����ġ�
     *
     * @param [in,out]  reader  ָ�����ݶ���ָ�롣
     *
     * @return  #RETCODE_OK ��ʾȡ���ɹ���������ʾʧ�ܣ�
     */

    static ReturnCode_t UnSubTopic(DataReader* reader);

    /**
     * @fn  static ReturnCode_t DDSIF::UnSubTopicWTopicName(DomainId_t domainId, const Char* topicName);
     *
     * @brief   ͨ�����Լ���������ȡ�����ģ�������ڴ��ڶ����������ͬ�Ķ����߽�ɾ������ͬ�����ⶩ�ġ� 
     *          �ýӿڽ���ָ���������ҽ���һ���������������ʹ�ã�
     *
     * @param   domainId    ָ����š�
     * @param   topicName   ָ���������ơ�
     *
     * @return  #RETCODE_OK ��ʾȡ���ɹ���������ʾʧ�ܣ�
     */

    static ReturnCode_t UnSubTopicWTopicName(DomainId_t domainId, const Char* topicName);

    /**
     * @fn  static ReturnCode_t DDSIF::Finalize();
     *
     * @brief   ������Դ��
     *
     * @return  RETCODE_OK��ʾ�ɹ��������ʾ������Դ����ʧ�ܡ�
     */

    static ReturnCode_t Finalize();

    /**
     * @fn  static ZeroCopyBytes* DDSIF::ZeroCopyBytesCreate(ULong maximum);
     *
     * @brief   �����㿽�����󣬲�����󳤶ȷ���ռ䡣
     *
     * @param   maximum �㿽�������ܷ��͵ĳ��ȡ�
     *
     * @return  NULL��ʾʧ�ܣ����ܵ�ԭ��Ϊ�����ڴ�ʧ�ܣ����򷵻��㿽������
     */

    static ZeroCopyBytes* ZeroCopyBytesCreate(ULong maximum);

    /**
     * @fn  static void DDSIF::ZeroCopyBytesDestroy(ZeroCopyBytes* sample);
     *
     * @brief   �� ZeroCopyBytesCreate ������Ӧ�Ļ����㿽������ռ䡣
     *
     * @param [in,out]  sample  ָ���㿽������
     */

    static void ZeroCopyBytesDestroy(ZeroCopyBytes* sample);

    /**
     * @fn  static ReturnCode_t DDSIF::ZeroCopyBytesWrite( DomainId_t domainId, Char* topicName, ZeroCopyBytes* sample);
     *
     * @brief   ��ָ��������ָ��������㿽�����ݡ�ʹ�øýӿڵ�ǰ�᣺
     *          - ָ�����������ҽ���һ��������ߣ�
     *          - ָ�����������ҽ���һ����ָ����������ķ����ߣ�
     *          - ָ���������������������Ϊ�㿽���������ͣ�
     *          ���������������������ʹ�� ZeroCopyBytesDataWriter::write �ӿ�ָ�������߷������ݡ�.
     *
     * @param   domainId            ָ����š�
     * @param [in,out]  topicName   ָ���������ơ�
     * @param [in,out]  sample      ָ�����͵����ݡ�
     *
     * @return  #RETCODE_OK ��ʾ���ͳɹ��� ������ʾʧ�ܡ�
     */

    static ReturnCode_t ZeroCopyBytesWrite(
        DomainId_t domainId,
        Char* topicName,
        ZeroCopyBytes* sample);

    /**
     * @fn  static Long DDSIF::BytesWrapper(Bytes& self, const Char* buffer, const Long length);
     *
     * @brief   �û���������װ��DDS_Bytes���ͣ����㿽���������������ͣ����ýӿڲ�����ռ䣬�����Ӧ�Ļ��պ�����.
     *
     * @param [in,out]  self    ָ����װ��Ŀ�ꡣ
     * @param   buffer          �û��ṩ�ռ䡣
     * @param   length          �ռ䳤�ȡ�
     *
     * @return  0��ʾ�ɹ��������ʾʧ�ܡ�
     */

    static Long BytesWrapper(Bytes& self, const Char* buffer, const Long length);

    /**
     * @fn  static ReturnCode_t DDSIF::BytesWrite( DomainId_t domainId, Char* topicName, const Char* content, const Long length);
     *
     * @brief   ��ָ��������ָ������ķ��㿽��Bytes���ݡ�ʹ�øýӿڵ�ǰ�᣺
     *          - ָ�����������ҽ���һ��������ߣ�
     *          - ָ�����������ҽ���һ����ָ����������ķ����ߣ�
     *          - ָ���������������������ΪBytes�������ͣ�
     *          ���������������������ʹ�� BytesDataWriter::write �ӿ�ָ�������߷������ݡ�
     *
     * @param   domainId            ָ����š�
     * @param [in,out]  topicName   ָ���������ơ�
     * @param   content             �������ݻ�������
     * @param   length              ���������ȡ�
     *
     * @return  #RETCODE_OK ��ʾ���ͳɹ��� ������ʾʧ�ܡ�
     */

    static ReturnCode_t BytesWrite(
        DomainId_t domainId,
        Char* topicName,
        const Char* content,
        const Long length);
};
} // namespace DDS

#endif //_ZRDDS_INCLUDE_SIMPLE_INTERFACE

#endif // ZRDDSCppSimpleInterface_h__
