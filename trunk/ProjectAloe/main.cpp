#include "Aloe/aloeWin32.h"

#include <stdio.h>
#include <set>
#include <map>

#pragma warning(disable:4250)

namespace Aloe {

    Utils::SmartPtr< IFactory > Root;

};//Aloe



struct MyWindowEvents
    : Aloe::Detail::Implementation
    < MyWindowEvents
    , Aloe::Detail::Interfaces< Aloe::Win32::IWindowEvents, Aloe::IWindowEvents >
    , Aloe::Detail::Bases< Aloe::Detail::CRefCount > >
{
    aloe__method_imp( Aloe::IWindowEvents, Close, argv )
    {
        aloe__extract1( Close, args, argv, sender );

        return false;
    }
    
    aloe__method_imp( Aloe::IWindowEvents, Activate, argv )
    {
        aloe__extract2( Activate, args, argv, sender, active );
        
        return false;
    }
    
    aloe__method_imp( Aloe::IWindowEvents, Move, argv )
    {
        aloe__extract3( Move, args, argv, sender, frameRect, flags );
        
        return false;
    }
    
    aloe__method_imp( Aloe::IWindowEvents, Key, argv )
    {
        aloe__extract3( Key, args, argv, sender, virtKey, isDown );
        
        return false;
    }
    
    aloe__method_imp( Aloe::IWindowEvents, Motion, argv )
    {
        aloe__extract2( Motion, args, argv, sender, position );

        return false;
    }
    
    aloe__method_imp( Aloe::IWindowEvents, Button, argv )
    {
        aloe__extract4( Button, args, argv, sender, position, buttonNo, isDown );
        
        return false;
    }
    
    aloe__method_imp( Aloe::IWindowEvents, DoubleClick, argv )
    {
        aloe__extract3( DoubleClick, args, argv, sender, position, buttonNo );
        
        return false;
    }
    
    aloe__method_imp( Aloe::Win32::IWindowEvents, Event, argv )
    {
        aloe__extract4( Event, args, argv, sender, message, wParam, lParam );

        return true;
    };

    static Aloe::Utils::SmartPtr<> New()
    {
        MyWindowEvents *p = new MyWindowEvents();
        return Aloe::Utils::SmartPtr<>( p, p );
    }
};


int main()
{
    using Aloe::Types::Point2i;
    using Aloe::Types::Vector2i;
    using Aloe::Types::Recti;
    using Aloe::Utils::SmartPtr;
    using Aloe::Utils::ArrayOf;
    using Aloe::Utils::VectorOf;
    namespace Win32 = Aloe::Win32;
    namespace Types = Aloe::Types;
    namespace Utils = Aloe::Utils;

    Aloe::Root = Win32::Initialize( ::GetModuleHandle(NULL) );

    aloe__try {

        SmartPtr<> wnd = Aloe::Root[ Win32::IWindowFactory::CreateWindow ]
            ( aloe__string("TestClass"), CS_HREDRAW | CS_VREDRAW,
              aloe__string("TestWindow"), WS_OVERLAPPEDWINDOW, 0, Recti( Point2i(10,10), Vector2i( 640, 480 )),
              (HWND)NULL, (HMENU)NULL
            );

        aloe__try {

            wnd[ Win32::IWindow::Class ][ Win32::IWindowClass::Style ] = 
                wnd[ Win32::IWindow::Class ][ Win32::IWindowClass::Style ] | CS_DBLCLKS;
            
            wnd[ Aloe::IEventSource::Listeners ] += MyWindowEvents::New();

        } aloe__finish;

        aloe__try {
        
            SmartPtr<> stream = Aloe::Root[ Aloe::IStorage::Create ]( aloe__string("dupa.bmp"), 0L );
            stream[ Aloe::IStream::Open ]();
    
        } aloe__finish;

        aloe__try {
            
            Aloe::Root[ IFactory::Load ](aloe__string("Win32Client.dll"));
            Aloe::Root[ IFactory::Load ](aloe__string("MeshLayout.dll"));
            Aloe::Root[ IFactory::Load ](aloe__string("TargetLayout.dll"));
            Aloe::Root[ IFactory::Load ](aloe__string("Widget.dll"));
            Aloe::Root[ IFactory::Load ](aloe__string("ButtonDesigner.dll"));
            Aloe::Root[ IFactory::Load ](aloe__string("LayoutDesigner.dll"));
            Aloe::Root[ IFactory::Load ](aloe__string("UIDispatcher.dll"));

            SmartPtr<> window  = Root[ IFactory::Create ][aloe__string("Window")]( Types::None() );
            SmartPtr<> widget  = Root[ IFactory::Create ][aloe__string("Widget")]( Types::None() );
            SmartPtr<> button  = Root[ IFactory::Create ][aloe__string("ButtonDesigner")]( Types::None() );
            SmartPtr<> label   = Root[ IFactory::Create ][aloe__string("LabelDesigner")]( Types::None() );
            SmartPtr<> layout  = Root[ IFactory::Create ][aloe__string("MeshLayout")]( Types::None() );
            SmartPtr<> line_x1 = Root[ IFactory::Create ][aloe__string("MeshLine")]( Types::None() );
            SmartPtr<> line_x2 = Root[ IFactory::Create ][aloe__string("MeshLine")]( Types::None() );
            SmartPtr<> line_y1 = Root[ IFactory::Create ][aloe__string("MeshLine")]( Types::None() );
            SmartPtr<> line_y2 = Root[ IFactory::Create ][aloe__string("MeshLine")]( Types::None() );
            SmartPtr<> cell    = Root[ IFactory::Create ][aloe__string("MeshCell")]( Types::None() );
            SmartPtr<> uidisp  = Root[ IFactory::Create ][aloe__string("UIDispatcher")]( Types::None() );
            
            cell[ IMeshCell::HLineStart ] = line_x1[ IMeshLine::This ];
            cell[ IMeshCell::VLineStart ] = line_y1[ IMeshLine::This ];
            cell[ IMeshCell::HLineEnd ] = line_x2[ IMeshLine::This ];
            cell[ IMeshCell::VLineEnd ] = line_y2[ IMeshLine::This ];
            
            widget[ IFrameClient::Frame ] = cell[ IFrame::This ];
            layout[ IFrameClient::Frame ] = window[ IFrame::This ];
            window[ IContainer::Objects ] += widget;
            window[ IEventSource::Listeners ] += uidisp;
            
            line_x1[ IMeshLine::Placement ] = Utils::makeTuple( 1, 5 );
            line_x2[ IMeshLine::Placement ] = Utils::makeTuple( 2, 5 );
            line_y1[ IMeshLine::Placement ] = Utils::makeTuple( 3, 5 );
            line_y2[ IMeshLine::Placement ] = Utils::makeTuple( 4, 5 );
            
            layout[ IMeshLayout::HLines ] += line_x1[ IMeshLine::This ];
            layout[ IMeshLayout::HLines ] += line_x2[ IMeshLine::This ];
            layout[ IMeshLayout::VLines ] += line_y1[ IMeshLine::This ];
            layout[ IMeshLayout::VLines ] += line_y2[ IMeshLine::This ];
            layout[ IMeshLayout::Cells ]  += cell[ IMeshCell::This ];
            
            widget[ IGraphicsDesignerClient::Designers ] += button[ IGraphicsDesigner::This ];
            widget[ IGraphicsDesignerClient::Designers ] += label[ IGraphicsDesigner::This ];
            
            widget[ IGraphicsDesignerClient::LayerOrder ][aloe__string("background")] = 100;
            widget[ IGraphicsDesignerClient::LayerOrder ][aloe__string("label")] = 200;
            widget[ IGraphicsDesignerClient::LayerOrder ][aloe__string("overlay")] = 300;


        } aloe__finish;
        
        Aloe::Root[ Win32::IMessageLoop::Run ]();

    } aloe__finish;

    return 0;
}

