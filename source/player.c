static inline void RestartContext(struct context * context);
static inline void Die(struct context * context)
{ PlaySound(context->sound[DEATH_SOUND]);
  RestartContext(context);
}
static inline void PlayerHeal(struct context * context)
{ if (context->player->health < MAGIC_HEALTH) ++context->player->health;
  if (context->player->bomb < MAGIC_BOMB) ++context->player->bomb;
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
  ||  IsGamepadButtonPressed(context->gamepad, context->gconfig[R_DOWN]))
  { context->player->speed = MAGIC_SPEED / context->player->slow_ratio;
  }
  if (duokey(IsKeyReleased, SLOW)
  ||  IsGamepadButtonReleased(context->gamepad, context->gconfig[R_DOWN]))
  { context->player->speed = MAGIC_SPEED;
  }
  if (context->player->bomb
   && (duokey(IsKeyPressed, BOMB)
      ||  IsGamepadButtonPressed(context->gamepad, context->gconfig[R_LEFT]))
      )
  { context->player->invuln = 200;
    context->effects->flash = MAGIC_FLASH;
    context->player->bomb--;
    PlaySound(context->sound[WHISTLE_SOUND]);
  }
  if (IsKeyPressed(KEY_T))
  { printf("time %f\n", context->time);
  }
  context->player->position.x += context->delta * context->player->speed * context->player->move.x;
  context->player->position.y += context->delta * context->player->speed * context->player->move.y;
  if (duokey(IsKeyPressed, RESTART)
  ||  IsGamepadButtonPressed(context->gamepad, context->gconfig[START])) Die(context);
  if (context->player->position.x > GAME_AREA) context->player->position.x -= GAME_AREA;
  if (context->player->position.x < 0)         context->player->position.x += GAME_AREA;
  if (context->player->position.y > GAME_AREA) context->player->position.y -= GAME_AREA;
  if (context->player->position.y < 0)         context->player->position.y += GAME_AREA;
}
static inline void UpdatePlayer(struct context * context)
{ if (context->effects->flash > 0)
  { context->effects->flash -= context->delta;
  }
  UpdatePlayerInput(context);
  if (context->player->invuln > 0)
  { context->player->invuln -= context->delta;
  }
  size_t i, j;
  size_t size_map[] = { 32, 24, 20, 16, 12, 8 };
  struct bullet * b = &context->bullet;
  for (i = 0; i < b->group_used; ++i)
  { if (b->ttl[i]
    && b->hurts[i] > 0.99
    && context->player->invuln <= 0)
    for (j = i != 0 ? b->count[i-1] : 0; j < b->count[i]; ++j)
    { if (CheckCollisionCircles((Vector2) { b->x[j], b->y[j] }, size_map[b->size[i]-B32]/3, context->player->position, MAGIC_PLAYER_RADIUS))
      { context->player->invuln = MAGIC_INVULN_TIME;
        if (!context->player->health)
        { Die(context);
        }
        PlaySound(context->sound[HIT_SOUND]);
        --context->player->health;
        goto freedom;
      }
    }
  }
 freedom:
}
static inline void RenderPlayer(struct context * context)
{ Color damage = ColorAlpha(WHITE, context->player->invuln ? 1 / (context->player->invuln % 10) : 1);
  DrawCenteredWrapped(context->texture + CIRNO, context->player->position, fmod(context->time, context->effects->player_flip_speed) > context->effects->player_flip_speed / 2,
               0, damage);
  DrawCenteredWrapped(context->texture + B20, context->player->position, 0, fmodf(context->time, 2), ColorAlpha(damage, context->player->speed != MAGIC_SPEED ? 1 : 0.5));
  DrawRectangleLinesEx((Rectangle) { 0, 0, GAME_AREA, GAME_AREA }, 9 - context->player->health, (Color) {255 - context->player->health * 85, context->player->health * 85, 0, damage.a < 100 ? 100 : 175});
  DrawRectangleLinesEx((Rectangle) { 0, 0, GAME_AREA, GAME_AREA }, context->player->bomb + 1, (Color) {20, 0, 84 * context->player->bomb, context->effects->flash > 0 ? 100 : 255});
}
#if (MAGIC_HEALTH > 3 || MAGIC_BOMB > 3) && !defined(NO_IM_NOT)
#error CUCK
#endif
static inline void RestartPlayer(struct context * context)
{ context->player->position = (Vector2) { GAME_AREA/2, GAME_AREA - GAME_AREA/4 };
  context->player->speed = MAGIC_SPEED;
  context->player->health = MAGIC_HEALTH;
  context->player->bomb = MAGIC_BOMB;
  context->player->slow_ratio = 1.75;
  context->effects->player_flip_speed = 100;
  context->effects->flash = 0;
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
    KEY_R, KEY_F1,
  };
  int gconfig[] =
  { GAMEPAD_BUTTON_MIDDLE_RIGHT,
    GAMEPAD_BUTTON_LEFT_FACE_LEFT,
    GAMEPAD_BUTTON_LEFT_FACE_RIGHT,
    GAMEPAD_BUTTON_LEFT_FACE_UP,
    GAMEPAD_BUTTON_LEFT_FACE_DOWN,
    GAMEPAD_BUTTON_RIGHT_FACE_LEFT,
    GAMEPAD_BUTTON_RIGHT_FACE_RIGHT,
    GAMEPAD_BUTTON_RIGHT_FACE_UP,
    GAMEPAD_BUTTON_RIGHT_FACE_DOWN,
  };
  memcpy(context->kconfig, kconfig, sizeof(kconfig) / sizeof(*kconfig) * sizeof(int));
  memcpy(context->gconfig, gconfig, sizeof(gconfig) / sizeof(*gconfig) * sizeof(int));
}
