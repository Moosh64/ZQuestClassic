/* Zelda Classic Music Library        	*/
/* ------------------------------------ */
/* Wrapper for transparently extending	*/
/* supported music file formats.      	*/

#ifndef _ZCMUSIC_H_
#define _ZCMUSIC_H_

#if defined ZCM_DLL
#define ZCM_EXTERN extern __declspec(dllexport)
#elif defined ZCM_DLL_IMPORT
#define ZCM_EXTERN extern __declspec(dllimport)
#else
#define ZCM_EXTERN extern
#endif
#include <cstdint>

#ifdef __cplusplus
extern "C"
{
#endif

#define ZCMF_DUH      0x00000001
#define ZCMF_OGG      0x00000002
#define ZCMF_MP3      0x00000004
#define ZCMF_GME	  0x00000008
#define ZCMF_OGGEX	  0x00000010

#define ZCM_PLAYING 1
#define ZCM_STOPPED 0
#define ZCM_PAUSED -1

#define ZCM_PAUSE   1
#define ZCM_RESUME  0
#define ZCM_TOGGLE -1

ZCM_EXTERN char const * zcmusic_types;
ZCM_EXTERN int32_t zcmusic_bufsz;

typedef struct
{
    int32_t type;                                               // uses ZCMF defines
    int32_t playing;                                            // -1 = paused, 0 = stopped, 1 = playing
    int32_t position;                                           // Only needed to sync Triforce jingle
    char filename[256];
    int32_t track;
} ZCMUSIC;

ZCM_EXTERN ZCMUSIC* zcmusic_load_for_quest(char* filename, char* quest_path);

ZCM_EXTERN bool zcmusic_init(int32_t flags = -1);
ZCM_EXTERN bool zcmusic_poll(int32_t flags = -1);
ZCM_EXTERN void zcmusic_exit();

ZCM_EXTERN ZCMUSIC * zcmusic_load_file(const char *filename);
ZCM_EXTERN ZCMUSIC * zcmusic_load_file_ex(const char *filename);
ZCM_EXTERN bool zcmusic_play(ZCMUSIC* zcm, int32_t vol);
ZCM_EXTERN bool zcmusic_pause(ZCMUSIC* zcm, int32_t pause);
ZCM_EXTERN bool zcmusic_stop(ZCMUSIC* zcm);
ZCM_EXTERN void zcmusic_unload_file(ZCMUSIC* &zcm);
ZCM_EXTERN int32_t zcmusic_get_tracks(ZCMUSIC* zcm);
ZCM_EXTERN int32_t zcmusic_change_track(ZCMUSIC* zcm, int32_t tracknum);
ZCM_EXTERN int32_t zcmusic_get_curpos(ZCMUSIC* zcm);
ZCM_EXTERN void zcmusic_set_curpos(ZCMUSIC* zcm, int32_t value);
ZCM_EXTERN void zcmusic_set_speed(ZCMUSIC* zcm, int32_t value);

#ifdef __cplusplus
}                                                           // extern "C"
#endif

#undef ZCM_EXTERN
#endif

