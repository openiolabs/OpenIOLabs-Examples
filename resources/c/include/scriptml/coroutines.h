/** @file
 *
 * @brief Direct access to ScriptML coroutines
 *
 * Coroutines behave like simple and lightweight threads. However, a coroutine
 * must call sml_coroutine_yield() or sml_coroutine_wait() regularly in 
 * order to allow other coroutines to run.
 * 
 * Copyright (c) Open IO Labs Ltd 2016
 * All Rights Reserved
 */

#ifndef __COROUTINE_H
#define __COROUTINE_H

#ifndef __SCRIPTML
#error "This header file can only be used with ScriptML" 
#endif

/// Id of the main coroutine
#define MAIN_COROUTINE_ID 0

/// Coroutine handle
typedef ___CoroutineType_T() *sml_coroutine_handle_t;

/**
 *  @brief Create a coroutine with 0 arguments
 *
 *  @param entrypoint Pointer to the entry point function
 *  @return Coroutine handle
 */
sml_coroutine_handle_t sml_coroutine_create_0( void (*entrypoint)() )
{
	return &___Construct( object_type:___CoroutineType(), args_list:___ArgsList(args:___ISeq(*entrypoint)), args_map:___ArgsMap(args:___IMap()), variadic_arg:___NULL() );
}

/**
 *  @brief Create a coroutine with 1 argument
 *
 *  @param entrypoint Pointer to the entry point function
 *  @param arg1 First argument to entry point function (any type)
 *  @return Coroutine handle
 */
sml_coroutine_handle_t sml_coroutine_create_1( void (*entrypoint)(___NULL_T() arg1), ___NULL_T() arg1 )
{
	return &___Construct( object_type:___CoroutineType(), args_list:___ArgsList(args:___ISeq(*entrypoint, arg1)), args_map:___ArgsMap(args:___IMap()), variadic_arg:___NULL() );
}


/**
 *  @brief Create a coroutine with 2 arguments
 *
 *  @param entrypoint Pointer to the entry point function
 *  @param arg1 First argument to entry point function (any type)
 *  @param arg2 Second argument to entry point function (any type)
 *  @return Coroutine handle
 */
sml_coroutine_handle_t sml_coroutine_create_2( void (*entrypoint)(___NULL_T() arg1, ___NULL_T() arg2), ___NULL_T() arg1, ___NULL_T() arg2 )
{
	return &___Construct( object_type:___CoroutineType(), args_list:___ArgsList(args:___ISeq(*entrypoint, arg1, arg2)), args_map:___ArgsMap(args:___IMap()), variadic_arg:___NULL() );
}


/**
 *  @brief Wait for a coroutine to exit
 * 
 *  @param coroutine Handle of coroutine to wait for
 *  @return Coroutine's result value
 */
___NULL_T() sml_coroutine_join( sml_coroutine_handle_t coroutine )
{
	___Wait( test:___IsCompleted(target:*coroutine) );
	return ___PopResult(target:*coroutine);
}


/**
 *  @brief Get id of a coroutine
 *
 *  @param coroutine Coroutine handle
 *  @return The coroutine's id
 */
int sml_coroutine_get_id( sml_coroutine_handle_t coroutine )
{
	return ___GetId(target:*coroutine);
}


/**
 *  @brief Yield the current coroutine
 */
void sml_coroutine_yield()
{
	___Yield();
}


/**
 *  @brief Wait for the given expression to evaluate true
 * 
 *  @param TEST Expression to wait for (evaluated multiple times; not side-effect-safe)
 *  
 * Note: a preprocessor macro is used to permit the Wait node to evaluate TEST
 * more than once (and in future to access the spinless-wait feature).
 */
#define sml_coroutine_wait(TEST) ___Wait(test:(TEST))


/**
 *  @brief Exit and delete the current coroutine
 *
 *  @param result Current coroutine's result value
 */
void sml_coroutine_exit( ___NULL_T() result )
{
	___CoroutineExit(value:result);
}


/**
 *  @brief Get id of currently running coroutine
 *
 *  @return The current coroutine's id
 */
int sml_coroutine_get_current_id() 
{
	return ___GetId( target:___CurrentCoroutine() );
}

#endif
