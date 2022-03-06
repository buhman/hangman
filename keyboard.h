void keyboard_draw(u32 col, u32 row);
int keyboard_get_letter(int x, int y);

#ifdef ROMANIAN
#define KEYBOARD_COLS (13)
#else
#define KEYBOARD_COLS (10)
#endif

extern const int keyboard_max_x[3];

typedef enum letter {
  _A_ = 0,
  _B_,
  _C_,
  _D_,
  _E_,
  _F_,
  _G_,
  _H_,
  _I_,
  _J_,
  _K_,
  _L_,
  _M_,
  _N_,
  _O_,
  _P_,
  _Q_,
  _R_,
  _S_,
  _T_,
  _U_,
  _V_,
  _W_,
  _X_,
  _Y_,
  _Z_,
  _A_CIRCUMFLEX_,
  _I_CIRCUMFLEX_,
  _A_BREVE_,
  _S_COMMA_,
  _T_COMMA_,
  _UNDERSCORE,
  LETTER_LAST
} letter_t;
