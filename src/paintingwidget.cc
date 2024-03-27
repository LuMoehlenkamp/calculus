#include "paintingwidget.hh"

#include <Wt/WBrush.h>
#include <Wt/WColor.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WPaintDevice.h>
#include <Wt/WPaintedWidget.h>
#include <Wt/WPainter.h>
#include <Wt/WPainterPath.h>
#include <Wt/WPen.h>
#include <Wt/WPointF.h>
#include <Wt/WSpinBox.h>

PaintingWidget::PaintingWidget()
  : WPaintedWidget()
{
	resize(310, 400);
}

void
PaintingWidget::paintEvent(Wt::WPaintDevice *paintDevice) 
{
        Wt::WPainter painter(paintDevice);
        painter.setPen(Wt::WColor(Wt::StandardColor::Red));

	// DRAWING PRIMITIVE SHAPES
	// Draw a line from (0, 0) to (200, 0) and then 30 px downwards.
	painter.drawLine(0, 0, 200, 0);
	painter.drawLine(200, 0, 200, 30);
}