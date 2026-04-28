#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
/* change_directory */
#include <sys/stat.h>
#include <unistd.h>
#include <limits.h>
/* collide definition[offset] and definition[offset+1] together */
#define duokey(f,o) ((bool)f((int)context->kconfig[o])|(bool)f((int)context->kconfig[o+1]))
#define public
#define GAME_AREA 1080
/* table of abstracted keyboard input */
/* We'll name this their functionality for sake of usability considering keyboard space is much larger */
enum kconfig
  { /* use duokey */ LEFT=0, RIGHT=2, UP=4, DOWN=6, SLOW=8, FIRE=10, BOMB=12
  };
/* because gamepads are sparse and usually have contextual logic
 * we'll just set it as an abstraction layer that enables remapping.
 * This thinking is technically applicable to keyboards however I don't wish to do that for this game. kconfig[104][2]
 */
enum gconfig
  { START, L_LEFT, L_RIGHT, L_UP, L_DOWN, R_LEFT, R_RIGHT, R_UP, R_DOWN,
  };
enum texture
  { BACKGROUND, CHECKER, BORDER, CIRNO, FLAN, TUTOR, B32, B24, B20, B16, B12, B8, END_TEXTURE,
  };
enum song
  { SONG_A, SONG_B, SONG_C, END_SONG,
  };
struct player {
  Vector2 position, move;
  double speed;
  double slow_ratio;
  int health, bomb;
  int invuln;
};
struct effects {
  double scroll_speed;
  double player_flip_speed;
  int checker_alpha;
  float flash;
  float tutor_alpha;
};
struct bullet {
  size_t group_max, group_used;
  size_t bullet_max;
  float * x, * y, * r;
  /* group_max ... */
  unsigned * tm; /* inverts ttl when time */
  unsigned * ttl;
  size_t * count; /* absolute, count[group_used-1] == bullet_top */
  bool * hurts;
  int * size;
  Color * color;
  float * dx, * dy, * dr;
};
struct context {
  float delta, time;
  Texture texture[16];
  RenderTexture render;
  int kconfig[16], gconfig[16]; /* abstraction layer for input */
  int gamepad;                  /* gamepad integer */
  Vector2 area[1];              /* screen area */
  int music_select;
  Sound music[3];
  int phase;
  struct player player[1];      /* player */
  struct effects effects[1];    /* effect levers */
  struct bullet bullet;    /* bullet abstraction */
};
void DrawCentered(Texture * texture, Vector2 point, int invert, float radian, Color color)
{ DrawTexturePro(*texture,
                 (Rectangle){ 0, 0,
                              texture->width  * (invert >> 0 & 1 ? -1 : 1),
                              texture->height * (invert >> 1 & 1 ? -1 : 1) },
                 (Rectangle){ point.x, point.y, texture->width, texture->height },
                 (Vector2){ texture->width / 2.0f, texture->height / 2.0f },
                 radian * (180.0f / M_PI),
                 color);
}
void DrawCenteredWrapped(Texture * texture, Vector2 point, int invert, float radian, Color color)
{ float hw = texture->width  / 2.0f;
  float hh = texture->height / 2.0f;
  float ox = point.x > GAME_AREA - hw ? -GAME_AREA : point.x < hw ? GAME_AREA : 0;
  float oy = point.y > GAME_AREA - hh ? -GAME_AREA : point.y < hh ? GAME_AREA : 0;
  DrawCentered(texture, point,                                           invert, radian, color);
  if (ox) DrawCentered(texture, (Vector2){point.x+ox, point.y},          invert, radian, color);
  if (oy) DrawCentered(texture, (Vector2){point.x,    point.y+oy},       invert, radian, color);
  if (ox && oy) DrawCentered(texture, (Vector2){point.x+ox, point.y+oy}, invert, radian, color);
}
#include "player.c"
#include "boss.c"
#include "bullet.c"
#include "background.c"
#include "music.c"
#include "context.c"
int change_directory(const char * filename) {
  struct stat statistics;
  char path[PATH_MAX];
  if (!filename) { return -1; }
  strncpy(path, filename, PATH_MAX-1);
  if (stat(path, &statistics)) { return -1; }
  if (!S_ISDIR(statistics.st_mode)) {
    char * terminator = strrchr(path, '/');
    if (!terminator) { return -1; }
    *terminator = '\0';
  }
  return chdir(path);
}
public static inline int Main( int ac , char * av [ ] )
{ struct context context[1] = {0};
  change_directory(av[0]);
  PreinitContext(av[0]);
  InitContext(context);
  LoopContext(context);
  DeinitContext(context);
  PostdeinitContext();
  return 0;
}
int main(int ac, char ** av)
{ return Main(ac,av); }
