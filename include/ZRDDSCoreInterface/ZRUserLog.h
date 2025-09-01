#ifndef ZRUserLog_h__
#define ZRUserLog_h__

#include "InstanceHandle_t.h"

#if defined(_WIN32) && defined(_ZRDDS_GENERATOR_DEBUG_INFO)
#define ZRLOG_DO_STRINGIZE(x) #x
#define ZRLOG_STRINGIZE(x) ZRLOG_DO_STRINGIZE(x)
template<const int line, const int number> 
void ZRLogWarningPrint() 
{ 
#pragma message(__FUNCSIG__) 
}
#define ZRLOG_MESSAGE_STRING(msg) "ZRLOG_INFO: " __FILE__ ": " __FUNCTION__ ": " ZRLOG_STRINGIZE(__LINE__) ": " msg
#define ZRLOG_PRINT_MESSAGE(msg, debugNo) __pragma(message(ZRLOG_MESSAGE_STRING(msg))); ZRLogWarningPrint<__LINE__, debugNo>();
#else
#define ZRLOG_PRINT_MESSAGE(msg, debugNo) 
#endif

#ifdef __cplusplus
extern "C"
{
#endif

#define ZRDDS_NETWORK_TOPIC "ZRDDS_NETWORK_TOPIC"

#define ZRDDS_DOMAINPARTICIPANT_TOPIC "ZRDDS_DOMAINPARTICIPANT_TOPIC"

#define ZRDDS_PUBLISHER_TOPIC "ZRDDS_PUBLISHER_TOPIC"

#define ZRDDS_DOMAINPARTICIPANTFACTORY_TOPIC "ZRDDS_DOMAINPARTICIPANTFACTORY_TOPIC"

#define ZRDDS_MPORT_TOPIC "ZRDDS_MPORT_TOPIC"

#define ZRDDS_SHMEM_TOPIC "ZRDDS_SHMEM_TOPIC"

#define ZRDDS_VALIDATOR_TOPIC "ZRDDS_VALIDATOR_TOPIC"

#define ZRDDS_INTERACTIVECMD_TOPIC "ZRDDS_INTERACTIVECMD_TOPIC"

#define ZRDDS_ANY_TOPICNAME "ZRDDS_ANY_LOG_TOPIC_NAME___"

#define ZRDDS_LOG_ENABLE_BEGIN_NUM 7000

#define ZRDDS_LOG_ENABLE_END_NUM 7000

/**
 * @enum    ZRLogDisplayStyle
 *
 * @brief    ��־�����ʽ���
 */

typedef enum ZRLogDisplayStyle
{
    /** @brief Ĭ��ģʽ. */
    GRACEFUL_STYLE = 0,
    /** @brief ����ģʽ. */
    PRACTICAL_STYLE = 2,
    /** @brief Ԫ��Ϣģʽ. */
    META_STYLE = 4,
    /** @brief ����ģʽ������ǵ�����־����ֻ��ʾ��־�ţ�������־������ʾ. */
    DEBUG_STYLE = 6,
    /** @brief δ֪��������Ĭ��ģʽ. */
    UNKNOWN_STYLE
}ZRLogDisplayStyle;

/**
 * @typedef enum ZRLogBackupMode
 *
 * @brief   ��־����ģʽ.
 */
typedef enum ZRLogBackupMode
{
    /** @brief  Ĭ��ģʽ����ʹ����־���ݹ��ܡ�ÿ������Ӧ�ã���������ԭ����־�� */
    ZRLOG_BACKUP_NOTUSED,
    /** @brief  ͬ������ģʽ������ͬ����־ʱ����ԭ�е���־���ݵ���־���Ŀ¼/��־�ļ���-ʱ����� */
    ZRLOG_BACKUP_EXIST_FILE,
    /**   
     * @brief   ��ǰ��־�ļ��ﵽһ����С�󽫽��б��ݣ������´�����־�ļ���  
     *          ѡ�ø�ģʽ����־�ļ������ƽ�Ϊ����־�ļ�����_����ʱ��.ddslog�� 
     */
    ZRLOG_BACKUP_FILE_SIZE,
    /**
     * @brief   ÿ��һ��ʱ��󽫽��б��ݣ������´�����־�ļ���
     *          ѡ�ø�ģʽ����־�ļ������ƽ�Ϊ����־�ļ�����_����ʱ��.ddslog��
     */
    ZRLOG_BACKUP_TIME_INTERVAL,
} ZRLogBackupMode;

/**
 * @typedef struct ZRLogBackupParam
 *
 * @brief   Defines an alias representing the zr log parameter.
 */

typedef struct ZRLogBackupParam
{
    /** @brief   ��־����ģʽ. */
    ZRLogBackupMode mode;
    /**   
     * @brief   ��mode������ΪZRLOG_BACKUP_NOTUSEDʱ���ò�����Ч�� 
     *          ��mode������ΪZRLOG_BACKUP_FILE_SIZEʱ���ò���Ϊ��־�ļ���С���ޣ�KB����
     *          ��mode������ΪZRLOG_BACKUP_TIME_INTERVALʱ���ò���Ϊʱ������s����
     */
    ZR_INT32 param;
}ZRLogBackupParam;

/**
 * @typedef struct ZRLogParam
 *
 * @brief   Defines an alias representing the zr log parameter.
 */

typedef struct ZRLogParam
{
    /** @brief   ���������̨����־�ȼ��� */
    ZR_UINT32 consoleMask;
    /** @brief   ������ļ��е���־�ȼ��� */
    ZR_UINT32 fileMask;
    /** @brief   ������ֲ�ʽ��־����־�ȼ��� */
    ZR_UINT32 distMask;
    /** @brief   ��־չʾ��� */
    ZRLogDisplayStyle style;
    /** @brief   ָ����־������ļ�·�����������ΪNULL����ʹ��Ĭ��·������ǰ����Ŀ¼������ʼ����ò������ɱ䡣 */
    ZR_INT8* logFileDir;
    /** @brief   ָ����־������ļ������������ΪNULL����ʹ��Ĭ�����ƣ�Ӧ����.ddslog������ʼ����ò������ɱ䡣 */
    ZR_INT8* logFileName;
    /** @brief   Ӧ�ñ��ݲ��ԡ���ʼ����ò��Բ��ɱ䡣 */
    ZRLogBackupParam backupParam;
} ZRLogParam;

DCPSDLL extern void ZRLogParamInitial(ZRLogParam* param);

/**
 * @enum DDS_LogType
 *
 * @ingroup CoreQosStruct
 *
 * @brief   ���ڱ�ʾĳһ����־������ȼ������ڲ�ͬ�ĵȼ����û����Կ�����ͬ����־�ļ���
 *
 */

typedef enum DDS_LogType
{
    /** @brief  ������ֲ��ɺ��ԵĴ��� @ingroup CoreQosStruct */
    ZRLOG_ERROR = 0x0001 << 1,
    /** @brief  ϵͳ����Ա�ӽǵ���Ϣ,����һЩ������Ϣ�� @ingroup CoreQosStruct */
    ZRLOG_ADMIN_INFO = 0x0001 << 2,
    /** @brief  ֪ͨ�û��ӽ���Ϣ����ֻ�ܿ����Զ���Endpoint֮������ݽ����� @ingroup CoreQosStruct */
    ZRLOG_USER_INFO = 0x0001 << 3,
    /** @brief  ������Ϣ�����ܹ��������С� @ingroup CoreQosStruct */
    ZRLOG_WARNING = 0x0001 << 4,
    /** @brief  ��Ч��ѡ�  @ingroup CoreQosStruct */
    LOGTYPE_UNKNOWN = 0x0001 << 9
} DDS_LogType;

/**
 * @typedef ZR_INT32(*ZRLogCallbackInitialize)(void* logCallbackParam)
 *
 * @brief   ��������־�ӿ������ڳ�ʼ���Ļص�������
 *          �����Ҫ���õ�������־�ӿڣ�����ҪԤ�Ƚ��г�ʼ���Ĳ����������ռ�ȣ������û���Ҫʵ�ָ����͵ĺ�����
 *          ���ں���ʵ���б�д��ʼ���������߼���
 *          ����Ӧ������ָ������ZRLogCallbackParam�У�������ZRLogSetListener��
 *          ������ط�0ֵ�����ʾ��ʼ������ʧ�ܣ��õ�������־�ӿڽ��������á�
 */
typedef ZR_INT32(*ZRLogCallbackInitialize)(void* logCallbackParam);

/**
 * @typedef ZR_INT32(*ZRLogCallback)(DDS_LogType type, const ZR_INT8* topicName, 
 *          unsigned int debugNo, const ZR_INT8* time, const ZR_INT8* file, 
 *          const ZR_INT8* func, ZR_UINT32 line, const ZR_INT8* content, void* logCallbackParam)
 *
 * @brief   ��������־�ӿ���������־����Ļص�������
 *          �����Ҫ���õ�������־�ӿڣ����û���Ҫʵ�ָ����͵ĺ��������ں���ʵ���б�д�Զ������־������߼���
 *          ����Ӧ������ָ������ZRLogCallbackParam�У�������ZRLogSetListener��
 *          �ص��ӿڽ������ȵ��á�
 *          �������0�����ʾ��Ҫ��������ZRDDSԭʼ����־����������������-1�����ʾ����ZRDDSԭʼ����־���������
 */

typedef ZR_INT32(*ZRLogCallbackOutput)(DDS_LogType type, const ZR_INT8* topicName, 
    unsigned int debugNo, const ZR_INT8* time, const ZR_INT8* file, 
    const ZR_INT8* func, ZR_UINT32 line, const ZR_INT8* content, void* logCallbackParam);

/**
 * @typedef ZR_INT32(*ZRLogCallbackFinalize)(void* logCallbackParam)
 *
 * @brief   ��������־�ӿ������ڽ�������Ļص�������
 *          ����û������õ�������־�ӿ�ʱ�������ʼ���ص��������˳�ʼ���Ĳ����������ռ�ȣ�������ʵ�ָ����͵ĺ�����
 *          ���ں���ʵ���б�д��Ӧ�����������������߼���
 *          ����Ӧ������ָ������ZRLogCallbackParam�У�������ZRLogSetListener��
 *          ������ط�0ֵ�����ʾ����������ڴ��󡣣����ܴ��󣬸õ�������־�ӿ�Ҳ�ᱻ�Ƴ������������ã�
 */

typedef ZR_INT32(*ZRLogCallbackFinalize)(void* logCallbackParam);

/**
 * @struct  ZRLogCallbackParam
 *
 * @brief   ���ڴ���û��ص�����ָ�롢���εĽṹ��.
 */

typedef struct ZRLogCallback
{
    /** @brief   ��������־�ӿ������ڳ�ʼ���Ļص�����������ΪNULL. */
    ZRLogCallbackInitialize initialize_callback;
    /** @brief   ��������־�ӿ���������־����Ļص�������������ΪNULL������ZRLogSetListener��ʧ��*/
    ZRLogCallbackOutput log_output_callback;
    /** @brief   ��������־�ӿ������ڽ�������Ļص�����������ΪNULL. */
    ZRLogCallbackFinalize finalize_callback;
    /** @brief   ��������־�ӿ��е��û�����. */
    void* log_callback_param;
}ZRLogCallback;

/**
 * @fn    extern ZR_INT32 ZRLogInitial(ZR_UINT32 consoleMask, ZR_UINT32 fileMask, ZRLogDisplayStyle style);
 *
 * @brief    ��ʼ���û���־�ӿ�.
 *
 * @param    consoleMask    ���������̨����־�ȼ�����.
 * @param    fileMask       �������־�ļ�����־�ȼ�����.
 * @param    style           ��־���Ĭ��ΪGRACEFUL_STYLE.
 *
 * @return    A ZR_INT32.
 */

DCPSDLL extern ZR_INT32 ZRLogInitial(const ZRLogParam* param);

/**
 * @fn  ZR_INT32 ZRLogInitial();
 *
 * @brief   ����Ϊ��־ϵͳ�ṩ��Դ�ȡ�
 *
 * @author  Hzy
 * @date    2015/9/24
 */

DCPSDLL extern ZR_INT32 ZRLogDestroy();

/**
 * @fn    void ZRLogSetDisplayStyle(ZRLogDisplayStyle style);
 *
 * @brief    ���÷����ʽ.
 *
 * @param    style    The style.
 */

DCPSDLL extern void ZRLogSetDisplayStyle(ZRLogDisplayStyle style);

/**
 * @fn  ZR_INT32 ZRLogSetListener(ZRLogCallback listener);
 *
 * @brief   ���õ�������־�ص��ӿڡ�
 *          ��Ҫ���û����й���ZRLogCallbackָ�롣
 *          �����δ����ZRLogRemoveListener������£��ͷ��˸�ָ��Ŀռ䣬���ܻᵼ�³��������
 *          �������־ʱ���������ȵ��õ������ӿڡ�
 *
 * @param   listener    �ص��ӿڵ�ָ��.
 *
 * @return  �����óɹ����򷵻�0�����򷵻ط�0ֵ.
 */

DCPSDLL extern ZR_INT32 ZRLogSetListener(ZRLogCallback* listener);

/**
 * @fn  ZR_INT32 ZRLogRemoveListener(ZRLogCallback listener);
 *
 * @brief   �Ƴ���������־�ص��ӿڡ�
 *          �Ƴ���ZRLogCallbackָ�벢δ���ͷţ���Ҫ���û��ֶ��ͷš�
 *
 * @param   listener    �ص��ӿڵĺ���ָ��.
 *
 * @return  ���Ƴ��ɹ����򷵻�0�����򷵻ط�0ֵ.
 */

DCPSDLL extern ZR_INT32 ZRLogRemoveListener(ZRLogCallback* listener);

/**
 * @fn  ZR_BOOLEAN ZRLogDebugMask(ZR_UINT32 debugNum);
 *
 * @ingroup ZRDDSLog
 *
 * @brief   ָ���ĵ�����Ϣ����Ƿ����á�
 *
 * @param   debugNum    ָ��������Ϣ��š�
 *
 * @return  true��ʾ�����ã�false��ʾδ���á�
 */

DCPSDLL ZR_BOOLEAN ZRLogDebugMask(ZR_UINT32 debugNum);

/**
 * @fn  ZR_INT32 ZRLogDebugMaskEnableRange(ZR_UINT32 beginNum, ZR_UINT32 endNum);
 *
 * @ingroup ZRDDSLog
 *
 * @brief   ʹ�ܵ�����Ϣ��Χ��
 *
 * @param   beginNum    ��ʼ���(����)��
 * @param   endNum      �������(����)��
 *
 * @return  0��ʾ�ɹ���С��0��ʾʧ�ܡ�
 */

DCPSDLL ZR_INT32 ZRLogDebugMaskEnableRange(ZR_UINT32 beginNum, ZR_UINT32 endNum);

/**
 * @fn  void ZRLogDebugMaskDisableRange(ZR_UINT32 beginNum, ZR_UINT32 endNum);
 *
 * @ingroup ZRDDSLog
 *
 * @brief   ȡ��������Ϣ��Χ��
 *
 * @param   beginNum    ��ʼ���(����)��
 * @param   endNum      �������(����)��
 *
 * @return  0��ʾ�ɹ���С��0��ʾʧ�ܡ�
 */

DCPSDLL ZR_INT32 ZRLogDebugMaskDisableRange(ZR_UINT32 beginNum, ZR_UINT32 endNum);

/**
 * @fn  ZR_INT32 ZRLogDebugMaskEnableTopicName(const ZR_INT8* topicName);
 *
 * @ingroup ZRDDSLog
 *
 * @brief   ʹ��ָ���������ݵ���־��
 *
 * @param   topicName   ָ���������ƣ����û���֤�������Ƶ���Ч�ԡ�
 *
 * @return  0��ʾ�ɹ���С��0��ʾʧ�ܡ�
 */

DCPSDLL ZR_INT32 ZRLogDebugMaskEnableTopicName(const ZR_INT8* topicName);

/**
 * @fn  ZR_INT8 ZRLogDebugMaskDisableTopicName(const ZR_INT8* topicName);
 *
 * @ingroup ZRDDSLog
 *
 * @brief   ȡ��ʹ��ָ���������ݵ���־��
 *
 * @param   topicName   ָ���������ƣ����û���֤�������Ƶ���Ч�ԡ�
 *
 * @return  0��ʾ�ɹ���С��0��ʾʧ�ܡ�
 */

DCPSDLL ZR_INT8 ZRLogDebugMaskDisableTopicName(const ZR_INT8* topicName);

/**
 * @fn  ZR_INT32 ZRLogDebugMaskEnableEntityId(const DDS_InstanceHandle_t* handle);
 *
 * @ingroup ZRDDSLog
 *
 * @brief   ʹ��ָ��ʵ�����־��
 *
 * @param   handle  ʵ��Ψһ��ʶ��( Entity::get_instance_handle ), ���û���֤InstanceHandle����Ч�ԡ�.
 *
 * @return  0��ʾ�ɹ���С��0��ʾʧ�ܡ�
 */

DCPSDLL ZR_INT32 ZRLogDebugMaskEnableEntityId(const DDS_InstanceHandle_t* handle);

/**
 * @fn  ZR_INT32 ZRLogDebugMaskDisableEntityId(const DDS_InstanceHandle_t* handle);
 *
 * @ingroup ZRDDSLog
 *
 * @brief   ʹ��ָ��ʵ�����־��
 *
 * @param   handle  ʵ��Ψһ��ʶ��( Entity::get_instance_handle ), ���û���֤InstanceHandle����Ч�ԡ�.
 *
 * @return  0��ʾ�ɹ���С��0��ʾʧ�ܡ�
 */

DCPSDLL ZR_INT32 ZRLogDebugMaskDisableEntityId(const DDS_InstanceHandle_t* handle);

/**
 * @fn  void ZRLogBeginLog(DDS_LogType type, const ZR_INT8* file, const ZR_INT8* func, ZR_UINT32 line, ZR_BOOLEAN combie);
 *
 * @brief   ����Ҫ����д����־��Ϣʱ���ã� ������ZRLogEndLog���ʹ�á�
 *
 * @param   type    ���µ�����Ϣ���������͡�
 * @param   file    �����ļ�����
 * @param   func    ������������
 * @param   line    ������
 * @param   combie  �Ƿ�������־�ϲ���һ�����ڷֲ�ʽ��־ʱ�����𣬺ϲ�����һ����־�����ϲ����Ͷ�����־���ϲ�������������ĳ��������ơ�
 */

DCPSDLL extern void ZRLogBeginLog(DDS_LogType type, const ZR_INT8* file, const ZR_INT8* func, ZR_UINT32 line, ZR_BOOLEAN combie);

/**
 * @fn  DCPSDLL extern void ZRLogBeginLogWNo(DDS_LogType type, const ZR_INT8* file, const ZR_INT8* func, ZR_UINT32 line, ZR_BOOLEAN combie, const ZR_INT8* topicName, ZR_UINT32 debugNo);
 *
 * @brief   ����Ҫ����д����־��Ϣʱ���ã� ������ZRLogEndLog���ʹ�á�.
 *
 * @param   type        ���µ�����Ϣ���������͡�
 * @param   file        �����ļ�����
 * @param   func        ������������
 * @param   line        ������
 * @param   combie      �Ƿ�������־�ϲ���һ�����ڷֲ�ʽ��־ʱ�����𣬺ϲ�����һ����־�����ϲ����Ͷ�����־���ϲ�������������ĳ��������ơ�
 * @param   topicName   ��������
 * @param   debugNo     ��š�
 */

DCPSDLL extern void ZRLogBeginLogWNo(DDS_LogType type, const ZR_INT8* file, const ZR_INT8* func, ZR_UINT32 line, ZR_BOOLEAN combie, const ZR_INT8* topicName, ZR_UINT32 debugNo);

/**
 * @fn  void ZRLogEndLog();
 *
 * @brief   ������д����־��Ϣ����ʱ���ã� ��ZRLogBeginLog���ʹ�á�
 *
 */
DCPSDLL extern void ZRLogEndLog();

DCPSDLL extern void ZRLogToConsole(DDS_LogType type, const struct GUID_t* guid, const ZR_INT8* topicName, ZR_UINT32 debugNo,
    const ZR_INT8* file, const ZR_INT8* func, ZR_UINT32 line, const ZR_INT8* content, ...);

DCPSDLL extern ZR_BOOLEAN ZRLogVerifyDebugCondition(ZR_UINT32 debugNo, const ZR_INT8* topicName, const struct GUID_t* guid);

DCPSDLL extern void ZRLogAquireLock();

DCPSDLL extern void ZRLogReleaseLock();

DCPSDLL extern const ZR_INT8* InstanceHandleToString(const DDS_InstanceHandle_t* self);

DCPSDLL extern const ZR_INT8* InstanceHandleToString2(const DDS_InstanceHandle_t* self);

/**
 * @def ZRLOG(type, format, ...) ZRLogToConsole(type, __FILE__, __FUNCTION__, __LINE__, format,
 *      ##__VA_ARGS__)
 *
 * @ingroup ZRDDSLog
 *
 * @brief   �����־�ĺꡣ
 *
 * @param   type    ����־�����ļ���
 * @param   format  �ַ�����ʽ(��printf).
 * @param   ...     ��Ρ�
 */

#define ZRLOG(type, format, ...)                                                                \
        ZRLogAquireLock();                                                                      \
        ZRLogToConsole(type, NULL, NULL, 0, __FILE__, __FUNCTION__, __LINE__, format, ##__VA_ARGS__); \
        ZRLogReleaseLock();

/**
 * @def ZRLOG_W_NO(type, guid, topic, debugNo, format, ...) ZRLOG_PRINT_MESSAGE(format, debugNo);
 *
 * @brief   ����������־�ĺꡣ.
 *
 * @param   type    ����־�����ļ���.
 * @param   guid    ����־����ʵ��.
 * @param   topic   ����־��������.
 * @param   debugNo ����־�ı��.
 * @param   format  �ַ�����ʽ(��printf).
 * @param   ...     ��Ρ�.
 */
#define ZRLOG_W_NO(type, guid, topic, debugNo, format, ...)                                                                \
    ZRLOG_PRINT_MESSAGE(format, debugNo);                                                                           \
    if (ZRLogVerifyDebugCondition(debugNo, topic, guid))                                                            \
    {                                                                                                               \
        ZRLogAquireLock();                                                                                          \
        ZRLogToConsole(type, guid, topic, debugNo, __FILE__, __FUNCTION__, __LINE__, format, ##__VA_ARGS__);  \
        ZRLogReleaseLock();                                                                                         \
    }

/**
 * @def ZRLOG_DEBUG(guid, topic, debugNo, format, ...) if (ZRLogVerifyDebugCondition(debugNo,
 *      topic, guid))
 *
 * @ingroup ZRDDSLog
 *
 * @brief   ���������Ϣ�ꡣ
 *
 * @param   guid    �õ�����Ϣ����ʵ�塣
 * @param   topic   �õ�����Ϣ�������⡣
 * @param   debugNo �õ�����Ϣ�ı�š�
 * @param   format  �ַ�����ʽ(��printf).
 * @param   ...     ��Ρ�
 */

#ifndef _ZRDDS_FT_6678_MPORT_SRIO
#define ZRLOG_DEBUG(guid, topic, debugNo, format, ...)                                                              \
    ZRLOG_PRINT_MESSAGE(format, debugNo);                                                                           \
    if (ZRLogVerifyDebugCondition(debugNo, topic, guid))                                                            \
    {                                                                                                               \
        ZRLogAquireLock();                                                                                          \
        ZRLogToConsole(ZRLOG_ADMIN_INFO, guid, topic, debugNo, __FILE__, __FUNCTION__, __LINE__, format, ##__VA_ARGS__);  \
        ZRLogReleaseLock();                                                                                         \
    }

#else
#define ZRLOG_DEBUG(guid, topic, debugNo, format, ...)
#endif

/**
 * @def ZRLOG_DEBUG_W_POS(guid, topic, debugNo, file, func, line, format, ...)
 *
 * @ingroup ZRDDSLog
 *
 * @brief   ���������Ϣ�꣬��Я��λ����Ϣ��
 *
 * @param   guid    �õ�����Ϣ����ʵ�塣
 * @param   topic   �õ�����Ϣ�������⡣
 * @param   debugNo �õ�����Ϣ�ı�š�
 * @param   file    �����ļ����ַ����͡�
 * @param   func    �����������ַ����͡�
 * @param   line    �кţ����͡�
 * @param   format  �ַ�����ʽ(��printf).
 * @param   ...     ��Ρ�
 */

#define ZRLOG_DEBUG_W_POS(guid, topic, debugNo, file, func, line, format, ...)                          \
    ZRLOG_PRINT_MESSAGE(format, debugNo);                                                               \
    if (ZRLogVerifyDebugCondition(debugNo, topic, guid))                                                \
    {                                                                                               \
        ZRLogAquireLock();                                                                          \
        ZRLogToConsole(ZRLOG_ADMIN_INFO, guid, topic, debugNo, file, func, line, format, ##__VA_ARGS__);  \
        ZRLogReleaseLock();                                                                         \
    }

/**
 * @def ZRLOG_USER(guid, topic, debugNo, format, ...) ZRLOG_PRINT_MESSAGE(format, debugNo);
 *
 * @ingroup  ZRDDSLog
 *
 * @brief   ����û���Ϣ�ꡣ
 *
 * @param   guid    ����Ϣ����ʵ�塣
 * @param   topic   ����Ϣ�������⡣
 * @param   debugNo ����Ϣ�ı�š�
 * @param   format  �ַ�����ʽ(��printf).
 * @param   ...     ��Ρ�
 */

#define ZRLOG_USER(guid, topic, debugNo, format, ...)                                               \
    ZRLOG_PRINT_MESSAGE(format, debugNo);                                                           \
    if (ZRLogVerifyDebugCondition(debugNo, topic, guid))                                            \
    {                                                                                               \
        ZRLogAquireLock();                                                                          \
        ZRLogToConsole(ZRLOG_USER_INFO, __FILE__, __FUNCTION__, __LINE__, format, ##__VA_ARGS__);   \
        ZRLogReleaseLock();                                                                         \
    }

/**
 * @def ZRLOG_USER_W_POS(guid, topic, debugNo, file, func, line, format, ...)
 *
 * @ingroup ZRDDSLog
 *
 * @brief   ����û���Ϣ�ꡣ
 *
 * @param   guid    ���û���Ϣ����ʵ�塣
 * @param   topic   ���û���Ϣ�������⡣
 * @param   debugNo ���û���Ϣ�ı�š�
 * @param   file    �����ļ����ַ����͡�
 * @param   func    �����������ַ����͡�
 * @param   line    �кţ����͡�
 * @param   format  �ַ�����ʽ(��printf).
 * @param   ...     ��Ρ�
 */

#define ZRLOG_USER_W_POS(guid, topic, debugNo, file, func, line, format, ...)                       \
    ZRLOG_PRINT_MESSAGE(format, debugNo);                                                           \
    if (ZRLogVerifyDebugCondition(debugNo, topic, guid))                                            \
    {                                                                                               \
        ZRLogAquireLock();                                                                          \
        ZRLogToConsole(ZRLOG_USER_INFO, guid, topic, debugNo, file, func, line, format, ##__VA_ARGS__);   \
        ZRLogReleaseLock();                                                                         \
    }

/**
 * @def ZRLOG_DEBUG_W_EXP(guid, topic, debugNo, preState1, preState2, postState1, postState2,
 *      format, ...) ZRLOG_PRINT_MESSAGE(format, debugNo);
 *
 * @ingroup  ZRDDSLog
 *
 * @brief   ���������Ϣ�꣬�����ǰ��ֱ�ִ��ָ�����ʽ��
 *
 * @param   guid        �õ�����Ϣ����ʵ�塣
 * @param   topic       �õ�����Ϣ�������⡣
 * @param   debugNo     �õ�����Ϣ�ı�š�
 * @param   preState1   ��һ��ǰ����䡣
 * @param   preState2   �ڶ���ǰ����䡣
 * @param   postState1  ��һ��������䡣
 * @param   postState2  �ڶ���������䡣
 * @param   format      �ַ�����ʽ(��printf).
 * @param   ...         ��Ρ�
 */

#define ZRLOG_DEBUG_W_EXP(guid, topic, debugNo, preState1, preState2, postState1, postState2, format, ...)          \
    ZRLOG_PRINT_MESSAGE(format, debugNo);                                                                           \
    if (ZRLogVerifyDebugCondition(debugNo, topic, guid))                                                            \
    {                                                                                                               \
        preState1;                                                                                                  \
        preState2;                                                                                                  \
        ZRLogAquireLock();                                                                                          \
        ZRLogToConsole(ZRLOG_ADMIN_INFO, guid, topic, debugNo, __FILE__, __FUNCTION__, __LINE__, format, ##__VA_ARGS__);  \
        ZRLogReleaseLock();                                                                                         \
        postState1;                                                                                                 \
        postState2;                                                                                                 \
    }

/**
 * @def ZRLOG_DEBUG_W_EXP2(guid, topic, debugNo, preState1, preState2, postState1, postState2,
 *      format, ...) if (ZRLogVerifyDebugCondition(debugNo, topic, guid))
 *
 * @ingroup  ZRDDSLog
 *
 * @brief   ���������Ϣ�꣬���������־��������ַ������������������ʣ�����ݡ�
 *
 * @param   guid        �õ�����Ϣ����ʵ�塣
 * @param   topic       �õ�����Ϣ�������⡣
 * @param   debugNo     �õ�����Ϣ�ı�š�
 * @param   preState1   ��һ��ǰ����䡣
 * @param   preState2   �ڶ���ǰ����䡣
 * @param   postState1  ��һ��������䡣
 * @param   postState2  �ڶ���������䡣
 * @param   format      �ַ�����ʽ(��printf).
 * @param   ...         ��Ρ�
 */

#define ZRLOG_DEBUG_W_EXP2(guid, topic, debugNo, preState1, preState2, postState1, postState2, format, ...)         \
    ZRLOG_PRINT_MESSAGE(format, debugNo);                                                                           \
    if (ZRLogVerifyDebugCondition(debugNo, topic, guid))                                                            \
    {                                                                                                               \
        ZRLogBeginLogWNo(ZRLOG_ADMIN_INFO, __FILE__, __FUNCTION__, __LINE__, true, topic, debugNo);                 \
        preState1;                                                                                                  \
        preState2;                                                                                                  \
        ZRLogAquireLock();                                                                                          \
        ZRLogToConsole(ZRLOG_ADMIN_INFO, guid, topic, debugNo, __FILE__, __FUNCTION__, __LINE__, format, ##__VA_ARGS__);  \
        ZRLogReleaseLock();                                                                                         \
        postState1;                                                                                                 \
        postState2;                                                                                                 \
        ZRLogEndLog();                                                                                              \
    }

#ifdef __cplusplus
}
#endif

#endif // ZRUserLog_h__
