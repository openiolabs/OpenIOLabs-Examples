/* Test Script that Pushes a JSON text Blob using C */
#include <lwm2m.h> // lwm2m.h is auto-generated

#include <stdint.h>
#include <test_print.h>
#include <stdio.h>

/* Define an instance of a client Push LWM2M Text Object */ 
LWM2M_OpenIO_Clientpushed_text_object_T  LWM2M_OpenIO_Clientpushed_text_object;

int main()
{
printf( "Point 1\n" );

/* Define the Text Object in json format to push to the text Object on the server */
char *strToSend ="{\"objectName\": \"ObjectText\", \"objectText\": \"Hello ScriptML\", \"tags\": [\"my_text_tag\"], \"pushToUI\": true}";

/* Link the text fields to the Client text Object to the Server */ 
LWM2M_OpenIO_Clientpushed_text_object.Object = strToSend; 

/* Register the Client Push Text Object with the Server */
sml_lwm2m_register_object(LWM2M_OpenIO_Clientpushed_text_object);

printf( "Point -1\n" );
return 0;
}
