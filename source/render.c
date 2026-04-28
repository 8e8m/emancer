void DrawCentered(Texture * texture, Vector2 point, int invert, float radian, Color color)
{ DrawTexturePro(*texture,
                 (Rectangle){ 0, 0,
                              texture->width  * (invert >> 0 & 1 ? -1 : 1),
                              texture->height * (invert >> 1 & 1 ? -1 : 1) },
                 (Rectangle){ point.x, point.y, texture->width, texture->height },
                 (Vector2){ texture->width / 2.0f, texture->height / 2.0f },
                 radian * (180.0f / M_PI),
                 color);
}
void DrawCenteredWrapped(Texture * texture, Vector2 point, int invert, float radian, Color color)
{ float hw = texture->width  / 2.0f;
  float hh = texture->height / 2.0f;
  float ox = point.x > GAME_AREA - hw ? -GAME_AREA : point.x < hw ? GAME_AREA : 0;
  float oy = point.y > GAME_AREA - hh ? -GAME_AREA : point.y < hh ? GAME_AREA : 0;
  DrawCentered(texture, point,                                           invert, radian, color);
  if (ox) DrawCentered(texture, (Vector2){point.x+ox, point.y},          invert, radian, color);
  if (oy) DrawCentered(texture, (Vector2){point.x,    point.y+oy},       invert, radian, color);
  if (ox && oy) DrawCentered(texture, (Vector2){point.x+ox, point.y+oy}, invert, radian, color);
}
