
import socket
import sys

print( "starting server..." )

sock = socket.socket( socket.AF_INET, socket.SOCK_STREAM )
address = ( '', 6522 )
sock.bind( address )
sock.listen()

print( "started!" )

while True:
    print( "waiting for a connection" )
    connection, client_address = sock.accept()
    print( "got a connection" );
