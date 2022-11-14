/*
GitHub description

This project demonstrates the following:

- Template classes with parameter packs
- Template specialisation
- SOLID principles (ok, 95% of the time)
- C++ Best Practices (isocpp)
- Multithreading via QT systems
- Custom RAII class
- CTAD
- std::variant


*/

#include "mainwindow.h"

#include <Windows.h>
#include <stdio.h>
#include <iostream>

#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>

using namespace irsf;

int main(int argc, char* argv[]) {
  //----- console--- start|...

  /*
    detach from the current console window
    if launched from a console window, that will still run waiting for the
      new console (below) to close.
    it is useful to detach from Qt Creator's <Application output> panel.
  */
  FreeConsole();

  // create a separate new console window
  AllocConsole();

  // attach the new console to this application's process
  AttachConsole(GetCurrentProcessId());

  // reopen the std I/O streams to redirect I/O to the new console
  freopen("CON", "w", stdout);
  freopen("CON", "w", stderr);
  freopen("CON", "r", stdin);

  QApplication a(argc, argv);

  MainWindow w;
  w.Init();
  w.show();

  std::cout << "IRSF starting..." << std::endl;

  return a.exec();
}
