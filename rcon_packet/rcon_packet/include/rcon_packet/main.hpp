#include "amxx/api.h"
#include "rcon_packet/rehlds_api.h"
#include "rcon_packet/regamedll_api.h"

#ifdef _WIN32
#include <winsock.h>

#pragma comment(lib, "Ws2_32.lib")
#else
#include <arpa/inet.h>
#endif

#pragma once

bool PreProcessPacket(ReHookPreprocessPacket* chain, uint8* data, unsigned int len, const NetAddress& srcAddr);
char* NET_AdrToString(const NetAddress& a);
