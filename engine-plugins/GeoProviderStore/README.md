# Geo Provider Store

Geo Provider Store is an advanced-preview Unreal provider gateway for geospatial APIs and local datasets. It makes provider capabilities, credential profiles, request policy, cache/export rules, license obligations, provenance, and reports visible before data moves downstream.

Not a verbatim copy of shipped docs.

## What It Does

- Lists mock, local, open-data, and restricted remote provider capabilities.
- Executes explicit geospatial requests with credential, network, cache, and license checks.
- Normalizes features and road-network data where provider policy allows it.
- Writes reviewed request and provider reports for local handoff.
- Keeps restricted provider payloads out of reusable exports unless policy permits that use.

## Best Entry Points

- Use the shipped `Documentation/QUICKSTART.md` for first offline `mock_geo` validation.
- Use `Documentation/UserManual.md` and `Documentation/PROVIDERS.md` for provider selection and request flow.
- Use `Documentation/SettingsReference.md`, `Documentation/LICENSE_AND_PROVENANCE.md`, and `Documentation/TROUBLESHOOTING.md` for credentials, license policy, and blocked request behavior.
