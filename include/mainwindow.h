#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QGroupBox>
#include <QGridLayout>
#include <QSpacerItem>
#include "OpenGLWidget.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    OpenGLWidget *m_openGLWidget;
    QPushButton *m_addAnchorBtn;
    QPushButton *m_setAnchorBtn;
    QPushButton *m_addHandleBtn;
    QPushButton *m_setHandleBtn;
    QGroupBox *m_controlsGroupBox;
    QGridLayout *m_controlGridLayout;
    QSpacerItem *m_controlSpacer;





};

#endif // MAINWINDOW_H
