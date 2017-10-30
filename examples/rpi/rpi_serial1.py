import serial

h = serial.device()

h.write( "hello\n" )

h.close()

print "done"
