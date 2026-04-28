/* Ideas
Add mountains that shift in an inverted triangle along with:
tilt scolling background background with perspective, zoom or upscale as needed.
healthbar should be a bar, where the most important is longest and by the edge of
the screen, and each subsequent bar is shorter. Color gradient and pad with contrast.
Spellbar should be a split in the above healthbar, use a very different color grade.
Bosses' health bar should not be a bar, but a segmented spinning circle in the topleft:
i.e. 4 segments, ensuring visibility, large, in corner, with the same gradient idea,
should show damage per phase relatively well. The spinning can vary with damage.
Also consider the idea of making said healthbar spin at the rate of damage, though this
may not be ideal. Perhaps an endless circle where the color grade actually determines
the amount of damage? ((100%) cyan -> (50%) purple -> (10%) red).
Maybe add a trail to cirno.
 */
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
struct boss {
  Vector2 position;
  int phase, health;
  float timeout;
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
  struct player player[1];      /* player */
  struct boss boss[1];          /* boss */
  struct effects effects[1];    /* effect levers */
  struct bullet bullet;    /* bullet abstraction */
};
static inline float square(float a)
{ return a * a;
}
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
#include "player.c"
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
  srand(time(NULL));
  change_directory(av[0]);
  SetTraceLogLevel(LOG_ERROR);
  SetConfigFlags(FLAG_MSAA_4X_HINT);
  InitWindow(0, 0, av[0]);
  InitAudioDevice();
  SetMasterVolume(0.1f);
  InitContext(context);
  while (!WindowShouldClose())
  { SetTargetFPS(IsWindowFocused() ? 60 : 10);
    UpdateContext(context);
    { BeginDrawing();
      RenderContext(context);
    } EndDrawing();
  }
  DeinitContext(context);
  CloseAudioDevice();
  CloseWindow();
  return 0;
}
int main(int ac, char ** av)
{ return Main(ac,av); }
