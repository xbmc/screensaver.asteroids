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

#include <time.h>

CRenderD3D gRender;

#define BUFFER_OFFSET(i) ((char *)nullptr + (i))

CMyAddon::CMyAddon()
  : m_asteroids(nullptr),
    m_timer(nullptr)
{
}

CMyAddon::~CMyAddon()
{
  gRender.DeInit();
}

////////////////////////////////////////////////////////////////////////////
// Kodi tells us we should get ready to start rendering. This function
// is called once when the screensaver is activated by Kodi.
//
bool CMyAddon::Start()
{
  if (!gRender.Init(Device()))
    return false;

  gRender.m_Width = Width();
  gRender.m_Height = Height();

  srand((u32)time(nullptr));
  m_asteroids = new CAsteroids(this);
  if (!m_asteroids)
    return false;

  m_timer = new CTimer();
  m_timer->Init();
  if (!gRender.RestoreDevice() || !m_asteroids->RestoreDevice(&gRender))
  {
    Stop();
    return false;
  }

  return true;
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

  gRender.Begin();
  m_timer->Update();
  m_asteroids->Update(m_timer->GetDeltaTime());
  m_asteroids->Draw(&gRender);
  gRender.Draw();
}

////////////////////////////////////////////////////////////////////////////
// Kodi tells us to stop the screensaver we should free any memory and release
// any resources we have created.
//
void CMyAddon::Stop()
{
  if (!m_asteroids)
    return;

  gRender.InvalidateDevice();
  m_asteroids->InvalidateDevice(&gRender);
  SAFE_DELETE(m_asteroids);
  SAFE_DELETE(m_timer);
}


////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
#ifdef WIN32
const BYTE PixelShader[] =
{
     68,  88,  66,  67,  18, 124,
    182,  35,  30, 142, 196, 211,
     95, 130,  91, 204,  99,  13,
    249,   8,   1,   0,   0,   0,
    124,   1,   0,   0,   4,   0,
      0,   0,  48,   0,   0,   0,
    124,   0,   0,   0, 188,   0,
      0,   0,  72,   1,   0,   0,
     65, 111, 110,  57,  68,   0,
      0,   0,  68,   0,   0,   0,
      0,   2, 255, 255,  32,   0,
      0,   0,  36,   0,   0,   0,
      0,   0,  36,   0,   0,   0,
     36,   0,   0,   0,  36,   0,
      0,   0,  36,   0,   0,   0,
     36,   0,   0,   2, 255, 255,
     31,   0,   0,   2,   0,   0,
      0, 128,   0,   0,  15, 176,
      1,   0,   0,   2,   0,   8,
     15, 128,   0,   0, 228, 176,
    255, 255,   0,   0,  83,  72,
     68,  82,  56,   0,   0,   0,
     64,   0,   0,   0,  14,   0,
      0,   0,  98,  16,   0,   3,
    242,  16,  16,   0,   1,   0,
      0,   0, 101,   0,   0,   3,
    242,  32,  16,   0,   0,   0,
      0,   0,  54,   0,   0,   5,
    242,  32,  16,   0,   0,   0,
      0,   0,  70,  30,  16,   0,
      1,   0,   0,   0,  62,   0,
      0,   1,  73,  83,  71,  78,
    132,   0,   0,   0,   4,   0,
      0,   0,   8,   0,   0,   0,
    104,   0,   0,   0,   0,   0,
      0,   0,   1,   0,   0,   0,
      3,   0,   0,   0,   0,   0,
      0,   0,  15,   0,   0,   0,
    116,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,
      3,   0,   0,   0,   1,   0,
      0,   0,  15,  15,   0,   0,
    122,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,
      3,   0,   0,   0,   2,   0,
      0,   0,   3,   0,   0,   0,
    122,   0,   0,   0,   1,   0,
      0,   0,   0,   0,   0,   0,
      3,   0,   0,   0,   2,   0,
      0,   0,  12,   0,   0,   0,
     83,  86,  95,  80,  79,  83,
     73,  84,  73,  79,  78,   0,
     67,  79,  76,  79,  82,   0,
     84,  69,  88,  67,  79,  79,
     82,  68,   0, 171,  79,  83,
     71,  78,  44,   0,   0,   0,
      1,   0,   0,   0,   8,   0,
      0,   0,  32,   0,   0,   0,
      0,   0,   0,   0,   0,   0,
      0,   0,   3,   0,   0,   0,
      0,   0,   0,   0,  15,   0,
      0,   0,  83,  86,  95,  84,
     65,  82,  71,  69,  84,   0,
    171, 171
};
#endif
////////////////////////////////////////////////////////////////////////////
//
bool CRenderD3D::Init(void* pContext)
{
  m_NumLines = 0;
  m_Verts = nullptr;

#ifndef WIN32

  m_shader = new CGUIShader("vert.glsl", "frag.glsl");
  if (!m_shader->CompileAndLink())
  {
    delete m_shader;
    m_shader = nullptr;
    return false;
  }

  glGenBuffers(1, &m_vertexVBO);
  glGenBuffers(1, &m_indexVBO);

#else
  m_pContext = reinterpret_cast<ID3D11DeviceContext*>(pContext);
  ID3D11Device* pDevice = nullptr;
  m_pContext->GetDevice(&pDevice);

  CD3D11_BUFFER_DESC vbDesc(sizeof(TRenderVertex) * (NUMLINES * 2 + 2 /*safe*/), D3D11_BIND_VERTEX_BUFFER, D3D11_USAGE_DYNAMIC, D3D11_CPU_ACCESS_WRITE);
  pDevice->CreateBuffer(&vbDesc, nullptr, &m_pVBuffer);
  pDevice->CreatePixelShader(PixelShader, sizeof(PixelShader), nullptr, &m_pPShader);
  SAFE_RELEASE(pDevice);
#endif

  return true;
}

void CRenderD3D::DeInit()
{
#ifndef WIN32
  glDeleteBuffers(1, &m_vertexVBO);
  glDeleteBuffers(1, &m_indexVBO);

  delete m_shader;
  m_shader = nullptr;
#endif
}

////////////////////////////////////////////////////////////////////////////
//
bool CRenderD3D::RestoreDevice()
{
  return true;
}

////////////////////////////////////////////////////////////////////////////
//
void CRenderD3D::InvalidateDevice()
{
#ifdef WIN32
  SAFE_RELEASE(m_pPShader);
  SAFE_RELEASE(m_pVBuffer);
#endif
}

////////////////////////////////////////////////////////////////////////////
//
bool CRenderD3D::Begin()
{
#ifdef WIN32
  D3D11_MAPPED_SUBRESOURCE res = {};
  if (SUCCEEDED(m_pContext->Map(m_pVBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &res)))
    m_Verts = (TRenderVertex*)res.pData;
#endif
  return true;
}

////////////////////////////////////////////////////////////////////////////
//
bool CRenderD3D::Draw()
{
  if (m_NumLines == 0)
    return true;

#ifndef WIN32
  struct PackedVertex
  {
    GLfloat x, y, z;
    GLfloat r, g, b;
  } vertex[m_NumLines * 2];
  unsigned int idx[m_NumLines * 2];

  for (size_t j = 0; j < m_NumLines * 2; ++j)
  {
    vertex[j].x = (m_VertBuf[j].x - gRender.m_Width / 2.0f) / gRender.m_Width * 2.0f;
    vertex[j].y = (m_VertBuf[j].y - gRender.m_Height / 2.0f) / gRender.m_Height * 2.0f;
    vertex[j].z = 0.0;
    vertex[j].r = m_VertBuf[j].col[0];
    vertex[j].g = m_VertBuf[j].col[1];
    vertex[j].b = m_VertBuf[j].col[2];
    idx[j] = j;
  }

  GLint colLoc = m_shader->GetColLoc();

  glBindBuffer(GL_ARRAY_BUFFER, m_vertexVBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(PackedVertex)*m_NumLines*2, vertex, GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexVBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(idx), idx, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(PackedVertex), BUFFER_OFFSET(offsetof(PackedVertex, x)));
  glEnableVertexAttribArray(0);

  glVertexAttribPointer(colLoc, 3, GL_FLOAT, GL_FALSE, sizeof(PackedVertex), BUFFER_OFFSET(offsetof(PackedVertex, r)));
  glEnableVertexAttribArray(colLoc);

  glBindBuffer(GL_ARRAY_BUFFER, 0);

  // render
  m_shader->Enable();
  glDrawArrays(GL_LINES, 0, m_NumLines * 2);
  m_shader->Disable();

  m_Verts = m_VertBuf;
#else
  m_pContext->Unmap(m_pVBuffer, 0);
  m_pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
  UINT strides = sizeof(TRenderVertex), offsets = 0;
  m_pContext->IASetVertexBuffers(0, 1, &m_pVBuffer, &strides, &offsets);
  m_pContext->PSSetShader(m_pPShader, nullptr, 0);
  m_pContext->Draw(m_NumLines * 2, 0);
  Begin();
#endif
  m_NumLines = 0;
  return true;
}

////////////////////////////////////////////////////////////////////////////
//
void CRenderD3D::DrawLine(const CVector2& pos1, const CVector2& pos2, const CRGBA& col1, const CRGBA& col2)
{
  if (m_NumLines >= NUMLINES)
  {
    Draw();
  }
#ifndef WIN32
  if (m_Verts == nullptr)
  {
    m_VertBuf = new TRenderVertex[10000];
    m_Verts = m_VertBuf;
  }
#endif
  m_Verts->x = pos1.x; m_Verts->y = pos1.y; m_Verts->z = 0.0f;
  m_Verts->col[0] = col1.r;
  m_Verts->col[1] = col1.g;
  m_Verts->col[2] = col1.b;
  m_Verts->col[3] = col1.a;  m_Verts++;

  m_Verts->x = pos2.x; m_Verts->y = pos2.y; m_Verts->z = 0.0f;
  m_Verts->col[0] = col2.r;
  m_Verts->col[1] = col2.g;
  m_Verts->col[2] = col2.b;
  m_Verts->col[3] = col2.a;  m_Verts++;

  m_NumLines++;
}

ADDONCREATOR(CMyAddon);
