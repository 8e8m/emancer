static inline void UpdateMusic(struct context * context)
{ if (!IsSoundPlaying(context->music[context->music_select]))
  { context->music_select = (context->music_select + 1) % 2;
    if (!context->music_select)
    { Die(context);
    }
    PlaySound(context->music[context->music_select]);
  }
}
static inline void InitMusic(struct context * context)
{ Sound music[] =
  { LoadSound("resource/flan.mp3"),
    LoadSound("resource/sakuya.mp3"),
    LoadSound("resource/yukari.mp3"),
  };
  memcpy(context->music, music, sizeof(music) / sizeof(*music) * sizeof(Sound));
  context->music_select = 0;
  PlaySound(context->music[context->music_select]);
}
