static inline void UpdateContext(struct context * context)
{ context->area->x = GetRenderWidth();
  context->area->y = GetRenderHeight();
  context->delta = GetFrameTime();
  context->time += context->delta * 100;
  UpdateBackground(context);
  UpdatePlayer(context);
  UpdateBullet(context);
}
static inline void RenderContext(struct context * context)
{ BeginTextureMode(context->render);
  RenderBackground(context);
  RenderPlayer(context);
  RenderBullet(context);
  EndTextureMode();
  if (context->area->x > GAME_AREA
  ||  context->area->y > GAME_AREA)
  { RenderBorder(context);
  }
  DrawTexturePro(context->render.texture, 
                 (Rectangle) { 0, 0, GAME_AREA, -GAME_AREA},
                 (Rectangle) { context->area->x / 2 - GAME_AREA/2, 0, GAME_AREA, context->area->y}, 
                 (Vector2){0,0}, 0, WHITE);
}
static inline void InitContext(struct context * context)
{ Texture texture[] =
    { LoadTexture("resource/background.png"),
      LoadTexture("resource/checker.png"),
      LoadTexture("resource/border.png"),
      LoadTexture("resource/cirno.png"),
      LoadTexture("resource/flan.png"),
      LoadTexture("resource/bullet32.png"),
      LoadTexture("resource/bullet24.png"),
      LoadTexture("resource/bullet20.png"),
      LoadTexture("resource/bullet16.png"),
      LoadTexture("resource/bullet12.png"),
      LoadTexture("resource/bullet8.png"),
    };
  context->render = LoadRenderTexture(GAME_AREA, GAME_AREA);
  memset(context, 0, sizeof(context));
  memcpy(context->texture, texture, sizeof(texture) / sizeof(*texture) * sizeof(Texture));
  context->area->x = GetRenderWidth();
  context->area->y = GetRenderHeight();
  InitPlayer(context);
  InitBullet(context);
  InitBackground(context);
  InitMusic(context);
}
static inline void DeinitContext(struct context * context)
{ int i = 0;
  for (i = 0; i < END_TEXTURE; ++i)
  { UnloadTexture(context->texture[i]);
  }
  for (i = 0; i < END_SONG; ++i)
  { UnloadSound(context->music[i]);
  }
  UnloadRenderTexture(context->render);
}
