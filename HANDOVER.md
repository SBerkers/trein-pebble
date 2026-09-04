# Trein (Stef) — agent handover

Hand this file to the next Grok/Cursor agent. Source of truth is **GitHub**, not a stale local checkout.

**Paste into a new chat:**

> Read `HANDOVER.md` and `AGENTS.md` in this repo. Continue Trein (Stef) on branch `cursor/emery-time2-layout-1675`. Do not start from `main` or upstream. Layout is emery/Time 2 only. GitHub is source of truth; CloudPebble is compile + watch + logs. Do not merge upstream unless Stef asks. Do not put API keys in git.

---

## Repo

| | |
|---|---|
| Fork | https://github.com/SBerkers/trein-pebble |
| Upstream | https://github.com/guusbeckett/trein-pebble — **do not merge unless Stef asks** |
| Branch | `cursor/emery-time2-layout-1675` (**not** `main`) |
| PR | https://github.com/SBerkers/trein-pebble/pull/1 |
| HEAD at handover | `2ffb655` — **v1.7.23** |
| UUID | `026fe1f0-12c4-4598-b240-7cc69509d724` |
| displayName | Trein (Stef) |
| Config page | https://sberkers.github.io/trein-pebble/config.html |
| Owner | Stef, Pebble Time 2 (**emery**, 200×228, colour) |

```bash
git clone https://github.com/SBerkers/trein-pebble.git
cd trein-pebble
git checkout cursor/emery-time2-layout-1675
```

## Who does what

Stef compiles on a **real Time 2** via **CloudPebble in Chrome**. He does not need a local ARM toolchain.

The agent edits in Cursor, **pushes this branch**, then Stef (or the agent, if CloudPebble is logged in) Pulls and installs.

| Role | Tool |
|---|---|
| Edit C/JS | Cursor on this repo |
| Compile for the watch | [CloudPebble](https://cloudpebble.repebble.com) — GitHub import of this branch |
| Layout screenshots before a pixel-sensitive push | Repebble SDK emulator, platform **emery** (Ubuntu/cloud agent). Not Rebble/rebbletool. |
| Live NS / ORS / GPS | Physical watch + phone. Emulator has no keys/GPS unless injected. |

Windows cannot run the Pebble SDK natively. Do not fight WSL/Hyper-V on Stef’s PC.

---

## CloudPebble loop (preferred for watch work)

Stef already has CloudPebble logged in, Dev Connect on, and logs working.

1. Agent commits and **pushes** `cursor/emery-time2-layout-1675`.
2. CloudPebble → **GitHub → Pull** (do not re-import unless Pull is stuck).
3. Confirm `package.json` version (must match the push, currently **1.7.23**).
4. **Compile** → **Install and Run**.
5. Stef reproduces on the watch; paste Compilation / log pane here.

Phone: Pebble app → Devices → ⋮ → **Dev Connect** on. Same Pebble/GitHub account as CloudPebble.

Connection: **Cloud relay** (`wss://cloudpebble-proxy.repebble.com`) — no USB, no LAN IP.

If the agent can use a logged-in CloudPebble tab, Pull/Compile/Install there. Cursor’s built-in browser is often **logged out**; Stef’s Chrome session is the one that works. Do not ask Stef to paste C into CloudPebble.

**Do not enable** `TREIN_LAYOUT_FIXTURE` on a CloudPebble/watch build. It is compile-time only (`wscript` + env). Default in `trein.c` is `-1` (off). CloudPebble builds stay live NS.

---

## Repebble emulator (layout only)

Docs: https://developer.repebble.com/sdk/

```bash
uv tool install pebble-tool
pebble sdk install latest   # from https://sdk.repebble.com — SDK 4.33.x
```

Three mock countdown screens (no NS key):

```bash
export TREIN_LAYOUT_FIXTURE=0   # ORS dual Tilburg Univ → Amsterdam C
pebble build && pebble install --emulator emery
# screenshot, then repeat with 1 (Aankomst Tilburg → Den Bosch) and 2 (Vertrek+delay Den Bosch → Tilburg)
```

`pebble clean` / wipe `build/` between fixture numbers so the `-D` sticks.

v1.7.23 fixtures were **PASS** on emery qemu (delay under the clock, ~36px chrome with GOTHIC_24, one cream-inset leg, no VAN/NAAR overlap). Stef still needs to confirm on the **physical** Time 2 after CloudPebble Pull.

---

## Product rules (do not “simplify” these)

- **Emery-only layout.** Do not redesign flint/basalt/chalk/diorite.
- **OVER** = real OpenRouteService walk/bike duration vs **actual** departure (planned + delay), minus station offset. Never equal VERTREK. **No haversine-as-OVER.**
- Dual OVER+VERTREK only if `reistijd` on **and** ORS duration present **and** not at station **and** train not departed.
- At station (~150 m): no OVER; hero VERTREK or AANKOMST; cream band.
- **VERTREK** = countdown to **planned** departure. Delay is a **separate red timer under** that clock (not beside — beside wraps `00:0-` on LECO 42).
- **OVER** uses actual departure minus walk minus offset.
- OVER colours: green >2 min slack, orange 0–2 (not yellow-on-yellow), red <0; cream when at station.
- **AANKOMST** = when the selected train arrives on the **VAN** platform (origin arrival), not destination arrival.
- Footer HH:MM = **planned** destination arrival.
- Duration `1u21` / `20m` = actual destination arrival epoch − planned departure epoch.
- **Departed** only when NS `departureStatus === "DEPARTED"`, not when the clock hits 0.
- Chrome times stay **GOTHIC_24_BOLD**. Thinner bars = less **padding**, not smaller type. Names **GOTHIC_18_BOLD**, NS `namen.kort`.
- Bike profile: **`cycling-regular`** (NL fietspaden), not `cycling-road`.
- ORS host: **HeiGIT only** `https://api.heigit.org/openrouteservice/v2/directions/` with `?api_key=` **and** `Authorization` header. Pebble XHR often strips Authorization; query key is required. Compact POST (`geometry: "false"`, etc.) like the playground.

## API shape (keep it small)

- Initial: NS trips v3, ≤5 trips.
- Every 30s: one `/api/v2/departures?station=&maxJourneys=12`, match selected train, send live `TRIP_INDEX` + actual epoch + delay + `TRIP_DEPARTED` + platform.
- ORS only if GPS moved >80 m. Cache 403.
- Do **not** bring back a 60-train board, full trips every 2 min, or 3 auth-mode retries.

Keys live in **phone** `localStorage` via the config page (`api_key`, `routing_api_key`). Never commit keys. Logs: `getOrsKey: length=N`, `ORS status:`, `origin arr iso=`, `live trip` — never the key string.

## Layout (emery countdown)

Blue chrome **36px**. Times GOTHIC_24 in ~30px slots (side ~60px). Names GOTHIC_18 in the remaining centre. Destination name Y = **bottom bar**, not top (`bot_name_y` was a real overlap bug).

Cream: duration + platform, then clocks, then **one** vertical leg (`transfers+1` or `trip_legs[].leg_count`). Inset 10px inside cream, not into chrome. Direct train = 1 line + 2 dots.

Hero VERTREK/AANKOMST: label high, LECO_42 clock, delay LECO_26 **under** it, centred.

Dual: OVER (Roboto 49 / LECO 42) then VERTREK LECO_26, delay under VERTREK, left-aligned, full width.

## Files

| Path | Role |
|---|---|
| `src/c/trein.c` | Watch UI, countdown, chrome, fixtures |
| `src/c/trein_data.h` | Trip/routing structs, `departed[]` |
| `src/pkjs/index.js` | NS, ORS, live departures, short names |
| `wscript` | Optional `-DTREIN_LAYOUT_FIXTURE=N` |
| `package.json` | Version + `messageKeys` (incl. `TRIP_DEPARTED`) |
| `config.html` | Phone settings |

Version every watch-facing change (`1.7.xx`). Commit style: `v1.7.23: why, not what.`

## Open / verify on the watch

1. **Physical Time 2 after CloudPebble Pull of 1.7.23** — emulator passed; watch not signed off in this handover.
2. **ORS 403** — phone logs `Access to this API has been disallowed` were from older builds. 1.7.21+ is HeiGIT + query key. Confirm `ORS status: 200` with a key in **phone** storage (config page), not only playground.
3. **Aankomst** — NS trips often omit origin arrival (`origin arr iso=none` → fallback to departure, so Aankomst ≈ Vertrek). Fix parse / arrivals API; don’t fake it with dest arrival.
4. Delay wrap `00:0-` should be gone with stacked delay; confirm with a delayed train on device.
5. Crash dest-menu → countdown was fixed 1.7.15–1.7.17 (`dest_menu_layer` destroyed **before** countdown alloc). Don’t resurrect post-unload `menu_layer_destroy`.

## Hard no’s

- No flint redesign, no haversine OVER, no delay beside the hero clock, no shrinking GOTHIC_24 to make bars look thinner.
- No force-push to `main`. This PR branch is fine to push.
- No CloudPebble-only edits that never get **GitHub → Push** (they will be overwritten on the next Pull).
- Fixture boot must stay behind `#if TREIN_LAYOUT_FIXTURE >= 0`.
