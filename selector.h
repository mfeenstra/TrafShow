/*
 * Copyright (c) 1999,2004 Rinet Corp., Novosibirsk, Russia
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

#ifndef	_SELECTOR_H_
#define	_SELECTOR_H_

typedef	struct selector {
	int window_color;
	int cursor_color;

	int LINE;		/* first line on screen		*/
	int COL;		/* first column on screen	*/
	int LINES;		/* number of lines on screen	*/
	int COLS;		/* number of columns on screen	*/
	int items;		/* size of items array 		*/

	int (*get_header)(char *dst, int size, const void *header);
	void *header;		/* header args pointer		*/

	int (*get_line)(char *dst, int size, const void *list, int idx);
	void *list;		/* list args pointer		*/

	int (*get_footer)(char *dst, int size, const void *footer);
	void *footer;		/* footer args pointer		*/

	int index;		/* array current index		*/
	int fline;		/* first displayed line		*/
	int cline;		/* current screen line		*/
} SELECTOR;

SELECTOR *selector_init();
void selector_redraw(SELECTOR *sp);
void selector_withdraw(SELECTOR *sp);
int selector_get(SELECTOR *sp);
void selector_set(int new_index, SELECTOR *sp);
int selector_move(int ch, SELECTOR *sp);

#endif	/* !_SELECTOR_H_ */
