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

#ifndef	_SHOW_IF_H_
#define	_SHOW_IF_H_

#define	SHOW_IF_NAME	15
#define	SHOW_IF_ADDR	45
#define	SHOW_IF_DESCR	20

struct selector;
struct pcap_handler;
struct selector *show_if_list(struct pcap_handler *list);
struct selector *show_if_selector();
int show_if_search(struct pcap_handler *list, const char *str);

#endif	/* !_SHOW_IF_H_ */
