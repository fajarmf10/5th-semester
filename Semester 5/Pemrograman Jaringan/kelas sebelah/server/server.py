import socket
import select
import sys
import os
import subprocess

addr = open("httpserver.conf","r").read()
server_config = addr.split(" ")
server_address = (server_config[1],int(server_config[3]))
server_socket=socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
server_socket.bind(server_address)
server_socket.listen(5)

input_socket=[server_socket]

try:
	while True:
		read_ready, write_ready, exception = select.select(input_socket, [], [])

		for sock in read_ready:
			if sock == server_socket:
				client_socket, client_address = server_socket.accept()
				input_socket.append(client_socket)
				
			else:
				data=sock.recv(4096)
				if not data:
					input_socket.remove(sock)
					sock.close()
					continue
				print(data)

				# response_data=''
				# for file in os.listdir("/"):
				# 	response_data+=(os.path.join("/",file)+'\n')


				request_header= data.split('\r\n')
				request_file = request_header[0].split()[1]
				response_data="<html>";

				if request_file=='/index.html' or request_file=="/":
					index=open("index.html","r")
					response_data=index.read()
					content_length = len(response_data)
					response_header = 'HTTP/1.1 200 OK\r\nContent-Type: text/html; charset=UTF-8\r\nContent-Length:' + str(content_length) + '\r\n\r\n'
				elif request_file=='/test.php':
					proc = subprocess.Popen("php test.php", shell=True, stdout=subprocess.PIPE)
					response_data+=proc.stdout.read()+'</html>'
					content_length = len(response_data)
					response_header = 'HTTP/1.1 200 OK\r\nContent-Type: text/html; charset=UTF-8\r\nContent-Length:' + str(content_length) + '\r\n\r\n'
				elif os.path.isdir(os.curdir+request_file):
					files = os.listdir(os.curdir+request_file)
					if request_file != "/":
						request_file = request_file + '/'
					for f in files:
						response_data+=("<a href="+ request_file + f + ">" + f + "</a><br>")
					response_data+="</html>"
					content_length = len(response_data)
					response_header = 'HTTP/1.1 200 OK\r\nContent-Type: text/html; charset=UTF-8\r\nContent-Length:' + str(content_length) + '\r\n\r\n'

				elif os.path.isfile(os.curdir+request_file):
					f=open(request_file[1:],"rb")
					response_data=f.read()
					content_length = len(response_data)
					response_header = 'HTTP/1.1 200 OK\r\nContent-Type: application/misc; charset=UTF-8\r\nContent-Length:' + str(content_length) + '\r\n\r\n'
				
				else:
					page404=open("404.html","r")
					response_data=page404.read()
					content_length = len(response_data)
					response_header = 'HTTP/1.1 404 Not Found\r\nContent-Type: text/html; charset=UTF-8\r\nContent-Length:' + str(content_length) + '\r\n\r\n'

				
				sock.sendall(response_header + response_data)

except KeyboardInterrupt:
	server_socket.close()
	sys.exit()