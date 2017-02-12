# Food Spirit

## About:
 - Food Spirit is a homebrew game for the original Game Boy and Game Boy Color. It will run on real hardware, but you can play it on a computer with an emulator. It works best on Game Boy Color.

## Set Up:
 - Building requires gbdk 2.96a to be installed. I've included an archive of it in the root directory of this folder.
 - Run `make.sh` to compile the rom into the `build` directory.

### Installing gbdk:
Follow the instructions in gbdk's readme to install it for Linux. Essentially:

1. Extract the archive to `/opt/gbdk/`
2. `export GBDKDIR=/opt/gbdk/`

Some problems I ran into:

 - gbdk is quite old and depends on 32-bit executables. You'll need to make sure to enable this on your system. As of early-2017, Windows bash doesn't support this.
 - If you're on Windows and using a VM to compile and you run into an error like `Value too large for defined data type`. It's because you're accessing the directory through a shared folder. I've included `make-in-vm.sh` as a convenience script when building like this.