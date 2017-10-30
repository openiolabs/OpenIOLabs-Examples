/** @file
 * 
 *  @brief Posix sempahores
 *
 *  See https://www.mankier.com/0p/semaphore.h
 *  Implemented here: semaphore
 *
 * Copyright (c) Open IO Labs Ltd 2016
 * All Rights Reserved
 */
 
#ifndef __SEMAPHORE_H
#define __SEMAPHORE_H

#include <coroutines.h>
#include <stddef.h>

/** Semaphore object */
typedef unsigned int sem_t;

/**
 *  @brief Create semaphore object
 *
 *  @param sem Pointer to semaphore object to initialise 
 *  @param pshared Shared flag for semaphore (unused)
 *  @param value Semaphore's initial state (number of posts)
 *  @return Zero on success, non-zero on failure
 */
int sem_init(sem_t *sem, int pshared, unsigned int value)
{ 
	*sem = value;
	return 0; 
}


/**
 *  @brief Destroy semaphore object
 *
 *  @param sem Pointer to semaphore object to uninitialise 
 *  @return Zero on success, non-zero on failure
 */
int sem_destroy(sem_t *sem)
{ 
	return 0; 
}


/**
 *  @brief Get semaphore's state
 *
 *  @param sem Pointer to semaphore object to query 
 *  @param svasl Pointer to int to receive value 
 *  @return Zero on success, other on failure
 */
int sem_getvalue(sem_t *sem, int *sval)
{ 
	*sval = *sem;
	return 0; 
}


/**
 *  @brief Set semaphore's state to posted, possibly invoking other threads
 *
 *  @param sem Pointer to semaphore object to post 
 *  @return Zero on success, other on failure
 */
int sem_post(sem_t *sem)
{ 
	(*sem)++;
	// Since post() is *intended* to allow other threads to run, yield here 
	// (unlike mutex unlock, which *could* allow other threads to run but is not 
	// intentionally put there to do so)
	sml_coroutine_yield(); 
	return 0;
}


/**
 *  @brief Wait for semaphore to be posted, blocking
 *
 *  @param sem Pointer to semaphore object to wait for 
 *  @return Zero on success, other on failure
 */
int sem_wait(sem_t *sem)
{ 
	sml_coroutine_wait( *sem != 0 );
	(*sem)--;		
	return 0; 
}


/**
 *  @brief Attempt to wait for semaphore to be posted
 *
 *  @param sem Pointer to semaphore object to wait for 
 *  @return Zero on success, EBUSY if sempahore is not posted, other on failure
 */
int sem_trywait(sem_t *sem)
{ 
	if( *sem == 0 )
		return EBUSY; 
	(*sem)--;		
	return 0; 
}

#endif
