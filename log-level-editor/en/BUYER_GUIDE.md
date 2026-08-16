# Buyer Guide

LogLevelEditor gives Unreal Engine teams a practical log-verbosity control surface inside the editor. Instead of remembering console commands, scanning source files manually, or editing ini files for every investigation, users can inspect discovered categories and apply verbosity changes from one place.

## Who It Is For

LogLevelEditor is useful for:

- Solo developers who need cleaner Output Log sessions.
- Technical artists who need to quiet unrelated plugin channels.
- Gameplay programmers who frequently switch systems to `Verbose` or `VeryVerbose`.
- Tools programmers who maintain several editor plugins.
- QA and support teams who need reproducible diagnostic logging.

It is especially helpful in projects with many plugins where log channels accumulate quickly and the default Output Log becomes hard to scan.

## Core Value

The plugin focuses on three everyday problems:

1. Discovery: find project and plugin log categories without manual grep work.
2. Control: change log verbosity from an editor UI.
3. Persistence: save intentional overrides in a DataAsset and reapply them on startup.

The result is not a new logging framework. It is a practical layer over Unreal's existing log category and console command system.

## What Makes It Different

- It scans common Unreal log category declarations instead of relying only on hard-coded lists.
- It distinguishes detected default verbosity from active override intent.
- It stores persistent overrides in an asset that can be inspected, versioned, and shared.
- It supports temporary hide settings for local focus without polluting source control.
- It applies saved values after editor startup with retry handling.

## Typical Buyer Scenarios

### Debugging A Specific System

A programmer raises only `LogInventory`, `LogAbilitySystem`, or `LogMyPlugin` to `Verbose`, reproduces a bug, then restores the detected default from the same row.

### Reducing Plugin Noise

A content-heavy project uses multiple marketplace plugins. The team hides or lowers unrelated channels while investigating one plugin.

### Standardizing Support Logs

A support engineer provides a known DataAsset with recommended verbosity levels, then asks a user to reproduce an issue after restarting the editor.

### Team-Friendly Editor Setup

Persistent rules live in a DataAsset rather than being hidden in one user's local console history.

## Before You Buy

The plugin is editor-only. It is intended for debugging, support, development, and project hygiene in the Unreal Editor.

It does not:

- Replace Unreal's Output Log.
- Add remote logging.
- Modify C++ source declarations.
- Guarantee that all categories are discoverable when declarations use unusual macro wrappers.
- Force runtime modules to keep a verbosity if those modules change it later.

## Recommended Price Positioning

This plugin belongs in the small productivity-tool category. It is narrow, practical, and low-risk when documented well.

Suggested Fab positioning:

- Personal launch price: USD 9.99 to 14.99.
- Professional launch price: USD 24.99 to 34.99.
- Discount campaigns: 20 percent launch discount can help early adoption.

## Buyer-Facing Summary

Use LogLevelEditor when you want a clean, editor-native way to discover log categories, adjust verbosity, hide noise, and persist intentional logging setups without writing custom tooling or editing ini files manually.
