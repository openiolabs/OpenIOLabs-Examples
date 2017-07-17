#include <scriptml/i2c.h>
#include <scriptml/max518.h>

#define OPTIMISED

#ifdef OPTIMISED

int main()
{
	sml_max518_t dac = sml_max518_create( sml_i2c_open( "/dev/i2c-1" ), 0 );
    sml_i2c_t dev = *(dac.piic);
    
    struct i2c_msg msg0;
	msg0.addr = dac.addr;
	msg0.flags = 0;
	char b0[2];
	msg0.buf = b0;
    msg0.len = 2;
	struct i2c_rdwr_ioctl_data rdwr_arg0;
	rdwr_arg0.msgs = &msg0;
	rdwr_arg0.nmsgs = 1;
    _data data0 = &rdwr_arg0;
    b0[0] = 0; 

    struct i2c_msg msg1;
	msg1.addr = dac.addr;
	msg1.flags = 0;
	char b1[2];
	msg1.buf = b1;
    msg1.len = 2;
	struct i2c_rdwr_ioctl_data rdwr_arg1;
	rdwr_arg1.msgs = &msg1;
	rdwr_arg1.nmsgs = 1;
    _data data1 = &rdwr_arg1;
    b1[0] = 1; 

	int l=0;
	while(1)
	{
		for( l=0; l<255; l++ )
		{
            b0[1] = l;
            ___Ioctl( device:dev, request:I2C_RDWR, data:data0 );	
            b1[1] = 255-l;
            ___Ioctl( device:dev, request:I2C_RDWR, data:data1 );	
		}
		
		for( l=255; l>0; l-- )
		{
            b0[1] = l;
            ___Ioctl( device:dev, request:I2C_RDWR, data:data0 );	
            b1[1] = 255-l;
            ___Ioctl( device:dev, request:I2C_RDWR, data:data1 );	
		}
	}
	return 0;
}

#else

// Original version
int main()
{
	sml_max518_t dac = sml_max518_create( sml_i2c_open( "/dev/i2c-1" ), 0 );
	int l=0;
	while(1)
	{
		for( ; l<255; l++ )
		{
			sml_max518_set_level( dac, 0, l );
			sml_max518_set_level( dac, 1, 255-l );
		}
		
		for( ; l>0; l-- )
		{
			sml_max518_set_level( dac, 0, l );
			sml_max518_set_level( dac, 1, 255-l );
		}
	}
	return 0;
}

#endif
