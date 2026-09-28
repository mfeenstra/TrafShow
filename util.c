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

#ifdef	HAVE_CONFIG_H
#include <config.h>
#endif

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "util.h"

char *
strip_path(path)
	const char *path;
{
	char *cp;
	if (path && (cp = strrchr(path, '/')) != 0)
		return (++cp);
	return (char *)path;
}

char *
strip_blanks(str)
	char *str;
{
	char *bp, *ep;

	if (!str || !*str)
		return str;

	bp = str;
	while (*bp == ' ' || *bp == '\t') bp++;

	ep = bp + (strlen(bp)-1);
	while (ep >= bp &&
	       (*ep == ' ' || *ep == '\t' || *ep == '\r' || *ep == '\n'))
		*ep-- = '\0';

	return bp;
}

/*
 * Copy arg vector into a new buffer, concatenating arguments with spaces.
 */
char *
copy_argv(av)
	char **av;
{
	unsigned int len = 0;
	char **p, *buf, *src, *dst;

	p = av;
	if (*p == 0) return 0;
	while (*p) len += strlen(*p++) + 1;
	if ((buf = (char *)malloc(len)) == 0) {
		perror("malloc");
		return 0;
	}
	p = av;
	dst = buf;
	while ((src = *p++) != 0) {
		while ((*dst++ = *src++) != '\0');
		dst[-1] = ' ';
	}
	dst[-1] = '\0';

	return buf;
}

/*
 * Return size in bytes of regular file `name'.
 */
long
fd_size(fd)
	int fd;
{
	struct stat st;
	if (fstat(fd, &st) < 0)
		return -1;
	return (long)st.st_size;
}

char *
load_file(name)
	const char *name;
{
	int fd;
	long sz;
	char *cp;

	if ((fd = open(name, O_RDONLY)) < 0) {
		perror(name);
		return 0;
	}
	if ((sz = fd_size(fd)) < 0) {
		perror(name);
		close(fd);
		return 0;
	}
	if ((cp = (char *)malloc(sz + 1)) == 0) {
		perror(name);
		close(fd);
		return 0;
	}
	if ((sz = read(fd, cp, sz)) < 0) {
		perror(name);
		close(fd);
		free(cp);
		return 0;
	}
	close(fd);
	cp[sz] = '\0';

	return cp;
}

