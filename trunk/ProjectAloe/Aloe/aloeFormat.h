#ifndef ALOE_INCLUDED_ALOE_FORMAT_H
#define ALOE_INCLUDED_ALOE_FORMAT_H

#include "Aloe/aloeTypes.h"

#include <iostream>
#include <sstream>

namespace Aloe {
    
    namespace Types {
        
        typedef WideChar CharType;
        typedef std::basic_string< CharType > String;
#define aloe__string( t ) Aloe::Types::String( L##t )
        typedef std::basic_stringstream< CharType > StringStream;
        typedef std::basic_istream< CharType > StreamIn;
        typedef std::basic_ostream< CharType > StreamOut;
            
    };//Types

    static Types::StreamOut &StdOut = std::wcout;
    static Types::StreamIn  &StdIn  = std::wcin;
    
    inline Types::StreamOut & EndLine  ( Types::StreamOut &out ) { return std::endl( out ); }
    inline Types::StreamOut & EndStream( Types::StreamOut &out ) { return std::ends( out ); }
    inline Types::StreamOut & Flush    ( Types::StreamOut &out ) { return std::flush( out ); }

    namespace Utils {

        // przyk³adowo mo¿na by poszerzyæ funkcjjonalnoœæ o parametry konwersji:
        // 
        //  String s = Format("³ab¹dŸ", "--enc=cp1250 --dict=polish");
        //  
        inline Aloe::Types::String Format( Aloe::Types::CStr *cstr, const Aloe::Types::String &fmt = Aloe::Types::String() )
        {
            Aloe::Types::String str;

            if ( cstr )
            {
                for ( ; *cstr; ++cstr )
                {
                    str += copyCast< Aloe::Types::CharType >( *cstr );
                }
            }

            return str;
        }

        inline Aloe::Types::String Format( const Aloe::Types::Point2i &pt, const Aloe::Types::String &fmt = Aloe::Types::String() )
        {
            Aloe::Types::StringStream ss;
            if ( fmt.empty() )
            {
                ss << pt.x << ", " << pt.y;
            }
            else
            {
                size_t q = 0;
                size_t p = fmt.find(L"%", q);
                while ( p != Aloe::Types::String::npos )
                {
                    ss << fmt.substr( q, p-q );
                    size_t l = 1;

                    if ( p + 1 < fmt.size() )
                    {
                             if ( fmt[ p + 2 ] == L'x' ) { ss << pt.x; l = 2; }
                        else if ( fmt[ p + 2 ] == L'y' ) { ss << pt.y; l = 2; }
                        else if ( fmt[ p + 1 ] == L'%' ) { ss << L'%'; l = 2; }
                    }
                    
                    q = p + l;
                    p = fmt.find(L"%", q);
                }
                ss << fmt.substr( q, -1 );
            }
            return ss.str();
        }

        inline Aloe::Types::String Format( const Aloe::Types::Vector2i &v, const Aloe::Types::String &fmt = Aloe::Types::String() )
        {
            Aloe::Types::StringStream ss;
            if ( fmt.empty() )
            {
                ss << v.dx << ", " << v.dy;
            }
            else
            {
                size_t q = 0;
                size_t p = fmt.find(L"%", q);
                while ( p != Aloe::Types::String::npos )
                {
                    ss << fmt.substr( q, p-q );
                    size_t l = 1;

                    if ( p + 2 < fmt.size() )
                    {
                        if ( fmt[ p + 1 ] == L'd' )
                        {
                                 if ( fmt[ p + 2 ] == L'x' ) { ss << v.dx; l = 3; }
                            else if ( fmt[ p + 2 ] == L'y' ) { ss << v.dy; l = 3; }
                        }
                    }
                    if ( p + 1 < fmt.size() )
                    {
                        if ( fmt[ p + 1 ] == L'%' ) { ss << L'%'; l = 2; }
                    }
                    
                    q = p + l;
                    p = fmt.find(L"%", q);
                }
                ss << fmt.substr( q, -1 );
            }
            return ss.str();
        }
        
        inline Aloe::Types::String Format( const Aloe::Types::Recti &rc, const Aloe::Types::String &fmt = Aloe::Types::String() )
        {
            Aloe::Types::StringStream ss;
            if ( fmt.empty() )
            {
                ss << rc.x1 << ", " << rc.y1 << ", " << rc.x2 << ", " << rc.y2 << " [ " << rc.width() << ", " << rc.height() << " ]";
            }
            else
            {
                size_t q = 0;
                size_t p = fmt.find(L"%", q);
                while ( p != Aloe::Types::String::npos )
                {
                    ss << fmt.substr( q, p-q );
                    size_t l = 1;

                    if ( p + 2 < fmt.size() )
                    {
                        if ( fmt[ p + 1 ] == L'x' )
                        {
                                 if ( fmt[ p + 2 ] == L'1' ) { ss << rc.x1; l = 3; }
                            else if ( fmt[ p + 2 ] == L'2' ) { ss << rc.x2; l = 3; }
                        }
                        else if ( fmt[ p + 1 ] == L'y' )
                        {
                                 if ( fmt[ p + 2 ] == L'1' ) { ss << rc.y1; l = 3; }
                            else if ( fmt[ p + 2 ] == L'2' ) { ss << rc.y2; l = 3; }
                        }
                    }

                    if ( p + 1 < fmt.size() )
                    {
                             if ( fmt[ p + 1 ] == L'w' ) { ss << rc.width(); l = 2; }
                        else if ( fmt[ p + 1 ] == L'h' ) { ss << rc.height(); l = 2; }
                        else if ( fmt[ p + 1 ] == L'%' ) { ss << L'%'; l = 2; }
                    }
                    
                    q = p + l;
                    p = fmt.find(L"%", q);
                }
                ss << fmt.substr( q, -1 );
            }
            return ss.str();
        }
        
    };//Utils
};//Aloe

#endif//ALOE_INCLUDED_ALOE_FORMAT_H
