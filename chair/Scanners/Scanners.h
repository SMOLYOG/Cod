#pragma once
#include "..\Globals\Globals.h"

extern bool gotcmdq;
extern bool gotpacket;
#define ADD_ADDRESS_FUNCTION( name, func ) shared::address_t name =  func( );

namespace ScanSigs {
	namespace Miscellaneous {
		extern void ScanSigs();
	}
	extern int Init_Scanners;
}

