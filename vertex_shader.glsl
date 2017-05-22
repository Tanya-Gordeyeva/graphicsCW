attribute highp vec4 posAtr;
attribute highp vec4 posAtrCol;
uniform lowp float R;
uniform lowp vec4 colAtr;
uniform lowp float sizeAtr;
uniform highp mat4 matrix;
varying lowp vec4 col;
varying lowp float point;
varying vec3 l;
varying vec3 n;
varying vec3 v;
uniform vec4 lightPos;
uniform vec4 eyePos;
uniform vec3 normal;



void main()
{

//    if (abs(sin(posAtr.y))*abs(sin(posAtr.y))+abs(sin(posAtr.z))*abs(sin(posAtr.z))>=(0.4)){
//        col=vec4(1.0,0.0,0.0,1.0);
//    }else
//    {if (abs(sin(posAtr.y))*abs(sin(posAtr.y))+abs(sin(posAtr.z))*abs(sin(posAtr.z))>=(0.2*R*cos(1.0)+R/2.0)){
//        col=vec4(0.0,1.0,0.0,1.0);
//    } else col=vec4(0.0,0.0,1.0,1.0);}
   vec3 p = vec3 ( matrix * posAtr );
   l = normalize ( vec3 ( lightPos ) - p );
   v = normalize ( vec3 ( eyePos )   - p );
   n = normalize ( gl_NormalMatrix * normal );
    col=colAtr;
    gl_PointSize=sizeAtr;
    gl_Position = matrix*posAtr;



}
