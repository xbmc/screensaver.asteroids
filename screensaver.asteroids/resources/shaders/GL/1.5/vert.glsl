#version 150

in vec3 m_attrpos;
in vec4 m_attrcol;
out vec4 m_col;

void main()
{
   gl_Position = vec4(m_attrpos.x, m_attrpos.y, m_attrpos.z, 1.0);
   m_col = m_attrcol;
}
