/*
 * Copyright (c) 2003 Rinet Corp., Novosibirsk, Russia
 *
 * This file is part of TrafShow.
 *
 * TrafShow is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * TrafShow is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with TrafShow.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef	_DOMAIN_RESOLVER_H_
#define	_DOMAIN_RESOLVER_H_

/*
 * Domain Name Service support.
 */

#include <sys/types.h>
#include <netinet/in.h>

#define	NAMESERVER_TIMEOUT	10	/* awaiting reply in seconds */
#define	NAMESERVER_RETRIES	3	/* max number of retries */

typedef	struct domain_data_ent {
	u_int ttl;		/* max seconds may be cached */
	u_int pref;		/* preference if any (for ex. in MX list) */
	char *name;		/* domain name */
	in_addr_t addr;		/* ip address */
	unsigned char addr6[16]; /* ipv6 address; valid only if is6 */
	int is6;		/* addr6 holds the original address, not addr */

	struct domain_data_ent *next;
} DOMAIN_DATA;

struct session_ent;

/*
 * [Re]initialize nameservers (probably using /etc/resolv.conf).
 * Public just for nameservers to be reconfigured by outside signals.
 */
int domain_resolver_init();

/*
 * Get IP address at the domain asynchronously.
 * If return -1 (an error) requester of this function will not be notified.
 */
int domain_resolve_addr(const char *domain,
			struct session_ent *sd,
			void (*notify)(struct session_ent *sd, DOMAIN_DATA *dd));
/*
 * Get MX list at the domain asynchronously.
 * If return -1 (an error) requester of this function will not be notified.
 */
int domain_resolve_mxlist(const char *domain,
			  struct session_ent *sd,
			  void (*notify)(struct session_ent *sd, DOMAIN_DATA *dd));
/*
 * Get domain name at the IP address asynchronously.
 * If return -1 (an error) requester of this function will not be notified.
 */
int domain_resolve_name(in_addr_t ipaddr, /* Network Byte Order */
			struct session_ent *sd,
			void (*notify)(struct session_ent *sd, DOMAIN_DATA *dd));

/*
 * Get domain name at the IPv6 address asynchronously.
 * 'ipaddr6' points to 16 bytes (struct in6_addr) in network byte order;
 * unlike domain_resolve_name() it is only used for the duration of the
 * call, so the caller need not keep it alive afterwards.
 * If return -1 (an error) requester of this function will not be notified.
 */
int domain_resolve_name6(const void *ipaddr6,
			 struct session_ent *sd,
			 void (*notify)(struct session_ent *sd, DOMAIN_DATA *dd));

/*
 * Domain data container utilities.
 */
DOMAIN_DATA *domain_data_add(DOMAIN_DATA **list, const char *name, int pref);
DOMAIN_DATA *domain_data_find(DOMAIN_DATA **list, const char *name);
void domain_data_free(DOMAIN_DATA **list, const char *name); /* null to all */

#endif	/* !_DOMAIN_RESOLVER_H_ */

