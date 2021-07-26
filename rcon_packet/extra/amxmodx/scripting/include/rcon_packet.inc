#if defined _rcon_packet_included
	#endinput
#endif

#define _rcon_packet_included

/**
 * Called when a rcon packet arrives to server.
 * The packet can be obtain by read_argv native
 *
 * @param ip 		ip address
 * @return bool		true for normal action, otherwise ignore the packet
 */
forward rcon_packet(const ip[]);

/**
 * Called when a challenge rcon packet arrives to server.
 * The packet can be obtain by read_argv native
 *
 * @param ip 		ip address
 * @return bool		true for normal action, otherwise ignore the packet
 */
forward rcon_challenge_packet(const ip[]);
