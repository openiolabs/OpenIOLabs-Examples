/** @file
 *
 *  @brief LWM2M core utilities
 * 
 * Copyright (c) Open IO Labs Ltd 2017
 * All Rights Reserved
 */

#ifndef __LWM2M_CORE_H
#define __LWM2M_CORE_H

#include <assert.h>

/** Create an object identifier (i.e. variable or field name) bound to an LWM2M object ID */
#define LWM2M_OBJECT_ID(ID)   ___IndexObjectIdentifier(index:ID)

/** Create an object identifier (i.e. variable or field name) bound to an LWM2M resource ID */
#define LWM2M_RESOURCE_ID(ID) ___IndexObjectIdentifier(index:ID)

/** Create an object identifier (i.e. variable or field name) bound to an LWM2M object ID and name */
#define LWM2M_OBJECT(ID, NAME)   ___IndexObjectIdentifier(index:ID, alias:NAME)

/** Create an object identifier (i.e. variable or field name) bound to an LWM2M resource ID and name */
#define LWM2M_RESOURCE(ID, NAME) ___IndexObjectIdentifier(index:ID, alias:NAME)

/** Register an LWM2M object with the server */
#define sml_lwm2m_register_object_id( OBJ, OBJ_ID ) \
{ \
  ___OMISend(request:"SM2M_AddObjects", client_handle:-1, str_payload:___NULL(), snippet_payload:___ISeq(OBJ), int_payload:___ISeq(OBJ_ID), float_payload:___ISeq()); \
  ___ListType_T(element_type:___NULL(), size:___NULL()) l = ___Receive(); \
  assert( l[0]=="OK" ); \
}

/** Register an LWM2M object with the server 
 * Note: ID is deduced as the identifier index/OMI handle for OBJ
 */
#define sml_lwm2m_register_object( OBJ ) \
{ \
  ___OMISend(request:"SM2M_AddObjects", client_handle:-1, str_payload:___NULL(), snippet_payload:___ISeq(OBJ), int_payload:___ISeq(), float_payload:___ISeq()); \
  ___ListType_T(element_type:___NULL(), size:___NULL()) l = ___Receive(); \
  assert( l[0]=="OK" ); \
}

/** Map an index into the user-defined object ID range (no registration required) */
#define user_object_id( OFS ) \
	((OFS)+26241)

#endif
