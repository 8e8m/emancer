static inline void Group(struct context * context, size_t count, Vector3 start, Vector3 offset, Vector3 delta, unsigned ttl)
{ struct bullet * b = &context->bullet;
  size_t i, first = b->group_used ? b->count[b->group_used-1] : 0;
  if (b->group_used >= b->group_max) { return; }
  b->count[b->group_used] = count + first;
  for (i = first; i < b->count[b->group_used]; ++i)
  { b->x[i] = start.x + (i - first) * offset.x;
    b->y[i] = start.y + (i - first) * offset.y;
    b->r[i] = start.z + (i - first) * offset.z;
  }
  b->dx[b->group_used] = delta.x;
  b->dy[b->group_used] = delta.y;
  b->dr[b->group_used] = delta.z;
  b->ttl[b->group_used] = ttl;
  b->group_used++;
}
static inline void UpdateBullet(struct context * context)
{ size_t i, j;
  struct bullet * b = &context->bullet;
  size_t size_map[] = { 32, 24, 20, 16, 12, 8 };
  for (i = 0; i < b->group_used; ++i)
  { if (b->ttl[i])
    { b->ttl[i] -= context->delta;
      if (i == b->group_used-1
      &&  b->ttl[i] <= 0)
      { --b->group_used;
      }
      if (b->hurts[i] < 1)
      { b->hurts[i] += 0.01;
      }
      for (j = i != 0 ? b->count[i-1] : 0; j < b->count[i]; ++j)
      { b->x[j] += b->dx[i] * cosf(b->r[j]) - b->dy[i] * sinf(b->r[j]);
        b->y[j] += b->dx[i] * sinf(b->r[j]) + b->dy[i] * cosf(b->r[j]);
        b->r[j] += b->dr[i];
        size_t size = (size_t) b->size[i] < sizeof(size_map) / sizeof(*size_map) ? b->size[i] : 0;
        if (b->x[j] > GAME_AREA + size)
        { b->x[j] = fmodf(b->x[j], GAME_AREA);
        }
        if (b->x[j] <             size)
        { b->x[j] = fmodf(b->x[j], GAME_AREA);
        }
        if (b->y[j] > GAME_AREA + size)
        { b->y[j] = fmodf(b->y[j], GAME_AREA);
        }
        if (b->y[j] <             size)
        { b->y[j] = fmodf(b->y[j], GAME_AREA);
        }
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
      { DrawCenteredWrapped(&context->texture[b->size[i]], (Vector2) { b->x[j], b->y[j] }, 0, b->r[j], ColorAlpha(b->color[i], b->hurts[i]));
      }
    }
  }
}
static inline void RestartBullet(struct context * context)
{ struct bullet * b = &context->bullet;
  for (size_t i = 0; i < b->group_max; ++i)
  { b->color[i] = RED;
    b->size[i] = B24;
    b->hurts[i] = 0;
  }
  b->group_used = 0;
}
static inline void InitBullet(struct context * context)
{ struct bullet * b = &context->bullet;
  b->group_max = 64;
  b->bullet_max = 2048;
  b->x     = calloc(b->bullet_max, sizeof(b->x));
  b->y     = calloc(b->bullet_max, sizeof(b->y));
  b->r     = calloc(b->bullet_max, sizeof(b->r));
  b->ttl   = calloc(b->group_max, sizeof(b->ttl));
  b->tm    = calloc(b->group_max, sizeof(b->tm));
  b->count = calloc(b->group_max, sizeof(b->count));
  b->size  = calloc(b->group_max, sizeof(b->size));
  b->color = calloc(b->group_max, sizeof(b->color));
  b->hurts = calloc(b->group_max, sizeof(b->hurts));
  b->dx = calloc(b->group_max, sizeof(b->dx));
  b->dy = calloc(b->group_max, sizeof(b->dy));
  b->dr = calloc(b->group_max, sizeof(b->dr));
}
static inline void DeinitBullet(struct context * context)
{ struct bullet * b = &context->bullet;
  free(b->x);
  free(b->y);
  free(b->r);
  free(b->ttl);
  free(b->tm);
  free(b->count);
  free(b->size);
  free(b->color);
  free(b->hurts);
  free(b->dx);
  free(b->dy);
  free(b->dr);
}
