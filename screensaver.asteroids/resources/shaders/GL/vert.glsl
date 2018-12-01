#version 150

in vec3 m_attrpos;
in vec4 m_attrcol;

out vec4 m_cord;
out vec4 m_col;

uniform mat4 m_proj;
uniform mat4 m_model;

void main ()
{
  mat4 mvp = m_proj * m_model;
  gl_Position = mvp * vec4(m_attrpos.x, m_attrpos.y, m_attrpos.z, 1.0);
  m_col = m_attrcol;
}
