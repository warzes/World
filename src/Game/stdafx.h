#pragma once

//#define NOT_USE_LEFT_HANDED_MATH

#if defined(_MSC_VER) // TODO: ���������
#	pragma warning(disable : 4365) // ���������
#	pragma warning(disable : 4514) // C4: 'function' : unreferenced inline function has been removed
#	pragma warning(disable : 4625) // C4: 'derived class' : copy constructor was implicitly defined as deleted because a base class copy constructor is inaccessible or deleted
#	pragma warning(disable : 4626) // C4: 'derived class' : assignment operator was implicitly defined as deleted because a base class assignment operator is inaccessible or deleted
#	pragma warning(disable : 4820) // ���������
#	pragma warning(disable : 5027) // 'function': move assignment operator was implicitly defined as deleted
#	pragma warning(disable : 5045) // Compiler will insert Spectre mitigation for memory load if /Qspectre switch specified
#	pragma warning(disable : 5219) // ���������
#	pragma warning(disable : 5246)
#	pragma warning(push, 0)
#	pragma warning(disable : 4619)
#	pragma warning(disable : 5039)
#endif

#include "TinyEngine.h"

#if defined(_MSC_VER)
#	pragma warning(pop)
#endif