static inline void UpdateMusic(struct context * context)
{ if (!IsSoundPlaying(context->music[context->music_select]))
  { context->music_select = (context->music_select + 1) % 2;
    if (!context->music_select)
    { Die(context);
    }
    PlaySound(context->music[context->music_select]);
  }
}
static inline void RestartMusic(struct context * context)
{ context->music_select = 0;
  for (size_t i = 0; i < END_SONG; ++i)
  { StopSound(context->music[i]);
  }
  PlaySound(context->music[context->music_select]);
}
static inline void InitMusic(struct context * context)
{ Sound music[] =
  { LoadSound("resource/flan.mp3"),
    LoadSound("resource/sakuya.mp3"),
    LoadSound("resource/yukari.mp3"),
  };
  Sound sound[] =
  { LoadSound("resource/hit.mp3"),
    LoadSound("resource/death.mp3"),
    LoadSound("resource/world.mp3"),
    LoadSound("resource/whistle.mp3"),
    LoadSound("resource/weird.mp3"),
    LoadSound("resource/reward.mp3"),
  };
  memcpy(context->music, music, sizeof(music) / sizeof(*music) * sizeof(Sound));
  memcpy(context->sound, sound, sizeof(sound) / sizeof(*sound) * sizeof(Sound));
}
/* static inline void DeinitMusic(struct context * context) */
/* After testing does not seem to be important, and causes segv */
