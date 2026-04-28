#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
/* collide definition[offset] and definition[offset+1] together */
#define duokey(f,o) ((bool)f((int)context->kconfig[o])|(bool)f((int)context->kconfig[o+1]))
#define public
#define GAME_AREA 1080
#define MAGIC_SPEED 200
#define MAGIC_FLASH 1.2
#define MAGIC_PLAYER_RADIUS 1
#define MAGIC_INVULN_TIME 70
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
enum sound
{ HIT_SOUND, DEATH_SOUND, WORLD_SOUND, WHISTLE_SOUND, WEIRD_SOUND, REWARD_SOUND
};
struct player
{ Vector2 position, move;
  double speed;
  double slow_ratio;
  int health, bomb;
  int invuln;
};
struct effects
{ double scroll_speed;
  double player_flip_speed;
  int checker_alpha;
  float flash;
  float tutor_alpha;
};
struct bullet
{ size_t group_max, group_used;
  size_t bullet_max;
  float * x, * y, * r;
  /* group_max ... */
  unsigned * ttl;
  size_t * count; /* absolute, count[group_used-1] == bullet_top */
  float * hurts;
  int * size;
  Color * color;
  float * dx, * dy, * dr;
};
struct context
{ float delta, time;
  Texture texture[16];
  RenderTexture render;
  int kconfig[16], gconfig[16]; /* abstraction layer for input */
  int gamepad;                  /* gamepad integer */
  Vector2 area[1];              /* screen area */
  int music_select;
  Sound music[3];
  Sound sound[6];
  int phase;
  struct player player[1];      /* player */
  struct effects effects[1];    /* effect levers */
  struct bullet bullet;    /* bullet abstraction */
};
#include "render.c"
#include "player.c"
#include "boss.c"
#include "bullet.c"
#include "background.c"
#include "music.c"
#include "context.c"
#include "change_directory.c"
public static inline int Main( int ac , char * av [ ] )
{ (void) ac;
  struct context context[1] = {0};
  PreinitContext(av[0]);
  InitContext(context);
  ContextLoop(context);
  DeinitContext(context);
  PostdeinitContext();
  return 0;
}
int main(int ac, char ** av)
{ return Main(ac,av); }
