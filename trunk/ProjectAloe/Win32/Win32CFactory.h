#ifndef ALOE_WIN32_SYSTEM
#error "DO NOT INCLUDE THIS FILE!!! This header file can be only included by source file 'Win32System.cpp'."
#endif

namespace Aloe {
    namespace Win32 {
        struct CFactory
            : Detail::Implementation
            < CFactory
            , Detail::Interfaces< IFactory, Win32::IWindowFactory, Win32::IMessageLoop >
            , Detail::Bases< Detail::CRefCount > >
        {   
            HINSTANCE m_hInstance;
            DWORD m_lastError;
            typedef std::map< Types::String, Utils::SmartPtr< IFactory > > DictFactory_t;
            DictFactory_t m_dictFactory;

            Utils::SmartPtr<> __init__( HINSTANCE hInstance )
            {
                m_lastError = 0L;
                m_hInstance = hInstance;
                return Utils::SmartPtr<>( this, this );
            }

            aloe__prop_map_imp_get( IFactory, IdOfName, csName )
            {
                typedef std::map< Types::String, Types::Identifier > IdMap_t;
                static IdMap_t s_idMap;
                static Types::Long s_next = 0x1000;

                IdMap_t::iterator found = s_idMap.find( csName );
                if ( found != s_idMap.end() )
                {
                    return found->second;
                }
                else {
                    Types::Identifier id( Types::LongPointer( ++s_next ));
                    s_idMap[ csName ] = id;
                    return id;
                }
            }

            aloe__method_imp( IFactory, Load, argv )
            {
                aloe__extract1( Load, args, argv, library );

                return false;
            }
            
            aloe__property_imp_put( IFactory, Parent, parent )
            {
            }

            aloe__property_imp_get( IFactory, Parent )
            {
                return Types::None();
            }

            aloe__prop_map_imp_put( IFactory, Create, index, cons )
            {
                m_dictFactory[ index ] = cons;
            };

            aloe__prop_map_imp_get( IFactory, Create, index )
            {
                DictFactory_t::iterator found = m_dictFactory.find( index );
                if ( found != m_dictFactory.end() )
                {
                    return found->second;
                }
                else {
                    return Types::None();
                }
            };

            aloe__prop_map_imp_call( IFactory, Create, index, argv )
            {
                aloe__extract1( Create, args, argv, propMap );

                DictFactory_t::iterator found = m_dictFactory.find( index );
                if ( found != m_dictFactory.end() )
                {
                    return found->second[ IFactory::Create ][ index ]( argv );
                }
                else {
                    return Types::None();
                }
            };
            
            aloe__method_imp( Win32::IWindowFactory, CreateWindow, argv )
            {
                aloe__extract8( CreateWindow, args, argv, className, classStyle,
                        windowName, windowStyle, windowStyleEx, windowRect, windowParent, windowMenu );

                ::HWND hWnd = NULL;
                
                ::WNDCLASSEX wcex;
                ::ZeroMemory( &wcex, sizeof( WNDCLASSEX ));
                
                wcex.cbSize         = sizeof( WNDCLASSEX ); 
                wcex.style          = classStyle;
                wcex.lpfnWndProc    = (WNDPROC)MessageProc;
                wcex.cbClsExtra     = 0;
                wcex.cbWndExtra     = 0;
                wcex.hInstance      = m_hInstance;
                wcex.hCursor        = ::LoadCursor(NULL, IDC_ARROW);
                wcex.hbrBackground  = (HBRUSH)(COLOR_BACKGROUND+1);
                wcex.lpszMenuName   = 0;
                wcex.lpszClassName  = className.c_str();
        
                if ( !RegisterClassEx( &wcex ))
                {
                    m_lastError = GetLastError();
                    return Utils::SmartPtr<>();
                }

                hWnd = ::CreateWindowEx( windowStyleEx, className.c_str(), windowName.c_str(), windowStyle,
                        windowRect.upperLeft().x, windowRect.upperLeft().y, windowRect.width(), windowRect.height(),
                        windowParent, windowMenu, m_hInstance, NULL );

                if ( !hWnd )
                {
                    m_lastError = GetLastError();
                    return Utils::SmartPtr<>();
                }

                ::ShowWindow( hWnd, SW_SHOW );

                return ( new CWindow )->__init__( hWnd );
            }

            static LRESULT WINAPI MessageProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
            {
                if ( CWindow *pWnd = CWindow::GetObject( hWnd ))
                {
                    return pWnd->ProcessMessage( uMsg, wParam, lParam );
                }
                else {
                    return ::DefWindowProc( hWnd, uMsg, wParam, lParam );
                }
            }

            aloe__method_imp( Win32::IMessageLoop, Run, argv )
            {
                ::MSG msg;

                while ( ::GetMessage( &msg, 0, 0, 0 ))
                {
                    ::TranslateMessage( &msg );
                    ::DispatchMessage( &msg );
                };
                
                return 0L;
            }
            
        };//CFactory
    };//Win32
};//Aloe

