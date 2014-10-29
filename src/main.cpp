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
#include "kodi/xbmc_scr_dll.h"
#include <GL/gl.h>
#include "main.h"
#include "Asteroids.h"
#include "timer.h"

CAsteroids*	gAsteroids = null;
CRenderD3D		gRender;
CTimer*			gTimer = null;

extern "C" {

#include <time.h>


extern "C" void Stop();

ADDON_STATUS ADDON_Create(void* hdl, void* props)
{
  if (!props)
    return ADDON_STATUS_UNKNOWN;

  SCR_PROPS* scrprops = (SCR_PROPS*)props;

  gRender.Init();
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
	if (!gRender.RestoreDevice())				Stop();
	if (!gAsteroids->RestoreDevice(&gRender))	Stop();
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

////////////////////////////////////////////////////////////////////////////
// 
void	CRenderD3D::Init()
{
	m_NumLines = 0;
	m_Verts = null;
}

////////////////////////////////////////////////////////////////////////////
// 
bool		CRenderD3D::RestoreDevice()
{
	return true;
}

////////////////////////////////////////////////////////////////////////////
// 
void			CRenderD3D::InvalidateDevice()
{
}

////////////////////////////////////////////////////////////////////////////
// 
bool			CRenderD3D::Draw()
{
	if (m_NumLines == 0)
		return true;

        glBegin(GL_LINES);
        for (size_t j=0;j<m_NumLines*2;++j)
        {
          glColor4f(m_VertBuf[j].col[0], m_VertBuf[j].col[1], m_VertBuf[j].col[2], m_VertBuf[j].col[3]);
          glVertex2f(m_VertBuf[j].x, m_VertBuf[j].y);
        }
        glEnd();

	m_NumLines = 0;
        m_Verts = m_VertBuf;
	return true;
}

////////////////////////////////////////////////////////////////////////////
// 
void			CRenderD3D::DrawLine(const CVector2& pos1, const CVector2& pos2, const CRGBA& col1, const CRGBA& col2)
{
	if (m_NumLines >= NUMLINES)
	{
		Draw();
	}

	if (m_Verts == null)
	{
          m_VertBuf = new TRenderVertex[10000];
          m_Verts = m_VertBuf;
	}

	m_Verts->x = pos1.x; m_Verts->y = pos1.y; m_Verts->z = 0.0f; m_Verts->w = 0.0f; 
        m_Verts->col[0] = col1.r;
        m_Verts->col[1] = col1.g;
        m_Verts->col[2] = col1.b;
        m_Verts->col[3] = col1.a;	m_Verts++;
	m_Verts->x = pos2.x; m_Verts->y = pos2.y; m_Verts->z = 0.0f; m_Verts->w = 0.0f; 
        m_Verts->col[0] = col2.r;
        m_Verts->col[1] = col2.g;
        m_Verts->col[2] = col2.b;
        m_Verts->col[3] = col2.a;	m_Verts++;
	
	m_NumLines++;
}
