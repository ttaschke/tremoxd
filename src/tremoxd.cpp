/*
 * File: tremoxd.cpp
 *
 * Tremolo effect for Minilogue XD mod fx
 *
 * Param time: Tremolo effect LFO rate
 * Param depth: Tremolo effect depth
 * 
 */

#include "usermodfx.h"
#include "osc_api.h"
#include "fx_api.h"
#include "usermodfx.h"
#include "simplelfo.hpp"

static dsp::SimpleLFO lfo;

float tremolo_depth;

enum lfo_shape {
  SINE,
  TRIANGLE,
  SAW,
  SQUARE
};

lfo_shape shape;

/* Implementation of the initialization callback */
void MODFX_INIT(uint32_t platform, uint32_t api)
{
  tremolo_depth = 0.0;
  lfo.reset();
  lfo.setF0(0.0, k_samplerate_recipf);
  shape = SINE;
}


/**
 * Implementation of the process callback
 * Ref: https://korginc.github.io/logue-sdk/ref/minilogue-xd/v1.1-0/html/group__modfx__inst.html
 *
 * @param main_xn Input sample buffer for main timbre
 * @param main_yn Output sample buffer for main timbre
 * @param sub_xn  Input sample buffer for sub timbre
 * @param sub_yn  Output sample buffer for sub timbre
 * @param frames  Size of buffers. (2 samples per frames)
 *
 * Note: sub_xn and sub_yn are not used here, as the Minilogue XD has no sub timbre
 */
void MODFX_PROCESS(const float *main_xn, float *main_yn,
                   const float *sub_xn,  float *sub_yn,
                   uint32_t frames)
{

  // main input
  const float * mx = main_xn;

  // main output
  float * __restrict my = main_yn;

  // one sample per channel (L/R)
  const float * my_e = my + 2*frames;

  float processed_mx;

  // value of LFO for current phase
  float lfo_val;

  float tremolo_factor;

  for (; my != my_e; ) {

    switch(shape) {
      case SINE:
        lfo_val = lfo.sine_bi();
        break;
      case TRIANGLE:
        lfo_val = lfo.triangle_bi();
        break;
      case SAW:
        lfo_val = lfo.saw_bi();
        break;
      case SQUARE:
        lfo_val = lfo.square_bi();
        break;
    }

    tremolo_factor = 1.0 - (tremolo_depth * lfo_val);

    processed_mx = *(mx++) * tremolo_factor; // use L channel sample as input (mono)
    mx++; //ignore R channel sample

    // write to both channels (L/R)
    *(my++) = processed_mx;
    *(my++) = processed_mx;

    lfo.cycle();
  }

}

/**
 * Implementation of the param callback that gets called when the user changes the time or depth knob
 */
void MODFX_PARAM(uint8_t index, int32_t value)
{
  const float valf = q31_to_f32(value); // valf is in range (0.0 - 1.0)
  switch (index) {
    case k_user_modfx_param_time:
      {
        float time_value = valf;
        if (time_value < 0.25) {
          shape = SINE;
        } else if (time_value >= 0.25 && time_value < 0.5) {
          shape = TRIANGLE;
          time_value -= 0.25;
        } else if (time_value >= 0.5 && time_value < 0.75) {
          shape = SAW;
          time_value -= 0.5;
        } else if (time_value >= 0.75) {
          shape = SQUARE;
          time_value -= 0.75;
        }
        lfo.setF0(time_value * 4.0 * 10, k_samplerate_recipf);
        break;
      }
    case k_user_modfx_param_depth:
      tremolo_depth = valf;
      break;
    default:
      break;
  }
}
