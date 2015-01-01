#ifndef __FRONTEND_SDL2_FRONTEND_H__
#define __FRONTEND_SDL2_FRONTEND_H__

#include "frontends/sdl2/sdl_inc.h"


typedef struct sdl2_video_data_t
{
	SDL_Window *window;
	SDL_Renderer *render;
	SDL_Texture *texture;
} sdl2_video_data;

typedef struct sdl2_audio_data_t
{
	int freq;
	int freq_rem;
	int per_env;
	struct {
		uint16_t per_remain;
		uint8_t len_wait;
		uint8_t outseq;
	} ch1;
	struct {
		uint16_t per_remain;
		uint8_t len_wait;
		uint8_t outseq;
	} ch2;
	struct {
		uint16_t per_remain;
	} ch3;
	struct {
		uint16_t per_remain;
		uint16_t lfsr;
	} ch4;
} sdl2_audio_data;


extern const frontend_audio sdl2_frontend_audio;
extern const frontend_video sdl2_frontend_video;
int sdl2_event_loop(emu_state *);

#endif
