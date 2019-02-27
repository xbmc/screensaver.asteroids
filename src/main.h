////////////////////////////////////////////////////////////////////////////
//
// Author:
//   Joakim Eriksson
//
////////////////////////////////////////////////////////////////////////////

#pragma once

#include <glm/gtc/type_ptr.hpp>
#include <kodi/gui/gl/GL.h>
#include <kodi/gui/gl/Shader.h>
#include <kodi/addon-instance/Screensaver.h>

#include "types.h"

#define NUMLINES 100

typedef struct TRenderVertex
{
  float x, y, z;
  float col[4];
} TRenderVertex;

class CAsteroids;
class CTimer;

class ATTRIBUTE_HIDDEN CMyAddon
  : public kodi::addon::CAddonBase,
    public kodi::addon::CInstanceScreensaver,
    /*public kodi::gui::gl::CGLonDX,*/
    public kodi::gui::gl::CShaderProgram
{
public:
  CMyAddon();

  virtual bool Start() override;
  virtual void Stop() override;
  virtual void Render() override;

  void OnCompiledAndLinked() override;
  bool OnEnabled() override;

  bool Draw();
  void DrawLine(const CVector2& pos1, const CVector2& pos2, const CRGBA& col1, const CRGBA& col2);

private:
  size_t m_NumLines;
  glm::mat4 m_projMat;
  unsigned int m_vertexVBO;
  TRenderVertex* m_Verts;
  TRenderVertex* m_VertBuf;
  CAsteroids* m_asteroids;
  CTimer* m_timer;

  GLint m_uProjMatrix = -1;
  GLint m_aPosition = -1;
  GLint m_aColor = -1;
};
