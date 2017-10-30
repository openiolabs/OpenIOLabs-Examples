/** @file
 *
 * @brief Streaming video to external server
 *
 * General:
 *
 * Capture a video stream from a video device such as a webcam and send
 * it to an HTTP server in the manner documented for stream.h
 *
 * Copyright (c) Open IO Labs Ltd 2017
 * All Rights Reserved
 */

#ifndef __VIDEO_H
#define __VIDEO_H

#include <unistd.h>

// Doing strings this way makes for slightly smaller scripts and faster
typedef ___StringType_T( size:___NULL() ) _str;
// OP-844 is to let this be a typedef
#define _data ___NULL_T()

/**
 *  @brief Open the device (only one per IMU). 
 *
 *  @param dev_path Path to video device
 *  @param format Format of video stream; use "avi" if unsure
 *  @param frame_rate Frame rate in frames per second
 *  @param width Width of frames in pixels
 *  @param height Height of frames in pixels
 *  @param bitrate Bitrate in bits per second
 *  @param dest_ip IP address of customer server
 *  @param dest_path HTTP path to POST/PUT to (typically a file path in some sandbox)
 *  @param append 1 to append to object to dest_path, 0 to overwrite
 */
void sml_video_stream_start( _str dev_path, _str format, int frame_rate, int width, int height, int bitrate, _str dest_ip, _str dest_path, bool append )  
{ 
	_str s = dest_ip+":"+dest_path+":"+dev_path+":"+format;
	___Send(request:"Video_Start", client_handle:-1, str_payload:s, int_payload:___ISeq(frame_rate, width, height, bitrate, append), float_payload:___ISeq()); 
	___ListType_T(element_type:___NULL(), size:___NULL()) l = ___Receive(); 
	assert( l[0]=="OK" ); 
}


/**
 *  @brief Close a device. 
 */
void sml_video_stream_stop()
{
	___Send(request:"Video_Stop", client_handle:-1, str_payload:___NULL(), int_payload:___ISeq(), float_payload:___ISeq()); 
	___ListType_T(element_type:___NULL(), size:___NULL()) l = ___Receive(); 
	assert( l[0]=="OK" ); 
}

#endif
 
