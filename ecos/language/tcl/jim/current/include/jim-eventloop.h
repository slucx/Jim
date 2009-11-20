/* Jim - A small embeddable Tcl interpreter
 *
 * Copyright 2005 Salvatore Sanfilippo <antirez@invece.org>
 * Copyright 2005 Clemens Hintze <c.hintze@gmx.net>
 * Copyright 2005 patthoyts - Pat Thoyts <patthoyts@users.sf.net>
 * Copyright 2008 oharboe - Øyvind Harboe - oyvind.harboe@zylin.com
 * Copyright 2008 Andrew Lunn <andrew@lunn.ch>
 * Copyright 2008 Duane Ellis <openocd@duaneellis.com>
 * Copyright 2008 Uwe Klein <uklein@klein-messgeraete.de>
 *
 * The FreeBSD license
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above
 *    copyright notice, this list of conditions and the following
 *    disclaimer in the documentation and/or other materials
 *    provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE JIM TCL PROJECT ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 * PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * JIM TCL PROJECT OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * The views and conclusions contained in the software and documentation
 * are those of the authors and should not be interpreted as representing
 * official policies, either expressed or implied, of the Jim Tcl Project.
 **/
/* ------ USAGE -------
 *
 * In order to use this file from other extensions include it in every
 * file where you need to call the eventloop API, also in the init
 * function of your extension call Jim_ImportEventloopAPI(interp)
 * after the Jim_InitExtension() call.
 *
 * See the UDP extension as example.
 */


#ifndef __JIM_EVENTLOOP_H__
#define __JIM_EVENTLOOP_H__

typedef int Jim_FileProc(Jim_Interp *interp, void *clientData, int mask);
typedef int Jim_SignalProc(Jim_Interp *interp, void *clientData, void *msg);
typedef void Jim_TimeProc(Jim_Interp *interp, void *clientData);
typedef void Jim_EventFinalizerProc(Jim_Interp *interp, void *clientData);

/* File event structure */
#define JIM_EVENT_READABLE 1
#define JIM_EVENT_WRITABLE 2
#define JIM_EVENT_EXCEPTION 4
#define JIM_EVENT_FEOF 8

#define JIM_API(x) x
#define JIM_STATIC

JIM_STATIC int Jim_EventLoopOnLoad(Jim_Interp *interp);

/* --- POSIX version of Jim_ProcessEvents, for now the only available --- */
#define JIM_FILE_EVENTS 1
#define JIM_TIME_EVENTS 2
#define JIM_ALL_EVENTS (JIM_FILE_EVENTS | JIM_TIME_EVENTS)
#define JIM_DONT_WAIT 4

JIM_STATIC void JIM_API(Jim_CreateFileHandler) (Jim_Interp *interp,
        void *handle, int mask,
        Jim_FileProc *proc, void *clientData,
        Jim_EventFinalizerProc *finalizerProc);
JIM_STATIC void JIM_API(Jim_DeleteFileHandler) (Jim_Interp *interp,
        void *handle);
JIM_STATIC jim_wide JIM_API(Jim_CreateTimeHandler) (Jim_Interp *interp,
        jim_wide milliseconds,
        Jim_TimeProc *proc, void *clientData,
        Jim_EventFinalizerProc *finalizerProc);
JIM_STATIC jim_wide JIM_API(Jim_DeleteTimeHandler) (Jim_Interp *interp, jim_wide id);
JIM_STATIC int JIM_API(Jim_ProcessEvents) (Jim_Interp *interp, int flags);

#undef JIM_STATIC
#undef JIM_API

#ifndef __JIM_EVENTLOOP_CORE__

#define JIM_GET_API(name) \
    Jim_GetApi(interp, "Jim_" #name, ((void *)&Jim_ ## name))

#undef JIM_GET_API
#endif /* __JIM_EVENTLOOP_CORE__ */

#endif /* __JIM_EVENTLOOP_H__ */