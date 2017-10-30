## @file
#  @package lwm2m_core
#
#  @brief LWM2M core utilities
#
# Copyright (c) Open IO Labs Ltd 2016
# All Rights Reserved
#

##
# @brief Register an LWM2M object or objects with the server, explicit ID
#
# @param obj A lambda evaluating to the object to register, which must be a dict or sequence of dicts
# @param obj_id Object ID to use
#
def register_object_id( obj, obj_id ):
	___OMILambdaSend(request="SM2M_AddObjects", client_handle=-1, snippet_payload=___ISeq(obj), int_payload=___ISeq(obj_id))
	l = ___Receive()
	assert l[0]=="OK"
	
	
##
# @brief Map an index into the user-defined object ID range
#
# @param ofs user-defined object index, starting at 0
#
# Note: no registration required in this range
def user_object_id( ofs ):
	return ofs+26241

