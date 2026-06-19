# Cost Tracking

LLM Store records AI usage so a team can analyze cost by provider, model, and route.

## What Is Recorded?

Each executed request can create an `FLLMAuditEvent` containing:

- timestamp
- task route
- provider id
- provider type
- model id
- operation type
- success state
- result code
- cache-hit flag
- prompt tokens
- completion tokens
- total tokens
- estimated cost
- message or error summary

The same event stream powers the audit view and the cost report.

## Ledger Location

The cost ledger is stored under:

```text
Saved/LLMStore/CostLedger.json
```

It is saved in `Saved` because usage data may contain sensitive route names, model names, or project workflow information. Do not commit it unless your team explicitly wants to archive usage history.

## Cost Rules

Costs are estimated from `FLLMCostRule` entries.

Fields:

| Field | Meaning |
| --- | --- |
| `ProviderType` | Provider type such as `openai`, `anthropic`, or `mistral`. |
| `ModelId` | Optional project-local model id. Empty can apply to all models for the provider type. |
| `InputCostPer1KTokens` | Prompt/input cost per 1000 tokens. |
| `OutputCostPer1KTokens` | Completion/output cost per 1000 tokens. |
| `Currency` | Currency label, normally `USD`. |

Example:

```text
ProviderType: openai
ModelId: openai-fast
InputCostPer1KTokens: 0.00015
OutputCostPer1KTokens: 0.00060
Currency: USD
```

## Token Counts

When a provider returns usage information, LLM Store uses it.

When usage information is missing, the store estimates tokens. Estimates are sufficient for trend analysis and budget warnings, but provider billing remains the source of truth for exact invoices.

## Costs Tab

The `Costs` tab shows:

- total events
- successes
- cache hits
- prompt tokens
- completion tokens
- total tokens
- estimated total cost
- breakdown by provider
- breakdown by model
- breakdown by task route
- recent events

## CSV Export

Use `Export CSV` to write:

```text
Saved/LLMStore/CostReports/LLMStoreCostReport.csv
```

The CSV is useful for:

- finance review
- comparing local and cloud routes
- finding expensive workflows
- validating cache usefulness
- preparing release or internal adoption reports

## Cache Hits

Cached responses are counted separately. A cache hit can reduce provider calls and cost, but it still records an event so usage analysis remains complete.

## Local Model Costs

Local models can use `0` cost rules or internal accounting values.

Examples:

- `0` for fully free local usage
- approximate GPU cost per 1000 tokens
- internal chargeback values for shared inference servers

## Budget Policies

Route policies can set `MaxEstimatedCost`. This depends on:

- token estimation
- cost rules
- provider usage data when available

For production cloud routes, add cost rules before enabling cost limits.

## Clearing the Ledger

The editor and Blueprint API expose a clear operation for the cost ledger. Use it carefully; it removes usage history from the local saved ledger.

Recommended before clearing:

1. Export CSV.
2. Confirm the ledger is not needed for audit.
3. Clear only on the intended machine or branch.

## Privacy Notes

The ledger should not include full prompts by default, but route names, model ids, and error messages can still reveal project information. Treat the ledger as project-sensitive operational data.

