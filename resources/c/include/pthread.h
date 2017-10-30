/** @file
 * 
 *  @brief Posix pthreads
 *
 *  See https://www.mankier.com/7/pthreads
 *  Implemented here: PThread, mutex, read/write lock, condition
 *  variable.
 *
 * Copyright (c) Open IO Labs Ltd 2016
 * All Rights Reserved
 */
 
// TODO in all these, where an any-type variable is needed, use ___NULL_T()
// rather than void *

#ifndef __PTHREAD_H
#define __PTHREAD_H

#include <coroutines.h>
#include <stddef.h>

///////////////////////// PThread /////////////////////////

typedef sml_coroutine_handle_t pthread_t;

/* Detach state.  */
#define PTHREAD_CREATE_JOINABLE 0
#define PTHREAD_CREATE_DETACHED 1

/* Scope handling.  */
#define PTHREAD_SCOPE_SYSTEM  0
#define PTHREAD_SCOPE_PROCESS 1

/* Scheduler inheritance.  */
#define PTHREAD_INHERIT_SCHED  0
#define PTHREAD_EXPLICIT_SCHED 1

/* Scheduling algorithms.  */
#define SCHED_OTHER 0
#define SCHED_FIFO  1
#define SCHED_RR    2

struct sched_param {
    int sched_priority;     /* Scheduling priority */
};
           
/** Thread attributes object */
typedef struct 
{
	int detachstate;
	int scope;
	int inheritsched;
	int policy;
	struct sched_param param;
	int guardsize;
	int stack_addr;
	int stack_size;
} pthread_attr_t;


/* defaults from the man page
                   Detach state        = PTHREAD_CREATE_JOINABLE
                   Scope               = PTHREAD_SCOPE_SYSTEM
                   Inherit scheduler   = PTHREAD_INHERIT_SCHED
                   Scheduling policy   = SCHED_OTHER
                   Scheduling priority = 0
                   Guard size          = 4096 bytes
                   Stack address       = 0x40196000
                   Stack size          = 0x201000 bytes
*/

/**
 *  @brief Initialise a pthreads attribute structure
 *
 *  @param attr Pointer to the attribute block to initialise
 *  @return Zero on success, non-zero on failure
 */
int pthread_attr_init(pthread_attr_t *attr)
{
	attr->detachstate = PTHREAD_CREATE_JOINABLE;
	attr->scope = PTHREAD_SCOPE_SYSTEM;
	attr->inheritsched = PTHREAD_INHERIT_SCHED;
	attr->policy = SCHED_FIFO; // Non-standard: gives coroutine behaviour
	attr->param.sched_priority = 1; // Non-standard: gives coroutine behaviour
	attr->stack_addr = 0;
	attr->stack_size = 0;
	return 0;
}


/**
 *  @brief Uninitialise a pthreads attribute structure
 *
 *  @param attr Pointer to the attribute block to uninitialise
 *  @return Zero on success, non-zero on failure
 */
int pthread_attr_destroy(pthread_attr_t *attr)
{
	return 0;
}


/**
 *  @brief Set the detach state in a thread attributes block
 *
 *  @param attr Pointer to the attribute block to update
 *  @param detachstate One of PTHREAD_CREATE_JOINABLE or PTHREAD_CREATE_DETACHED
 *  @return Zero on success, non-zero on failure
 */
int pthread_attr_setdetachstate(pthread_attr_t *attr, int detachstate)
{ 
	attr->detachstate = detachstate;
	return 0;
}


/**
 *  @brief Read the detach state from a thread attributes block
 *
 *  @param attr Pointer to the attribute block to update
 *  @param detachstate Pointer to the detachment state (int)
 *  @return Zero on success, non-zero on failure
 */
int pthread_attr_getdetachstate(const pthread_attr_t *attr, int *detachstate)
{
	*detachstate = attr->detachstate;
	return 0;
}


/**
 *  @brief Set the scheduler inheritance in a thread attributes block
 *
 *  @param attr Pointer to the attribute block to update
 *  @param inheritsched One of PTHREAD_INHERIT_SCHED or PTHREAD_EXPLICIT_SCHED
 *  @return Zero on success, non-zero on failure
 */
int pthread_attr_setinheritsched(pthread_attr_t *attr, int inheritsched)
{
	attr->inheritsched = inheritsched;
	return 0;
}


/**
 *  @brief Read the scheduler inheritance from a thread attributes block
 *
 *  @param attr Pointer to the attribute block to update
 *  @param inheritsched Pointer to the scheduler inheritance (int)
 *  @return Zero on success, non-zero on failure
 */
int pthread_attr_getinheritsched(const pthread_attr_t *attr, int *inheritsched)
{
	*inheritsched = attr->inheritsched;
	return 0;
}


/**
 *  @brief Set the scheduler parameters in a thread attributes block
 *
 *  @param attr Pointer to the attribute block to update
 *  @param param Pointer to the sched_param struct to use
 *  @return Zero on success, non-zero on failure
 */
int pthread_attr_setschedparam(pthread_attr_t *attr, const struct sched_param *param)
{
	attr->param = *param;
	return 0;
}


/**
 *  @brief Read the scheduler parameters from a thread attributes block
 *
 *  @param attr Pointer to the attribute block to update
 *  @param param Pointer to the sched_param struct to receive the scheduler parameters
 *  @return Zero on success, non-zero on failure
 */
int pthread_attr_getschedparam(const pthread_attr_t *attr, struct sched_param *param)
{
	*param = attr->param;
	return 0;
}


/**
 *  @brief Set the scheduler policy in a thread attributes block
 *
 *  @param attr Pointer to the attribute block to update
 *  @param policy One of SCHED_OTHER, SCHED_FIFO or SCHED_RR
 *  @return Zero on success, non-zero on failure
 */
int pthread_attr_setschedpolicy(pthread_attr_t *attr, int policy)
{
	attr->policy = policy;
	return 0;
}


/**
 *  @brief Read the scheduler policy from a thread attributes block
 *
 *  @param attr Pointer to the attribute block to update
 *  @param policy Pointer to the scheduler policy (int)
 *  @return Zero on success, non-zero on failure
 */
int pthread_attr_getschedpolicy(const pthread_attr_t *attr, int *policy)
{
	*policy = attr->policy;
	return 0;
}


/**
 *  @brief Set the thread scope in a thread attributes block
 *
 *  @param attr Pointer to the attribute block to update
 *  @param policy One of PTHREAD_SCOPE_SYSTEM, PTHREAD_SCOPE_PROCESS
 *  @return Zero on success, non-zero on failure
 */
int pthread_attr_setscope(pthread_attr_t *attr, int scope)
{
	attr->scope = scope;
	return 0;
}


/**
 *  @brief Read the scheduler policy from a thread attributes block
 *
 *  @param attr Pointer to the attribute block to update
 *  @param policy Pointer to the scheduler policy (int)
 *  @return Zero on success, non-zero on failure
 */
int pthread_attr_getscope(const pthread_attr_t *attr, int *scope)
{
	*scope = attr->scope;
	return 0;
}


/**
 *  @brief Create a thread
 *
 *  @param thread Thread id is written here
 *  @param attr Pointer to the attribute block to update
 *  @param start_routine Pointer to the thread's initial function 
 *  @param arg An arbitrary argument
 *  @return Zero on success, non-zero on failure
 */
int pthread_create( pthread_t *thread, 
				    const pthread_attr_t *attr,
                    void *(*start_routine) (___NULL_T() arg), 
                    ___NULL_T() arg )
{	
	// Require that the attributes are configured to make the thread
	// resemble a coroutine.
	if( attr &&
		( attr->param.sched_priority != 1 || 
	      attr->policy != SCHED_FIFO ) )
		return EINVAL; 
		
	*thread = sml_coroutine_create_1( *start_routine, arg );
	return 0;
}                 


/**
 *  @brief Yield the current thread to other threads
 *
 *  @return Zero on success, non-zero on failure
 */
int pthread_yield()
{
	sml_coroutine_yield();
	return 0;
}   


/**
 *  @brief Exit the thread, supplying a result code
 *
 *  @param value_ptr value to return (any type)
 *  @return Never returns
 */
void pthread_exit( ___NULL_T() value)
{
	sml_coroutine_exit(value);
}


/**
 *  @brief Wait for thread to complete 
 *
 *  @param thread Thread to await 
 *  @param value_ptr Pointer to void * value result 
 *  @return Zero on success, non-zero on failure
 */
int pthread_join(pthread_t thread, void **value_ptr)
{
	void *result = sml_coroutine_join(thread);
	if( value_ptr )
		*value_ptr = result;
	return 0;
}


/**
 *  @brief Obtain id of current thread
 *
 *  @return Current thread's thread id
 */
pthread_t pthread_self()
{
	return sml_coroutine_get_current_id();
}

///////////////////////// Mutex /////////////////////////

/** Mutex object */
typedef bool pthread_mutex_t; // Bool is true when locked and false when unlocked

#define PTHREAD_MUTEX_INITIALIZER false

typedef int pthread_mutexattr_t;

/**
 *  @brief Create mutex object
 *
 *  @param mutex Pointer to mutex object to initialise 
 *  @param attr Pointer to mutex attributes object (unused)
 *  @return Zero on success, non-zero on failure
 */
int pthread_mutex_init(pthread_mutex_t *mutex,
                       const pthread_mutexattr_t *attr)
{
	*mutex = PTHREAD_MUTEX_INITIALIZER;
	return 0;
}


/**
 *  @brief Destroy mutex object
 *
 *  @param mutex Pointer to mutex object to uninitialise 
 *  @return Zero on success, non-zero on failure
 */
int pthread_mutex_destroy(pthread_mutex_t *mutex)
{
	return 0;
}                       


/**
 *  @brief Attempt to lock mutex object
 *
 *  @param mutex Pointer to mutex object to lock 
 *  @return Zero on success, EBUSY if locked, other on failure
 */
int pthread_mutex_trylock(pthread_mutex_t *mutex)
{
	if( *mutex )
		return EBUSY; // fail if locked
	*mutex = true;
	return 0;
}


/**
 *  @brief Lock mutex object, blocking 
 *
 *  @param mutex Pointer to mutex object to lock 
 *  @return Zero on success, non-zero on failure
 */
int pthread_mutex_lock(pthread_mutex_t *mutex)
{
	sml_coroutine_wait( !(*mutex) ); // all threads waiting on the mutex are waiting here
	*mutex = true;
	return 0;
}


/**
 *  @brief Unlock mutex object
 *
 *  @param mutex Pointer to mutex object to lock 
 *  @return Zero on success, non-zero on failure
 */
int pthread_mutex_unlock(pthread_mutex_t *mutex)
{
	*mutex = false;
	return 0;
}

///////////////////////// Read/Write Lock /////////////////////////

// -1 locked for write, 0 unlocked, >0 locked for read by n threads
/** Read/write lock object */
typedef int pthread_rwlock_t;

#define PTHREAD_RWLOCK_INITIALIZER 0

typedef int pthread_rwlockattr_t;

/**
 *  @brief Create read/write lock object
 *
 *  @param rwlock Pointer to read/write lock object to initialise 
 *  @param attr Pointer to read/write lock attributes object (unused)
 *  @return Zero on success, non-zero on failure
 */
int pthread_rwlock_init(pthread_rwlock_t *rwlock,
                        const pthread_rwlockattr_t *attr)
{
	*rwlock = 0;
	return 0;
}


/**
 *  @brief Destroy read/write lock object
 *
 *  @param rwlock Pointer to read/write lock object to uninitialise 
 *  @return Zero on success, non-zero on failure
 */
int pthread_rwlock_destroy(pthread_rwlock_t *rwlock)
{
	return 0;
}                       


/**
 *  @brief Attempt to lock read/write lock object as writer
 *
 *  @param rwlock Pointer to read/write lock object to lock 
 *  @return Zero on success, EBUSY if locked, other on failure
 */
int pthread_rwlock_trywrlock(pthread_rwlock_t *rwlock)
{
	if( *rwlock != 0 )
		return EBUSY; // fail if locked
	*rwlock = -1;
	return 0;
}


/**
 *  @brief Lock read/write lock object as writer, blocking 
 *
 *  @param rwlock Pointer to read/write lock object to lock 
 *  @return Zero on success, non-zero on failure
 */
int pthread_rwlock_wrlock(pthread_rwlock_t *rwlock)
{
	sml_coroutine_wait( *rwlock == 0 ); // all threads waiting to write are waiting here
	*rwlock = -1;
	return 0;
}


/**
 *  @brief Attempt to lock read/write lock object as reader
 *
 *  @param rwlock Pointer to read/write lock object to lock 
 *  @return Zero on success, EBUSY if locked, other on failure
 */
int pthread_rwlock_tryrdlock(pthread_rwlock_t *rwlock)
{
	if( *rwlock == -1 )
		return EBUSY; // fail if locked
	(*rwlock)++;
	return 0;
}


/**
 *  @brief Lock read/write lock object as reader, blocking 
 *
 *  @param rwlock Pointer to read/write lock object to lock 
 *  @return Zero on success, non-zero on failure
 */
int pthread_rwlock_rdlock(pthread_rwlock_t *rwlock)
{
	sml_coroutine_wait( *rwlock != -1 ); // all threads waiting to read are waiting here
	(*rwlock)++;
	return 0;
}


/**
 *  @brief Unlock read/write lock object
 *
 *  @param rwlock Pointer to read/write lock object to lock 
 *  @return Zero on success, non-zero on failure
 */
int pthread_rwlock_unlock(pthread_rwlock_t *rwlock)
{
	if( *rwlock == -1 )
		*rwlock = 0;
	else
		(*rwlock)--;
	return 0;
}

///////////////////////// Condition variable /////////////////////////

/** Read/write lock object */
typedef struct
{
	int waiters;
	int triggers;
} pthread_cond_t;

#define PTHREAD_COND_INITIALIZER {0, 0}

typedef int pthread_condattr_t;

/**
 *  @brief Create condition variable object
 *
 *  @param cond Pointer to condition variable object to initialise 
 *  @param attr Pointer to condition variable attributes object (unused)
 *  @return Zero on success, non-zero on failure
 */
int pthread_cond_init(pthread_cond_t * cond,
                      const pthread_condattr_t * attr)
{
	cond->waiters = 0;
	cond->triggers = 0;
	return 0;
}
                   

/**
 *  @brief Destroy condition variable object
 *
 *  @param rwlock Pointer to condition variable object to uninitialise 
 *  @return Zero on success, non-zero on failure
 */
int pthread_cond_destroy(pthread_cond_t *cond)
{
	return 0;
}


/**
 *  @brief Wait on condition variable object
 *
 *  @param cond Pointer to condition variable object to wait on 
 *  @param mutex Pointer to mutex object 
 *  @return Zero on success, non-zero on failure
 */
int pthread_cond_wait(pthread_cond_t *cond,
					  pthread_mutex_t *mutex)
{
	// release the mutex
	*mutex = false;
	// Wait for a signal
	cond->waiters++;
	sml_coroutine_wait( cond->triggers != 0 );
	// consume the signal
    cond->triggers--;
	cond->waiters--;
	// wait for the mutex and re-lock
	sml_coroutine_wait( !(*mutex) );
	*mutex = true;
	return 0;
}	


/**
 *  @brief Signal condition variable object for one waiter
 *
 *  @param cond Pointer to condition variable object to signal
 *  @return Zero on success, non-zero on failure
 */
int pthread_cond_signal(pthread_cond_t *cond)
{
	cond->triggers++;
	// Since signal() is *intended* to allow other threads to run, yield here 
	// (unlike mutex unlock, which *could* allow other threads to run but is not 
	// intentionally put there to do so)
	sml_coroutine_yield(); 
	return 0;
}


/**
 *  @brief Signal condition variable object for all waiters
 *
 *  @param cond Pointer to condition variable object to signal
 *  @return Zero on success, non-zero on failure
 */
int pthread_cond_broadcast(pthread_cond_t *cond)
{
	cond->triggers = cond->waiters;
	// Since broadcast() is *intended* to allow other threads to run, yield here 
	// (unlike mutex unlock, which *could* allow other threads to run but is not 
	// intentionally put there to do so)
	sml_coroutine_yield(); 
	return 0;
}

#endif

