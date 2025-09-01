/**
 * @file:       DomainId_t.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#if !defined(_DOMAINID_T_H)
#define _DOMAINID_T_H

#include "OsResource.h"

/**
 * @typedef DDS_ULong DDS_DomainId_t
 *
 * @ingroup CoreBaseStruct
 *
 * @brief   ������ʾ��������������ֵ��
 *
 * @details  ʹ���޷�����������ʾ��������������ֵ����RTPSЭ���£����ڶ˿ڼ��㷽ʽ:���ܳ���65536��һ�����ж˿ڲ��� userPort =
 *              (7400+250*domainId+2*partId + 11)�� builtinPort = (7400+250*domainId+2*partId + 10)
 *              �ڵ���һ���ڵ��ϣ����ȡֵ��Χ��[0, 232],����[0, 231]������125��Participant��232������64��Participant��
 */

typedef DDS_ULong DDS_DomainId_t;

#endif  /* _DOMAINID_T_H */
