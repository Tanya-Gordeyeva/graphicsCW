#include "mywidget.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <QVector3D>
#include <QVector4D>

MyWidget::MyWidget(QWidget *parent):
    QGLWidget(parent)
{
    setGeometry(50,50,500,500);
    R=0.9f;
    size=M_PI/27.0;
    x_light=1.0f;
    y_light=1.0f;
    z_light=0.0f;

}

void MyWidget::initializeGL(){
    initializeOpenGLFunctions();
    glClearColor(0.1, 0.1, 0.2, 1);
    glViewport(0,0,500,500);
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    glMatrixMode( GL_MODELVIEW );

    glPushMatrix ();


    glColor4f          ( 1, 1, 1, 1 );

    glPopMatrix        ();

    glMatrixMode   ( GL_MODELVIEW );
    glPushMatrix   ();

    initShaders();
    glPopMatrix ();


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

    m_program->setUniformValue("lightPos", QVector4D(x_light,y_light,z_light,1.0) );
    m_program->setUniformValue("eyePos", QVector4D(0.0,0.0,0.0,1.0) );





    //отрисовка фигуры
    GLfloat vec[12];
    if (light){
        m_program->setUniformValue("light", true );
    } else {
        m_program->setUniformValue("lightPos", QVector4D(x_light,y_light,z_light,1.0) );
        m_program->setUniformValue("light", false );
    }
    //    for (double j = 0; j<=2.0*M_PI; j += size/2.0){
    //            for (double t =0; t <= 2*M_PI; t += size){

    //                vec[0]=x_light+k;
    //                vec[1]=y_light+0.03*sin(j)*cos(t);
    //                vec[2]=z_light+0.03*sin(j)*sin(t);
    //                vec[3]=x_light+k;
    //                vec[4]=y_light+0.03*sin(j)*cos(t-size);
    //                vec[5]=z_light+0.03*sin(j)*sin(t-size);
    //                vec[6]=x_light+y;
    //                vec[7]=y_light+0.03*sin(j-size/2.0)*cos(t-size);
    //                vec[8]=z_light+0.03*sin(j)*sin(t-size);
    //                vec[9]=x_light+y;
    //                vec[10]=y_light+0.03*sin(j-size/2.0)*cos(t);
    //                vec[11]=z_light+0.03*sin(j-size/2.0)*sin(t);
    //                glVertexAttribPointer( m_posAtr, 3, GL_FLOAT, GL_FALSE, 0,vec);
    //                glEnableVertexAttribArray( m_posAtr );
    //                glEnable(GL_CULL_FACE);
    //                glCullFace(GL_FRONT);
    //                glDrawArrays( GL_POLYGON, 0, 4);
    //                glDisable(GL_CULL_FACE);
    //                glDisableVertexAttribArray( m_posAtr);


    //        }
    //            //m_program->setUniformValue("normal",vec[0],vec[1],vec[2]);

    //            m_program->setUniformValue(m_colAtr,1.0,1.0,1.0,1.0);
    //            y=k;
    //            k=0.03*cos(j);
    //    }
    float k1 = 0.2*R*sin(-size/20.0);
    float y1 = 0;
    float y = 0;
    float k = 0;
    m_program->setUniformValue("light", true );

    for (double j = -3*M_PI/2.0; j<=M_PI/2.0+size; j += size/2.0){
        for (double t =size/18.0; t <= 2*M_PI; t += size){
            glEnable(GL_CULL_FACE);
            glCullFace(GL_FRONT);
            if (color<=0)
                m_program->setUniformValue(m_colAtr,0.5*(sin(j+M_PI/2.0))+0.3+color/2.0,0.5*abs(sin(j-color/2.0))+0.1+color/2.0,-0.5*sin(j+M_PI/2.0)-color/2.0,1.0);
            else
                m_program->setUniformValue(m_colAtr,0.5*(sin(j+M_PI/2.0))+0.3+color/2.0,0.5*abs(sin(j+color/2.0))+0.1-color/2.0,-0.5*sin(j+M_PI/2.0)-color/2.0,1.0);

            vec[0]=k1;
            vec[1]=(0.2*R*cos(j)+R/2.0)*cos(t);
            vec[2]=(0.2*R*cos(j)+R/2.0)*sin(t);
            vec[3]=k1;
            vec[4]=(0.2*R*cos(j)+R/2.0)*cos(t-size);
            vec[5]=(0.2*R*cos(j)+R/2.0)*sin(t-size);
            vec[6]=y1;
            vec[7]=(0.2*R*cos(j-size/2.0)+R/2.0)*cos(t-size);
            vec[8]=(0.2*R*cos(j-size/2.0)+R/2.0)*sin(t-size);
            vec[9]=y1;
            vec[10]=(0.2*R*cos(j-size/2.0)+R/2.0)*cos(t);
            vec[11]=(0.2*R*cos(j-size/2.0)+R/2.0)*sin(t);
            m_program->setUniformValue("normal",vec[0]+R/2.0,vec[1]+R/2.0,vec[2]+R/2.0);
            glVertexAttribPointer( m_posAtr, 3, GL_FLOAT, GL_FALSE, 0,vec);
            glEnableVertexAttribArray( m_posAtr );
            glDrawArrays( GL_POLYGON, 0, 4);

            glDisableVertexAttribArray( m_posAtr);
            vec[0]=x_light+k;
            vec[1]=y_light+0.02*sin(j)*cos(t);
            vec[2]=z_light+0.02*sin(j)*sin(t);
            vec[3]=x_light+k;
            vec[4]=y_light+0.02*sin(j)*cos(t-size);
            vec[5]=z_light+0.02*sin(j)*sin(t-size);
            vec[6]=x_light+y;
            vec[7]=y_light+0.02*sin(j-size/2.0)*cos(t-size);
            vec[8]=z_light+0.02*sin(j)*sin(t-size);
            vec[9]=x_light+y;
            vec[10]=y_light+0.02*sin(j-size/2.0)*cos(t);
            vec[11]=z_light+0.02*sin(j-size/2.0)*sin(t);
            m_program->setUniformValue(m_colAtr,1.0,1.0,1.0,1.0);
            glVertexAttribPointer( m_posAtr, 3, GL_FLOAT, GL_FALSE, 0,vec);
            glEnableVertexAttribArray( m_posAtr );

            glDrawArrays( GL_POLYGON, 0, 4);
            glDisable(GL_CULL_FACE);
            glDisableVertexAttribArray( m_posAtr);
        }

        y1=k1;
        k1=0.2*R*sin(j);
        y=k;
        k=0.02*cos(j);
    }

    m_program->setUniformValue("light", false );
    for (double j = -0.99; j<=1.01; j += 0.01){

        vec[0]=1.0;
        vec[1]=j;
        vec[2]=0.0;
        vec[3]=0.8;
        vec[4]=j;
        vec[5]=0.0;
        vec[6]=0.8;
        vec[7]=j-0.01;
        vec[8]=0.0;
        vec[9]=1.0;
        vec[10]=j-0.01;
        vec[11]=0.0;
        if (color>0)
        m_program->setUniformValue(m_colAtr,j*1.5+0.6+color,(1.0-abs(j+color))*1.5-color,-j*1.5-color,1.0);
        else
        m_program->setUniformValue(m_colAtr,j*1.5+0.6+color,(1.0-abs(j+color))*1.5+2.0*color,-j*1.5-1.5*color,1.0);
        glVertexAttribPointer( m_posAtr, 3, GL_FLOAT, GL_FALSE, 0,vec);
        glEnableVertexAttribArray( m_posAtr );

        glDrawArrays( GL_POLYGON, 0, 4);
        glDisable(GL_CULL_FACE);
        glDisableVertexAttribArray( m_posAtr);
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

void MyWidget::changeX_light(int val){
    x_light = val;
    x_light = x_light/10.0;
    this->updateGL();
}

void MyWidget::changeY_light(int val){
    y_light = val;
    y_light = y_light/10.0;
    this->updateGL();
}

void MyWidget::changeZ_light(int val){
    z_light = val;
    z_light = z_light/10.0;
    this->updateGL();
}

void MyWidget::changeColor(int val){
    color = -val;
    color = color/10.0;
    this->updateGL();
}



