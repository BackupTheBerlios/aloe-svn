#ifndef ALOE_INCLUDED_ALOE_WIN32_H
#define ALOE_INCLUDED_ALOE_WIN32_H

#include "Aloe/aloeSystem.h"
#include "Aloe/aloeStorage.h"
#include "Aloe/aloeRaster.h"
#include "Aloe/aloeUI.h"

#define MEAN_AND_LEAN
#include <windows.h>
#ifndef UNICODE
#   define WIN32__CreateWindow CreateWindowA
#else
#   define WIN32__CreateWindow CreateWindowW
#endif
#undef CreateWindow
#undef Sleep


namespace Aloe {
    namespace Win32 {

        struct IMessageLoop;
        struct IWindowFactory;
        struct IWindowClass;
        struct IWindow;
        struct IWindowEvents;

        extern Utils::SmartPtr< IFactory > Initialize( HINSTANCE hInstance );

        aloe__interface( IMessageLoop )
        {
            aloe__iid( Win32::IMessageLoop );

            aloe__method( IMessageLoop, Run, type( Long ) ,____ );
        };
        
        aloe__runtime_method( Win32::IMessageLoop, Run );

        aloe__interface( IWindowFactory )
        {
            aloe__iid( Win32::IWindowFactory );

            aloe__method( IWindowFactory, CreateWindow
                    , pointer( IProvider )
                    , tuple8(
                        arg( className,     In, type( String )),
                        arg( classStyle,    In, type( Long )),
                        arg( windowName,    In, type( String )),
                        arg( windowStyle,   In, type( Long )),
                        arg( windowStyleEx, In, type( Long )),
                        arg( windowRect,    In, type( Recti )),
                        arg( windowParent,  In, custom( ::HWND )),
                        arg( windowMenu,    In, custom( ::HMENU ))
                        ));
        };

        aloe__runtime_method( Win32::IWindowFactory, CreateWindow );

        aloe__interface( IWindowClass )
        {
            aloe__iid( Win32::IWindowClass );

            aloe__prop( IWindowClass, Style
                    , ____, ____
                    , get , put , type( Long )
                    , ____, ____, ____
                    , ____, ____, ____
                    , ____, ____, ____ );
            
            aloe__prop( IWindowClass, Long
                    , map , type( Long )
                    , get , put , type( Long )
                    , ____, ____, ____
                    , ____, ____, ____
                    , ____, ____, ____ );
        };

        aloe__runtime_prop( Win32::IWindowClass, Style );
        aloe__runtime_prop( Win32::IWindowClass, Long );

        aloe__interface( IWindow )
        {
            aloe__iid( Win32::IWindow );

            aloe__prop( IWindow, Class
                    , ____, ____
                    , get , ____, pointer( Win32::IWindowClass )
                    , ____, ____, ____
                    , ____, ____, ____
                    , ____, ____, ____ );
            
            aloe__prop( IWindow, Style
                    , ____, ____
                    , get , put , type( Long )
                    , ____, ____, ____
                    , ____, ____, ____
                    , ____, ____, ____ );
            
            aloe__prop( IWindow, ExStyle
                    , ____, ____
                    , get , put , type( Long )
                    , ____, ____, ____
                    , ____, ____, ____
                    , ____, ____, ____ );
            
            aloe__prop( IWindow, UserData
                    , ____, ____
                    , get , put , type( Long )
                    , ____, ____, ____
                    , ____, ____, ____
                    , ____, ____, ____ );
            
            aloe__prop( IWindow, Long
                    , map , type( Long )
                    , get , put , type( Long )
                    , ____, ____, ____
                    , ____, ____, ____
                    , ____, ____, ____ );

            aloe__prop( IWindow, HWnd
                    , ____, ____
                    , get , ____, custom( ::HWND )
                    , ____, ____, ____
                    , ____, ____, ____
                    , ____, ____, ____ );
        };

        aloe__runtime_prop( Win32::IWindow, Class );
        aloe__runtime_prop( Win32::IWindow, Style );
        aloe__runtime_prop( Win32::IWindow, ExStyle );
        aloe__runtime_prop( Win32::IWindow, UserData );
        aloe__runtime_map ( Win32::IWindow, Long );
        aloe__runtime_prop( Win32::IWindow, HWnd );
        
        aloe__interface( IWindowEvents )
        {
            aloe__iid( Win32::IWindowEvents );

            aloe__method( IWindowEvents, Event
                    , type( Bool )
                    , tuple4(
                        arg( sender,   In, pointer( IProvider )),
                        arg( message,  In, type( Long )),
                        arg( wParam,   In, type( LongPointer )),
                        arg( lParam,   In, type( LongPointer ))
                        ));
        };

        aloe__runtime_method( Win32::IWindowEvents, Event );
        
    };//Win32
};//Aloe

#endif//ALOE_INCLUDED_ALOE_WIN32_H
