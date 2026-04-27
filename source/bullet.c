static inline void Linear(struct context * context, Vector2 vector, Vector2 interval, float radian, size_t count)
{ struct bullet * b = &context->bullet;
  for (size_t i; i < count; ++i)
  { b->x[i] += interval.x * i;
    b->y[i] += interval.y * i;
  }
  b->count[b->group_used] = count;
  b->group_used++;
}
static inline LastVector(struct context * context, size_t ttl, float x, float y, float r, size_t count)
{ struct bullet * b = &context->bullet;
   b->dx[b->group_used] = vector.x;
  b->dy[b->group_used] = vector.y;
  b->dr[b->group_used] = radian;
  b->ttl[b->group_used] = ttl;
}
static inline void UpdateBullet(struct context * context)
{ size_t i, j;
  struct bullet * b = &context->bullet;
  for (i = 0; i < b->group_used; ++i)
  { if (b->ttl[i])
    { b->ttl[i] -= context->delta;
      for (j = 0; j < b->count[i]; ++j)
      { b->x[j] += b->dx[i] * cosf(b->r[j]) - b->dy[i] * sinf(b->r[j]);
        b->y[j] += b->dx[i] * sinf(b->r[j]) + b->dy[i] * cosf(b->r[j]);
        b->r[j] += b->dr[i];
        b->x[j] = fmodf(b->x[j], GAME_AREA);
        if (b->x[j] < 0) b->x[j] = GAME_AREA;
        b->y[j] = fmodf(b->y[j], GAME_AREA);
        if (b->y[j] < 0) b->y[j] = GAME_AREA;
      }
    }
  }
}
static inline void RenderBullet(struct context * context)
{ size_t i, j;
  struct bullet * b = &context->bullet;
  for (i = 0; i < b->group_used; ++i)
  { if (b->ttl[i])
    { for (j = i != 0 ? b->count[i-1] : 0; j < b->count[i]; ++j)
      { DrawCentered(&context->texture[b->size[i]], (Vector2) { b->x[j], b->y[j] }, 0, b->r[j], b->color[i]);
      }
    }
  }
}
static inline void InitBullet(struct context * context)
{ size_t i;
  struct bullet * b = &context->bullet;
  b->group_max = 64;
  b->bullet_max = 2048;
  b->x     = calloc(sizeof(b->x), b->bullet_max);
  b->y     = calloc(sizeof(b->y), b->bullet_max);
  b->r     = calloc(sizeof(b->r), b->bullet_max);
  b->ttl   = calloc(sizeof(b->ttl), b->group_max);
  b->count = calloc(sizeof(b->count), b->group_max);
  b->size  = calloc(sizeof(b->size), b->group_max);
  b->color = calloc(sizeof(b->color), b->group_max);
  b->hurts = calloc(sizeof(b->hurts), b->group_max);
  b->dx = calloc(sizeof(b->dx), b->group_max);
  b->dy = calloc(sizeof(b->dy), b->group_max);
  b->dr = calloc(sizeof(b->dr), b->group_max);
  for (i = 0; i < b->group_max; ++i)
  { b->color[i] = RED;
    b->size[i] = B24;
    b->hurts[i] = 1;
  }

  Linear(context, 3000, (Vector2){20,20}, (Vector2){1, 0}, (Vector2){0, 20}, 0.f, 20);
}
static inline void DeinitBullet(struct context * context)
{ struct bullet * b = &context->bullet;
  free(b->x);
  free(b->y);
  free(b->r);
  free(b->ttl);
  free(b->count);
  free(b->size);
  free(b->color);
  free(b->hurts);
  free(b->dx);
  free(b->dy);
  free(b->dr);
}
