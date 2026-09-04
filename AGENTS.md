# Agent notes — Trein (Stef)

Read **[HANDOVER.md](HANDOVER.md)** before editing.

- Branch: `cursor/emery-time2-layout-1675` (not `main`). PR: https://github.com/SBerkers/trein-pebble/pull/1
- GitHub is source of truth. CloudPebble ([cloudpebble.repebble.com](https://cloudpebble.repebble.com)) only compiles, installs on the Time 2, and shows logs.
- Layout is **emery / Pebble Time 2** only. Do not redesign other platforms.
- OVER is real OpenRouteService duration, never a haversine stand-in, never equal to VERTREK.
- Delay timer sits **under** the VERTREK clock. Chrome uses GOTHIC_24; shrink **padding**, not type.
- Do not put API keys in the repo. Do not ship `TREIN_LAYOUT_FIXTURE` enabled to CloudPebble.
- SDK: Repebble (`pebble-tool`, `pebble sdk install latest` from sdk.repebble.com), not Rebble.
