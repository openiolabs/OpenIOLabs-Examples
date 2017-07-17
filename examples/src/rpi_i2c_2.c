#include <scriptml/i2c.h>
#include <scriptml/max518.h>


int main()
{
	sml_max518_t dac = sml_max518_create( sml_i2c_open( "/dev/i2c-1" ), 0 );
	int l=0;
	while(1)
	{
		for( ; l<255; l++ )
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

