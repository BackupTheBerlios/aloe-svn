#ifndef ALOE_INCLUDED_ALOE_SYSTEM_H
#define ALOE_INCLUDED_ALOE_SYSTEM_H

#include "Aloe/aloe.h"

namespace Aloe {

    struct IWindow;
    struct IWindowEvents;
    
    aloe__interface( IWindow )
    {
        aloe__iid( IWindow );

        aloe__prop( IWindow, FrameRect
                , ____, ____
                , get , put , type( Recti )
                , ____, ____, ____
                , ____, ____, ____
                , ____, ____, ____ );

        aloe__prop( IWindow, ClientRect
                , ____, ____
                , get , put , type( Recti )
                , ____, ____, ____
                , ____, ____, ____
                , ____, ____, ____ );

        aloe__method( IWindow, Close
                , ____
                , ____
                );
    };

    aloe__runtime_prop( IWindow, FrameRect );
    aloe__runtime_prop( IWindow, ClientRect );
    
    aloe__interface( IWindowEvents )
    {
        aloe__iid( IWindowEvents );

        aloe__method( IWindowEvents, Close
                , type( Bool )
                , tuple1(
                    arg( sender, In, pointer( IProvider ))
                    )
                );
        
        aloe__method( IWindowEvents, Activate
                , type( Bool )
                , tuple2(
                    arg( sender, In, pointer( IProvider )),
                    arg( active, In, type( Bool ))
                    )
                );
        
        aloe__method( IWindowEvents, Move
                , type( Bool )
                , tuple3(
                    arg( sender   , In, pointer( IProvider )),
                    arg( frameRect, In, type( Recti )),
                    arg( flags    , In, type( Long ))
                    )
                );

        aloe__method( IWindowEvents, Key
                , type( Bool )
                , tuple3(
                    arg( sender , In, pointer( IProvider )),
                    arg( virtKey, In, type( Long )),
                    arg( isDown , In, type( Bool ))
                    )
                );
        
        aloe__method( IWindowEvents, Motion
                , type( Bool )
                , tuple2(
                    arg( sender,   In, pointer( IProvider )),
                    arg( position, In, type( Point2i ))
                    )
                );
        
        aloe__method( IWindowEvents, Button
                , type( Bool )
                , tuple4(
                    arg( sender,   In, pointer( IProvider )),
                    arg( position, In, type( Point2i )),
                    arg( buttonNo, In, type( Long )),
                    arg( isDown  , In, type( Bool ))
                    )
                );
        
        aloe__method( IWindowEvents, DoubleClick
                , type( Bool )
                , tuple3(
                    arg( sender,   In, pointer( IProvider )),
                    arg( position, In, type( Point2i )),
                    arg( buttonNo, In, type( Long ))
                    )
                );
    };

    aloe__runtime_method( IWindowEvents, Close );
    aloe__runtime_method( IWindowEvents, Activate );
    aloe__runtime_method( IWindowEvents, Move );
    aloe__runtime_method( IWindowEvents, Key );
    aloe__runtime_method( IWindowEvents, Motion );
    aloe__runtime_method( IWindowEvents, Button );
    aloe__runtime_method( IWindowEvents, DoubleClick );

};//Aloe

#endif//ALOE_INCLUDED_ALOE_SYSTEM_H
