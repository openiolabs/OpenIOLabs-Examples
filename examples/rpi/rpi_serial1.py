import serial

h = serial.Serial("/dev/ttyUSB0")
h.open()

h.write( "hello\n" )

print h.read(6)

h.close()

print "done"
