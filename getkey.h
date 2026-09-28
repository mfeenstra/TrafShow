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

#ifndef	_GETKEY_H_
#define	_GETKEY_H_

#define	MAX_PARAM_LEN	512

#define	ESCAPE		'\033'
#define	K_CTRL(c)	((c) & 0x1f)
#define	K_DEL		0x7f
#define	K_CR		'\r'
#define	K_NL		'\n'
#define	K_BS		'\b'
#define	K_TAB		'\t'

/* arrow keys */
#define	K_ARROW(c)	((c) & 0x0f00)
#define	K_ESC		0x0100
#define	K_UP		0x0200
#define	K_DOWN		0x0300
#define	K_LEFT		0x0400
#define	K_RIGHT		0x0500
#define	K_PAGEUP	0x0600
#define	K_PAGEDOWN	0x0700
#define	K_HOME		0x0800
#define	K_END		0x0900
#define	K_INS		0x0a00

/* func keys */
#define	K_FUNC(c)	((c) & 0xf000)
#define	K_F1		0x1000
#define	K_F2		0x2000
#define	K_F3		0x3000
#define	K_F4		0x4000
#define	K_F5		0x5000
#define	K_F6		0x6000
#define	K_F7		0x7000
#define	K_F8		0x8000
#define	K_F9		0x9000
#define	K_F10		0xa000
#define	K_F11		0xb000
#define	K_F12		0xc000

struct pcap_handler;
void getkey_init(struct pcap_handler *ph_list);

#endif	/* !_GETKEY_H_ */
