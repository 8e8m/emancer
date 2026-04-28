static inline void UpdateBackground(struct context * context)
{ short r,g,b; r=g=b=0;
  context->effects->checker_alpha = fabs(cos(context->time/25)) * 60 + 94;
  if (context->effects->background_color.r != context->effects->target_background_color.r)
  { if (context->effects->target_background_color.r > context->effects->background_color.r) r=1;
    else r=-1;
  }
  if (context->effects->background_color.g != context->effects->target_background_color.g)
  { if (context->effects->target_background_color.g > context->effects->background_color.r) g=1;
    else g=-1;
  }
  if (context->effects->background_color.b != context->effects->target_background_color.b)
  { if (context->effects->target_background_color.b > context->effects->background_color.r) b=1;
    else b=-1;
  }
  context->effects->background_color.r += r;
  context->effects->background_color.g += g;
  context->effects->background_color.b += b;
}
static inline void RenderBackground(struct context * context)
{ int i;
  double offset = fmod(context->time * context->effects->scroll_speed, GAME_AREA);
  ClearBackground(BLACK);
  DrawTexture(context->texture[BACKGROUND], 0, offset - GAME_AREA, context->effects->background_color);
  DrawTexture(context->texture[BACKGROUND], 0, offset, context->effects->background_color);
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
{ DrawTexturePro(context->texture[BORDER],
                 (Rectangle) { 0, 0, context->texture[BORDER].width, context->texture[BORDER].height},
                 (Rectangle) { 0, 0, context->area->x / 2 - GAME_AREA / 2, context->area->y}, 
                 (Vector2){0,0}, 0, context->effects->background_color);
  DrawTexturePro(context->texture[BORDER],
                 (Rectangle) { 0, 0, context->texture[BORDER].width, context->texture[BORDER].height},
                 (Rectangle) { context->area->x / 2 + GAME_AREA / 2, 0, context->area->x / 2 - GAME_AREA / 2, context->area->y}, 
                 (Vector2){0,0}, 0, context->effects->background_color);
}
static inline void RestartBackground(struct context * context)
{ context->effects->scroll_speed = 3;
  context->effects->background_color = context->effects->target_background_color = WHITE;
}
