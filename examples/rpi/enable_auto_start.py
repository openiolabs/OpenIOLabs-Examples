import auto_start

print "top level"	

auto_start.enable()

print "Enabled auto-start"

import persistent

# General flags test; write after read so value only seen on second run
print persistent.flag("abc").read_str()
persistent.flag("abc").write_float(2.34)
