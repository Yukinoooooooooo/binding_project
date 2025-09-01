#ifndef DataReaderReadOrTakeParams_h__
#define DataReaderReadOrTakeParams_h__

typedef struct DataReaderReadOrTakeParams
{
    ZR_BOOLEAN isLoan;
    void** dataPtrArray;
    ZR_UINT32 dataCount;
    DDS_SampleInfoSeq* sampleInfos;
    ZR_INT32 dataSeqLen;
    ZR_INT32 dataSeqMaxLen;
    ZR_BOOLEAN dataSeq_has_ownership;
    ZR_INT8* dataSeqBuffer;
    ZR_UINT32 dataSize;
    /**   
     * @brief   C/C++�е�dataSeqBufferΪ�����ڴ棬����Java�Ȳ���¶�ڴ��������dataSeqBuffer����Ϊ�������ڴ棬
     *          �����Ҫ�˳�Ա���֣�0��ʾ�����ڴ棬1��ʾ�������ڴ档 
     */
    ZR_UINT32 dataSeqBufferType;
    ZR_INT32 maxSamples;
    const DDS_InstanceHandle_t* handle;
    ZR_BOOLEAN isNext;
    DDS_SampleStateMask sampleMask;
    DDS_ViewStateMask viewMask;
    DDS_InstanceStateMask instanceMask;
    ZR_BOOLEAN isTake;
    void* userCondition;
    void* readCondition;
}DataReaderReadOrTakeParams;

#endif // DataReaderReadOrTakeParams_h__
