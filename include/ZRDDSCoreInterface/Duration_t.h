/**
 * @file:       Duration_t.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#if !defined(_DURATION_T_H)
#define _DURATION_T_H

#include "ZRDDSCommon.h"
#include "OsResource.h"

#define DDS_MILLISEC_PER_SEC    1000
#define DDS_MICROSEC_PER_SEC    1000000
#define DDS_NANOSEC_PER_SEC     1000000000

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * ������Duration_tֵ
 */
DCPSDLL extern const DDS_Long DDS_DURATION_INFINITE_SEC;	/* ������ */
DCPSDLL extern const DDS_Long DDS_DURATION_ZERO_SEC;	/* 0�� */
DCPSDLL extern const DDS_ULong DDS_DURATION_INFINITE_NSEC;/* �������� */
DCPSDLL extern const DDS_ULong DDS_DURATION_ZERO_NSEC;	/* 0���� */

/**
 * @struct  DDS_Duration_t
 *
 * @ingroup CoreBaseStruct
 *
 * @brief   ��������һ��ʱ��Σ�Э��涨�����к�΢��ķֱ��ʡ�
 *
 * @details  ZRDDS�ĵ�ʵ��ֻ��ȷ���˺��룬Windows/linuxʱ����clock��ȡ��vxworksʱ����time��ȡ����ȷ���롣
 */

typedef struct DCPSDLL DDS_Duration_t
{
    /** @brief	���ֵ. */
    DDS_Long sec;
    /** @brief	��΢���ֵ. */
    DDS_ULong nanosec;
#ifdef _ZRDDSCPPINTERFACE
    DDS_Boolean operator==(const DDS_Duration_t& duration) const;
    DDS_Boolean operator<(const DDS_Duration_t& duration) const;
    DDS_Boolean operator<=(const DDS_Duration_t& duration) const;
    DDS_Boolean operator>(const DDS_Duration_t& duration) const;
    DDS_Boolean operator>=(const DDS_Duration_t& duration) const;
    DDS_Duration_t operator+(const DDS_Duration_t& duration) const;
    DDS_Duration_t operator-(const DDS_Duration_t& duration) const;
#endif
}DDS_Duration_t;

/**
 * @fn  DCPSDLL DDS_Duration_t DurationAdd(const DDS_Duration_t* self, const DDS_Duration_t* right);
 *
 * @ingroup CoreBaseFunction
 *
 * @brief   ���� DDS_Duration_t ��ӷ���һ���µĽ����
 *
 * @param   self    �������
 * @param   right   �Ҽ�����
 *
 * @return  ���صĽ����
 */

DCPSDLL DDS_Duration_t DurationAdd(const DDS_Duration_t* self, const DDS_Duration_t* right);

/**
 * @fn  void DurationAddAssign(Duration_t* self, const Duration_t* right);
 *
 * @ingroup CoreBaseFunction
 *
 * @brief   DDS_Duration_t �ӵ��ڲ�����
 *
 * @param [in,out]  self    ������
 * @param   right           ��������
 */


DCPSDLL DDS_Duration_t DurationSub(const DDS_Duration_t* self, const DDS_Duration_t* subtractor);

/**
 * @fn  DCPSDLL DDS_Long DurationCompare(const DDS_Duration_t* const self, const DDS_Duration_t* const right);
 *
 * @ingroup  CoreFunction
 *
 * @brief   DDS_Duration_t ��С�ں�����
 *
 * @param   self    ָ����ߵĲ�������
 * @param   right   ָ���ұߵĲ�������
 *
 * @return  - 0��ʾ��������ֵ���
 *          - ����0��ʾ��߶�������ұ߶����С  
 *          - С��0��ʾ��߶���С���ұ߶����С
 */

DCPSDLL DDS_Long DurationCompare(const DDS_Duration_t* const self,
    const DDS_Duration_t* const right);

/**
 * @fn  DCPSDLL DDS_ULongLong DurationGetMicrosec(const DDS_Duration_t* const self);
 *
 * @ingroup  CoreFunction
 *
 * @brief   ��ȡ�ȼ۵�΢������
 *
 * @param   self    ת��Ŀ�ꡣ
 *
 * @return  ����Ľ����
 */

DCPSDLL DDS_ULongLong DurationGetMicrosec(const DDS_Duration_t* const self);

/**
 * @fn  DCPSDLL DDS_ULongLong DurationGetMillisec(const DDS_Duration_t* const self);
 *
 * @ingroup  CoreFunction
 *
 * @brief   ��ȡ�ȼ۵ĺ�������
 *
 * @param   self    ת��Ŀ�ꡣ
 *
 * @return  ����Ľ����
 */

DCPSDLL DDS_ULongLong DurationGetMillisec(const DDS_Duration_t* const self);

/**
 * @fn  DCPSDLL DDS_Duration_t DurationFromSec(DDS_ULong seconds);
 *
 * @ingroup CoreBaseFunction
 *
 * @brief   ������ת��Ϊ�ȼ۵� DDS_Duration_t ��
 *
 * @param   seconds ������
 *
 * @return  ��seconds��ȵ� DDS_Duration_t ʱ��Ρ�
 */

DCPSDLL DDS_Duration_t DurationFromSec(DDS_ULong seconds);

/**
 * @fn  DCPSDLL DDS_Duration_t DurationFromMillis(DDS_ULong milliseconds);
 *
 * @ingroup CoreBaseFunction
 *
 * @brief   �Ӻ�����ת��Ϊ�ȼ۵� DDS_Duration_t ��
 *
 * @param   milliseconds ��������
 *
 * @return  ��milliseconds��ȵ� DDS_Duration_t ʱ��Ρ�
 */

DCPSDLL DDS_Duration_t DurationFromMillis(DDS_ULong milliseconds);

/**
 * @fn  DCPSDLL DDS_Duration_t DurationFromMicros(DDS_ULong microseconds);
 *
 * @ingroup CoreBaseFunction
 *
 * @brief   ��΢����ת��Ϊ�ȼ۵� DDS_Duration_t ��
 *
 * @param   microseconds ��������
 *
 * @return  ��microseconds��ȵ� DDS_Duration_t ʱ��Ρ�
 */

DCPSDLL DDS_Duration_t DurationFromMicros(DDS_ULong microseconds);


/**
 * @fn  DCPSDLL DDS_Duration_t DurationFromNanos(DDS_ULong nanoseconds);
 *
 * @ingroup CoreBaseFunction
 *
 * @brief   ��������ת��Ϊ�ȼ۵� DDS_Duration_t ��
 *
 * @param   nanoseconds ��������
 *
 * @return  ��nanoseconds��ȵ� DDS_Duration_t ʱ��Ρ�
 */
DCPSDLL DDS_Duration_t DurationFromNanos(DDS_ULong nanoseconds);

/* Э���õ���һЩDuration_t��Ĭ��ֵ */
/** @brief	��Ч��ֵ��@ingroup   CoreVar */
DCPSDLL extern const DDS_Duration_t INVALID_DURATION;
/** @brief   ���޳��� @ingroup  CoreVar */
DCPSDLL extern const DDS_Duration_t INFINITE_DURATION;
/** @brief   ʱ��Ϊ0��@ingroup  CoreVar */
DCPSDLL extern const DDS_Duration_t ZERO_DURATION;

/** @brief	HB�ӳ���Ӧ������ACKNACK��ʱ�䣬100ms.*/
extern const DDS_Duration_t DEFALUT_HB_RESP_DELAY;
/** @brief	HB���ƣ���ֹ������յ�HB, 0s. */
extern const DDS_Duration_t DEFALUT_HB_SUPPRESSION;
/** @brief	д��HistoryCache������ӳ�ʱ��,100ms. */
extern DDS_Duration_t DEFALUT_MAX_BLOCKING_TIME;
/** @brief	����HB������. */
extern const DDS_Duration_t DEFALUT_HB_PERIOD;
/** @brief	ACKNACK����Ӧ�ӳ�ʱ��,200ms. */
extern const DDS_Duration_t DEFALUT_NACK_RESP_DELAY;
/** @brief	NACK���ƣ�SENT���Unacknowledged״̬(Э��������)��10ms. */
extern const DDS_Duration_t DEFALUT_NACK_SUPPRESSION;
/** @brief	����Participant����ʱ��. */
extern const DDS_Duration_t DEFALUT_UPDATE_PARTICIPANT;
/** @brief	Participant����ʱ��,15s. */
extern const DDS_Duration_t DEFALUT_PARTICIPANT_LEASE;
/** @brief	ParticipantReader������Participant�����Ϣ�ļ��. */
extern const DDS_Duration_t DEFALUT_CHECK_PARTICIPANT_STALE;
/** @brief	Writerˢ����Ӧ��ʱ����. */
extern const DDS_Duration_t DEFALUT_REFRESH_UNACK;
/** @brief  Ĭ�ϵ�Data(p)��������ʱ�䡣 */
extern DDS_Duration_t DEFAULT_DATAP_SUPPRESSION;

/**
 * @typedef struct DDS_Duration_t DDS_Time_t
 *
 * @ingroup CoreBaseStruct
 *
 * @brief   ʱ��㣬�ο�IETF NTP���壬time = seconds+[fraction/(2^32)].
 *
 * @sa  DDS_Duration_t
 */

typedef struct DDS_Duration_t DDS_Time_t;
/** @brief	ʱ���Ϊ0�� @ingroup   CoreVar */
DCPSDLL extern const DDS_Time_t DDS_TIME_ZERO;
/** @brief	��Ч��ʱ��㡣 @ingroup   CoreVar */
DCPSDLL extern const DDS_Time_t DDS_TIME_INVALID;
/** @brief	���޳���ʱ��㡣 @ingroup   CoreVar */
DCPSDLL extern const DDS_Time_t DDS_TIME_INFINITE;

/**
 * @fn  DCPSDLL void ZRGetNowTime(DDS_Time_t* nowTime);
 *
 * @ingroup CoreBaseFunction
 *
 * @brief   ���ص��øú���ʱ��UTC��׼ʱ�䡣
 *
 * @param [in,out]  nowTime ���ڲ�������ǰʱ�����
 */

DCPSDLL void ZRGetNowTime(DDS_Time_t* nowTime);

/**
 * @fn  DDS_Long ZRGetNowTimeString(DDS_Char* strformat);
 *
 * @ingroup  CoreFunction
 *
 * @brief   ��ȡ����ʱ����ַ�����ʽ. ��ʽ"1970-01-01 00:00:00:000"��
 *
 * @param [in,out]  strformat   �ַ��������������洢�������Ҫ��֤���㹻�Ŀռ䡣
 *
 * @pre     strformatΪ64�ֽ����ϵĿռ䡣
 *
 * @return  ���ؾ���1970/1/1 00:00:00�ĺ�����.
 */

DDS_LongLong ZRGetNowTimeString(DDS_Char* strformat);

/**
* @fn  DDS_Long ZRGetNowTimeString2(DDS_Char* strformat);
*
* @ingroup  CoreFunction
*
* @brief   ��ȡ����ʱ����ַ�����ʽ. ��ʽ"1970-01-01-00-00-00-000"��
*
* @param [in,out]  strformat   �ַ��������������洢�������Ҫ��֤���㹻�Ŀռ䡣
*
* @pre     strformatΪ64�ֽ����ϵĿռ䡣
*
* @return  ���ؾ���1970/1/1 00:00:00�ĺ�����.
*/

DDS_LongLong ZRGetNowTimeString2(DDS_Char* strformat);

#ifdef __cplusplus
}
#endif

#endif  /*_DURATION_T_H*/
