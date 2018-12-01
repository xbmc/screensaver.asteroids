#version 300 es

precision mediump float;
in vec4 m_col;
out vec4 FragColor;

void main()
{
   FragColor = m_col;
}
