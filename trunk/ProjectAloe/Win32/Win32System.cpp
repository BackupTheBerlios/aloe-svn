#include "Aloe/aloeWin32.h"
#include <set>
#include <map>

#define ALOE_WIN32_SYSTEM
#include "Win32CWindowClass.h"
#include "Win32CWindow.h"
#include "Win32CFactory.h"

#pragma warning(disable:4250)

namespace Aloe {

    namespace Win32 {
       
        CWindow::DictWindows_t CWindow::s_dictWindows;

        Utils::SmartPtr< IFactory > Initialize( HINSTANCE hInstance )
        {
			return ( new CFactory )->__init__( hInstance )[ IFactory::This ];
        }

    };//Win32
};//Aloe

