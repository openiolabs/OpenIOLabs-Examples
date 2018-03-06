## @file
#
# @brief Special functions for managing persistent flags.
# 
# API for controlling pipette fine movement and sampling. The API controls
# both simultaeusly in order to ensure correct alignment of FPGA output data.
#
# Copyright (c) Open IO Labs Ltd 2018
# All Rights Reserved
#


import sicm.SICMTypes
import coroutines


def Control_Initialise():
    if TRACE_DESTATE:
        print "Enter Control_Initialise() in #%d\n", sml_coroutine_get_current_id()
          # Switch the client into scripted operation
    ___Send(request="SICM_Control_EnableScript", client_handle=___NULL(), str_payload=___NULL(), int_payload=___ISeq(1), float_payload=___ISeq())
    l = ___Receive()
    
    # Check that the response message was as expected - we require OK
    assert l[0]=="OK"
    
    if TRACE_DESTATE:
        print "Control_Initialise() backgrounding in #%d\n", sml_coroutine_get_current_id()
          
    # yield locally; exit in client. Client will proceed into control loop, and the re-enter via ScanManager_Run()
    sml_coroutine_background()
    
    if TRACE_DESTATE:
        print "Exit Control_Initialise() in #%d\n", sml_coroutine_get_current_id()
            

def Control_SetMode( mode ): 
    ___Send(request="SICM_Control_SetMode", client_handle=___NULL(), str_payload=___NULL(), int_payload=___ISeq(mode), float_payload=___ISeq())
    l = ___Receive()
    
    # Check that the response message was as expected - we require OK
    assert l[0]=="OK"
      

def Control_Start3D( width, height ):      
    ___Send(request="SICM_Control_Start3D", client_handle=___NULL(), str_payload=___NULL(), int_payload=___ISeq(width, height), float_payload=___ISeq())
    l = ___Receive()
    
    # Check that the response message was as expected - we require OK
    assert l[0]=="OK"
      

def Control_Start2D( num_samples ):   
    ___Send(request="SICM_Control_Start2D", client_handle=___NULL(), str_payload=___NULL(), int_payload=___ISeq(num_samples), float_payload=___ISeq())
    l = ___Receive()
    
    # Check that the response message was as expected - we require OK
    assert l[0]=="OK"
      

def Control_Sample3D( x, y ):   
    ___Send(request="SICM_Control_Sample", client_handle=___NULL(), str_payload=___NULL(), int_payload=___ISeq(x, y), float_payload=___ISeq())
    l = ___Receive()
    
    # Check that the response message was as expected - we require OK
    assert l[0]=="OK"
      


def Control_SubSample3D( x, y ):     
    ___Send(request="SICM_Control_SubSample", client_handle=___NULL(), str_payload=___NULL(), int_payload=___ISeq(x, y), float_payload=___ISeq())
    l = ___Receive()
    
    # Check that the response message was as expected - we require OK
    assert l[0]=="OK"
      

def Control_Sample2D():    
    ___Send(request="SICM_Control_Sample", client_handle=___NULL(), str_payload=___NULL(), int_payload=___ISeq(0, 0), float_payload=___ISeq())
    l = ___Receive()
    
    # Check that the response message was as expected - we require OK
    assert l[0]=="OK"
      


def Control_SubSample2D():      
    ___Send(request="SICM_Control_SubSample", client_handle=___NULL(), str_payload=___NULL(), int_payload=___ISeq(0, 0), float_payload=___ISeq())
    l = ___Receive()
    
    # Check that the response message was as expected - we require OK
    assert l[0]=="OK"
      

def Control_Complete():  
    ___Send(request="SICM_Control_Complete", client_handle=___NULL(), str_payload=___NULL(), int_payload=___ISeq(), float_payload=___ISeq())
    l = ___Receive()
    
    # Check that the response message was as expected - we require OK
    assert l[0]=="OK"
      

def Control_Iterate():    
    if TRACE_DESTATE:
        print "Enter Control_Iterate() in", sml_coroutine_get_current_id()
      
    sml_coroutine_yield() # yields to iterate_state_machine() which exits allowing client to proceed

    if TRACE_DESTATE:
        print "Exit Control_Iterate() in", sml_coroutine_get_current_id()
                

def ScanManager_Run(): # invoked repeatedly by client (full invocation using RunToEnd())      
    if TRACE_DESTATE:
        print "Enter ScanManager_Run() in", sml_coroutine_get_current_id()
      
    sml_coroutine_yield() # yields to main() coroutine that backgrounded itself earlier

    if TRACE_DESTATE:
        print "Exit ScanManager_Run() in", sml_coroutine_get_current_id()
      
    return # control returns to client when this coroutine exits (initial coroutine for the invocation)
      