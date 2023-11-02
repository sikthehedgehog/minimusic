# MiniMusic changelog

## Version 1.02 (2023-11-02)

- (GitHub issue #10) Fixed sound effect priority not resetting when stopping music (or playing new music, which implicitly stops the previous one), which prevented further lower priority sound effects from playing until a higher priority one reset it again. Last patch had a similar bugfix for pausing.
- Fixed an issue where `MuteFm` did not necessarily mute correctly FM channels 4 to 6 (and seemed to "work" by sheer coincidence only).

## Version 1.01 (2023-08-31)

- Added `CHANGELOG.md` (this file).
- (GitHub issue #9) Fixed PSG channels not muting when pausing.
- (GitHub issue #8) Fixed sound effect priority not resetting when pausing, which prevented further lower priority sound effects from playing until a higher priority one reset it again.

## Version 1.00 (2023-08-26)

- Initial release.
