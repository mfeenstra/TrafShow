/*
 * Copyright (c) 2004 Rinet Corp., Novosibirsk, Russia
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

#ifndef	_SHOW_STAT_H_
#define	_SHOW_STAT_H_

#define	SHOW_STAT_ADDR	25	/* size * 2 */
#define	SHOW_STAT_PROT	10
#define	SHOW_STAT_DATA	10
#define	SHOW_STAT_RATE	10

typedef	enum { Size, Data, Packets } ShowStatMode;

extern ShowStatMode show_stat_mode;

struct selector;
struct pcap_handler;
struct netstat_header;

struct selector *show_stat_list(struct pcap_handler *ph);
int show_stat_input(struct pcap_handler *ph, int ch);
struct selector *show_stat_selector(struct pcap_handler *ph);
struct netstat *show_stat_get(struct pcap_handler *ph, int at);
int show_stat_search(struct pcap_handler *ph, const char *str);

void hdr2str(const struct netstat_header *nh,
	     char *src_buf, int src_len,
	     char *dst_buf, int dst_len,
	     char *proto_buf, int proto_len);

#endif	/* !_SHOW_STAT_H_ */
