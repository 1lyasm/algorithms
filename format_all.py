import os

for subdir, dirs, _ in os.walk("."):
  for dir in dirs:
    if dir != "." and dir != "..":
      for _, _, files in os.walk(f"./{dir}"):
        for file_ in files:
          if os.path.splitext(file_)[1] in [".cpp", ".c", ".h", ".java", ".cppm"]:
            print(f"formatting {file_}")
            os.system(f"clang-format -i -style=Google {dir}/{file_}")
