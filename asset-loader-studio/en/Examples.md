# Examples

These examples use package-real fields and profile ids. Replace `/Game/...` paths with assets from
your project before running them.

Inspect a DataTable:

```json
{
  "source_asset_path": "/Game/Data/DT_Items.DT_Items",
  "filter_text": "sword",
  "include_diagnostics": true
}
```

Preview a DataAsset field edit:

```json
{
  "profile_id": "guided_safe",
  "operation_request": {
    "operation_id": "rename-display-name",
    "kind": "update",
    "permission_profile_id": "guided_safe",
    "dry_run": false,
    "require_approval": true,
    "targets": [
      {
        "asset_path": "/Game/Data/DA_Item.DA_Item",
        "row_id": "asset",
        "field_id": "DisplayName",
        "new_value": "Long Sword"
      }
    ]
  }
}
```

Preview a duplicate workflow:

```json
{
  "profile_id": "guided_safe",
  "operation_request": {
    "operation_id": "duplicate-item-template",
    "kind": "duplicate",
    "permission_profile_id": "guided_safe",
    "dry_run": false,
    "require_approval": true,
    "targets": [
      {
        "asset_path": "/Game/Data/DA_Item.DA_Item",
        "destination_path": "/Game/Data/DA_Item_Copy.DA_Item_Copy"
      }
    ]
  }
}
```

Preview a DataAsset create workflow:

```json
{
  "profile_id": "guided_safe",
  "operation_request": {
    "operation_id": "create-item-dataasset",
    "kind": "create",
    "permission_profile_id": "guided_safe",
    "dry_run": false,
    "targets": [
      {
        "destination_path": "/Game/Data/DA_NewItem.DA_NewItem",
        "target_class_path": "/Script/Engine.DataAsset"
      }
    ]
  }
}
```

Submit a load request:

```json
{
  "request_id": "load-ui-icons",
  "source_context": "example",
  "soft_object_paths": ["/Game/UI/T_Icon.T_Icon"],
  "timeout_seconds": 10,
  "allow_partial_success": true
}
```

Read governance state:

```json
{
  "include_profiles": true,
  "include_route_overrides": true,
  "include_audit_status": true
}
```

Read recent audit entries:

```json
{
  "limit": 25,
  "operation_id": "rename-display-name"
}
```
