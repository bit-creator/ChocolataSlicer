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
 * Abstract: this is declaretion of geometry types
 *
 */

#ifndef GEOMETRY_HPP
#define GEOMETRY_HPP

#include <optional>
#include <memory>
#include <cmath>
#include <iostream>

constexpr float F_TOL = 0.000001;  // TOLERANCE_FOR_FLOAT_COMPARING

/** BAGFIX
 * 1. using a global constant for bed plate normal
*/


namespace Geometry  // GEOMETRIC_TYPES_IMPL
{
    /**
     * @brief Function for compare two float value
     *
     * @param first this is first comparing value (const ref)
     * @param second this is second comparing value (const ref)
     *
     * @return TRUE if param equal to F_TOL order, FALSE if no
     *
     * this function no throw exeption
     *
     * this function is embeded
     */
    inline constexpr bool
    is_equal(const float first, const float second) noexcept
    { return  (std::abs ( first - second ) < 0.000001); }

    /**
     * @struct Point2d impliment point on face
     *
     */
    struct Point2d
    {
        Point2d()
            : _x(0.)
            , _y(0.)
        {  }

        Point2d(const float& x, const float y)
            : _x(x)
            , _y(y)
        {  }

        float _x;
        float _y;
    };

    /**
     * Texture coordinate is pair has two float value: u & v respectivetly
    */
    using uv_t = std::pair < const float&, const float& >;

    /**
     * optional point is point who may be or not maybe and all version correct
     */
    using optPoint2d = std::optional < Point2d >;

    /**
     * cut_t this is type triangle intersection
     */
    using cut_t = std::optional < std::pair < optPoint2d, optPoint2d > >;

    /**
     * @class Primitive is abstract base for real geometric object
     *
     * derived: @class Vertex, @class Vector
     *
     * cannot be constructing (have clear virtual function)
     */
    class Primitive
    {
        protected:  // DATA
            float _x;       // x coordinate
            float _y;       // y coordinate
            float _z;       // z coordinate

        public:    // DERIVED
            enum class simplyType // real geometric types
            {
                GEOMETRIC_VERTEX,
                GEOMETRIC_VECTOR
            };

        public:   // CONSTRUCT_DESTRUCT_ASSIGNMENT_OPERATORS
            /**
             * @brief default (constructor) for @class Primitive
             * initalize all coordinate as null
             *
             * this method no throw exeption
            */
            constexpr
            Primitive() noexcept
                : _x ( 0. )
                , _y ( 0. )
                , _z ( 0. )
            { }

            /**
             * @brief (constructor) for @class Primitive
             * initalize coordinate as @param
             *
             * @param x value x coordinate (const reference)
             * @param y value y coordinate (const reference)
             * @param z value z coordinate (const reference)
             *
             * this method no throw exeption
            */
            constexpr
            Primitive(const float& x, const float& y, const float& z) noexcept
                : _x ( std::forward < const float > ( x ) )
                , _y ( std::forward < const float > ( y ) )
                , _z ( std::forward < const float > ( z ) )
            { }

            /**
             * @brief (constructor) for @class Primitive
             * initalize coordinate as @param
             *
             * @param x value x coordinate (const r-value reference)
             * @param y value y coordinate (const r-value reference)
             * @param z value z coordinate (const r-value reference)
             *
             * this method no throw exeption
            */
            constexpr
            Primitive(const float&& x, const float&& y, const float&& z) noexcept
                : _x ( std::move ( x ) )
                , _y ( std::move ( y ) )
                , _z ( std::move ( z ) )
            { }

            /**
             * @brief copy (constructor) for @class Primitive
             *
             * @param other Primitive object (const reference)
             *
             * this method no throw exeption
            */
            constexpr
            Primitive(const Primitive& other) noexcept
                : _x ( other._x )
                , _y ( other._y )
                , _z ( other._z )
            { }

            /**
             * @brief move (constructor) for @class Primitive
             *
             * @param other Primitive object (const r-value reference)
             *
             * this method no throw exeption
            */
            constexpr
            Primitive(const Primitive&& other) noexcept
                : _x ( std::move ( other._x ) )
                , _y ( std::move ( other._y ) )
                , _z ( std::move ( other._z ) )
            { }

            /**
             * @brief virtual (destructor) for @class Primitive
             *
             * this method no throw exeption
            */
            virtual
            ~Primitive( ) noexcept
            { }

            /**
             * @brief copy assignment operator for @class Primitive
             *
             * @param other Primitive object (const reference)
             *
             * this method no throw exeption
            */
            constexpr Primitive&
            operator = (const Primitive& other) noexcept
            {
                if(this == &other)
                    return *this;

                _x = other._x;
                _y = other._y;
                _z = other._z;

                return *this;
            }

            /**
             * @brief move assignment operator for @class Primitive
             *
             * @param other Primitive object (const r-value reference)
             *
             * this method no throw exeption
            */
            constexpr Primitive&
            operator = (const Primitive&& other) noexcept
            {
                if(this == &other)
                    return *this;

                _x = std::move ( other._x );
                _y = std::move ( other._y );
                _z = std::move ( other._z );

                return *this;
            }

        public:     // SIMPLY_TYPE_GETER
            /**
             * @brief clear virtual function, definished in derived
             *
             * @return type of real geometric object
             *
             * this method no change object
             *
             * this method no throw exeption
            */
            virtual const simplyType
            getSimplyType() const noexcept = 0;

        public:   // SETER_FOO
            /**
             * @brief this method set x coordinate
             *
             * @param x value x coordinate (const reference)
             *
             * this method no throw exeption
            */
            constexpr void
            setX(const float& x) noexcept
            { _x = x; }

            /**
             * @brief this method set y coordinate
             *
             * @param y value y coordinate (const reference)
             *
             * this method no throw exeption
            */
            constexpr void
            setY(const float& y) noexcept
            { _y = y; }

            /**
             * @brief this method set z coordinate
             *
             * @param z value z coordinate (const reference)
             *
             * this method no throw exeption
            */
            constexpr void
            setZ(const float& z) noexcept
            { _z = z; }

            /**
             * @brief this method set all coordinate
             *
             * @param x value x coordinate (const reference)
             * @param y value y coordinate (const reference)
             * @param z value z coordinate (const reference)
             *
             * this method no throw exeption
            */
            constexpr void
            setCoordinate(const float& x, const float& y, const float& z) noexcept
            { _x = x; _y = y; _z = z; }

        public:    // GETER_FOO
            /**
             * @brief this method get x coordinate
             *
             * @return const reference on x coordinate
             *
             * this method no change object
             *
             * this method no throw exeption
            */
            constexpr const float&
            getX() const noexcept
            { return _x; }

            /**
             * @brief this method get y coordinate
             *
             * @return const reference on y coordinate
             *
             * this method no throw exeption
            */
            constexpr const float&
            getY() const noexcept
            { return _y; }

            /**
             * @brief this method get z coordinate
             *
             * @return const reference on z coordinate
             *
             * this method no change object
             *
             * this method no throw exeption
            */
            constexpr const float&
            getZ() const noexcept
            { return _z; }

        public:     // LOGIC_OPERATORS
            /**
             * @brief equal operator compares two Primitive object
             *
             * @param oth left handle operand
             *
             * @return TRUE if all coordinates equal, another else
             *
             * this method no change object
             *
             * this method no throw exeption
            */
            constexpr bool
            operator == (const Primitive& oth) const noexcept
            { return (is_equal(_x, oth.getX())
                   && is_equal(_y, oth.getY())
                   && is_equal(_z, oth.getZ())); }

            /**
             * @brief equal operator compares two Primitive object
             *
             * @param oth left handle operand
             *
             * @return FALSE if all coordinates equal, another TRUE
             *
             * this method no change object
             *
             * this method no throw exeption
            */
            constexpr bool
            operator != (const Primitive& oth) const noexcept
            { return !(*this == oth); }
    }; // CLASS_PRIMITIVE

    /**
     * @class Vertex implimented real geometric vertex,
     *
     * Vertex is derived @class Primitive
     *
     * construction with (constructor)
    */
    class Vertex : public Primitive
    {
        private:   // DATA
            float _u;       // texture coordinate u
            float _v;       // texture coordinate v

        public:   // CONSTRUCT_DESTRUCT_ASSIGNMENT_OPERATORS
            /**
             * @brief default (constructor) for Vertex
             *
             * this method no throw exeption
            */
            constexpr
            Vertex() noexcept
                : Primitive()
                , _u(0.)
                , _v(0.)
            { }

            /**
             * @brief (constructor) initialize geometric coordinate
             * texture coordinate initialize null
             *
             * @param x value of x coordinate (const reference)
             * @param y value of y coordinate (const reference)
             * @param z value of z coordinate (const reference)
             *
             * this method no throw exeption
            */
            constexpr
            Vertex(const float& x, const float& y, const float& z) noexcept
                : Primitive(std::forward < const float > ( x ),
                            std::forward < const float > ( y ),
                            std::forward < const float > ( z ))
                , _u(0.)
                , _v(0.)
            { }

            /**
             * @brief (constructor) initialize geometric coordinate
             * texture coordinate initialize null
             *
             * @param x value of x coordinate (const r-value reference)
             * @param y value of y coordinate (const r-value reference)
             * @param z value of z coordinate (const r-value reference)
             *
             * this method no throw exeption
            */
            constexpr
            Vertex(const float&& x, const float&& y, const float&& z) noexcept
                : Primitive(std::move ( x ),
                            std::move ( y ),
                            std::move ( z ))
                , _u(0.)
                , _v(0.)
            { }

            /**
             * @brief (constructor) initialize geometric coordinate
             * and texture coordinate
             *
             * @param x value of x coordinate (const reference)
             * @param y value of y coordinate (const reference)
             * @param z value of z coordinate (const reference)
             * @param u value of u coordinate (const reference)
             * @param v value of v coordinate (const reference)
             *
             * this method no throw exeption
            */
            constexpr
            Vertex(const float& x, const float& y, const float& z,
                const float& u, const float& v) noexcept
                : Primitive(std::forward < const float > ( x ),
                            std::forward < const float > ( y ),
                            std::forward < const float > ( z ))
                , _u(u)
                , _v(v)
            { }

            /**
             * @brief (constructor) initialize geometric coordinate
             * and texture coordinate
             *
             * @param x value of x coordinate (const r-value reference)
             * @param y value of y coordinate (const r-value reference)
             * @param z value of z coordinate (const r-value reference)
             * @param u value of u coordinate (const r-value reference)
             * @param v value of v coordinate (const r-value reference)
             *
             * this method no throw exeption
            */
            constexpr
            Vertex(const float&& x, const float&& y, const float&& z,
                const float&& u, const float&& v) noexcept
                : Primitive(std::move ( x ),
                            std::move ( y ),
                            std::move ( z ))
                , _u(std::move ( u ))
                , _v(std::move( v ))
            { }

            /**
             * @brief copy (constructor) for class Vertex
             *
             * @param other object of class Vertex (const reference)
             *
             * this method no throw exeption
            */
            constexpr
            Vertex(const Vertex& other) noexcept
                : Primitive(other)
                , _u(other._u)
                , _v(other._v)
            { }

            /**
             * @brief move (constructor) for class Vertex
             *
             * @param other object of class Vertex (const r-value reference)
             *
             * this method no throw exeption
            */
            constexpr
            Vertex(const Vertex&& other) noexcept
                : Primitive(std::move(other))
                , _u(std::move(other._u))
                , _v(std::move(other._v))
            { }

            /**
             * @brief virtual (destructor) for class Vertex
             *
             * this is the final in object in the base-derived sequence
             *
             * this method no throw exeption
            */
            virtual
            ~Vertex( ) noexcept final
            { }

            /**
             * @brief copy assignment operator for class Vertex
             *
             * @param other object of class Vertex (const reference)
             *
             * @return this Vertex object
             *
             * this method no throw exeption
            */
            constexpr Vertex&
            operator = (const Vertex& other) noexcept
            {
                if (this == &other)
                    return *this;

                _x = other.getX();
                _y = other.getY();
                _z = other.getZ();
                _u = other.getU();
                _v = other.getV();

                return *this;
            }

            /**
             * @brief move asignment operator for class Vertex
             *
             * @param other object of class Vertex (const r-value reference)
             *
             * @return this Vertex object
             *
             * this method no throw exeption
            */
            constexpr Vertex&
            operator = (const Vertex&& other) noexcept
            {
                if (this == &other)
                    return *this;

                _x = std::move(other.getX());
                _y = std::move(other.getY());
                _z = std::move(other.getZ());
                _u = std::move(other.getU());
                _v = std::move(other.getV());

                return *this;
            }

        public:   // SIMPLY_TYPE_GETTER
            /**
             * @brief this method get type of object
             *
             * @return real geometric type
             *
             * this method last in base-derived sequence
             *
             * this method no change object
             *
             * this method no throw exeption
            */
            const simplyType
            getSimplyType() const noexcept final
            { return simplyType::GEOMETRIC_VERTEX; }

        public:   // SETTER_FOO
            /**
             * @brief this method set u texture coordinate
             *
             * @param u value of texture coordinate u
             *
             * this method no throw exeption
            */
            constexpr void
            setU(const float& u) noexcept
            { _u = u; }

            /**
             * @brief this method set v texture coordinate
             *
             * @param v value of texture coordinate v
             *
             * this method no throw exeption
            */
            constexpr void
            setV(const float& v) noexcept
            { _v = v; }

            /**
             * @brief this method set texture coordinate
             *
             * @param u value of texture coordinate u
             * @param v value of texture coordinate v
             *
             * this method no throw exeption
            */
            constexpr void
            setUV(const float& u, const float& v) noexcept
            { _u = u; _v = v; }

        public:    // GETTER_FOO
            /**
             * @brief this method get texture coordinate u
             *
             * @return const reference on u texture coordinate
             *
             * this method no change object
             *
             * this method no throw exeption
            */
            constexpr const float&
            getU() const noexcept
            { return _u; }

            /**
             * @brief this method get texture coordinate v
             *
             * @return const reference on v texture coordinate
             *
             * this method no change object
             *
             * this method no throw exeption
            */
            constexpr const float&
            getV() const noexcept
            { return _v; }

            /**
             * @brief this method get texture coordinate
             *
             * @return const pair as u, v texture coordinate
             *
             * this method no change object
             *
             * this method no throw exeption
            */
            constexpr const uv_t
            getUV() const noexcept
            { return std::make_pair(_u, _v); }

        public:     // LOGIC_OPERATORS
            /**
             * @brief equal operator compare two Vertex
             *
             * @param oth left handle operand
             *
             * @return TRUE if all coordinate is equal, enother FALSE
             *
             * this method no change object
             *
             * this method no throw exeption
            */
            constexpr bool
            operator == (const Vertex& oth) const noexcept
            { return (is_equal(_x, oth.getX())
                   && is_equal(_y, oth.getY())
                   && is_equal(_z, oth.getZ())
                   && is_equal(_u, oth.getU())
                   && is_equal(_v, oth.getV())); }

            /**
             * @brief equal operator compare two Vertex
             *
             * @param oth left handle operand
             *
             * @return FALSE if all coordinate is equal, enother TRUE
             *
             * this method no change object
             *
             * this method no throw exeption
            */
            constexpr bool
            operator != (const Vertex& oth) noexcept
            { return !(*this == oth); }
    }; // CLASS_VERTEX

    /**
     * @class Vector implimented real geometric vector
     *
     * Vector is derived @class Primitive
     *
     * construction with (constructor)
    */
    class Vector : public Primitive
    {
        public:   // CONSTRUCT_DESTRUCT_ASSIGNMENT_OPERATOR
            /**
             * @brief defualt (constructor) for Vector
             *
             * this method no throw exeption
            */
            constexpr
            Vector() noexcept
                : Primitive()
            { }

            /**
             * @brief (constructor) for Vector
             * initialize all vector coordinate
             *
             * @param x value of x coordinate (const reference)
             * @param y value of y coordinate (const reference)
             * @param z value of z coordinate (const reference)
             *
             * this method no throw exeption
            */
            constexpr
            Vector(const float& x, const float& y, const float& z) noexcept
                : Primitive(std::forward < const float > ( x ),
                            std::forward < const float > ( y ),
                            std::forward < const float > ( z ))
            { }

            /**
             * @brief (constructor) for Vector
             * initialize all vector coordinate
             *
             * @param x value of x coordinate (const r-value reference)
             * @param y value of y coordinate (const r-value reference)
             * @param z value of z coordinate (const r-value reference)
             *
             * this method no throw exeption
            */
            constexpr
            Vector(const float&& x, const float&& y, const float&& z) noexcept
                : Primitive(std::move ( x ),
                            std::move ( y ),
                            std::move ( z ))
            { }

            /**
             * @brief copy (constructor) for Vector
             *
             * @param other object of Vector (const reference)
             *
             * this method no throw exeption
            */
            constexpr
            Vector(const Vector& other) noexcept
                : Primitive(other)
            { }

            /**
             * @brief copy (constructor) for Vector
             *
             * @param other object of Vector (const r-value reference)
             *
             * this method no throw exeption
            */
            constexpr
            Vector(const Vector&& other) noexcept
                : Primitive(std::move(other))
            { }

            /**
             * @brief virtual (destructor) for Vector
             *
             * this method last in base-derived sequence
             *
             * this method no throw exeption
            */
            virtual
            ~Vector( ) noexcept final
            { }

            /**
             * @brief copy assignment operator for Vector
             *
             * @param other object of Vector (const reference)
             *
             * this method no throw exeption
            */
            constexpr Vector&
            operator = (const Vector& other) noexcept
            {
                if(this == &other)
                    return *this;

                _x = other._x;
                _y = other._y;
                _z = other._z;

                return *this;
            }

            /**
             * @brief move assignment operator for Vector
             *
             * @param other object of Vector (const r-value reference)
             *
             * this method no throw exeption
            */
            constexpr Vector&
            operator = (const Vector&& other) noexcept
            {
                if(this == &other)
                    return *this;

                _x = std::move ( other._x );
                _y = std::move ( other._y );
                _z = std::move ( other._z );

                return *this;
            }

        public:   // SIMPLY_TYPE_GETTER
            /**
             * @brief this method get type of object
             *
             * @return real geometric type
             *
             * this method last in base-derived sequence
             *
             * this method no change object
             *
             * this method no throw exeption
            */
            virtual const simplyType
            getSimplyType() const noexcept final
            { return simplyType::GEOMETRIC_VECTOR; }

        public:   // VECTOR_WORK
            /**
             * @brief this method count length of vector
             *
             * @return vector length (aka float)
             *
             * this method no change object
             *
             * this method no throw exeption
            */
            constexpr float
            getLength() const noexcept
            { return sqrt(pow(this -> getX(), 2)
                        + pow(this -> getY(), 2)
                        + pow(this -> getZ(), 2)); }

            /**
             * @brief this method normalizing vector
             *
             * this method no throw exeption
            */
            constexpr void
            normalize() noexcept
            {
                float lenght = getLength();

                if(!lenght) return;

                this->_x /= lenght;
                this->_y /= lenght;
                this->_z /= lenght;
            }

            /**
             * @brief this method compare two vector on colinearity
             *
             * @param vec other Vector object
             *
             * @return TRUE if vectors colinear, enother FALSE
             *
             * this method no change object
             *
             * this method no throw exeption
            */
            constexpr bool
            isColinear(const Vector &vec) const noexcept
            { return ( is_equal(vec.getX() / this->getX(), vec.getY() / this->getY())
                    && is_equal(vec.getY() / this->getY(), vec.getZ() / this->getZ())
                    && is_equal(vec.getX() / this->getX(), vec.getZ() / this->getZ())); }

            /**
             * @brief operator asignment summ incrize this object on @param
             *
             * @param vec other Vector object
             *
             * this method no throw exeption
            */
            void
            operator += (const Vector& vec) noexcept
            { _x += vec.getX(); _y += vec.getY(); _z += vec.getZ(); }

            /**
             * @brief operator summ for two Vector
             *
             * @param vec left handle vector
             *
             * @return new vector created as summ this & vec
             *
             * this method no change object
             *
             * this method no throw exeption
            */
            Vector&&
            operator + (const Vector& vec) const noexcept
            { return std::move(Vector(_x + vec.getX(), _y + vec.getY(), _z + vec.getZ())); }

            /**
             * @brief operator asignment multiply increase this vector
             *
             * @param lambda value has increases vector
             *
             * this method no throw exeption
            */
            void
            operator *= (const float& lambda) noexcept
            { _x *= lambda; _y *= lambda; _z *= lambda; }

            /**
             * @brief operator multiply for two Vector
             *
             * @param lambda value has increase
             *
             * @return new vector created as multiply this & lambda
             *
             * this method no change object
             *
             * this method no throw exeption
            */
            Vector&&
            operator * (const float& lambda) const noexcept
            { return std::move(Vector(_x * lambda, _y * lambda, _z * lambda)); }

            /**
             * @brief operator assignment minus decrease this vector
             *
             * @param vec left handle operand
             *
             * this method no throw exeption
            */
            void
            operator -= (Vector &vec) noexcept
            { return *this += vec * (-1.); }

            /**
             * @brief operator minus for two vector
             *
             * @param vec left handle operand
             *
             * @return new Vector created as difference this & vec
             *
             * this method no change object
             *
             * this method no throw exeption
            */
            Vector&&
            operator - (Vector &vec) const noexcept
            { return std::move(*this + vec * (-1.)); }

            /**
             * @brief this method count scalar multiply
             *
             * @param vec other Vector object
             *
             * @return scalar multiple (aka float)
             *
             * this method no change object
             *
             * this method no throw exeption
            */
            constexpr float
            scalarMultiplication(const Vector& vec) const noexcept
            { return vec.getX() * this->getX()
                   + vec.getY() * this->getY()
                   + vec.getZ() * this->getZ(); }

            /**
             * @brief this method count cosinus angle for two vectors
             *
             * @param vec second vector
             *
             * @return angle value (aka float)
             *
             * this method no change object
             *
             * this method no throw exeption
            */
            inline constexpr float
            VectorAngle(const Vector& vec) const noexcept
            { return (scalarMultiplication(vec) / (getLength() * vec.getLength())); }

            /**
             * @brief this method count angle for this vector & surface(XZ)
             *
             * this method no change object
             *
             * this method no throw exeption
            */
            inline float
            normalAngle() const noexcept
            { return VectorAngle(Vector(0., 1., 0.)); }

        public:     // LOGIC_OPERATORS
            /**
             * @brief equal operator compare two Vector
             *
             * @param oth left handle operand
             *
             * @return TRUE if all coordinate is equal, enother FALSE
             *
             * this method no change object
             *
             * this method no throw exeption
            */
            constexpr bool
            operator == (const Vector& oth) noexcept
            { return (is_equal(_x, oth.getX())
                   && is_equal(_y, oth.getY())
                   && is_equal(_z, oth.getZ())); }

            /**
             * @brief equal operator compare two Vector
             *
             * @param oth left handle operand
             *
             * @return FALSE if all coordinate is equal, enother TRUE
             *
             * this method no change object
             *
             * this method no throw exeption
            */
            constexpr bool
            operator != (const Vector& oth) noexcept
            { return !(*this == oth); }
    }; // CLASS_VECTOR

    /**
     * @class Triangle is real geometric type who declaredes as
     * tree object Vertex type, and one normal Vector type
     *
     * construction with (constructor)
    */
    class Triangle
    {
        private:   // TYPES
            using _vertexPtr = std::shared_ptr < Vertex >;
            using _vectorPtr = std::unique_ptr < Vector >;

        private:  // DATA
            _vectorPtr __normal;          // triangle normal        (aka std::unique_ptr<Vector>)
            _vertexPtr __vertex_A;        // first triangle vertex  (aka std::shared_ptr<vertex>)
            _vertexPtr __vertex_B;        // second triangle vertex (aka std::shared_ptr<vertex>)
            _vertexPtr __vertex_C;        // third triangle vertex  (aka std::shared_ptr<vertex>)

        // in triangle vertex_A.z >= vertex_B.z >= vertex_C.z

        public:   // CONSTRUCT_DESTRUCT_ASSIGNMENT_OPERATORS
            /**
             * @brief default (constructor) for Triangle
             * allocation memory for variable
             *
             * this method can throw bedAlloc exeption
            */
            Triangle()
                : __normal   (std::make_unique<Vector>())
                , __vertex_A (std::make_shared<Vertex>())
                , __vertex_B (std::make_shared<Vertex>())
                , __vertex_C (std::make_shared<Vertex>())
            { }

            /**
             * @brief (constructor) for triangle who init all data with r-value reference
             *
             * @param vector normal for this triangle
             * @param vertex_A first vertex
             * @param vertex_B second vertex
             * @param vertex_C third vertex
             *
             * this method no throw exeption
            */
            Triangle(Vector&& vector, _vertexPtr&& vertex_A,
                _vertexPtr&& vertex_B, _vertexPtr&& vertex_C) noexcept
                : __normal  (std::make_unique<Vector>(vector))
                , __vertex_A(std::move(vertex_A))
                , __vertex_B(std::move(vertex_B))
                , __vertex_C(std::move(vertex_C))
            { }

            /**
             * @brief copy (constructor) for Triangle
             *
             * @param other Triangle object
             *
             * this method no throw exeption
            */
            Triangle(const Triangle& other) noexcept
                : __vertex_A (other.__vertex_A)
                , __vertex_B (other.__vertex_B)
                , __vertex_C (other.__vertex_C)
            { normal(); }

            /**
             * @brief move (constructor) for Triangle
             *
             * @param other Triangle object
             *
             * this method no throw exeption
            */
            Triangle(const Triangle&& other) noexcept
                : __vertex_A (std::move(other.__vertex_A))
                , __vertex_B (std::move(other.__vertex_B))
                , __vertex_C (std::move(other.__vertex_C))
            { normal(); }

            /**
             * @brief (destructor) for Triangle
             *
             * this method no throw exeption
            */
            ~Triangle() noexcept
            { }

            /**
             * @brief copy assignment operator for Triangle
             *
             * @param other Triangle object
             *
             * @return this object
             *
             * this method no throw exeption
            */
            Triangle&
            operator=(const Triangle &other) noexcept
            {
                if(this == &other)
                    return *this;

                __vertex_A = other.__vertex_A;
                __vertex_B = other.__vertex_B;
                __vertex_C = other.__vertex_C;

                normal();

                return *this;
            }

            /**
             * @brief move assignment operator for Triangle
             *
             * @param other Triangle object
             *
             * @return this object
             *
             * this method no throw exeption
            */
            Triangle&
            operator=(const Triangle&& other) noexcept
            {
                if(this == &other)
                    return *this;

                __vertex_A = std::move(other.__vertex_A);
                __vertex_B = std::move(other.__vertex_B);
                __vertex_C = std::move(other.__vertex_C);

                normal();

                return *this;
            }

        public:   // SETTER_FOO
            /**
             * @brief this method set value for triangle normal
             *
             * @param vec vector object
             *
             * this method no throw exeption
            */
            void
            setNormal(const Vector& vec) noexcept
            { *__normal = vec; }

            /**
             * @brief this method set value for vertex_A
             *
             * @param vertex_A vertex object
             *
             * this method no throw exeption
            */
            void
            setVertex_A(const Vertex& vertex_A) noexcept
            { *__vertex_A = vertex_A; }

            /**
             * @brief this method set value for vertex_B
             *
             * @param vertex_B vertex object
             *
             * this method no throw exeption
            */
            void
            setVertex_B(const Vertex& vertex_B) noexcept
            { *__vertex_B = vertex_B; }

            /**
             * @brief this method set value for vertex_C
             *
             * @param vertex_C vertex object
             *
             * this method no throw exeption
            */
            void
            setVertex_C(const Vertex& vertex_C) noexcept
            { *__vertex_C = vertex_C; }

            /**
             * @brief this method set value for triangle normal via pointer
             *
             * @param vec vector pointer object (aka std::unique_ptr<vector>)
             *
             * this method no throw exeption
            */
            void
            setNormal(_vectorPtr&& vec) noexcept
            { __normal = std::move(vec); }

            /**
             * @brief this method set value for vertex_A via pointer
             *
             * @param vertex_A vertex pointer object (aka std::shared_ptr<vertex>)
             *
             * this method no throw exeption
            */
            void
            setVertex_A(_vertexPtr vertex_A) noexcept
            { __vertex_A = vertex_A; }

           /**
             * @brief this method set value for vertex_B via pointer
             *
             * @param vertex_B vertex pointer object (aka std::shared_ptr<vertex>)
             *
             * this method no throw exeption
            */
            void
            setVertex_B(_vertexPtr vertex_B) noexcept
            { __vertex_B = vertex_B; }

           /**
             * @brief this method set value for vertex_C via pointer
             *
             * @param vertex_C vertex pointer object (aka std::shared_ptr<vertex>)
             *
             * this method no throw exeption
            */
            void
            setVertex_C(_vertexPtr vertex_C) noexcept
            { __vertex_C = vertex_C; }

           /**
             * @brief this method set value for all data via pointer
             *
             * @param vector   vector pointer object (aka std::shared_ptr<vector>)
             * @param vertex_A vertex pointer object (aka std::shared_ptr<vertex>)
             * @param vertex_B vertex pointer object (aka std::shared_ptr<vertex>)
             * @param vertex_C vertex pointer object (aka std::shared_ptr<vertex>)
             *
             * this method no throw exeption
            */
            void
            set(_vectorPtr&& vector, _vertexPtr vertex_A,
                _vertexPtr vertex_B, _vertexPtr vertex_C) noexcept
            {
                __normal   = std::move(vector);
                __vertex_A = vertex_A;
                __vertex_B = vertex_B;
                __vertex_C = vertex_C;
            }

           /**
             * @brief this method set value for all data
             *
             * @param vector   vector object
             * @param vertex_A vertex object
             * @param vertex_B vertex object
             * @param vertex_C vertex object
             *
             * this method no throw exeption
            */
            void
            set(const Vector& vector, const Vertex& vertex_A,
                const Vertex& vertex_B, const Vertex& vertex_C) noexcept
            {
                *__normal   = vector  ;
                *__vertex_A = vertex_A;
                *__vertex_B = vertex_B;
                *__vertex_C = vertex_C;
            }

           /**
             * @brief this method set value for all vertex via pointer
             *
             * @param vertex_A vertex pointer object (aka std::shared_ptr<vertex>)
             * @param vertex_B vertex pointer object (aka std::shared_ptr<vertex>)
             * @param vertex_C vertex pointer object (aka std::shared_ptr<vertex>)
             *
             * this method no throw exeption
            */
            void
            set(_vertexPtr vertex_A, _vertexPtr vertex_B
                , _vertexPtr vertex_C) noexcept
            {
                __vertex_A = vertex_A;
                __vertex_B = vertex_B;
                __vertex_C = vertex_C;
                normal();
            }

           /**
             * @brief this method set value for all vertex
             *
             * @param vertex_A vertex object
             * @param vertex_B vertex object
             * @param vertex_C vertex object
             *
             * this method no throw exeption
            */
            void
            set(const Vertex& vertex_A, const Vertex& vertex_B
                , const Vertex& vertex_C) noexcept
            {
                *__vertex_A = vertex_A;
                *__vertex_B = vertex_B;
                *__vertex_C = vertex_C;
                normal();
            }

        public:   // GETTER_FOO
            /**
             * @brief this method get triangle normal
             *
             * @return triangle normal via pointer
             *
             * this method no change object
             *
             * this methid no throw exeption
            */
            const Vector&
            getNormal() const noexcept
            { return *__normal; }

            /**
             * @brief this method get first triangle vertex
             *
             * @return triangle vertex via pointer
             *
             * this method no change object
             *
             * this methid no throw exeption
            */
            const _vertexPtr
            getVertex_A() const noexcept
            { return __vertex_A; }

            /**
             * @brief this method get second triangle vertex
             *
             * @return triangle vertex via pointer
             *
             * this method no change object
             *
             * this methid no throw exeption
            */
            const _vertexPtr
            getVertex_B() const noexcept
            { return __vertex_B; }

            /**
             * @brief this method get third triangle vertex
             *
             * @return triangle vertex via pointer
             *
             * this method no change object
             *
             * this methid no throw exeption
            */
            const _vertexPtr
            getVertex_C() const noexcept
            { return __vertex_C; }

            /**
             * @brief this method standartization triangle
             *
             * this method no throw exeption
            */
            void fixTriangle() noexcept
            { moveVertex(); normal(); }

        public:
            /**
             * @brief equal operator compare two Vector
             *
             * @param oth left handle operand
             *
             * @return TRUE if all coordinate is equal, enother FALSE
             *
             * this method no change object
             *
             * this method no throw exeption
            */
            bool
            operator == (const Triangle& oth) const noexcept
            { return *__normal   ==  oth.getNormal()
                  && *__vertex_A == *oth.getVertex_A()
                  && *__vertex_B == *oth.getVertex_B()
                  && *__vertex_C == *oth.getVertex_C(); }

            /**
             * @brief equal operator compare two Vector
             *
             * @param oth left handle operand
             *
             * @return FALSE if all coordinate is equal, enother TRUE
             *
             * this method no change object
             *
             * this method no throw exeption
            */
            bool
            operator != (const Triangle& oth) noexcept
            { return !(*this == oth); }


            /**
             * @brief calculate two 2d vertex on intersection triangles
             * @brief and layer face
             * @param Height layer face height
             * @return two optional point
            */
            cut_t cut(const float& Height) noexcept
            {
                fixTriangle();

                std::cout << '\n' << "CUT" << '\n' << '\n';

                if (__vertex_A -> getZ() < Height
                 || __vertex_C -> getZ() > Height)
                    return {};

                if (is_equal(__vertex_A -> getZ(), Height)
                 && is_equal(__vertex_B -> getZ(), Height))
                    return std::pair ( Point2d( __vertex_A -> getX(),
                                                __vertex_A -> getY() ),
                                       Point2d( __vertex_B -> getX(),
                                                __vertex_B -> getY() ) );

                if (is_equal(__vertex_C -> getZ(), Height)
                 && is_equal(__vertex_B -> getZ(), Height))
                    return std::pair ( Point2d ( __vertex_B -> getX(),
                                                 __vertex_B -> getY() ),
                                       Point2d ( __vertex_C -> getX(),
                                                 __vertex_C -> getY() ) );

                if (is_equal(__vertex_A -> getZ(), Height))
                    return std::pair ( Point2d ( __vertex_A -> getX(),
                                                 __vertex_A -> getY() ),
                                       std::nullopt );

                if (is_equal(__vertex_C -> getZ(), Height))
                    return std::pair ( Point2d ( __vertex_C -> getX(),
                                                 __vertex_C -> getY() ),
                                       std::nullopt );

                float h              =             Height            ;
                float n_x            =           __normal   -> getX();
                float n_y            =           __normal   -> getY();
                float n_z            =           __normal   -> getZ();
                float a_x            =           __vertex_A -> getX();
                float a_y            =           __vertex_A -> getY();
                float a_z            =           __vertex_A -> getZ();
                float b_x            =           __vertex_B -> getX();
                float b_y            =           __vertex_B -> getY();
                float b_z            =           __vertex_B -> getZ();
                float c_x            =           __vertex_C -> getX();
                float c_y            =           __vertex_C -> getY();
                float c_z            =           __vertex_C -> getZ();

                float k = - n_x / n_y;
                float p = (n_x * a_x + n_y * a_y - n_z * (h - a_z)) / n_y;

                float Kac = (a_y - c_y) / (a_x - c_x);
                float Bac = (c_y * (a_x - c_x) - c_x * (a_y - c_y)) / (a_x - c_x);

                float l_x = (p - Bac) / (k - Kac);
                float l_y = k * l_x + p;

                if(is_equal(__vertex_B -> getZ(), Height))
                    return std::pair ( Point2d ( __vertex_B -> getX(),
                                                 __vertex_B -> getY() ),
                                       Point2d ( l_x, l_y ) );

                float x_1 = __vertex_B -> getX();
                float y_1 = __vertex_B -> getY();

                float x_2 = 0.;
                float y_2 = 0.;

                if(__vertex_B -> getZ() < Height)
                {
                    x_2 = __vertex_A -> getX();
                    y_2 = __vertex_A -> getY();
                }
                else
                {
                    x_2 = __vertex_C -> getX();
                    y_2 = __vertex_C -> getY();
                }

                float K12 = (y_2 - y_1) / (x_2 - x_1);
                float B12 = (y_1 * (x_2 - x_1) - x_1 * (y_2 - y_1)) / (x_2 - x_1);

                float k_x = (p - B12) / (k - K12);
                float k_y = k * k_x + p;

                return std::pair ( Point2d ( k_x, k_y ),
                                   Point2d ( l_x, l_y ) );
            }

            /**
             * @brief check triangle incidence on range
             * @param height is height of layer face
             * @return true if height in triangle gabarit range
             */
            inline bool
            onRange(float height) const noexcept
            { return __vertex_A -> getZ() > height
                  && __vertex_C -> getZ() < height; }


        private:    // INTERNAL_METHOD
            /**
             * @brief calculate normal use vertex coord
             *
             * this method no throw exeption
            */
            inline void
            normal() noexcept
            {
                Vector V1( __vertex_A -> getX() - __vertex_B -> getX()
                         , __vertex_A -> getY() - __vertex_B -> getY()
                         , __vertex_A -> getZ() - __vertex_B -> getZ() );

                Vector V2( __vertex_B -> getX() - __vertex_C -> getX()
                         , __vertex_B -> getY() - __vertex_C -> getY()
                         , __vertex_B -> getZ() - __vertex_C -> getZ() );

                __normal -> setCoordinate( V1.getY() * V2.getZ() - V2.getY() * V1.getZ()
                                         , V1.getX() * V2.getZ() - V2.getX() * V1.getZ()
                                         , V1.getX() * V2.getY() - V2.getX() * V1.getY() );

                __normal -> normalize();
            }

            /**
             * @brief this method change vertex position if
             * !(vertex_a.z >= vartex_b.z >= vertex_c.z)
             *
             * this method no throw exeption
            */
            inline void
            moveVertex() noexcept
            {
                auto z_a = __vertex_A -> getZ();
                auto z_b = __vertex_B -> getZ();
                auto z_c = __vertex_C -> getZ();

                if(z_c >= z_b)
                    if(z_c >= z_a)
                    {
                        std::swap(__vertex_A, __vertex_C);
                        if(z_a >= z_b) std::swap(__vertex_C, __vertex_B);
                    }
                    else std::swap(__vertex_B, __vertex_A);
                else if(z_b >= z_a)
                {
                    std::swap(__vertex_B, __vertex_A);
                    if(z_c >= z_a) std::swap(__vertex_C, __vertex_B);
                }
            }
    }; // CLASS_TRIANGLE

    // TYPES
    using _vectorPtr   = std::unique_ptr < Vector >;
    using _vertexPtr   = std::shared_ptr < Vertex >;
    using _trianglePtr = std::shared_ptr < Triangle >;   // !!! Maybe unique?

}; // NAMESPACE_GEOMETRY

#endif //GEOMETRY_HPP
