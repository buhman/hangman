/* 4 LCD Status */
#define DISPSTAT 0x004
#define DISPSTAT__V_BLANK_INT_ENABLE (1 << 3)
#define DISPSTAT__H_BLANK_INT_ENABLE (1 << 4)
#define DISPSTAT__V_COUNT_INT_ENABLE (1 << 5)
#define VCOUNT 0x006

/* 5 Image System */
#define DISPCNT 0x000
#define DISPCNT__WINDOW_1 (1 << 14)
#define DISPCNT__WINDOW_0 (1 << 13)
#define DISPCNT__OBJ (1 << 12)
#define DISPCNT__BG3 (1 << 11)
#define DISPCNT__BG2 (1 << 10)
#define DISPCNT__BG1 (1 << 9)
#define DISPCNT__BG0 (1 << 8)
#define DISPCNT__FORCED_BLANK (1 << 7)
#define DISPCNT__OBJ_1_DIMENSION (1 << 6)
#define DISPCNT__FRAMEBUFFER(n) ((n) << 4) /* 1-bit */
#define DISPCNT__BG_MODE_0 (0 << 0)
#define DISPCNT__BG_MODE_1 (1 << 0)
#define DISPCNT__BG_MODE_2 (2 << 0)
#define DISPCNT__BG_MODE_3 (3 << 0)
#define DISPCNT__BG_MODE_4 (4 << 0)
#define DISPCNT__BG_MODE_5 (5 << 0)

/* 6 Rendering Functions */
#define BG0CNT 0x008
#define BG1CNT 0x00a
#define BG2CNT 0x00c
#define BG3CNT 0x00e

#define BG_CNT__CHARACTER_BASE_BLOCK(n) ((n) << 2)
#define BG_CNT__MOSAIC (1 << 6)
#define BG_CNT__COLOR_16_16 0
#define BG_CNT__COLOR_256 (1 << 7)
#define BG_CNT__SCREEN_BASE_BLOCK(n) ((n) << 8)
#define BG_CNT__SCREEN_SIZE(n) ((n) << 14)
#define BG_CNT__PRIORITY(n) ((n) << 0)

#define MOSAIC 0x04c

/* 6.1.7 BG Rotation and Scaling Features */
#define BG2PA 0x020
#define BG2PB 0x022
#define BG2PC 0x024
#define BG2PD 0x026
#define BG3PA 0x030
#define BG3PB 0x032
#define BG3PC 0x034
#define BG3PD 0x036

/* 6.1.8 BG Scrolling */
#define BG0HOFS 0x010
#define BG0VOFS 0x012
#define BG1HOFS 0x014
#define BG1VOFS 0x016
#define BG2HOFS 0x018
#define BG2VOFS 0x01a
#define BG3HOFS 0x01c
#define BG3VOFS 0x01e

/* text screen */
#define SCREEN_TEXT__PALETTE(n) ((n) << 12)
#define SCREEN_TEXT__V_FLIP (1 << 11)
#define SCREEN_TEXT__H_FLIP (1 << 10)

/* 6.3 OBJ */
#define OBJ_A0__SHAPE_SQUARE   (0b00 << 14)
#define OBJ_A0__SHAPE_H_RECT   (0b01 << 14)
#define OBJ_A0__SHAPE_V_RECT   (0b10 << 14)
#define OBJ_A0__COLOR_MODE_256 (1 << 13)
#define OBJ_A0__MOSAIC         (1 << 12)
#define OBJ_A0__MODE_NORMAL    (0b00 << 10)
#define OBJ_A0__MODE_TRANSPARENT (0b01 << 10)
#define OBJ_A0__MODE_WINDOW    (0b10 << 10)
#define OBJ_A0__DOUBLE_SIZE      (1 << 9)
#define OBJ_A0__ROTATION_SCALING (1 << 8)
#define OBJ_A0__Y_COORDINATE(n)  ((n) << 0) /* 8-bit */

#define OBJ__SQUARE_8_8   (0)
#define OBJ__SQUARE_16_16 (1)
#define OBJ__SQUARE_32_32 (2)
#define OBJ__SQUARE_64_64 (3)
#define OBJ__H_RECT_16_8  (0)
#define OBJ__H_RECT_32_8  (1)
#define OBJ__H_RECT_32_16 (2)
#define OBJ__H_RECT_64_32 (3)
#define OBJ__V_RECT_8_16  (0)
#define OBJ__V_RECT_8_32  (1)
#define OBJ__V_RECT_16_32 (2)
#define OBJ__V_RECT_32_64 (3)
#define OBJ_A1__SIZE(n) ((n) << 14) /* 2-bit */
#define OBJ_A1__V_FLIP  (1 << 13)
#define OBJ_A1__H_FLIP  (1 << 12)
#define OBJ_A1__ROTATION_SCALING(n) ((n) << 9) /* 5-bit */
#define OBJ_A1__X_COORDINATE(n) ((n) << 0) /* 9-bit */

#define OBJ_A2__COLOR_PALETTE(n) ((n) << 12) /* 4-bit */
#define OBJ_A2__PRIORITY(n)  ((n) << 10) /* 2-bit */
#define OBJ_A2__CHARACTER(n) ((n) << 0) /* 10-bit */

/* 14 Key Input */
#define KEY_INPUT 0x130
#define KEY_INPUT__A   0
#define KEY_INPUT__B   1
#define KEY_INPUT__SL  2
#define KEY_INPUT__ST  3
#define KEY_INPUT__RIGHT 4
#define KEY_INPUT__LEFT  5
#define KEY_INPUT__UP    6
#define KEY_INPUT__DOWN  7
#define KEY_INPUT__L   8
#define KEY_INPUT__R   9

#define KEYCNT 0x132
#define KEYCNT__ALL_KEYS 0x3ff
#define KEYCNT__INPUT_A   (1 << 0)
#define KEYCNT__INPUT_B   (1 << 1)
#define KEYCNT__INPUT_SL  (1 << 2)
#define KEYCNT__INPUT_ST  (1 << 3)
#define KEYCNT__INPUT_RIGHT (1 << 4)
#define KEYCNT__INPUT_LEFT  (1 << 5)
#define KEYCNT__INPUT_UP    (1 << 6)
#define KEYCNT__INPUT_DOWN  (1 << 7)
#define KEYCNT__INPUT_L   (1 << 8)
#define KEYCNT__INPUT_R   (1 << 9)
#define KEYCNT__INT_AND (1 << 15)
#define KEYCNT__INT_ENABLE (1 << 14)

/* 15 Interrupt Control */
#define IME 0x208
#define IME__INT_MASTER_ENABLE (1 << 0)

#define IE  0x200
#define IE__V_BLANK         (1 << 0)
#define IE__H_BLANK         (1 << 1)
#define IE__V_COUNTER_MATCH (1 << 2)
#define IE__TIMER_0         (1 << 3)
#define IE__TIMER_1         (1 << 4)
#define IE__TIMER_2         (1 << 5)
#define IE__TIMER_3         (1 << 6)
#define IE__SERIAL          (1 << 7)
#define IE__DMA_0           (1 << 8)
#define IE__DMA_1           (1 << 9)
#define IE__DMA_2           (1 << 10)
#define IE__DMA_3           (1 << 11)
#define IE__KEY             (1 << 12)
#define IE__GAME_PAK        (1 << 13)

#define IF  0x202

/* sound */

#define SOUND1_CNT_L 0x060
#define SOUND1_CNT_L__SWEEP_TIME_OFF 0
#define SOUND1_CNT_L__SWEEP_TIME(n) ((n) << 4)
#define SOUND1_CNT_L__SWEEP_DECREASE (1 << 3)
#define SOUND1_CNT_L__SWEEP_SHIFTS(n) ((n) << 0)

#define SOUND1_CNT_H 0x062
#define SOUND1_CNT_H__ENVELOPE_VALUE(n) ((n) << 12)
#define SOUND1_CNT_H__ENVELOPE_AMPLIFY (1 << 11)
#define SOUND1_CNT_H__ENVELOPE_STEPS(n) ((n) << 8)
#define SOUND1_CNT_H__DUTY_CYCLE(n) ((n) << 6)
#define SOUND1_CNT_H__SOUND_LENGTH(n) ((n) << 0)

#define SOUND1_CNT_X 0x064
#define SOUND1_CNT_X__RESTART (1 << 15)
#define SOUND1_CNT_X__SOUND_LENGTH (1 << 14)
#define SOUND1_CNT_X__FREQUENCY_DATA(n) ((n) << 0)

#define SOUND2_CNT_L 0x68
#define SOUND2_CNT_L__ENVELOPE_VALUE(n) ((n) << 12)
#define SOUND2_CNT_L__ENVELOPE_AMPLIFY (1 << 11)
#define SOUND2_CNT_L__ENVELOPE_STEPS(n) ((n) << 8)
#define SOUND2_CNT_L__DUTY_CYCLE(n) ((n) << 6)
#define SOUND2_CNT_L__SOUND_LENGTH(n) ((n) << 0)

#define SOUND2_CNT_H 0x06c
#define SOUND2_CNT_H__RESTART (1 << 15)
#define SOUND2_CNT_H__SOUND_LENGTH (1 << 14)
#define SOUND2_CNT_H__FREQUENCY_DATA(n) ((n) << 0)

#define SOUND3_CNT_L 0x070
#define SOUND3_CNT_L__SOUND_OUTPUT (1 << 7)
#define SOUND3_CNT_L__WAVE_BANK(n) ((n) << 6)
#define SOUND3_CNT_L__WAVE_32_STEP (0 << 5)
#define SOUND3_CNT_L__WAVE_64_STEP (1 << 5)

#define SOUND3_CNT_H 0x072
#define SOUND3_CNT_H__FORCE_OUTPUT_LEVEL (1 << 15)
#define SOUND3_CNT_H__OUTPUT_LEVEL(n) ((n) << 13)
#define SOUND3_CNT_H__SOUND_LENGTH(n) ((n) << 0)

#define SOUND3_CNT_X 0x074
#define SOUND3_CNT_X__RESTART (1 << 15)
#define SOUND3_CNT_X__SOUND_LENGTH (1 << 14)
#define SOUND3_CNT_X__FREQUNCY_DATA(n) ((n) << 0)

#define WAVE_RAM0_L 0x090
#define WAVE_RAM0_H 0x092
#define WAVE_RAM1_L 0x094
#define WAVE_RAM1_H 0x096
#define WAVE_RAM2_L 0x098
#define WAVE_RAM2_H 0x09a
#define WAVE_RAM3_L 0x09c
#define WAVE_RAM3_H 0x09e

#define SOUND4_CNT_L 0x78
#define SOUND4_CNT_L__ENVELOPE_VALUE(n) ((n) << 12)
#define SOUND4_CNT_L__ENVELOPE_AMPLIFY (1 << 11)
#define SOUND4_CNT_L__ENVELOPE_STEPS(n) ((n) << 8)
#define SOUND4_CNT_L__SOUND_LENGTH(n) ((n) << 0)

#define SOUND4_CNT_H 0x07c
#define SOUND4_CNT_H__RESTART (1 << 15)
#define SOUND4_CNT_H__SOUND_LENGTH (1 << 14)
#define SOUND4_CNT_H__COUNTER_SHIFT_FREQ(n) ((n) << 4)
#define SOUND4_CNT_H__COUNTER_7_STEP (1 << 3)
#define SOUND4_CNT_H__COUNTER_PRESCALAR(n) ((n) << 0)

#define SOUNDCNT_L 0x080
#define SOUNDCNT_L__OUTPUT_1_L (1 << 12)
#define SOUNDCNT_L__OUTPUT_2_L (1 << 13)
#define SOUNDCNT_L__OUTPUT_3_L (1 << 14)
#define SOUNDCNT_L__OUTPUT_4_L (1 << 15)
#define SOUNDCNT_L__OUTPUT_1_R (1 << 8)
#define SOUNDCNT_L__OUTPUT_2_R (1 << 9)
#define SOUNDCNT_L__OUTPUT_3_R (1 << 10)
#define SOUNDCNT_L__OUTPUT_4_R (1 << 11)
#define SOUNDCNT_L__OUTPUT_LEVEL_L(n) ((n) << 4)
#define SOUNDCNT_L__OUTPUT_LEVEL_R(n) ((n) << 0)

#define SOUNDCNT_H 0x082
#define SOUNDCNT_H__OUTPUT_1234_RATIO_QUARTER (0 << 0)
#define SOUNDCNT_H__OUTPUT_1234_RATIO_HALF    (1 << 0)
#define SOUNDCNT_H__OUTPUT_1234_RATIO_FULL    (2 << 0)
#define SOUNDCNT_H__OUTPUT_SOUNDA_RATIO_HALF  (0 << 2)
#define SOUNDCNT_H__OUTPUT_SOUNDA_RATIO_FULL  (1 << 2)
#define SOUNDCNT_H__OUTPUT_SOUNDB_RATIO_HALF  (0 << 2)
#define SOUNDCNT_H__OUTPUT_SOUNDB_RATIO_FULL  (1 << 2)
#define SOUNDCNT_H__OUTPUT_SOUNDA_L (1 << 8)
#define SOUNDCNT_H__OUTPUT_SOUNDA_R (1 << 9)
#define SOUNDCNT_H__OUTPUT_SOUNDA_TIMER0 (0 << 10)
#define SOUNDCNT_H__OUTPUT_SOUNDA_TIMER1 (1 << 10)
#define SOUNDCNT_H__OUTPUT_SOUNDA_RESET  (1 << 11)
#define SOUNDCNT_H__OUTPUT_SOUNDB_L (1 << 12)
#define SOUNDCNT_H__OUTPUT_SOUNDB_R (1 << 13)
#define SOUNDCNT_H__OUTPUT_SOUNDB_TIMER0 (0 << 14)
#define SOUNDCNT_H__OUTPUT_SOUNDB_TIMER1 (1 << 14)
#define SOUNDCNT_H__OUTPUT_SOUNDB_RESET  (1 << 15)

#define SOUNDCNT_X 0x084
#define SOUNDCNT_X__ENABLE (1 << 7)
#define SOUNDCNT_X__ENABLE_1 (1 << 0)
#define SOUNDCNT_X__ENABLE_2 (1 << 1)
#define SOUNDCNT_X__ENABLE_3 (1 << 2)
#define SOUNDCNT_X__ENABLE_4 (1 << 3)

#define SOUNDBIAS 0x88
#define SOUNDBIAS__RESOLUTION_9BIT (0 << 14)
#define SOUNDBIAS__RESOLUTION_8BIT (1 << 14)
#define SOUNDBIAS__RESOLUTION_7BIT (2 << 14)
#define SOUNDBIAS__RESOLUTION_6BIT (3 << 14)

#define FIFO_A_L 0x0a0
#define FIFO_A_H 0x0a2
#define FIFO_B_L 0x0a4
#define FIFO_B_H 0x0a6

/* timers */

#define TM0CNT_L 0x100
#define TM1CNT_L 0x104
#define TM2CNT_L 0x108
#define TM3CNT_L 0x10c

#define TM0CNT_H 0x102
#define TM1CNT_H 0x106
#define TM2CNT_H 0x10a
#define TM3CNT_H 0x10e
#define TM_CNT_H__ENABLE (1 << 7)
#define TM_CNT_H__INT_ENABLE (1 << 6)
#define TM_CNT_H__COUNT_UP (1 << 2)
#define TM_CNT_H__PRESCALAR_1 (0)
#define TM_CNT_H__PRESCALAR_64 (1)
#define TM_CNT_H__PRESCALAR_256 (2)
#define TM_CNT_H__PRESCALAR_1024 (3)

/* 12.1 DMA 0 */
#define DMA0_SAD_L 0x0b0 /* source address */
#define DMA0_SAD_H 0x0b2

#define DMA0_DAD_L 0x0b4 /* destination address */
#define DMA0_DAD_H 0x0b6

#define DMA0_CNT_L 0x0b8 /* word count */

#define DMA0_CNT_H 0x0ba /* control */

/* 12.2 DMA 1 */
#define DMA1_SAD_L 0x0bc /* source address */
#define DMA1_SAD_H 0x0be

#define DMA1_DAD_L 0x0c0 /* destination address */
#define DMA1_DAD_H 0x0c2

#define DMA1_CNT_L 0x0c4 /* word count */

#define DMA1_CNT_H 0x0c6 /* control */

/* 12.2 DMA 2 */
#define DMA2_SAD_L 0x0c8 /* source address */
#define DMA2_SAD_H 0x0ca

#define DMA2_DAD_L 0x0cc /* destination address */
#define DMA2_DAD_H 0x0ce

#define DMA2_CNT_L 0x0d0 /* word count */

#define DMA2_CNT_H 0x0d2 /* control */

/* DMA control */
#define DMAn_CNT_H__ENABLE (1 << 15)
#define DMAn_CNT_H__INT_ENABLE (1 << 14)
#define DMAn_CNT_H__START_IMMEDIATE (0 << 12)
#define DMAn_CNT_H__START_V_BLANK (1 << 12)
#define DMAn_CNT_H__START_H_BLANK (2 << 12)
#define DMAn_CNT_H__START_SOUND_FIFO (3 << 12) /* DMA{1,2} only */
#define DMAn_CNT_H__WORD_16_BIT (0 << 10)
#define DMAn_CNT_H__WORD_32_BIT (1 << 10)
#define DMAn_CNT_H__REPEAT (1 << 9)
#define DMAn_CNT_H__SRC_INCREMENT (0 << 7)
#define DMAn_CNT_H__SRC_DECREMENT (1 << 7)
#define DMAn_CNT_H__SRC_FIXED (2 << 7)
#define DMAn_CNT_H__DST_INCREMENT (0 << 5)
#define DMAn_CNT_H__DST_DECREMENT (1 << 5)
#define DMAn_CNT_H__DST_FIXED (2 << 5)
#define DMAn_CNT_H__DST_RELOAD (3 << 5)

/* 16 Power Down */
#define HALTCNT 0x301 /* 1 byte */
#define HALTCNT__PAUSE 0x0
#define HALTCNT__STOP 0x80

/* 13 UART Communication Functions */
#define SIODATA8 0x12a

#define SIOCNT 0x128
#define SIOCNT__INT_ENABLE (1 << 14)
#define SIOCNT__UART_MODE (0b11 << 12)
#define SIOCNT__UART_RECV_ENABLE (1 << 11)
#define SIOCNT__UART_SEND_ENABLE (1 << 10)
#define SIOCNT__UART_PARITY_ENABLE (1 << 9)
#define SIOCNT__UART_FIFO_ENABLE (1 << 8)
#define SIOCNT__UART_DATA_8BIT (1 << 7)
#define SIOCNT__UART_ERROR 6
#define SIOCNT__UART_RECV_EMPTY 5
#define SIOCNT__UART_SEND_FULL 4
#define SIOCNT__UART_PARITY_ODD (1 << 3)
#define SIOCNT__UART_CTS_ENABLE (1 << 2)
#define SIOCNT__BAUD_RATE_9600 (0b00 << 0)
#define SIOCNT__BAUD_RATE_38400 (0b01 << 0)
#define SIOCNT__BAUD_RATE_57600 (0b10 << 0)
#define SIOCNT__BAUD_RATE_115200 (0b11 << 0)

/* 13.4 General Purpose Communication */
#define RCNT 0x134
#define RCNT__SERIAL_ENABLE (0b00 << 14)
#define RCNT__GPIO (0b10 << 14)
#define RCNT__JOYBUS (0b11 << 14)
#define RCNT__INT_ENABLE (1 << 8)
#define RCNT__SO_OUTPUT_ENABLE (1 << 7)
#define RCNT__SI_OUTPUT_ENABLE (1 << 6)
#define RCNT__SD_OUTPUT_ENABLE (1 << 5)
#define RCNT__SC_OUTPUT_ENABLE (1 << 4)
#define RCNT__SO_DATA 3
#define RCNT__SI_DATA 2
#define RCNT__SD_DATA 1
#define RCNT__SC_DATA 0
