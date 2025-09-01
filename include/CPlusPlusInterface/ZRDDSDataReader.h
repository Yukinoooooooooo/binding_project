/**
 * @file:       ZRDDSDataReader.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#ifndef ZRDDSDataReader_h__
#define ZRDDSDataReader_h__

#include "DataReader.h"

namespace DDS {

/**
 * @class   ZRDDSDataReader
 *
 * @ingroup CppSubscription
 *
 * @tparam  T       �û������������ͣ����磺 Foo 
 * @tparam  TSeq    �û����������������У����磺 FooSeq
 *
 * @brief   ZRDDS�ṩ�Ķ�����ģ���࣬�����ṩǿ���Ͱ�ȫ�ӿڵ����ݶ��߽ӿڡ�
 *          
 * @details ģ�����TΪ�û������������ͣ�TSeq�û����������������У���ģ����������ݶ��������������������������صĽӿڣ�
 *          �����������޹صĽӿ�ֱ��ʹ�ø��� DDS::DataReader �ļ��ɡ�
 *
 */
template<typename T, typename TSeq>
class ZRDDSDataReader : public DataReader
{
public:

    /**
     * @fn  ReturnCode_t ZRDDSDataReader::read( TSeq &data_values, SampleInfoSeq &sample_infos, Long max_samples, SampleStateMask sample_mask, ViewStateMask view_mask, InstanceStateMask instance_mask);
     *
     * @brief   �ýӿڴ����ݶ��ߵײ��ȡ�û��������ݡ�
     *
     * @details �÷������ص�����˳��μ� DDS_PresentationQosPolicy �� @e data_values �Լ� @e sample_infos ����
     *          ���б��������ͬ�� ���ȣ� FooSeq::length �¼��len������󳤶ȣ� FooSeq::maximum �¼��max_len����
     *          �Ƿ�ӵ�пռ䣨 FooSeq::has_ownership �¼��own�� �������ԣ����򽫷��� #DDS_RETCODE_PRECONDITION_NOT_MET ����
     *          ���ú������سɹ�ʱ��@e data_values �Լ� @e sample_infos ������������Ҳ��ͬ�����±���ͬ�������Լ�����
     *          ��Ϣ���Ӧ��
     *          
     *          �� max_len == 0��������û�û���ṩ�����ռ䣬�÷������ԡ���衱���㿽�����������ݵ�ָ�룩�ķ�ʽ��� 
     *          @e data_values �Լ� @e sample_infos ����own�������ó�false��len����Ϊ��ȡ��������������
     *          ���û�ʹ���귵�ص���������ʱӦ�õ��� #return_loan �����黹��Щ�ռ䣻
     *          
     *          �� max_len > 0 && own == true ʱ��������û��ṩ�������ռ䣬�÷������ײ�洢�����������Լ�
     *          ��Ӧ��������Ϣ�������ṩ�Ŀռ��У�len��ʾ����������������max_len���ֲ��䣬��Щ����������������黹��
     *          ��Ϊ��ͳһ�û���ʹ��ϰ�ߣ����� #return_loan ��ɣ��ײ����Ա��ε��á�
     *          �� @e max_samples <= max_len ʱ���÷��������ȡ @e max_samples ��������
     *          �� @e max_samples > max_len ʱ���÷��������� #DDS_RETCODE_PRECONDITION_NOT_MET  ����
     *
     * @param [in,out]  data_values     ���������������������ݶ����ж�ȡ���������н����
     * @param [in,out]  sample_infos    ���������������������ݶ����ж�ȡ��������Ϣ���н����
     * @param   max_samples             ָ�����β������ӵײ��ȡ������������
     * @param   sample_mask             ָ��Ŀ�����������ķ���״̬���ϵ����룻
     * @param   view_mask               ָ��Ŀ��������������ͼ״̬���ϵ����룻
     * @param   instance_mask           ָ��Ŀ����������������ʵ����ʵ��״̬���ϵ����룻
     *                                  
     * @return  ��ǰ���ܵķ���ֵ���£�
     *          - #DDS_RETCODE_OK :��ʾȡ�����ݳɹ���
     *          - #DDS_RETCODE_PRECONDITION_NOT_MET  :�����д��ڴ���
     *          - #DDS_RETCODE_NO_DATA :��ʾ��ǰû���������������ݣ�
     *          - #DDS_RETCODE_ERROR :��ʾδ֪�����µĶ�ȡ����
     *
     * @note    - ʹ��@ref read-take ϵ�к���ʱ��Ӧ�жϷ���ֵ�Ƿ�ɹ�������������ɳ����쳣��
     *          - ��ʹ�ò������ص�����ʱ��Ӧ�����Ӧ�� DDS_SampleInfo::valid_data �Ƿ���Ч��  
     */

    ReturnCode_t read(
        TSeq &data_values,
        SampleInfoSeq &sample_infos,
        Long max_samples,
        SampleStateMask sample_mask,
        ViewStateMask view_mask,
        InstanceStateMask instance_mask);

    /**
     * @fn  ReturnCode_t ZRDDSDataReader::take( TSeq &data_values, SampleInfoSeq &sample_infos, Long max_samples, SampleStateMask sample_mask, ViewStateMask view_mask, InstanceStateMask instance_mask);
     *
     * @brief   �ýӿڴ����ݶ��ߵײ�ȡ���û��������ݡ�
     *
     * @param [in,out]  data_values     ���������������������ݶ����ж�ȡ���������н����
     * @param [in,out]  sample_infos    ���������������������ݶ����ж�ȡ��������Ϣ���н����
     * @param   max_samples             ָ�����β������ӵײ��ȡ������������
     * @param   sample_mask             ָ��Ŀ�����������ķ���״̬���ϵ����룻
     * @param   view_mask               ָ��Ŀ��������������ͼ״̬���ϵ����룻
     * @param   instance_mask           ָ��Ŀ����������������ʵ����ʵ��״̬���ϵ����룻
     *
     * @details �÷����� #read ��ʽ���ƣ��������ڱ������Ὣ��ȡ�������������ӵײ�������Ƴ����Ƴ���ʱ�����£�
     *          - �������㿽���ķ�ʽ��ȡʱ���ڵ��� #return_loan ���Ƴ���  
     *          - ����û��ṩ�洢�ռ伴���ÿ����ķ�ʽ��ȡʱ���ڱ������Ѿ��Ƴ���
     *
     * @return  �μ� #read ������
     */

    ReturnCode_t take(
        TSeq &data_values,
        SampleInfoSeq &sample_infos,
        Long max_samples,
        SampleStateMask sample_mask,
        ViewStateMask view_mask,
        InstanceStateMask instance_mask);

    /**
     * @fn  ReturnCode_t ZRDDSDataReader::read_next_sample( T &data_value, SampleInfo &sample_info);
     *
     * @brief   �÷������ڴ�ͨ���м�����ζ�ȡδ��ȡ����������
     *          
     * @details �÷������û��ṩ�����ռ䣬���ӵײ���������������������ṩ�Ŀռ��У�������� #return_loan ������
     *          ������˳���� DDS_PresentationQosPolicy ȷ����
     *
     * @param [in,out]  data_value  ���������������������ݶ����ж�ȡ�����������
     * @param [in,out]  sample_info ���������������������ݶ����ж�ȡ��������Ϣ�����
     *
     * @return  ��ǰ���ܵķ���ֵ���£�
     *          - #DDS_RETCODE_OK :��ʾȡ�����ݳɹ���
     *          - #DDS_RETCODE_NO_DATA :��ʾ��ǰû���������������ݣ�
     *          - #DDS_RETCODE_ERROR :��ʾδ֪�����µĶ�ȡ����
     */
    ReturnCode_t read_next_sample(
        T &data_value,
        SampleInfo &sample_info);

    /**
     * @fn  ReturnCode_t ZRDDSDataReader::take_next_sample( T &data_value, SampleInfo &sample_info);
     *
     * @brief   �÷������ڴ�ͨ���м������ȡ��δ��ȡ����������
     *
     * @param [in,out]  data_value  ���������������������ݶ����ж�ȡ�����������
     * @param [in,out]  sample_info ���������������������ݶ����ж�ȡ��������Ϣ�����
     *
     * @return  ��ǰ���ܵķ���ֵ���£�
     *          - #DDS_RETCODE_OK :��ʾȡ�����ݳɹ���
     *          - #DDS_RETCODE_NO_DATA :��ʾ��ǰû���������������ݣ�
     *          - #DDS_RETCODE_ERROR :��ʾδ֪�����µĶ�ȡ����
     */
    ReturnCode_t take_next_sample(
        T &data_value,
        SampleInfo &sample_info);

    /**
     * @fn  ReturnCode_t ZRDDSDataReader::read_instance( TSeq &data_values, SampleInfoSeq &sample_infos, Long max_samples, const InstanceHandle_t &handle, SampleStateMask sample_mask, ViewStateMask view_mask, InstanceStateMask instance_mask);
     *
     * @brief   ��ȡָ������ʵ�������������������������ϡ�
     *
     * @details �÷����� #read �ӿڻ������ټ���ָ������ʵ����Ҫ��
     *          
     * @param [in,out]  data_values     ���������������������ݶ����ж�ȡ���������н����
     * @param [in,out]  sample_infos    ���������������������ݶ����ж�ȡ��������Ϣ���н����
     * @param   max_samples             ָ�����β������ӵײ��ȡ������������
     * @param   handle                  ָ��Ŀ������ʵ���ı�ʶ��
     * @param   sample_mask             ָ��Ŀ�����������ķ���״̬���ϵ����룻
     * @param   view_mask               ָ��Ŀ��������������ͼ״̬���ϵ����룻
     * @param   instance_mask           ָ��Ŀ����������������ʵ����ʵ��״̬���ϵ����룻
     *
     * @return  �μ� #read ���������⵱�ײ�û�� @e handle ��ʶ������ʵ����Ϣʱ������ #DDS_RETCODE_BAD_PARAMETER ��
     */

    ReturnCode_t read_instance(
        TSeq &data_values,
        SampleInfoSeq &sample_infos,
        Long max_samples,
        const InstanceHandle_t &handle,
        SampleStateMask sample_mask,
        ViewStateMask view_mask,
        InstanceStateMask instance_mask);

    /**
     * @fn  ReturnCode_t ZRDDSDataReader::take_instance( TSeq &data_values, SampleInfoSeq &sample_infos, Long max_samples, const InstanceHandle_t &handle, SampleStateMask sample_mask, ViewStateMask view_mask, InstanceStateMask instance_mask);
     *
     * @brief   ȡ��ָ������ʵ�������������������������ϡ�
     *
     * @details �÷����� #take �ӿڻ������ټ���ָ������ʵ����Ҫ��
     *
     * @param [in,out]  data_values     ���������������������ݶ����ж�ȡ���������н����
     * @param [in,out]  sample_infos    ���������������������ݶ����ж�ȡ��������Ϣ���н����
     * @param   max_samples             ָ�����β������ӵײ��ȡ������������
     * @param   handle                  ָ��Ŀ������ʵ���ı�ʶ��
     * @param   sample_mask             ָ��Ŀ�����������ķ���״̬���ϵ����룻
     * @param   view_mask               ָ��Ŀ��������������ͼ״̬���ϵ����룻
     * @param   instance_mask           ָ��Ŀ����������������ʵ����ʵ��״̬���ϵ����룻
     *
     * @return  �μ� #read ���������⵱�ײ�û�� @e handle ��ʶ������ʵ����Ϣʱ������ #DDS_RETCODE_BAD_PARAMETER ��
     */

    ReturnCode_t take_instance(
        TSeq &data_values,
        SampleInfoSeq &sample_infos,
        Long max_samples,
        const InstanceHandle_t &handle,
        SampleStateMask sample_mask,
        ViewStateMask view_mask,
        InstanceStateMask instance_mask);

    /**
     * @fn  ReturnCode_t ZRDDSDataReader::read_next_instance( TSeq &data_values, SampleInfoSeq &sample_infos, Long max_samples, const InstanceHandle_t &previous_handle, SampleStateMask sample_mask, ViewStateMask view_mask, InstanceStateMask instance_mask);
     *
     * @brief   ��ȡָ������ʵ�����棨��һ��Ϊ���ڵ�����ʵ��������ʵ�������������������������ϡ�
     *
     * @details ����ʵ����˳�������£�
     *          - ���� #DDS_HANDLE_NIL_NATIVE ����ֵ�������С������ʵ����ʼ���ҡ�
     *          - ������������������ʱ��˳�򣬼����������յ���һ������������˳��
     *          
     * @param [in,out]  data_values     ���������������������ݶ����ж�ȡ���������н����
     * @param [in,out]  sample_infos    ���������������������ݶ����ж�ȡ��������Ϣ���н����
     * @param   max_samples             ָ�����β������ӵײ��ȡ������������
     * @param   previous_handle         ָ����ǰ������ʵ����ʶ��
     * @param   sample_mask             ָ��Ŀ�����������ķ���״̬���ϵ����룻
     * @param   view_mask               ָ��Ŀ��������������ͼ״̬���ϵ����룻
     * @param   instance_mask           ָ��Ŀ����������������ʵ����ʵ��״̬���ϵ����룻
     *
     * @return  �μ� #read ������
     */

    ReturnCode_t read_next_instance(
        TSeq &data_values,
        SampleInfoSeq &sample_infos,
        Long max_samples,
        const InstanceHandle_t &previous_handle,
        SampleStateMask sample_mask,
        ViewStateMask view_mask,
        InstanceStateMask instance_mask);

    /**
     * @fn  ReturnCode_t ZRDDSDataReader::take_next_instance( TSeq &data_values, SampleInfoSeq &sample_infos, Long max_samples, const InstanceHandle_t &previous_handle, SampleStateMask sample_mask, ViewStateMask view_mask, InstanceStateMask instance_mask);
     *
     * @brief   ȡ��ָ������ʵ�����棨��һ��Ϊ���ڵ�����ʵ��������ʵ�������������������������ϡ�
     *
     * @details ����ʵ����˳�������£�
     *          - ���� #DDS_HANDLE_NIL_NATIVE ����ֵ�������С������ʵ����ʼ���ҡ�
     *          - ������������������ʱ��˳�򣬼����������յ���һ������������˳��
     *
     * @param [in,out]  data_values     ���������������������ݶ����ж�ȡ���������н����
     * @param [in,out]  sample_infos    ���������������������ݶ����ж�ȡ��������Ϣ���н����
     * @param   max_samples             ָ�����β������ӵײ��ȡ������������
     * @param   previous_handle         ָ����ǰ������ʵ����ʶ��
     * @param   sample_mask             ָ��Ŀ�����������ķ���״̬���ϵ����룻
     * @param   view_mask               ָ��Ŀ��������������ͼ״̬���ϵ����룻
     * @param   instance_mask           ָ��Ŀ����������������ʵ����ʵ��״̬���ϵ����룻
     *
     * @return  �μ� #read ������
     */

    ReturnCode_t take_next_instance(
        TSeq &data_values,
        SampleInfoSeq &sample_infos,
        Long max_samples,
        const InstanceHandle_t &previous_handle,
        SampleStateMask sample_mask,
        ViewStateMask view_mask,
        InstanceStateMask instance_mask);

#ifdef _ZRDDS_INCLUDE_READ_CONDITION

    /**
     * @fn  ReturnCode_t ZRDDSDataReader::read_next_instance_w_condition( TSeq &data_values, SampleInfoSeq &sample_infos, Long max_samples, const InstanceHandle_t &previous_handle, ReadCondition *condition);
     *
     * @brief   ��ȡָ������ʵ�����棨��һ��Ϊ���ڵ�����ʵ��������ʵ�������������������������ϡ�
     *
     * @details �÷����� #read_next_instance ������ȫ��ͬ���÷���ʹ�� #DDS::ReadCondition ����ֿ�д������״̬��
     *
     * @param [in,out]  data_values     ���������������������ݶ����ж�ȡ���������н����
     * @param [in,out]  sample_infos    ���������������������ݶ����ж�ȡ��������Ϣ���н����
     * @param   max_samples             ָ�����β������ӵײ��ȡ������������
     * @param   previous_handle         ָ����ǰ������ʵ����ʶ��
     * @param [in,out]  condition       ָ��Ŀ��״̬��
     *
     * @return  �μ� #read ������������� @e condition ��Ч�ǣ����� #DDS_RETCODE_PRECONDITION_NOT_MET ��
     */

    ReturnCode_t read_next_instance_w_condition(
        TSeq &data_values,
        SampleInfoSeq &sample_infos,
        Long max_samples,
        const InstanceHandle_t &previous_handle,
        ReadCondition *condition);

    /**
     * @fn  ReturnCode_t ZRDDSDataReader::take_next_instance_w_condition( TSeq &data_values, SampleInfoSeq &sample_infos, Long max_samples, const InstanceHandle_t &previous_handle, ReadCondition *condition);
     *
     * @brief   ȡ��ָ������ʵ�����棨��һ��Ϊ���ڵ�����ʵ��������ʵ�������������������������ϡ�
     *
     * @details �÷����� #take_next_instance ������ȫ��ͬ���÷���ʹ�� #DDS::ReadCondition ����ֿ�д������״̬��
     *
     * @param [in,out]  data_values     ���������������������ݶ����ж�ȡ���������н����
     * @param [in,out]  sample_infos    ���������������������ݶ����ж�ȡ��������Ϣ���н����
     * @param   max_samples             ָ�����β������ӵײ��ȡ������������
     * @param   previous_handle         ָ����ǰ������ʵ����ʶ��
     * @param [in,out]  condition       ָ��Ŀ��״̬��
     *
     * @return  �μ� #read ������������� @e condition ��Ч�ǣ����� #DDS_RETCODE_PRECONDITION_NOT_MET ��
     */

    ReturnCode_t take_next_instance_w_condition(
        TSeq &data_values,
        SampleInfoSeq &sample_infos,
        Long max_samples,
        const InstanceHandle_t &previous_handle,
        ReadCondition *condition);

    /**
     * @fn  ReturnCode_t ZRDDSDataReader::read_w_condition( TSeq &data_values, SampleInfoSeq &sample_infos, Long max_samples, ReadCondition *condition);
     *
     * @brief   �ýӿڴ����ݶ��ߵײ��ȡ�û��������ݡ�
     *
     * @details �÷����� #read ������ȫ��ͬ���÷���ʹ�� #DDS::ReadCondition ����ֿ�д������״̬��
     *
     * @param [in,out]  data_values     ���������������������ݶ����ж�ȡ���������н����
     * @param [in,out]  sample_infos    ���������������������ݶ����ж�ȡ��������Ϣ���н����
     * @param   max_samples             ָ�����β������ӵײ��ȡ������������
     * @param [in,out]  condition       ָ��Ŀ��״̬��
     *
     * @return  �μ� #read ������������� @e condition ��Ч�ǣ����� #DDS_RETCODE_PRECONDITION_NOT_MET ��
     */

    ReturnCode_t read_w_condition(
        TSeq &data_values,
        SampleInfoSeq &sample_infos,
        Long max_samples,
        ReadCondition *condition);

    /**
     * @fn  ReturnCode_t ZRDDSDataReader::take_w_condition( TSeq &data_values, SampleInfoSeq &sample_infos, Long max_samples, ReadCondition *condition);
     *
     * @brief   �ýӿڴ����ݶ��ߵײ�ȡ���û��������ݡ�
     *
     * @details �÷����� #take ������ȫ��ͬ���÷���ʹ�� #DDS::ReadCondition ����ֿ�д������״̬��
     *
     * @param [in,out]  data_values     ���������������������ݶ����ж�ȡ���������н����
     * @param [in,out]  sample_infos    ���������������������ݶ����ж�ȡ��������Ϣ���н����
     * @param   max_samples             ָ�����β������ӵײ��ȡ������������
     * @param [in,out]  condition       ָ��Ŀ��״̬��
     *
     * @return  �μ� #read ������������� @e condition ��Ч�ǣ����� #DDS_RETCODE_PRECONDITION_NOT_MET ��
     */

    ReturnCode_t take_w_condition(
        TSeq &data_values,
        SampleInfoSeq &sample_infos,
        Long max_samples,
        ReadCondition *condition);
#endif //_ZRDDS_INCLUDE_READ_CONDITION

    /**
     * @fn  ReturnCode_t ZRDDSDataReader::return_loan( TSeq &data_values, SampleInfoSeq &sample_infos);
     *
     * @brief   �÷�������Ӧ�ù黹�����ݶ������Ŀռ䡣
     *          
     * @details Ϊ�˼�Ӧ�õ�ʹ�ã����ݶ����ṩ������Ч�Լ�飬������Ч���� #DDS_RETCODE_PRECONDITION_NOT_MET  
     *          ���黹�ɹ������е���󳤶��Լ�������������Ϊ0��ӵ�пռ�����Ϊtrue��������Ч�԰�����
     *          - ��������������Ƿ�Ϊͨ���м������ȥ�ģ�����ǣ�����й黹����������ֱ�Ӻ��ԣ�
     *          - ��������������Ƿ������Լ�������Ϣ�Լ������Ƿ�һһ��Ӧ��
     *          - ��������������Ƿ����ڸ����ݶ��ߣ�����ǣ�������黹��
     *
     * @param [in,out]  data_values     �� #read #take ϵ�з����з��صĲ�����
     * @param [in,out]  sample_infos    �� #read #take ϵͳ�����з��صĲ�����
     *
     * @return  ��ǰ���ܵķ���ֵ���£�
     *          - #DDS_RETCODE_OK :��ʾ�ɹ���
     *          - #DDS_RETCODE_PRECONDITION_NOT_MET :��ʾ����Ĳ���������������
     */

    ReturnCode_t return_loan(
        TSeq &data_values,
        SampleInfoSeq &sample_infos);

    ReturnCode_t return_recv_buffer(
        SampleInfo &sample_info);

    ReturnCode_t loan_recv_buffer(
        SampleInfo &sample_info);
    /**
     * @fn  ReturnCode_t ZRDDSDataReader::get_key_value( T &key_holder, const InstanceHandle_t &handle);
     *
     * @brief   ͨ������ʵ����Ψһ��ʶ��ȡ����ʵ���ļ�ֵ��
     *
     * @param [in,out]  key_holder  ���ڲ��������ڱ�������ʵ���ļ�ֵ��ע�Ȿ��������������Ա����
     * @param   handle              �����Ψһ��ʶ��
     *
     * @return  ��ǰ���ܵķ���ֵ���£�
     *          - #DDS_RETCODE_OK :��ʾ�ɹ���
     *          - #DDS_RETCODE_BAD_PARAMETER :��ʾ�ײ�û��ָ��������ʵ����Ϣ��
     */

    ReturnCode_t get_key_value(
        T &key_holder,
        const InstanceHandle_t &handle);

    /**
     * @fn  InstanceHandle_t ZRDDSDataReader::lookup_instance(T& instance);
     *
     * @brief   ͨ������ʵ����ֵ������Ӧ�ı�ʶ��
     *
     * @param [in,out]  instance    ��������ʵ��������������
     *
     * @return  ��ǰ���ܵķ���ֵ���£�
     *          - ��Ч�ı�ʶ �� DDS_InstanceHandle_t::valid �� ��ʾ��ȡ�ɹ���
     *          - #DDS_HANDLE_NIL_NATIVE :��ʾ�ײ�û��ָ������ʵ������Ϣ�����߹�������������δ�����ֵ��
     */

    InstanceHandle_t lookup_instance(T& instance);

    static ZRDDSDataReader* createI(DataReader* impl, void* typesupport);

    static ReturnCode_t destroyI(ZRDDSDataReader *dr, void* typesupport);

protected:
    ZRDDSDataReader(DataReader* impl);

    ~ZRDDSDataReader();
private:
    ReturnCode_t readOrTake(TSeq &data_values, DataReaderReadOrTakeParams& params);
};

template<typename T, typename TSeq>
ReturnCode_t ZRDDSDataReader<T, TSeq>::readOrTake(
    TSeq &dataValues,
    DataReaderReadOrTakeParams& params)
{
    ReturnCode_t result = DDS_RETCODE_OK;
    params.isLoan = false;
    params.dataPtrArray = NULL;
    params.dataCount = 0;
    params.dataSeqLen = dataValues.length();
    params.dataSeqMaxLen = dataValues.maximum();
    params.dataSeq_has_ownership = dataValues.has_ownership();
    params.dataSeqBuffer= (ZR_INT8*)dataValues.get_contiguous_buffer();
    params.dataSize = sizeof(T);
    params.dataSeqBufferType = 0;

    result = this->m_cppImpl->read_or_take_untype(params);
    if (result == DDS_RETCODE_NO_DATA)
    {
        dataValues.length(0);
        params.sampleInfos->length(0);
        return result;
    }

    if (result != DDS_RETCODE_OK)
    {
        return result;
    }

    if (params.isLoan)
    {
        if (!dataValues.loan_discontiguous((T**)params.dataPtrArray, params.dataCount, params.dataCount))
        {
            result = DDS_RETCODE_ERROR;
            this->m_cppImpl->return_loan_untype(params.dataPtrArray, params.dataCount, params.sampleInfos);
        }
    }
    else
    {
        if (!dataValues.length(params.dataCount))
        {
            result = DDS_RETCODE_ERROR;
        }
        if (!params.sampleInfos->length(params.dataCount))
        {
            result = DDS_RETCODE_ERROR;
        }
    }
    return result;
}

template<typename T, typename TSeq>
ReturnCode_t ZRDDSDataReader<T, TSeq>::read(
    TSeq &data_values,
    SampleInfoSeq &sample_infos,
    Long max_samples,
    SampleStateMask sample_mask,
    ViewStateMask view_mask,
    InstanceStateMask instance_mask)
{
    DataReaderReadOrTakeParams params;
    params.sampleInfos = &sample_infos;
    params.maxSamples = max_samples;
    params.handle = NULL;
    params.sampleMask = sample_mask;
    params.viewMask = view_mask;
    params.instanceMask = instance_mask;
    params.isTake = false;
    params.isNext = false;
    params.userCondition = NULL;
    return this->readOrTake(data_values, params);
}

template<typename T, typename TSeq>
ReturnCode_t ZRDDSDataReader<T, TSeq>::take(
    TSeq &data_values,
    SampleInfoSeq &sample_infos,
    Long max_samples,
    SampleStateMask sample_mask,
    ViewStateMask view_mask,
    InstanceStateMask instance_mask)
{
    DataReaderReadOrTakeParams params;
    params.sampleInfos = &sample_infos;
    params.maxSamples = max_samples;
    params.handle = NULL;
    params.sampleMask = sample_mask;
    params.viewMask = view_mask;
    params.instanceMask = instance_mask;
    params.isTake = true;
    params.isNext = false;
    params.userCondition = NULL;
    return this->readOrTake(data_values, params);
}

template<typename T, typename TSeq>
ReturnCode_t ZRDDSDataReader<T, TSeq>::read_next_sample(
    T &data_value,
    SampleInfo &sample_info)
{
    return this->m_cppImpl->read_or_take_next_sample_untype(
        (ZR_INT8*)&data_value,
        &sample_info,
        false);
}

template<typename T, typename TSeq>
ReturnCode_t ZRDDSDataReader<T, TSeq>::take_next_sample(
    T &data_value,
    SampleInfo &sample_info)
{
    return this->m_cppImpl->read_or_take_next_sample_untype(
        (ZR_INT8*)&data_value,
        &sample_info,
        true);
}

template<typename T, typename TSeq>
ReturnCode_t ZRDDSDataReader<T, TSeq>::read_instance(
    TSeq &data_values,
    SampleInfoSeq &sample_infos,
    Long max_samples,
    const InstanceHandle_t &handle,
    SampleStateMask sample_mask,
    ViewStateMask view_mask,
    InstanceStateMask instance_mask)
{
    DataReaderReadOrTakeParams params;
    params.sampleInfos = &sample_infos;
    params.maxSamples = max_samples;
    params.handle = &handle;
    params.sampleMask = sample_mask;
    params.viewMask = view_mask;
    params.instanceMask = instance_mask;
    params.isTake = false;
    params.isNext = false;
    params.userCondition = NULL;
    return this->readOrTake(data_values, params);
}

template<typename T, typename TSeq>
ReturnCode_t ZRDDSDataReader<T, TSeq>::take_instance(
    TSeq &data_values,
    SampleInfoSeq &sample_infos,
    Long max_samples,
    const InstanceHandle_t &handle,
    SampleStateMask sample_mask,
    ViewStateMask view_mask,
    InstanceStateMask instance_mask)
{
    DataReaderReadOrTakeParams params;
    params.sampleInfos = &sample_infos;
    params.maxSamples = max_samples;
    params.handle = &handle;
    params.sampleMask = sample_mask;
    params.viewMask = view_mask;
    params.instanceMask = instance_mask;
    params.isTake = true;
    params.isNext = false;
    params.userCondition = NULL;
    return this->readOrTake(data_values, params);
}

template<typename T, typename TSeq>
ReturnCode_t ZRDDSDataReader<T, TSeq>::read_next_instance(
    TSeq &data_values,
    SampleInfoSeq &sample_infos,
    Long max_samples,
    const InstanceHandle_t &previous_handle,
    SampleStateMask sample_mask,
    ViewStateMask view_mask,
    InstanceStateMask instance_mask)
{
    DataReaderReadOrTakeParams params;
    params.sampleInfos = &sample_infos;
    params.maxSamples = max_samples;
    params.handle = &previous_handle;
    params.sampleMask = sample_mask;
    params.viewMask = view_mask;
    params.instanceMask = instance_mask;
    params.isTake = false;
    params.isNext = true;
    params.userCondition = NULL;
    return this->readOrTake(data_values, params);
}

template<typename T, typename TSeq>
ReturnCode_t ZRDDSDataReader<T, TSeq>::take_next_instance(
    TSeq &data_values,
    SampleInfoSeq &sample_infos,
    Long max_samples,
    const InstanceHandle_t &previous_handle,
    SampleStateMask sample_mask,
    ViewStateMask view_mask,
    InstanceStateMask instance_mask)
{
    DataReaderReadOrTakeParams params;
    params.sampleInfos = &sample_infos;
    params.maxSamples = max_samples;
    params.handle = &previous_handle;
    params.sampleMask = sample_mask;
    params.viewMask = view_mask;
    params.instanceMask = instance_mask;
    params.isTake = true;
    params.isNext = true;
    params.userCondition = NULL;
    return this->readOrTake(data_values, params);
}

#ifdef _ZRDDS_INCLUDE_READ_CONDITION
template<typename T, typename TSeq>
ReturnCode_t ZRDDSDataReader<T, TSeq>::read_next_instance_w_condition(
    TSeq &data_values,
    SampleInfoSeq &sample_infos,
    Long max_samples,
    const InstanceHandle_t &previous_handle,
    ReadCondition *condition)
{
    DataReaderReadOrTakeParams params;
    params.sampleInfos = &sample_infos;
    params.maxSamples = max_samples;
    params.handle = &previous_handle;
    params.isTake = false;
    params.isNext = true;
    params.userCondition = condition;
    return this->readOrTake(data_values, params);
}

template<typename T, typename TSeq>
ReturnCode_t ZRDDSDataReader<T, TSeq>::take_next_instance_w_condition(
    TSeq &data_values,
    SampleInfoSeq &sample_infos,
    Long max_samples,
    const InstanceHandle_t &previous_handle,
    ReadCondition *condition)
{
    DataReaderReadOrTakeParams params;
    params.sampleInfos = &sample_infos;
    params.maxSamples = max_samples;
    params.handle = &previous_handle;
    params.isTake = true;
    params.isNext = true;
    params.userCondition = condition;
    return this->readOrTake(data_values, params);
}

template<typename T, typename TSeq>
ReturnCode_t ZRDDSDataReader<T, TSeq>::read_w_condition(
    TSeq &data_values,
    SampleInfoSeq &sample_infos,
    Long max_samples,
    ReadCondition *condition)
{
    DataReaderReadOrTakeParams params;
    params.sampleInfos = &sample_infos;
    params.maxSamples = max_samples;
    params.handle = NULL;
    params.isTake = false;
    params.isNext = false;
    params.userCondition = condition;
    return this->readOrTake(data_values, params);
}

template<typename T, typename TSeq>
ReturnCode_t ZRDDSDataReader<T, TSeq>::take_w_condition(
    TSeq &data_values,
    SampleInfoSeq &sample_infos,
    Long max_samples,
    ReadCondition *condition)
{
    DataReaderReadOrTakeParams params;
    params.sampleInfos = &sample_infos;
    params.maxSamples = max_samples;
    params.handle = NULL;
    params.isTake = true;
    params.isNext = false;
    params.userCondition = condition;
    return this->readOrTake(data_values, params);
}
#endif //_ZRDDS_INCLUDE_READ_CONDITION

template<typename T, typename TSeq>
ReturnCode_t ZRDDSDataReader<T, TSeq>::return_loan(
    TSeq &data_values,
    SampleInfoSeq &sample_infos)
{
    ReturnCode_t result = DDS_RETCODE_OK;
    if (data_values.has_ownership() &&
        sample_infos.has_ownership())
    {
        return result;
    }

    Long dataSeqMaxLen = data_values.maximum();
    T **dataSeqDiscontiguousBuffer = data_values.get_discontiguous_buffer();
    result = this->m_cppImpl->return_loan_untype(
        (void**)dataSeqDiscontiguousBuffer, dataSeqMaxLen, &sample_infos);
    if (result != DDS_RETCODE_OK)
    {
        return result;
    }
    if (!data_values.unloan())
    {
        result = DDS_RETCODE_ERROR;
        return result;
    }
    if (!sample_infos.unloan())
    {
        return DDS_RETCODE_ERROR;
    }
    return result;
}

template<typename T, typename TSeq>
ReturnCode_t ZRDDSDataReader<T, TSeq>::return_recv_buffer(
    SampleInfo &sample_info)
{
    return this->m_cppImpl->return_recv_buffer_untype(
        &sample_info);
}

template<typename T, typename TSeq>
ReturnCode_t ZRDDSDataReader<T, TSeq>::loan_recv_buffer(
    SampleInfo &sample_info)
{
    return this->m_cppImpl->loan_recv_buffer_untype(
        &sample_info);
}

template<typename T, typename TSeq>
ReturnCode_t ZRDDSDataReader<T, TSeq>::get_key_value(
    T &key_holder,
    const InstanceHandle_t &handle)
{
    return this->m_cppImpl->get_key_value_untype(
        (void*)&key_holder,
        &handle);
}

template<typename T, typename TSeq>
InstanceHandle_t ZRDDSDataReader<T, TSeq>::lookup_instance(T& instance)
{
    return this->m_cppImpl->lookup_instance_untype((void*)&instance);
}

template<typename T, typename TSeq>
ZRDDSDataReader<T, TSeq>* ZRDDSDataReader<T, TSeq>::createI(DataReader* impl, void* typesupport)
{
    return new ZRDDSDataReader<T, TSeq>(impl);
}

template<typename T, typename TSeq>
ReturnCode_t ZRDDSDataReader<T, TSeq>::destroyI(ZRDDSDataReader<T, TSeq> *dr, void* typesupport)
{
    if (NULL != dr) delete dr;
    return DDS_RETCODE_OK;
}

template<typename T, typename TSeq>
ZRDDSDataReader<T, TSeq>::ZRDDSDataReader(DataReader* impl)
    :DataReader(impl)
{
}

template<typename T, typename TSeq>
ZRDDSDataReader<T, TSeq>::~ZRDDSDataReader() {}

} // namespace DDS

#endif // ZRDDSDataReader_h__
