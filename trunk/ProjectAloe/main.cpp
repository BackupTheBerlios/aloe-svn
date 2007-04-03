#define _WIN32_WINNT 0x0500
#define WINVER 0x0410

#include "Aloe/aloeWin32.h"

#include <stdio.h>
#include <set>
#include <map>

#pragma warning(disable:4250)

#include "UI/CButtonDesigner.h"
#include "UI/CEntity.h"
#include "UI/CRelativeFrame.h"
#include "UI/CWindowUI.h"

namespace Aloe {

    Utils::SmartPtr< IFactory > Root;

};//Aloe


Aloe::Utils::SmartPtr< CEntity > CreateButton(
		const Aloe::Utils::SmartPtr< IContainer > &container,
		const Aloe::Utils::SmartPtr< CRelativeFrame > &frame,
		const Aloe::Types::Vector2i &leftUpper,
		const Aloe::Types::Vector2i &rightBottom,
		const Aloe::Types::String   &strName,
		const Aloe::Types::String	&textLabel )
{
	aloe__try {

		Utils::SmartPtr< CRelativeFrame > frame1;
		Utils::SmartPtr< CEntity > entity;
		Utils::SmartPtr< CButtonDesigner > designer;

		frame1   = ( new CRelativeFrame  )->__init__( leftUpper, rightBottom );
		entity   = ( new CEntity         )->__init__( strName );
		designer = ( new CButtonDesigner )->__init__( entity, textLabel );

		entity[ &IEventSource::Listeners ] += designer;

		entity[ &IFrameClient::Frame     ] = frame1;
		frame1[ &IFrame::Clients         ] += entity;

		frame1[ &IFrameClient::Frame     ] = frame;
		frame [ &IFrame::Clients         ] += frame1;

		container[ &IContainer::Objects	 ] += entity;
		entity	 [ &IEntity::Container   ] = container;

		return entity;

	} aloe__finish;

	return Aloe::Types::None();
}


int main()
{
    aloe__try {
    
		Root = Win32::Initialize( ::GetModuleHandle(NULL) );

		Utils::SmartPtr<> wnd = Root[ &Win32::IWindowFactory::CreateWindow ]
            ( aloe__string("TestClass"), CS_HREDRAW | CS_VREDRAW,
              aloe__string("TestWindow"), WS_POPUP,
#ifdef WIN32
			  WS_EX_LAYERED,
#else
			  0,
#endif
			  Types::Recti( Types::Point2i(10,10), Types::Vector2i( 640, 480 )),
              (HWND)NULL, (HMENU)NULL
            );

        aloe__try {
        
            wnd[ &Win32::IWindow::Class ][ &Win32::IWindowClass::Style ] = 
                wnd[ &Win32::IWindow::Class ][ &Win32::IWindowClass::Style ] | CS_DBLCLKS;
            
            Utils::SmartPtr< CWindowUI > myWndEvents = (new CWindowUI )->__init__( wnd.AutoQ() );
            
            wnd[ &IEventSource::Listeners ] += myWndEvents;

            aloe__try {
                Utils::SmartPtr< CRelativeFrame > frame;

                frame = ( new CRelativeFrame  )->__init__( Types::Vector2i(10,-201), Types::Vector2i(-11,-11) );
                
                wnd[ &IFrame::Clients ] += frame;
                frame[ &IFrameClient::Frame ] = wnd.AutoQ();

				CreateButton( wnd.AutoQ(), frame,
						Types::Vector2i(10,10), Types::Vector2i(110,50),
						aloe__string("Button1"), aloe__string("Hello !!!"));

				CreateButton( wnd.AutoQ(), frame,
						Types::Vector2i(-111,10), Types::Vector2i(-11,50),
						aloe__string("Button2"), aloe__string("Goodbye !!!"));

            } aloe__finish;
            
            
            wnd[ &IWindow::ClientRect ] = Types::Recti( Types::Point2i(0,0), Types::Vector2i( 300, 480 ));

#ifdef WIN32
            wnd[ &Win32::ILayeredWindow::Opacity ] = 225;
            wnd[ &Win32::ILayeredWindow::ColorKey ] = Types::Color32( 255, 0, 255 );
            wnd[ &Win32::ILayeredWindow::Flags ] = LWA_COLORKEY | LWA_ALPHA;
            wnd[ &Win32::ILayeredWindow::Commit ]();
#endif

        } aloe__finish;

        
        Root[ &Win32::IMessageLoop::Run ]();

    } aloe__finish;

    return 0;
}

int __stdcall WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
    return main();
}


