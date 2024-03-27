#include <Wt/WPaintDevice.h>
#include <Wt/WPaintedWidget.h>
#include <Wt/WPainter.h>

#include <cmath>

#define M_PI 3.14159265358979323846

class PaintingInteractiveWidget : public Wt::WPaintedWidget
{
public:
  PaintingInteractiveWidget();

  void rotate(int aDegrees);

  Wt::JSlot rotateSlot;

protected:
  void paintEvent(Wt::WPaintDevice *aPaintDevice);

private:
  Wt::WJavaScriptHandle<Wt::WTransform> transform;
};