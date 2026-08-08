#!/usr/bin/env python3
"""Mirror TTD plugin Documentation/<lang> trees into the Documentation repo."""

from __future__ import annotations

import argparse
import shutil
from pathlib import Path

DEFAULT_MAP = {
    "editor-extension-base": Path(
        "GovernanceDevelopmentPlugins/EditorExtensionBase/Documentation"
    ),
    "game-featured-classes": Path(
        "ScenePlugins/GameFeaturedClasses/Documentation"
    ),
    "lightweight-dummy-actor-system": Path(
        "ScenePlugins/LightweightDummyActorSystem/Documentation"
    ),
}
LANGS = ("en", "de", "fr", "it", "es", "ja", "zh")


def sync_one(src_doc: Path, dest_root: Path, *, dry_run: bool) -> int:
    copied = 0
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
    for slug, rel in DEFAULT_MAP.items():
        src = args.ttd_root / rel
        dest = args.docs_root / slug
        if not src.is_dir():
            print(f"[warn] missing source {src}")
            continue
        count = sync_one(src, dest, dry_run=args.dry_run)
        print(f"{slug}: copied={count}")
        total += count
    print(f"Done. total_copied={total}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
