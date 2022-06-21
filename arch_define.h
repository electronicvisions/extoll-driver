/*
 *  This file is part of the  Linux Kernel Driver Package for EXTOLL R2.
 *
 *  Copyright (C) 2011 EXTOLL GmbH
 *
 *  Written by Mondrian Nuessle (2011)
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#ifndef _ARCH_DEFINE_H_
#define _ARCH_DEFINE_H_  


//Uncomment for KNC Support
//#define MICEXTOLL

//Uncomment for BIC support
//#define DEEP_HOST

//Uncomment for KNC support in DEEP setup
//#define DEEP_KNC

//Uncomment for LS3B support
//#define LS3BEXTOLL

/*
#include <generated/compile.h>

#define KNC_ARCH __builtin_strcmp(__ELF__, "k1om")
//#if 'k1om' == UTS_MACHINE 
//#ifdef UTS_MACHINE
//#if __ELF__ == "k1om"
#if ( KNC_ARCH == 0 )
  #define MICEXTOLL
  #error "KNC COMPILE"

#else
  #error "NO KNC COMPILE"
#endif
*/

//Define the page attributes used for "write combining" access, platform dependent
#ifdef LS3BEXTOLL
  #define EXTOLLWCATTR 0
  #define EXTOLLWBATTR 0
#else
 #ifdef MICEXTOLL
   #define EXTOLLWCATTR 0
   #define EXTOLLWBATTR 0
 #else
   #define EXTOLLWCATTR EKVCL_PAGE_CACHE_MODE_WC
   #define EXTOLLWBATTR EKVCL_PAGE_CACHE_MODE_WB
 #endif
#endif

#endif
