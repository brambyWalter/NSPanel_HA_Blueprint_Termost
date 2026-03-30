# Version compatibility

NSPanel Easy targets **Home Assistant** and **ESPHome** versions released no more than
two months before the NSPanel Easy release date.

For example, a firmware released in March 2026 will generally require Home Assistant and
ESPHome versions from January 2026 or later (i.e., `2026.1.x`).

> [!NOTE]
> This is a best-effort guideline, not a hard contract.
> It has been upheld for every release to date, but exceptions may occur
> if a dependency introduces a breaking change that requires a newer version.

## Finding the exact minimum ESPHome version

The enforced minimum ESPHome version is declared in the firmware itself and checked at
compile time. You will get a clear error if your ESPHome installation is too old to
compile the firmware.
