/***
 * Aloe (http://aloe.berlios.de)
 *
 * This example describes how to display text using aloe IFont and IRaster interfaces.
 *
 */


// let's say we've got some window from previous code
SmartPtr< IWindow > wnd;

// creating font by factory
SmartPtr< IFont > font = Root[ IFactory::CreateFont ]("Helvetica", 12);

// setting font parameters italic/bold
font[ IFont::Slant ] = 100;
font[ IFont::Weight ] = 600;

// getting font glyphs for given text
SmartPtr< ITextFaceset > faceset = font[ IFont::TextFaceset ]("Hello World!!!", 0L);

// area in which we'll try to render text
Recti rect( Point2i( 10, 10 ), Vector2i( 100, 100 ));

// we're converting glyphs of logical font into device dependant form (but w/o any rendering or memory waste - just mathematical operation)
SmartPtr< IRasterRect > ras = faceset[ ITextFaceset::Render ]( wnd[ IRaster::PixelRect ][ rect ] );

// after convertion to raster space coordinates, we know the rectangle occupied by text
Rect where = ras[ IRasterRect::Rect ];
// we're checking the height of text - it depends on number of lines (words may be wrapped)
Int height = where.height();
// if it is a single line text (for instance we're rendering menu item) the width may change
Int width = where.width();


// finally we accept result and we want it be to displayed
wnd[ IRasterRect::PixelRect ][ where ] = ras;

// if we're constructing some graphics, we'll need to use graphics design (I suppose we may obtain it from Root)
SmartPtr< IGraphicsDesign > design;

// just like in case of IWindow, we use IGraphicsDesign as logical blit target for text.
design[ IGraphicsDesign::PixelRect ][ where ] = ras;

// after design is complete we blit it into device
wnd[ IRasterRect::PixelRect ][ where ] = design;
