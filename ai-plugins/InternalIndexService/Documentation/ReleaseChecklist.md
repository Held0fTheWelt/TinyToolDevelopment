# Release Checklist

## Build

- [ ] UE 5.4 build succeeds.
- [ ] UE 5.5 build succeeds if targeted.
- [ ] UE 5.6 build succeeds.
- [ ] IIS `.Build.cs` files use C++20.
- [ ] `git diff --check` is clean.

## Source Headers

- [ ] Every IIS `.h`, `.cpp`, `.cs`, and `.py` file has a top comment with `Publisher: Tiny Tool Development`.
- [ ] Every IIS code file includes `Intended publication year: 2026`.
- [ ] Bundled third-party headers contain the bundle notice without removing upstream license files.
- [ ] `THIRD_PARTY_SOFTWARE.md` is current.

## Documentation

- [ ] `README.md` is current.
- [ ] `BUYER_GUIDE.md` explains scope and limits.
- [ ] `QUICKSTART.md` describes first use.
- [ ] `UserManual.md` describes editor workflows.
- [ ] `TechnicalOverview.md` describes architecture and data flow.
- [ ] `CodeDocumentation.md` maps the C++ source.
- [ ] `INTEGRATION.md` explains companion plugin boundaries.
- [ ] `SettingsReference.md` documents settings and paths.
- [ ] `FAQ.md` and `TROUBLESHOOTING.md` cover common review questions.

## Functional Smoke

- [ ] Control Panel opens from **Tools → AI → Internal Index Service**.
- [ ] Settings page is visible.
- [ ] Prepared chunks import succeeds.
- [ ] Catalog rebuild writes a report.
- [ ] Lexical search returns expected chunks.
- [ ] Embedding job build handles missing executor cleanly.
- [ ] Agent contracts are written.
- [ ] UMCP bridge exposes `iis_*` tools when enabled.

## Packaging

- [ ] `Config/FilterPlugin.ini` includes documentation and intended extra files.
- [ ] `Source/ThirdParty/hnswlib/LICENSE` and `NOTICE.md` are included.
- [ ] No local Python cache files are included.
- [ ] No local gate config or private generated data is included.
- [ ] Fab third-party software declaration includes hnswlib.
