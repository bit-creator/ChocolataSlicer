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

#ifndef BASECONFIGS_HPP
#define BASECONFIGS_HPP

#include <optional>
#include <variant>
#include <cstring>
#include <map>

namespace Configs
{
   /**
    * @brief declaration of the foo that controls the correctness of the assigned values
    * this foo no throw exeption
    */
    void validate() noexcept;

    /**
     * @brief declaration of the foo that read configs data
     * @param path this is correct path to configs file
     * this foo no throw exeption
     */
    void open(std::string path) noexcept;

    /**
     * @brief declaration of the foo that write configs data in file
     * @param path this is correct path to configs file
     * this foo no throw exeption
     */
    void save(std::string path) noexcept;

   /**
    * @brief configuration value type class declaration
    * @brief @class Value this is specification of std::optional type which
    *               call validate functor every assigned
    */
   template < typename _Tp >
       class Value : public std::optional<_Tp>
       {
           public:
               /**
                * @brief (constructor) call Base class (constructor)
                * @brief (constructor) no throw exeption
                */
               Value(_Tp val) noexcept : std::optional<_Tp>(val) {  }

               /**
                * @brief (constructor) for specific data call Base class (constructor)
                * @brief (constructor) no throw exeption
                */
               Value(std::nullopt_t val = std::nullopt) noexcept : std::optional<_Tp>(val) {  }

               /**
                * @brief virtual (destructor) for Value type
                */
               virtual ~Value() {  }

               /**
                * @brief assigned operator which detected all of changes this values
                * #brief used special validate function
                */
               Value<_Tp>& operator = (const _Tp& val)
               {
                   this->std::optional<_Tp>::operator=(val);
                   stateIsChanged =! stateIsChanged;
                   validate();
                   stateIsChanged =! stateIsChanged;
                   return *this;
               }

               bool                stateIsChanged = false;      // state parametr
           };

   /**
    * @brief class wrapper for bool type
    * @brief need for detected changes of configs
    */
   class Boolean
   {
       public:
           bool                            _value;                  // wrapped value
           bool                            stateIsChanged = false;  // state parametr

           /**
            * @brief operator for implicit cast this type to bool
            */
           operator bool () { return _value; }

           /**
            * @brief assigned operator which detected all of changes this values
            * #brief used special validate function
            */
           Boolean operator = (bool val)
           {
               _value = val;
               stateIsChanged =! stateIsChanged;
               validate();
               stateIsChanged =! stateIsChanged;
               return *this;
           }
   };

   using floatopt_t = Value < float >;              // optional float pseudonim
   using intopt_t   = Value <  int  >;              // optional int pseudonim

   /**
    * @brief template abstract base for all configs
    */
   template < typename _Tp >
       class ParamType
       {
           protected:
               _Tp                             __min;                 // minimum configs value
               _Tp                             __max;                 // maximum configs value
               _Tp                             __value;               // config value

               inline static ParamType<_Tp>*   __instance = nullptr;  // static instance pointer

           protected:
               ParamType() noexcept = default;                      // default (constructor)
               ParamType(ParamType<_Tp>&) = delete;                 // copy/move operations
               ParamType& operator = (ParamType<_Tp>&) = delete;    // are prohibited

           public:
               /**
                * @brief getter for configs value
                * @brief nothrow exeption
                * @return config value
                */
               _Tp& get()    noexcept { return __value; };

               /**
                * @brief getter for max configs value
                * @brief nothrow exeption
                * @return max value
                */
               _Tp& getMax() noexcept { return __max; };

               /**
                * @brief getter for min configs value
                * @brief nothrow exeption
                * @return min value
                */
               _Tp& getMin() noexcept { return __min; };

               /**
                * @brief checks all value changes
                * @brief nothrow exeption
                * @brief no change object
                * @return true if some of data changes
                */
               bool isChanged() const noexcept { return __min.stateIsChanged
                                                     || __max.stateIsChanged
                                                     || __value.stateIsChanged; }

               /**
                * @brief virtual checker
                * for search conflicts configs
                */
               virtual void check() = 0;

               /*virtual destructor*/
               virtual ~ParamType() noexcept = default;
       };

   /**
    * configs param general value
    */
   using Param = std::variant  < ParamType <   Boolean    > *,
                                 ParamType <  Value<int>  > *,
                                 ParamType < Value<float> > * >;
};

#endif  // BASECONFIGS_HPP
