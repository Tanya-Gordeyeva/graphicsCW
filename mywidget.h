#ifndef MYWIDGET_H
#define MYWIDGET_H


#include <QMainWindow>
#include <QObject>
#include <QGLWidget>
#include <math.h>
#include <QMouseEvent>
#include <QOpenGLShaderProgram>
#include <QOpenGLFunctions>
#include <QMatrix4x4>
#include <QtGui>

class MyWidget: public QGLWidget, public QOpenGLFunctions
{
    Q_OBJECT
public:
    MyWidget(QWidget *parent = 0);
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);
    void initShaders();
    void draw();
    void NormalizePlane(float frustum[6][4], int side);


private:
    float R;
    int prev[3]={0,0,0};
    float x_light;
    float y_light;
    float z_light;
    float color=0;
    bool light=false;
    QMatrix4x4 matrix;
    GLuint m_posAtr;
    GLuint m_colAtr;
    GLuint m_sizeAtr;
    GLuint m_matrix;
    GLuint m_R;
    GLuint m_posAtrCol;
    QOpenGLShaderProgram *m_program;
    float size;


public slots:
    void rotateX (int);
    void rotateY(int);
    void rotateZ(int);
    void changeR(int);
    void changeX_light(int);
    void changeY_light(int);
    void changeZ_light(int);
    void changeColor(int);

};

#endif // MYWIDGET_H
