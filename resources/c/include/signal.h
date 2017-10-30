/** @file
 * 
 *  @brief Standard C time functions
 *
 * See https://www.mankier.com/0p/signal.h
 * UNIX signals.
 *
 * Copyright (c) Open IO Labs Ltd 2016
 * All Rights Reserved 
 */

#ifndef __SIGNAL_H
#define __SIGNAL_H

#include <stddef.h>

#define SIGHUP           1
#define SIGINT           2
#define SIGQUIT          3
#define SIGILL           4
#define SIGTRAP          5
#define SIGABRT          6
#define SIGIOT           6
#define SIGBUS           7
#define SIGFPE           8
#define SIGKILL          9
#define SIGUSR1         10
#define SIGSEGV         11
#define SIGUSR2         12
#define SIGPIPE         13
#define SIGALRM         14
#define SIGTERM         15
#define SIGSTKFLT       16
#define SIGCHLD         17
#define SIGCONT         18
#define SIGSTOP         19
#define SIGTSTP         20
#define SIGTTIN         21
#define SIGTTOU         22
#define SIGURG          23
#define SIGXCPU         24
#define SIGXFSZ         25
#define SIGVTALRM       26
#define SIGPROF         27
#define SIGWINCH        28
#define SIGIO           29
#define SIGPOLL         SIGIO
#define SIGPWR          30
#define SIGSYS          31
#define SIGUNUSED       31
#define SIGRTMIN        32
#define SIGRTMAX        64

#define SIG_IGN			NULL

void __sig_dfl( int signum ) {}

#define SIG_DFL (&__sig_dfl)

typedef void (*sighandler_t)(int signum);

/**
 *  @brief Set the action on a signal
 *
 *  @param signum The signal to update
 *  @param handler Pointer to the new handler function or SIG_IGN or SIG_DFL
 *  @return 0 on success 
 */
sighandler_t signal(int signum, sighandler_t handler)
{
	if( handler==SIG_DFL )
		___ResetSignalHandler( signal:signum );
	else if( handler==0 )
		___SetSignalHandler( signal:signum, handler:___NULL() );
	else
		___SetSignalHandler( signal:signum, handler:*handler );
	return 0;
}

/**
 * Set a handler for script exceptions (used as a substitute for exception handling in C)
 * 
 * Pass in the exception type (as a type) and a pointer to a handler function.
 * 
 * Handler will be called as soon as the exception occurs (i.e. at the point of throwing).
 * If it requrns, script execution will continue from the failed operation. Return values
 * and other putputs from the failing operation will be undefined.
 * 
 * Typically, the script will set an error flag and/or an LWM2M error resource, OR
 * just halt or restart the script.
 */
#define set_exception_handler(TYPE, HANDLER) ___SetExceptionHandler( exception_type:TYPE, handler:*(HANDLER) )
#define external_error ___EnvironmentErrorExceptionType()

#endif
