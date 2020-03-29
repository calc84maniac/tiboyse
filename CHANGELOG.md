# TI-Boy SE Changelog

## Beta 0.2.05:
* Open-source release on github.
* Fixed an issue causing incorrect output when building with the latest version of SPASM.
* tiboyse_makeapp.exe updates:
  - Created Visual Studio solution which also builds librabbitsign dependency.
  - Switched to absorbing SPASM build output directly as a PE resource.

## Beta 0.2.04:
* First official beta release on ticalc.
* Included a sample homebrew ROM, Adjustris.
* Properly errors on low free RAM when starting a 32K-save game and the first save appvar does not exist.
* Fixed detection of sprite disabling.
* makeapp.exe updates:
  - Name changed to tiboyse_makeapp.exe.
  - Compiled against librabbitsign, so it no longer requires a separate rabbitsign executable.
  - As a result, the program no longer calls the system() function which was making some users' antivirus software very angry.
  - The tiboy.bin file is also now baked into the executable.

## Beta 0.2.03:
* Rearranged code and data to allow using 16KB of cartridge RAM on all calculators. This means that Pokemon Red/Blue/Yellow can be run on all calculators!
* Games that have 32KB of cartridge RAM but only use the first 8KB, 16KB, or 24KB will now only save to 1, 2, or 3 appvars respectively.
* Fixed a waitloop detection error, speeding up parts of some games like Kirby's Dream Land.

## Beta 0.2.02:
* The STAT behavior is fixed for real, cycling through all 3 modes within each scanline.

## Beta 0.2.01:
* Timer emulation is more accurate relative to emulation speed, fixes Super Mario Land freezing.
* More STAT compatibility. Now it cycles through all 3 modes.

## Beta 0.2.00:
* Rearranged some code/data, allowing TI-84 Pocket.fr compatibility and freeing some RAM.
* Reimplemented waitloop detection, which should eat much less CPU time per frame now.
* Rendering tricks are more reliably detected, fixing graphics in parts of some games.
* Emulator control keys are checked more often, improving responsiveness. Also, sprite tracking selection improved.
* Added custom frameskip settings.
* GPU speed is more accurate when sound is enabled, speeding up parts of some games.
* Timer emulation is more accurate, fixes music in Super Mario Land among other things.
* Extremely high-pitched sounds are changed to a slightly lower pitch, which should prevent freezes.
* Bit 1 of STAT is now toggled at every scanline from 0 to 143, which fixes some games.
* makeapp.exe updates:
  - Allow manual special character entry in app names, by typing \XY (XY is a hexadecimal character value)

## Beta 0.1.07:
* Fixed some small bugs introduced in Beta 0.1.06.

## Beta 0.1.06:
* Added support for 4-channel sound.

## Beta 0.1.05:
* Added some support for low-priority sprites, i.e. sprites can be displayed behind the background tilemap. Fixes quite a few graphical glitches!
* Fixed a cartridge RAM mapping glitch, which fixes compatibility with TI-Boy Alpha 4-appvar saves. Breaks compatibility with TI-Boy Beta 4-appvar saves.

## Beta 0.1.04:
* Added timer check in RET opcodes, which significantly increases framerate in Pokemon textboxes.

## Beta 0.1.03:
* Added light and dark monochrome palettes
* Reincluded the defragmentation OS glitch patch so APPs won't get corrupted if pages start with 0xFF.
* makeapp.exe updates:
  - Internal appnames are padded with spaces instead of null bytes for better linking software compatibility.
  - Trailing pages filled with 0x00 or 0xFF bytes are now removed from ROMs. This saves a lot of space in certain ROMs (e.g. saves 304KB in Pokemon Red).

## Beta 0.1.02:
* Save files are archived upon exit.
* Fixed glitch in which only the first 8KB is loaded from a 32KB save.
* Fixed very bad glitch in 32KB saving caused by `bcall(_DelVarArc)` trashing `(OP1)`.
* Pressing Select no longer causes a false press of B on some calculators.
* makeapp.exe updates:
  - Output app is now always placed in the same folder as the exe.
  - APPs which have 32KB saves now have a maximum of 7 characters in their names (because the save data goes into 4 separate appvars which need unique names)

## Beta 0.1.01:
* TI-Boy no longer makes a resident patch to the OS (so the OS stays valid and there are no conflicts with other patches).
* Flash writing is now done in 6MHz mode so it works on slower flash chips.
* makeapp.exe updates:
  - Spaces in ROM filename now handled correctly when program is run with no arguments.
  - Searches for tiboy.bin and rabbitsign in the same folder as the exe.
  - Displays number of pages in generated APP.

## Beta 0.1.00:
* First public beta (on omnimaga.org)
