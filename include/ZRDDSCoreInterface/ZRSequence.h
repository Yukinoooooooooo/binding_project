/**
 * @file:       ZRSequence.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#ifndef ZRSequence_h__
#define ZRSequence_h__

#include "ZRDDSCommon.h"
#include "OsResource.h"
#include "ZRMemPool.h"

#define DDS_INITIALIZE_NUMBER 0xCDEFAB

#define DDS_SEQUENCE_INITIALIZER \
    {true, NULL, NULL, 0, 0, DDS_INITIALIZE_NUMBER, NULL, NULL}

#ifdef _ZRDDS_INCLUDE_DR_NO_SERIALIZE_MODE
#define DDS_SEQUENCE_NO_SERIALIZE_MEMBERS(T)                            \
    /** @brief   �ֶ��������飬Ԥ����64���ֶ� */                           \
    T* _fixedFragments[64];                                             \
    /** @brief   �ֶ��������飬�ֶ�������64���ֶεĴ洢λ�� */              \
    T** _variousFragments;                                              \
    /** @brief   �ֶ����������ͷָ�룬�ڻ��տռ�ʱʹ�� */                  \
    T* _fixedHeader[64];                                                \
    /** @brief   �ֶ����������ͷָ�룬�ֶ�������64��ʱ�洢 */              \
    T** _variousHeader;                                                 \
    /** @brief   �ֶ���������������*/                                     \
    ZR_UINT32 _fragmentNum;                                             \
    /** @brief   �ֶγ��ȣ����׸��Լ����һ���ֶ��⣬���зֶ�һ����*/        \
    ZR_UINT32 _fragmentSize;                                            \
    /** @brief   �׸��ֶεĳ��ȡ� */                                      \
    ZR_UINT32 _firstFragSize;                                           \
    /** @brief   ���һ���ֶεĳ��ȡ� */                                  \
    ZR_UINT32 _lastFragSize;
#else
#define DDS_SEQUENCE_NO_SERIALIZE_MEMBERS(T)
#endif //_ZRDDS_INCLUDE_DR_NO_SERIALIZE_MODE


#define DDS_SEQUENCE_MEMBERS(T)                                         \
    /** @brief   �Ƿ�ӵ�д洢�ռ䡣 */                                  \
    DDS_Boolean _owned;                                                 \
    /** @brief   Ԫ�ص������ڴ�洢�ռ䡣 */                            \
    T* _contiguousBuffer;                                               \
    /** @brief   Ԫ�صķ������ڴ�ռ䣬�洢Ԫ�ص�ָ�����顣 */          \
    T** _discontiguousBuffer;                                           \
    /** @brief   sequence��������*/                                     \
    DDS_ULong _maximum;                                                 \
    /** @brief   sequence��ǰ��Ԫ�ظ����� */                            \
    DDS_ULong _length;                                                  \
    /** @brief   ������sequence�Ƿ񱻳�ʼ���� */                        \
    DDS_Long _sequenceInit;                                             \
    /** @brief   ���ռ���Դ��DataReader��ָ�롣 */                    \
    void* _readerPtr;                                                   \
    /** @brief   ���ռ���Դ������ָ�롣 */                            \
    void* _dataPtr;                                                     \
    /** @brief   ����ռ���ڴ�ء� */                                  \
    ZRMemPool* _mempool;                                                \
    /** @brief   ��ʼ��ԭʼʱ�Ƿ����ռ䡣*/                           \
    DDS_Boolean _allocMemory;                                           \
    DDS_SEQUENCE_NO_SERIALIZE_MEMBERS(T)
    

#define DDS_SEQUENCE_METHODS(TSeq, T)                                                                       \
    DCPSDLL                                                                                                 \
    DDS_Boolean TSeq##_is_initialized(const struct TSeq *self);                                             \
    DCPSDLL                                                                                                 \
    DDS_Boolean TSeq##_set(struct TSeq *self, DDS_ULong index, const T *newValue);                          \
    DCPSDLL                                                                                                 \
    void TSeq##_initialize(struct TSeq *self);                                                              \
    DCPSDLL                                                                                                 \
    struct TSeq *TSeq##_new(DDS_ULong newMax);                                                              \
    DCPSDLL                                                                                                 \
    DDS_ULong TSeq##_get_maximum(const struct TSeq *self);                                                  \
    DCPSDLL                                                                                                 \
    DDS_Boolean TSeq##_set_maximum(struct TSeq *self, DDS_ULong newMax);                                    \
    DCPSDLL                                                                                                 \
    DDS_ULong TSeq##_get_length(const struct TSeq *self);                                                   \
    DCPSDLL                                                                                                 \
    DDS_Boolean TSeq##_set_length(struct TSeq *self, DDS_ULong newLength);                                  \
    DCPSDLL                                                                                                 \
    DDS_Boolean TSeq##_ensure_length(struct TSeq *self, DDS_ULong length, DDS_ULong max);                   \
    DCPSDLL                                                                                                 \
    T* TSeq##_get_reference(const struct TSeq *self, DDS_ULong index);                                      \
    DCPSDLL                                                                                                 \
    DDS_Boolean TSeq##_append(struct TSeq *self, const T *newValue);                                        \
    DCPSDLL                                                                                                 \
    DDS_Boolean TSeq##_append_autosize(struct TSeq *self, const T *newValue);                               \
    DCPSDLL                                                                                                 \
    DDS_Boolean TSeq##_copy_no_alloc(struct TSeq *self, const struct TSeq *src);                            \
    DCPSDLL                                                                                                 \
    struct TSeq* TSeq##_copy(struct TSeq *self, const struct TSeq *src);                                    \
    DCPSDLL                                                                                                 \
    DDS_Long TSeq##_compare(const struct TSeq *self, const struct TSeq *src);                               \
    DCPSDLL                                                                                                 \
    DDS_Boolean TSeq##_from_array(struct TSeq *self, const T* const srcArray, DDS_ULong length);            \
    DCPSDLL                                                                                                 \
    DDS_Boolean TSeq##_to_array(const struct TSeq *self, T* dstArray, DDS_ULong length);                    \
    DCPSDLL                                                                                                 \
    DDS_Boolean TSeq##_loan_contiguous(struct TSeq *self, T *buffer, DDS_ULong newLength, DDS_ULong newMax);\
    DCPSDLL                                                                                                 \
    DDS_Boolean TSeq##_loan_discontiguous(struct TSeq *self, T **buffer, DDS_ULong newLength, DDS_ULong newMax); \
    DCPSDLL                                                                                                 \
    DDS_Boolean TSeq##_unloan(struct TSeq *self);                                                           \
    DCPSDLL                                                                                                 \
    T* TSeq##_get_contiguous_buffer(const struct TSeq *self);                                               \
    DCPSDLL                                                                                                 \
    T** TSeq##_get_discontiguous_buffer(const struct TSeq *self);                                           \
    DCPSDLL                                                                                                 \
    void TSeq##_get_reader_and_data_ptr(const struct TSeq *self, void **readerPtr, void **dataPtr);         \
    DCPSDLL                                                                                                 \
    void TSeq##_set_reader_and_data_ptr(struct TSeq *self, void *readerPtr, void *dataPtr);                 \
    DCPSDLL                                                                                                 \
    DDS_Boolean TSeq##_has_ownership(const struct TSeq *self);                                              \
    DCPSDLL                                                                                                 \
    DDS_Boolean TSeq##_clear(struct TSeq *self);                                                            \
    DCPSDLL                                                                                                 \
    DDS_Boolean TSeq##_finalize(struct TSeq *self);                                                         \
    DCPSDLL                                                                                                 \
    void TSeq##_shallow_copy(struct TSeq *self, struct TSeq *other);                                        \
    DCPSDLL                                                                                                 \
    void TSeq##_initialize_ex(struct TSeq *self, ZRMemPool* mempool, DDS_Boolean allocateMemory)

#ifdef _ZRDDSCPPINTERFACE
#define DDS_SEQUENCE_MEMBER_METHODS(TSeq, T)            \
                                                        \
    /**
     * @fn  explicit TSeq(DDS_ULong max = 0);
     *
     * @brief   ���캯����Ĭ�Ϲ�������Ϊ0��Sequence��
     *
     * @param   max ָ��Sequence������
     */                                                 \
                                                        \
    explicit TSeq(DDS_ULong max = 0);                   \
                                                        \
    /**
     * @fn  TSeq(const struct TSeq& seq);
     *
     * @brief   �������캯����
     *
     * @param   seq ԴSequence��
     */                                                 \
                                                        \
    TSeq(const struct TSeq& seq);                       \
                                                        \
    /**
     * @fn  ~TSeq();
     *
     * @brief   ����������
     */                                                 \
                                                        \
    ~TSeq();                                            \
    const T& operator[](DDS_ULong i) const;             \
    T& operator[](DDS_ULong i);                         \
    DDS_Boolean append(const T& val);                   \
    DDS_Boolean append_autosize(const T& val);         \
    DDS_ULong maximum() const;                          \
    DDS_Boolean maximum(DDS_ULong new_max);             \
    DDS_ULong length() const;                           \
    DDS_Boolean clear();                                \
    DDS_Boolean length(DDS_ULong new_length);           \
    DDS_Boolean unloan();                               \
    T* get_contiguous_buffer() const;                   \
    T** get_discontiguous_buffer() const;               \
    DDS_Boolean set_at(DDS_ULong i, const T &val);      \
    const T& get_at(DDS_ULong i) const;                 \
    DDS_Boolean ensure_length(DDS_ULong length, DDS_ULong max);  \
    DDS_Boolean has_ownership() const;                           \
    DDS_Boolean copy_no_alloc(const struct TSeq& src_seq);       \
    DDS_Long compare(const struct TSeq& compared_seq) const ;    \
    DDS_Boolean from_array(const T array[], DDS_ULong length);   \
    DDS_Boolean to_array(T array[], DDS_ULong length) const ;    \
    DDS_Boolean loan_contiguous(T* buffer, DDS_ULong new_length, DDS_ULong new_max);     \
    DDS_Boolean loan_discontiguous(T** buffer, DDS_ULong new_length, DDS_ULong new_max);
#else
#define DDS_SEQUENCE_MEMBER_METHODS(TSeq, T)
#endif

#ifdef __cplusplus
#define DDS_SEQUENCE_OPERATOR_ASSIGN(TSeq)  \
    TSeq& operator=(const TSeq& right);
#else
#define DDS_SEQUENCE_OPERATOR_ASSIGN(TSeq)
#endif

#define DDS_USER_SEQUENCE_METHODS(TSeq, T)                                                                  \
    DDS_Boolean TSeq##_is_initialized(const struct TSeq *self);                                             \
    DDS_Boolean TSeq##_set(struct TSeq *self, DDS_ULong index, const T *newValue);                          \
    void TSeq##_initialize(struct TSeq *self);                                                              \
    struct TSeq *TSeq##_new(DDS_ULong newMax);                                                              \
    DDS_ULong TSeq##_get_maximum(const struct TSeq *self);                                                  \
    DDS_Boolean TSeq##_set_maximum(struct TSeq *self, DDS_ULong newMax);                                    \
    DDS_ULong TSeq##_get_length(const struct TSeq *self);                                                   \
    DDS_Boolean TSeq##_set_length(struct TSeq *self, DDS_ULong newLength);                                  \
    DDS_Boolean TSeq##_ensure_length(struct TSeq *self, DDS_ULong length, DDS_ULong max);                   \
    T* TSeq##_get_reference(const struct TSeq *self, DDS_ULong index);                                      \
    DDS_Boolean TSeq##_append(struct TSeq *self, const T *newValue);                                        \
    DDS_Boolean TSeq##_append_autosize(struct TSeq *self, const T *newValue);                              \
    DDS_Boolean TSeq##_copy_no_alloc(struct TSeq *self, const struct TSeq *src);                            \
    struct TSeq* TSeq##_copy(struct TSeq *self, const struct TSeq *src);                                    \
    DDS_Long TSeq##_compare(const struct TSeq *self, const struct TSeq *src);                               \
    DDS_Boolean TSeq##_from_array(struct TSeq *self, const T* array, DDS_ULong length);                     \
    DDS_Boolean TSeq##_to_array(const struct TSeq *self, T* array, DDS_ULong length);                       \
    DDS_Boolean TSeq##_loan_contiguous(struct TSeq *self, T *buffer, DDS_ULong newLength, DDS_ULong newMax);\
    DDS_Boolean TSeq##_loan_discontiguous(struct TSeq *self, T **buffer, DDS_ULong newLength, DDS_ULong newMax); \
    DDS_Boolean TSeq##_unloan(struct TSeq *self);                                                           \
    T* TSeq##_get_contiguous_buffer(const struct TSeq *self);                                               \
    T** TSeq##_get_discontiguous_buffer(const struct TSeq *self);                                           \
    void TSeq##_get_reader_and_data_ptr(const struct TSeq *self, void **readerPtr, void **dataPtr);         \
    void TSeq##_set_reader_and_data_ptr(struct TSeq *self, void *readerPtr, void *dataPtr);                 \
    DDS_Boolean TSeq##_has_ownership(const struct TSeq *self);                                              \
    DDS_Boolean TSeq##_clear(struct TSeq *self);                                                            \
    DDS_Boolean TSeq##_finalize(struct TSeq *self);                                                         \
    void TSeq##_initialize_ex(struct TSeq *self, ZRMemPool* mempool, DDS_Boolean allocateMemory)

#define DDS_SEQUENCE_CPP(TSeq, T)           \
typedef struct DCPSDLL TSeq {               \
    DDS_SEQUENCE_MEMBERS(T)                 \
    DDS_SEQUENCE_MEMBER_METHODS(TSeq, T)    \
    DDS_SEQUENCE_OPERATOR_ASSIGN(TSeq)      \
}TSeq;                                      \
DDS_SEQUENCE_METHODS(TSeq, T)

#define DDS_SEQUENCE_C(TSeq, T)             \
typedef struct DCPSDLL TSeq {               \
    DDS_SEQUENCE_MEMBERS(T)                 \
    DDS_SEQUENCE_OPERATOR_ASSIGN(TSeq)      \
}TSeq;                                      \
DDS_SEQUENCE_METHODS(TSeq, T)

#define DDS_SEQUENCE_C_NO_ASSIGN(TSeq, T)   \
typedef struct DCPSDLL TSeq {               \
    DDS_SEQUENCE_MEMBERS(T)                 \
}TSeq;                                      \
DDS_SEQUENCE_METHODS(TSeq, T)

/**
 * @def DDS_USER_SEQUENCE_CPP(TSeq, T) typedef struct TSeq
 *
 * @ingroup CoreSeqStruct
 *
 * @brief   �궨��ʵ��C++����ģ�壬�ú���������T���͵���������TSeq����֧�ַ���������μ�@ref CoreSeqFunction ��
 *
 * @param   TSeq    �������������ơ�
 * @param   T       ����Ԫ�����͡�
 */

#define DDS_USER_SEQUENCE_CPP(TSeq, T)      \
typedef struct TSeq {                       \
    DDS_SEQUENCE_MEMBERS(T)                 \
    DDS_SEQUENCE_MEMBER_METHODS(TSeq, T)    \
    DDS_SEQUENCE_OPERATOR_ASSIGN(TSeq)      \
}TSeq;                                      \
DDS_USER_SEQUENCE_METHODS(TSeq, T)

/**
 * @def DDS_USER_SEQUENCE_C(TSeq, T) typedef struct TSeq
 *
 * @ingroup CoreSeqStruct
 *
 * @brief   �궨��ʵ��C����ģ�壬�ú���������T���͵���������TSeq����֧�ַ���������μ�@ref CoreSeqFunction ��
 *
 * @param   TSeq    �������������ơ�
 * @param   T       ����Ԫ�����͡�
 */

#define DDS_USER_SEQUENCE_C(TSeq, T)        \
typedef struct TSeq {                       \
    DDS_SEQUENCE_MEMBERS(T)                 \
    DDS_SEQUENCE_OPERATOR_ASSIGN(TSeq)      \
}TSeq;                                      \
DDS_USER_SEQUENCE_METHODS(TSeq, T)

#endif /*ZRSequence_h__*/
