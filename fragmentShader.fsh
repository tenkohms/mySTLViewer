#version 120

//! [0]
varying vec4 varyingColor;

varying vec4 fragColor;

void main(void)
{
    gl_FragColor = varyingColor;
}
//! [0]
