////////////////////////////////////////////////////////////////////////////
//
// Asteroids Screensaver for XBox Media Center
// Copyright (c) 2005 Joakim Eriksson <je@plane9.com>
//
// The TestXBS framework and program is made by Warren
//
////////////////////////////////////////////////////////////////////////////
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
//
////////////////////////////////////////////////////////////////////////////
//

#include "main.h"
#include "Asteroids.h"
#include "timer.h"

#include <glm/glm.hpp>

////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////

CMyAddon::CMyAddon()
  : m_projMat(glm::ortho(0.0f, float(Width()), float(Height()), 0.0f)),
    m_asteroids(nullptr),
    m_timer(nullptr)
{ 
  //CGLonDX::InitContext();
}

////////////////////////////////////////////////////////////////////////////
// Kodi tells us we should get ready to start rendering. This function
// is called once when the screensaver is activated by Kodi.
//
bool CMyAddon::Start()
{
  std::string fraqShader = kodi::GetAddonPath("resources/shaders/GLES/glsl.frag");
  std::string vertShader = kodi::GetAddonPath("resources/shaders/GLES/glsl.vert");
  if (!LoadShaderFiles(vertShader, fraqShader) || !CompileAndLink())
    return false;

  m_NumLines = 0;
  m_VertBuf = new TRenderVertex[10000];
  m_Verts = m_VertBuf;

  glGenBuffers(1, &m_vertexVBO);

  srand((u32)time(nullptr));
  m_asteroids = new CAsteroids(this);
  if (!m_asteroids)
    return false;

  m_timer = new CTimer();
  m_timer->Init();
  if (!m_asteroids->RestoreDevice())
  {
    Stop();
    return false;
  }

  return true;
}

void CMyAddon::Stop()
{
  if (!m_asteroids)
    return;

  m_asteroids->InvalidateDevice();
  SAFE_DELETE(m_asteroids);
  SAFE_DELETE(m_timer);
  SAFE_DELETE(m_VertBuf);

  glDeleteBuffers(1, &m_vertexVBO);
  m_vertexVBO = 0;
}

////////////////////////////////////////////////////////////////////////////
// Kodi tells us to render a frame of our screensaver. This is called on
// each frame render in Kodi, you should render a single frame only - the DX
// device will already have been cleared.
//
void CMyAddon::Render()
{
  if (!m_asteroids)
    return;
 
  m_timer->Update();
  m_asteroids->Update(m_timer->GetDeltaTime());
  m_asteroids->Draw();
  Draw();
}

////////////////////////////////////////////////////////////////////////////
//
bool CMyAddon::Draw()
{
  if (m_NumLines == 0)
    return true;

  glBindBuffer(GL_ARRAY_BUFFER, m_vertexVBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(TRenderVertex)*m_NumLines * 2, m_VertBuf, GL_STATIC_DRAW);

  glVertexAttribPointer(m_aPosition, 3, GL_FLOAT, GL_FALSE, sizeof(TRenderVertex), BUFFER_OFFSET(offsetof(TRenderVertex, x)));
  glEnableVertexAttribArray(m_aPosition);

  glVertexAttribPointer(m_aColor, 4, GL_FLOAT, GL_FALSE, sizeof(TRenderVertex), BUFFER_OFFSET(offsetof(TRenderVertex, col)));
  glEnableVertexAttribArray(m_aColor);

  glBindBuffer(GL_ARRAY_BUFFER, 0);

  // render
  EnableShader();
  glDrawArrays(GL_LINES, 0, m_NumLines * 2);
  DisableShader();

  m_Verts = m_VertBuf;

  m_NumLines = 0;
  return true;
}

////////////////////////////////////////////////////////////////////////////
//
void CMyAddon::DrawLine(const CVector2& pos1, const CVector2& pos2, const CRGBA& col1, const CRGBA& col2)
{
  if (m_NumLines >= NUMLINES)
  {
    Draw();
  }

  m_Verts->x = pos1.x; m_Verts->y = pos1.y; m_Verts->z = 1.0f;
  m_Verts->col[0] = col1.r;
  m_Verts->col[1] = col1.g;
  m_Verts->col[2] = col1.b;
  m_Verts->col[3] = col1.a;  m_Verts++;

  m_Verts->x = pos2.x; m_Verts->y = pos2.y; m_Verts->z = 1.0f;
  m_Verts->col[0] = col2.r;
  m_Verts->col[1] = col2.g;
  m_Verts->col[2] = col2.b;
  m_Verts->col[3] = col2.a;  m_Verts++;

  m_NumLines++;
}

void CMyAddon::OnCompiledAndLinked()
{
  m_uProjMatrix = glGetUniformLocation(ProgramHandle(), "u_modelViewProjectionMatrix");
  m_aPosition = glGetAttribLocation(ProgramHandle(), "a_position");
  m_aColor = glGetAttribLocation(ProgramHandle(), "a_color");
}

bool CMyAddon::OnEnabled()
{
  glUniformMatrix4fv(m_uProjMatrix, 1, GL_FALSE, glm::value_ptr(m_projMat));
  return true;
}

ADDONCREATOR(CMyAddon);
