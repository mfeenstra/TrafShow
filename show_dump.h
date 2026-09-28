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

#ifndef	_SHOW_DUMP_H_
#define	_SHOW_DUMP_H_

#define	DUMP_SNAPLEN	1536

struct pcap_handler;
struct netstat;

int show_dump_open(const struct pcap_handler *ph, const struct netstat *ns);
void show_dump_print(struct pcap_handler *ph);
void show_dump_close(void);
void show_dump_input(int ch);

extern const char *dump_file;
extern const char *cisco_netflow_dump;
extern struct netstat *dump_match;

#endif	/* !_SHOW_DUMP_H_ */
