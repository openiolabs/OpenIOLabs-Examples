import serial

h = serial.device()
	
text = h.read()

print text
	
h.close()
	
print "done"
