static inline void DefaultVisual(struct context * context, int size, Color color);
static inline void Visual(struct context * context, int size, Color color);
static inline void Group(struct context * context, size_t count, Vector3 start, Vector3 offset, Vector3 delta, unsigned ttl);
static inline void ShootAt(struct context * context, Vector2 position, size_t group, float speed);
static inline void RestartBullet(struct context * context);
static inline void UpdateBoss(struct context * context)
{ int require = -1; /* GAMEPLAY: */
  struct bullet * b = &context->bullet; (void) b;
  /* song 1 flan */
  if (context->time > 50 && context->phase == ++require)
  { ++context->phase;
    context->effects->target_background_color = BLUE;
    Group(context, 250, (Vector3){GAME_AREA/2, GAME_AREA/4, 1}, (Vector3){5, 20, 0.1}, (Vector3){0,   1, 0}, 1600);
    Group(context, 150, (Vector3){GAME_AREA/2, GAME_AREA/5, 0}, (Vector3){5, 20, 0.1}, (Vector3){0, 1.1, 0.001}, 1600);
  }
  if (context->time >= 1600 && context->phase == ++require)
  { ++context->phase;
    Group(context, 200, (Vector3){GAME_AREA/2,GAME_AREA/4,1}, (Vector3){5,-20, 0.1}, (Vector3){0,1,0}, 2700);
  }
  if (context->time >= 2700 && context->phase == ++require)
  { ++context->phase;
    Group(context, 200, (Vector3){GAME_AREA/3,GAME_AREA,1}, (Vector3){5,-30, 0.1}, (Vector3){0,-1,0.0001}, 4200);
  }
  if (context->time >= 4200 && context->phase == ++require)
  { ++context->phase;
    DefaultVisual(context, B20, BLUE);
    Group(context, 500, (Vector3){GAME_AREA/2,GAME_AREA/4,1}, (Vector3){5,-200, 0.1}, (Vector3){0.1,0.5,0.0001}, 7200);
  }
  if (context->time >= 6600 && context->phase == ++require)
  { ++context->phase;
    Group(context, 500, (Vector3){GAME_AREA/2,GAME_AREA/4,1}, (Vector3){5,-200, 0.1}, (Vector3){0.1,0.5,0.0001}, 7200);
  }
  if (context->time >= 7200 && context->phase == ++require)
  { ++context->phase;
    PlayerHeal(context);
    DefaultVisual(context, B24, BLUE);
    Group(context, 500, (Vector3){0, 0,1}, (Vector3){5, 20, 0}, (Vector3){0.1, 2, 0}, 12000);
    Group(context, 300, (Vector3){0, 50,1}, (Vector3){5, 20, 0}, (Vector3){0.11, 2.01, 0}, 12000);
  }
  if (context->time >= 9900 && context->phase == ++require)
  { ++context->phase;
    Group(context, 200, (Vector3){0, 0, 1}, (Vector3){30, 15, 0}, (Vector3){-1.5, -0.1, 0}, 12000);
    Group(context, 200, (Vector3){0, 50, 1}, (Vector3){30, 15, 0}, (Vector3){-1.3, -0.1, 0}, 12000);
  }
  if (context->time >= 11000 && context->phase == ++require)
  { ++context->phase;
    Group(context, 200, (Vector3){0, 100, 1}, (Vector3){30, 15, 0}, (Vector3){-1, -0.1, 0}, 12000);
    Group(context, 200, (Vector3){0, 200, 1}, (Vector3){30, 15, 0}, (Vector3){-1, -0.1, 0}, 12000);
    Group(context, 200, (Vector3){0, 250, 1}, (Vector3){30, 15, 0}, (Vector3){-1, -0.1, 0}, 12000);
  }
  /* song 2 sakuya */
  if (context->time >= 12001 && context->phase == ++require)
  { ++context->phase;
    context->effects->target_background_color = RED;
    PlayerHeal(context);
    RestartBullet(context);
    DefaultVisual(context, B32, RED);
    Group(context, 30, (Vector3){GAME_AREA/3, GAME_AREA/3, 1}, (Vector3){15, -1, 0}, (Vector3){-0.01, -0.01, 0}, 13000);
    Group(context, 30, (Vector3){GAME_AREA - GAME_AREA/3, GAME_AREA/3, 1}, (Vector3){-15, -1, 0}, (Vector3){0.01, 0.01, 0}, 13000);
  }
  if (context->time >= 12300 && context->phase == ++require)
  { ShootAt(context, context->player->position, b->group_used-1, 6);
    ShootAt(context, context->player->position, b->group_used-2, 6);
  }
  if (context->time >= 12350 && context->phase == require)
  { ++context->phase;
  }
  /* END GAMEPLAY. */
}
static inline void RestartBoss(struct context * context)
{ context->phase = 0;
}
