# Sample Presets Reference

Performance Preset Wizard ships with sample preset assets in the plugin content folder. They are intended as starting points, examples, and quick validation assets.

Enable **Show Plugin Content** in the Content Browser to see them.

## Included Presets

| Asset | Target Platform | Intended Use |
| --- | --- | --- |
| `DA_MobilePrototype` | Mobile Prototype | Early gameplay and feature prototyping where responsiveness matters more than visual quality. |
| `DA_LaptopDev` | Laptop Development | Daily editor work on thermally constrained laptops or low-power machines. |
| `DA_LowRange` | Desktop Low Range | Older desktop hardware or low-cost compatibility checks. |
| `DA_MidRange` | Desktop Mid Range | General-purpose review profile for common gaming PCs. |
| `DA_HighEnd` | Desktop High End | High-quality desktop review with stronger GPU assumptions. |
| `DA_UltraHighEnd` | Desktop Ultra High End | Top-tier desktop review and visual validation. |
| `DA_ConsoleLike` | Console Like | Fixed-budget review profile for console-style targets. |
| `DA_VR_Mobile` | VRHeadset Mobile | Standalone/mobile VR budget with strict performance expectations. |
| `DA_VR_HighEnd` | VRHeadset PC | PC-driven VR profile for higher-end headset workflows. |
| `DA_CinematicMenu` | Cinematic Menu / Showcase | High-quality menu, showroom, or non-interactive presentation scenes. |
| `DA_CinematicCapture4k` | Cinematic Capture 4k | High-quality capture workflows where visual output is prioritized. |

## How To Use Samples

1. Duplicate a sample into your project content folder.
2. Rename the duplicate to match your production target.
3. Update the display name and description.
4. Review every scalability level.
5. Remove CVars that do not apply to your renderer setup.
6. Add project-specific CVars only after verifying their effect.
7. Apply the preset in a representative map.
8. Use Restore Previous to confirm reversible editor workflow.

## Why Duplicate Instead Of Edit In Place

Duplicating keeps the shipped examples intact. This makes it easier to compare against the original plugin defaults after updates and gives buyers a safe baseline while experimenting.

## Recommended Sample Review

After installing the plugin, test at least these paths:

- Apply `DA_LaptopDev`, then restore.
- Apply `DA_MidRange`, then inspect the status counters.
- Open `DA_CinematicCapture4k` and review quality levels.
- Duplicate `DA_MidRange`, add a harmless CVar such as `r.ScreenPercentage=90`, and apply the duplicate.
- Configure a duplicated preset as the startup preset, then restart the editor.

## Sample Presets Are Not Universal Defaults

The included assets cannot know your map scale, material cost, target frame rate, renderer feature set, or platform profile policy. Treat them as authored examples and tune them for the project.

For production, the most useful presets are usually the ones your team names after real workflows: `Laptop Dev`, `Console Review`, `VR Standalone QA`, `Marketing Capture`, and similar.

