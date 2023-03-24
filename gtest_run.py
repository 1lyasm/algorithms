import os
import sys

def main():
    if sys.platform.startswith("win"):
        os.system("test_dsa")
    elif sys.platform.startswith("linux"):
        os.system("./test_dsa")

if __name__ == "__main__": main()