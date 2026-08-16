#!/usr/bin/env python3
"""Mirror TTD plugin Documentation/<lang> trees into the Documentation repo."""

from __future__ import annotations

import argparse
import shutil
from pathlib import Path

DEFAULT_MAP = {
    "editor-extension-base": {
        "title": "Editor Extension Base",
        "source": Path("GovernanceDevelopmentPlugins/EditorExtensionBase/Documentation"),
        "landing": Path("editor-tools/EditorExtensionBase/README.md"),
    },
    "game-featured-classes": {
        "title": "Game Featured Classes",
        "source": Path("ScenePlugins/GameFeaturedClasses/Documentation"),
        "landing": Path("scene-tools/GameFeaturedClasses/README.md"),
    },
    "lightweight-dummy-actor-system": {
        "title": "Lightweight Dummy Actor System",
        "source": Path("ScenePlugins/LightweightDummyActorSystem/Documentation"),
        "landing": Path("scene-tools/LightweightDummyActorSystem/README.md"),
    },
    "internal-index-service": {
        "title": "Internal Index Service",
        "source": Path("AIPlugins/InternalIndexService/Documentation"),
        "landing": Path("ai-plugins/InternalIndexService/README.md"),
    },
    "llm-store": {
        "title": "LLM Store",
        "source": Path("AIPlugins/LLMStore/Documentation"),
        "landing": Path("ai-plugins/LLMStore/README.md"),
    },
    "unified-mcp-server": {
        "title": "Unified MCP Server",
        "source": Path("AIPlugins/UnifiedMcpServer/Documentation"),
        "landing": Path("ai-plugins/UnifiedMcpServer/README.md"),
    },
    "asset-loader-studio": {
        "title": "Asset Loader Studio",
        "source": Path("EnginePlugins/AssetLoaderStudio/Documentation"),
        "landing": Path("engine-plugins/AssetLoaderStudio/README.md"),
    },
    "unreal-capability-mesh": {
        "title": "Unreal Capability Mesh",
        "source": Path("EnginePlugins/UnrealCapabilityMesh/Documentation"),
        "landing": Path("foundation-plugins/UnrealCapabilityMesh/README.md"),
    },
    "best-practices-journal": {
        "title": "Best Practices Journal",
        "source": Path("GovernanceDevelopmentPlugins/BestPracticesJournal/Documentation"),
        "landing": Path("editor-tools/BestPracticesJournal/README.md"),
    },
    "code-copyright-editor": {
        "title": "Code Copyright Editor",
        "source": Path("GovernanceDevelopmentPlugins/CodeCopyrightEditor/Documentation"),
        "landing": Path("editor-tools/CodeCopyrightEditor/README.md"),
    },
    "lightweight-editor-mode": {
        "title": "Lightweight Editor Mode",
        "source": Path("GovernanceDevelopmentPlugins/LightweightEditorMode/Documentation"),
        "landing": Path("editor-tools/LightweightEditorMode/README.md"),
    },
    "log-level-editor": {
        "title": "LogLevelEditor",
        "source": Path("GovernanceDevelopmentPlugins/LogLevelEditor/Documentation"),
        "landing": Path("editor-tools/LogLevelEditor/README.md"),
    },
    "naming-convention-utility": {
        "title": "Naming Convention Utility",
        "source": Path("GovernanceDevelopmentPlugins/NamingConventionUtility/Documentation"),
        "landing": Path("editor-tools/NamingConventionUtility/README.md"),
    },
    "performance-preset-wizard": {
        "title": "Performance Preset Wizard",
        "source": Path("GovernanceDevelopmentPlugins/PerformancePresetWizard/Documentation"),
        "landing": Path("editor-tools/PerformancePresetWizard/README.md"),
    },
    "smart-content-diet": {
        "title": "Smart Content Diet",
        "source": Path("GovernanceDevelopmentPlugins/SmartContentDiet/Documentation"),
        "landing": Path("editor-tools/SmartContentDiet/README.md"),
    },
    "visual-fidelity-director": {
        "title": "Visual Fidelity Director",
        "source": Path("GovernanceDevelopmentPlugins/VisualFidelityDirector/Documentation"),
        "landing": Path("editor-tools/VisualFidelityDirector/README.md"),
    },
    "async-spline-builder": {
        "title": "Async Spline Builder",
        "source": Path("ScenePlugins/AsyncSplineBuilder/Documentation"),
        "landing": Path("scene-tools/AsyncSplineBuilder/README.md"),
    },
    "procedural-generated-structures": {
        "title": "Procedural Generated Structures",
        "source": Path("ScenePlugins/ProceduralGeneratedStructures/Documentation"),
        "landing": Path("scene-tools/ProceduralGeneratedStructures/README.md"),
    },
}
LANGS = ("en", "de", "fr", "it", "es", "ja", "zh")


def ensure_root_readme(
    dest_root: Path,
    *,
    title: str,
    slug: str,
    landing: Path,
    dry_run: bool,
) -> None:
    readme = dest_root / "README.md"
    if readme.is_file():
        return
    landing_display = landing.as_posix().removesuffix("/README.md")
    content = (
        f"# {title}\n\n"
        f"This path matches descriptor `DocsURL` "
        f"`https://docs.tiny-tool-development.com/{slug}/`.\n\n"
        f"Canonical category landing: "
        f"[{landing_display}](../{landing.as_posix()}).\n\n"
        "## Available languages\n\n"
        "Buyer docs are available under `/en/`, `/de/`, `/fr/`, `/it/`, "
        "`/es/`, `/ja/`, and `/zh/` (English remains the default landing).\n"
    )
    if dry_run:
        print(f"[dry-run] create {readme}")
        return
    dest_root.mkdir(parents=True, exist_ok=True)
    readme.write_text(content, encoding="utf-8")


def sync_one(
    src_doc: Path,
    dest_root: Path,
    *,
    title: str,
    slug: str,
    landing: Path,
    dry_run: bool,
) -> int:
    copied = 0
    ensure_root_readme(
        dest_root,
        title=title,
        slug=slug,
        landing=landing,
        dry_run=dry_run,
    )
    for lang in LANGS:
        src_lang = src_doc / lang
        if not src_lang.is_dir():
            continue
        dest_lang = dest_root / lang
        if not dry_run:
            dest_lang.mkdir(parents=True, exist_ok=True)
        for path in sorted(src_lang.glob("*.md")):
            dest = dest_lang / path.name
            if dry_run:
                print(f"[dry-run] {path} -> {dest}")
            else:
                shutil.copy2(path, dest)
            copied += 1
    readme = dest_root / "README.md"
    if readme.is_file() and not dry_run:
        text = readme.read_text(encoding="utf-8")
        marker = "## Available languages"
        note = (
            "## Available languages\n\n"
            "Buyer docs are available under `/en/`, `/de/`, `/fr/`, `/it/`, "
            "`/es/`, `/ja/`, and `/zh/` (English remains the default landing).\n"
        )
        if marker not in text:
            readme.write_text(text.rstrip() + "\n\n" + note, encoding="utf-8")
    return copied


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument(
        "--ttd-root",
        type=Path,
        default=Path(r"D:\TinyToolDevelopment\Git"),
    )
    parser.add_argument(
        "--docs-root",
        type=Path,
        default=Path(r"D:\TinyToolDevelopment\Documentation"),
    )
    parser.add_argument("--dry-run", action="store_true")
    args = parser.parse_args()

    total = 0
    for slug, meta in DEFAULT_MAP.items():
        src = args.ttd_root / meta["source"]
        dest = args.docs_root / slug
        if not src.is_dir():
            print(f"[warn] missing source {src}")
            continue
        count = sync_one(
            src,
            dest,
            title=str(meta["title"]),
            slug=slug,
            landing=Path(meta["landing"]),
            dry_run=args.dry_run,
        )
        print(f"{slug}: copied={count}")
        total += count
    print(f"Done. total_copied={total}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
