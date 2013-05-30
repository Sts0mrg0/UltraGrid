/*
 * FILE:    module.h
 * AUTHORS: Martin Benes     <martinbenesh@gmail.com>
 *          Lukas Hejtmanek  <xhejtman@ics.muni.cz>
 *          Petr Holub       <hopet@ics.muni.cz>
 *          Milos Liska      <xliska@fi.muni.cz>
 *          Jiri Matela      <matela@ics.muni.cz>
 *          Dalibor Matura   <255899@mail.muni.cz>
 *          Ian Wesley-Smith <iwsmith@cct.lsu.edu>
 *
 * Copyright (c) 2005-2010 CESNET z.s.p.o.
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
 *      This product includes software developed by CESNET z.s.p.o.
 *
 * 4. Neither the name of the CESNET nor the names of its contributors may be
 *    used to endorse or promote products derived from this software without
 *    specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHORS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESSED OR IMPLIED WARRANTIES, INCLUDING,
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
#ifndef MODULE_H_
#define MODULE_H_

#ifdef HAVE_CONFIG_H
#include "config.h"
#include "config_win32.h"
#include "config_unix.h"
#endif

#include "messaging.h"

#ifdef __cplusplus
extern "C" {
#endif

#define MODULE_MAGIC 0xf1125b44

enum module_class {
        MODULE_CLASS_NONE = 0,
        MODULE_CLASS_ROOT,
        MODULE_CLASS_COMPRESS,
        MODULE_CLASS_DATA,
        MODULE_CLASS_SENDER,
        MODULE_CLASS_TX,
        MODULE_CLASS_AUDIO,
};

struct module;
struct simple_linked_list;

typedef void (*module_deleter_t)(struct module *);

struct module {
        uint32_t magic;
        pthread_mutex_t lock;
        enum module_class cls;
        struct module *parent;
        struct simple_linked_list *childs;
        module_deleter_t deleter;

        msg_callback_t msg_callback;

        void *priv_data;
};

void module_init_default(struct module *module_data);
void module_register(struct module *module_data, struct module *parent);
void module_done(struct module *module_data);
const char *module_class_name(enum module_class cls);
void make_message_path(char *buf, int buflen, enum module_class modules[]);

#define CAST_MODULE(x) ((struct module *) x)

#ifdef __cplusplus
}
#endif

#endif
