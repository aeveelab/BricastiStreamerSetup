#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <unistd.h>
#include <io.h>
#include <windows.h>

int parse_ping_for_IP(char * buffer, FILE * fp)
{
	char buff_1[100] = { '0' };
	char * start_ptr = NULL;
	char * end_ptr = NULL;
	char * tracker;
	int i = 0;

	// setup ptrs to the IP address
	fread(buff_1, 99, 1, fp);
	printf("\n\n this is the buffer %s\n\n\n", buff_1);

	// check if no streamer is connected to network
	start_ptr = strstr(buff_1, "could not find");
	if (start_ptr != NULL) return 0;

	// get ptrs to IP address in ping response
	start_ptr = strstr(buff_1, "[");
	end_ptr = strstr(buff_1, "]");

	// adjust end_ptr and store IP address
	end_ptr--;
	while (start_ptr++ != end_ptr)
	{
		buffer[i++] = *start_ptr;
	}
	strcat(buffer, ":8080");
	//    printf("this is IP buffer: %s\n\n", buffer);

	return 1;
}

int main(void)
{
	char buffer[40] = { "start /max http://" };			// prebuild the launch web page cmd string
	FILE *fp;

	// create and open text file
	system("an_5p > temp.txt");
	if ((fp = fopen("temp.txt", "r")) == NULL) return (-1);

	// ping and check for any streamer, exit if not
	system("/WINDOWS/System32/ping.exe -a AeVeeStreamer -4 > temp.txt");		// was AeVeeStreamer : ping host/domain for IPv4 IP address -a maybe reverse dns lookup
	//    system("ping -a AeVeeStreamer > temp.txt");
 
	// streamer present get IP address(s)
	parse_ping_for_IP(&buffer[18], fp);
	printf("this is IP buffer: %s\n\n", buffer);
//	Sleep(10000);

	// execute full web page launch cmd
	system(buffer);

	// close and delete text file
	fclose(fp);
	system("del temp.txt");
	return 0;
}

