#ifndef ALOE_INCLUDED_ALOE_WIDGET_H
#define ALOE_INCLUDED_ALOE_WIDGET_H

#include "Aloe/aloe.h"

namespace Aloe {
    
    struct ILayout;
    struct ILayoutItem;
    struct IWidget;
    struct IWidgetEvents;
    struct IContainer;
    
    aloe__interface( ILayout )
    {
        aloe__iid( ILayout );

        aloe__prop( ILayout, Items
                , ____, ____
                , ____, ____, ____
                , append, ____, pointer( ILayoutItem )
                , remove, ____, pointer( ILayoutItem )
                , ____, ____, ____ );
    };

    aloe__runtime_prop( ILayout, Items );


    aloe__interface( ILayoutItem )
    {
        aloe__iid( ILayoutItem );

        aloe__prop( ILayoutItem, MinSize
                , ____, ____
                , get , put, type( Vector2i )
                , ____, ____, ____
                , ____, ____, ____
                , ____, ____, ____ );

        aloe__prop( ILayoutItem, MaxSize
                , ____, ____
                , get , put, type( Vector2i )
                , ____, ____, ____
                , ____, ____, ____
                , ____, ____, ____ );

        aloe__prop( ILayoutItem, Weight
                , ____, ____
                , get , put, type( Vector2i )
                , ____, ____, ____
                , ____, ____, ____
                , ____, ____, ____ );
        
        aloe__prop( ILayoutItem, Pad
                , ____, ____
                , get , put, tuple2( type( Vector2i ), type( Vector2i ))
                , ____, ____, ____
                , ____, ____, ____
                , ____, ____, ____ );
        
        aloe__prop( ILayoutItem, Area
                , ____, ____
                , get , put, type( Recti )
                , ____, ____, ____
                , ____, ____, ____
                , ____, ____, ____ );
        
        aloe__prop( ILayoutItem, Layout
                , ____, ____
                , get , put, pointer( ILayout )
                , ____, ____, ____
                , ____, ____, ____
                , ____, ____, ____ );
        
        aloe__prop( ILayoutItem, Flags
                , ____, ____
                , get , put, type( Long )
                , ____, ____, ____
                , ____, ____, ____
                , ____, ____, ____ );
    };

    aloe__runtime_prop( ILayoutItem, MinSize );
    aloe__runtime_prop( ILayoutItem, MaxSize );
    aloe__runtime_prop( ILayoutItem, Weight );
    aloe__runtime_prop( ILayoutItem, Pad );
    aloe__runtime_prop( ILayoutItem, Area );
    aloe__runtime_prop( ILayoutItem, Layout );
    aloe__runtime_prop( ILayoutItem, Flags );


    aloe__interface( IWidget )
    {
        aloe__iid( IWidget );

        aloe__prop( IWidget, BoundRect
                , ____, ____
                , get , ____, type( Recti )
                , ____, ____, ____
                , ____, ____, ____
                , ____, ____, ____ );

        aloe__prop( IWidget, Size
                , ____, ____
                , get , ____, type( Vector2i )
                , ____, ____, ____
                , ____, ____, ____
                , ____, ____, ____ );

        aloe__prop( IWidget, Position
                , ____, ____
                , get , ____, type( Point2i )
                , ____, ____, ____
                , ____, ____, ____
                , ____, ____, ____ );

        aloe__prop( IWidget, Visible
                , ____, ____
                , get , put , type( Bool )
                , ____, ____, ____
                , ____, ____, ____
                , ____, ____, ____ );
        
        aloe__prop( IWidget, ClipRect
                , ____, ____
                , get , put , type( Recti )
                , ____, ____, ____
                , ____, ____, ____
                , ____, ____, ____ );
        
        aloe__prop( IWidget, Dirty
                , ____, ____
                , get , put , type( Long )
                , ____, ____, ____
                , ____, ____, ____
                , ____, ____, ____ );
        
        aloe__prop( IWidget, Container
                , ____, ____
                , get , put , pointer( IContainer )
                , ____, ____, ____
                , ____, ____, ____
                , ____, ____, ____ );

        aloe__prop( IWidget, Window
                , ____, ____
                , get , put , pointer( IWindow )
                , ____, ____, ____
                , ____, ____, ____
                , ____, ____, ____ );

        aloe__prop( IWidget, Item
                , ____, ____
                , get , put , pointer( ILayoutItem )
                , ____, ____, ____
                , ____, ____, ____
                , ____, ____, ____ );

        aloe__method( IWidget, Calculate
                , ____
                , tuple0()
                );

        aloe__method( IWidget, Design
                , ____
                , tuple1(
                    arg( design, Modify, pointer( IGraphicsDesign ))
                    )
                );
        aloe__method( IWidget, Expose
                , ____
                , tuple2(
                    arg( kind, In, type( Long )),
                    arg( flags, In, type( Long ))
                    )
                );
    };

    aloe__runtime_prop( IWidget, BoundRect );
    aloe__runtime_prop( IWidget, Size );
    aloe__runtime_prop( IWidget, Position );
    aloe__runtime_prop( IWidget, Visible );
    aloe__runtime_prop( IWidget, ClipRect );
    aloe__runtime_prop( IWidget, Dirty );
    aloe__runtime_prop( IWidget, Container );
    aloe__runtime_prop( IWidget, Window );
    aloe__runtime_prop( IWidget, Item );
    aloe__runtime_method( IWidget, Calculate );
    aloe__runtime_method( IWidget, Design );
    aloe__runtime_method( IWidget, Expose );


    aloe__interface( IWidgetEvents )
    {
        aloe__iid( IWidgetEvents );

        enum EventFlags
        {
            F_BEFORE  = 0x10,
            F_AFTER   = 0x00,
            F_VISIBLE = 0x01,
            F_HIDDEN  = 0x00,
            F_INSERT  = 0x01,
            F_REMOVE  = 0x00,
            F_ATTACH  = 0x01,
            F_DETACH  = 0x00,
        };

        aloe__method( IWidgetEvents, Expose
                , ____
                , tuple3(
                    arg( sender, In, pointer( IWidget )),
                    arg( kind, In, type( Long )),
                    arg( flags, In, type( Long ))
                    )
                );
        
        aloe__method( IWidgetEvents, Move
                , ____
                , tuple3(
                    arg( sender, In, pointer( IWidget )),
                    arg( bound, In, type( Recti )),
                    arg( flags, In, type( Long ))
                    )
                );
        
        aloe__method( IWidgetEvents, Insert
                , ____
                , tuple3(
                    arg( sender, In, pointer( IWidget )),
                    arg( bound, In, pointer( IContainer )),
                    arg( flags, In, type( Long ))
                    )
                );
        
        aloe__method( IWidgetEvents, Attach
                , ____
                , tuple3(
                    arg( sender, In, pointer( IWidget )),
                    arg( bound, In, pointer( IContainer )),
                    arg( flags, In, type( Long ))
                    )
                );
        
        aloe__method( IWidgetEvents, Calculate
                , ____
                , tuple2(
                    arg( sender, In, pointer( IWidget )),
                    arg( flags, In, type( Long ))
                    )
                );
        
        aloe__method( IWidgetEvents, Design
                , ____
                , tuple3(
                    arg( sender, In, pointer( IWidget )),
                    arg( design, In, pointer( IGraphicsDesign )),
                    arg( flags, In, type( Long ))
                    )
                );
    };

    aloe__runtime_method( IWidgetEvents, Expose );
    aloe__runtime_method( IWidgetEvents, Move );
    aloe__runtime_method( IWidgetEvents, Insert );
    aloe__runtime_method( IWidgetEvents, Attach );
    aloe__runtime_method( IWidgetEvents, Calculate );
    aloe__runtime_method( IWidgetEvents, Design );

    aloe__interface( IContainer )
    {
        aloe__iid( IContainer );

        aloe__prop( IContainer, Children
                , ____, ____
                , ____, ____, ____
                , append, ____, pointer( IWidget )
                , remove, ____, pointer( IWidget )
                , ____, ____, ____ );
        
        aloe__prop( IContainer, ChildByPoint
                , map , type( Point2i )
                , get , ____, pointer( IWidget )
                , ____, ____, ____ 
                , ____, ____, ____ 
                , ____, ____, ____ );
        
        aloe__prop( IContainer, ChildByName
                , map , type( Identifier )
                , get , ____, pointer( IWidget )
                , ____, ____, ____ 
                , ____, ____, ____ 
                , ____, ____, ____ );
        
        aloe__prop( IContainer, Layout
                , ____, ____
                , get , put , pointer( ILayout )
                , ____, ____, ____ 
                , ____, ____, ____ 
                , ____, ____, ____ );
    };

    aloe__interface( IContainerEvents )
    {
        aloe__iid( IContainerEvents );
        
        aloe__method( IContainerEvents, InsertChild
                , ____
                , tuple3(
                    arg( sender, In, pointer( IContainer )),
                    arg( child, In, pointer( IWidget )),
                    arg( flags, In, type( Long ))
                    )
                );
        
        aloe__method( IContainerEvents, CalculateChild
                , ____
                , tuple3(
                    arg( sender, In, pointer( IContainer )),
                    arg( child, In, pointer( IWidget )),
                    arg( flags, In, type( Long ))
                    )
                );
        
        aloe__method( IContainerEvents, DesignChild
                , ____
                , tuple4(
                    arg( sender, In, pointer( IContainer )),
                    arg( child, In, pointer( IWidget )),
                    arg( design, In, pointer( IGraphicsDesign )),
                    arg( flags, In, type( Long ))
                    )
                );
    };
    
    aloe__runtime_method( IContainerEvents, InsertChild );
    aloe__runtime_method( IContainerEvents, CalculateChild );
    aloe__runtime_method( IContainerEvents, DesignChild );

};//Aloe

#endif//ALOE_INCLUDED_ALOE_WIDGET_H
