# TI-Boy SE

[![License: GPL v3](https://img.shields.io/badge/License-GPLv3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0)

TI-Boy SE is a Game Boy emulator (no Game Boy Color support) for the TI-83+SE, TI-84+, and TI-84+SE calculators. Do not expect incredible compatibility.

This was rewritten from scratch since the Alpha version, specifically to support newer TI-84+/TI-84+SE calculators (which have smaller RAM chips).

TI-83+ and TI-Nspire with 84+ keypad are not supported, and never will be.

Grab the latest pre-built release at <https://github.com/calc84maniac/tiboyse/releases> or check out the [Build Instructions](#build-instructions) to build from source.

## Disclaimer
This is a beta piece of software (though a well-tested one). The creator is not held responsible for any damages caused. Use at your own risk!

TI-Boy will temporarily replace part of the TI-OS, for greater speed and more available RAM. An automatic recovery feature is included in the case of a crash.

Nonetheless, this program is not likely to permanently brick your calculator. The most damage it might cause is a RAM clear and/or an OS reinstall.

## Beta Version Features
* Works on all black-and-white TI-84+ models
* Better game compatibility
* Significantly faster CPU emulation
* Has four zoom levels (100%, 75%, 60%, 50%)
* More intuitive zooming controls (pressing Plus and Minus!)
* Black-and-white zoom modes use dithering to increase visual quality
* Supports 4-channel sound output
* Recovers RAM data in the case of a crash

## Creating APPs
Note: Any warnings given about pages beginning with FFh can be safely ignored, because TI-Boy patches the defragmentation glitch in the TI-OS.

### Method 1: Drag-and-drop
Open the TI-Boy folder, then drag a Game Boy ROM file onto `tiboyse_makeapp.exe`. A command-line window should open.

If the ROM opened successfully, the program will request a name for the APP. Type it in and press Enter.

Watch the console output for any compatibility warnings.

### Method 2: Run the EXE
Open `tiboyse_makeapp.exe` directly. A command-line window should open and ask for a ROM filename. You may have to enter the entire filepath.

If the ROM opened successfully, the program will request a name for the APP. Type it in and press Enter.

Watch the console output for any compatibility warnings.

### Method 3: Command-line arguments
Open a command-line window and navigate to the TI-Boy folder. Enter in the following format:

    tiboyse_makeapp romfilename.gb AppName

Watch the console output for any compatibility warnings.

If you get a missing DLL error when running the command-line utility, you may need to install the [Universal C Runtime](https://support.microsoft.com/en-us/help/2999226/update-for-universal-c-runtime-in-windows).

## Sending APPs
Use TI-Connect or other compatible linking software. Note: Not all TI-Boy APPs can fit on non-Silver Edition calculators (see [FAQ](#frequently-asked-questions)).

## Running TI-Boy
Open the APPs menu, and start the APP.

It should display the loading screen. Do not remove a battery while this is loading, or you will have to reinstall the TI-OS.

Then, start playing! (See controls below.)

To quit, press the ON button. Quitting takes a few seconds as it restores the TI-OS. Again, do not remove a battery during this step.

If the emulator freezes and pressing ON does not cause it to quit (which does work in most cases), feel free to remove a battery.

TI-Boy will automatically restore the TI-OS and your previous RAM contents if this happens.

## Controls

### Game controls:
*   <kbd>↑</kbd> <kbd>↓</kbd> <kbd>←</kbd> <kbd>→</kbd> D-Pad
*   <kbd>2ND</kbd> A
*   <kbd>ALPHA</kbd> B
*   <kbd>MODE</kbd> START
*   <kbd>XTθn</kbd> SELECT
*   <kbd>ON</kbd> Power switch (exit the emulator)

### Emulator controls:
*   <kbd>CLEAR</kbd> Battery Saver or Teacher Key (suspends emulation and turns off the screen)
*   <kbd>STAT</kbd> Toggle sound emulation (default is off). See FAQ for more information.
*   <kbd>×</kbd> Increase LCD contrast
*   <kbd>÷</kbd> Decrease LCD contrast 
*   <kbd>+</kbd> Zoom in
*   <kbd>-</kbd> Zoom out
*   <kbd>WINDOW</kbd> <kbd>ZOOM</kbd> <kbd>TRACE</kbd> Light/Normal/Dark monochrome modes (smooth zoom)
*   <kbd>GRAPH</kbd> Grayscale mode (rough zoom)
*   <kbd>1</kbd> <kbd>2</kbd> <kbd>3</kbd> <kbd>4</kbd> <kbd>6</kbd> <kbd>7</kbd> <kbd>8</kbd> <kbd>9</kbd> Move view
*   <kbd>.</kbd> Follow next sprite in the internal list (selected sprite will flash for a few frames)
*   <kbd>5</kbd> Center view on selected sprite
*   <kbd>0</kbd> Turn off sprite follower
*   <kbd>(-)</kbd> Set frameskip (hold the negation key and press a number 0-9 to set the value)

## Frequently Asked Questions
**Q.** Sound emulation? What's up with that?

**A.** When sound emulation is turned on, TI-Boy will to the best of its ability emulate the Game Boy sound hardware and output sound waves to the I/O data port.

However, this comes at a performance cost. There are 4 channels that are emulated, and 2 are outputted to each ear. There is no volume control.

##
**Q.** How do I listen to the sound?

**A.** You will need a 2.5mm-male to 3.5mm-female adapter to plug in standard headphones/speakers to the I/O data port.

It is recommended that you plug in the headphones after starting TI-Boy (because the homescreen responds very slowly when headphones are plugged in).

##
**Q.** How big are the APPs?

**A.** Generally, take the size of the ROM and add 16KB (16384 bytes). Sometimes you might get lucky and have a smaller APP if there is a lot of empty space in the ROM.

Pay attention to the size displayed when `tiboyse_makeapp.exe` finishes.

##
**Q.** Will xxxx ROM fit on my calculator?

**A.** If you have a Silver Edition, ROMs up to 1MB (1024KB) in size will fit. If you have a normal TI-84+, ROMs up to 256KB in size will fit.

Make sure to delete useless APPs from your calculator if needed.

##
**Q.** So the compatibility issues with newer calculators are fixed?

**A.** Mostly. There is still not enough RAM to emulate cartridges which use 32KB RAM, added to all the RAM in the Game Boy itself.

Thankfully, such cartridges are few and far between. Also, such games that do not use all of that RAM, such as Pokemon Red/Blue/Yellow, can run with few issues.

##
**Q.** Which calculators have a large enough RAM chip for this RAM-hogging game I want to play?

**A.** All TI-83+SE calculators have the larger RAM chips. TI-84+ and TI-84+SE calculators have larger RAM chips if they were manufactured before around April 2007.

To be more specific, check the back of your calculator. The last part of the serial number should be in the format X-MMYYR,
where MM is the month, YY is the year, and R is the revision. For example, S-0207G means manufactured in February 2007 with revision G.

Revisions G and earlier have the larger RAM chips, and revisions H and later have the smaller RAM chips.
If the revision letter is missing, that means it is before revision A (and should work).

##
**Q.** What exactly does TI-Boy do to my calculator when it runs? Why the warnings?

**A.** TI-Boy needs part of the Flash (Archive) memory which is taken by the TI-OS. So, it backs up this section of the OS and puts its own data there.

Also, this is where your RAM is backed up in the case of a crash. When TI-Boy exits, the OS is put completely back to normal. There are two reasons for doing this:

1. The emulator becomes quite a bit faster and simpler if GameBoy data can be in the space normally taken by the OS.

2. Having control of this memory space allows automatic recovery in the case of a crash.

##
**Q.** Does tiboyse_makeapp convert Game Boy ROMs into native TI code?

**A.** No. The ROM is slightly rearranged to fit into an APP and bundled with the emulator code. Converting to native TI code is infeasible for many reasons.

##
**Q.** My calculator died! It's all your fault!

**A.** Don't panic! To send a new OS, hold DEL while inserting a battery to bring up the Send OS screen.

And make sure to report the bug, because we don't want this sort of thing to happen, now do we? ;)

##
**Q.** Where is xxxx feature?

**A.** This project is no longer under active development; it has been superceded by [TI-Boy CE](https://github.com/calc84maniac/tiboyce).

However, it is open source, so feel free to fork the project if you're adventurous!

##
**Q.** xxxx ROM doesn't work!

**A.** Sorry, but specific game compatibility is a low priority due to the emphasis on performance.

##
**Q.** how do i tern on my caclulater

**A.** ...

## Build Instructions

To build the emulator from source, first clone the git repository and init/update submodules with the following command:

        git submodule update --init

Now grab the latest release of [SPASM-ng](https://github.com/alberthdev/spasm-ng/releases).

For simplicity's sake, I'll call the name of the executable `spasm` below. Run the following to produce the emulator file:

        spasm tiboyse.z80 tiboyse_makeapp/tiboy.bin

To build the app generation tool, use the provided Visual Studio solution in the [tiboyse_makeapp](tiboyse_makeapp) directory,
which will consume the output from SPASM as a PE resource to create a standalone executable.

In theory, you can build the source for any platform with your C compiler of choice, by building `makeapp.cpp` and linking against
librabbitsign from the submodule. In this case, the executable will read tiboyse.bin from its own directory at runtime.

## Credits
* calc84maniac for coding/design
* thepenguin77 for clean flash unlock hack
* FloppusMaximus for Rabbitsign (app signer). Source code can be found at <https://github.com/abbrev/rabbitsign>.
* Omnimaga for all the awesome community support
* Runer112 for yelling TI-BOYYYYYY at me periodically

## License

TI-Boy SE — a Game Boy emulator for the TI-84 Plus calculator family.
Copyright © 2009 – 2020 Brendan Fletcher
