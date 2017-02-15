#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <net/if.h>
int
main(int argc, char *argv[])
{
	struct ip_mreqn mreqn;
	int s;
	if (argc != 3) {
		fprintf(stderr, "usage: %s <dev> <group>\n", argv[0]);
		exit(1);
	}
	s = socket(PF_INET, SOCK_DGRAM, 0);
	if (s < 0) {
		perror("socket");
		exit(1);
	}
	memset(&mreqn, 0, sizeof(mreqn));
	mreqn.imr_ifindex = if_nametoindex(argv[1]);
	if (!mreqn.imr_ifindex) {
		fprintf(stderr, "%s: \"%s\" invalid interface\n", argv[0],
		        argv[1]);
		exit(1);
	}
	if (inet_pton(AF_INET, argv[2], &mreqn.imr_multiaddr) <= 0) {
		fprintf(stderr, "%s: \"%s\" invalid group address\n", argv[0],
		        argv[2]);
		exit(1);
	}
	if (setsockopt(s, SOL_IP, IP_ADD_MEMBERSHIP, &mreqn,sizeof mreqn) < 0) {
		perror("IP_ADD_MEMBERSHIP");
		exit(1);
	}
	printf("joined group %s on %s (pausing...)\n", argv[2], argv[1]);
	fflush(stdout);
	pause();
	exit(0);
}

