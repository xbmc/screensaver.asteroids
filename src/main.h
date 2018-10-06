////////////////////////////////////////////////////////////////////////////
//
// Author:
//   Joakim Eriksson
//
////////////////////////////////////////////////////////////////////////////

#pragma once

#include <kodi/addon-instance/Screensaver.h>

#ifndef WIN32
  #include "shaders/GUIShader.h"
#else
  #include <d3d11.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include "types.h"

/***************************** D E F I N E S *******************************/

#define NUMLINES    100

/****************************** M A C R O S ********************************/
/***************************** C L A S S E S *******************************/

typedef struct TRenderVertex
{
  f32 x, y, z;
  float col[4];
} TRenderVertex;

class CAsteroids;
class CTimer;

class CMyAddon
  : public kodi::addon::CAddonBase,
    public kodi::addon::CInstanceScreensaver
{
public:
  CMyAddon();

  virtual bool Start() override;
  virtual void Stop() override;
  virtual void Render() override;

  bool Begin();
  bool Draw();
  void DrawLine(const CVector2& pos1, const CVector2& pos2, const CRGBA& col1, const CRGBA& col2);

private:
  s32 m_NumLines;
  int m_Width;
  int m_Height;

  TRenderVertex* m_Verts;
#ifndef WIN32
  TRenderVertex* m_VertBuf;
  CGUIShader* m_shader;
  unsigned int m_vertexVBO;
  unsigned int m_vertexVAO;
  unsigned int m_indexVBO;

#else
  ID3D11DeviceContext* m_pContext;
  ID3D11Buffer*        m_pVBuffer;
  ID3D11PixelShader*   m_pPShader;
#endif

  CAsteroids* m_asteroids;
  CTimer* m_timer;
};

/***************************** I N L I N E S *******************************/
