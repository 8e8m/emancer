static inline void StopMusic(struct context * context);
static inline void DefaultVisual(struct context * context, int size, Color color);
static inline void Visual(struct context * context, int size, Color color);
static inline void Group(struct context * context, size_t count, Vector3 start, Vector3 offset, Vector3 delta, unsigned ttl);
static inline void ShootAt(struct context * context, Vector2 position, size_t group, float speed);
static inline void RestartBullet(struct context * context);
static inline void UpdateBoss(struct context * context)
{ int require = -1; /* GAMEPLAY: */
  struct bullet * b = &context->bullet; (void) b;
  /* song 1 flan */
  if (context->phase == ++require && context->time > 50)
  { ++context->phase;
    StopMusic(context);
    PlaySound(context->music[FLAN]);
    context->effects->target_background_color = BLUE;
    DefaultVisual(context, B16, BLUE);
    Group(context, 200, (Vector3){GAME_AREA/2, GAME_AREA/4, 1}, (Vector3){5, 20, 0.1}, (Vector3){0,   1, 0 + (rand()%100/1000)}, 1600);
    Group(context, 200, (Vector3){GAME_AREA/2, GAME_AREA/5, 0}, (Vector3){5, 20, 0.1}, (Vector3){0, 1.1, 0.001 + (rand()%100/1000)}, 1600);
  }
  if (context->phase == ++require && context->time >= 1650)
  { ++context->phase;
    RestartBullet(context);
    Group(context, 200, (Vector3){GAME_AREA/2,GAME_AREA/4,1}, (Vector3){5,-20-(rand()%5), 0.1}, (Vector3){0,1,0}, 4200);
  }
  if (context->phase == ++require && context->time >= 2750)
  { ++context->phase;
    Group(context, 200, (Vector3){GAME_AREA/(rand()%3+2),GAME_AREA,1}, (Vector3){5,-30, 0.1}, (Vector3){0,-1,0.0001}, 4200);
  }
  if (context->phase == ++require && context->time >= 4250)
  { ++context->phase;
    RestartBullet(context);
    DefaultVisual(context, B20, BLUE);
    Group(context, 500, (Vector3){GAME_AREA/2,GAME_AREA/4,1}, (Vector3){5,-200, 0.1}, (Vector3){0.1,0.5,0.0001}, 8000);
  }
  if (context->phase == ++require && context->time >= 7250)
  { ++context->phase;
    Group(context, 500, (Vector3){GAME_AREA/2,GAME_AREA/4,1}, (Vector3){5,-200, 0.1}, (Vector3){0.1,0.5,0.0001}, 8000);
  }
  if (context->phase == ++require && context->time >= 8050)
  { ++context->phase;
    PlayerHeal(context);
    RestartBullet(context);
    DefaultVisual(context, B24, BLUE);
    Group(context, 500, (Vector3){0, 0,1}, (Vector3){5, 20, 0}, (Vector3){0.1, 2, 0}, 12000);
    Group(context, 300, (Vector3){0, 50,1}, (Vector3){5, 20, 0}, (Vector3){0.11, 2.01, 0}, 12000);
  }
  if (context->phase == ++require && context->time >= 9850)
  { ++context->phase;
    Group(context, 200, (Vector3){0, 0, 1}, (Vector3){30, 15, 0}, (Vector3){-1.5, -0.1, 0}, 12000);
    Group(context, 200, (Vector3){0, 50, 1}, (Vector3){30, 15, 0}, (Vector3){-1.3, -0.1, 0}, 12000);
  }
  if (context->phase == ++require && context->time >= 10950)
  { ++context->phase;
    Group(context, 200, (Vector3){0, 100, 1}, (Vector3){30, 15, 0}, (Vector3){-1, -0.1, 0}, 12000);
    Group(context, 200, (Vector3){0, 200, 1}, (Vector3){30, 15, 0}, (Vector3){-1, -0.1, 0}, 12000);
    Group(context, 200, (Vector3){0, 250, 1}, (Vector3){30, 15, 0}, (Vector3){-1, -0.1, 0}, 12000);
  }
  /* song 2 sakuya */
  if (context->phase == ++require && context->time >= 12120)
  { ++context->phase;
    StopMusic(context);
    PlaySound(context->music[SAKUYA]);
    context->effects->target_background_color = RED;
    PlayerHeal(context);
    RestartBullet(context);
    DefaultVisual(context, B32, RED);
    Group(context, 50, (Vector3){GAME_AREA/3, GAME_AREA/3, 1}, (Vector3){15, -1, 0}, (Vector3){-0.01, -0.01, 0}, 14500);
    Group(context, 50, (Vector3){GAME_AREA - GAME_AREA/3, GAME_AREA/3, 1}, (Vector3){-15, -1, 0}, (Vector3){0.01, 0.01, 0}, 14500);
    Group(context, 50, (Vector3){GAME_AREA/4, GAME_AREA/4, 1}, (Vector3){15, -1, 0}, (Vector3){-0.01, -0.01, 0}, 14500);
    Group(context, 50, (Vector3){GAME_AREA - GAME_AREA/4, GAME_AREA/4, 1}, (Vector3){-10, -1, 0}, (Vector3){0.01, 0.01, 0}, 14500);
  }
  if (context->phase == ++require && context->time >= 12300)
  { ShootAt(context, context->player->position, b->group_used-3, 2);
    ShootAt(context, context->player->position, b->group_used-4, 2);
  }
  if (context->phase == require && context->time >= 12330)
  { ++context->phase;
  }
  if (context->phase == ++require && context->time >= 12350)
  { ShootAt(context, context->player->position, b->group_used-1, 4);
    ShootAt(context, context->player->position, b->group_used-2, 4);
  }
  if (context->phase == require && context->time >= 12370)
  { ++context->phase;
  }
  if (context->phase == ++require && context->time >= 14500)
  { ++context->phase;
    RestartBullet(context);
    DefaultVisual(context, B20, RED);
    Group(context, BULLET_LIMIT/2, (Vector3){0, 0, 1}, (Vector3){15, 10, 0.1}, (Vector3){0, 1, 0.01}, 16600);
    Group(context, BULLET_LIMIT/2, (Vector3){0, 0, 0}, (Vector3){150, 10, 1}, (Vector3){1, 0, 0}, 16600);
  }
  if (context->phase == ++require && context->time >= 14550)
  { ++context->phase;
    b->dx[b->group_used-1] = 2;
    b->dy[b->group_used-1] = 0;
    b->dr[b->group_used-1] = 1;
  }
  if (context->phase == ++require && context->time >= 16650)
  { ++context->phase;
    context->thanks = 1;
  }
  if (context->phase == ++require && context->time >= 16700)
  { ++context->phase;
    RestartBullet(context);
    printf("BLEH.\n");
    Group(context, BULLET_LIMIT/2, (Vector3){0, 0, 1}, (Vector3){-15, -10, 1}, (Vector3){18, 0.0001, 0.008}, 300000);
    Group(context, BULLET_LIMIT/2, (Vector3){0, 0, 1}, (Vector3){-10, -15, 1}, (Vector3){0.0001, -18.00, 0.00}, 300000);
  }
  /* END GAMEPLAY. */
}
static inline void RestartBoss(struct context * context)
{ context->phase = 0;
  context->time = 0;
  context->thanks = 0;
}
