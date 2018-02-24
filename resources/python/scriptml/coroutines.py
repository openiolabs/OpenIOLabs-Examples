## @file
#  @package coroutines
#
#  @brief Direct access to ScriptML coroutines
#
# Coroutines behave like simple and lightweight threads. However, a coroutine
# must call sml_coroutine_yield() or sml_coroutine_wait() regularly in 
# order to allow other coroutines to run.
# 
# Copyright (c) Open IO Labs Ltd 2016
# All Rights Reserved
#

## @brief Coroutine class
#
# Instantiate one of these for each coroutine you wish to create
class coroutine:
	##
	# @brief Create a coroutine
	#
	# @param entrypoint The entrypoint function
	# @param args List of arguments for the entrypoint function (will be unpacked into separate arguments)
    #
	def __init__(self, entrypoint, args):
		self.cob = ___Construct( object_type=___CoroutineType(), args_list=___ArgsList(args=___ISeq(entrypoint)), args_map=___ArgsMap(args=___IMap()), variadic_arg=args )

	##
	#  @brief Wait for the coroutine to exit
	# 
	#  @return Coroutine's result value
	#
	def join( self ): 
		___Wait( test=___IsCompleted(target=self.cob) )
		return ___PopResult(target=self.cob)

	##
	#  @brief Get id of the coroutine
	#
	#  @return The coroutine's id
	#
	def get_id( self ):
		return ___GetId(target=self.cob)


##
#  @brief Yield the current coroutine
#
def _yield():
	___Yield()

##
#  @brief Wait for the given function or lambda to return true
# 
#  @param test Lambda or function to wait for
#
# Note: the usual usage of wait is as follows:
#
# coroutines.wait( lambda: <expression to wait for> )
#
# In this case, the lambda is required so that the implmentation
# of wait() can work on the expression itself, rather than the value
# it evaluated to when wait() was called. wait() can then evaluate the 
# expression repeatedly and/or perform special spinless waiting 
# operations.
#
def wait( test ):
	___Wait( test=test() )

##
#  @brief Exit and delete the current coroutine
#
#  @param result Current coroutine's result value
#
def exit(result):
	___CoroutineExit( value=result )

##
#  @brief Get id of currently running coroutine
#
#  @return The current coroutine's id
#
def get_current_id():
	return ___GetId( target=___CurrentCoroutine() )

##
#  @brief Background all current coroutines
# 
# Note: this operation causes the script to exit as seen in the cloud-based user interface 
# but in fact all currently existant coroutines will be retained. This means that the user
# or system may run the script again and yields will still reach the previously existing 
# coroutines. Since the current coroutine is retained, this function returns.
#
def background():
	___Background()

