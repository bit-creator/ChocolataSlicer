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

#ifndef CONFIGS_HPP
#define CONFIGS_HPP

#include <fstream>
#include <string>
#include <memory>
#include <vector>
#include <stack>
#include <map>

#include "configspecification.h"

/**
 * @brief list of all configs names
 */
enum class CfgNames
{
        /* Printer_configs */               /*Slicer_config*/            /*Material_config*/
          WORKSPACE_SIZE_X,                      INFILL,                       //...
          WORKSPACE_SIZE_Y,                                                   //...
          WORKSPACE_SIZE_Z,                     PERIMETRS,                       //...
                                               DYNAMIC_LAYER,
                                                 MIN_LAYER,
                                                 MAX_LAYER,
                                                   LAYER,
                                                INTERSECTION,
                                                FIRST_LAYER
            //...                                 //...
            //...                                 //...
            //...                                 //...
};

namespace Configs
{
    using errors_array = const std::vector < std::string >;            // errors text
    using err_indx  = uint32_t;                                        // index of error
    using conflict = std::stack < std::pair < err_indx, CfgNames > >;  // stack of conflicts
    using config_array = std::map < CfgNames, Param >;                 // configs collection

    errors_array errors =
    {
          "value is greater than allowed"
        , "value less than acceptable"
        , ""
        , ""
        , ""
        , ""
        , ""
        , ""
    };

    static config_array configs =
    {
          { CfgNames::INFILL,        Infill::Instance()       }
        , { CfgNames::PERIMETRS,     Perimetrs::Instance()    }
        , { CfgNames::DYNAMIC_LAYER, DynamicLayer::Instance() }
        , { CfgNames::MIN_LAYER,     MinLayer::Instance()     }
        , { CfgNames::MAX_LAYER,     MaxLayer::Instance()     }
        , { CfgNames::LAYER,         Layer::Instance()        }
        , { CfgNames::INTERSECTION,  Intersection::Instance() }
        , { CfgNames::FIRST_LAYER,   FirstLayer::Instance()   }
    };

    /**
     * @brief abstract base pointer extraction
     * @param param std::variant for configs
     * @return ParamType<noknowing type>*
     */
    template<typename _Tp> _Tp& get_(Param& param)
    { return std::get<_Tp>(param); }

    /**
     * @brief config value extraction
     * @param name of need config
     * @return reference on config value
     */
    template<typename _Tp> _Tp& get(const CfgNames name)
    { return get_<ParamType<_Tp>*>(configs.at(name))->get(); }

    /**
     * @brief config max value extraction
     * @param name of need config
     * @return reference on config max value
     */
    template<typename _Tp> _Tp& getMax(const CfgNames name)
    { return get_<ParamType<_Tp>*>(configs.at(name))->getMax(); }

    /**
     * @brief config min value extraction
     * @param name of need config
     * @return reference on config min value
     */
    template<typename _Tp> _Tp& getMin(const CfgNames name)
    { return get_<ParamType<_Tp>*>(configs.at(name))->getMin(); }
};

namespace cfg = Configs;

using f = cfg::Value < float >;
using i = cfg::Value < int >;
using b = cfg::Boolean;

#endif //CONFIGS_HPP
