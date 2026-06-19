# Integration Notes

This document helps teams integrate Lightweight Editor Mode into a project or
shared editor workflow.

## Recommended rollout

1. Enable the plugin in a development branch.
2. Build the editor target.
3. Test in a small map.
4. Test in the heaviest production map.
5. Tune profiles for the project.
6. Share recommended profile usage with the team.
7. Decide whether startup enable should be user-specific or discouraged.

## Team profile policy

Because the settings are user-oriented, each developer can keep personal
preferences. Teams should still define guidance such as:

- Use Mild for material work.
- Use Balanced for general level editing.
- Use Aggressive for large-world layout.
- Disable before lighting review and screenshots.

## Source control policy

Do commit:

- Plugin source.
- Plugin descriptor.
- Plugin config.
- Documentation.
- Changelog.
- Readme and icon resources.

Do not commit:

- Local generated binaries unless required by your release process.
- Intermediate files.
- Saved editor state.
- Derived data.
- Personal test logs.

## Existing project renderer settings

Lightweight Editor Mode should not be used to hide problematic renderer
configuration. Treat it as an editor comfort tool. Keep normal project renderer
settings understandable and documented.

## Interaction with other tools

Other plugins or editor utilities can set the same CVars. The last writer may
win. If conflicts occur:

- Check Output Log order.
- Identify the other writer.
- Decide which tool should own the setting.
- Consider disabling overlapping features in one tool.

## Training users

The most important user habit is simple:

Enable the mode for editing speed, disable it for visual truth.

Make sure artists and designers understand that Unlit, missing fog, and reduced
shadows are expected profile effects.

## Support workflow

When a user reports an issue, ask for:

- Selected profile.
- Whether the mode was active.
- Whether the issue happened after restart.
- Output Log lines containing "[Lightweight]".
- A short description of the viewport state before enabling.
- A short description of what did not restore.

## Project-specific profile examples

Teams can document local defaults here or in a project wiki.

Example:

- Mild: Keep Lit, 95 screen percentage, disable fog only.
- Balanced: 85 screen percentage, disable Lumen and virtual shadows.
- Aggressive: 70 screen percentage, force Unlit, disable realtime.
- Extreme: 55 screen percentage, force Unlit, disable realtime and all feature
  toggles.

## When to disable globally

Consider disabling the plugin for a milestone if:

- The team is doing final art review.
- The team is comparing screenshots.
- The team is investigating renderer bugs.
- Automated visual capture depends on editor viewport appearance.

The plugin can be re-enabled after the visual pass.

