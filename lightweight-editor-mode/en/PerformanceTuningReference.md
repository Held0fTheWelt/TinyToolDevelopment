# Performance Tuning Reference

This reference explains how to tune Lightweight Editor Mode profiles for
different project and hardware needs.

## Tuning philosophy

Start with the least destructive profile that solves the editor responsiveness
problem. Lower quality only as far as needed for the current task.

Recommended order:

1. Disable realtime viewport rendering.
2. Lower screen percentage.
3. Lower scalability.
4. Disable expensive features such as Lumen, virtual shadows, and fog.
5. Force Unlit only when lighting fidelity is not needed.

The default profiles are intentionally editable because every project has a
different cost distribution.

## Main cost controls

| Control | Main benefit | Main tradeoff |
| --- | --- | --- |
| ScreenPercentage | Reduces pixel cost | Softer viewport image |
| OverallQuality | Reduces broad scalability groups | Less visual detail |
| Disable Lumen | Reduces dynamic GI/reflection cost | Lighting and reflections differ |
| Disable Virtual Shadows | Reduces shadow cost | Shadow appearance changes |
| Disable Volumetric Fog | Reduces atmospheric cost | Fog and depth mood disappear |
| Force Unlit | Avoids lighting work | Not useful for final visual review |
| Disable Realtime | Stops continuous redraws | Viewport updates less automatically |

## Profile design examples

### Visual editing profile

Use when artists still need lighting context.

- OverallQuality: 2
- ScreenPercentage: 90..100
- Disable Lumen: false or true depending on scene cost
- Disable Virtual Shadows: true
- Disable Volumetric Fog: true
- Force Unlit: false
- Disable Realtime: false

### Layout profile

Use when placement and navigation matter more than appearance.

- OverallQuality: 1
- ScreenPercentage: 75..85
- Disable Lumen: true
- Disable Virtual Shadows: true
- Disable Volumetric Fog: true
- Force Unlit: true
- Disable Realtime: true

### Emergency profile

Use for very heavy maps or constrained machines.

- OverallQuality: 0
- ScreenPercentage: 50..65
- Disable Lumen: true
- Disable Virtual Shadows: true
- Disable Volumetric Fog: true
- Force Unlit: true
- Disable Realtime: true

## Hardware-oriented recommendations

### High-end workstation

Balanced is usually enough. Keep Mild close to production visuals so users can
quickly switch to a less destructive mode.

### Mid-range desktop

Balanced should disable the most expensive features. Aggressive can force Unlit
for heavy scenes.

### Laptop

Aggressive should be practical for daily work. Extreme can reduce heat and fan
noise during non-visual tasks.

### Remote desktop or streaming

Lower screen percentage can help remote sessions because fewer expensive pixels
need to be rendered before encoding.

## Scene-oriented recommendations

### Lumen-heavy interiors

Disable Lumen and virtual shadows first. If interaction is still poor, lower
screen percentage and force Unlit for layout-only work.

### Outdoor worlds

Disable virtual shadows, fog, and realtime. Use Unlit for large placement tasks.

### Fog-heavy scenes

Disable volumetric fog early. Fog can dominate the perceived cost of a scene
even when geometry is not the main issue.

### Material review

Avoid forcing Unlit. Lower screen percentage and disable realtime instead.

### Lighting review

Do not use Lightweight Editor Mode for final review. Disable it and verify with
production settings.

## Measuring effect

Use normal Unreal tools:

- Stat FPS
- Stat Unit
- Stat GPU
- Unreal Insights
- Viewport realtime toggle
- Output Log for plugin apply/restore messages

Measure before enabling, after enabling, and after disabling.

## Avoiding profile confusion

Give profiles clear team meanings:

- Mild: "I still care how it looks."
- Balanced: "I want general editing responsiveness."
- Aggressive: "I am arranging things."
- Extreme: "I need the editor to move."

Document any project-specific profile choices in your team wiki.

## When not to tune the plugin

If the bottleneck is not viewport rendering, profile changes may not help. Look
elsewhere when the editor is slow because of:

- Shader compilation.
- Asset loading.
- Blueprint construction scripts.
- Editor tick from custom tools.
- Source control.
- Disk IO.
- Antivirus scanning.

Lightweight Editor Mode is one tool in a broader editor performance workflow.

