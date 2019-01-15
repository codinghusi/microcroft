
import socket

port = 6522
contactPort = 6523
contactMessage = "new microcroft"

print( "scanning network..." )

scanClient = socket.socket( socket.AF_INET, socket.SOCK_STREAM )
address = ( '192.168.178.255', 6523 )
scanClient.sendto( "hello".encode(), address )

print( "waiting for contact..." )

contactServer = socket.socket( socket.AF_INET, socket.SOCK_DGRAM )
address = ( '', 6522 )
contactServer.bind( address )

data, addr = contactServer.recvfrom(1024)

print( "found ip: ", addr )