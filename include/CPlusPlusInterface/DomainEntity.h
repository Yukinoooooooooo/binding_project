/**
 * @file:       DomainEntity.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#if !defined(_DOMAINENTITY_H)
#define _DOMAINENTITY_H

#include "ZRDDSCommon.h"
#include "Entity.h"

namespace DDS {

/**
 * @class   DomainEntity
 *
 * @ingroup CppInfrastruct
 *
 * @brief   �������������������ʵ��ĸ��࣬û��ʵ�����壬��������Э�鶨�塣
 */

class DCPSDLL DomainEntity 
    : virtual public Entity
{
public:
    DomainEntity(){}
    virtual ~DomainEntity(){}
};

} // namespace DDS

#endif  //_DOMAINENTITY_H
