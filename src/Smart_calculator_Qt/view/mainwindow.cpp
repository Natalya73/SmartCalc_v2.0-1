/// \file
#include "mainwindow.h"

QString string_to_solve;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  connect(ui->Button0, SIGNAL(released()), this, SLOT(NumPressed()));
  connect(ui->Button1, SIGNAL(released()), this, SLOT(NumPressed()));
  connect(ui->Button2, SIGNAL(released()), this, SLOT(NumPressed()));
  connect(ui->Button3, SIGNAL(released()), this, SLOT(NumPressed()));
  connect(ui->Button4, SIGNAL(released()), this, SLOT(NumPressed()));
  connect(ui->Button5, SIGNAL(released()), this, SLOT(NumPressed()));
  connect(ui->Button6, SIGNAL(released()), this, SLOT(NumPressed()));
  connect(ui->Button7, SIGNAL(released()), this, SLOT(NumPressed()));
  connect(ui->Button8, SIGNAL(released()), this, SLOT(NumPressed()));
  connect(ui->Button9, SIGNAL(released()), this, SLOT(NumPressed()));
  // operators
  connect(ui->ButtonAdd, SIGNAL(released()), this, SLOT(NumPressed()));
  connect(ui->Multiply, SIGNAL(released()), this, SLOT(NumPressed()));
  connect(ui->Divide, SIGNAL(released()), this, SLOT(NumPressed()));
  connect(ui->Subtract, SIGNAL(released()), this, SLOT(NumPressed()));
  // functions
  connect(ui->ButtonACOS, SIGNAL(released()), this, SLOT(NumPressed()));
  connect(ui->ButtonATAN, SIGNAL(released()), this, SLOT(NumPressed()));
  connect(ui->ButtonAsin, SIGNAL(released()), this, SLOT(NumPressed()));
  connect(ui->ButtonDot, SIGNAL(released()), this, SLOT(NumPressed()));
  connect(ui->CloseBracket, SIGNAL(released()), this, SLOT(NumPressed()));
  connect(ui->OpenBracket, SIGNAL(released()), this, SLOT(NumPressed()));
  connect(ui->Ln, SIGNAL(released()), this, SLOT(NumPressed()));
  connect(ui->Logarithm, SIGNAL(released()), this, SLOT(NumPressed()));
  connect(ui->Modulo, SIGNAL(released()), this, SLOT(NumPressed()));
  connect(ui->Power, SIGNAL(released()), this, SLOT(NumPressed()));
  connect(ui->Sinus, SIGNAL(released()), this,
          SLOT(NumPressed()));  // numPressed+(
  connect(ui->Cosinus, SIGNAL(released()), this, SLOT(NumPressed()));
  connect(ui->SquareRoot, SIGNAL(released()), this, SLOT(NumPressed()));
  connect(ui->X_button, SIGNAL(released()), this, SLOT(NumPressed()));
  connect(ui->Tangence, SIGNAL(released()), this, SLOT(NumPressed()));
  connect(ui->Equals, SIGNAL(released()), this, SLOT(EqualButton()));
  connect(ui->ChangeSign, SIGNAL(released()), this, SLOT(ChangeNumberSign()));
  connect(ui->Clear, SIGNAL(released()), this, SLOT(Clear()));
  //    connect(ui->ValueX, SIGNAL(textChanged()), this, SLOT(on_ValueX
  connect(ui->BackSpace, SIGNAL(released()), this, SLOT(BackSpace()));
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::BackSpace() {
  //    QByteArray ba = string_to_solve.toLocal8Bit();
  //    char* string_from_display = ba.data();
  if (!ui->Display->text().isEmpty()) {
    ui->Display->setText(ui->Display->text().chopped(1));
  }
}
void MainWindow::NumPressed() {
  QPushButton *button = (QPushButton *)
      sender();  // sender will return the pointer to the button pressed
  QString butVal = button->text();  // we get the text off of the QButton
  QString displayVal = ui->Display->text();  // get the value in the display
  QString X_ValueX_2 = ui->ValueX_2->text();
//  QString Sinus_button = ui->Sinus->text();
  if (displayVal == '0') {
    ui->Display->setText(butVal);
    string_to_solve = butVal + displayVal;
  } else if (displayVal == 'x') {
    ui->Display->setText(X_ValueX_2);
    string_to_solve = displayVal + butVal;
    ui->Display->setText(string_to_solve);
  } else if (butVal == "sin" || butVal == "cos" || butVal == "tan" ||
             butVal == "asin" || butVal == "acos" || butVal == "atan" ||
             butVal == "sqrt" || butVal == "ln" || butVal == "log") {
    string_to_solve = displayVal + butVal + "(";
    ui->Display->setText(string_to_solve);
  } else {
    string_to_solve = displayVal + butVal;  // + "("
    ui->Display->setText(string_to_solve);
  }
}

void MainWindow::EqualButton() {
  QByteArray ba = string_to_solve.toLocal8Bit();
  char *string_from_display = ba.data();
  QString X_ValueX_2 = ui->ValueX_2->text();
  double xxx = X_ValueX_2.toDouble();
  s21::Controller controller;
  if (controller.C_validated(string_from_display) == 0) {
    ui->Result->clear();
    ui->Result->setText("Please check your input");
  } else {
    double res = controller.C_string_calc(string_from_display, xxx);
    QString solution = QString::number(res, 'g', 15);
    ui->Result->setText(solution);
  }
}

void MainWindow::ChangeNumberSign() {
  QString displayVal = ui->Display->text();
  QRegularExpression reg("[-]?[0-9.]*");
  //    static const QString match = reg.match(displayVal);
  static const QRegularExpressionMatch match = reg.match(displayVal);
  if (match.hasMatch()) {
    double dblDisplayVal = displayVal.toDouble();
    double dblDisplayValSign = -1 * dblDisplayVal;
    ui->Display->setText(QString::number(dblDisplayValSign));
  }
}

void MainWindow::Clear() {
  ui->Display->clear();
  ui->Result->clear();
  ui->FieldForGraph->clearGraphs();
  ui->FieldForGraph->replot();
}

void MainWindow::on_Graph_clicked() {
  ui->FieldForGraph->replot();
  double X_MIN_value = ui->X_MIN->text().toDouble();
  double Y_MAX_value = ui->Y_MAX->text().toDouble();
  double Y_MIN_value = ui->Y_MIN->text().toDouble();
  double step_2 = ui->Step_2->text().toDouble();
  double X_MAX_value = ui->X_MAX->text().toDouble() + step_2;
  QVector<double> x, y;
  s21::Controller controller;
  int N =
      (X_MAX_value - X_MIN_value) / step_2 + 2;  // don't know where to use it
  double X;
  int i = 0;
  QByteArray ba = string_to_solve.toLocal8Bit();
  char *string_from_display = ba.data();
  //run through all the dots
  ui->FieldForGraph->clearGraphs();
  for (double X = X_MIN_value; X <= X_MAX_value; X += step_2) {
    x.push_back(X);
    double res = 0;
    res = controller.C_string_calc(string_from_display, X);
    y.push_back(res);
    i++;
  }
  ui->FieldForGraph->clearGraphs();
  ui->FieldForGraph->addGraph();
  ui->FieldForGraph->xAxis->setLabel("x");
  ui->FieldForGraph->yAxis->setLabelColor(Qt::green);
  ui->FieldForGraph->yAxis->setLabel("y");
  ui->FieldForGraph->xAxis->setLabelColor(Qt::red);
  ui->FieldForGraph->xAxis->setRange(X_MIN_value, X_MAX_value);
  ui->FieldForGraph->yAxis->setRange(Y_MIN_value, Y_MAX_value);

  ui->FieldForGraph->graph(0)->setLineStyle(QCPGraph::lsLine);
//  ui->FieldForGraph->graph(0)->setLineStyle(QCPGraph::lsNone);
  ui->FieldForGraph->graph(0)->setScatterStyle(
      QCPScatterStyle(QCPScatterStyle::ssDisc, 3));

  ui->FieldForGraph->graph(0)->setData(x, y);
  ui->FieldForGraph->graph(0)->rescaleAxes();
  ui->FieldForGraph->replot();
  ui->FieldForGraph->clearGraphs();
}

// it is static created
void MainWindow::on_Credit_clicked() {
  //    form_credit_calc window;
  //    window.setModal(true);
  //    window->exec();
  form_credit_calc.show();
}

void MainWindow::on_pushButton_3_clicked() { Form_deposit_calc.show(); }
