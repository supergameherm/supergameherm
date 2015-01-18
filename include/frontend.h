#ifndef __FRONTEND_H__
#define __FRONTEND_H__

#include "config.h"	// bool
#include "typedefs.h"	// typedefs
#include "input.h"	// input_key


struct frontend_audio_t
{
	bool (*init)(emu_state *restrict);		//! Initalise the audio output
	void (*finish)(emu_state *restrict);		//! Deinitalise the audio output
	void (*output_sample)(emu_state *restrict);	//! Output an audio sample

	void *data;					//! Opaque data
};

struct frontend_video_t
{
	bool (*init)(emu_state *restrict);		//! Initalise the video output
	void (*finish)(emu_state *restrict);		//! Deinitalise the video output
	void (*blit_canvas)(emu_state *restrict);	//! Blit the canvas

	void *data;					//! Opaque data
};

struct frontend_t
{
	frontend_audio audio;
	frontend_video video;

	bool input_set, audio_set, video_set;

	int (*event_loop)(emu_state *restrict);	//! Event loop function (for use with toolkits)

	void *data;				//! Opaque data
};

//! Frontend indicies
typedef enum
{
	FRONT_NULL = 0,
	FRONT_LIBCACA = 1,
	FRONT_WIN32 = 2,
	FRONT_SDL2 = 3,
} frontend_type;


//! Change the frontend
bool select_frontend_audio(emu_state * restrict, const frontend_audio * restrict);
bool select_frontend_video(emu_state * restrict, const frontend_video * restrict);
bool select_frontend_all(emu_state * restrict, const frontend_audio * restrict,
	const frontend_video * restrict, int (*)(emu_state *));
void finish_frontend(emu_state *restrict);

//! Null frontends
extern const frontend_audio null_frontend_audio;
extern const frontend_video null_frontend_video;
int null_event_loop(emu_state *restrict);

#define NULL_AUDIO &null_frontend_audio
#define NULL_VIDEO &null_frontend_video
#define NULL_LOOP &null_event_loop

//! libcaca frontends
#ifdef HAVE_LIBCACA
#	include "frontends/caca/frontend.h"
#	define LIBCACA_AUDIO &null_frontend_audio
#	define LIBCACA_VIDEO &libcaca_frontend_video
#	define LIBCACA_LOOP &libcaca_event_loop
#else
#	define LIBCACA_AUDIO &null_frontend_audio
#	define LIBCACA_VIDEO &null_frontend_video
#	define LIBCACA_LOOP &null_event_loop
#endif

//! SDL2 frontends
#ifdef HAVE_SDL2
#	include "frontends/sdl2/frontend.h"
#	define SDL2_AUDIO &sdl2_frontend_audio
#	define SDL2_VIDEO &sdl2_frontend_video
#	define SDL2_LOOP sdl2_event_loop
#else
#	define SDL2_INPUT &null_frontend_input
#	define SDL2_AUDIO &null_frontend_audio
#	define SDL2_VIDEO &null_frontend_video
#	define SDL2_LOOP &null_event_loop
#endif

//! Win32 frontend
#ifdef HAVE_WINDOWS
#	include "frontends/w32/frontend.h"
#	define WIN32_AUDIO &w32_frontend_audio
#	define WIN32_VIDEO &w32_frontend_video
#	define WIN32_LOOP &w32_event_loop
#else
#	define WIN32_AUDIO &null_frontend_audio
#	define WIN32_VIDEO &null_frontend_video
#	define WIN32_LOOP &null_event_loop
#endif

// Helpers to call functions
#define CALL_FRONTEND_0(state, type, fn) ((*(state->front.type.fn))(state))
#define CALL_FRONTEND_1(state, type, fn, _1) ((*(state->front.type.fn))(state, _1))
#define EVENT_LOOP(state) ((*(state->front.event_loop))(state))

#define FRONTEND_INIT_AUDIO(state) CALL_FRONTEND_0(state, audio, init)
#define FRONTEND_INIT_VIDEO(state) CALL_FRONTEND_0(state, video, init)
#define FRONTEND_FINISH_AUDIO(state) CALL_FRONTEND_0(state, audio, finish)
#define FRONTEND_FINISH_VIDEO(state) CALL_FRONTEND_0(state, video, finish)

#define BLIT_CANVAS(state) CALL_FRONTEND_0(state, video, blit_canvas)
#define OUTPUT_SAMPLE(state) CALL_FRONTEND_0(state, audio, output_sample)

#endif /*__FRONTEND_H__*/
