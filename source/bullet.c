static inline void DefaultVisual(struct context * context, int size, Color color)
{ struct bullet * b = &context->bullet;
  for (size_t i = 0; i < GROUP_LIMIT; ++i)
  { b->color[i] = color;
    b->size[i] = size;
  }
}
static inline void Visual(struct context * context, int size, Color color)
{ struct bullet * b = &context->bullet;
  b->color[b->group_used] = color;
  b->size[b->group_used] = size;
}
static inline void Group(struct context * context, size_t count, Vector3 start, Vector3 offset, Vector3 delta, unsigned ttl)
{ struct bullet * b = &context->bullet;
  size_t i, first = b->group_used ? b->count[b->group_used-1] : 0;
  if (b->group_used >= GROUP_LIMIT) { return; }
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
static inline void ShootAt(struct context * context, Vector2 position, size_t group, float speed)
{ struct bullet * b = &context->bullet;
  size_t start = group != 0 ? b->count[group-1] : 0;
  float px = position.x;
  float py = position.y;
  for (size_t j = start; j < b->count[group]; ++j)
  { b->r[j] = atan2f(py - b->y[j], px - b->x[j]);
  }
  b->dx[group] = speed;
  b->dy[group] = 0;
}
static inline void UpdateBullet(struct context * context)
{ size_t i, j;
  struct bullet * b = &context->bullet;
  size_t size_map[] = { 32, 24, 20, 16, 12, 8 };
  for (i = 0; i < b->group_used; ++i)
  { if (b->ttl[i])
    { if (b->hurts[i] < 1
      &&  b->ttl[i] - 160 > context->time)
      { b->hurts[i] += 0.0075f;
      }
      else if (b->hurts[i] > 0)
      { b->hurts[i] -= 0.01f;
      }
      for (j = i != 0 ? b->count[i-1] : 0; j < b->count[i]; ++j)
      { b->x[j] += b->dx[i] * cosf(b->r[j]) - b->dy[i] * sinf(b->r[j]);
        b->y[j] += b->dx[i] * sinf(b->r[j]) + b->dy[i] * cosf(b->r[j]);
        b->r[j] += b->dr[i];
        size_t size = b->size[i] - B32;
        size = size < sizeof(size_map) / sizeof(*size_map) ? size_map[size] : 0;
        b->x[j] = fmodf(b->x[j], GAME_AREA);
        if (b->x[j] < 0) b->x[j] += GAME_AREA;
        b->y[j] = fmodf(b->y[j], GAME_AREA);
        if (b->y[j] < 0) b->y[j] += GAME_AREA;
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
  for (size_t i = 0; i < GROUP_LIMIT; ++i)
  { b->color[i] = BLUE;
    b->hurts[i] = 0;
  }
  b->group_used = 0;
  DefaultVisual(context, B24, BLUE);
}
