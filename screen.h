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

#ifndef	_SCREEN_H_
#define	_SCREEN_H_

#define DEFAULT_COLUMNS		80      /* mandatory */
#define DEFAULT_LINES		24
#define	MINPAGESIZE		20

#ifndef	ACS_HLINE
#define	ACS_HLINE	'-'
#endif

int screen_open(int resize);
void screen_close(void);
void screen_status(const char *fmt, ...);
void screen_update(void);
void screen_clear(void);
void screen_dock_cursor(int y, int x);

extern int use_colors;
extern int prompt_mode;
extern double line_factor;

#endif	/* !_SCREEN_H_ */
