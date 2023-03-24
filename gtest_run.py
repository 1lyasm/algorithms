import os
import sys

def main():
    if sys.platform.startswith("win"):
        os.system("build/test_dsa.exe")
    elif sys.platform.startswith("linux"):
        os.system("cd build && ./test_dsa && cd ..")

if __name__ == "__main__": main()