# Author Martin Chukaleski 29/04
# Simple script that detects the ip on the machine and replaces the docker compose 
# file with the correct ip argument

import socket

def get_ip_address():
    s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    s.connect(("8.8.8.8", 80))
    s.close
    return s.getsockname()[0]

def save_new_arg():
    arg = "--ip="
    ip = get_ip_address()
    ip_arg = arg+ip
    file = open("ip_arg.txt","w+")
    file.write(ip_arg)

def get_new_arg():
    arg = "--ip="
    ip = get_ip_address()
    ip_arg = arg+ip
    return ip_arg

def get_old_arg():
    f = open("ip_arg.txt",'r')
    fline = f.readline().rstrip()
    return fline

def replace_in_compose():
    f = open("docker-compose.yml",'r')
    filedata = f.read()
    f.close()
    #print(filedata)
    old = get_old_arg()
    new = get_new_arg()
    newdata = filedata.replace(old,new)

    f = open("docker-compose.yml",'w')
    f.write(newdata)
    f.close() 
    save_new_arg()
    #print(newdata)   

replace_in_compose()


