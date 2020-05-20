import os
import subprocess
import shutil
import sys

import build

TOWNSTYPE="MX"

THISFILE=os.path.realpath(__file__)
THISDIR=os.path.dirname(THISFILE)
BUILDDIR=os.path.join(THISDIR,"..","build")
SRCDIR=os.path.join(THISDIR,"..","src")
ROMDIR=os.path.join(THISDIR,"..","..","TOWNSEMU_TEST","ROM_"+TOWNSTYPE)
DISKDIR=os.path.join(THISDIR,"..","..","TOWNSEMU_TEST","DISKIMG")



def ExeExtension():
	if sys.platform.startswith('win'):
		return ".exe"
	else:
		return ""


def Run(argv):
	os.chdir(BUILDDIR)
	subprocess.Popen([
		"./main_cui/main_cui"+ExeExtension(),
		ROMDIR,
		"-CD",
		"E:/ISOImage/FM-TOWNS/AfterburnerII/AFTER_BURNER.CUE",
		"-GAMEPORT0",
		"KEY",
		"-SYM",
		"../../TOWNSEMU_TEST/symtables/AB2_"+TOWNSTYPE+".txt",
		"-HD0",
		os.path.join(DISKDIR,"hddimage.bin"),
		"-CMOS",
		"../testdata/CMOS.bin",
		# "-DEBUG",
		# "-PAUSE",
	]+argv).wait()



if __name__=="__main__":
	build.Run()
	Run(sys.argv[1:])