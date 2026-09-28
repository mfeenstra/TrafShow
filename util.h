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

#ifndef	_UTIL_H_
#define	_UTIL_H_

char *strip_path(const char *path);
char *strip_blanks(char *str);
char *copy_argv(char **av);		/* malloc is used */
long fd_size(int fd);
char *load_file(const char *name);	/* malloc is used */

#endif	/* !_UTIL_H_ */
