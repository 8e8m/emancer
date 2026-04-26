static inline Vector3 BulletDelta(Vector3 o, Vector3 d)
{ return (Vector3)
    { o.x + d.x * cosf(o.z) - d.y * sinf(o.z),
      o.y + d.y * sinf(o.z) + d.y * cosf(o.z),
      fmod((o.z + d.z), 2)
    };
}
/*
 * Closest point on segment AB to point P, returns squared distance.
 * Also writes the closest point into (cx, cy) if you need it later.
 */
static inline float segment_point_dist2(
                                        float ax, float ay,
                                        float bx, float by,
                                        float px, float py)
{
  float abx = bx - ax, aby = by - ay;
  float apx = px - ax, apy = py - ay;
  float ab2 = abx*abx + aby*aby;
  float t   = (ab2 > 1e-9f) ? (apx*abx + apy*aby) / ab2 : 0.0f;
  if (t < 0.0f) t = 0.0f;
  if (t > 1.0f) t = 1.0f;
  float nx = ax + t*abx - px;
  float ny = ay + t*aby - py;
  return nx*nx + ny*ny;
}
static inline bool BulletIntersect(struct bullet * b, Vector2 position, float radius)
{ float bloodtype[B8-B32+1] = {32, 24, 20, 16, 12, 8}; 
  float br     = bloodtype[b->type-B32];
  float touch  = br + (float)radius;      /* sum of radii          */
  float touch2 = touch * touch;           /* compare squared, skip sqrt */

  float px = position.x;
  float py = position.y;

  if (fabsf(b->dr) < 1e-6f) {
    /*
     * ── Straight bullets ──────────────────────────────────────────
     * All c bullet positions lie on the segment [origin → end].
     * A circle intersects that segment iff its center is within
     * (br + radius) of the nearest point on the segment — a capsule test.
     * O(1) regardless of c.
     */
    float ex = b->ox + b->dx * (float)(b->c - 1);
    float ey = b->oy + b->dy * (float)(b->c - 1);

    return segment_point_dist2(b->ox, b->oy, ex, ey, px, py) < touch2;

  } else {
    /*
     * ── Curving bullets ───────────────────────────────────────────
     * Each step the velocity vector rotates by dr radians.
     * Position at step i cannot be reduced to a simple segment,
     * so we walk the arc.
     *
     * Velocity at step 0  = (dx, dy)
     * Velocity at step i  = rotate((dx,dy), dr * i)
     * We iterate, rotating cheaply with a cached (cos, sin).
     *
     * For large c you could use the closed-form arc midpoint trick
     * from the earlier discussion, but for typical bullet counts
     * (<256) this is plenty fast and stays branchless inside.
     */
    float cos_dr = cosf(b->dr);
    float sin_dr = sinf(b->dr);
    float vx = b->dx;
    float vy = b->dy;
    float x  = b->ox;
    float y  = b->oy;

    for (size_t i = 0; i < b->c; i++) {
      float nx = x - px;
      float ny = y - py;
      if (nx*nx + ny*ny < touch2) return true;

      /* Advance: apply current velocity, then rotate for next step */
      x += vx;
      y += vy;
      float nvx = vx*cos_dr - vy*sin_dr;
      float nvy = vx*sin_dr + vy*cos_dr;
      vx = nvx;
      vy = nvy;
    }
    return false;
  }
}
static inline void UpdateBullet(struct context * context)
{ for (int i = 0; i < BULLET_GROUPS; ++i)
  { struct bullet * b = &context->bullet[i];
    if (b->ttl)
    { --b->ttl;
      Vector3 v = BulletDelta((Vector3) { b->ox, b->oy, b->or },
                              (Vector3) { b->dx, b->dy, b->dr });
      b->ox = v.x;
      b->oy = v.y;
      b->or = v.z;
    }
  }
}
static inline void RenderBullet(struct context * context)
{ Vector3 v;
  struct bullet * b;
  for (int i = 0; i < BULLET_GROUPS; ++i)
  { b = &context->bullet[i];
    if (b->ttl)
    { v = (Vector3) { b->ox, b->oy, b->or };
      DrawTexture(context->texture[b->type], v.x, v.y, b->color);
      for (int j = 0; j < b->c; ++j) {
        DrawTexture(context->texture[b->type], v.x, v.y, b->color);
        for (int k = 0; k < b->interval; ++k)
        { v = BulletDelta(v,
                          (Vector3) { b->dx, b->dy, b->dr });
        }
      }
    }
  }
}
static inline void InitBullet(struct context * context)
{ for (int i = 0; i < BULLET_GROUPS; ++i)
  { struct bullet * b = &context->bullet[i];
    b->ttl = 1000;
    b->type = B32;
    b->hurts = 1;
    b->color = RED;
    b->ox = rand() % GAME_AREA;
    b->dx = rand() % 10 - 5 + 1;
    b->oy = rand() % GAME_AREA;
    b->dy = rand() % 10 - 5 + 1;
    b->or = 0;
    b->dr = 0.01f;
    b->interval = rand() % 50 + 25;
    b->c = 100;
  }
}
