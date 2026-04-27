#define MAGIC_SPEED 330
static inline void InitContext(struct context * context);
static inline void DeinitContext(struct context * context);
static inline void Die(struct context * context)
{ DeinitContext(context);
  InitContext(context);
}
static inline void UpdatePlayerInput(struct context * context)
{ if (IsGamepadAvailable(context->gamepad))
  {
    Vector2 lsd =
      { 0.2f, 0.2f /* I have an older controller with drift... */
        /* now I know the industry standard is 0.1f<->0.2f... */
      };
    static Vector2 prior = {0};
    
    Vector2 ls =
      { GetGamepadAxisMovement(context->gamepad, GAMEPAD_AXIS_LEFT_X),
        GetGamepadAxisMovement(context->gamepad, GAMEPAD_AXIS_LEFT_Y)
      };

    if (ls.x > -lsd.x && ls.x < lsd.x) ls.x = 0;
    if (ls.y > -lsd.y && ls.y < lsd.y) ls.y = 0;
    if (ls.x >= lsd.x
    ||  prior.x) context->player->move.x = ls.x;
    if (ls.y >= lsd.y
    ||  prior.y) context->player->move.y = ls.y;

    prior = (Vector2) { ls.x, ls.y };
  }
  if (duokey(IsKeyPressed, LEFT)
  ||  IsGamepadButtonPressed(context->gamepad, context->gconfig[L_LEFT]))
  { context->player->move.x = -1;
  }
  if (duokey(IsKeyPressed, RIGHT)
  ||  IsGamepadButtonPressed(context->gamepad, context->gconfig[L_RIGHT]))
  { context->player->move.x =  1;
  }
  if (duokey(IsKeyPressed, UP)
  ||  IsGamepadButtonPressed(context->gamepad, context->gconfig[L_UP]))
  { context->player->move.y = -1;
  }
  if (duokey(IsKeyPressed, DOWN)
  ||  IsGamepadButtonPressed(context->gamepad, context->gconfig[L_DOWN]))
  { context->player->move.y =  1;
  }
  if ((duokey(IsKeyReleased, LEFT)
  ||   IsGamepadButtonReleased(context->gamepad, context->gconfig[L_LEFT]))
  &&   context->player->move.x < 0)
  { context->player->move.x  = (duokey(IsKeyDown, RIGHT) || IsGamepadButtonDown(context->gamepad, context->gconfig[L_LEFT])) ? -context->player->move.x : 0;
  }
  if ((duokey(IsKeyReleased, RIGHT)
  ||   IsGamepadButtonReleased(context->gamepad, context->gconfig[L_RIGHT]))
  &&   context->player->move.x > 0)
  { context->player->move.x  = (duokey(IsKeyDown, LEFT) || IsGamepadButtonDown(context->gamepad, context->gconfig[L_RIGHT])) ? -context->player->move.x : 0;
  }
  if ((duokey(IsKeyReleased, UP)
  ||   IsGamepadButtonReleased(context->gamepad, context->gconfig[L_UP]))
  &&   context->player->move.y < 0)
  { context->player->move.y  = (duokey(IsKeyDown, DOWN) || IsGamepadButtonDown(context->gamepad, context->gconfig[L_UP])) ? -context->player->move.y : 0;
  }
  if ((duokey(IsKeyReleased, DOWN)
  ||   IsGamepadButtonReleased(context->gamepad, context->gconfig[L_DOWN]))
  &&   context->player->move.y > 0)
  { context->player->move.y  = (duokey(IsKeyDown, UP) || IsGamepadButtonDown(context->gamepad, context->gconfig[L_DOWN])) ? -context->player->move.y : 0;
  }
  if (duokey(IsKeyPressed, SLOW)
  ||  IsGamepadButtonPressed(context->gamepad, L_TRIGGER))
  { context->player->speed = MAGIC_SPEED / context->player->slow_ratio;
  }
  if (duokey(IsKeyReleased, SLOW)
  ||  IsGamepadButtonReleased(context->gamepad, L_TRIGGER))
  { context->player->speed = MAGIC_SPEED;
  }
  if (duokey(IsKeyPressed, BOMB)
  ||  IsGamepadButtonPressed(context->gamepad, R_UP))
  { context->bullet.group_used = 0;
    #define MAGIC_FLASH 1.2
    context->effects->flash = MAGIC_FLASH;
  }
  if (duokey(IsKeyPressed, FIRE)
  ||  IsGamepadButtonPressed(context->gamepad, R_TRIGGER))
  { 
  }
  if (duokey(IsKeyReleased, FIRE)
  ||  IsGamepadButtonReleased(context->gamepad, R_TRIGGER))
  { 
  }
  context->player->position.x += context->delta * context->player->speed * context->player->move.x;
  context->player->position.y += context->delta * context->player->speed * context->player->move.y;
  if (IsKeyPressed(KEY_F1)) Die(context);
  if (context->player->position.x + context->texture[CIRNO].width / 2 > GAME_AREA)
  { context->player->position.x = GAME_AREA - context->texture[CIRNO].width / 2;
  }
  if (context->player->position.x - context->texture[CIRNO].width / 2 < 0)
  { context->player->position.x = 0 + context->texture[CIRNO].width / 2;
  }
  if (context->player->position.y + context->texture[CIRNO].height / 2 > GAME_AREA)
  { context->player->position.y = GAME_AREA - context->texture[CIRNO].height / 2;
  }
  if (context->player->position.y - context->texture[CIRNO].height / 2 < 0)
  { context->player->position.y = 0 + context->texture[CIRNO].height / 2;
  }
}
static inline void UpdatePlayer(struct context * context)
{ if (context->effects->flash > 0)
  { context->effects->flash -= context->delta;
  }
  UpdatePlayerInput(context);
  if (context->player->invuln > 0)
  { context->player->invuln -= context->delta;
  }
  #define MAGIC_PLAYER_RADIUS 3
  #define MAGIC_INVULN_TIME 70
  int i, j;
  size_t size_map[] = { 32, 24, 20, 16, 12, 8 };
  struct bullet * b = &context->bullet;
  for (i = 0; i < b->group_used; ++i)
  { if (b->ttl[i]
    && b->hurts[i]
    && context->player->invuln <= 0)
    for (j = 0; j < b->count[i]; ++j)
    { if (CheckCollisionCircles((Vector2) { b->x[j], b->y[j] }, size_map[b->size[i]-B32]/2, context->player->position, MAGIC_PLAYER_RADIUS))
      { context->player->invuln = MAGIC_INVULN_TIME;
        if (!context->player->health)
        { Die(context);
        }
        --context->player->health;
        goto freedom;
      }
    }
  }
 freedom:
}
static inline void RenderPlayer(struct context * context)
{ Color damage = ColorAlpha(WHITE, context->player->invuln ? 1 / (context->player->invuln % 10) : 1);
  DrawCentered(context->texture + CIRNO, context->player->position, fmod(context->time, context->effects->player_flip_speed) > context->effects->player_flip_speed / 2,
               0, damage);
  if (duokey(IsKeyDown, SLOW))
  { DrawCentered(context->texture + B20, context->player->position, 0, fmodf(context->time, 2), damage);
  }
  Color color = GREEN;
  DrawRectangleLinesEx((Rectangle) { 0, 0, GAME_AREA, GAME_AREA }, 6 - context->player->health, (Color) {255 - context->player->health * 85, context->player->health * 85, 0,
                                                                                                         damage.a < 100 ? 100 : 175});
}
static inline void InitPlayer(struct context * context)
{ int kconfig[] =
  { KEY_A, KEY_LEFT,
    KEY_D, KEY_RIGHT,
    KEY_W, KEY_UP,
    KEY_S, KEY_DOWN,
    KEY_LEFT_SHIFT, KEY_RIGHT_SHIFT,
    KEY_Z, KEY_SPACE,
    KEY_B, KEY_F,
  };
  int gconfig[] =
  { GAMEPAD_BUTTON_MIDDLE_RIGHT,
    GAMEPAD_BUTTON_MIDDLE_LEFT,
    GAMEPAD_BUTTON_LEFT_FACE_LEFT,
    GAMEPAD_BUTTON_LEFT_FACE_RIGHT,
    GAMEPAD_BUTTON_LEFT_FACE_UP,
    GAMEPAD_BUTTON_LEFT_FACE_DOWN,
    GAMEPAD_BUTTON_RIGHT_FACE_LEFT,
    GAMEPAD_BUTTON_RIGHT_FACE_RIGHT,
    GAMEPAD_BUTTON_RIGHT_FACE_UP,
    GAMEPAD_BUTTON_RIGHT_FACE_DOWN,
    GAMEPAD_BUTTON_LEFT_TRIGGER_1,
    GAMEPAD_BUTTON_RIGHT_TRIGGER_1,
  };
  memcpy(context->kconfig, kconfig, sizeof(kconfig) / sizeof(*kconfig) * sizeof(int));
  memcpy(context->gconfig, gconfig, sizeof(gconfig) / sizeof(*gconfig) * sizeof(int));
  context->player->position = (Vector2) { GAME_AREA/2, GAME_AREA - GAME_AREA/4 };
  context->player->speed = MAGIC_SPEED;
  context->player->health = 3;
  context->player->spell = 3;
  context->player->slow_ratio = 3;
  context->effects->player_flip_speed = 100;
}
