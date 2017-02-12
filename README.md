# Gameboy Platformer

## Set Up:
 - Building requires gbdk 2.96a to be installed.
 - I've included a tar of it in the root directory of this folder. 
 - Run `make.sh` to build the rom.

### Installing gbdk:
Follow the instructions in gbdk's readme to install it for Linux. Essentially:

1. Extract the archive to `/opt/gbdk/`
2. `export GBDKDIR=/opt/gbdk/`

Some problems I ran into:

 - gbdk is quite old and depends on 32-bit executables. You'll need to make sure to enable this on your system. As of early-2017, Windows bash doesn't support this.
 - If you're on Windows and using a VM to compile and you run into an error like `Value too large for defined data type`. It's because you're accessing the directory through a shared folder. I've included `make-in-vm.sh` as a convenience script when building like this.