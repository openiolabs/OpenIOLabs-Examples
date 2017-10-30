##  @package led
#
#  @brief ScriptML client communications example
#
# Example code only. Demonstrates the use of intrinsics to create
# Send and Receive nodes and how to wrap them in straightforward 
# API functions.
# 
# Copyright (c) Open IO Labs Ltd 2016
# All Rights Reserved
#

def LEDInit(pinNum):
  ___Send(request="HW_LEDInit", client_handle=-1, str_payload=___NULL(), int_payload=___ISeq(pinNum), float_payload=___ISeq())
  l = ___Receive()
  assert l[0]=="Value"
  return l[1]


# returns 0 on success, other values on error 
def LEDTurnON(ID):
  ___Send(request="HW_LEDTurnON", client_handle=ID, str_payload=___NULL(), int_payload=___ISeq(), float_payload=___ISeq())
  l = ___Receive()
  assert l[0]=="Value"
  return l[1]


# returns 0 on success, other values on error 
def LEDTurnOFF(ID):
  ___Send(request="HW_LEDTurnOFF", client_handle=ID, str_payload=___NULL(), int_payload=___ISeq(), float_payload=___ISeq())
  l = ___Receive()
  assert l[0]=="Value"
  return l[1]
  
