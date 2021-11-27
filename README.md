# sendudp command line utility

## Usage

```bash
beaglebone:~> ./sendudp
usage: ./sendudp <port> <payload>
```

## Example

```bash
beaglebone:~> ./sendudp 8000 "This is just a test"
```

And the output in tcpdump:

```bash
mars:~> sudo tcpdump -i enxd0374505d925 -n "broadcast" and port 8000 -s 1024 -X
tcpdump: verbose output suppressed, use -v or -vv for full protocol decode
listening on enxd0374505d925, link-type EN10MB (Ethernet), capture size 1024 bytes
06:51:50.676886 IP 192.168.2.104.43532 > 255.255.255.255.8000: UDP, length 19
	0x0000:  4500 002f 99db 4000 4011 ddd2 c0a8 0268  E../..@.@......h
	0x0010:  ffff ffff aa0c 1f40 001b 29c3 5468 6973  .......@..).This
	0x0020:  2069 7320 6a75 7374 2061 2074 6573 7400  .is.just.a.test.
	0x0030:  0000                                     ..
```	

## License

(c) 2021 Greg Herlein, released under the MIT-0 license
