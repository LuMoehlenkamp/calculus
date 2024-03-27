#include <Wt/Chart/WCartesianChart.h>
#include <Wt/WApplication.h>
#include <Wt/WBreak.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WLineEdit.h>
#include <Wt/WPushButton.h>
#include <Wt/WRegExpValidator.h>
#include <Wt/WSlider.h>
#include <Wt/WSpinBox.h>
#include <Wt/WText.h>

#include "paintinginteractivewidget.hh"
#include "paintingwidget.hh"

// #include <string>

class HelloApplication : public Wt::WApplication {
public:
  HelloApplication(const Wt::WEnvironment &env);

private:
  Wt::WLineEdit *nameEdit_;
  Wt::WText *greeting_;
  Wt::Chart::WCartesianChart *chart;
  Wt::Chart::WAbstractChartModel *model;
  Wt::WLineEdit *resistanceEdit_;
  Wt::WLineEdit *voltageEdit_;
  Wt::WLineEdit *currentEdit_;
};

HelloApplication::HelloApplication(const Wt::WEnvironment &env)
    : Wt::WApplication(env) {
  auto path = internalPath();
  path = "/testpath/dir/";
  setTitle("calculus");
  setTitle(path);
  setInternalPath(path);
  root()->addWidget(std::make_unique<Wt::WText>("Your name, please? "));
  nameEdit_ = root()->addWidget(std::make_unique<Wt::WLineEdit>());
  Wt::WPushButton *button =
      root()->addWidget(std::make_unique<Wt::WPushButton>("Greet me."));
  Wt::WPushButton *del_button =
      root()->addWidget(std::make_unique<Wt::WPushButton>("Clear"));
  root()->addWidget(std::make_unique<Wt::WBreak>());
  root()->addWidget(std::make_unique<Wt::WBreak>());
  greeting_ = root()->addWidget(std::make_unique<Wt::WText>());

  auto greet = [this] {
    if (!nameEdit_->text().empty())
      greeting_->setText("Hello there, " + nameEdit_->text());
  };
  button->clicked().connect(greet);
  nameEdit_->enterPressed().connect(greet);

  auto clear_functor = [this] {
    greeting_->setText("");
    nameEdit_->setText("");
  };
  del_button->clicked().connect(clear_functor);

  // chart = root()->addWidget(std::make_unique<Wt::Chart::WCartesianChart>());
  // model = std::make_shared<Wt::Chart::WAbstractChartModel>();
  // chart->setModel(std::make_shared<Wt::Chart::WAbstractChartModel>());

  root()->addWidget(std::make_unique<Wt::WBreak>());
  root()->addWidget(std::make_unique<Wt::WBreak>());

  root()->addWidget(std::make_unique<Wt::WText>("Enter resistance: "));
  resistanceEdit_ = root()->addWidget(std::make_unique<Wt::WLineEdit>());
  root()->addWidget(std::make_unique<Wt::WText>("Enter voltage: "));
  voltageEdit_ = root()->addWidget(std::make_unique<Wt::WLineEdit>());
  auto validator = std::make_shared<Wt::WRegExpValidator>("[0-9]{0,2}");
  validator->setMandatory(true);
  resistanceEdit_->setValidator(validator);
  voltageEdit_->setValidator(validator);

  Wt::WPushButton *calc_button =
      root()->addWidget(std::make_unique<Wt::WPushButton>("calc current"));

  auto calc_current = [this] {
    if (!resistanceEdit_->text().empty() && !voltageEdit_->text().empty()) {
      auto resistance_str(resistanceEdit_->text().toUTF8());
      auto resistance(std::stof(resistance_str));

      auto voltage_str(voltageEdit_->text().toUTF8());
      auto voltage(std::stof(voltage_str));

      auto current{voltage / resistance};
      currentEdit_->setText(std::to_string(current));
    }
  };
  calc_button->clicked().connect(calc_current);

  currentEdit_ = root()->addWidget(std::make_unique<Wt::WLineEdit>());
  currentEdit_->setReadOnly(true);

  root()->addWidget(std::make_unique<Wt::WBreak>());
  root()->addWidget(std::make_unique<Wt::WBreak>());

  auto container_interactive =
      root()->addWidget(std::make_unique<Wt::WContainerWidget>());
  PaintingInteractiveWidget *painting_interactive_widget =
      container_interactive->addNew<PaintingInteractiveWidget>();

  // Wt::WSpinBox* spin_box = container->addNew<Wt::WSpinBox>();
  // spin_box->setWidth(300);
  // spin_box->setRange(0, 360);
  // spin_box->setValue(0);

  Wt::WSlider *slider =
      container_interactive->addNew<Wt::WSlider>(Wt::Orientation::Horizontal);
  slider->resize(300, 50);
  // slider->setNativeControl(true);
  // slider->enableAjax();
  // slider->
  slider->setRange(0, 360);

  slider->sliderMoved().connect(painting_interactive_widget->rotateSlot);

  slider->valueChanged().connect(
      [=] { painting_interactive_widget->rotate(slider->value()); });

  root()->addWidget(std::make_unique<Wt::WBreak>());
  root()->addWidget(std::make_unique<Wt::WBreak>());

  auto container_painting =
      root()->addWidget(std::make_unique<Wt::WContainerWidget>());
  PaintingWidget *painting_widget =
      container_painting->addNew<PaintingWidget>();
}

int main(int argc, char **argv) {
  return Wt::WRun(argc, argv, [](const Wt::WEnvironment &env) {
    return std::make_unique<HelloApplication>(env);
  });
}