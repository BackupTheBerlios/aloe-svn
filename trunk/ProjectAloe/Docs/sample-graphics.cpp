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



//----
window = Root[ IFactory::Create ]["Window"];
widget = Root[ IFactory::Create ]["Widget"];

button = Root[ IFactory::Create ]["ButtonDesigner"]();
label = Root[ IFactory::Create ]["LabelDesigner"]();

mesh = Root[ IFactory::Create ]["MeshLayout"]();
lnx1 = Root[ IFactory::Create ]["MeshLine"]();
lnx2 = Root[ IFactory::Create ]["MeshLine"]();
lny1 = Root[ IFactory::Create ]["MeshLine"]();
lny2 = Root[ IFactory::Create ]["MeshLine"]();
rect = Root[ IFactory::Create ]["MeshCell"]();

rect[ IMeshCell::HLineStart ] = lnx1;
rect[ IMeshCell::VLineStart ] = lny1;
rect[ IMeshCell::HLineEnd ] = lnx2;
rect[ IMeshCell::VLineEnd ] = lny2;

widget[ IFrameClient::Frame ] = rect;
mesh[ IFrameClient::Frame ] = window;
window[ IContainer::Objects ] += widget;

x1[ IMeshLine::Placement ] = make_tuple( 1, 5 );
x2[ IMeshLine::Placement ] = make_tuple( 2, 5 );
y1[ IMeshLine::Placement ] = make_tuple( 3, 5 );
y2[ IMeshLine::Placement ] = make_tuple( 4, 5 );

mesh[ IMeshLayout::HLines ] += x1;
mesh[ IMeshLayout::HLines ] += x2;
mesh[ IMeshLayout::VLines ] += y1;
mesh[ IMeshLayout::VLines ] += y2;
mesh[ IMeshLayout::Cells ] += rect;

button[ IButtonDesigner::BgImage ] = bgRaster;
button[ IButtonDesigner::BgRect ] = bgRect;
label[ ILabelDesigner::Text ] = aloe__string("Hello World!!!");
label[ ILabelDesigner::Font ] = font;

widget[ IGraphicsDesignerClient::Designers ] += button;
widget[ IGraphicsDesignerClient::Designers ] += label;

widget[ ILabelDesigner::TextByState ]["normal"] = aloe__string("Hello!!!");
widget[ ILabelDesigner::TextByState ]["hover"] = aloe__string("Goodbye!!!");

widget[ IGraphicsDesignerClient::LayerOrder ]["background"] = 100;
widget[ IGraphicsDesignerClient::LayerOrder ]["label"] = 200;
widget[ IGraphicsDesignerClient::LayerOrder ]["overlay"] = 300;

window[ IWindow::ClientSize ] = Vector2i( 800, 600 );
window[ IFullscreen::Size ] = Vector2i( 800, 600 );
window[ IFullscreen::Refresh ] = 85;
window[ IFullscreen::ColorBits ] = 24;
window[ IFullscreen::DepthBits ] = 24;
window[ IFullscreen::Enter ]();
window[ IFullscreen::Leave ]();

design = design[ IGraphicsDesign::Compile ]( window );
text = Root[ IFactory::Create ]["TextDesign"]();
text[ ITextDesign::Text ] = aloe__string("Hello!!!");
text[ IGraphicsDesignItem::Font ] = font;
text = text[ IGraphicsDesignItem::Compile ]( window );

design[ IGraphicsDesign::Items ] += text;
design = design[ IGraphicsDesign::Compile ]( window );

tools[ IDrawingTools::Draw ]( text );
