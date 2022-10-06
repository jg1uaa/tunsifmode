# tunsifmode

---
## Description

set IFF_BROADCAST or IFF_POINTOPOINT to tun(4) device for *BSD

## Usage

```
# ./tunsifmode
./tunsifmode [device] [(ptp|bcast)]
#
```

### Example

#### FreeBSD
```
# ifconfig tun0 create
# ifconfig tun0 192.168.200.1 192.168.200.2
# ifconfig tun0
tun0: flags=8051<UP,POINTOPOINT,RUNNING,MULTICAST> metric 0 mtu 1500
        options=80000<LINKSTATE>
        inet 192.168.200.1 --> 192.168.200.2 netmask 0xffffff00
        groups: tun
        nd6 options=29<PERFORMNUD,IFDISABLED,AUTO_LINKLOCAL>
# ifconfig tun0 down
# ./tunsifmode /dev/tun0 bcast
# ifconfig tun0
tun0: flags=8002<BROADCAST,MULTICAST> metric 0 mtu 1500
        options=80000<LINKSTATE>
        groups: tun
        nd6 options=29<PERFORMNUD,IFDISABLED,AUTO_LINKLOCAL>
# 
```

#### DragonflyBSD
```
# ifconfig tun0 create 
# ifconfig tun0 192.168.200.1 192.168.200.2
# ifconfig tun0
tun0: flags=8051<UP,POINTOPOINT,RUNNING,MULTICAST> metric 0 mtu 1500
        inet 192.168.200.1 --> 192.168.200.2 netmask 0xffffff00
        inet6 fe80::3c08:d2d4:7cbf:1e5a%tun0 prefixlen 64 scopeid 0x3
        groups: tun
# ifconfig tun0 down
# ./tunsifmode /dev/tun0 bcast
# ifconfig tun0
tun0: flags=8002<BROADCAST,MULTICAST> metric 0 mtu 1500
        inet 192.168.200.1 netmask 0xffffff00 broadcast 192.168.200.2
        inet6 fe80::3c08:d2d4:7cbf:1e5a%tun0 prefixlen 64 scopeid 0x3
        groups: tun
#
```

#### NetBSD
```
# ifconfig tun0 create
# ifconfig tun0 192.168.200.1 192.168.200.2
# ifconfig tun0
tun0: flags=0x51<UP,POINTOPOINT,RUNNING> mtu 1500
        status: down
        inet 192.168.200.1/32 -> 192.168.200.2 flags 0x4<DETACHED>
# ifconfig tun0 down
# ./tunsifmode /dev/tun0 bcast
# ifconfig tun0
tun0: flags=0x42<BROADCAST,RUNNING> mtu 1500
        status: down
        inet 192.168.200.1/32 broadcast 192.168.200.2 flags 0x4<DETACHED>
#
```

#### OpenBSD
```
# ifconfig tun0 create
# ifconfig tun0 192.168.200.1 192.168.200.2
# ifconfig tun0
tun0: flags=8051<UP,POINTOPOINT,RUNNING,MULTICAST> mtu 1500
        index 5 priority 0 llprio 3
        groups: tun
        status: down
        inet 192.168.200.1 --> 192.168.200.2 netmask 0xffffff00
# ifconfig tun0 down
# ./tunsifmode /dev/tun0 bcast                                  
# ifconfig tun0
tun0: flags=8002<BROADCAST,MULTICAST> mtu 1500
        index 5 priority 0 llprio 3
        groups: tun
        status: down
        inet 192.168.200.1 netmask 0xffffff00 broadcast 192.168.200.2
# 
```

## Limitation

There is no TUNSIFMODE or alike ioctl, no plan to support Linux.

## License

MIT License
