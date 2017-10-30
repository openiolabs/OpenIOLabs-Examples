
def StepperMotorInit(pinNum):
  ___Send(request="HW_StepperMotorInit", client_handle=-1, str_payload=___NULL(), int_payload=___ISeq(pinNum), float_payload=___ISeq())
  l = ___Receive()
  assert l[0]=="Value"
  return l[1]


# returns 0 on success, other values on error 
def StepperMotorStart(ID):
  ___Send(request="HW_StepperMotorStart", client_handle=ID, str_payload=___NULL(), int_payload=___ISeq(1), float_payload=___ISeq())
  l = ___Receive()
  assert l[0]=="Value"
  return l[1]


# returns 0 on success, other values on error 
def StepperMotorStop(ID):
  ___Send(request="HW_StepperMotorStop", client_handle=ID, str_payload=___NULL(), int_payload=___ISeq(), float_payload=___ISeq())
  l = ___Receive()
  assert l[0]=="Value"
  return l[1]
  
