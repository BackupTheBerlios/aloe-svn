#ifndef ALOE_INCLUDED_ALOE_GRAPHICS_H
#define ALOE_INCLUDED_ALOE_GRAPHICS_H

#include "Aloe/aloe.h"

namespace Aloe {

    struct IGraphicsDesign;


    aloe__interface( IGraphicsDesign )
    {
        aloe__iid( IGraphicsDesign );

        aloe__method( IGraphicsDesign, Sector
                , ____
                , tuple2(
                    arg( startPoint, In, type( Point2i )),
                    arg( endPoint, In, type( Point2i ))
                    )
                );
        
        aloe__method( IGraphicsDesign, Segment
                , ____
                , tuple3(
                    arg( startPoint, In, type( Point2i )),
                    arg( midPoint, In, type( Point2i )),
                    arg( endPoint, In, type( Point2i ))
                    )
                );
        
        aloe__method( IGraphicsDesign, Polyline
                , ____
                , tuple1(
                    arg( points, In, array_of( type( Point2i )))
                    )
                );
        
        aloe__method( IGraphicsDesign, Polygon
                , ____
                , tuple1(
                    arg( points, In, array_of( type( Point2i )))
                    )
                );
        
        aloe__method( IGraphicsDesign, Rectangle
                , ____
                , tuple1(
                    arg( points, In, type( Recti ))
                    )
                );

        aloe__prop( IGraphicsDesign, LineWidth
                , ____, ____
                , get , put , type( Float )
                , ____, ____, ____
                , ____, ____, ____
                , ____, ____, ____ );

        aloe__prop( IGraphicsDesign, LineSmooth
                , ____, ____
                , get , put , type( Int )
                , ____, ____, ____
                , ____, ____, ____
                , ____, ____, ____ );

        aloe__prop( IGraphicsDesign, LineStyle
                , ____, ____
                , get , put , type( Long )
                , ____, ____, ____
                , ____, ____, ____
                , ____, ____, ____ );

        aloe__prop( IGraphicsDesign, LineColor
                , ____, ____
                , get , put , type( Color32 )
                , ____, ____, ____
                , ____, ____, ____
                , ____, ____, ____ );

        aloe__prop( IGraphicsDesign, FillStyle
                , ____, ____
                , get , put , type( Long )
                , ____, ____, ____
                , ____, ____, ____
                , ____, ____, ____ );

        aloe__prop( IGraphicsDesign, FillColor
                , ____, ____
                , get , put , type( Color32 )
                , ____, ____, ____
                , ____, ____, ____
                , ____, ____, ____ );
        
        aloe__prop( IGraphicsDesign, Texture
                , ____, ____
                , get , put , pointer( IProvider )
                , ____, ____, ____
                , ____, ____, ____
                , ____, ____, ____ );
        
        aloe__prop( IGraphicsDesign, PixelRect
                , map , type( Recti )
                , ____, put , pointer( IProvider )
                , ____, ____, ____
                , ____, ____, ____
                , ____, ____, ____ );
        
    };

    aloe__runtime_method( IGraphicsDesign, Sector );
    aloe__runtime_method( IGraphicsDesign, Segment );
    aloe__runtime_method( IGraphicsDesign, Polyline );
    aloe__runtime_method( IGraphicsDesign, Polygon );
    aloe__runtime_method( IGraphicsDesign, Rectangle );
    aloe__runtime_prop( IGraphicsDesign, LineWidth );
    aloe__runtime_prop( IGraphicsDesign, LineSmooth );
    aloe__runtime_prop( IGraphicsDesign, LineStyle );
    aloe__runtime_prop( IGraphicsDesign, LineColor );
    aloe__runtime_prop( IGraphicsDesign, FillStyle );
    aloe__runtime_prop( IGraphicsDesign, FillColor );
    aloe__runtime_prop( IGraphicsDesign, Texture );
    aloe__runtime_map( IGraphicsDesign, PixelRect );


    aloe__interface( ITextFaceset )
    {
        aloe__iid( ITextFaceset );

        aloe__method( ITextFaceset, Render
                , pointer( IRasterRect )
                , tuple1(
                    arg( raster, In, pointer( IRasterRect ))
                    )
                );
    };

    aloe__runtime_method( ITextFaceset, Render );


    aloe__interface( IFont )
    {
        aloe__iid( IFont );

        enum FormatFlags
        {
            F_LEFT      = 0x000,
            F_RIGHT     = 0x001,
            F_CENTER    = 0x002,
            F_TOP       = 0x000,
            F_BOTTOM    = 0x004,
            F_VCENTER   = 0x008,
            F_SINGLELINE= 0x010,
            F_BREAKWORD = 0x000,
            F_ELLIPSIS  = 0x020
        };

        enum FontFlags
        {
            F_UNDERLINE = 0x001,
            F_STRIKEOUT = 0x002,
            F_CAPITALS  = 0x004
        };

        aloe__method( IFont, TextFaceset
                , pointer( ITextFaceset )
                , tuple2(
                    arg( text, In, type( String )),
                    arg( flags, In, type( Long ))
                    )
                );

        aloe__prop( IFont, Size
                , ____, ____
                , get , put , type( Int )
                , ____, ____, ____
                , ____, ____, ____
                , ____, ____, ____ );

        aloe__prop( IFont, Weight
                , ____, ____
                , get , put , type( Int )
                , ____, ____, ____
                , ____, ____, ____
                , ____, ____, ____ );
        
        aloe__prop( IFont, Slant
                , ____, ____
                , get , put , type( Int )
                , ____, ____, ____
                , ____, ____, ____
                , ____, ____, ____ );
        
        aloe__prop( IFont, Flags
                , ____, ____
                , get , put , type( Long )
                , ____, ____, ____
                , ____, ____, ____
                , ____, ____, ____ );
    };

    aloe__runtime_method( IFont, TextFaceset );
    aloe__runtime_prop( IFont, Size );
    aloe__runtime_prop( IFont, Weight );
    aloe__runtime_prop( IFont, Slant );
    aloe__runtime_prop( IFont, Flags );
    
};//Aloe

#endif//ALOE_INCLUDED_ALOE_GRAPHICS_H
