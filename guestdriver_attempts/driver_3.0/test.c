#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define DEV_FILE "/dev/hello"

int main( int argc, char** argv){

	int rd, length;
	int stat;
	char command;
	char buffer[100];
	bzero(buffer, 100);
	rd = open( DEV_FILE, O_RDWR);
	if ( rd < 0){
		perror("opening device file");
	}
	printf("Please, enter command : w, r\n");
	scanf("%c", &command);
	switch(command){
	case 'r':
		length = read( rd, buffer, 100);
		if ( length < 0) perror("readind");
		printf("length = %d\nline : %s\n", length, buffer );
		break;
	case 'w':
		printf("Enter your string please : \n");
		scanf("%s", buffer );
		length = write( rd, buffer, strlen(buffer));
		if ( length < 0) perror("writing");
		break;
	default:
		printf("Format is uncorrect. Please, try again");
	}


}

