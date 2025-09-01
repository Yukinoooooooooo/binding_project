/**
 * @file:       Listener.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#if !defined(_LISTENER_H)
#define _LISTENER_H

#include "ZRDDSCommon.h"

namespace DDS {

/**
 * @class   Listener
 *
 * @ingroup CppListener
 *
 * @brief   ���������м������Ļ��࣬��������ZRDDS�ṩ��һ���첽�ص����ƣ��μ� @ref listener-introduction 
 */

class DCPSDLL Listener
{
public:
    virtual ~Listener() {}
};

} /*namespace DDS*/

#endif  //_LISTENER_H
