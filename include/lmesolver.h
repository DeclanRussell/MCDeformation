#ifndef LMESOLVER_H
#define LMESOLVER_H

#include <eigen3/Eigen/Sparse>
#include <ngl/Vec3.h>

class LMESolver
{
public:
    /// @brief contructor to load in our vertex's and will create our laplace and delta matricies
    /// @param _points - an array of our vertex's
    //----------------------------------------------------------------------------------------------------------------------
    LMESolver(std::vector<ngl::Vec3> _points);
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief adds handles to our matricies for deformation
    /// @param _vertex - which vertex in our array points we wish to add a handle to (not idea managment but ok for this demo)
    /// @param _weight - the weight of influence you wish to add to this vertex
    //----------------------------------------------------------------------------------------------------------------------
    void addHandle(int _vertex, float _weight);
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief our function to calculate our new points from our matricies
    //----------------------------------------------------------------------------------------------------------------------
    std::vector<ngl::Vec3> calculatePoints();
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief a function to move our handles
    //----------------------------------------------------------------------------------------------------------------------
    void moveHandle(int _handleId, ngl::Vec3 _pos);
    //----------------------------------------------------------------------------------------------------------------------
protected:
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief defualt contructor, wont have very much functionality generally just allocates space for our matricies
    /// @brief for time being best to just leave protected, Hands off!
    //----------------------------------------------------------------------------------------------------------------------
    LMESolver();
    //----------------------------------------------------------------------------------------------------------------------
private:
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief a funciton to calculate our laplace matrix and delta matrix
    /// @brief in very early stages, only does basic 2D geomtry at the moment
    //----------------------------------------------------------------------------------------------------------------------
    void createMatricies(std::vector<ngl::Vec3> _points);
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief a sparse matrix to hold our calculated laplace matrix
    //----------------------------------------------------------------------------------------------------------------------
    Eigen::SparseMatrix<double> m_laplaceMatrix;
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief a sparse matrix to hold our calculated vertex deltas
    //----------------------------------------------------------------------------------------------------------------------
    Eigen::SparseMatrix<double> m_delta;
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief our original verticies, used for when we add handles
    //----------------------------------------------------------------------------------------------------------------------
    std::vector<ngl::Vec3> m_OGVertex;
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief a vector to store the vertex Id's of our handles
    //----------------------------------------------------------------------------------------------------------------------
    std::vector<int> m_handleID;
    //----------------------------------------------------------------------------------------------------------------------

};

#endif // LMESolver_H
