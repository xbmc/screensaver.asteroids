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
#include "xbmc_scr_dll.h"
#ifndef WIN32
#include <GL/gl.h>
#else
#include <d3d11.h>
#endif
#include "main.h"
#include "Asteroids.h"
#include "timer.h"

CAsteroids*  gAsteroids = null;
CRenderD3D   gRender;
CTimer*      gTimer = null;

extern "C" {

#include <time.h>


extern "C" void Stop();

ADDON_STATUS ADDON_Create(void* hdl, void* props)
{
  if (!props)
    return ADDON_STATUS_UNKNOWN;

  SCR_PROPS* scrprops = (SCR_PROPS*)props;

  gRender.Init(scrprops->device);
  gRender.m_Width = scrprops->width;
  gRender.m_Height = scrprops->height;

  return ADDON_STATUS_OK;
}

////////////////////////////////////////////////////////////////////////////
// XBMC tells us we should get ready to start rendering. This function
// is called once when the screensaver is activated by XBMC.
//
extern "C" void Start()
{
  srand((u32)time(null));
  gAsteroids = new CAsteroids();
  if (!gAsteroids)
    return;
  gTimer = new CTimer();
  gTimer->Init();
  if (!gRender.RestoreDevice())        Stop();
  if (!gAsteroids->RestoreDevice(&gRender))  Stop();
}

////////////////////////////////////////////////////////////////////////////
// XBMC tells us to render a frame of our screensaver. This is called on
// each frame render in XBMC, you should render a single frame only - the DX
// device will already have been cleared.
//
extern "C" void Render()
{
  if (!gAsteroids)
    return;
  gRender.Begin();
  gTimer->Update();
  gAsteroids->Update(gTimer->GetDeltaTime());
  gAsteroids->Draw(&gRender);
  gRender.Draw();
}

////////////////////////////////////////////////////////////////////////////
// XBMC tells us to stop the screensaver we should free any memory and release
// any resources we have created.
//
extern "C" void Stop()
{
  if (!gAsteroids)
    return;
  gRender.InvalidateDevice();
  gAsteroids->InvalidateDevice(&gRender);
  SAFE_DELETE(gAsteroids);
  SAFE_DELETE(gTimer);
}

// XBMC tells us to stop the screensaver
// we should free any memory and release
// any resources we have created.
extern "C" void ADDON_Stop()
{
}

void ADDON_Destroy()
{
}

ADDON_STATUS ADDON_GetStatus()
{
  return ADDON_STATUS_OK;
}

bool ADDON_HasSettings()
{
  return false;
}

unsigned int ADDON_GetSettings(ADDON_StructSetting ***sSet)
{
  return 0;
}

ADDON_STATUS ADDON_SetSetting(const char *strSetting, const void *value)
{
  return ADDON_STATUS_OK;
}

void ADDON_FreeSettings()
{
}

void ADDON_Announce(const char *flag, const char *sender, const char *message, const void *data)
{
}

void GetInfo(SCR_INFO *info)
{
}

};


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
void CRenderD3D::Init(void* pContext)
{
  m_NumLines = 0;
  m_Verts = null;
#ifdef WIN32
  m_pContext = reinterpret_cast<ID3D11DeviceContext*>(pContext);
  ID3D11Device* pDevice = nullptr;
  m_pContext->GetDevice(&pDevice);

  CD3D11_BUFFER_DESC vbDesc(sizeof(TRenderVertex) * (NUMLINES * 2 + 2 /*safe*/), D3D11_BIND_VERTEX_BUFFER, D3D11_USAGE_DYNAMIC, D3D11_CPU_ACCESS_WRITE);
  pDevice->CreateBuffer(&vbDesc, nullptr, &m_pVBuffer);
  pDevice->CreatePixelShader(PixelShader, sizeof(PixelShader), nullptr, &m_pPShader);
  SAFE_RELEASE(pDevice);
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
  glBegin(GL_LINES);
  for (size_t j = 0; j < m_NumLines * 2; ++j)
  {
    glColor4f(m_VertBuf[j].col[0], m_VertBuf[j].col[1], m_VertBuf[j].col[2], m_VertBuf[j].col[3]);
    glVertex2f(m_VertBuf[j].x, m_VertBuf[j].y);
  }
  glEnd();
  m_Verts = m_VertBuf;
#else
  m_pContext->Unmap(m_pVBuffer, 0);
  m_pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
  size_t strides = sizeof(TRenderVertex), offsets = 0;
  m_pContext->IASetVertexBuffers(0, 1, &m_pVBuffer, &strides, &offsets);
  m_pContext->PSSetShader(m_pPShader, NULL, 0);
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
  if (m_Verts == null)
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
