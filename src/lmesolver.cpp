#include "lmesolver.h"

LMESolver::LMESolver()
{
    m_laplaceMatrix = new Eigen::SparseMatrix<double>;
    m_delta = new Eigen::SparseMatrix<double>;
}
//----------------------------------------------------------------------------------------------------------------------
LMESolver::LMESolver(std::vector<ngl::Vec3> _points){
    m_OGVertex = _points;
    m_laplaceMatrix = new Eigen::SparseMatrix<double>(_points.size(),_points.size());
    m_delta = new Eigen::SparseMatrix<double>(_points.size(),3);
    createMatricies(_points);
}
//----------------------------------------------------------------------------------------------------------------------
void LMESolver::createMatricies(std::vector<ngl::Vec3> _points){
    ngl::Vec3 current,prev,next,delta;
    int prevLoc, nextLoc;
    for(unsigned int i=0; i<_points.size();i++){
        //do some bourndary checks
        if(i==0)
            prevLoc = _points.size()-1;
        if(i==(_points.size()-1))
            nextLoc = 0;

        current = _points[i];
        prev = _points[prevLoc];
        next = _points[nextLoc];

        delta = current - 0.5*(prev+next);

        m_delta->coeffRef(i,0) = delta.m_x;
        m_delta->coeffRef(i,1) = delta.m_y;
        m_delta->coeffRef(i,2) = delta.m_z;

        //some lame hard coded mathematics!
        //to be improoved at a later date
        m_laplaceMatrix->coeffRef(i,i) = 1.0;
        m_laplaceMatrix->coeffRef(i,prevLoc) = -0.5;
        m_laplaceMatrix->coeffRef(i,nextLoc) = -0.5;
    }
}
//----------------------------------------------------------------------------------------------------------------------
void LMESolver::addHandle(int _vertex, float _weight){
    //add the handle to our laplace matrix
    m_laplaceMatrix->resize(m_laplaceMatrix->rows()+1,m_laplaceMatrix->cols());
    m_laplaceMatrix->coeffRef(m_laplaceMatrix->rows()-1,_vertex) = _weight;

    //add the handle to our delta matrix
    m_delta->resize(m_delta->rows()+1,m_delta->cols());
    m_delta->coeffRef(m_delta->rows()-1,0) = m_OGVertex[_vertex].m_x;
    m_delta->coeffRef(m_delta->rows()-1,1) = m_OGVertex[_vertex].m_y;
    m_delta->coeffRef(m_delta->rows()-1,2) = m_OGVertex[_vertex].m_z;
}

//----------------------------------------------------------------------------------------------------------------------
std::vector<ngl::Vec3> LMESolver::calculatePoints(){
    Eigen::MatrixXf A, At, b, final;

    m_laplaceMatrix;
    At = m_laplaceMatrix;
    At.transpose();
    b = m_delta;

    final = (At * A


}

//----------------------------------------------------------------------------------------------------------------------
