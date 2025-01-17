#ifndef _REPLAY_H_
#define _REPLAY_H_

#include "base/random.h"
#include "cheats.h"
#include <string>

// Records the button input state, RNG seeds, and interesting events to a .zplay file,
// and play it back while optionally asserting that everything happens the same way
// on every frame.
//
// See docs/replays.md for an overview.
//
// See tests/run_replay_tests.py for the test runner, and instructions for the CLI.

const std::string REPLAY_EXTENSION = "zplay";

enum ReplayMode
{
    Off,
    Replay,
    Record,
    Assert,
    Update,
    ManualTakeover,
};

void replay_start(ReplayMode mode_, std::string filename_);
void replay_continue(std::string filename_);
void replay_poll();
void replay_peek_quit();
bool replay_is_assert_done();
void replay_forget_input();
void replay_stop();
void replay_quit();
void replay_save();
void replay_save(std::string filename);
void replay_stop_manual_takeover();

void replay_step_comment(std::string comment);
void replay_step_quit(int quit_state);
void replay_step_cheat(Cheat cheat, int arg1 = -1, int arg2 = -1);

void replay_set_meta(std::string key, std::string value);
void replay_set_meta(std::string key, int value);
void replay_set_meta_bool(std::string key, bool value);
std::string replay_get_meta_str(std::string key);
int replay_get_meta_int(std::string key);
bool replay_get_meta_bool(std::string key);

ReplayMode replay_get_mode();
std::string replay_get_filename();
std::string replay_get_buttons_string();
bool replay_is_active();
void replay_set_debug(bool enable_debug);
bool replay_is_debug();
void replay_set_sync_rng(bool enable);
bool replay_is_replaying();
void replay_set_frame_arg(int frame);

size_t replay_register_rng(zc_randgen *rng);
void replay_set_rng_seed(zc_randgen *rng, int seed);
void replay_sync_rng();

#endif
