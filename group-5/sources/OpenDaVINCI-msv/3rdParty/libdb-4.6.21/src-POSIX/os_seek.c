/*-
 * See the file LICENSE for redistribution information.
 *
 * Copyright (c) 1997,2007 Oracle.  All rights reserved.
 *
 * $Id: os_seek.c,v 12.13 2007/05/17 15:15:46 bostic Exp $
 */

#include "db_config.h"

#include "db_int.h"

/*
 * __os_seek --
 *	Seek to a page/byte offset in the file.
 *
 * PUBLIC: int __os_seek __P((DB_ENV *,
 * PUBLIC:      DB_FH *, db_pgno_t, u_int32_t, u_int32_t));
 */
int
__os_seek(dbenv, fhp, pgno, pgsize, relative)
	DB_ENV *dbenv;
	DB_FH *fhp;
	db_pgno_t pgno;
	u_int32_t pgsize;
	u_int32_t relative;
{
	off_t offset;
	int ret;

	DB_ASSERT(dbenv, F_ISSET(fhp, DB_FH_OPENED) && fhp->fd != -1);

	offset = (off_t)pgsize * pgno + relative;

	if (dbenv != NULL && FLD_ISSET(dbenv->verbose, DB_VERB_FILEOPS_ALL))
		__db_msg(dbenv,
		    "fileops: seek %s to %lu", fhp->name, (u_long)offset);

	if (DB_GLOBAL(j_seek) != NULL)
		ret = DB_GLOBAL(j_seek)(fhp->fd, offset, SEEK_SET);
	else
		RETRY_CHK((lseek(
		    fhp->fd, offset, SEEK_SET) == -1 ? 1 : 0), ret);

	if (ret == 0) {
		fhp->pgsize = pgsize;
		fhp->pgno = pgno;
		fhp->offset = relative;
	} else {
		__db_syserr(dbenv, ret,
		    "seek: %lu: (%lu * %lu) + %lu", (u_long)offset,
		    (u_long)pgno, (u_long)pgsize, (u_long)relative);
		ret = __os_posix_err(ret);
	}

	return (ret);
}
