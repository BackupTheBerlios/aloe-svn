#define _WIN32_WINNT 0x0500
#define WINVER 0x0410

#include "Aloe/aloeWin32.h"
//#include "GL/gl.h"

#include <stdio.h>
#include <set>
#include <map>

#pragma warning(disable:4250)

namespace Aloe {

    Utils::SmartPtr< IFactory > Root;

/*
    Window To UIEvents Translation Table
    {
        IWindowEvents::Close       -> IUserInterfaceEvents::Close;
        IWindowEvents::Show        -> IUserInterfaceEvents::Show;
        IWindowEvents::Activate    -> IUserInterfaceEvents::Activate;
        IWindowEvents::Focus       -> IUserInputEvents::Focus;
        IWindowEvents::Move        -> IUserInterfaceEvents::Move;
        IWindowEvents::Key         -> IUserInputEvents::Key;
        
        IWindowEvents::Motion      -> IUserInterfaceEvents2::Motion,
                                      IUserInterfaceEvents2::Hover,
                                      IUserInterfaceEvents2::Leave,
                                      IUserInterfaceEvents4::DragContinue;
                                      
        IWindowEvents::Button      -> IUserInterfaceEvents3::Press,
                                      IUserInterfaceEvents3::Release,
                                      IUserInterfaceEvents3::Click,
                                      IUserInterfaceEvents4::DragStart,
                                      IUserInterfaceEvents4::DragEnd;
                                      
        IWindowEvents::DoubleClick -> IUserInterfaceEvents3::DoubleClick;

        IWindowEvents::Paint       -> IUserInterfaceEvents::Paint,
                                      IUserInterfaceEvents1::Design;
    };
*/

    struct CButtonDesigner
        : Detail::Implementation
        < CButtonDesigner
        , Detail::Interfaces< IUserInterfaceEvents, IUserInterfaceEvents1, IUserInterfaceEvents2, IUserInterfaceEvents3 >
        , Detail::Bases< Detail::CRefCount > >
    {
        Utils::SmartPtr< IEntity > m_entity;
        Utils::SmartPtr< IGraphicsDesign > m_design;
        Utils::SmartPtr< IRaster > m_bitmapNormal;
        Utils::SmartPtr< IRaster > m_bitmapHighlight;
        Utils::SmartPtr< IRaster > m_bitmapPressed;
        Utils::SmartPtr< IRaster > m_bitmap;
        Utils::SmartPtr< IFont > m_font;
        Types::String m_label;

        ThisPtr __init__( const Utils::SmartPtr< IEntity > &entity, const Types::String &label )
        {
            m_entity = entity;
            m_label = label;

            m_font = Root[ &IFactory::Create ][aloe__string("Font")]().AutoQ();
            m_font[ &IFont::Family ] = aloe__string("Arial");
            m_font[ &IFont::Size ] = 20;
            m_font[ &IFont::Weight ] = FW_BOLD;
            m_font[ &IFont::Encoding ] = EASTEUROPE_CHARSET;

            Utils::SmartPtr< IPropertyMap > prop  = Root[ &IFactory::Create ][aloe__string("PropertyMap")]().AutoQ();

            prop[ &IPropertyMap::String ](aloe__string("Bitmap.Filename"),0) = aloe__string("buttonNormal.bmp");
            m_bitmapNormal= Root[ &IFactory::Create ][aloe__string("Bitmap")]( prop ).AutoQ();

            prop[ &IPropertyMap::String ](aloe__string("Bitmap.Filename"),0) = aloe__string("buttonHighlight.bmp");
            m_bitmapHighlight= Root[ &IFactory::Create ][aloe__string("Bitmap")]( prop ).AutoQ();

            prop[ &IPropertyMap::String ](aloe__string("Bitmap.Filename"),0) = aloe__string("buttonPressed.bmp");
            m_bitmapPressed= Root[ &IFactory::Create ][aloe__string("Bitmap")]( prop ).AutoQ();

            m_bitmap = m_bitmapNormal;
                
            return Super::__init__();
        }

        aloe__method_imp( IUserInterfaceEvents, Close, argv )
        {
            aloe__extract2( IUserInterfaceEvents, Close, args, argv, sender, flags );

            return false;
        }

        aloe__method_imp( IUserInterfaceEvents, Show, argv )
        {
            return false;
        }

        aloe__method_imp( IUserInterfaceEvents, Activate, argv )
        {
            return false;
        }

        aloe__method_imp( IUserInterfaceEvents, Move, argv )
        {
            aloe__extract3( IUserInterfaceEvents, Move, args, argv, sender, frameRect, flags );
            
            m_entity[ &IEventSource::Raise ][ &IUserInterfaceEvents1::Dirty ]
                ( m_entity, m_entity[ &IFrameClient::Frame ][ &IFrame::Bound ].value() );

            return true;
        }

        aloe__method_imp( IUserInterfaceEvents, Paint, argv )
        {
            aloe__extract3( IUserInterfaceEvents, Paint, args, argv, sender, screen, rect );

            return false;
        }

        aloe__method_imp( IUserInterfaceEvents1, Dirty, argv )
        {
            aloe__extract2( IUserInterfaceEvents1, Dirty, args, argv, sender, rect );
            
            m_design = Types::None();

            if ( sender.get() == m_entity.get() )
            {
                Utils::SmartPtr< IContainer > container = m_entity[ &IEntity::Container ].value();
                Types::Recti rect = m_entity[ &IFrameClient::Frame ][ &IFrame::Bound ];
                container[ &IEventSource::Raise ][ &IUserInterfaceEvents1::Dirty ]( container, rect );
            }
            
            return true;
        }

        aloe__method_imp( IUserInterfaceEvents1, Design, argv )
        {
            aloe__extract2( IUserInterfaceEvents1, Design, args, argv, sender, design );
            
            if ( !m_design )
            {
                Types::Recti rcSrc( Types::Point2i(0,0), m_bitmap[ &IRasterFormat::RasterSize ] );
                Types::Recti rect = m_entity[ &IFrameClient::Frame ][ &IFrame::Bound ];
                
                m_design = design[ &IGraphicsDesign::CreateDesign ]( rect );
                Types::SizeType nFont = ( m_design[ &IGraphicsDesign::Fonts ] += m_font );
                m_design[ &IDrawing::DrawRaster ]( rect, m_bitmap, rcSrc, Types::Color32(255,255,255), 0, 0x0 );
                m_design[ &IDrawing::DrawString ]( m_label, rect, nFont, Types::Color32(0,0,255), DT_CENTER | DT_SINGLELINE | DT_VCENTER );
            }
                
            Types::SizeType nSubDesign = design[ &IGraphicsDesign::SubDesigns ] += m_design;
            design[ &IDrawing::DrawSubDesign ]( m_design[ &IGraphicsDesign::Bound ], nSubDesign );
            
            return true;
        }

        aloe__method_imp( IUserInterfaceEvents2, Motion, argv )
        {
            aloe__extract2( IUserInterfaceEvents2, Motion, args, argv, sender, pos );
            
            return true;
        }

        aloe__method_imp( IUserInterfaceEvents2, Hover, argv )
        {
            aloe__extract1( IUserInterfaceEvents2, Hover, args, argv, sender );
            
            if ( m_bitmap.get() != m_bitmapPressed.get() )
            {
                m_bitmap = m_bitmapHighlight;
                
                m_entity[ &IEventSource::Raise ][ &IUserInterfaceEvents1::Dirty ]
                    ( m_entity, m_entity[ &IFrameClient::Frame ][ &IFrame::Bound ].value() );
            }
            
            return true;
        }
        
        aloe__method_imp( IUserInterfaceEvents2, Leave, argv )
        {
            aloe__extract1( IUserInterfaceEvents2, Hover, args, argv, sender );

            if ( m_bitmap.get() != m_bitmapPressed.get() )
            {
                m_bitmap = m_bitmapNormal;

                m_entity[ &IEventSource::Raise ][ &IUserInterfaceEvents1::Dirty ]
                    ( m_entity, m_entity[ &IFrameClient::Frame ][ &IFrame::Bound ].value() );
            }
            
            return true;
        }

        aloe__method_imp( IUserInterfaceEvents3, Press, argv )
        {
            aloe__extract3( IUserInterfaceEvents3, Press, args, argv, sender, button, pos );

            m_bitmap = m_bitmapPressed;

            m_entity[ &IEventSource::Raise ][ &IUserInterfaceEvents1::Dirty ]
                ( m_entity, m_entity[ &IFrameClient::Frame ][ &IFrame::Bound ].value() );

            return true;
        }

        aloe__method_imp( IUserInterfaceEvents3, Release, argv )
        {
            aloe__extract3( IUserInterfaceEvents3, Release, args, argv, sender, button, pos );
            
            Types::Recti rect = m_entity[ &IFrameClient::Frame ][ &IFrame::Bound ];
            if ( rect.isPointInside( pos ))
            {
                m_bitmap = m_bitmapHighlight;
            }
            else {
                m_bitmap = m_bitmapNormal;
            }

            m_entity[ &IEventSource::Raise ][ &IUserInterfaceEvents1::Dirty ]( m_entity, rect );

            return true;
        }

        aloe__method_imp( IUserInterfaceEvents3, Click, argv )
        {
            aloe__extract3( IUserInterfaceEvents3, Click, args, argv, sender, button, pos );

            return true;
        }

        aloe__method_imp( IUserInterfaceEvents3, DoubleClick, argv )
        {
            aloe__extract3( IUserInterfaceEvents3, DoubleClick, args, argv, sender, button, pos );

            return true;
        }
    
    };
    
    struct CEntity
        : Detail::Implementation
        < CEntity
        , Detail::Interfaces< IEntity, IEventSource, IFrameClient >
        , Detail::Bases< Detail::CRefCount > >
    {
        ThisPtr __init__( const Types::String &name )
        {
            m_name = name;

            return Super::__init__();
        }
            
        //
        // IEntity
        //

        Types::String m_name;
        Utils::SmartPtr< IContainer, Utils::WeakPointerPolicy > m_container;
        
        aloe__property_imp_put( IEntity, Name, name )
        {
            m_name = name;
        }
        
        aloe__property_imp_get( IEntity, Name )
        {
            return m_name;
        }
        
        aloe__property_imp_put( IEntity, Container, container)
        {
            m_container = container;
        }
        
        aloe__property_imp_get( IEntity, Container )
        {
            return m_container;
        }
       
        //
        // IFrameClient
        //
        
        Utils::SmartPtr< IFrame, Utils::WeakPointerPolicy > m_frame;
        
        aloe__property_imp_put( IFrameClient, Frame, frame )
        {
            m_frame = frame;
        }
        
        aloe__property_imp_get( IFrameClient, Frame )
        {
            return m_frame;
        }

        aloe__method_imp( IFrameClient, Move, argv )
        {
            aloe__extract1( IFrameClient, Move, args, argv, rect );

            Types::Long flags = 1;

            __self__()[ &IEventSource::Raise ][ &IUserInterfaceEvents::Move ]( __self__(), rect, flags );

            return Types::None();
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
    };
    
    struct CRelativeFrame
        : Detail::Implementation
        < CRelativeFrame
        , Detail::Interfaces< IFrame, IFrameClient >
        , Detail::Bases< Detail::CRefCount > >
    {
        Types::Vector2i m_distP1;
        Types::Vector2i m_distP2;
        Types::Recti m_bound;
        Utils::SmartPtr< IFrame, Utils::WeakPointerPolicy > m_frame;
        
        typedef std::set< Utils::SmartPtr< IFrameClient > > SetOfClients_t;
        SetOfClients_t m_setOfClients;

        void CalcBound( const Types::Recti &rect )
        {
            m_bound.x1 = Utils::makePositiveCoord( m_distP1.dx, rect.x1, rect.x2 );
            m_bound.y1 = Utils::makePositiveCoord( m_distP1.dy, rect.y1, rect.y2 );
            m_bound.x2 = Utils::makePositiveCoord( m_distP2.dx, rect.x1, rect.x2 );
            m_bound.y2 = Utils::makePositiveCoord( m_distP2.dy, rect.y1, rect.y2 );
        }

        ThisPtr __init__( const Types::Vector2i &distP1, const Types::Vector2i &distP2 )
        {
            m_distP1 = distP1;
            m_distP2 = distP2;
            return Super::__init__();
        }
        
        aloe__property_imp_put( IFrame, Bound, bound )
        {
            m_bound = bound;
        }

        aloe__property_imp_get( IFrame, Bound )
        {
            return m_bound;
        }

        aloe__property_imp_put( IFrame, Parent, frame )
        {
            m_frame = frame;
        }

        aloe__property_imp_get( IFrame, Parent )
        {
            return m_frame;
        }

        aloe__property_imp_put( IFrame, Clients, clients )
        {
            m_setOfClients.clear();

            for ( size_t i = 0, n = clients.size(); i < n; ++i )
            {
                m_setOfClients.insert( clients[i] );
            }
        }

        aloe__property_imp_get( IFrame, Clients )
        {
            Utils::VectorOf< Utils::SmartPtr< IFrameClient > > array;

            for ( SetOfClients_t::iterator iter = m_setOfClients.begin(); iter != m_setOfClients.end(); ++iter )
            {
                array.push_back( *iter );
            }

            return array.m_array;
        }

        aloe__property_imp_append( IFrame, Clients, client )
        {
            return m_setOfClients.insert( client ).second;
        }

        aloe__property_imp_remove( IFrame, Clients, client )
        {
            SetOfClients_t::iterator iter = m_setOfClients.find( client );
            if ( iter != m_setOfClients.end() )
            {
                m_setOfClients.erase( iter );
                return true;
            }
            else {
                return false;
            }
        }

        aloe__property_imp_put( IFrameClient, Frame, frame )
        {
            m_frame = frame;
        }
        
        aloe__property_imp_get( IFrameClient, Frame )
        {
            return m_frame;
        }

        aloe__method_imp( IFrameClient, Move, argv )
        {
            aloe__extract1( IFrameClient, Move, args, argv, rect );

            CalcBound( rect );
            
            for ( SetOfClients_t::iterator iter = m_setOfClients.begin(); iter != m_setOfClients.end(); ++iter )
            {
                (*iter)[ &IFrameClient::Move ]( m_bound );
            }

	    return Types::None();
        }
    };

    
};//Aloe


struct MyWindowEvents
    : Aloe::Detail::Implementation
    < MyWindowEvents
    , Aloe::Detail::Interfaces
        < Aloe::Win32::IWindowEvents
        , Aloe::IWindowEvents
        , Aloe::IUserInputEvents
        , Aloe::IUserInterfaceEvents
        , Aloe::IUserInterfaceEvents1
        , Aloe::IUserInterfaceEvents2
        , Aloe::IUserInterfaceEvents3 >
    , Aloe::Detail::Bases< Aloe::Detail::CRefCount > >
{
    Aloe::Utils::SmartPtr< Aloe::IWindow, Aloe::Utils::WeakPointerPolicy > m_window;
    Aloe::Utils::SmartPtr< Aloe::IGraphicsDesign > m_design;
    Aloe::Utils::SmartPtr< Aloe::IRaster > m_backBitmap;
    Aloe::Utils::SmartPtr< Aloe::IRaster > m_bitmapBackImage;
    Aloe::Types::Point2i m_mouseTouch;
    Aloe::Types::Recti m_boundTouch;
    Aloe::Types::Recti m_frameRect;
    Aloe::Types::Int m_iMouseTouch;
    Aloe::Types::Vector2i m_resizeLeftUpper;
    Aloe::Types::Vector2i m_resizeRightBottom;
    Aloe::Utils::SmartPtr< Aloe::ICursorShape > m_cursorArrow, m_cursorNWSE, m_cursorNESW, m_cursorNS, m_cursorWE;
    Aloe::Utils::SmartPtr<> m_objectUnderMouse;
    Aloe::Utils::SmartPtr<> m_objectPressed;

    enum {
        TOUCH_NONE   = 0,
        TOUCH_LEFT   = 1,
        TOUCH_RIGHT  = 2,
        TOUCH_TOP    = 4,
        TOUCH_BOTTOM = 8
    };

    MyWindowEvents() : m_iMouseTouch( TOUCH_NONE ), m_resizeLeftUpper( 4, 4 ), m_resizeRightBottom( 4, 4 )
    {
        aloe__try {
            
            Utils::SmartPtr< IPropertyMap > prop  = Root[ &IFactory::Create ][aloe__string("PropertyMap")]().AutoQ();

            prop[ &IPropertyMap::Int ]( aloe__string("Cursor.SystemResource"),0 ) = Utils::copyCast< Types::Int >( IDC_ARROW );
            m_cursorArrow = Root[ &IFactory::Create ][aloe__string("Cursor")]( prop ).AutoQ();
            
            prop[ &IPropertyMap::Int ]( aloe__string("Cursor.SystemResource"),0 ) = Utils::copyCast< Types::Int >( IDC_SIZENWSE );
            m_cursorNWSE = Root[ &IFactory::Create ][aloe__string("Cursor")]( prop ).AutoQ();
            
            prop[ &IPropertyMap::Int ]( aloe__string("Cursor.SystemResource"),0 ) = Utils::copyCast< Types::Int >( IDC_SIZENESW );
            m_cursorNESW = Root[ &IFactory::Create ][aloe__string("Cursor")]( prop ).AutoQ();
            
            prop[ &IPropertyMap::Int ]( aloe__string("Cursor.SystemResource"),0 ) = Utils::copyCast< Types::Int >( IDC_SIZENS );
            m_cursorNS = Root[ &IFactory::Create ][aloe__string("Cursor")]( prop ).AutoQ();
            
            prop[ &IPropertyMap::Int ]( aloe__string("Cursor.SystemResource"),0 ) = Utils::copyCast< Types::Int >( IDC_SIZEWE );
            m_cursorWE = Root[ &IFactory::Create ][aloe__string("Cursor")]( prop ).AutoQ();
            
            prop[ &IPropertyMap::String ](aloe__string("Bitmap.Filename"),0) = aloe__string("backImage.bmp");
            m_bitmapBackImage = Root[ &IFactory::Create ][aloe__string("Bitmap")]( prop ).AutoQ();

        } aloe__finish;
    
    }
    
    ~MyWindowEvents()
    {
        //KillOpenGL();
    }

    ThisPtr __init__( Aloe::Utils::SmartPtr< Aloe::IWindow > window )
    {
        m_window = window;
        //InitOpenGL();
        return Super::__init__();
    }

    const Aloe::Utils::SmartPtr< Aloe::IRaster > & GetBackBitmap( const Aloe::Types::Recti &clientRect )
    {
        aloe__try {
            
            Types::Vector2i bitmapSize;
            //Types::Vector2i screenSize( ::GetSystemMetrics( SM_CXSCREEN ), ::GetSystemMetrics( SM_CYSCREEN ));

            if ( !!m_backBitmap )
            {
                bitmapSize = m_backBitmap[ &IRasterFormat::RasterSize ];
            }

            if ( clientRect.size() != bitmapSize )
            //if ( screenSize != bitmapSize )
            {
                m_backBitmap = Root[ &IFactory::Create ][aloe__string("Bitmap")]().AutoQ();
                m_backBitmap[ &IRasterFormat::RasterSize ] = clientRect.size();
                //m_backBitmap[ &IRasterFormat::RasterSize ] = screenSize;
                m_backBitmap[ &IRasterFormat::PixelType ] = Types::PixelType::RGB;
                //m_backBitmap[ &IRasterFormat::PixelType ] = 0;
            }

        } aloe__finish;

        return m_backBitmap;
    }

    Aloe::Types::Long DetectResizeAreas( const Aloe::Types::Recti &bound, const Aloe::Types::Point2i &mouse )
    {
        Aloe::Types::Long areas = 0;

        if ( bound.x1 + m_resizeLeftUpper.dx > mouse.x )
        {
            areas |= TOUCH_LEFT;
        }
        if ( bound.x2 - m_resizeRightBottom.dx < mouse.x )
        {
            areas |= TOUCH_RIGHT;
        }
        if ( bound.y1 + m_resizeLeftUpper.dy > mouse.y )
        {
            areas |= TOUCH_TOP;
        }
        if ( bound.y2 - m_resizeRightBottom.dy < mouse.y )
        {
            areas |= TOUCH_BOTTOM;
        }
        if ( 0 == areas )
        {
            areas = TOUCH_LEFT | TOUCH_RIGHT | TOUCH_TOP | TOUCH_BOTTOM;
        }
        return areas;
    }

    void SelectCursorShape( Aloe::Types::Long areas )
    {
        aloe__try {
            Utils::SmartPtr< ICursorShape > cursor = m_cursorArrow;

            if (( areas == (TOUCH_LEFT | TOUCH_TOP) ) || ( areas == (TOUCH_RIGHT | TOUCH_BOTTOM) ))
            {
                cursor = m_cursorNWSE;
            }
            if (( areas == (TOUCH_RIGHT | TOUCH_TOP )) || ( areas == (TOUCH_LEFT | TOUCH_BOTTOM )))
            {
                cursor = m_cursorNESW;
            }
            if (( areas == ( TOUCH_TOP )) || ( areas == ( TOUCH_BOTTOM )))
            {
                cursor = m_cursorNS;
            }
            if (( areas == ( TOUCH_LEFT )) || ( areas == ( TOUCH_RIGHT )))
            {
                cursor = m_cursorWE;
            }

            Root[ &IUserInputState::CursorShape ] = cursor;
        } aloe__finish;
    }

    aloe__method_imp( IUserInterfaceEvents, Close, argv )
    {
        aloe__extract2( IUserInterfaceEvents, Close, args, argv, sender, flags );

        return false;
    }
    
    aloe__method_imp( IUserInterfaceEvents, Show, argv )
    {
        return false;
    }
    
    aloe__method_imp( IUserInterfaceEvents, Activate, argv )
    {
        return false;
    }
    
    aloe__method_imp( IUserInterfaceEvents, Move, argv )
    {
        aloe__extract3( IUserInterfaceEvents, Move, args, argv, sender, frameRect, flags );
        
        return false;
    }
    
    aloe__method_imp( IUserInterfaceEvents, Paint, argv )
    {
        aloe__extract3( IUserInterfaceEvents, Paint, args, argv, sender, screen, rect );

        return false;
    }
    
    aloe__method_imp( IUserInterfaceEvents1, Dirty, argv )
    {
        aloe__extract2( IUserInterfaceEvents1, Dirty, args, argv, sender, rect );

        m_design = Aloe::Types::None();

        aloe__try {
            
            sender[ &IWindow::DirtyRects ] += rect;
                
        } aloe__finish;

        return false;
    }
    
    aloe__method_imp( IUserInterfaceEvents1, Design, argv )
    {
        aloe__try {
            aloe__extract2( IUserInterfaceEvents1, Design, args, argv, sender, design );

            Utils::ArrayOf< Utils::SmartPtr<> > array = sender[ &IContainer::Objects ];
            for ( size_t i = 0, n = array.size(); i < n ; ++i )
            {
                aloe__try {

                    Utils::SmartPtr<> widget = array[i];

                    widget[ &IEventSource::Raise ][ &IUserInterfaceEvents1::Design ]( widget, design );

                } aloe__finish;
            }
        } aloe__finish;

        return false;
    }
    
    aloe__method_imp( IUserInterfaceEvents2, Motion, argv )
    {
        aloe__extract2( IUserInterfaceEvents2, Motion, args, argv, sender, pos );

        aloe__try {
        
            Utils::SmartPtr<> underMouse = sender[ &IContainer::ObjectByPoint ][ pos ].value();
        
            if ( m_objectUnderMouse.get() != underMouse.get() )
            {
                if ( m_objectUnderMouse.get() )
                {
                    m_objectUnderMouse[ &IEventSource::Raise ][ &IUserInterfaceEvents2::Leave ]( sender );
                }

                m_objectUnderMouse = underMouse;

                if ( m_objectUnderMouse.get() )
                {
                    m_objectUnderMouse[ &IEventSource::Raise ][ &IUserInterfaceEvents2::Hover ]( m_objectUnderMouse );
                }
            }
            
            if ( m_objectUnderMouse.get() )
            {
                m_objectUnderMouse[ &IEventSource::Raise ][ &IUserInterfaceEvents2::Motion ]( m_objectUnderMouse, pos );
            }

        } aloe__finish;        


        return true;
    }

    aloe__method_imp( IUserInterfaceEvents2, Hover, argv )
    {
        aloe__extract1( IUserInterfaceEvents2, Hover, args, argv, sender );

        aloe__try {
        } aloe__finish;        

        return true;
    }

    aloe__method_imp( IUserInterfaceEvents2, Leave, argv )
    {
        aloe__extract1( IUserInterfaceEvents2, Leave, args, argv, sender );

        aloe__try {
            if ( m_objectUnderMouse.get() )
            {
                m_objectUnderMouse[ &IEventSource::Raise ][ &IUserInterfaceEvents2::Leave ]( m_objectUnderMouse );
            }
        } aloe__finish;        

        return true;
    }
    
    aloe__method_imp( IUserInterfaceEvents3, Press, argv )
    {
        aloe__extract3( IUserInterfaceEvents3, Press, args, argv, sender, button, pos );

        aloe__try {
            if ( m_objectUnderMouse.get() )
            {
                m_objectUnderMouse[ &IEventSource::Raise ][ &IUserInterfaceEvents3::Press ]( m_objectUnderMouse, button, pos );
                m_objectPressed = m_objectUnderMouse;
            }
        } aloe__finish;        

        return true;
    }
    
    aloe__method_imp( IUserInterfaceEvents3, Release, argv )
    {
        aloe__extract3( IUserInterfaceEvents3, Release, args, argv, sender, button, pos );

        aloe__try {
            if ( m_objectPressed.get() )
            {
                m_objectPressed[ &IEventSource::Raise ][ &IUserInterfaceEvents3::Release ]( m_objectPressed, button, pos );
                m_objectPressed = Types::None();
            }
        } aloe__finish;        

        return true;
    }
    
    aloe__method_imp( IUserInterfaceEvents3, Click, argv )
    {
        aloe__extract3( IUserInterfaceEvents3, Click, args, argv, sender, button, pos );

        aloe__try {
            if ( m_objectUnderMouse.get() == m_objectPressed.get() )
            {
                m_objectPressed[ &IEventSource::Raise ][ &IUserInterfaceEvents3::Click ]( m_objectPressed, button, pos );
            }
        } aloe__finish;        

        return true;
    }
    
    aloe__method_imp( IUserInterfaceEvents3, DoubleClick, argv )
    {
        aloe__extract3( IUserInterfaceEvents3, DoubleClick, args, argv, sender, button, pos );

        aloe__try {
            if ( m_objectUnderMouse.get() )
            {
                m_objectUnderMouse[ &IEventSource::Raise ][ &IUserInterfaceEvents3::DoubleClick ]( m_objectUnderMouse, button, pos );
            }
        } aloe__finish;        


        return true;
    }
    
    aloe__method_imp( IUserInputEvents, Key, argv )
    {
        return false;
    }

    aloe__method_imp( IUserInputEvents, Focus, argv )
    {
        return false;
    }
    

    aloe__method_imp( Aloe::IWindowEvents, Close, argv )
    {
        aloe__extract1( Aloe::IWindowEvents, Close, args, argv, sender );

        return false;
    }
    
    /*aloe__method_imp( Aloe::IWindowEvents, Show, argv )
    {
        aloe__extract2( Aloe::IWindowEvents, Show, args, argv, sender, flags );

        return false;
    }*/
    
    aloe__method_imp( Aloe::IWindowEvents, Activate, argv )
    {
        aloe__extract2( Aloe::IWindowEvents, Activate, args, argv, sender, active );
        
        return false;
    }
    
    aloe__method_imp( Aloe::IWindowEvents, Focus, argv )
    {
        aloe__extract2( Aloe::IWindowEvents, Focus, args, argv, sender, active );
        
        return false;
    }
    
    aloe__method_imp( Aloe::IWindowEvents, LostCapture, argv )
    {
        aloe__extract2( Aloe::IWindowEvents, LostCapture, args, argv, sender, capture );
        
        return false;
    }
    
    aloe__method_imp( Aloe::IWindowEvents, Move, argv )
    {
        aloe__extract3( Aloe::IWindowEvents, Move, args, argv, sender, frameRect, flags );

        aloe__try {

            if ( Utils::valueOf( m_frameRect.size() ) != Utils::valueOf( frameRect.size() ))
            {
                m_design = Types::None();

                /*Types::Recti area;
                area.x2 = frameRect.width();
                area.y2 = frameRect.height();
                Utils::SmartPtr< IRegion > region = Root[ &IFactory::Create ][aloe__string("Region")]().AutoQ();
                region[ &IRegion::RoundRect ]( area, Types::Vector2i(128,128) );
                sender[ &IWindow::Region ] = region;*/
            }

            m_frameRect = frameRect;

        } aloe__finish;
        
        return false;
    }
    
    aloe__method_imp( Aloe::IWindowEvents, Key, argv )
    {
        aloe__extract3( Aloe::IWindowEvents, Key, args, argv, sender, virtKey, isDown );
        
        return false;
    }
    
    aloe__method_imp( Aloe::IWindowEvents, Motion, argv )
    {
        aloe__extract2( Aloe::IWindowEvents, Motion, args, argv, sender, position );
            
        aloe__try {

            if ( m_objectUnderMouse.get() || m_objectPressed.get() )
            {
                return true;
            }
            
            Types::Recti frame = sender[ &IWindow::FrameRect ];
            Types::Point2i mouse = position;
            mouse.x += frame.x1;
            mouse.y += frame.y1;

            if ( m_iMouseTouch )
            {

                Types::Vector2i distance = mouse - m_mouseTouch;
                Types::Recti bound = m_boundTouch;
                
                if ( m_iMouseTouch & TOUCH_LEFT )
                {
                    bound.x1 += distance.dx;
                }
                if ( m_iMouseTouch & TOUCH_RIGHT )
                {
                    bound.x2 += distance.dx;
                }
                if ( m_iMouseTouch & TOUCH_TOP )
                {
                    bound.y1 += distance.dy;
                }
                if ( m_iMouseTouch & TOUCH_BOTTOM )
                {
                    bound.y2 += distance.dy;
                }
                
                sender[ &IWindow::FrameRect ] = bound.fixCoords();
            }
            
            SelectCursorShape( DetectResizeAreas( frame, mouse ));

            m_window[ &IWindow::DirtyRects ] += m_window[ &IWindow::ClientRect ];

        } aloe__finish;

        return true;
    }
    
    aloe__method_imp( Aloe::IWindowEvents, Button, argv )
    {
        aloe__extract4( Aloe::IWindowEvents, Button, args, argv, sender, position, buttonNo, isDown );
        aloe__try {

            if ( m_objectUnderMouse.get() )
            {
                m_iMouseTouch = TOUCH_NONE;
                return true;
            }
            
            m_mouseTouch = position;
            m_boundTouch = sender[ &IWindow::FrameRect ];
            m_mouseTouch.x += m_boundTouch.x1;
            m_mouseTouch.y += m_boundTouch.y1;
            
            Types::Long areas = DetectResizeAreas( m_boundTouch, m_mouseTouch );

            if ( isDown )
            {
                m_iMouseTouch = areas;
            }
            else
            {
                m_iMouseTouch = TOUCH_NONE;
            }
            
            SelectCursorShape( areas );
            
        } aloe__finish;
        return false;
    }
    
    aloe__method_imp( Aloe::IWindowEvents, DoubleClick, argv )
    {
        aloe__extract3( Aloe::IWindowEvents, DoubleClick, args, argv, sender, position, buttonNo );
        
        return false;
    }
       
    /*
    ::HWND  m_hWnd;
    ::HDC   m_hDc;
    ::HGLRC m_glRc;
    */

    void InitOpenGL()
    {
	/*
        m_hWnd = NULL;
        m_hDc  = NULL;
        m_glRc = NULL;

        aloe__try {

            m_hWnd = m_window[ &Win32::IWindow::HWnd ];
            m_hDc = ::GetDC( m_hWnd );
            SetupOpenGL( m_hDc );
            
        } aloe__finish;
	*/
    }

    void SetPixelFormatOpenGL( ::HDC hDc )
    {
	/*
        PIXELFORMATDESCRIPTOR pfd = { 
            sizeof(PIXELFORMATDESCRIPTOR),   // size of this pfd 
            1,                     // version number 
            PFD_DRAW_TO_WINDOW |   // support window 
                PFD_SUPPORT_OPENGL |   // support OpenGL 
                PFD_DOUBLEBUFFER,      // double buffered 
            PFD_TYPE_RGBA,         // RGBA type 
            24,                    // 24-bit color depth 
            0, 0, 0, 0, 0, 0,      // color bits ignored 
            0,                     // no alpha buffer 
            0,                     // shift bit ignored 
            0,                     // no accumulation buffer 
            0, 0, 0, 0,            // accum bits ignored 
            32,                    // 32-bit z-buffer 
            0,                     // no stencil buffer 
            0,                     // no auxiliary buffer 
            PFD_MAIN_PLANE,        // main layer 
            0,                     // reserved 
            0, 0, 0                // layer masks ignored 
        }; 
        int  iPixelFormat; 

        // get the best available match of pixel format for the device context  
        iPixelFormat = ChoosePixelFormat( hDc, &pfd); 

        // make that the pixel format of the device context 
        ::BOOL bSetPF = SetPixelFormat(hDc, iPixelFormat, &pfd); 
	*/
    }
    
    void SetupOpenGL( ::HDC hDc )
    {
	/*
        SetPixelFormatOpenGL( hDc );

        m_glRc = ::wglCreateContext( hDc );
	*/
    }

    void PrepareOpenGL()
    {
	/*
        aloe__try {
            
            ::wglMakeCurrent( m_hDc, m_glRc );
            Types::Recti clientRect = m_window[ &IWindow::ClientRect ]; 
            glViewport( clientRect.x1, clientRect.y1, clientRect.x2, clientRect.y2 );
            glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
            
        } aloe__finish;
	*/
    }

    void PaintOpenGL()
    {
	/*
        PrepareOpenGL();
        
        aloe__try {

            aloe__try {
                Types::Recti clientRect = m_window[ &IWindow::ClientRect ];
                Utils::SmartPtr< IPixelArray > bkPixels = m_backBitmap[ &IRaster::PixelRect ][ clientRect ].value().AutoQ();
                Types::PixelRectangle pixRect;
                bkPixels[ &IPixelArray::Lock ]( &pixRect );
                glPixelStorei( GL_UNPACK_ROW_LENGTH, pixRect.m_bytesPerRow / pixRect.m_bytesPerPixel );
                glDrawPixels( pixRect.m_rect.width(), pixRect.m_rect.height(), GL_BGR_EXT, GL_UNSIGNED_BYTE, pixRect.m_pixels );
                bkPixels[ &IPixelArray::Unlock ]();
                
            } aloe__finish;

            glMatrixMode( GL_MODELVIEW );

            glLoadIdentity();
            glBegin( GL_LINES );
            {
                glColor3f( 0.0f, 0.0f, 1.0f );
                glVertex3f( -1.0f, 0.0f, 0.0f );
                glVertex3f( 1.0f, 0.0f, 0.0f );
                glColor3f( 1.0f, 0.0f, 0.0f );
                glVertex3f( -0.0f, -1.0f, 0.0f );
                glVertex3f( 0.0f, 1.0f, 0.0f );
            }
            glEnd();

            Types::Point2i mouse = Root[ &IUserInputState::CursorPos ];
            Types::Recti frameRect = m_window[ &IWindow::FrameRect ];
            
            //glOrtho( frameRect.x1, frameRect.y1, frameRect.x2, frameRect.y2, 1, 1 );
            glScaled( 2.0 / frameRect.width(), -2.0 / frameRect.height(), 1.0 );
            glBegin( GL_LINES );
            {
                glColor3f( 0.0f, 1.0f, 0.0f );
                glVertex2i( 0, 0 );
                glVertex2i( mouse.x - frameRect.x1 - frameRect.width()/2, mouse.y - frameRect.y1 - frameRect.height()/2 );
            }
            glEnd();

            glFlush();

        } aloe__finish;

        ::SwapBuffers( m_hDc );
	*/
    }

    void KillOpenGL()
    {
	/*
        ::wglDeleteContext( m_glRc );
        ::ReleaseDC( m_hWnd, m_hDc );
	*/
    }
    
    aloe__method_imp( Aloe::IWindowEvents, Paint, argv )
    {
        aloe__try {

            aloe__extract3( Aloe::IWindowEvents, Paint, args, argv, sender, screen, rect );
            
            Types::Recti clientRect = sender[ &IFrame::Bound ];
            
            {
                Utils::SmartPtr<> device = Root[ &IFactory::Create ][aloe__string("GraphicDevice")]();

                device[ &IGraphicDevice::Raster ] = GetBackBitmap( clientRect );

                if ( !m_design )
                {
                    m_design = device[ &IGraphicDevice::CreateDesign ]( clientRect );
                    
                    Types::Vector2i sizeBackImage = m_bitmapBackImage[ &IRasterFormat::RasterSize ];
                    Types::Vector2i sizeBackBuffer = m_backBitmap[ &IRasterFormat::RasterSize ];
                    
                    Types::Int xCuts[4] = { 0, 64, -65, -1 };
                    Types::Int yCuts[4] = { 0, 64, -65, -1 };
                    
                    for ( int row = 0; row < 3; ++row )
                    {
                        for ( int col = 0; col < 3; ++col )
                        {
			    Types::Point2i ptSrc1(
				    Utils::makePositiveCoord( xCuts[ col + 0 ], 0, sizeBackImage.dx ),
				    Utils::makePositiveCoord( yCuts[ row + 0 ], 0, sizeBackImage.dy ));

			    Types::Point2i ptSrc2(
				    Utils::makePositiveCoord( xCuts[ col + 1 ], 0, sizeBackImage.dx ),
				    Utils::makePositiveCoord( yCuts[ row + 1 ], 0, sizeBackImage.dy ));

                            Types::Recti rcSrc( ptSrc1, ptSrc2 );
                                    
			    Types::Point2i ptDst1(
				    Utils::makePositiveCoord( xCuts[ col + 0 ], 0, sizeBackBuffer.dx ),
				    Utils::makePositiveCoord( yCuts[ row + 0 ], 0, sizeBackBuffer.dy ));
			    
			    Types::Point2i ptDst2(
				    Utils::makePositiveCoord( xCuts[ col + 1 ], 0, sizeBackBuffer.dx ),
				    Utils::makePositiveCoord( yCuts[ row + 1 ], 0, sizeBackBuffer.dy ));
                            
                            Types::Recti rcDst( ptDst1, ptDst2 );

			    Types::Color32 color(255,255,255);
                    
                            m_design[ &IDrawing::DrawRaster ]( rcDst, m_bitmapBackImage, rcSrc, color, 0, 0x0 );
                        }
                    }
                        
                    sender[ &IEventSource::Raise ][ &IUserInterfaceEvents1::Design ]( sender, m_design );
                }

                device[ &IGraphicDevice::RenderDesign ]( m_design, rect );
            }
                
            screen[ &Win32::IDevContext::DrawBitmap ]( rect, m_backBitmap.AutoQ(), rect, 255, 0 );
                
            //PaintOpenGL();
            

            //static bBlt = false;
            //if ( bBlt )
            //{
            //    screen[ &Win32::IDevContext::DrawBitmap ]( rect, m_backBitmap.AutoQ(), rect, 255, 0 );
            //}

        } aloe__finish;

        return true;
    }

    
    aloe__method_imp( Aloe::Win32::IWindowEvents, Event, argv )
    {
        aloe__extract4( Aloe::Win32::IWindowEvents, Event, args, argv, sender, message, wParam, lParam );

        return true;
    };

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

        SmartPtr<> wnd = Aloe::Root[ &Win32::IWindowFactory::CreateWindow ]
            ( aloe__string("TestClass"), CS_HREDRAW | CS_VREDRAW,
              aloe__string("TestWindow"), WS_POPUP /*WS_OVERLAPPEDWINDOW*/, 0/*WS_EX_LAYERED*/, Recti( Point2i(10,10), Vector2i( 640, 480 )),
              (HWND)NULL, (HMENU)NULL
            );

        aloe__try {
        

            wnd[ &Win32::IWindow::Class ][ &Win32::IWindowClass::Style ] = 
                wnd[ &Win32::IWindow::Class ][ &Win32::IWindowClass::Style ] | CS_DBLCLKS;
            
            Utils::SmartPtr< MyWindowEvents > myWndEvents = (new MyWindowEvents)->__init__( wnd.AutoQ() );
            
            wnd[ &Aloe::IEventSource::Listeners ] += myWndEvents;

            aloe__try {
                Utils::SmartPtr< CRelativeFrame > frame0;

                frame0 = ( new CRelativeFrame  )->__init__( Vector2i(10,-201), Vector2i(-11,-11) );
                
                wnd[ &IFrame::Clients ] += frame0;
                frame0[ &IFrameClient::Frame ] = wnd.AutoQ();

                aloe__try {

                    Utils::SmartPtr< CRelativeFrame > frame;
                    Utils::SmartPtr< CEntity > entity;
                    Utils::SmartPtr< CButtonDesigner > designer;

                    frame    = ( new CRelativeFrame  )->__init__( Vector2i(10,10), Vector2i(110,50) );
                    entity   = ( new CEntity         )->__init__( aloe__string("Hello") );
                    designer = ( new CButtonDesigner )->__init__( entity, aloe__string("Hello !!!") );

                    entity[ &IEventSource::Listeners ] += designer;

                    entity[ &IFrameClient::Frame     ] = frame;
                    frame [ &IFrame::Clients         ] += entity;

                    frame [ &IFrameClient::Frame     ] = frame0;
                    frame0[ &IFrame::Clients         ] += frame;

                    wnd   [ &IContainer::Objects     ] += entity;
                    entity[ &IEntity::Container      ] = wnd.AutoQ();

                } aloe__finish;

                aloe__try {

                    Utils::SmartPtr< CRelativeFrame > frame;
                    Utils::SmartPtr< CEntity > entity;
                    Utils::SmartPtr< CButtonDesigner > designer;

                    frame    = ( new CRelativeFrame  )->__init__( Vector2i(-111,10), Vector2i(-11,50) );
                    entity   = ( new CEntity         )->__init__( aloe__string("Bye") );
                    designer = ( new CButtonDesigner )->__init__( entity, aloe__string("Goodbye !!!") );

                    entity[ &IEventSource::Listeners ] += designer;

                    entity[ &IFrameClient::Frame     ] = frame;
                    frame [ &IFrame::Clients         ] += entity;

                    frame [ &IFrameClient::Frame     ] = frame0;
                    frame0[ &IFrame::Clients         ] += frame;

                    wnd   [ &IContainer::Objects     ] += entity;
                    entity[ &IEntity::Container      ] = wnd.AutoQ();

                } aloe__finish;

            } aloe__finish;
            
            
            wnd[ &IWindow::ClientRect ] = Recti( Point2i(0,0), Vector2i( 300, 480 ));

            wnd[ &Win32::ILayeredWindow::Opacity ] = 225;
            wnd[ &Win32::ILayeredWindow::ColorKey ] = Types::Color32( 255, 0, 255 );
            //wnd[ &Win32::ILayeredWindow::Flags ] = LWA_COLORKEY | LWA_ALPHA;
            wnd[ &Win32::ILayeredWindow::Commit ]();

        } aloe__finish;

        
        Aloe::Root[ &Win32::IMessageLoop::Run ]();

    } aloe__finish;

    return 0;
}

int __stdcall WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
    return main();
}


