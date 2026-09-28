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

#ifndef	_COLORMASK_H_
#define	_COLORMASK_H_

/* SLcurses can't handle attributes as well; so hack it */
#ifdef	HAVE_SLCURSES
#ifdef	SLTT_BOLD_MASK
#undef	A_BOLD
#define	A_BOLD		SLTT_BOLD_MASK
#endif
#ifdef	SLTT_BLINK_MASK
#undef	A_BLINK
#define	A_BLINK		SLTT_BLINK_MASK
#endif
#endif

struct netstat_header;
int init_colormask(void);
int colormask(const struct netstat_header *nh);
int colormask_header(void);
int colormask_footer(void);
int colormask_help(void);

#endif	/* !_COLORMASK_H_ */
