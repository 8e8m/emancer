static inline void DefaultVisual(struct context * context, int size, Color color);
static inline void Visual(struct context * context, int size, Color color);
static inline void Group(struct context * context, size_t count, Vector3 start, Vector3 offset, Vector3 delta, unsigned ttl);
static inline void RestartBullet(struct context * context);
static inline void UpdateBoss(struct context * context)
{ int require = 0; /* GAMEPLAY: */
  struct bullet * b = &context->bullet; (void) b;
  /* flan */
  /* song 1 flan
     time 693.284790
     time 848.392090
     time 1603.466187
     time 1678.325806
     time 2830.225098
     time 2926.721680
     time 4155.109375
     time 5356.948242
     time 5394.999023
     time 6668.221680
     time 7269.838867
     time 7286.807617
     time 9773.407227
     time 9915.417969
   */
  if (context->time > 50 && context->phase == require)
  { ++context->phase;
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
    DefaultVisual(context, B24, BLUE);
    Group(context, 500, (Vector3){0, 0,1}, (Vector3){5, 20, 0}, (Vector3){0.1, 1, 0}, 12000);
  }
  if (context->time >= 9900 && context->phase == ++require)
  { ++context->phase;
    Group(context, 200, (Vector3){0, 0, 1}, (Vector3){30, 15, 0}, (Vector3){-1, -0.1, 0}, 12000);
    Group(context, 200, (Vector3){0, 50, 1}, (Vector3){30, 15, 0}, (Vector3){-1, -0.1, 0}, 12000);
  }
  if (context->time >= 11000 && context->phase == ++require)
  { ++context->phase;
    Group(context, 200, (Vector3){0, 100, 1}, (Vector3){30, 15, 0}, (Vector3){-1, -0.1, 0}, 12000);
    Group(context, 200, (Vector3){0, 200, 1}, (Vector3){30, 15, 0}, (Vector3){-1, -0.1, 0}, 12000);
    Group(context, 200, (Vector3){0, 250, 1}, (Vector3){30, 15, 0}, (Vector3){-1, -0.1, 0}, 12000);
  }
  /* song 2 sakuya */
  if (context->time >= 12000 && context->phase == ++require)
  { ++context->phase;
    DefaultVisual(context, B32, RED);
    Group(context, 30, (Vector3){GAME_AREA/3, GAME_AREA/3, 1}, (Vector3){15, -1, 0}, (Vector3){-0.01, -0.01, 0}, 12000);
    Group(context, 30, (Vector3){GAME_AREA - GAME_AREA/3, GAME_AREA/3, 1}, (Vector3){-15, -1, 0}, (Vector3){0.01, 0.01, 0}, 12000);
  }
  if (context->time >= 12300 && context->phase == ++require)
  { ++context->phase;
  }
  /* END GAMEPLAY. */
}
static inline void RestartBoss(struct context * context)
{ context->phase = 0;
}
