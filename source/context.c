static inline void UpdateContext(struct context * context)
{ context->area->x = GetRenderWidth();
  context->area->y = GetRenderHeight();
  context->delta = GetFrameTime();
  context->time += context->delta * 100;
  if (context->time > 2000)
  { context->effects->tutor_alpha -= 0.01f;
  }
  UpdateBackground(context);
  UpdatePlayer(context);
  UpdateBullet(context);
  UpdateMusic(context);
  UpdateBoss(context);
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
                 (Vector2){0,0}, 0, context->effects->flash > 0 ? (Color) { 255 * -context->effects->flash, 255 * -context->effects->flash, 255, 255 } : WHITE);
  DrawCentered(context->texture+TUTOR, (Vector2) {context->area->x/10, context->area->y/10}, 0, 0, ColorAlpha(WHITE, context->effects->tutor_alpha));
}
/* Instant restarts are done via minimal changes to state via restart functions
 * This outperforms Deinit Init by ∞ */
static inline void RestartContext(struct context * context)
{ context->time = 0;
  RestartBoss(context);
  RestartPlayer(context);
  RestartBullet(context);
  RestartBackground(context);
  RestartMusic(context);
  context->effects->tutor_alpha = 1;
}
static inline void InitContext(struct context * context)
{ Texture texture[] =
    { LoadTexture("resource/background.png"),
      LoadTexture("resource/checker.png"),
      LoadTexture("resource/border.png"),
      LoadTexture("resource/cirno.png"),
      LoadTexture("resource/flan.png"),
      LoadTexture("resource/tutor.png"),
      LoadTexture("resource/bullet32.png"),
      LoadTexture("resource/bullet24.png"),
      LoadTexture("resource/bullet20.png"),
      LoadTexture("resource/bullet16.png"),
      LoadTexture("resource/bullet12.png"),
      LoadTexture("resource/bullet8.png"),
    };
  memset(context, 0, sizeof(*context));
  context->render = LoadRenderTexture(GAME_AREA, GAME_AREA);
  memcpy(context->texture, texture, sizeof(texture) / sizeof(*texture) * sizeof(Texture));
  context->area->x = GetRenderWidth();
  context->area->y = GetRenderHeight();
  InitPlayer(context);
  InitBullet(context);
  InitMusic(context);
  RestartContext(context);
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
  DeinitBullet(context);
}
static inline void PreinitContext(char * name)
{ srand(time(NULL));
  SetTraceLogLevel(LOG_ERROR);
  SetConfigFlags(FLAG_MSAA_4X_HINT);
  InitWindow(0, 0, name);
  InitAudioDevice();
  SetMasterVolume(0.1f);
}
static inline void ContextLoop(struct context * context)
{ while (!WindowShouldClose())
  { SetTargetFPS(IsWindowFocused() ? 60 : 10);
    UpdateContext(context);
    { BeginDrawing();
      RenderContext(context);
    } EndDrawing();
  }
}
static inline void PostdeinitContext(void)
{ CloseAudioDevice();
  CloseWindow();
}
