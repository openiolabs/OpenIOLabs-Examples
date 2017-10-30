
def ServoMotorInit(pinNum):
  ___Send(request="HW_ServoMotorInit", client_handle=-1, str_payload=___NULL(), int_payload=___ISeq(pinNum), float_payload=___ISeq())
  l = ___Receive()
  assert l[0]=="Value"
  return l[1]


# returns 0 on success, other values on error 
def ServoMotorStart(ID):
  ___Send(request="HW_ServoMotorStart", client_handle=ID, str_payload=___NULL(), int_payload=___ISeq(), float_payload=___ISeq())
  l = ___Receive()
  assert l[0]=="Value"
  return l[1]


# returns 0 on success, other values on error 
def ServoMotorStop(ID):
  ___Send(request="HW_ServoMotorStop", client_handle=ID, str_payload=___NULL(), int_payload=___ISeq(), float_payload=___ISeq())
  l = ___Receive()
  assert l[0]=="Value"
  return l[1]
  
