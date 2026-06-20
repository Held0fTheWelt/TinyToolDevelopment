# Lightweight Editor Mode

Lightweight Editor Mode is a reversible Unreal Editor performance overlay. It applies profile-based viewport, scalability, CVar, Unlit, and realtime reductions while keeping the main project configuration and runtime game settings outside its mutation boundary.

Not a verbatim copy of shipped docs.

## What It Does

- Provides Mild, Balanced, Aggressive, and Extreme editor profiles.
- Applies cheaper editor viewport/rendering settings for heavy scenes, demos, or laptop work.
- Captures session backups so disabling the mode can restore owned editor state.
- Keeps startup enable, stale-session recovery, and profile refresh behavior explicit.
- Offers optional UCM/UMCP JSON actions for the same enable, disable, refresh, and read-state workflow.

## Best Entry Points

- Use the shipped `Documentation/QUICKSTART.md` for first-run enable/disable flow.
- Use `Documentation/UserManual.md` and `Documentation/SettingsReference.md` for profile tuning.
- Use `Documentation/TROUBLESHOOTING.md` when viewport, CVar, or restore behavior needs diagnosis.

Fab listing: <https://www.fab.com/listings/94911975-ec7d-4d7c-8408-04bc647eb373>
