/*
 * FILE:   video_display/null.c
 * AUTHOR: Colin Perkins <csp@isi.edu>
 *
 * Copyright (c) 2001-2003 University of Southern California
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, is permitted provided that the following conditions
 * are met:
 * 
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 * 
 *      This product includes software developed by the University of Southern
 *      California Information Sciences Institute.
 * 
 * 4. Neither the name of the University nor of the Institute may be used
 *    to endorse or promote products derived from this software without
 *    specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE AUTHORS AND CONTRIBUTORS
 * ``AS IS'' AND ANY EXPRESSED OR IMPLIED WARRANTIES, INCLUDING,
 * BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY
 * AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO
 * EVENT SHALL THE AUTHORS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * $Revision: 1.1 $
 * $Date: 2007/11/08 09:48:59 $
 *
 */

#include "config.h"
#include "config_unix.h"
#include "config_win32.h"
#include "debug.h"
#include "video_display.h"
#include "video_display/null.h"

#define MAGIC_NULL	0x17bad83f

struct state_null {
	uint32_t	magic;
};

void *
display_null_init(void)
{
	struct state_null *s;

	s = (struct state_null *) malloc(sizeof(struct state_null));
	if (s != NULL) {
		s->magic = MAGIC_NULL;
	}
	return s;
}

void
display_null_done(void *state)
{
	struct state_null *s = (struct state_null *) state;
	assert(s->magic == MAGIC_NULL);
	free(s);
}

char *
display_null_getf(void *state)
{
	struct state_null *s = (struct state_null *) state;
	assert(s->magic == MAGIC_NULL);
	return NULL;
}

int
display_null_putf(void *state, char *frame)
{
	struct state_null *s = (struct state_null *) state;
	assert(s->magic == MAGIC_NULL);
	UNUSED(frame);
	return 0;
}

display_colour_t
display_null_colour(void *state)
{
	struct state_null *s = (struct state_null *) state;
	assert(s->magic == MAGIC_NULL);
	return DC_NONE;
}

display_type_t *
display_null_probe(void)
{
	display_type_t		*dt;
	display_format_t	*df;

	df = malloc(sizeof(display_format_t));
	if (df == NULL) {
		return NULL;
	}
	df->size        = DS_NONE;
	df->colour_mode = DC_NONE;
	df->num_images  = 0;

	dt = malloc(sizeof(display_type_t));
	if (dt != NULL) {
		dt->id	        = DISPLAY_NULL_ID;
		dt->name        = "none";
		dt->description = "No display device";
		dt->formats     = df;
		dt->num_formats = 1;
	}
	return dt;
}

