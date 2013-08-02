/**
 * @file   video_capture.h
 * @author Colin Perkins <csp@csperkins.org>
 * @author Martin Benes     <martinbenesh@gmail.com>
 * @author Lukas Hejtmanek  <xhejtman@ics.muni.cz>
 * @author Petr Holub       <hopet@ics.muni.cz>
 * @author Milos Liska      <xliska@fi.muni.cz>
 * @author Jiri Matela      <matela@ics.muni.cz>
 * @author Dalibor Matura   <255899@mail.muni.cz>
 * @author Martin Pulec     <pulec@cesnet.cz>
 * @author Ian Wesley-Smith <iwsmith@cct.lsu.edu>
 *
 * @ingroup vidcap
 */
/**
 * Copyright (c) 2005-2013 CESNET z.s.p.o
 * Copyright (c) 2002 University of Southern California
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
 *      California Information Sciences Institute. This product also includes
 *      software developed by CESNET z.s.p.o.
 * 
 * 4. Neither the name of the University, Institute, CESNET nor the names of
 *    its contributors may be used to endorse or promote products derived from
 *    this software without specific prior written permission.
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
 */

/**
 * @defgroup vidcap Video Capture
 *
 * API for video capture. Normal operation is something like:
 * @code{.c}
 * v = vidcap_init(id);
 * ...
 * while (!done) {
 *     ...
 *     f = vidcap_grab(v, timeout);
 *     ...use the frame "f"
 * }
 * vidcap_done(v);
 * @endcode
 *
 * Where the "id" parameter to vidcap_init() is obtained from
 * the probing API. The vidcap_grab() function returns a pointer
 * to the frame, or NULL if no frame is currently available. It
 * does not block.
 *
 * @note
 * The vidcap_grab() API is currently slightly different - the function does
 * not take the timeout parameter and may block, but only for a short period
 * (ideally no longer than 2x frame time)
 *
 * @{
 */

#ifndef _VIDEO_CAPTURE_H_
#define _VIDEO_CAPTURE_H_

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/** @anchor vidcap_flags
 * @name Initialization Flags
 * @{ */
#define VIDCAP_FLAG_AUDIO_EMBEDDED (1<<1) ///< HD-SDI embedded audio
#define VIDCAP_FLAG_AUDIO_AESEBU (1<<2)   ///< AES/EBU audio
#define VIDCAP_FLAG_AUDIO_ANALOG (1<<3)   ///< (balanced) analog audio
/** @} */

typedef uint32_t	vidcap_id_t; ///< driver unique ID

struct audio_frame;

/** Defines video capture device */
struct vidcap_type {
	vidcap_id_t		 id;          ///< device unique identifier
	const char		*name;        ///< short name (one word)
	const char		*description; ///< description of the video device
	unsigned	 	 width;       ///< @deprecated AFAIK not used any more
	unsigned	 	 height;      ///< @deprecated no more used
	//video_colour_mode_t	 colour_mode;
};

struct vidcap_params;

/**
 * Defines parameters passed to video capture driver.
 * Unused parameters should be set to zero.
  */
struct vidcap_params {
        const char  *driver; ///< driver name
        const char  *fmt;    ///< driver options
        unsigned int flags;  ///< one of @ref vidcap_flags
};

int			 vidcap_init_devices(void);
void			 vidcap_free_devices(void);
int			 vidcap_get_device_count(void);
struct vidcap_type	*vidcap_get_device_details(int index);
vidcap_id_t 		 vidcap_get_null_device_id(void);

struct vidcap;

int                      vidcap_init(vidcap_id_t id, const struct vidcap_params *param, struct vidcap **);
void			 vidcap_done(struct vidcap *state);
struct video_frame	*vidcap_grab(struct vidcap *state, struct audio_frame **audio);

extern int vidcap_init_noerr;

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // _VIDEO_CAPTURE_H_
/**
 * @}
 */

