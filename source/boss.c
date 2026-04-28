static inline void Group(struct context * context, size_t count, Vector3 start, Vector3 offset, Vector3 delta, unsigned ttl);
static inline void UpdateBoss(struct context * context)
{ if (context->time >   50 && context->phase == 0) { ++context->phase; Group(context, 55,     (Vector3){20, 20, 0}, (Vector3){20,  20, 0}, (Vector3){0,2,     0}, 10000); }
  if (context->time >  500 && context->phase == 1) { ++context->phase; Group(context, 35,     (Vector3){20, 20, 0}, (Vector3){25,  30, 0}, (Vector3){1,0,     0}, 10000); }
  if (context->time > 1000 && context->phase == 2) { ++context->phase; Group(context, 35,     (Vector3){20, 20, 0}, (Vector3){25,  30, 0}, (Vector3){1,0,0.0001}, 10000); }
  if (context->time > 1500 && context->phase == 3) { ++context->phase; Group(context, 205,    (Vector3){20, 0,  0}, (Vector3){10, 100, 0}, (Vector3){1,0, 0.001}, 10000); }
}
static inline void RestartBoss(struct context * context)
{ context->phase = 0;
}
