#include <QGuiApplication>

#include "OpenGLWidget.h"
#include <iostream>

#include <ngl/NGLInit.h>
#include <ngl/ShaderLib.h>
#include <ngl/Random.h>
#include <ngl/VertexArrayObject.h>




//----------------------------------------------------------------------------------------------------------------------
/// @brief the increment for x/y translation with mouse movement
//----------------------------------------------------------------------------------------------------------------------
const static float INCREMENT=0.01;
//----------------------------------------------------------------------------------------------------------------------
/// @brief the increment for the wheel zoom
//----------------------------------------------------------------------------------------------------------------------
const static float ZOOM=0.1;

OpenGLWidget::OpenGLWidget(const QGLFormat _format, QWidget *_parent) : QGLWidget(_format,_parent){
    // set this widget to have the initial keyboard focus
    setFocus();
    setFocusPolicy( Qt::StrongFocus );
    setWindowTitle("Bounded Biharmonic Weights for Real-Time Deformation");
    // re-size the widget to that of the parent (in this case the GLFrame passed in on construction)
    m_rotate=false;
    // mouse rotation values set to 0
    m_spinXFace=0;
    m_spinYFace=0;
    m_modelPos=ngl::Vec3(0.0);
    m_handlesAdded=false;
    // re-size the widget to that of the parent (in this case the GLFrame passed in on construction)
    this->resize(_parent->size());
}
//----------------------------------------------------------------------------------------------------------------------
OpenGLWidget::~OpenGLWidget(){
    ngl::NGLInit *Init = ngl::NGLInit::instance();
    std::cout<<"Shutting down NGL, removing VAO's and Shaders\n";
    Init->NGLQuit();
}
//----------------------------------------------------------------------------------------------------------------------
void OpenGLWidget::initializeGL(){

    // we must call this first before any other GL commands to load and link the
    // gl commands from the lib, if this is not done program will crash
    ngl::NGLInit::instance();


    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    // enable depth testing for drawing
    glEnable(GL_DEPTH_TEST);
    // enable multisampling for smoother drawing
    //glEnable(GL_MULTISAMPLE);

    // as re-size is not explicitly called we need to do this.
    glViewport(0,0,width(),height());

    // Initialise the model matrix
    m_modelMatrix = ngl::Mat4(1.0);
    ngl::ShaderLib *shader=ngl::ShaderLib::instance();
    //first lets add out deformation shader to our program
    //create the program
    shader->createShaderProgram("DeformationShader");
    //add our shaders
    shader->attachShader("DeformationVert",ngl::VERTEX);
    shader->attachShader("DeformationFrag",ngl::FRAGMENT);
    //load the source
    shader->loadShaderSource("DeformationVert","shaders/DeformationVert.glsl");
    shader->loadShaderSource("DeformationFrag","shaders/DeformationFrag.glsl");
    //compile them
    shader->compileShader("DeformationVert");
    shader->compileShader("DeformationFrag");
    //attach them to our program
    shader->attachShaderToProgram("DeformationShader","DeformationVert");
    shader->attachShaderToProgram("DeformationShader","DeformationFrag");
    //link our shader to opengl
    shader->linkProgramObject("DeformationShader");
    //set our shader uniforms
    (*shader)["DeformationShader"]->use();
    shader->setShaderParam3f("light.position",-1,-1,-1);
    shader->setShaderParam3f("light.intensity",0.8,0.8,0.8);
    shader->setShaderParam3f("Kd",0.5, 0.5, 0.5);
    shader->setShaderParam3f("Ka",0.5, 0.5, 0.5);
    shader->setShaderParam3f("Ks",1.0,1.0,1.0);
    shader->setShaderParam1f("shininess",100.0);

    (*shader)["nglDiffuseShader"]->use();
    shader->setShaderParam4f("Colour",1,1,1,1);

    (*shader)["nglDiffuseShader"]->use();
    shader->setShaderParam4f("Colour",1,1,0,1);
    shader->setShaderParam3f("lightPos",1,1,1);
    shader->setShaderParam4f("lightDiffuse",1,1,1,1);

    //create our sphere primative VAO
    ngl::VAOPrimitives *prim=ngl::VAOPrimitives::instance();
    prim->createSphere("sphere",0.1,5);



    // Initialize the camera
    // Now we will create a basic Camera from the graphics library
    // This is a static camera so it only needs to be set once
    // First create Values for the camera position
    ngl::Vec3 from(0,0,25);
    ngl::Vec3 to(0,0,0);
    ngl::Vec3 up(0,1,0);
    m_cam= new ngl::Camera(from,to,up);
    // set the shape using FOV 45 Aspect Ratio based on Width and Height
    // The final two are near and far clipping planes of 0.5 and 10
    m_cam->setShape(45,(float)width()/height(),0.5,150);

    //create some spheres for testing
//    ngl::Random *rng=ngl::Random::instance();
//    rng->setSeed();
//    for(int i=0; i<20; i++){
//        selectable *sel = new selectable(rng->getRandomVec3()*3);
//        m_selectables.push_back(sel);
//    }


    //lets import our mesh
    m_importedMesh = new ImportMesh("models/pikatchu.obj");
    m_LMESolver = new LMESolver(m_importedMesh->getMeshPtr());
    //lets make a circle
    for(unsigned int i=0; i<m_importedMesh->m_vertPositions.size(); i++){
        selectable *sel = new selectable(m_importedMesh->m_vertPositions[i],i,0.2);
        sel->isMovable(false);
        m_selectables.push_back(sel);
    }

    // create our text renderer
    m_text = new ngl::Text(QFont("Arial",14));
    m_text->setColour(255,0,0);
    m_text->setScreenSize(width(),height());

    startTimer(0);

}
//----------------------------------------------------------------------------------------------------------------------
void OpenGLWidget::resizeGL(const int _w, const int _h){
    // set the viewport for openGL
    glViewport(0,0,_w,_h);
    m_cam->setShape(45,(float)_w/_h, 0.5,150);

}
//----------------------------------------------------------------------------------------------------------------------
void OpenGLWidget::timerEvent(QTimerEvent *){
    m_importedMesh->update();
    updateGL();
}

//----------------------------------------------------------------------------------------------------------------------
void OpenGLWidget::paintGL(){

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //Initialise the model matrix

    ngl::Mat4 rotX;
    ngl::Mat4 rotY;

    // create the rotation matrices
    rotX.rotateX(m_spinXFace);
    rotY.rotateY(m_spinYFace);
    // multiply the rotations
    m_mouseGlobalTX=rotY*rotX;
    // add the translations
    m_mouseGlobalTX.m_m[3][0] = m_modelPos.m_x;
    m_mouseGlobalTX.m_m[3][1] = m_modelPos.m_y;
    m_mouseGlobalTX.m_m[3][2] = m_modelPos.m_z;

    m_importedMesh->draw(m_mouseGlobalTX,m_cam);
    //m_modelMatrix = m_mouseGlobalTX;
    for(unsigned int i=0; i<m_selectables.size(); i++){
        m_selectables[i]->draw(m_mouseGlobalTX,m_cam);
    }
    if(!m_handlesAdded){
        m_text->renderText(5,5,QString("Please selected your handles and click enter to add them :)"));
    }
    else{
        m_text->setColour(0.0,255,0.0);
        m_text->renderText(5,5,QString("All's good! feel free to select your handles and move them :)"));
    }
}
//----------------------------------------------------------------------------------------------------------------------
void OpenGLWidget::keyPressEvent(QKeyEvent *_event){
    if(_event->key()==Qt::Key_Return && !m_handlesAdded){
        //only add our handles if something has been selected
        if(m_selected.size()>0){
            std::cout<<"adding handles"<<std::endl;
            m_handlesAdded = true;
            std::vector<ngl::Vec3> points;
            unsigned int i;
            //get all our postions of our verts
            for(i=0;i<m_selectables.size();i++){
                points.push_back(m_selectables[i]->getPos());
                //remove interactive movement to everything that isnt a handle
                m_selectables[i]->isSelectable(false);
            }

            m_LMESolver = new LMESolver(points);
            for(i=0; i<m_selected.size();i++){
                m_LMESolver->addHandle(m_selected[i]->getID(),1.0);
                m_selected[i]->isSelectable(true);
                m_selected[i]->setSelected(false);
                m_selected[i]->isHandle(true);
            }
            m_selected.clear();
        }
    }
}

//----------------------------------------------------------------------------------------------------------------------
void OpenGLWidget::mouseMoveEvent (QMouseEvent * _event)
{
  // note the method buttons() is the button state when event was called
  // this is different from button() which is used to check which button was
  // pressed when the mousePress/Release event is generated
  if(m_movePoint && _event->buttons() == Qt::LeftButton)
  {
    int diffx=_event->x()-m_origX;
    int diffy=_event->y()-m_origY;
    ngl::Vec3 diff(diffx,diffy * -1.0,0.0);
    diff.normalize();
    diff*=0.1;
    if(m_selected.size()>0){
        if(m_handlesAdded){
            ngl::Vec3 newPos;
            for(unsigned int i=0;i<m_selected.size();i++){
                newPos = m_selected[i]->getPos()+diff;
                m_LMESolver->moveHandle(m_selected[i]->getID(),newPos);
            }
            std::vector<ngl::Vec3> newVerts = m_LMESolver->calculatePoints();
            for(unsigned int i=0;i<m_selectables.size();i++){
                m_selectables[i]->setPos(newVerts[i]);
            }
        }
        else{
            for(unsigned int i=0;i<m_selected.size();i++){
                m_selected[i]->move(diff);
            }
        }
        m_origX = _event->x();
        m_origY = _event->y();
    }
  }
  else if(m_rotate && _event->buttons() == Qt::MiddleButton){
      int diffx=_event->x()-m_origX;
      int diffy=_event->y()-m_origY;
      m_spinXFace += (float) 0.5f * diffy;
      m_spinYFace += (float) 0.5f * diffx;
      m_origX = _event->x();
      m_origY = _event->y();
  }
   // right mouse translate code
  else if(m_translate && _event->buttons() == Qt::RightButton)
  {
    int diffX = (int)(_event->x() - m_origXPos);
    int diffY = (int)(_event->y() - m_origYPos);
    m_origXPos=_event->x();
    m_origYPos=_event->y();
    m_modelPos.m_x += INCREMENT * diffX;
    m_modelPos.m_y -= INCREMENT * diffY;

   }
}
//----------------------------------------------------------------------------------------------------------------------
void OpenGLWidget::mousePressEvent ( QMouseEvent * _event)
{
  // this method is called when the mouse button is pressed in this case we
  // store the value where the maouse was clicked (x,y) and set the Rotate flag to true
  if(_event->button() == Qt::MiddleButton)
  {
    m_origX = _event->x();
    m_origY = _event->y();
    m_rotate =true;
  }
  else if(_event->button() == Qt::LeftButton){
      m_origX = _event->x();
      m_origY = _event->y();
      m_movePoint = true;
  }
  // right mouse translate mode
  else if(_event->button() == Qt::RightButton)
  {
    m_origXPos = _event->x();
    m_origYPos = _event->y();
    m_translate=true;
  }

  m_selected.clear();
  for(unsigned int i=0; i<m_selectables.size();i++){
      m_selectables[i]->testSelection(width(),height(),_event->x(),_event->y(),m_mouseGlobalTX, m_cam);
      if(m_selectables[i]->isSelected())
          m_selected.push_back(m_selectables[i]);
  }


}
//----------------------------------------------------------------------------------------------------------------------
void OpenGLWidget::mouseReleaseEvent ( QMouseEvent * _event )
{
  // this event is called when the mouse button is released
  // we then set Rotate to false
  if (_event->button() == Qt::MiddleButton)
  {
    m_rotate=false;
  }
  if(_event->button() == Qt::LeftButton){
      m_movePoint = false;
  }
        // right mouse translate mode
  if (_event->button() == Qt::RightButton)
  {
    m_translate=false;
  }
}
//----------------------------------------------------------------------------------------------------------------------
void OpenGLWidget::wheelEvent(QWheelEvent *_event)
{

    // check the diff of the wheel position (0 means no change)
    if(!m_rotate)
    if(_event->delta() > 0)
    {
        m_modelPos.m_z+=ZOOM;
    }
    else if(_event->delta() <0 )
    {
        m_modelPos.m_z-=ZOOM;
    }
    updateGL();
}
//-----------------------------------------------------------------------------------------------------------------------

