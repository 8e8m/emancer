static inline void UpdateMusic(struct context * context)
{ if (!IsSoundPlaying(context->music[context->music_select]))
  { context->music_select++;
    PlaySound(context->music[context->music_select % END_SONG]);
  }
}
static inline void InitMusic(struct context * context)
{ Sound music[] =
  { LoadSound("resource/flan.mp3"),
  };
  memcpy(context->music, music, sizeof(music) / sizeof(*music) * sizeof(Sound));
  PlaySound(context->music[0]);
}
