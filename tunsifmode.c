// SPDX-License-Identifier: MIT
// SPDX-FileCopyrightText: 2022 SASANO Takayoshi <uaa@uaa.org.uk>

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/socket.h>
#if defined(__DragonFly__)
#include <net/tun/if_tun.h>
#else
#include <net/if_tun.h>
#endif
#include <net/if.h>

/*
 * OpenBSD have flags in struct tuninfo, but other BSDs not.
 * Use traditional socket interface to obtain flags for compatibility.
 */
static int get_ifr_flags(char *dev, int *v)
{
	int fd, ret = -1;
	struct ifreq ifr;
	char *p;

	if ((fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
		printf("get_ifr_flags: socket\n");
		goto fin0;
	}

	p = strrchr(dev, '/') + 1;
	if (p == NULL) p = dev;
	snprintf(ifr.ifr_name, IFNAMSIZ, "%s", p);
	if (ioctl(fd, SIOCGIFFLAGS, &ifr) < 0) {
		printf("get_ifr_flags: ioctl\n");
		goto fin1;
	}

	*v = ifr.ifr_flags;
	ret = 0;

fin1:
	close(fd);
fin0:
	return ret;
}

int main(int argc, char *argv[])
{
	int fd, flags;

	if (argc < 2) {
		printf("%s [device] [(ptp|bcast)]\n", argv[0]);
		goto fin0;
	}

	if ((fd = open(argv[1], O_RDWR)) < 0) {
		printf("device open error\n");
		goto fin0;
	}

	if (get_ifr_flags(argv[1], &flags) < 0)
		goto fin1;

	if (argc < 3) {
		if (flags & IFF_BROADCAST)
			printf("IFF_BROADCAST is set\n");
		if (flags & IFF_POINTOPOINT)
			printf("IFF_POINTOPOINT is set\n");
		goto fin1;
	}

#if defined(__FreeBSD__) || defined(__DragonFly__)
	/* only IFF_MULTICAST, IFF_BROADCAST, IFF_POINTOPOINT is valid */
	flags &= IFF_MULTICAST;
#else
	/* all bits are valid */
	flags &= ~(IFF_BROADCAST | IFF_POINTOPOINT);
#endif
	if (!strcmp(argv[2], "bcast")) {
		flags |= IFF_BROADCAST;
	} else if (!strcmp(argv[2], "ptp")) {
		flags |= IFF_POINTOPOINT;
	} else {
		printf("option error\n");
		goto fin1;
	}

	if (ioctl(fd, TUNSIFMODE, &flags) < 0) {
		printf("ioctl (TUNSIFMODE) error\n");
		goto fin1;
	}
fin1:
	close(fd);
fin0:
	return 0;
}
