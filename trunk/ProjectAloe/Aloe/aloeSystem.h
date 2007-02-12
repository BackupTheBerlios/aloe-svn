#ifndef ALOE_INCLUDED_ALOE_SYSTEM_H
#define ALOE_INCLUDED_ALOE_SYSTEM_H

#include "Aloe/aloe.h"

namespace Aloe {
    
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
    
    aloe__interface( IStream )
    {
        aloe__iid( IStream );

        enum OpenMode {
            TEXT = 0x0,
            BINARY = 0x1,
            READ = 0x2,
            APPEND = 0x4,
            NEW = 0x8
        };

        aloe__method( IStream, Open
                , type( Bool )
                , tuple1(
                    arg( mode, In, type( Long ))
                    )
                );
        
        aloe__method( IStream, Close
                , ____
                , ____
                );
        
        aloe__method( IStream, Flush
                , ____
                , ____
                );
        
        aloe__method( IStream, GetPos
                , type( Long )
                , ____
                );
        
        aloe__method( IStream, SetPos
                , ____
                , tuple1(
                    arg( position, In, type( Long ))
                    )
                );
        
        aloe__method( IStream, Seek
                , ____
                , tuple2(
                    arg( distance, In, type( Long )),
                    arg( mode, In, type( Long ))
                    )
                );
        
        aloe__method( IStream, Read
                , type( Long )
                , tuple2(
                    arg( buffer, In, type( RawPointer )),
                    arg( bytes, In, type( Long ))
                    )
                );
        
        aloe__method( IStream, Write
                , type( Long )
                , tuple2(
                    arg( buffer, In, type( RawPointer )),
                    arg( bytes, In, type( Long ))
                    )
                );
    };
    
    aloe__interface( IStorage )
    {
        aloe__iid( IStorage );

        aloe__method( IStorage, CreateStream
                , pointer( IStream )
                , tuple1(
                    arg( filename, In, type( String ))
                    )
                );
        
        aloe__method( IStorage, CreateStorage
                , pointer( IStorage )
                , tuple1(
                    arg( dirname, In, type( String ))
                    )
                );
        
        aloe__method( IStorage, StreamExists
                , type( Bool )
                , tuple1(
                    arg( filename, In, type( String ))
                    )
                );
        
        aloe__method( IStorage, StorageExists
                , type( Bool )
                , tuple1(
                    arg( dirname, In, type( String ))
                    )
                );
        
        aloe__method( IStorage, RemoveStream
                , type( Bool )
                , tuple1(
                    arg( filename, In, type( String ))
                    )
                );
        
        aloe__method( IStorage, RemoveStorage
                , type( Bool )
                , tuple1(
                    arg( dirname, In, type( String ))
                    )
                );
    };

};//Aloe

#endif//ALOE_INCLUDED_ALOE_SYSTEM_H
