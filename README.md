## Tremoxd

Tremolo effect for Korg Minilogue XD based on Sine wave LFO

| Knob  | Function |
| ------------- | ------------- |
| TIME  | Frequency of tremolo LFO |
|   | `0.0 - 24.9` = Sine |
|   | `25.0 - 49.9` = Triangle |
|   | `50.0 - 74.9` = Saw |
|   | `75.0 - 100.0` = Square |
|   | (Each LFO shape's frequency range goes from 0-10 Hz) |
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

----

### Build from source (for developers)

* Prerequisite: Required toolchain and tools
  * Ref.: https://korginc.github.io/logue-sdk/

* Setup
  * Execute `logue-sdk/tools/gcc/get_gcc_...` for your platform
  * Update CMSIS git submodule
     * `tremoxd/logue-sdk/platform/minilogue-xd/ master git submodule update --init`
  
* Build  
  * Execute `make` to build `.mnlgxdunit` file
