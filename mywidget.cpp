#include "mywidget.h"
#include <GL/gl.h>
#include <GL/glu.h>

MyWidget::MyWidget(QWidget *parent):
    QGLWidget(parent)
{
    setGeometry(50,50,500,500);
    R=0.9f;
    size=M_PI/18.0;

}

void MyWidget::initializeGL(){
    initializeOpenGLFunctions();
    glClearColor(0.1, 0.1, 0.2, 1);
    glViewport(0,0,500,500);
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    glMatrixMode( GL_MODELVIEW );
    initShaders();
}

void MyWidget::paintGL(){
    glClear(GL_COLOR_BUFFER_BIT);
    if ( !m_program->bind() )
        return;
    draw();
}



void MyWidget::resizeGL(int width, int height){

}

void MyWidget::draw(){

    m_program->setUniformValue(m_matrix, matrix ); //устанавливаем значения матрицы

    m_program->setUniformValue(m_colAtr, 1.0f,1.0f,1.0f,1.0f); //устанавливаем цвет

    //отрисовка координатных осей
//    GLfloat coord[]={
//         1.0f,0.0f,0.0f,
//         -1.0f,0.0f,0.0f,
//         0.0f,1.0f,0.0f,
//         0.0f,-1.0f,0.0f,
//         0.0f,0.0f,1.0f,
//         0.0f,0.0f,-1.0f,

//    };
//    glVertexAttribPointer( m_posAtr, 3, GL_FLOAT, GL_FALSE, 0, coord);
//    glEnableVertexAttribArray( m_posAtr );
//    glDrawArrays( GL_LINES, 0, 6);
//    glDisableVertexAttribArray(  m_posAtr );

    //отрисовка фигуры
    GLfloat vec[12];
    float k = 0.2*R*sin(-size/20.0);
    double y = 0;




    m_program->setUniformValue(m_R, k);
    for (double j = -3*M_PI/2.0; j<=M_PI/2.0+size; j += size/2.0){
            for (double t =size/18.0; t <= 2*M_PI; t += size){

                vec[0]=k;
                vec[1]=(0.2*R*cos(j)+R/2.0)*cos(t);
                vec[2]=(0.2*R*cos(j)+R/2.0)*sin(t);
                vec[3]=k;
                vec[4]=(0.2*R*cos(j)+R/2.0)*cos(t-size);
                vec[5]=(0.2*R*cos(j)+R/2.0)*sin(t-size);
                vec[6]=y;
                vec[7]=(0.2*R*cos(j-size/2.0)+R/2.0)*cos(t-size);
                vec[8]=(0.2*R*cos(j-size/2.0)+R/2.0)*sin(t-size);
                vec[9]=y;
                vec[10]=(0.2*R*cos(j-size/2.0)+R/2.0)*cos(t);
                vec[11]=(0.2*R*cos(j-size/2.0)+R/2.0)*sin(t);
                glVertexAttribPointer( m_posAtr, 3, GL_FLOAT, GL_FALSE, 0,vec);
                glEnableVertexAttribArray( m_posAtr );
                glEnable(GL_CULL_FACE);
                glCullFace(GL_FRONT);
                glDrawArrays( GL_POLYGON, 0, 4);
                glDisable(GL_CULL_FACE);

                glDisableVertexAttribArray( m_posAtr);

        }



            m_program->setUniformValue(m_colAtr,0.5*(sin(j+M_PI/2.0)+0.3),0.5*abs(sin(j)),-0.5*sin(j+M_PI/2.0),1.0);
            y=k;
            k=0.2*R*sin(j);
            if(j>-M_PI && j<-M_PI+size/2.0 || j>-M_PI/2.0 && j<-M_PI/2.0+size/2.0
                   || j>0 && j<size/2.0)
            qDebug()<<cos(j)/0.2*R*(0.2*R*cos(j)+R/2.0);


    }

    m_program->release();

}







//инициализация шейдеров
void MyWidget::initShaders() {
    const GLubyte *extensions;
    extensions = glGetString(GL_EXTENSIONS);
    int i = 0;
    QString extensionsString;
    while (extensions[i] != 0) {
        extensionsString += extensions[i];
        i++;
    }
    if (!extensionsString.contains("GL_ARB_vertex_shader") ||
            !extensionsString.contains("GL_ARB_fragment_shader") ||
            !extensionsString.contains("GL_ARB_shader_objects") ||
            !extensionsString.contains("GL_ARB_shading_language_100"))
    {
        exit(0);
    }

    //compile shaders
    m_program = new QOpenGLShaderProgram( this );
    m_program->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/vertex_shader.glsl");
    m_program->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/fragment_shader.glsl");
    if ( !m_program->link() )
    {
        qWarning( "Error: unable to link a shader program" );
        return;
    }
    m_posAtr = m_program->attributeLocation( "posAtr" );
    m_posAtrCol = m_program->attributeLocation( "posAtrCol" );
    m_colAtr = m_program->uniformLocation( "colAtr" );
    m_sizeAtr = m_program->uniformLocation( "sizeAtr" );
    m_matrix= m_program->uniformLocation( "matrix" );
    m_R=m_program->uniformLocation( "R" );
    glEnable(GL_PROGRAM_POINT_SIZE);
    glEnable(GL_ALPHA_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void MyWidget::rotateX(int val){
    matrix.rotate(val-prev[0],1.0f,0.0f,0.0f);
    prev[0]=val;
    this->updateGL();
}

void MyWidget::rotateY(int val){
    matrix.rotate(val-prev[1],0.0f,1.0f,0.0f);
    prev[1]=val;
    this->updateGL();
}

void MyWidget::rotateZ(int val){
    matrix.rotate(val-prev[2],0.0f,0.0f,1.0f);
    prev[2]=val;
    this->updateGL();
}


void MyWidget::changeR(int val){
    R = val;
    R = R/10.0;
    this->updateGL();
}


