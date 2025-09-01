#ifndef ZRDDSInteractiveCMD_h__
#define ZRDDSInteractiveCMD_h__

/**
 * @typedef struct ZRDDSInteractiveCmdReqID
 *
 * @brief   ���ڱ�ʶ�����Ŀ�Ķˡ�
 */

typedef struct ZRDDSInteractiveCmdReqID
{
    /** @brief   ��ʶ�ڵ㡣 */
    DDS_Long hostId;
    /** @brief   ��ʶӦ�á� */
    DDS_Long appId;
    /** @brief   ��ʶ���кš� */
    DDS_Long seq;
} ZRDDSInteractiveCmdReqID; // @Extensibility(EXTENSIBLE)

/**
 * @typedef enum ZRDDSInteractiveCmdKind
 *
 * @brief   ���ֲ�ͬ��������͡�
 */

typedef enum ZRDDSInteractiveCmdKind
{
    ZRDDS_SET_LOG_ENABLE_RANGE = 0,
    ZRDDS_SET_LOG_DISABLE_RANGE = 1,
    ZRDDS_SET_LOG_ENABLE_TOPIC = 2,
    ZRDDS_SET_LOG_DISABLE_TOPIC = 3,
    ZRDDS_SET_LOG_ENABLE_ENTITYID = 4,
    ZRDDS_SET_LOG_DISABLE_ENTITYID = 5,
    ZRDDS_SET_LOG_MASK = 6,
    ZRDDS_GET_VARIABLE_VALUE = 7,
    ZRDDS_SET_LOG_STYLE = 8
} ZRDDSInteractiveCmdKind;// @BitBound(32)
/**
 * @typedef struct ZRDDSInteractiveCMD
 *
 * @brief   �����ⲿ����DDSִ�е����
 *
 * @details ��ǰ֧�ֵ����������Լ����������±�
 *          
 *          ���� | ���� | ����
 *          --- | --- | ---
 *          0 | zrdds.set.log.enable.range | 0,2
 *          1 | zrdds.set.log.disable.range | 0,2
 *          2 | zrdds.set.log.enable.topic | topic_name
 *          3 | zrdds.set.log.disable.topic | topic_name
 *          4 | zrdds.set.log.enable.entity_id | c0a80000 00000000 00000000 00000000
 *          5 | zrdds.set.log.disable.entity_id | c0a80000 00000000 00000000 00000000
 *          6 | zrdds.set.log.mask | 0xffff(console) 0xfffff(file) 0xfffff(dist) 
 *          7 | zrdds.get.variable.value | %s(ȫ�ֱ�������):(offset(����ڵ�ǰ��ַ��ƫ����)*size(��ȡ�ڴ�Ĵ�С��С��0�����⺬�塣-1 Ϊ��һ����ȡ����Ľ����ã�-2 Ϊ��һ����ַ����offset�����ٶ�ȡ�ڴ棩))+  
 *          8 | zrdds.set.log.style  |  ��ZRLogDisplayStyle�е�ֵ���Ӧ
 */

typedef struct ZRDDSInteractiveCMD
{
    /** @brief   ����ID�� */
    ZRDDSInteractiveCmdReqID cmdId;
    /** @brief   �������͡�*/
    ZRDDSInteractiveCmdKind cmdKind;
    /** @brief   ��������� */
    char cmdParameter[1024];
}ZRDDSInteractiveCMD;

/**
 * @typedef struct ZRDDSInteractiveResponse
 *
 * @brief   ����ִ�н����
 */

typedef struct ZRDDSInteractiveResponse
{
    /** @brief   ����Ӧ�����������ʶ�� */
    ZRDDSInteractiveCmdReqID cmdId;
    /** @brief   ����ִ�н���� */
    ZR_UINT32 ret;
    /** @brief   ��ϸ��Ϣ�� */
    DDS_Char response[1074];
} ZRDDSInteractiveResponse;

#endif // ZRDDSInteractiveCMD_h__
