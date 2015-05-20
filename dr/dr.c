/* dr.c: dice roll
 *
 * Copyright (c) 2015, Peter Piwowarski
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the following disclaimer. 
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * Usage: dr <numdice>d<dice size>
 *
 * Returns the value rolled, or 0 on error. The value rolled cannot be returned
 * reliably for large values without integer overflow, on most systems you
 * actually have an unsigned char to work with. Uses the OpenBSD functions
 * arc4random_uniform and strtonum, not included here.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main (int argc, char **argv)
{
	char *ndice_str = NULL;
	char *dsize_str = NULL;
	const char *ndice_err = NULL;
	const char *dsize_err = NULL;
	uint32_t ndice = 0;
	uint32_t dsize = 0;
	uint32_t dval = 0;

	uint32_t max = ~(0);

	if (argc != 2)
	{
		printf ("%s: bad arguments\n", argv[0]);
		return -1;
	}

	ndice_str = argv[1];
	dsize_str = argv[1];
	while (*ndice_str != '\0')
	{
		if (*dsize_str == 'd')
		{
			*dsize_str = '\0';
			dsize_str++;
			break;
		}
		dsize_str++;
	}

	if (strlen (ndice_str) == 0)
	{
		ndice = 1;
	}
	else
	{
		ndice = strtonum (ndice_str, 1, max, &ndice_err);
	}

	if (strlen (dsize_str) == 0)
	{
		printf ("%s: no dsize\n", argv[0]);
		return -1;
	}
	else
	{
		dsize = strtonum (dsize_str, 1, max, &dsize_err);
	}

	if (ndice_err != NULL && *ndice_err != '\0')
	{
		printf ("%s: bad ndice: %s\n", argv[0], ndice_err);
		return -1;
	}
	if (dsize_err != NULL && *dsize_err != '\0')
	{
		printf ("%s: bad dsize: %s\n", argv[0], dsize_err);
		return -1;
	}

	dval = ndice * (arc4random_uniform (dsize) + 1);
		
	printf ("%u\n", dval);
	return dval;
}