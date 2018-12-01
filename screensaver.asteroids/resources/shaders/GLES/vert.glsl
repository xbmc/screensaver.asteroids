#version 300 es

uniform mat4 modelViewProjectionMatrix;
layout (location = 0) in vec4 m_attrpos;
layout (location = 1) in vec4 m_attrcol;
out vec4 m_col;

void main()
{
   gl_Position = vec4(m_attrpos.x, m_attrpos.y, m_attrpos.z, 1.0);
   m_col = m_attrcol;
}
