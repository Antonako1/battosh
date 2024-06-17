import sys, os

path_to_battosh_hxx = "./_source/battosh.hxx"
battosh_search_for  = "#define VERSION             "

path_to_nsi         = "./release_building/installer.nsi"
nsi_search_for      = "!define VERSION "

if len(sys.argv) < 2:
    print("Usage: updateversion.py <version>")
    sys.exit(1)

# get version
version = sys.argv[1]
version = '"' + version + '"'

for path, search_for in [(path_to_battosh_hxx, battosh_search_for), (path_to_nsi, nsi_search_for)]:
    with open(path, "r") as f:
        lines = f.readlines()

    for i, line in enumerate(lines):
        if line.startswith(search_for):
            lines[i] = search_for + version + "\n"
            break

    with open(path, "w") as f:
        f.writelines(lines)