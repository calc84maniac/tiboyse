#include <cstring>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <limits>
#include <string>
#include "rabbitsign.h"

#ifdef USE_WINDOWS_RESOURCE
#include <Windows.h>
#include "resource.h"
#endif

const unsigned long TIBOY_SIZE = 0x4000 - 96;

void wait()
{
    std::cout << "< Press Enter to continue >";
    getchar();
}

unsigned char getHex(char letter)
{
    if(letter >= '0' && letter <= '9') return letter - '0';
    if(letter >= 'A' && letter <= 'Z') return letter - 'A' + 0xA;
    if(letter >= 'a' && letter <= 'z') return letter - 'a' + 0xA;
    return 0;
}

std::string escape(std::string& name)
{
    std::string valid = name;
    size_t search = std::string::npos;
    while((search = name.find('\\',search+1)) != std::string::npos)
    {
        name.replace(search, 3, 1, getHex(name[search+1])*16 + getHex(name[search+2]));
        valid.replace(search, 3, 1, '-');
    }
    return valid;
}

int main(int argc, char** argv)
{
    std::cout << "ROM to APP converter for TI-Boy Beta 0.2.04\n\n";
	if (argc < 3)
	{
		atexit(wait);
	}

    std::string romfilename;
    if(argc >= 2)
    {
        romfilename = argv[1];
    }
    else
    {
        std::cout << "Enter the filepath/name of the ROM to convert: ";
        std::getline(std::cin, romfilename);
    }

    std::ifstream romfile;
    romfile.open(romfilename.c_str(), std::ios::binary | std::ios::ate);
    if(romfile.fail())
    {
        std::cout << "Error opening ROM file!\n";
        return EXIT_FAILURE;
    }

    unsigned long romfilesize = (unsigned long)romfile.tellg();
    romfile.seekg(0, std::ios::beg);

    if (romfilesize & 0x3FFF)
    {
        std::cout << "Warning, ROM file is not a multiple of 16KB!\n";
        std::cout << "Ignoring last " << (romfilesize & 0x3FFF) << " bytes.\n\n";
        romfilesize &= ~0x3FFF;
    }

    char* romdata = new char[romfilesize];
    romfile.read(romdata, romfilesize);
    romfile.close();

    char internal_name[16];
    strncpy(internal_name, romdata+0x134, 15);
    internal_name[15] = 0;
    std::cout << "Successfully opened ROM: " << internal_name << "\n";

    std::string appname, appfilename;
    size_t maxName = (romdata[0x149] == 3 ? 7 : 8);
    if(argc >= 3)
    {
        appfilename = escape(appname = argv[2]);
    }
    if(argc < 3 || appname.length() > maxName)
    {
		if (argc >= 3)
		{
			atexit(wait);
		}
        do
        {
            std::cout << "Enter a name for the APP (" << maxName << " char max): ";
            std::cin >> appname;
            std::cin.ignore();
            appfilename = escape(appname);
        }
        while(appname.length() > maxName);
    }

    std::string appPath = argv[0];
    appPath = appPath.substr(0,appPath.find_last_of('\\')+1);

#ifdef USE_WINDOWS_RESOURCE
	HRSRC resourceInfo = FindResource(nullptr, MAKEINTRESOURCE(TIBOYSE_RESOURCE), RT_RCDATA);
	if (resourceInfo == nullptr)
	{
		std::cout << "Error: Could not find embedded tiboyse resource\n";
		return EXIT_FAILURE;
	}
	if (SizeofResource(nullptr, resourceInfo) != TIBOY_SIZE)
	{
		std::cout << "Error: Embedded tiboyse resource seems to be corrupt (incorrect size)\n";
		return EXIT_FAILURE;
	}
	HGLOBAL resourceData = LoadResource(nullptr, resourceInfo);
	if (resourceData == nullptr)
	{
		std::cout << "Error: Failed to load embedded tiboyse resource\n";
		return EXIT_FAILURE;
	}
	const void* resourcePtr = LockResource(resourceData);
	if (resourcePtr == nullptr)
	{
		std::cout << "Error: Failed to lock embedded tiboyse resource\n";
		return EXIT_FAILURE;
	}
#else
    std::ifstream tiboyfile;
    tiboyfile.open((appPath+"tiboyse.bin").c_str(), std::ios::binary | std::ios::ate);
    if(tiboyfile.fail())
    {
        std::cout << "Error: Could not locate vital file tiboyse.bin\n";
        return EXIT_FAILURE;
    }
    if((unsigned long)tiboyfile.tellg() != TIBOY_SIZE)
    {
        std::cout << "Error: tiboyse.bin seems to be corrupt (incorrect file size)\n";
        return EXIT_FAILURE;
    }
    tiboyfile.seekg(0, std::ios::beg);
#endif

    unsigned long newsize = romfilesize;
    unsigned char comp_byte = romdata[--newsize];
    if(comp_byte == 0x00 || comp_byte == 0xFF)
        while(romdata[--newsize] == comp_byte);
    romfilesize = (newsize | 0x3FFF) + 1;

    char* appdata = (char*)malloc(TIBOY_SIZE + romfilesize);
#ifdef USE_WINDOWS_RESOURCE
	memcpy(appdata, resourcePtr, TIBOY_SIZE);
#else
    tiboyfile.read(appdata, TIBOY_SIZE);
    tiboyfile.close();
#endif

    memcpy(appdata + 0x0012, appname.c_str(), appname.length());
    memcpy(appdata + TIBOY_SIZE, romdata + TIBOY_SIZE, romfilesize - TIBOY_SIZE);
    memcpy(appdata + romfilesize, romdata, TIBOY_SIZE);

    RSKey *key = rs_key_new();
    rs_key_find_for_id(key, 0x0104, 0);

    RSProgram *prgm = rs_program_new();
    prgm->calctype = RS_CALC_TI83P;
    prgm->datatype = RS_DATA_APP;
    prgm->data = (unsigned char*)appdata;
    prgm->length = prgm->length_a = TIBOY_SIZE + romfilesize;
    rs_repair_ti8x_app(prgm, (RSRepairFlags)((int)RS_IGNORE_ALL_WARNINGS | (int)RS_FIX_PAGE_COUNT));

    if (rs_sign_ti8x_app(prgm, key, 0) == RS_SUCCESS)
    {
        std::string binout = appPath + appfilename + ".8xk";
        FILE *appfile = fopen(binout.c_str(), "wb");
        if (rs_write_program_file(prgm, appfile, 0, 0, 0, (RSOutputFlags)0) == RS_SUCCESS)
        {
            std::cout << "\nGenerated a " << romfilesize + 0x4000 << " byte (" << romfilesize/0x4000+1 << " page) APP.\n\n";

            if((unsigned char)romdata[0x143] == 0xC0)
                std::cout << "Warning: This is a Game Boy Color ROM. TI-Boy does not support GBC.\n\n";

            if(romfilesize > 1540096)
                std::cout << "Warning: This APP will not fit on any TI-83+ or TI-84+ calculator.\n\n";
            else if(romfilesize > 491520)
                std::cout << "Warning: This APP will only fit on a Silver Edition calculator.\n\n";

            if(romdata[0x149] == 3)
                std::cout << "Warning: This APP may require more than 48KB RAM to emulate.\nIt might not work on new TI-84+ models.\nHowever, Pokemon Red/Blue/Yellow have been confirmed to work on all models.\nTo see if your model has 128KB RAM, check the serial number on the back.\nIf the ending letter is from A-G or has no letter, there is enough RAM.\nOtherwise, just test it and see if it gives an error.\n\n";
        }
        else
        {
            std::cout << "\nAn error occurred when writing to the output file!\n\n";
        }
        fclose(appfile);
    }
    else
    {
        std::cout << "\nAn error occurred when signing the application!\n\n";
    }

    return EXIT_SUCCESS;
}
