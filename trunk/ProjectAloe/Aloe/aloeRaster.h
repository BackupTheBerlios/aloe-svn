#ifndef ALOE_INCLUDED_ALOE_RASTER_H
#define ALOE_INCLUDED_ALOE_RASTER_H

#include "Aloe/aloe.h"

namespace Aloe {
    
    struct IRasterFormat;
    struct IPixelArray;
    struct IRasterRect;
    struct IRaster;
    

    aloe__interface( IRasterFormat )
    {
        aloe__iid( IRasterFormat );

        enum PixelTypes
        {
            F_FLAG          = 0x0100,
            F_SWAP          = F_FLAG,
            F_ALPHA         = F_FLAG << 1,
            F_LUMI          = F_FLAG << 2,
            F_RED           = F_FLAG << 3,
            F_GREEN         = F_FLAG << 4,
            F_BLUE          = F_FLAG << 5,
            
            LUMI_8          = 0x08 | F_LUMI,
            ALPHA_8         = 0x08 | F_ALPHA,
            RGB_5_5_5       = 0x0F,
            RGBA_5_5_5_1    = 0x0F | F_ALPHA,
            RGB_5_6_5       = 0x10,
            RGBA_4_4_4_4    = 0x10 | F_ALPHA,
            LUMI_ALPHA_8_8  = 0x10 | F_LUMI | F_ALPHA,
            RGB_8_8_8       = 0x18,
            RGB_8_8_8_8     = 0x20,
            RGBA_8_8_8_8    = 0x20 | F_ALPHA,
            
            RGB             = RGB_8_8_8,
            RGB16           = RGB_5_6_5,
            RGB24           = RGB_8_8_8,
            RGBA            = RGBA_8_8_8_8,
            RGBA32          = RGBA_8_8_8_8,
            BGR             = RGB | F_SWAP,
            BGRA            = RGBA | F_SWAP
        };


        aloe__prop( IRasterFormat, Size
                , ____, ____
                , get , put, type( Vector2i )
                , ____, ____, ____
                , ____, ____, ____
                , ____, ____, ____ );

        aloe__prop( IRasterFormat, Width
                , ____, ____
                , get , put, type( Int )
                , ____, ____, ____
                , ____, ____, ____
                , ____, ____, ____ );

        aloe__prop( IRasterFormat, Height
                , ____, ____
                , get , put, type( Int )
                , ____, ____, ____
                , ____, ____, ____
                , ____, ____, ____ );

        aloe__prop( IRasterFormat, PixelType
                , ____, ____
                , get , put, type( Long )
                , ____, ____, ____
                , ____, ____, ____
                , ____, ____, ____ );
        
        aloe__prop( IRasterFormat, BitsPerPixel
                , ____, ____
                , get , put, type( Int )
                , ____, ____, ____
                , ____, ____, ____
                , ____, ____, ____ );
        
        aloe__prop( IRasterFormat, BitsPerChannel
                , map , type( Long )
                , get , put, type( Int )
                , ____, ____, ____
                , ____, ____, ____
                , ____, ____, ____ );
        
        aloe__prop( IRasterFormat, NumChannels
                , ____, ____
                , get , put, type( Int )
                , ____, ____, ____
                , ____, ____, ____
                , ____, ____, ____ );
    };

    aloe__runtime_prop( IRasterFormat, Size );
    aloe__runtime_prop( IRasterFormat, Width );
    aloe__runtime_prop( IRasterFormat, Height );
    aloe__runtime_prop( IRasterFormat, PixelType );
    aloe__runtime_prop( IRasterFormat, BitsPerPixel );
    aloe__runtime_prop( IRasterFormat, BitsPerChannel );
    aloe__runtime_prop( IRasterFormat, NumChannels );

    aloe__interface( IPixelArray )
    {
        aloe__iid( IPixelArray );

        aloe__prop( IPixelArray, BytesPerRow
                , ____, ____
                , get , put , type( Int )
                , ____, ____, ____
                , ____, ____, ____
                , ____, ____, ____ );
        
        aloe__prop( IPixelArray, BytesPerPixel
                , ____, ____
                , get , put , type( Int )
                , ____, ____, ____
                , ____, ____, ____
                , ____, ____, ____ );
        
        aloe__method( IPixelArray, Lock
                , type( RawPointer )
                , tuple0()
                );
        
        aloe__method( IPixelArray, Unlock
                , ____
                , tuple0()
                );
    };

    aloe__runtime_prop( IPixelArray, BytesPerRow );
    aloe__runtime_prop( IPixelArray, BytesPerPixel );
    aloe__runtime_method( IPixelArray, Lock );
    aloe__runtime_method( IPixelArray, Unlock );

    aloe__interface( IRasterRect )
    {
        aloe__iid( IRasterRect );

        aloe__prop( IRasterRect, Raster
                , ____, ____
                , get , put , pointer( IRaster )
                , ____, ____, ____
                , ____, ____, ____
                , ____, ____, ____ );
        
        aloe__prop( IRasterRect, Rect
                , ____, ____
                , get , put , type( Recti )
                , ____, ____, ____
                , ____, ____, ____
                , ____, ____, ____ );
    };

    aloe__runtime_prop( IRasterRect, Raster );
    aloe__runtime_prop( IRasterRect, Rect );


    aloe__interface( IRaster )
    {
        aloe__iid( IRaster );

        aloe__prop( IRaster, PixelRect
                , map , type( Recti )
                , get , put , pointer( IRasterRect )
                , ____, ____, ____
                , ____, ____, ____
                , ____, ____, ____ );

        aloe__method( IRaster, CreateCompat
                , pointer( IRaster )
                , tuple1(
                    arg( format, In, pointer( IRasterFormat ))
                    )
                );
    };

    aloe__runtime_map( IRaster, PixelRect );
    aloe__runtime_method( IRaster, CreateCompat );
    

};//Aloe

#endif//ALOE_INCLUDED_ALOE_RASTER_H
