/**
 * Copyright (C) 2020 Chocolata Printer oficial software, All right reserved.
 *
 * Autors: Abernihin Ilia & Velichko Bohdan
 *
 * Redistribution and use in source and binary forms, with or without modification, are permitted provided
 * that the following conditions are met:
 *
 *  * Redistributions of source code must retain the above copyright notice, this list of conditions and
 * the following disclaimer.
 *  * Redistributions in binary form must reproduce the above copyright notice, this list of conditions and
 * the following disclaimer in the documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 * PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
 * TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 *
 * Abstract:
 */

#ifndef CONFIGSPECIFICATION_HPP
#define CONFIGSPECIFICATION_HPP

#include <iostream>

#include "baseconfigs.hpp"

namespace
{
  using flpt = Configs::ParamType<Configs::floatopt_t>*;      // internall helper types
  using inpt = Configs::ParamType<Configs::intopt_t >*;       // internall helper types
  using blpt = Configs::ParamType<Configs::Boolean  >*;       // internall helper types
}

namespace Configs
{
  struct Infill      : ParamType<floatopt_t>   // config which control internal model infill
                       { virtual void check(); static flpt Instance(); private: Infill()       = default; };

  struct Perimetrs   : ParamType< intopt_t >   // config which control num of perimetrs
                       { virtual void check(); static inpt Instance(); private: Perimetrs()    = default; };

  struct DynamicLayer: ParamType<  Boolean >   // config which control using dynamic layer strategy
                       { virtual void check(); static blpt Instance(); private: DynamicLayer() = default; };

  struct MinLayer    : ParamType<floatopt_t>   // config which control minimal layer height
                       { virtual void check(); static flpt Instance(); private: MinLayer()     = default; };

  struct MaxLayer    : ParamType<floatopt_t>   // config which control maximal layer height
                       { virtual void check(); static flpt Instance(); private: MaxLayer()     = default; };

  struct Layer       : ParamType<floatopt_t>   // config which control static layer height
                       { virtual void check(); static flpt Instance(); private: Layer()        = default; };

  struct Intersection: ParamType<floatopt_t>   // config which control critical layer intersection
                       { virtual void check(); static flpt Instance(); private: Intersection() = default; };

  struct FirstLayer  : ParamType<floatopt_t>   // config which control first layer height
                       { virtual void check(); static flpt Instance(); private: FirstLayer() = default; };
};

#endif // CONFIGSPECIFICATION_HPP
