#
# SICM Client
#
# Copyright (c) Open IO Labs Ltd 2016
# All Rights Reserved
#

##
#  @file
#  @brief SICM application type definitions
#
# @{
#

#
# Important note: these structures are updated via OMI, which assigns 
# rather than rebinding. If constants like True and False are used, updates
# will alias into the underlying variables, so True and False may cease to be 
# 1 and 0, causing undesirable effects.
#


## Sampling rate (samples per millisecond) 
SICM_SAMPLING_RATE = 50

## What to do with read back data from FPGA 
RA_NONE=0          # no action
RA_START=1         # start a new report
RA_SAMPLE=2        # add data to the report (average of current as well as previously accumulated)
RA_SUB_SAMPLE=3    # accumulate data for averaging calc, but don't report
RA_COMPLETE=4      # end the report

## Scanning mode enumeration (matches server) 
HOPPING_SCAN_MODE   = 0
APPROACH_CURVE_MODE = 1
MANUAL_MODE         = 2
 
## Z Control mode enumeration (matches FPGA) 
ZCONTROL_HOPPING_MODE              = 1
ZCONTROL_MANUAL_MODE               = 2
ZCONTROL_ALTERNATING_CURRENT_MODE  = 3 # Not approach curve!!!!!!!!!!1
ZCONTROL_FAST_HOPPING              = 4
ZCONTROL_SICM_SEC_MODE             = 5

## Measurement states enumeration 
HS_STOPPED              = 0
HS_STARTING             = 1
HS_START_REQUESTED      = 2
HS_MEASURING            = 3
HS_STOP_REQUESTED       = 4
HS_COMPLETE             = 5

## Manual mode states enumeration 
M_STOPPED               = 0
M_START_REQUESTED       = 1
M_TO_SAFE_HEIGHT        = 2
M_TO_XY_POSITION        = 3
M_UP_DOWN_CONTROL       = 4

## Approach curve mode states enumeration 
AC_STOPPED             = 0
AC_START_REQUESTED     = 1
AC_TO_SAFE_HEIGHT      = 2
AC_TO_XY_POSITION      = 3
AC_APPROACH_DOWN       = 4
AC_APPROACH_UP         = 5
AC_STOP_REQUESTED      = 6
AC_COMPLETE            = 7

## Z axis states enumeration 
Undefined   = 0
NotImmersed = 1
Immersing   = 2
Retracting  = 3
Immersed    = 4
Approaching = 5
Withdrawing = 6
InControl   = 7

## Z axis commands enumeration 
NO_COMMAND            = 0
IMMERSE               = 1
APPROACH              = 2
IMMERSE_AND_APPROACH  = 3
WITHDRAW              = 4
STOP                  = 5

## Coarse motor X axis commands enumeration 
X_NoCommand     = 0
X_MOVE_POS      = 1
X_MOVE_NEG      = 2
X_STOP          = 3
X_Initialise    = 4
X_Calibrate     = 5
X_SetDI1        = 6
X_SetDI2        = 7
X_SetDI3        = 8
X_SetDI4        = 9
X_ClearDI1      = 10
X_ClearDI2      = 11
X_ClearDI3      = 12
X_ClearDI4      = 13

## Coarse motor Y axis commands enumeration 
Y_NoCommand     = 0
Y_MOVE_POS      = 1
Y_MOVE_NEG      = 2
Y_STOP          = 3
Y_Initialise    = 4
Y_Calibrate     = 5
Y_SetDI1        = 6
Y_SetDI2        = 7
Y_SetDI3        = 8
Y_SetDI4        = 9
Y_ClearDI1      = 10
Y_ClearDI2      = 11
Y_ClearDI3      = 12
Y_ClearDI4      = 13

## Coarse motor Z axis commands enumeration 
Z_NoCommand     = 0
Z_MOVE_POS      = 1
Z_MOVE_NEG      = 2
Z_STOP          = 3
Z_Initialise    = 4
Z_Calibrate     = 5

## Amplifier type enumeration
Internal            = 0
External            = 1

## Scan head type enumeration
ICNanoS2            = 0
ICNano2043          = 1
ICNano2223          = 2
ICNano2243          = 3
Manual              = 4

## Measurement mode enumeration 
UniDirectionalHopping   = 0
BiDirectionalHopping    = 1
    
class Range:
    def __init__(self):
        self.min = 0.0
        self.max = 0.0
        
class FPGALimits:
    def __init__(self):
        self.volts = Range()
        self.microns = Range()
        

# SICM instrument status 
class SICMStatus:
    def __init__(self):    
        self.acceptedScanMode = HOPPING_SCAN_MODE  ##< SICM scan mode (used by system) 

        self.xPos = 0.0                            ##< X position 
        self.yPos = 0.0                            ##< Y position 
        self.measuredXs = 0.0                      ##< Measured X sample
        self.measuredYs = 0.0                      ##< Measured Y sample
        self.measuredZp = 0.0                      ##< Measured Z sample
        
        self.isRunning = 0                         ##< Scan in progress flag
        self.isPaused = 0                          ##< Measurement paused flag
        self.isComplete = 0                        ##< Scan complete flag

        self.scanIndex = 0                         ##< Used during a scan to count the number of points scanned 
        self.scanX = 0                             ##< Surface position in X-axis
        self.scanY = 0                             ##< Scan complete flag

        self.iMean = 0.0                           ##< The average current as calculated by the FPGA 
        self.iRMS = 0.0                            ##< The current current as calculated by the FPGA 
        self.iStart = 0.0						   ##< Approach curve mode starting current 
        self.auxIn = 0.0                           ##< The aux input 

        self.hoppingState = HS_STOPPED             ##< Hopping scan mode state 
        self.zState = Undefined                    ##< Z axis state

        self.manualState = M_STOPPED               ##< Manual mode state 
        self.manualStep = 0                        ##< Manual mode step number 

        self.approachCurveState = AC_STOPPED       ##< APPROACH curve mode state 
        self.ZOfs = 0.0
        self.stateCounter = 0

        self.zCommand = NO_COMMAND                 ##< Most recent Z axis command from user
        self.coarseXCommand = X_NoCommand          ##< Most recent coarse motor X axis command from user
        self.coarseYCommand = Y_NoCommand          ##< Most recent coarse motor Y axis command from user
        self.coarseZCommand = Z_NoCommand          ##< Most recent coarse motor Z axis command from user

## SICM instrument configuration 
class SICMConfig:
    def __init__(self):
        self.scanMode = HOPPING_SCAN_MODE          ##< SICM scan mode (at UI) 
        
        #  Hardware Settings
        self.scanHeadType = ICNanoS2                    ##< Scan head type
        self.zp = FPGALimits()                          ##< Z pipette displacement and voltage limits 
        self.xs = FPGALimits()                          ##< X sample displacement and voltage limits 
        self.ys = FPGALimits()                          ##< Y sample displacement and voltage limits 
        self.zs = FPGALimits()                          ##< Z sample displacement and voltage limits 

        #  Pipette Bias
        self.amplifier = Internal                  ##< Headstage amplifier selection
        self.vBias = 0.0                           ##< Pipette bias voltage 
        self.vOffset = 0.0                         ##< Pipette offset voltage 
        
        #  Positioning Settings
        self.zApproachSpeed = 0                    ##< Speed of pipette while approaching 
        self.zImmerseSpeed = 0                     ##< Speed of pipette immersion 
        self.xySpeed = 0                           ##< Speed at which X/Y coarse motors will move 
        self.zWithdrawSpeed = 0                    ##< Speed of pippette when withdrawing 
        self.immerseThreshold = 0.0                ##< Immersion detection threshold 
        self.immerseDepth = 0.0                    ##< Immersion depth 
        self.zPiezoStopCriteria = 0.0              ##< ZP piezo stop criteria 
        self.coarseMotorsStopCriteria = 0.0        ##< Coarse Motors stop criteria 
        self.joystickEnable = bool(0)              ##< Joystick positioning enabled when true 

        #  Hopping Parameters
        self.hopHeight = 0                 ##< Minimum hop height 
        self.detectThreshold = 0           ##< Detection threshold 
        self.fallRate = 0                  ##< Fall rate 
        self.riseRate = 0                  ##< Rise rate 
        self.xyDelay = 0.0                 ##< Pre-measurement pause 
        self.measureDelay = 0              ##< Ion current measurement time 
        self.zBrakeOffset = 0.0            ##< Z brake retract 
        self.zHoppingLimits = Range()      ##< Z hopping distance limits 
        self.xIdlePos = 0.0                ##< Idling X position 
        self.yIdlePos = 0.0                ##< Idling Y position 

        #  Scan Area
        self.xOrigin = 0.0                       ##< Scan X origin 
        self.yOrigin = 0.0                       ##< Scan Y origin 
        self.scanWidth = 0.0                     ##< Scan area width 
        self.scanHeight = 0.0                    ##< Scan area height 
        self.widthPix = 0                        ##< Number of X measurement points 
        self.heightPix = 0                       ##< Number of Y measurement points 
        self.scanAngle = 0.0                     ##< Scan angle 
        self.measurementMode = UniDirectionalHopping ##< Measurement mode (scan pattern)
        self.pipetteLengthFactor = 0.0           ##< Pipette length ratio 

        # Manual Control Parameters 
        self.manualXPos = 0.0                    ##< Manual mode X position 
        self.manualYPos = 0.0                    ##< Manual mode Y position 
        self.manualZInit = 0.0                   ##< Manual mode start height 
        self.manualZOfs = 0.0                    ##< Manual mode Z height 
        self.manualZInc = 0.0                    ##< Manual mode Z step size 
        self.manualZRef = 0.0                    ##< Manual mode Zp-reference 
        self.manualActive = bool(1)              ##< Enable manual mode 

        # APPROACH Curve Control Parameters 
        self.approachIMin = 0.0 
        self.approachZMin = 0.0 
        self.approachSamples = 0

        self.hasChanged = bool(0)                ##< Set true after a config change 

## @}
