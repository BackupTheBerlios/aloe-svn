#ifndef ALOE_WIN32_SYSTEM
#error "DO NOT INCLUDE THIS FILE!!! This header file can be only included by source file 'Win32System.cpp'."
#endif

namespace Aloe {
    namespace Win32 {
        struct CWindow
            : Detail::Implementation
            < CWindow
            , Detail::Interfaces< IEventSource, Aloe::IWindow, Win32::IWindow >
            , Detail::Bases< Detail::CRefCount > >
        {
            typedef std::map< ::HWND, CWindow * > DictWindows_t;
            static DictWindows_t s_dictWindows;

            ::HWND m_hWnd;
            
            Utils::SmartPtr<> __init__( ::HWND hWnd )
            {
                s_dictWindows[ hWnd ] = this;
                m_hWnd = hWnd;
                return Utils::SmartPtr<>( this, this );
            }

            ~CWindow()
            {
                if ( RemoveObject( m_hWnd ))
                {
                    Close( Types::None() );
                }
            }

            CWindow * RemoveObject( ::HWND hWnd )
            {
                DictWindows_t::iterator iter = s_dictWindows.find( hWnd );
                if ( iter != s_dictWindows.end() )
                {
                    CWindow *pWnd = iter->second;
                    s_dictWindows.erase( iter );
                    return pWnd;
                }
                else {
                    return NULL;
                }
            }

            static CWindow * GetObject( ::HWND hWnd )
            {
                DictWindows_t::iterator iter = s_dictWindows.find( hWnd );
                if ( iter != s_dictWindows.end() )
                {
                    return iter->second;
                }
                else {
                    return NULL;
                }
            }

            LRESULT ProcessMessage( UINT uMsg, WPARAM wParam, LPARAM lParam )
            {
                __self__()[ IEventSource::Raise ][ Win32::IWindowEvents::Event ]( __self__(),
                        Utils::copyCast< Types::Long >( uMsg ),
                        Utils::copyCast< Types::LongPointer >( wParam ),
                        Utils::copyCast< Types::LongPointer >( lParam )
                        );

                Types::Bool isButton = false;
                Types::Bool isDown = false;
                Types::Bool isDblClick = false;
                Types::Bool isSize = false;

                switch( uMsg )
                {
                    case WM_CREATE:
                        {
                        }
                        break;
                    case WM_DESTROY:
                        {
                            if ( RemoveObject( m_hWnd ))
                            {
                                if( s_dictWindows.empty() )
                                {
                                    ::PostQuitMessage(0);
                                }
                            }
                            __self__()[ IEventSource::Raise ][ Aloe::IWindowEvents::Close ]( __self__() );
                        }
                        break;

                    case WM_ACTIVATE:
                        {
                            Types::Bool bActive = ( LOWORD( wParam ) > 0 );
                            __self__()[ IEventSource::Raise ][ Aloe::IWindowEvents::Activate ]( __self__(), bActive );
                        }
                        break;

                    case WM_SIZE:
                        isSize = true;
                    case WM_MOVE:
                        {
                            Types::Recti rect = get_FrameRect();
                            Types::Long flags = ( isSize ? 1 : 0 );
                            __self__()[ IEventSource::Raise ][ Aloe::IWindowEvents::Move ]( __self__(), rect, flags );
                        }
                        break;

                    case WM_KEYDOWN:
                        isDown = true;
                    case WM_KEYUP:
                        {
                            __self__()[ IEventSource::Raise ][ Aloe::IWindowEvents::Key ]( __self__(),
                                    Utils::copyCast< Types::Long >( wParam ), isDown );
                        }
                        break;

                    case WM_LBUTTONDBLCLK:
                    case WM_RBUTTONDBLCLK:
                    case WM_MBUTTONDBLCLK:
                        isDblClick = true;
                    case WM_LBUTTONDOWN:
                    case WM_RBUTTONDOWN:
                    case WM_MBUTTONDOWN:
                        isDown = true;
                    case WM_LBUTTONUP:
                    case WM_RBUTTONUP:
                    case WM_MBUTTONUP:
                        isButton = true;
                    case WM_MOUSEMOVE:
                        {
                            ::POINT pt;
                            ::GetCursorPos( &pt );
                            ::ScreenToClient( m_hWnd, &pt );
                            
                            if ( !isButton )
                            {
                                __self__()[ IEventSource::Raise ][ Aloe::IWindowEvents::Motion ]( __self__(),
                                        Types::Point2i( pt.x, pt.y ));
                                break;
                            }
                            else
                            {
                                Types::Long btnNo = 0;

                                switch( uMsg )
                                {
                                    case WM_RBUTTONDBLCLK:
                                    case WM_RBUTTONDOWN:
                                    case WM_RBUTTONUP: btnNo = 1; break;
                                    case WM_MBUTTONDBLCLK:
                                    case WM_MBUTTONDOWN:
                                    case WM_MBUTTONUP: btnNo = 2; break;
                                };

                                if ( !isDblClick )
                                {
                                    __self__()[ IEventSource::Raise ][ Aloe::IWindowEvents::Button ]( __self__(),
                                            Types::Point2i( pt.x, pt.y ), btnNo, isDown );
                                }
                                else {
                                    __self__()[ IEventSource::Raise ][ Aloe::IWindowEvents::DoubleClick ]( __self__(),
                                            Types::Point2i( pt.x, pt.y ), btnNo );
                                }
                            }
                            
                        };
                        break;

                };

                return ::DefWindowProc( m_hWnd, uMsg, wParam, lParam );
            }
            
            //
            // IEventSource
            //

	    typedef std::set< Utils::SmartPtr<> > SetOfListeners_t;
            SetOfListeners_t m_setOfListeners;

            aloe__property_imp_append( IEventSource, Listeners, listener )
            {
                return m_setOfListeners.insert( listener ).second;
            }
            
            aloe__property_imp_remove( IEventSource, Listeners, listener )
            {
                SetOfListeners_t::iterator found = m_setOfListeners.find( listener );
                if ( found != m_setOfListeners.end() )
                {
                    m_setOfListeners.erase( found );
                    return true;
                }
                else {
                    return false;
                }
            }

            aloe__method_imp( IEventSource, RaiseEvent, event )
            {
                for ( SetOfListeners_t::iterator i = m_setOfListeners.begin(); i != m_setOfListeners.end(); ++i )
                {
                    if ( !event->Invoke( *i ))
                    {
                        break;
                    }
                }
                return Types::None();
            }

            //
            // IWindow
            //

            aloe__property_imp_put( Aloe::IWindow, FrameRect, rect )
            {
                ::MoveWindow( m_hWnd, rect.upperLeft().x, rect.upperLeft().y, rect.width(), rect.height(), TRUE );
            }

            aloe__property_imp_put( Aloe::IWindow, ClientRect, rect )
            {
                ::RECT w32RectClient;
                ::GetClientRect( m_hWnd, &w32RectClient );
                int dx = (w32RectClient.right - w32RectClient.left) - rect.width();
                int dy = (w32RectClient.bottom - w32RectClient.top) - rect.height();
                
                ::RECT w32Rect;
                ::GetWindowRect( m_hWnd, &w32Rect );
                w32Rect.left   += rect.upperLeft().x;
                w32Rect.top    += rect.upperLeft().y;
                w32Rect.right  += rect.upperLeft().x + dx;
                w32Rect.bottom += rect.upperLeft().y + dy;

                ::MoveWindow( m_hWnd, w32Rect.left, w32Rect.top, w32Rect.right - w32Rect.left, w32Rect.bottom - w32Rect.top, TRUE );
            }
            
            aloe__property_imp_get( Aloe::IWindow, FrameRect )
            {
                ::RECT w32Rect;
                ::GetWindowRect( m_hWnd, &w32Rect );
                
                Types::Recti rect;
                rect.upperLeft()   = Types::Point2i( w32Rect.left, w32Rect.top );
                rect.bottomRight() = Types::Point2i( w32Rect.right, w32Rect.bottom );

                return rect;
            }
            
            aloe__property_imp_get( Aloe::IWindow, ClientRect )
            {
                ::RECT w32Rect;
                ::GetClientRect( m_hWnd, &w32Rect );
                
                Types::Recti rect;
                rect.upperLeft()   = Types::Point2i( w32Rect.left, w32Rect.top );
                rect.bottomRight() = Types::Point2i( w32Rect.right, w32Rect.bottom );

                return rect;
            }
            
            aloe__method_imp( Aloe::IWindow, Close, argv )
            {
                ::PostMessage( m_hWnd, WM_CLOSE, 0, 0 );
                return Types::None();
            }

            //
            // Win32::IWindow
            //

            aloe__property_imp_put( Win32::IWindow, Style, style )
            {
                SetWindowLong( m_hWnd, GWL_STYLE, style );
            }
            
            aloe__property_imp_put( Win32::IWindow, ExStyle, exStyle )
            {
                SetWindowLong( m_hWnd, GWL_EXSTYLE, exStyle );
            }
            
            aloe__property_imp_put( Win32::IWindow, UserData, data )
            {
                SetWindowLong( m_hWnd, GWL_USERDATA, data );
            }
           
            aloe__prop_map_imp_put( Win32::IWindow, Long, idx, value )
            {
                SetWindowLong( m_hWnd, idx, value );
            }
            
            aloe__property_imp_get( Win32::IWindow, Class )
            {
                return  ( new CWindowClass )->__init__( m_hWnd );
            }
            
            aloe__property_imp_get( Win32::IWindow, Style )
            {
                return GetWindowLong( m_hWnd, GWL_STYLE );
            }
            
            aloe__property_imp_get( Win32::IWindow, ExStyle )
            {
                return GetWindowLong( m_hWnd, GWL_EXSTYLE );
            }
            
            aloe__property_imp_get( Win32::IWindow, UserData )
            {
                return GetWindowLong( m_hWnd, GWL_USERDATA );
            }
           
            aloe__prop_map_imp_get( Win32::IWindow, Long, idx )
            {
                return GetWindowLong( m_hWnd, idx );
            }
            
            aloe__property_imp_get( Win32::IWindow, HWnd )
            {
                return m_hWnd;
            }

        };//CWindow
    };//Win32
};//Aloe
