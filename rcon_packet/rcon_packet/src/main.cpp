#include "rcon_packet/main.hpp"

int rconForward;
int challengeForward;

AmxxStatus on_amxx_attach()
{
	if(!RehldsApi::init() || !RegamedllApi::init()) {
		return AmxxStatus::Failed;
	}

	RehldsApi::hook_chains()->preprocess_packet()->register_hook(&PreProcessPacket, HookChainPriority::Normal);
	
	return AmxxStatus::Ok;
}

void on_amxx_plugins_loaded() {
	rconForward = AmxxApi::register_forward("rcon_packet", ForwardExecType::Stop, ForwardParam::String);
	challengeForward = AmxxApi::register_forward("rcon_challenge_packet", ForwardExecType::Stop, ForwardParam::String);
}

void on_amxx_plugins_unloaded() {
	AmxxApi::unregister_sp_forward(rconForward);
	AmxxApi::unregister_sp_forward(challengeForward);
}

bool PreProcessPacket(ReHookPreprocessPacket* /* chain */, uint8* data, unsigned int /* len */, const NetAddress& srcAddr) {
	data += 4;
	
	RehldsApi::funcs()->tokenize_string(reinterpret_cast<char *>(data));
	const char *argv0 = RegamedllApi::funcs()->cmd_argv(0);
	const char* argv1 = RegamedllApi::funcs()->cmd_argv(1);

	if(!strcmp(argv0, "rcon")) {
		return AmxxApi::execute_forward(rconForward, NET_AdrToString(srcAddr));
	}
	else if (!strcmp(argv0, "challenge") && !strcmp(argv1, "rcon")) {
		return AmxxApi::execute_forward(challengeForward, NET_AdrToString(srcAddr));
	}

	return true;
}

char* NET_AdrToString(const NetAddress& a)
{
	static char s[64];

	if (a.type == NetAddressType::Loopback)
		snprintf(s, sizeof(s), "loopback");
	else if (a.type == NetAddressType::Ip)
		snprintf(s, sizeof(s), "%i.%i.%i.%i:%i", a.ip[0], a.ip[1], a.ip[2], a.ip[3], ntohs(a.port));
#ifdef _WIN32
	else // NA_IPX
		snprintf(s, sizeof(s), "%02x%02x%02x%02x:%02x%02x%02x%02x%02x%02x:%i", a.ipx[0], a.ipx[1], a.ipx[2], a.ipx[3], a.ipx[4], a.ipx[5], a.ipx[6], a.ipx[7], a.ipx[8], a.ipx[9], ntohs(a.port));
#endif // _WIN32

	return s;
}
