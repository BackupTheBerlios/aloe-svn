#ifndef ALOE_UI
#error "DO NOT INCLUDE THIS FILE!!! This header file can be only included by source file 'UI.cpp'."
#endif

namespace Aloe {

    struct CButtonDesigner
        : Detail::Implementation
        < CButtonDesigner
        , Detail::Interfaces<
			IUserInterfaceEvents,
			IUserInterfaceEvents1,
			IUserInterfaceEvents2,
			IUserInterfaceEvents3 >
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
    
    };//CButtonDesigner
    
};//Aloe
