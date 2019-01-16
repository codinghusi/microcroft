
import socket

port = 6522
contactPort = 6523
contactMessage = "new microcroft"
contactBackMessage = "alright!"



scanClient = socket.socket( socket.AF_INET, socket.SOCK_DGRAM )

contactServer = socket.socket( socket.AF_INET, socket.SOCK_DGRAM )
contactServer.bind( ( '', 6522 ) )

print( "scanning network..." )
scanClient.sendto( "hello".encode(), ( '10.1.146.255', 6523 ) )

print( "waiting for contact..." )
data, addr = contactServer.recvfrom( 1024 )

print( "found ip: ", addr )