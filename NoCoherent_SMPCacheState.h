/*

   This code is built on top of the CacheCore and SMPCache code from

   Sesc: Super ESCalar simulator
   Copyright (C) 2003 University of Illinois.

   This file was Created by Brandon Lucia


This file is based on a part of SESC.
SESC is free software; you can redistribute it and/or modify it under the terms
of the GNU General Public License as published by the Free Software Foundation;
either version 2, or (at your option) any later version.
SESC is    distributed in the  hope that  it will  be  useful, but  WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
PARTICULAR PURPOSE.  See the GNU General Public License for more details.
You should  have received a copy of  the GNU General  Public License along with
SESC; see the file COPYING.  If not, write to the  Free Software Foundation, 59
Temple Place - Suite 330, Boston, MA 02111-1307, USA.
*/

#ifndef NOCOHERENTSMPCACHESTATE_H
#define NOCOHERENTSMPCACHESTATE_H

enum Cachestate_t {
	NC_VALID   = 0x01,
	NC_INVALID = 0x10
};

#include "CacheCore.h"
// these states are the most basic ones you can have
// all classes that inherit from this class should
// have at least the following states and bits, with the same encoding

class NoCoherent_SMPCacheState : public StateGeneric<> {

private:
protected:

  //You can add other state that should be
  //maintained for each cache line here
  //e.g.: bool from_untrusted_source
  //or whatever.

public:
  NoCoherent_SMPCacheState() : StateGeneric<>() {
    state = (unsigned)NC_INVALID;
  }

  // BEGIN CacheCore interface
  bool isValid() const {
    return (state != (unsigned)NC_INVALID);
  }

  void invalidate() {
    clearTag();
    state = (unsigned)NC_INVALID;
  }

	bool isLocked() const {
    return false;
  }
  // END CacheCore interface

  unsigned getState() const {
    return state;
  }

  void changeStateTo(Cachestate_t newstate) {
    // not supposed to invalidate through this interface
    I(newstate != (unsigned)NC_INVALID);
    state = (unsigned)newstate;
  }

};

#endif //NOCOHERENTSMPCACHESTATE_H
