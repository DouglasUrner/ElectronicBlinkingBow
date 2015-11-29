typedef enum {
  A,
  As,
  B,
  // B# == C
  C,
  Cs,
  D,
  Ds,
  E,
  // E# == F
  F,
  Fs,
  G,
  Gs,
} NoteName;

typedef struct {
  int octave;
  NoteName note;
} Pitch;
