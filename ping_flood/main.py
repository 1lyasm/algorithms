#!/usr/bin/python3

import os
import threading

def ping(command):
    os.system(command)

def main():
    ip = None
    with open("in.txt", "r") as f:
        ip = f.read()
    command = "ping " + ip
    iter_count = 1000
    for i in range(iter_count):
        threading.Thread(target=ping, args=(command,)).start()


if __name__ == "__main__":
    main()
