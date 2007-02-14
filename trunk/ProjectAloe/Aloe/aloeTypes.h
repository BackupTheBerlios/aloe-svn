#ifndef ALOE_INCLUDED_ALOE_TYPES_H
#define ALOE_INCLUDED_ALOE_TYPES_H

#include "Aloe/aloePP.h"
#include "Aloe/aloeError.h"

#include <stddef.h>
#include <time.h>

namespace Aloe {
    
    // typy podstawowe
    namespace Types {

#ifdef WIN32
        // typy specyficzne
        typedef unsigned __int64 ULongLong;
        typedef unsigned __int64 UInt64;
        typedef unsigned __int32 UInt32;
        typedef unsigned __int16 UInt16;
        typedef unsigned __int8  UInt8;
        
        typedef __int64 Int64;
        typedef __int32 Int32;
        typedef __int16 Int16;
        typedef __int8  Int8;
#else
        // typy specyficzne
        typedef unsigned int64_t ULongLong;
        typedef unsigned int64_t UInt64;
        typedef unsigned int32_t UInt32;
        typedef unsigned int16_t UInt16;
        typedef unsigned int8_t  UInt8;
        
        typedef int64_t Int64;
        typedef int32_t Int32;
        typedef int16_t Int16;
        typedef int8_t  Int8;
#endif
        typedef float       Float32;
        typedef double      Float64;
        typedef long double BigFloat;
        
        typedef unsigned long  ULong;
        typedef unsigned int   UInt;
        typedef unsigned short UShort;
        typedef unsigned char  UByte;
        
        // typy ANSI
        typedef size_t    SizeType;
        typedef clock_t   ClockType;
        typedef time_t    TimeType;
        typedef ptrdiff_t PtrDiffType;
        
        // typy standardowe
        typedef Int64  LongLong;
        typedef double Float;
        typedef signed long   Long;
        typedef signed int    Int;
        typedef signed short  Short;
        typedef signed char   Byte;
        typedef bool   Bool;
        
        // typy znakowe
        typedef wchar_t WideChar;
        typedef char    Char;

        // typy buforów tylko do odczytu (C = Const)
        typedef const Char      *CStr;
        typedef const WideChar  *CWideStr;
        typedef const UByte     *CUByteArray;
        typedef const UInt      *CUIntArray;
        typedef const UShort    *CUShortArray;
        typedef const Int       *CIntArray;
        typedef const Short     *CShortArray;
        typedef const Float     *CFloatArray;
        typedef const Float32   *CFloat32Array;
        typedef const BigFloat  *CBigFloatArray;
        
        // typy buforów do odczytu i zapisu (NC = Non-Const)
        typedef Char            *NCStr;
        typedef WideChar        *NCWideStr;
        typedef UByte           *NCUByteArray;
        typedef UInt            *NCUIntArray;
        typedef UShort          *NCUShortArray;
        typedef Int             *NCIntArray;
        typedef Short           *NCShortArray;
        typedef Float           *NCFloatArray;
        typedef Float32         *NCFloat32Array;
        typedef BigFloat        *NCBigFloatArray;

        // wskaŸnik bez typu
        typedef void        *RawPointer;
        typedef void        *NCRawPointer;
        // j.w. tylko do odczytu
        typedef const void  *CRawPointer;
        

        union None
        {
            template< class T > Bool operator == ( const T & ) { return false; }
            Bool operator == ( const None & ) { return true; }
        };
        
        union LongPointer
        {
            LongPointer() { p = 0; l = 0; }
            LongPointer( Long il ) { p = 0; l = il; }
            LongPointer( RawPointer ip ) { l = 0; p = ip; }
            RawPointer p;
            Long l;
            Bool operator == ( const LongPointer &o ) const { return (p == o.p); }
            Bool operator < ( const LongPointer &o ) const { return (p < o.p); }
            RawPointer & getPointer() { return p; }
            Long       & getLong   () { return l; }
            const RawPointer & getPointer() const { return p; }
            const Long       & getLong   () const { return l; }
        };
    };//Types

    // funkcje uzytkowe
    namespace Utils {
        
        template< class T > Types::None varSwap( T &x, T &y )
        {
            T a( x );
            x = y;
            y = a;
            return Types::None();
        }

        template< class T, class C > const T & varMin( const T &x, const C &y )
        {
            return ( x < y ? x : y );
        }
        
        template< class T, class C > const T & varMax( const T &x, const C &y )
        {
            return ( y < x ? x : y );
        }
        
        template< class _T1, class _T2 > _T1 copyCast( const _T2 &x )
        {
            char b[ sizeof( _T1 ) > sizeof( _T2 ) ? sizeof( _T1 ) : sizeof( _T2 ) ] = {0, };
            (*reinterpret_cast< _T2 *>( b )) = x;
            return (*reinterpret_cast< _T1 *>( b ));
        }
    };//Utils

    // typy wyzsze
    namespace Types {

        union Color32;
        struct Point2i;
        struct Vector2i;
        struct Recti;

        union Color32
        {
            struct
            {
                UByte red;
                UByte green;
                UByte blue;
                UByte alpha;
            };
            ULong longWord;

            Color32( ULong lw ) : longWord( lw )
            {}

            Color32( UByte r, UByte g, UByte b, UByte a ) : red(r), green(g), blue(b), alpha(a)
            {}
            
            Color32( Int r, Int g, Int b, Int a ) : red(r), green(g), blue(b), alpha(a)
            {}
            
            Color32( Float r, Float g, Float b, Float a )
                : red  ( static_cast< UByte >( r*255.0 ))
                , green( static_cast< UByte >( g*255.0 ))
                , blue ( static_cast< UByte >( b*255.0 ))
                , alpha( static_cast< UByte >( a*255.0 ))
            {}
            
            UByte Redub() { return red; }
            UByte Greenub() { return green; }
            UByte Blueub() { return blue; }
            UByte Alphaub() { return alpha; }

            Int Redi()   { return static_cast< Int >( red ); }
            Int Greeni() { return static_cast< Int >( green ); }
            Int Bluei()  { return static_cast< Int >( blue ); }
            Int Alphai() { return static_cast< Int >( alpha ); }
            
            Float Redf()   { return static_cast< Float >( red )/255.0; }
            Float Greenf() { return static_cast< Float >( green )/255.0; }
            Float Bluef()  { return static_cast< Float >( blue )/255.0; }
            Float Alphaf() { return static_cast< Float >( alpha )/255.0; }
        };

        struct Point2i
        {
            Int x;
            Int y;

            Point2i( Int ix = 0, Int iy = 0 ): x( ix ), y( iy ) {}
            explicit Point2i( const Vector2i &v );

            Point2i & operator += ( const Vector2i &v );
            Point2i & operator -= ( const Vector2i &v );
        };

        struct Vector2i
        {
            Int dx;
            Int dy;

            Vector2i( Int idx = 0, Int idy = 0 ): dx( idx ), dy( idy ) {}
            explicit Vector2i( const Point2i &p );

            Vector2i & operator += ( const Vector2i &v );
            Vector2i & operator -= ( const Vector2i &v );
            Vector2i & operator *= ( Float c );
            Vector2i & operator /= ( Float c );
            Vector2i operator - () { return Vector2i( -dx, -dy ); }
        };

        struct Recti
        {
            Int x1;
            Int y1;
            Int x2;
            Int y2;

            Recti(): x1(0), y1(0), x2(0), y2(0) {}
            Recti( const Point2i &ul, const Point2i &br )
                : x1( ul.x )
                , y1( ul.y )
                , x2( br.x )
                , y2( br.y )
                {}
            Recti( const Point2i &ul, const Vector2i &s )
                : x1( ul.x )
                , y1( ul.y )
                , x2( ul.x + s.dx )
                , y2( ul.y + s.dy )
                {}
            Recti & fixCoords()
            {
                if ( x1 > x2 ) { Aloe::Utils::varSwap( x1, x2 ); }
                if ( y1 > y2 ) { Aloe::Utils::varSwap( y1, y2 ); }
                return (*this);
            }

            Recti & operator += ( const Vector2i v ) { x1 += v.dx; x2 += v.dx; y1 += v.dy; y2 += v.dy; return (*this); }
            Recti & operator -= ( const Vector2i v ) { x1 -= v.dx; x2 -= v.dx; y1 -= v.dy; y2 -= v.dy; return (*this); }

            struct corrner
            {
                Int &x;
                Int &y;

                corrner( Int &rx, Int &ry ): x( rx ), y( ry ) {}

                operator Point2i () const { return Point2i( x, y ); }
                corrner & operator = ( const Point2i &p ) { x = p.x; y = p.y; return (*this); }
                corrner & operator += ( const Vector2i &v ) { x += v.dx; y += v.dy; return (*this); }
                corrner & operator -= ( const Vector2i &v ) { x -= v.dx; y -= v.dy; return (*this); }
            };

            corrner upperLeft  () { return corrner( x1, y1 ); }
            corrner upperRight () { return corrner( x2, y1 ); }
            corrner bottomLeft () { return corrner( x1, y2 ); }
            corrner bottomRight() { return corrner( x2, y2 ); }

            Point2i upperLeft  () const { return Point2i( x1, y1 ); }
            Point2i upperRight () const { return Point2i( x2, y1 ); }
            Point2i bottomLeft () const { return Point2i( x1, y2 ); }
            Point2i bottomRight() const { return Point2i( x2, y2 ); }

            Int width () const { return x2 - x1; }
            Int height() const { return y2 - y1; }

            bool empty() const
            {
                return (0 == width() || 0 == height());
            }

            bool intersectWith( const Recti &o )
            {
                if ( o.empty() )
                    return false;

                if ( x1 >= o.x2 || o.x1 >= x2 )
                    return false;

                if ( y1 >= o.y2 || o.y1 >= y2 )
                    return false;

                if ( o.x1 > x1 )
                    x1 = o.x1;
                
                if ( o.x2 < x2 )
                    x2 = o.x2;
                
                if ( o.y1 > y1 )
                    y1 = o.y1;
                
                if ( o.y2 < y2 )
                    y2 = o.y2;

                return true;
            }

            Recti & growToFit( const Recti &r )
            {
                if ( r.x1 < x1 )
                    x1 = r.x1;

                if ( r.x2 > x2 )
                    x2 = r.x2;
                
                if ( r.y1 < y1 )
                    y1 = r.y1;

                if ( r.y2 > y2 )
                    y2 = r.y2;

                return (*this);
            }
        };

        inline Point2i::Point2i( const Vector2i &v )
        {
            x = v.dx;
            y = v.dy;
        }

        inline Vector2i::Vector2i( const Point2i &p )
        {
            dx = p.x;
            dy = p.y;
        }

        inline Point2i & Point2i::operator += ( const Vector2i &v )
        {
            x += v.dx;
            y += v.dy;
            return (*this);
        }


        inline Point2i & Point2i::operator -= ( const Vector2i &v )
        {
            x -= v.dx;
            y -= v.dy;
            return (*this);
        }


        inline Vector2i & Vector2i::operator += ( const Vector2i &v )
        {
            dx += v.dx;
            dy += v.dy;
            return (*this);
        }


        inline Vector2i & Vector2i::operator -= ( const Vector2i &v )
        {
            dx -= v.dx;
            dy -= v.dy;
            return (*this);
        }


        inline Vector2i & Vector2i::operator *= ( Float c )
        {
            dx = (Int)((Float)dx * c);
            dy = (Int)((Float)dy * c);
            return (*this);
        }


        inline Vector2i & Vector2i::operator /= ( Float c )
        {
            dx = (Int)((Float)dx / c);
            dy = (Int)((Float)dy / c);
            return (*this);
        }

        inline Vector2i operator - ( const Point2i &p1, const Point2i &p2 )
        {
            return Vector2i( p1.x - p2.x, p1.y - p2.y );
        }

        inline Point2i operator + ( Point2i p, const Vector2i &v ) { return (p += v); }
        inline Point2i operator - ( Point2i p, const Vector2i &v ) { return (p -= v); }

        inline Vector2i operator + ( Vector2i v1, const Vector2i &v2 ) { return (v1 += v2); }
        inline Vector2i operator - ( Vector2i v1, const Vector2i &v2 ) { return (v1 -= v2); }
        inline Vector2i operator * ( Vector2i v, Float c ) { return (v *= c); }
        inline Vector2i operator / ( Vector2i v, Float c ) { return (v /= c); }

        inline Recti operator + ( Recti r, const Vector2i &v ) { return ( r += v ); }
        inline Recti operator - ( Recti r, const Vector2i &v ) { return ( r -= v ); }

        struct Identifier
        {
            LongPointer lpIdent;            
			Identifier() {}
            Identifier( LongPointer ident ) : lpIdent( ident ) {}
            Bool operator == ( const Identifier &o ) const { return (lpIdent == o.lpIdent); }
            Bool operator < ( const Identifier &o ) const { return (lpIdent < o.lpIdent); }
        };

        template< ALOE_PP_TEMPLATE_MAX( NONE, COMMA, class, A,, = None ) > struct Tuple
        {
            ALOE_PP_TEMPLATE_MAX( NONE, SEMICOLON, typedef, A, T, );
            ALOE_PP_TEMPLATE_MAX( NONE, SEMICOLON, byValue, A, m_, );

#define ALOE_PP_Types__Tuple__ctor( N ) \
            Tuple( ALOE_PP_TEMPLATE_R( N, NONE, COMMA, byConstReference, A, a, ) ) \
                : ALOE_PP_TEMPLATE_R( N, NONE, COMMA, initFrom, m_, a, ) \
            {}

            ALOE_PP_GENERATE_MAX( NONE, SEMICOLON, Types__Tuple__ctor );

            Tuple() {}
            
            template< ALOE_PP_TEMPLATE_MAX( NONE, COMMA, class, B,, ) >
                Tuple( const Tuple< ALOE_PP_TEMPLATE_MAX( NONE, COMMA, getClass, B,, ) > &t )
                : ALOE_PP_TEMPLATE_MAX( NONE, COMMA, initFrom, m_, t.m_, )
                {}
        };

    };//Types

    struct IProvider;
    
    struct IRefCount
    {
        virtual void AddRef() = 0;
        virtual Types::Bool RemRef() = 0;
    };
    
    namespace Utils {

        template< class Interface = IProvider > struct SmartPtr;

#define ALOE_PP_make_tuple__definition( N ) \
        template< ALOE_PP_TEMPLATE_R( N, NONE, COMMA, class, A, a, ) > \
            Types::Tuple< ALOE_PP_TEMPLATE_R( N, NONE, COMMA, getClass, A, a, ) > \
            make_tuple( ALOE_PP_TEMPLATE_R( N, NONE, COMMA, byConstReference, A, a, ) ) \
            { \
                return Types::Tuple< ALOE_PP_TEMPLATE_R( N, NONE, COMMA, getClass, A, a, ) > \
                    ( ALOE_PP_TEMPLATE_R( N, NONE, COMMA, getValue, A, a, ) ); \
            }
    
        ALOE_PP_GENERATE_MAX( NONE, SEMICOLON, make_tuple__definition );
            
    };
    
    namespace Detail {
        
        template< class Interface, class R, class Meth > struct MethodCaller;

        template< class Ptr, class Interface, class ReferenceType >
            ReferenceType
            make_property( const Ptr &, ReferenceType property( const Utils::SmartPtr< Interface > & ));

#define ALOE_PP_make_property__declaration( N ) \
        template< class Ptr, class Interface, class R ALOE_PP_TEMPLATE_R( N, COMMA, COMMA, class, A,, ) > \
            MethodCaller< Interface, R, R (Interface::*)( ALOE_PP_TEMPLATE_R( N, NONE, COMMA, getClass, A,, ) ) > \
            make_property( const Ptr &, R (Interface::*property)( ALOE_PP_TEMPLATE_R( N, NONE, COMMA, getClass, A,, )) );
        
        ALOE_PP_make_property__declaration( 0 );
        ALOE_PP_GENERATE_MAX( NONE, SEMICOLON, make_property__declaration );

        template< class T > struct PropertyTraits;

        template< class Interface, class ReferenceType >
            struct PropertyTraits< ReferenceType (*)( const Utils::SmartPtr< Interface > & ) >
            {
                typedef Interface InterfaceType;
                typedef ReferenceType PropertyType;
            };

#define ALOE_PP_PropertyTraits__MethodCaller( N ) \
        template< class Interface, class R ALOE_PP_TEMPLATE_R( N, COMMA, COMMA, class, A,, ) > \
            struct PropertyTraits< R (Interface::*)( ALOE_PP_TEMPLATE_R( N, NONE, COMMA, getClass, A,, )) > \
            { \
                typedef Interface InterfaceType; \
                typedef Detail::MethodCaller< Interface, R, R (Interface::*)( ALOE_PP_TEMPLATE_R( N, NONE, COMMA, getClass, A,, )) > PropertyType; \
            };
            
        ALOE_PP_PropertyTraits__MethodCaller( 0 );
        ALOE_PP_GENERATE_MAX( NONE, SEMICOLON, PropertyTraits__MethodCaller );

    };//Detail

    namespace Utils {

        template< class Interface > struct SmartPtr
        {
            Interface         *m_object;
            Aloe::IRefCount   *m_count;

            SmartPtr() : m_object(0), m_count(0)
            {
            }

            SmartPtr( Interface *p, Aloe::IRefCount *c ) : m_object( p ), m_count( c ) 
            {
            }

            SmartPtr( const SmartPtr &p ) : m_object(p.m_object), m_count(p.m_count)
            {
                AddRef();
            }

            ~SmartPtr()
            {
                RemRef();
            }

            SmartPtr & operator = ( const SmartPtr &p )
            {
                SmartPtr q( p );
                varSwap( m_object  , q.m_object );
                varSwap( m_count, q.m_count );
                return (*this);
            }

            SmartPtr & AddRef()
            {
                if ( m_count )
                    m_count->AddRef();

                return (*this);
            }

            SmartPtr & RemRef()
            {   
                if ( m_count )
                {
                    if ( m_count->RemRef() )
                    {
                        m_object = NULL;
                        m_count = NULL;
                    }
                }

                return (*this);
            }

            template< class PropertyType >
                typename Aloe::Detail::PropertyTraits< PropertyType >::PropertyType operator [] ( PropertyType property )
                {
                    return Detail::make_property( (*this), property );
                }

            template< class Ptr >
                bool QueryFrom( const Ptr &ptr )
                {
                    if ( !ptr )
                        return false;
                    SmartPtr tmp;
                    varSwap( *this, tmp );
                    return ptr->Query( Interface::IId(), (Types::RawPointer&)m_object, m_count );
                }

            template< class InterfaceType >
                bool QueryTo( SmartPtr< InterfaceType > &ptr )
                {
                    if ( !m_object )
                        return false;
                    SmartPtr< InterfaceType > tmp;
                    varSwap( ptr, tmp );
                    return m_object->Query( InterfaceType::IId(), (Types::RawPointer&)ptr.m_object, ptr.m_count );
                }

            Interface * operator -> () const
            {
                return m_object;
            }

            Interface & operator * () const
            {
                return *m_object;
            }

            Interface * get() const
            {
                return m_object;
            }

            bool isNull () const
            {
                return !m_object;
            }

            bool isLess ( const SmartPtr &p ) const
            {
                return m_object < p.m_object;
            }

            bool operator < ( const SmartPtr &p ) const
            {
                return isLess( p );
            }

            bool operator ! () const
            {
                return isNull();
            }
        };
    };
    
    namespace Detail {

        template< class _Tx > struct CArrayDeletter : IRefCount
        {
            Types::Long m_iCount;
            _Tx        *m_vArray;

            CArrayDeletter( _Tx *vArray ) : m_vArray( vArray ), m_iCount(1)
            {}

            ~CArrayDeletter()
            {
                delete [] m_vArray;
            }

            void AddRef()
            {
                ++m_iCount;
            }

            Types::Bool RemRef()
            {
                if ( 0 == --m_iCount )
                {
                    delete this;
                    return true;
                }
                return false;
            }
        };

    };// namespace Detail

    namespace Utils {

        template< class _Tx > struct ArrayOf
        {
            Types::SizeType      m_size;
            _Tx                 *m_objects;
            Aloe::IRefCount     *m_count;

            ArrayOf() : m_size(0), m_objects(0), m_count(0)
            {}

            ArrayOf( Types::SizeType s, _Tx *p, Aloe::IRefCount *d ) : m_size(s), m_objects(p), m_count(d)
            {}

            ArrayOf( const ArrayOf &other ) : m_size( other.m_size ), m_objects( other.m_objects ), m_count( other.m_count )
            {
                AddRef();
            }

            template< class _Ty >
                explicit ArrayOf( const ArrayOf< _Ty >&other ) : m_objects( reinterpret_cast< _Tx *>( other.m_objects ))
                , m_count( other.m_count ), m_size( sizeof( _Tx ) * (other.m_size / sizeof( _Ty )) )
                {
                }

            ArrayOf( Types::SizeType s ) : m_size(s)
            {
                if ( m_size > 0 )
                {
                    m_objects = new _Tx[ s ];
                    m_count = new Aloe::Detail::CArrayDeletter< _Tx >( m_objects );
                }
                else {
                    m_objects = NULL;
                    m_count = NULL;
                }
            }

            ArrayOf( Types::SizeType s, const _Tx &v ) : m_size(s)
            {
                if ( m_size > 0 )
                {
                    m_objects = new _Tx[ s ];
                    m_count = new Aloe::Detail::CArrayDeletter< _Tx >( m_objects );

                    for ( _Tx *p = begin(); p != end(); ++p )
                    {
                        *p = v;
                    }
                }
                else {
                    m_objects = NULL;
                    m_count = NULL;
                }
            }

            ~ArrayOf()
            {
                RemRef();
            }

            ArrayOf< _Tx > & Resize( Types::SizeType s, const _Tx &value )
            {
                ArrayOf< _Tx > other( s );
                _Tx *p = begin();
                _Tx *q = other.begin();
                for ( ; p != end() && q != other.end(); ++p, ++q )
                {
                    *q = *p;
                }
                for ( ; q != other.end(); ++q )
                {
                    *q = value;
                }
                varSwap( m_objects, other.m_objects );
                varSwap( m_count, other.m_count );
                varSwap( m_size, other.m_size );
                return (*this);
            }

            ArrayOf< _Tx > & Resize( Types::SizeType s )
            {
                ArrayOf< _Tx > other( s );
                for ( _Tx *p = begin(), *q = other.begin(); p != end() && q != other.end(); ++p, ++q )
                {
                    *q = *p;
                }
                varSwap( m_objects, other.m_objects );
                varSwap( m_count, other.m_count );
                varSwap( m_size, other.m_size );
                return (*this);
            }

            ArrayOf< _Tx > & AddRef()
            {
                if ( m_count )
                    m_count->AddRef();
                return (*this);
            }

            ArrayOf< _Tx > & RemRef()
            {
                if ( m_count )
                {
                    if ( m_count->RemRef() )
                    {
                        m_objects = NULL;
                        m_count = NULL;
                        m_size = 0;
                    }
                }
                return (*this);
            }

            ArrayOf< _Tx > & operator = ( const ArrayOf< _Tx > &other )
            {
                ArrayOf< _Tx > q( other );
                varSwap( m_objects  , q.m_objects );
                varSwap( m_count, q.m_count );
                varSwap( m_size, q.m_size );
                return (*this);
            }

            _Tx & operator [] ( Types::SizeType index )
            {
                if ( index >= m_size )
                    throw Errors::Error_BadArrayIndex();

                return m_objects[ index ];
            }

            const _Tx & operator [] ( Types::SizeType index ) const
            {
                if ( index >= m_size )
                    throw Errors::Error_BadArrayIndex();

                return m_objects[ index ];
            }

            _Tx * begin() const
            {
                return m_objects;
            }

            _Tx * end() const
            {
                return (m_objects + m_size);
            }

            Types::SizeType size() const
            {
                return m_size;
            }

            void resize( Types::SizeType s )
            {
                Resize( s );
            }

            bool empty() const
            {
                return !m_objects;
            }

            bool operator ! () const
            {
                return empty();
            }
        };

        template< class _Tx > struct ArrayOf< SmartPtr< _Tx > >
        {
            Types::SizeType      m_size;
            SmartPtr< _Tx >     *m_objects;
            Aloe::IRefCount     *m_count;

            ArrayOf() : m_size(0), m_objects(0), m_count(0)
            {}

            ArrayOf( Types::SizeType s, _Tx *p, Aloe::IRefCount *d ) : m_size(s), m_objects(p), m_count(d)
            {}

            ArrayOf( const ArrayOf &other ) : m_size( other.m_size ), m_objects( other.m_objects ), m_count( other.m_count )
            {
                AddRef();
            }

            template< class _Ty >
                explicit ArrayOf( const ArrayOf< SmartPtr< _Ty > > &other ) : m_size( other.m_size )
                {
                    m_objects = new SmartPtr< _Tx >[ m_size ];
                    m_count = new Aloe::Detail::CArrayDeletter< SmartPtr< _Tx > >( m_objects );
                    SmartPtr< _Ty > *p = other.begin();
                    SmartPtr< _Tx > *q = begin();
                    for (; p != other.end(); ++p, ++q )
                    {
                        q->QueryFrom( *p );
                    }
                }

            ArrayOf( Types::SizeType s ) : m_size(s)
            {
                if ( m_size > 0 )
                {
                    m_objects = new SmartPtr< _Tx >[ s ];
                    m_count = new Aloe::Detail::CArrayDeletter< SmartPtr< _Tx > >( m_objects );
                }
                else {
                    m_objects = NULL;
                    m_count = NULL;
                }
            }

            ArrayOf( Types::SizeType s, const _Tx &v ) : m_size(s)
            {
                if ( m_size > 0 )
                {
                    m_objects = new SmartPtr< _Tx >[ s ];
                    m_count = new Aloe::Detail::CArrayDeletter< SmartPtr< _Tx > >( m_objects );

                    for ( _Tx *p = begin(); p != end(); ++p )
                    {
                        *p = v;
                    }
                }
                else {
                    m_objects = NULL;
                    m_count = NULL;
                }
            }

            ~ArrayOf()
            {
                RemRef();
            }

            ArrayOf< SmartPtr< _Tx > > & Resize( Types::SizeType s, const _Tx &value )
            {
                ArrayOf< SmartPtr< _Tx > > other( s );
                SmartPtr< _Tx > *p = begin();
                SmartPtr< _Tx > *q = other.begin();
                for ( ; p != end() && q != other.end(); ++p, ++q )
                {
                    *q = *p;
                }
                for ( ; q != other.end(); ++q )
                {
                    *q = value;
                }
                varSwap( m_objects, other.m_objects );
                varSwap( m_count, other.m_count );
                varSwap( m_size, other.m_size );
                return (*this);
            }

            ArrayOf< SmartPtr< _Tx > > & Resize( Types::SizeType s )
            {
                ArrayOf< SmartPtr< _Tx > > other( s );
                for ( SmartPtr< _Tx > *p = begin(), *q = other.begin(); p != end() && q != other.end(); ++p, ++q )
                {
                    *q = *p;
                }
                varSwap( m_objects, other.m_objects );
                varSwap( m_count, other.m_count );
                varSwap( m_size, other.m_size );
                return (*this);
            }

            ArrayOf< SmartPtr< _Tx > > & Clean()
            {
                Types::Int iCount = 0;
                for ( SmartPtr< _Tx > *p = begin(); p != end(); ++p )
                {
                    iCount += !!(*p);
                }
                ArrayOf< SmartPtr< _Tx > > other( iCount );
                for ( SmartPtr< _Tx > *p = begin(), *q = other.begin(); p != end(); ++p )
                {
                    if ( !!(*p) )
                    {
                        *q = *p;
                        ++q;
                    }
                }
                varSwap( m_objects, other.m_objects );
                varSwap( m_count, other.m_count );
                varSwap( m_size, other.m_size );
                return (*this);
            }

            ArrayOf< SmartPtr< _Tx > > & AddRef()
            {
                if ( m_count )
                    m_count->AddRef();
                return (*this);
            }

            ArrayOf< SmartPtr< _Tx > > & RemRef()
            {
                if ( m_count )
                {
                    if ( m_count->RemRef() )
                    {
                        m_objects = NULL;
                        m_count = NULL;
                        m_size = 0;
                    }
                }
                return (*this);
            }

            ArrayOf< SmartPtr< _Tx > > & operator = ( const ArrayOf< SmartPtr< _Tx > > &other )
            {
                ArrayOf< _Tx > q( other );
                varSwap( m_objects, q.m_objects );
                varSwap( m_count, q.m_count );
                varSwap( m_size, q.m_size );
                return (*this);
            }

            SmartPtr< _Tx > & operator [] ( Types::SizeType index )
            {
                if ( index >= m_size )
                    throw Errors::Error_BadArrayIndex();

                return m_objects[ index ];
            }
            
            const SmartPtr< _Tx > & operator [] ( Types::SizeType index ) const 
            {
                if ( index >= m_size )
                    throw Errors::Error_BadArrayIndex();

                return m_objects[ index ];
            }

            SmartPtr< _Tx > * begin() const
            {
                return m_objects;
            }

            SmartPtr< _Tx > * end() const
            {
                return (m_objects + m_size);
            }

            Types::SizeType size() const
            {
                return m_size;
            }

            void resize( Types::SizeType s )
            {
                Remsize( s );
            }

            bool empty() const
            {
                return !m_objects;
            }

            bool operator ! () const
            {
                return empty();
            }
        };

        template< class _Tx > struct VectorOf
        {
            ArrayOf< _Tx > m_array;
            Types::SizeType m_size;

            VectorOf() : m_size(0)
            {
            }

            VectorOf( Types::SizeType size )
            {
                m_array.Resize( size );
                m_size = size;
            }

            VectorOf( Types::SizeType size, const _Tx &x )
            {
                m_array.Resize( size, x );
                m_size = size;
            }

            VectorOf< _Tx > & push_back( const _Tx &x )
            {
                while ( m_array.size() <= m_size )
                {
                    m_array.resize( m_array.empty() ? 4 : m_array.size() * 2 );
                }
                m_array[ m_size++ ] = x;

                return (*this);
            }

            VectorOf< _Tx > & pop_back( _Tx &x )
            {
                if ( m_size > 0 )
                {
                    x = m_array[ --m_size ];
                    m_array[ m_size ] = _Tx();
                }
                return (*this);
            }
            
            VectorOf< _Tx > & pop_back()
            {
                if ( m_size > 0 )
                {
                    m_array[ --m_size ] = _Tx();
                }
                return (*this);
            }
            
            VectorOf< _Tx > & resize( Types::SizeType s )
            {
                reserve( s );

                while ( s < m_size )
                {
                    m_array[ --m_size ] = _Tx();
                }

                while ( s > m_size )
                {
                    m_array[ m_size++ ] = _Tx();
                }
                return (*this);
            }

            VectorOf< _Tx > & reserve( Types::SizeType s )
            {
                if ( m_array.size() < s )
                {
                    m_array.resize( s );
                }
                return (*this);
            }

            _Tx & back()
            {
                return m_array[ --m_size ];
            }

            _Tx * begin()
            {
                return m_array.begin();
            }

            _Tx * end()
            {
                return begin() + m_size;
            }

            Types::Bool empty()
            {
                return (0 == m_size);
            }

            Types::SizeType size()
            {
                return m_size;
            }

            Types::SizeType capacity()
            {
                return m_array.size();
            }

            ArrayOf< _Tx > & array()
            {
                return m_array;
            }
            
            _Tx & operator [] ( Types::SizeType index )
            {
                if ( index >= m_size )
                    throw Errors::Error_BadArrayIndex();

                return m_array[ index ];
            }

            const _Tx & operator [] ( Types::SizeType index ) const
            {
                if ( index >= m_size )
                    throw Errors::Error_BadArrayIndex();

                return m_array[ index ];
            }
        };


    };//Utils

};//Aloe

#endif//ALOE_INCLUDED_ALOE_TYPES_H
