import struct
import socket


s=socket.socket(socket.AF_INET, socket.SOCK_DGRAM, socket.getprotobyname("udp"))

s.connect(("225.2.3.4",5444))
a1=socket.inet_pton(socket.AF_INET, "225.2.3.4")
a2=struct.pack("=I",0)
aa=a1+a2
b=struct.pack("i",5)
s.setsockopt(socket.IPPROTO_IP, socket.IP_MULTICAST_TTL, b)
s.setsockopt(socket.IPPROTO_IP, socket.IP_ADD_MEMBERSHIP, aa)

s.send("Hello, World")

