/**
 * @file:       ZRDDSDataWriter.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#ifndef ZRDDSDataWriter_h__
#define ZRDDSDataWriter_h__

#include "DataWriter.h"
#include <stdlib.h>

struct DataWriterImpl;

namespace DDS {

/**
 * @class   ZRDDSDataWriter
 *
 * @ingroup CppPublication
 *
 * @tparam  T       �û������������ͣ����磺 Foo
 *
 * @brief   ZRDDS�ṩ������д��ģ���࣬�����ṩǿ���Ͱ�ȫ�ӿڵ�����д�߽ӿڡ�
 *          
 * @details ģ�����TΪ�û������������ͣ���ģ�����������д�������������������������صĽӿڣ�
 *          �����������޹صĽӿ�ֱ��ʹ�ø��� DDS::DataWriter �ļ��ɡ�
 *
 */
template<typename T>
class ZRDDSDataWriter : public DataWriter
{
public:

    /**
     * @fn InstanceHandle_t ZRDDSDataWriter::register_instance(const T& data);
     *
     * @brief ������д��ע��һ��ʵ��
     *
     * @details ����������T�д��м��������ĳ�Աʱ����Ա��ȡֵ��ͬ���γɲ�ͬ��ʵ����
     *          �ýӿ�������д��ע��һ��ʵ��������д�߻��ȡ����� @e data ������Ϊ�����������
     *          ������ֵ����һ��ʵ����������ظ��û���ʵ�������������ʵ������ #write �����е� @e handle ������
     *          �� DDS_DataWriterResourceLimitsQosPolicy::autoregister_instances == true ʱ��
     *          �ҵ��� #write �ӿ�ʱ @e handle �������� #DDS_HANDLE_NIL_NATIVE ʱ�����Զ�ע��δע���ʵ����
     *          ���Ƿ����ٶȻ��������˿�ʹ����ע���ʵ������������͵��ٶȡ�
     *
     * @param data �������ݣ�ֻ�б�����Ϊ����ĳ�Ա�ᱻ��ȡ��
     *
     * @return ���ע��ɹ�������������Ӧ��ʵ����������򷵻� #DDS_HANDLE_NIL_NATIVE
     */
    InstanceHandle_t register_instance(const T& data);

    /**
     * @fn InstanceHandle_t ZRDDSDataWriter::register_instance_w_timestamp( const T& data, const Time_t& timestamp);
     *
     * @brief ������д��ע��һ��ʵ������ #register_instance ������ʹ���ṩ��ʱ�������Ĭ�ϵ�ʱ���
     *
     * @param data      �������ݣ�ֻ�б�����Ϊ����ĳ�Ա�ᱻ��ȡ��
     * @param timestamp �û��ṩ��ʱ���
     *
     * @return ���ע��ɹ�������������Ӧ��ʵ����������򷵻� #DDS_HANDLE_NIL_NATIVE
     */
    InstanceHandle_t register_instance_w_timestamp(
        const T& data,
        const Time_t& timestamp);

    /**
     * @fn ReturnCode_t ZRDDSDataWriter::unregister_instance( const T& data, const InstanceHandle_t& handle);
     *
     * @brief ���Ѿ�ע���ʵ��������д����ע��
     *
     * @details ����ʹ������������ʵ���������ע��������ͬʱ�ṩ���г�ͻ��ȱʧʱ�����ش���
     *
     * @param data   �������ݣ�ֻ�б�����Ϊ����ĳ�Ա�ᱻ��ȡ
     * @param handle ע��ʵ��ʱ�õ���ʵ������� #DDS_HANDLE_NIL_NATIVE
     *
     * @return  ��ǰ���ܵķ���ֵ���£�
     *          - #DDS_RETCODE_OK :��ʾע��ʵ���ɹ���
     *          - #DDS_RETCODE_NOT_ENABLED :��ʾʵ��δʹ�ܣ�
     *          - #DDS_RETCODE_PRECONDITION_NOT_MET  :�������ṩ��������ʵ�������ƥ�䣻
     *          - #DDS_RETCODE_BAD_PARAMETER :�����д��ڴ���
     *          - #DDS_RETCODE_ERROR :��ʾδ֪�����µĶ�ȡ����
     */
    ReturnCode_t unregister_instance(
        const T& data,
        const InstanceHandle_t& handle);

    /**
     * @fn ReturnCode_t ZRDDSDataWriter::unregister_instance_w_timestamp( const T& data, const InstanceHandle_t& handle, const Time_t& timestamp);
     *
     * @brief ���Ѿ�ע���ʵ��������д����ע������ #unregister_instance ������ʹ���ṩ��ʱ�������Ĭ�ϵ�ʱ���
     *
     * @details ����ʹ������������ʵ���������ע��������ͬʱ�ṩ���г�ͻ��ȱʧʱ�����ش���
     *
     * @param data      �������ݣ�ֻ�б�����Ϊ����ĳ�Ա�ᱻ��ȡ
     * @param handle    ע��ʵ��ʱ�õ���ʵ������� #DDS_HANDLE_NIL_NATIVE
     * @param timestamp �û��ṩ��ʱ���
     *
     * @return ��ǰ���ܵķ���ֵ���£�
     *         - #DDS_RETCODE_OK :��ʾע��ʵ���ɹ���
     *         - #DDS_RETCODE_NOT_ENABLED :��ʾʵ��δʹ�ܣ�
     *         - #DDS_RETCODE_PRECONDITION_NOT_MET  :�������ṩ��������ʵ�������ƥ�䣻
     *         - #DDS_RETCODE_BAD_PARAMETER :�����д��ڴ���
     *         - #DDS_RETCODE_ERROR :��ʾδ֪�����µĶ�ȡ����
     */
    ReturnCode_t unregister_instance_w_timestamp(
        const T& data,
        const InstanceHandle_t& handle,
        const Time_t& timestamp);

    /**
     * @fn ReturnCode_t ZRDDSDataWriter::get_key_value( T& key_holder, const InstanceHandle_t& handle);
     *
     * @brief ��ʵ�������ȡ��Ӧ������ֵ��ֻ������Ϊ������������ֵ��Ч��
     *
     * @param [in,out] key_holder �����ȡ��������ֵ���ݵ�����
     * @param handle              ��Ҫ��ȡ��ʵ����Ӧ��ʵ�����
     *
     * @return  ��ǰ���ܵķ���ֵ���£�
     *          - #DDS_RETCODE_OK :��ʾ��ȡ�ɹ���
     *          - #DDS_RETCODE_NOT_ENABLED :��ʾʵ��δʹ�ܣ�
     *          - #DDS_RETCODE_BAD_PARAMETER :�����д��ڴ���
     *          - #DDS_RETCODE_ERROR :��ʾδ֪�����µĶ�ȡ����
     */
    ReturnCode_t get_key_value(
        T& key_holder,
        const InstanceHandle_t& handle);

    /**
     * @fn InstanceHandle_t ZRDDSDataWriter::lookup_instance(const T& key_holder);
     *
     * @brief ͨ������ֵ��ѯʵ�������
     *
     * @param key_holder ��������ֵ���ݵ�����
     *
     * @return �����ѯ�ɹ�������������Ӧ��ʵ����������򷵻� #DDS_HANDLE_NIL_NATIVE
     */
    InstanceHandle_t lookup_instance(const T& key_holder);

    /**
     * @fn ReturnCode_t ZRDDSDataWriter::write(const T& data, const InstanceHandle_t& handle);
     *
     * @brief ����һ������������
     *
     * @details �ýӿڿ��ܷ���������������Ϊ�ɿ����䣬�Ҹ�����д����ʷ�������� DDS_HistoryQosPolicy::kind == 
     *          #DDS_KEEP_ALL_HISTORY_QOS ʱ����������������ʱ�ᷢ��������
     *          ��ʹ��ͬ�������ҵ���Э��ջ�ӿڳ�������ʱ�ᷢ��������
     *          ���������������Ƶ��������������ʱ��ͨ�� DDS_ReliabilityQosPolicy::max_blocking_time ���ã�
     *          ��Э��ջ���µ����������ʱ�䲻��Ԥ֪
     *
     * @param data   ��Ҫ����������������
     * @param handle ����������Ӧ��ʵ���������������д����Դ�������� 
     *               DDS_DataWriterResourceLimitsQosPolicy::autoregister_instances == trueʱ��
     *               ���Դ��� #DDS_HANDLE_NIL_NATIVE ����ʱ�ײ㽫�Զ�ע�� @e data ��������ʵ����
     *
     * @return ��ǰ���ܵķ���ֵ���£�
     *          - #DDS_RETCODE_OK :��ʾ��ȡ�ɹ���
     *          - #DDS_RETCODE_NOT_ENABLED :��ʾʵ��δʹ�ܣ�
     *          - #DDS_RETCODE_BAD_PARAMETER :�����д��ڴ���
     *          - #DDS_RETCODE_OUT_OF_RESOURCES :��ǰ��Դ���㣻
     *          - #DDS_RETCODE_TIMEOUT :��ǰ������ʱ��
     *          - #DDS_RETCODE_ERROR :��ʾδ֪�����µĶ�ȡ����
     */
    ReturnCode_t write(const T& data, const InstanceHandle_t& handle);

    /**
     * @fn ReturnCode_t ZRDDSDataWriter::write_w_timestamp( const T& instance, const InstanceHandle_t& handle, const Time_t& timestamp);
     *
     * @brief ����һ�������������� #write ������ʹ���ṩ��ʱ�������Ĭ�ϵ�ʱ�����
     *
     * @param instance  ��Ҫ����������������
     * @param handle    ����������Ӧ��ʵ���������������д����Դ��������
     *               DDS_DataWriterResourceLimitsQosPolicy::autoregister_instances == trueʱ��
     *               ���Դ��� #DDS_HANDLE_NIL_NATIVE ����ʱ�ײ㽫�Զ�ע�� @e instance ��������ʵ����
     * @param timestamp �û��ṩ��ʱ���
     *
     * @return ��ǰ���ܵķ���ֵ���£�
     *          - #DDS_RETCODE_OK :��ʾ��ȡ�ɹ���
     *          - #DDS_RETCODE_NOT_ENABLED :��ʾʵ��δʹ�ܣ�
     *          - #DDS_RETCODE_BAD_PARAMETER :�����д��ڴ���
     *          - #DDS_RETCODE_OUT_OF_RESOURCES :��ǰ��Դ���㣻
     *          - #DDS_RETCODE_TIMEOUT :��ǰ������ʱ��
     *          - #DDS_RETCODE_ERROR :��ʾδ֪�����µĶ�ȡ����
     */
    ReturnCode_t write_w_timestamp(
        const T& instance, 
        const InstanceHandle_t& handle, 
        const Time_t& timestamp);

    /**
     * @fn ReturnCode_t ZRDDSDataWriter::write_w_dst(const T& instance, const InstanceHandle_t& handle, const Time_t& timestamp, const InstanceHandle_t& dst_handle);
     *
     * @brief ��ָ���Զ˷���һ������������
     *
     * @param instance      ��Ҫ����������������
     * @param handle        ����������Ӧ��ʵ���������������д����Դ��������
     *                      DDS_DataWriterResourceLimitsQosPolicy::autoregister_instances == trueʱ��
     *                      ���Դ��� #DDS_HANDLE_NIL_NATIVE ����ʱ�ײ㽫�Զ�ע�� @e instance ��������ʵ����
     * @param timestamp     �û��ṩ��ʱ���
     * @param dst_handle    �Զ˵�Ψһ��ʶ����Ϊ���ݶ��ߵ�Ψһ��ʶ����������ݶ��߷�������Ϊ������ߵ�Ψһ��ʶ�������������ߴ������������ݶ��߷�����
     *
     * @return ��ǰ���ܵķ���ֵ���£�
     *          - #DDS_RETCODE_OK :��ʾ��ȡ�ɹ���
     *          - #DDS_RETCODE_NOT_ENABLED :��ʾʵ��δʹ�ܣ�
     *          - #DDS_RETCODE_BAD_PARAMETER :�����д��ڴ���
     *          - #DDS_RETCODE_OUT_OF_RESOURCES :��ǰ��Դ���㣻
     *          - #DDS_RETCODE_TIMEOUT :��ǰ������ʱ��
     *          - #DDS_RETCODE_ERROR :��ʾδ֪�����µĶ�ȡ����
     */
    ReturnCode_t write_w_dst(
        const T& instance,
        const InstanceHandle_t& handle,
        const Time_t& timestamp,
        const InstanceHandle_t& dst_handle);

    /**
     * @fn ReturnCode_t ZRDDSDataWriter::write_w_dst(const T& instance, const InstanceHandle_t& handle, const InstanceHandle_t& dst_handle);
     *
     * @brief ��ָ���Զ˷���һ������������
     *
     * @param instance      ��Ҫ����������������
     * @param handle        ����������Ӧ��ʵ���������������д����Դ��������
     *                      DDS_DataWriterResourceLimitsQosPolicy::autoregister_instances == trueʱ��
     *                      ���Դ��� #DDS_HANDLE_NIL_NATIVE ����ʱ�ײ㽫�Զ�ע�� @e instance ��������ʵ����
     * @param dst_handle    �Զ˵�Ψһ��ʶ����Ϊ���ݶ��ߵ�Ψһ��ʶ����������ݶ��߷�������Ϊ������ߵ�Ψһ��ʶ�������������ߴ������������ݶ��߷�����
     *
     * @return ��ǰ���ܵķ���ֵ���£�
     *          - #DDS_RETCODE_OK :��ʾ��ȡ�ɹ���
     *          - #DDS_RETCODE_NOT_ENABLED :��ʾʵ��δʹ�ܣ�
     *          - #DDS_RETCODE_BAD_PARAMETER :�����д��ڴ���
     *          - #DDS_RETCODE_OUT_OF_RESOURCES :��ǰ��Դ���㣻
     *          - #DDS_RETCODE_TIMEOUT :��ǰ������ʱ��
     *          - #DDS_RETCODE_ERROR :��ʾδ֪�����µĶ�ȡ����
     */
    ReturnCode_t write_w_dst(
        const T& instance,
        const InstanceHandle_t& handle,
        const InstanceHandle_t& dst_handle);

    /**
     * @fn ReturnCode_t ZRDDSDataWriter::dispose( const T& instance, const InstanceHandle_t& handle);
     *
     * @brief ����һ���Ѿ�ע���ʵ����
     *
     * @details ����ʹ������������ʵ������������٣�����ͬʱ�ṩ���г�ͻ��ȱʧʱ�����ش���
     *
     * @param instance  �������ݣ�ֻ�б�����Ϊ����ĳ�Ա�ᱻ��ȡ
     * @param handle    ע��ʵ��ʱ�õ���ʵ������� #DDS_HANDLE_NIL_NATIVE
     *
     * @return  ��ǰ���ܵķ���ֵ���£�
     *          - #DDS_RETCODE_OK :��ʾע��ʵ���ɹ���
     *          - #DDS_RETCODE_NOT_ENABLED :��ʾʵ��δʹ�ܣ�
     *          - #DDS_RETCODE_PRECONDITION_NOT_MET  :�������ṩ��������ʵ�������ƥ�䣻
     *          - #DDS_RETCODE_BAD_PARAMETER :�����д��ڴ���
     *          - #DDS_RETCODE_ERROR :��ʾδ֪�����µĶ�ȡ����
     */
    ReturnCode_t dispose(
        const T& instance, 
        const InstanceHandle_t& handle);

    /**
     * @fn ReturnCode_t ZRDDSDataWriter::dispose_w_timestamp( const T& instance, const InstanceHandle_t& handle, const Time_t& timestamp);
     *
     * @brief ����һ���Ѿ�ע���ʵ������ #unregister_instance ������ʹ���ṩ��ʱ�������Ĭ�ϵ�ʱ�����
     *
     * @param instance  �������ݣ�ֻ�б�����Ϊ����ĳ�Ա�ᱻ��ȡ
     * @param handle    ע��ʵ��ʱ�õ���ʵ������� #DDS_HANDLE_NIL_NATIVE
     * @param timestamp �û��ṩ��ʱ���
     *
     * @return ��ǰ���ܵķ���ֵ���£�
     *         - #DDS_RETCODE_OK :��ʾע��ʵ���ɹ���
     *         - #DDS_RETCODE_NOT_ENABLED :��ʾʵ��δʹ�ܣ�
     *         - #DDS_RETCODE_PRECONDITION_NOT_MET  :�������ṩ��������ʵ�������ƥ�䣻
     *         - #DDS_RETCODE_BAD_PARAMETER :�����д��ڴ���
     *         - #DDS_RETCODE_ERROR :��ʾδ֪�����µĶ�ȡ����
     *
     * @details ����ʹ������������ʵ������������٣�����ͬʱ�ṩ���г�ͻ��ȱʧʱ�����ش���
     */
    ReturnCode_t dispose_w_timestamp(
        const T& instance, 
        const InstanceHandle_t& handle, 
        const Time_t& timestamp);
    static ZRDDSDataWriter* createI(DataWriter *impl, void *typesupport);
    static ReturnCode_t destroyI(ZRDDSDataWriter *dw, void* typesupport);
protected:
    ZRDDSDataWriter(DataWriter *impl);
};

template<typename T>
ZRDDSDataWriter<T>::ZRDDSDataWriter(DataWriter *impl)
    :DataWriter(impl)
{

}

template<typename T>
ZRDDSDataWriter<T>* ZRDDSDataWriter<T>::createI(DataWriter *impl, void *typesupport)
{
    return new ZRDDSDataWriter<T>(impl);
}

template<typename T>
ReturnCode_t ZRDDSDataWriter<T>::destroyI(ZRDDSDataWriter *dw, void* typesupport)
{
    if (NULL != dw) delete dw;
    return DDS_RETCODE_OK;
}

template<typename T>
InstanceHandle_t ZRDDSDataWriter<T>::register_instance(const T& data)
{
    return m_impl->register_instance_untype(&data, NULL);
}

template<typename T>
InstanceHandle_t ZRDDSDataWriter<T>::register_instance_w_timestamp(
    const T& data,
    const Time_t& timestamp)
{
    return m_impl->register_instance_untype(&data, &timestamp);
}

template<typename T>
ReturnCode_t ZRDDSDataWriter<T>::unregister_instance(
    const T& data,
    const InstanceHandle_t& handle)
{
    return m_impl->unregister_instance_untype(&data, handle, NULL);
}

template<typename T>
ReturnCode_t ZRDDSDataWriter<T>::unregister_instance_w_timestamp(
    const T& data,
    const InstanceHandle_t& handle,
    const Time_t& timestamp)
{
    return m_impl->unregister_instance_untype(&data, handle, &timestamp);
}

template<typename T>
ReturnCode_t ZRDDSDataWriter<T>::get_key_value(
    T& key_holder,
    const InstanceHandle_t& handle)
{
    return m_impl->get_key_value_untype(&key_holder, handle);
}

template<typename T>
InstanceHandle_t ZRDDSDataWriter<T>::lookup_instance(const T& key_holder)
{
    return m_impl->lookup_instance_untype(&key_holder);
}

template<typename T>
ReturnCode_t ZRDDSDataWriter<T>::write(const T& data, const InstanceHandle_t& handle)
{
    return m_impl->write_untype_w_dst(&data, handle, NULL, NULL);
}

template<typename T>
ReturnCode_t ZRDDSDataWriter<T>::write_w_timestamp(
    const T& data,
    const InstanceHandle_t& handle,
    const Time_t& timestamp)
{
    return m_impl->write_untype_w_dst(&data, handle, &timestamp, NULL);
}

template<typename T>
ReturnCode_t DDS::ZRDDSDataWriter<T>::write_w_dst(
    const T& instance,
    const InstanceHandle_t& handle,
    const Time_t& timestamp,
    const InstanceHandle_t& dst_handle)
{
    return m_impl->write_untype_w_dst(&instance, handle, &timestamp, &dst_handle);
}

template<typename T>
ReturnCode_t DDS::ZRDDSDataWriter<T>::write_w_dst(
    const T& instance,
    const InstanceHandle_t& handle,
    const InstanceHandle_t& dst_handle)
{
    return m_impl->write_untype_w_dst(&instance, handle, NULL, &dst_handle);
}

template<typename T>
ReturnCode_t ZRDDSDataWriter<T>::dispose(
    const T& instance,
    const InstanceHandle_t& handle)
{
    return m_impl->dispose_untype(&instance, handle, NULL);
}

template<typename T>
ReturnCode_t ZRDDSDataWriter<T>::dispose_w_timestamp(
    const T& instance,
    const InstanceHandle_t& handle,
    const Time_t& timestamp)
{
    return m_impl->dispose_untype(&instance, handle, &timestamp);
}

} // namespace DDS

#endif // ZRDDSDataWriter_h__
