import os
import sys

if sys.platform.startswith("win"):
        os.system("build/test_dsa.exe")
elif sys.platform.startswith("linux"):
    os.system("cd build && ./test_dsa && cd ..")
