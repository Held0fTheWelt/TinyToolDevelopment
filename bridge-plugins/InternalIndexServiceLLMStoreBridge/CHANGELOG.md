# Changelog

All notable changes to IIS LLM Store Bridge will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/de/1.0.0/),
and this plugin adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [Unreleased]

## [1.0.1] - 2026-06-16

### Fixed
- Hardened shutdown restore for `EmbeddingExecutorId`: the bridge now restores the previous IIS executor on engine pre-exit while settings are still available, and avoids creating or fetching `UIISSettings` during late editor teardown.

### Added
- Initial Freebie bridge plugin for projects that own both Internal Index Service and LLM Store.
- Registered an IIS embedding executor named `llmstore` through `IModularFeatures`.
- Added runtime bridge code that forwards IIS embedding route resolution and execution to LLM Store through the public `ILLMStore` interface.
- Added automatic IIS runtime selection: while the bridge is loaded, it sets IIS `EmbeddingExecutorId` to `llmstore`; when unloaded, it restores the previous value if it still owns the setting.
- Added Blueprint diagnostics and smoke-test helpers for executor registration, route resolution, and simple embedding execution.
- Added compact product, setup, runtime contract, source overview, and troubleshooting documentation.

### Security
- Kept provider credentials, provider selection, model routing, fallback behavior, and network policy inside LLM Store. The bridge only adapts IIS embedding DTOs to LLM Store embedding DTOs.

## [1.0.0] - 2026-06-15

### Added
- First plugin package skeleton for the optional IIS LLM Store Bridge.
