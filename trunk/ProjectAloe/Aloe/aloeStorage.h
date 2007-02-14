#ifndef ALOE_INCLUDED_ALOE_STORAGE_H
#define ALOE_INCLUDED_ALOE_STORAGE_H

#include "Aloe/aloe.h"

namespace Aloe {

    struct IByteArray;
    struct IStreamPos;
    struct IStream;
    struct IStorageEnum;
    struct IStorage;
    
    aloe__interface( IByteArray )
    {
        aloe__iid( IByteArray );

        aloe__prop( IByteArray, ByteOrder
                , ____, ____
                , get , put , type( Long )
                , ____, ____, ____
                , ____, ____, ____
                , ____, ____, ____ );
        
        aloe__prop( IByteArray, Size
                , ____, ____
                , get , put , type( LongLong )
                , ____, ____, ____
                , ____, ____, ____
                , ____, ____, ____ );

        aloe__method( IByteArray, Lock
                , type( RawPointer )
                , tuple0()
                );
        
        aloe__method( IByteArray, Unlock
                , ____
                , tuple0()
                );

    };

    aloe__runtime_prop( IByteArray, ByteOrder );
    aloe__runtime_prop( IByteArray, Size );
    aloe__runtime_method( IByteArray, Lock );
    aloe__runtime_method( IByteArray, Unlock );
    
    aloe__interface( IStreamPos )
    {
        aloe__iid( IStreamPos );

        aloe__prop( IStreamPos, BytesFromStart
                , ____, ____
                , get , put , type( LongLong )
                , append, ____, type( LongLong )
                , remove, ____, type( LongLong )
                , ____, ____, ____ );
        
        aloe__prop( IStreamPos, BytesToEnd
                , ____, ____
                , get , put , type( LongLong )
                , append, ____, type( LongLong )
                , remove, ____, type( LongLong )
                , ____, ____, ____ );

        aloe__prop( IStreamPos, DataSlice
                , map , type( LongLong )
                , get , put , pointer( IByteArray )
                , ____, ____, ____
                , ____, ____, ____
                , ____, ____, ____ );
        
        aloe__prop( IStreamPos, Stream
                , ____, ____
                , get , ____, pointer( IStream )
                , ____, ____, ____
                , ____, ____, ____
                , ____, ____, ____ );

    };

    aloe__runtime_prop( IStreamPos, BytesFromStart );
    aloe__runtime_prop( IStreamPos, BytesToEnd );
    aloe__runtime_map( IStreamPos, DataSlice );
    aloe__runtime_prop( IStreamPos, Stream );
    
    aloe__interface( IStream )
    {
        aloe__iid( IStream );

        aloe__method( IStream, Open
                , pointer( IStreamPos )
                , tuple0()
                );
        
        aloe__method( IStream, Close
                , ____
                , ____
                );
        
        aloe__method( IStream, Flush
                , ____
                , ____
                );
    };
    
    aloe__runtime_method( IStream, Open );
    aloe__runtime_method( IStream, Close );
    aloe__runtime_method( IStream, Flush );

    aloe__interface( IStorageEnum )
    {
        aloe__iid( IStorageEnum );

        aloe__method( IStorageEnum, Reset
                , type( Bool )
                , tuple0()
                );

        aloe__method( IStorageEnum, Next
                , type( Bool )
                , tuple2( 
                    arg( path, Out, type( String * )),
                    arg( flags, Out, type( Long * ))
                    )
                );
        
        aloe__prop( IStorageEnum, Storage
                , ____, ____
                , get , ____, pointer( IStorage )
                , ____, ____, ____
                , ____, ____, ____
                , ____, ____, ____ );
    };
    
    aloe__runtime_method( IStorageEnum, Reset );
    aloe__runtime_method( IStorageEnum, Next );
    aloe__runtime_method( IStorageEnum, Storage );
    
    aloe__interface( IStorage )
    {
        aloe__iid( IStorage );
        
        enum Flags
        {
            F_BINARY = 0,
            F_TEXT = 1,
            F_LITTLE = 0,
            F_BIG = 2,
            F_EXISTING = 0,
            F_CLEAN = 4,
            F_APPEND = 8,
            F_STREAM = 0,
            F_STORAGE = 16,
        };

        aloe__method( IStorage, Create
                , pointer( IProvider )
                , tuple2(
                    arg( path, In, type( String )),
                    arg( flags, In, type( Long ))
                    )
                );
        
        aloe__method( IStorage, Exists
                , type( Bool )
                , tuple2(
                    arg( path, In, type( String )),
                    arg( flags, In, type( Long ))
                    )
                );
        
        aloe__method( IStorage, Remove
                , type( Bool )
                , tuple2(
                    arg( path, In, type( String )),
                    arg( flags, In, type( Long ))
                    )
                );

        aloe__method( IStorage, Enumerate
                , pointer( IStorageEnum )
                , tuple1(
                    arg( flags, In, type( Long ))
                    )
                );
    };
    
    aloe__runtime_method( IStorage, Create );
    aloe__runtime_method( IStorage, Exists );
    aloe__runtime_method( IStorage, Remove );
    aloe__runtime_method( IStorage, Enumerate );

};//Aloe

#endif//ALOE_INCLUDED_ALOE_STORAGE_H
