# Raspberry Pi Pico Template for C Projects

This template is designed as a foundation for C programming projects for the RP2040, RP2350 microcontrollers and Raspberry Pi Pico development boards. By default, the output binary is very small at approximately 3kB by default, and can be reduced down to less than 2kB by configuring various build options.

This template is generally suitable for:

- Programs where limited NOR flash storage is available.
- Programs to be stored on the RP2350 OTP (7440 bytes max).
- Intermediate to advanced C developers.

By default, USB serial, floating point printf, assertions, and support for older versions of the RP2040, are disabled. These can be enabled again in CMakelists.txt.
