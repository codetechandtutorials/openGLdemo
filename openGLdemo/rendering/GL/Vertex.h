#pragma once
struct Vertex {
  Vertex(float posx, float posy, float posz, float colorr, float colorg, float colorb) {
    pos[0] = posx;
    pos[1] = posy;
    pos[2] = posz;
    color[0] = colorr;
    color[1] = colorg;
    color[2] = colorb;
  }
  Vertex(float posx, float posy, float posz, float texu, float texv) {
    pos[0] = posx;
    pos[1] = posy;
    pos[2] = posz;
    texCoord[0] = texu;
    texCoord[1] = texv;
  };
  float pos[3];
  float texCoord[2] = { -1.f, -1.f };
  float color[3] = { .9f, .1f, .1f };
};