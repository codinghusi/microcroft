
import socket
import threading

normalPort = 6522
contactPort = 6523
contactMessage = "new microcroft"

running = True

print( "starting normal server..." )

normalServer = socket.socket( socket.AF_INET, socket.SOCK_STREAM )
address = ( '', 6522 )
normalServer.bind( address )
normalServer.listen()

print( "started normal server!" )

print( "starting contact server..." )

contactServer = socket.socket( socket.AF_INET, socket.SOCK_DGRAM )
address = ( '', 6523 )
contactServer.bind( address )

contactClient = socket.socket( socket.AF_INET, socket.SOCK_DGRAM )

def handleNormalClients():
    while running:
        print( "waiting for a connection" )
        connection, client_address = normalServer.accept()
        print( "got a connection" )

def handleContactClients():
    while running:
        print( "waiting for a scan" )
        data, addr = contactServer.recvfrom( 1024 )
        print( "a microcroft scanned the network" )
        print(addr)
        contactClient.sendto( "alright!".encode(), ( addr[0], normalPort ) )

threadNormal = threading.Thread( target = handleNormalClients )
threadContact = threading.Thread( target = handleContactClients )
threadNormal.start()
threadContact.start()

print( "started contact server!" )

input( "press any key to stop the server\n" )

running = False