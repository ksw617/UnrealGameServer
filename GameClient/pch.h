#pragma once
#define WIN32_LEAN_AND_MEAN

#ifdef _DEBUG
#pragma comment(lib, "ServerCore\\Debug\\ServerCore.lib")  //Debug ����϶�
#pragma comment(lib, "Protobuf\\Debug\\libprotobufd.lib")  //Debug ����϶�
#else
#pragma comment(lib, "ServerCore\\Release\\ServerCore.lib")  //Release ����϶�
#pragma comment(lib, "Protobuf\\Release\\libprotobuf.lib")  //Debug ����϶�
#endif // _DEBUG

#include <CorePch.h>