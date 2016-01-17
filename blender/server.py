import socket
import sys
import random
import time

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server_address = ('localhost', 10000)
print >>sys.stderr, 'starting up on %s port %s' % server_address

sock.bind(server_address)

sock.listen(1)

import json
data = []
encoded_data = json.dumps( data )
print encoded_data

while True:
    # Wait for a connection
    print >>sys.stderr, 'waiting for a connection'
    connection, client_address = sock.accept()
    try:
        print >>sys.stderr, 'connection from', client_address

	while True:
#		a = connection.recv(1)
	        print >>sys.stderr, 'sending data to the client'

		#generate new points
		data.append( [random.randint(0,7), random.randint(0,7), random.randint(0,7)] )
		
		encoded_data = json.dumps( data )
		print encoded_data
	        connection.sendall(encoded_data + '\n' )
		time.sleep(1)
    finally:
        # Clean up the connection
        connection.close()
