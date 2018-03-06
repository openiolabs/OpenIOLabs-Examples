#
# SICM Client Script API
#
# Copyright (c) Open IO Labs Ltd 2016
# All Rights Reserved
#

##
#  @file
#  @brief SICM Conversion untility functions
#  @addtogroup sicm-api-fpga
#
#  This header file provides functions to convert 
#
#

import sicm.SICMTypes

##
#  @brief X sample microns to volts
#
#  @param xm X sample in microns
#  @return X sample in volts
#
def sml_sicm_xsmtov(config, xm):
    xpbm = config.xs.microns.min
    xptm = config.xs.microns.max
    xpbv = config.xs.volts.min
    xptv = config.xs.volts.max

    xvpm = (xptv - xpbv) / (xptm - xpbm)

    return xpbv + ((xm - xpbm) * xvpm)
      
##
#  @brief Y sample microns to volts
#
#  @param ym Y sample in microns
#  @return Y sample in volts
#
def sml_sicm_ysmtov(config, ym):  
    ypbm = config.ys.microns.min
    yptm = config.ys.microns.max
    ypbv = config.ys.volts.min
    yptv = config.ys.volts.max

    yvpm = (yptv - ypbv) / (yptm - ypbm)

    return ypbv + ((ym - ypbm) * yvpm)
      
##
#  @brief Z pipette microns to volts
#
#  @param zm Z sample in microns
#  @return Z sample in volts
#
def sml_sicm_zpmtov(config, zm):     
    zpbm = config.zp.microns.min
    zptm = config.zp.microns.max
    zpbv = config.zp.volts.min
    zptv = config.zp.volts.max
    
    zvpm = (zptv - zpbv) / (zptm - zpbm)

    if zm < zpbm:
        zm = zpbm
    elif zm > zptm:
        zm = zptm
        
    return zpbv + ((zm - zpbm) * zvpm)
      

def sml_sicm_calculate_hop_height( x, y ):
    ___Send(request="SICM_Calculate_HopHeight", client_handle=___NULL(), str_payload=___NULL(), int_payload=___ISeq(x, y), float_payload=___ISeq())
    l = ___Receive()
    
    # Check that the response message was as expected - we require OK
    assert l[0]=="Value"
    return l[1]
      