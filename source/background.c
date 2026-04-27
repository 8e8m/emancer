static inline void UpdateBackground(struct context * context)
{ context->effects->checker_alpha = fabs(cos(context->time/25)) * 60 + 94;
}
static inline void RenderBackground(struct context * context)
{ int i;
  double offset = fmod(context->time * context->effects->scroll_speed, GAME_AREA);
  ClearBackground(BLACK);
  DrawTexture(context->texture[BACKGROUND], 0, offset - GAME_AREA, WHITE);
  DrawTexture(context->texture[BACKGROUND], 0, offset, WHITE);
  for (i = 0; i < GAME_AREA; i += context->texture[CHECKER].width)
  { DrawTexturePro(context->texture[CHECKER],
                   (Rectangle) {0, 0, context->texture[CHECKER].width, context->texture[CHECKER].height},
                   (Rectangle) {i, GAME_AREA - context->texture[CHECKER].width, context->texture[CHECKER].width, context->texture[CHECKER].height},
                   (Vector2){0,0}, 0, (Color){255,255,255,context->effects->checker_alpha});
    DrawTexturePro(context->texture[CHECKER],
                   (Rectangle) {0, 0, context->texture[CHECKER].width, -context->texture[CHECKER].height},
                   (Rectangle) {i, 0, context->texture[CHECKER].width, context->texture[CHECKER].height},
                   (Vector2){0,0}, 0, (Color){255,255,255,context->effects->checker_alpha});
  }
}
static inline void RenderBorder(struct context * context)
{ Color color = (Color) {78*0.9, 90*0.9, 108*0.9, 255}; // meant to match BACKGROUND, variablize maybe
  DrawTexturePro(context->texture[BORDER],
                 (Rectangle) { 0, 0, context->texture[BORDER].width, context->texture[BORDER].height},
                 (Rectangle) { 0, 0, context->area->x / 2 - GAME_AREA / 2, context->area->y}, 
                 (Vector2){0,0}, 0, color);
  DrawTexturePro(context->texture[BORDER],
                 (Rectangle) { 0, 0, context->texture[BORDER].width, context->texture[BORDER].height},
                 (Rectangle) { context->area->x / 2 + GAME_AREA / 2, 0, context->area->x / 2 - GAME_AREA / 2, context->area->y}, 
                 (Vector2){0,0}, 0, color);
}
static inline void InitBackground(struct context * context)
{ context->effects->scroll_speed = 3;
}
