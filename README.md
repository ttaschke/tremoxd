## Tremoxd

Tremolo effect for Minilogue XD based on Sine wave LFO

| Knob  | Function |
| ------------- | ------------- |
| TIME  | Frequency of tremolo LFO |
| DEPTH  | Depth of tremolo effect (Amplitude) |


### Usage

* Download `tremoxd.mnlgxdunit` from this repository   
* Use Korg Minilogue XD librarian to send effect to synth
  * Librarian download: 
    * https://www.korg.com/us/products/synthesizers/minilogue_xd/librarian_contents.php)
  * Drag&Drop into `USER MODULATION FX` section
  * Click `USER OSC/FX - SEND ALL`

### Sound demo

   * https://soundcloud.com/sophon/tremoxd-demo/s-EXrVQNZ3i2d

### Build from source (for developers)

* Prerequisite: Required toolchain and tools
  * Ref.: https://korginc.github.io/logue-sdk/

* Execute `logue-sdk/tools/gcc/get_gcc_...` for your platform
* Update CMSIS git submodule
  * `tremoxd/logue-sdk/platform/minilogue-xd/ master git submodule update --init`
* Execute `make` to build `.mnlgxdunit` file