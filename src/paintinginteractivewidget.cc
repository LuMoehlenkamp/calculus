#include "paintinginteractivewidget.hh"

PaintingInteractiveWidget::PaintingInteractiveWidget()
    : WPaintedWidget(), rotateSlot(1, this)
{
  resize(300,300);

  transform = createJSTransform(); // Create a client side transform

 	rotateSlot.setJavaScript(
    "function(o,e,deg) {"
		  "if (" + objJsRef() + ") {"
	      "var rad = deg / 180 * Math.PI;"
	      "var c = Math.cos(rad);"
	      "var s = Math.sin(rad);" +
	      // You can assign a new 6 element array to a transform,
	      // or change its individual elements.
	      transform.jsRef() + " = [c,-s,s,c,0,0];" +
	      repaintSlot().execJs() + ";"
		  "}"
	  "}");
}

void
PaintingInteractiveWidget::rotate(int aDegrees)
{
  double radians = aDegrees / 180.0 * M_PI;
	double c = std::cos(radians);
	double s = std::sin(radians);
	// Changes in value will be synced from server to client
	transform.setValue(Wt::WTransform(c, -s, s, c, 0, 0));
	update();
}

void
PaintingInteractiveWidget::paintEvent(Wt::WPaintDevice* aPaintDevice)
{
  Wt::WPainter painter(aPaintDevice);

	painter.translate(150, 150);

	// Set a 5px wide pen
	Wt::WPen pen;
	pen.setWidth(5);
	painter.setPen(pen);

	// Draw an arrow shape
	Wt::WPainterPath path;
	path.moveTo(-50,100);
	path.lineTo(50,100);
	path.lineTo(50,20);
	path.lineTo(100,20);
	path.lineTo(0,-100);
	path.lineTo(-100,20);
	path.lineTo(-50, 20);
	path.lineTo(-50,100);
	path.lineTo(50, 100);

	// Client side transforms can be set with
	// setWorldTransform, or applied to a path
	// with the map() function. In the latter case,
	// line thickness will not be affected by the
	// transform.
	Wt::WPainterPath transformedPath =
	    transform.value().map(path);
	painter.drawPath(transformedPath);  
}