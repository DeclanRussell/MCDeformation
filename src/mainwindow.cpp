#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);

    QGLFormat format;
    format.setVersion(4,1);
    format.setProfile(QGLFormat::CoreProfile);

    //add our openGL context to our scene
    m_openGLWidget = new OpenGLWidget(format,this);
    ui->gridLayout->addWidget(m_openGLWidget,0,0,1,3);

    //add our grid layout
    m_controlGridLayout = new QGridLayout();
    //add our properties group box and set the layout
    m_controlsGroupBox = new QGroupBox("Controls",this);
    m_controlsGroupBox->setLayout(m_controlGridLayout);

    //add it to our form
    ui->gridLayout->addWidget(m_controlsGroupBox,0,3,1,1);

    //add our buttons to our widget
    m_addAnchorBtn = new QPushButton("Add Anchors",this);
    m_controlGridLayout->addWidget(m_addAnchorBtn,0,0,1,1);
    m_setAnchorBtn = new QPushButton("Set Anchors",this);
    m_controlGridLayout->addWidget(m_setAnchorBtn,1,0,1,1);
    m_addHandleBtn = new QPushButton("Add Handle",this);
    m_controlGridLayout->addWidget(m_addHandleBtn,2,0,1,1);
    m_setHandleBtn = new QPushButton("Set Handle",this);
    m_controlGridLayout->addWidget(m_setHandleBtn,3,0,1,1);

    m_controlSpacer = new QSpacerItem(1, 1, QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    m_controlGridLayout->addItem(m_controlSpacer,4,0,1,1);
    //connect our buttons up with our scene slots
    connect(m_addAnchorBtn,SIGNAL(clicked()),m_openGLWidget,SLOT(addAnchors()));
    connect(m_setAnchorBtn,SIGNAL(clicked()),m_openGLWidget,SLOT(setAnchors()));
    connect(m_addHandleBtn,SIGNAL(clicked()),m_openGLWidget,SLOT(addHandle()));
    connect(m_setHandleBtn,SIGNAL(clicked()),m_openGLWidget,SLOT(setHandle()));

}

MainWindow::~MainWindow(){
    delete ui;
    delete m_openGLWidget;
    delete m_addAnchorBtn;
    delete m_setAnchorBtn;
    delete m_addHandleBtn;
    delete m_setHandleBtn;
    delete m_controlsGroupBox;
    delete m_controlGridLayout;
    delete m_controlSpacer;

}
