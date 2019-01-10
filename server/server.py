
import socket
import thread

port = 6522
contactPort = 6523
contactMessage = "new microcroft"

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
    while True:
        print( "waiting for a connection" )
        connection, client_address = sock.accept()
        print( "got a connection" )

def handleContactClients():
    while True:
        data, addr = contactServer.recvfrom( len(contactMessage) )
        print( "a microcroft scanned the network" )
        contactClient.sendto( "allright!", addr, normalPort )

thread.start_new_thread( handleNormalClients, ( "normalClientsThread" ) )
thread.start_new_thread( handleNormalClients, ( "contactClientsThread" ) )

print( "started contact server!" )
