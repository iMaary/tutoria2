#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>

int main(void) {
	int pipeFileDescriptors[2];
	char writeMessages[2][20] = {"Message 1", "Message 2"};
	char readMessages[20];

	int returnPipe = pipe(pipeFileDescriptors);

	if (returnPipe == -1) {
		printf("Error to create pipe!\n");
		return 1;
	}

	printf("\n## processo pai ##\n");
	for (int i = 0; i < 2; i++) {
		printf("Writing: %s\n", writeMessages[i]);
		write(pipeFileDescriptors[1], writeMessages[i], sizeof(char) * 20);
	}

	pid_t np;
	np = fork();
	if (np == 0) {
		printf("\n## processo filho ##\n");
		for (int i = 0; i < 2; i++) {
			read(pipeFileDescriptors[0], readMessages, sizeof(char) * 20);
			printf("Reading: %s\n", readMessages);
		}
		return 0;
	}
	wait(NULL);
	printf("\n## sai ai bro :) ##\n");
	
	return 0;
}
