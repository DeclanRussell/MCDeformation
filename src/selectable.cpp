#include "include/selectable.h"
#include <ngl/VAOPrimitives.h>
#include <ngl/ShaderLib.h>
#include <ngl/Transformation.h>

//----------------------------------------------------------------------------------------------------------------------
selectable::selectable()
{
    m_pos = ngl::Vec3(0.0);
    m_radius = 0.5;
    m_seleted = false;
    m_isMovable = true;
}
//----------------------------------------------------------------------------------------------------------------------
selectable::selectable(ngl::Vec3 _pos, int _vertexID){
    m_pos = _pos;
    m_radius = 0.5;
    m_seleted = false;
    m_vertexID = _vertexID;
    m_isSelectable = true;
    m_isHandle = false;
    m_isMovable = true;
}
//----------------------------------------------------------------------------------------------------------------------
selectable::selectable(ngl::Vec3 _pos, int _vertexID, float _radius){
    m_pos = _pos;
    m_radius = _radius;
    m_seleted = false;
    m_vertexID = _vertexID;
    m_isSelectable = true;
    m_isHandle = false;
    m_isMovable = true;
}

//----------------------------------------------------------------------------------------------------------------------
void selectable::testSelection(int _width, int _height,int _mouseX, int _mouseY, ngl::Mat4 _mouseGlobalTX, ngl::Camera *_cam){
    // if this is not a selectable device then do nothing
    if(!m_isSelectable)
        return;
    //calculate our normal device coords
    float x = ((2.0f * _mouseX) / _width) - 1.0f;
    float y = 1.0f -  ((2.0f * _mouseY) / _height);
    float z = 1.0f;
    ngl::Vec3 ray_nds(x, y, z);

    //calculate our homogenous coords
    ngl::Vec4 ray_clip(ray_nds.m_x,ray_nds.m_y, 1.0, 1.0);

    //transform from clip space to eye space
    ngl::Mat4 P =_cam->getProjectionMatrix();
    ngl::Vec4 ray_eye = P.inverse() * ray_clip;

    //unproject the x y part
    ray_eye = ngl::Vec4(ray_eye.m_x,ray_eye.m_y, -1.0, 0.0);

    //transform to our world coordinates
    ngl::Mat4 V = _cam->getViewMatrix();
    ngl::Vec4 temp(V.inverse() * ray_eye);
    ngl::Vec3 ray_wor(temp.m_x,temp.m_y,temp.m_z);
    // don't forget to normalise the vector at some point
    ray_wor.normalize();

    //now to calculate if we intersect with out sphere
    ngl::Vec4 pos4(m_pos);
    pos4.m_w = 1.0;
    ngl::Mat4 modelTrans = _mouseGlobalTX.inverse();
    ngl::Vec4 posTX = modelTrans * pos4;
    ngl::Vec3 posTX3(posTX.m_x,posTX.m_y,posTX.m_z);
    ngl::Vec3 camPos(_cam->getEye().m_x,_cam->getEye().m_y,_cam->getEye().m_z);
    float b = ray_wor.dot(posTX3 - camPos);
    float c = (posTX3 - camPos).dot(posTX3 - camPos) - (m_radius*m_radius);

    if(((b*b)-c)>0.0){
        m_seleted ? m_seleted=false : m_seleted=true;
    }
}

//----------------------------------------------------------------------------------------------------------------------
void selectable::draw(ngl::Mat4 _mouseGlobalTX, ngl::Camera *_cam){
    //make our shader active
    ngl::ShaderLib *shader=ngl::ShaderLib::instance();
    (*shader)["nglDiffuseShader"]->use();

    loadMatricesToShader(_mouseGlobalTX,_cam);

    //grab our VAO
    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
    ngl::VAOPrimitives *prim=ngl::VAOPrimitives::instance();
    prim->draw("sphere");


}
//----------------------------------------------------------------------------------------------------------------------
void selectable::loadMatricesToShader(ngl::Mat4 _mouseGlobalTX, ngl::Camera *_cam){

    ngl::Transformation trans;
    trans.setPosition(m_pos);

    // Calculate MVP matricies
    ngl::Mat4 P = _cam->getProjectionMatrix();
    ngl::Mat4 MV = trans.getMatrix() * _mouseGlobalTX * _cam->getViewMatrix();


    ngl::Mat3 normalMatrix = ngl::Mat3(MV);
    normalMatrix.inverse();
    normalMatrix.transpose();

    ngl::Mat4 MVP = MV * P;

    //set our uniforms
    ngl::ShaderLib *shader=ngl::ShaderLib::instance();
    (*shader)["nglDiffuseShader"]->use();
    shader->setShaderParamFromMat4("MVP",MVP);
    shader->setShaderParamFromMat3("normalMatrix",normalMatrix);
    if(m_seleted){
        //if selected draw it red
        shader->setShaderParam4f("Colour",1,0,0,1);
    }
    else{
        // if its a handle set it cyan otherwise green
        m_isHandle ? shader->setShaderParam4f("Colour",0,1,1,1) : shader->setShaderParam4f("Colour",0,1,0,1);
    }
}
//----------------------------------------------------------------------------------------------------------------------





