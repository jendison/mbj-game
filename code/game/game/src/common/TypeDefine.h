#ifndef __TYPEDEFINE_H__
#define __TYPEDEFINE_H__
#include "platform/CCPlatformConfig.h"

//跨平台类型定义
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#include <hash_map>
using std::hash_map;

typedef  char	int8t;
typedef	 short	int16t;
typedef	 int	int32t;

typedef  unsigned char uint8t;
typedef	 unsigned short	uint16t;
typedef	 unsigned int	uint32t;

#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) || (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include <ext/hash_map>
using namespace __gnu_cxx;

typedef  char	int8t;
typedef	 short	int16t;
typedef	 int	int32t;

typedef  unsigned char uint8t;
typedef	 unsigned short	uint16t;
typedef	 unsigned int	uint32t;

#else

#error("unsupport platform")
#endif //WIN32

#endif//__TYPEDEFINE_H__
