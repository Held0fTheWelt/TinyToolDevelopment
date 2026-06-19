# Buyer Guide

## What This Plugin Is

UII Internal Index Service Bridge is an optional companion plugin for users who have both:

- **Unreal Integration Intelligence**; and
- **Internal Index Service**.

It exists to connect UII handoff artifacts to IIS indexing workflows without adding UII-specific logic to the IIS core plugin.

## Why It Exists

UII and IIS intentionally have different responsibilities:

- UII knows how to inspect Unreal projects and produce evidence.
- IIS knows how to import prepared evidence and make it searchable.

The bridge connects those responsibilities through a handoff contract.

## Who Should Use It

Use this bridge if:

- you own and use both UII and IIS;
- UII generates `iis_import_contract.json`;
- you want one command or menu action to import UII prepared chunks into IIS;
- you want IIS catalog, embedding job, smoke search, and agent contract actions chained after import.

You do not need this bridge if:

- you only import generic prepared chunks JSONL into IIS;
- you do not use UII;
- you want a custom evidence producer to write directly to IIS import APIs.

## Product Boundary

This repository does not include UII or IIS source code. It expects IIS to be installed and expects UII, or an equivalent producer, to generate compatible handoff files.

The bridge is a benefit layer for combined installations, not a standalone extraction tool and not a standalone indexing system.

