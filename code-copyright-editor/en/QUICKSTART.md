<!-- doc-provenance: product-facts.yml reconciled 2026-06-20; source AKDB:plugins/CodeCopyrightEditor/architecture.md -->
# Quick Start

This guide takes you from install to a **real result**: a consistent copyright notice applied to
selected source files, with a scan report you can open. Code Copyright Editor works entirely on its
own — no other plugin is required.

## What You'll Have After This Guide

Your owner/license configured, the codebase scanned with per-file status, and a controlled rewrite
applied to the files you selected — plus a JSON scan report under `Saved/CodeCopyrightEditor/`.

## Requirements

- Unreal Engine 5 editor (the plugin runs in the editor, not in packaged games).
- A C++ or Blueprint project with source/plugin folders to scan.
- No third-party software, account, or external runtime. See
  [THIRD_PARTY_SOFTWARE.md](THIRD_PARTY_SOFTWARE.md).

## 1. Install And Enable

1. Add **Code Copyright Editor** from your Fab library to the project (or install to the engine).
2. In the editor, open **Edit → Plugins**, enable **Code Copyright Editor**, and restart when asked.

## 2. Open The Tool (First Result)

1. Open **Tools → Code Tools → Code Copyright Editor**.
2. On the **Configure** tab, set your identity and license (owner, license identifier, template,
   scan scope). Click **Save**.
3. Switch to **Scan & Review** and click **Scan Files**.

You now see every eligible file with a status badge (`OK`, `MISSING`, `REPLACE`, `PROTECTED`, …).
Scanning never writes files — this is a safe preview.

## 3. A Real Worked Example: Apply Notices To Selected Files

1. On **Scan & Review**, click **Select Changeable** — this checks only the rows that can be safely
   rewritten (`MISSING`, `REPLACE`). `PROTECTED` and `CONFLICT` files stay untouched.
2. Select a single row first and compare the **existing** vs **proposed** notice in the preview.
3. (Recommended) On the **Configure** tab, enable **Create Backup Before Write**, and commit your
   work to source control first.
4. Click **Apply Selected** and confirm. The tool rewrites only the checked, changeable files and
   then re-scans.

**Expected output:** applied files move to status `UPDATED`; the apply result and a fresh scan are
shown. On **Apply & Reports**, click **Export JSON**.

## 4. Where Results Live

```text
Saved/CodeCopyrightEditor/LastCopyrightScan.json
```

You can also update the project-level notice (no source rewrite) with **Update Project Notice**,
which writes to *Project Settings → Project → Description → Legal → Copyright Notice*.

## 5. Next Steps

- Full workflow and every tab/action: [UserManual.md](UserManual.md).
- All template tokens (`{CopyrightText}`, `{LicenseIdentifier}`, `{FileMetadataBlock}`, …):
  [TemplateReference.md](TemplateReference.md).
- Settings fields: [SettingsReference.md](SettingsReference.md).
- Reports/compliance: [ReportsAndCompliance.md](ReportsAndCompliance.md).
- Problems: [TROUBLESHOOTING.md](TROUBLESHOOTING.md) and [FAQ.md](FAQ.md).

---

> **Optional, for CI maintainers:** Code Copyright Editor also ships a headless commandlet so you
> can check notices in continuous integration. It is optional and not needed for the editor
> workflow above — see [CommandletAndCI.md](CommandletAndCI.md).
