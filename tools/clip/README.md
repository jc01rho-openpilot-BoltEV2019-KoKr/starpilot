# Clip

`clip.py` records a video of a driving route by replaying it into a desktop UI and capturing the result. Use it to export footage of a route without watching it live.

## Setup

Install dependencies (this pulls in `uv`, `ffmpeg`, and `xvfb`):

```bash
tools/ubuntu_setup.sh
```

To clip a route from your comma account, authenticate first:

```bash
python3 tools/lib/auth.py
```

Public routes and `--demo` need no authentication.

`replay` and the c3 UI runtime are built automatically on first run, so expect the first
clip to take a few extra minutes.

## Usage

```bash
# Clip the demo route
python3 tools/clip/run.py --demo -o output.mp4

# Clip seconds 140-260 of a route, timing in the route ID
python3 tools/clip/run.py 78511c37de32c375/00000958--8cb1d3e165/140/260 -o clip.mp4

# Same, timing as flags
python3 tools/clip/run.py 78511c37de32c375/00000958--8cb1d3e165 -s 140 -e 260 -o clip.mp4
```

Recording happens in real time, so a 120s clip takes about 120s to produce.

## UI

Clips use the c3 raylib UI.

```bash
python3 tools/clip/run.py --demo -u c3 -o output.mp4
```

The UI exports its frames straight to `ffmpeg`. This bypasses screen capture, so it also works
where a compositor hides window contents from `x11grab` (notably WSLg).

## Options

| Flag | Description |
| --- | --- |
| `-o, --output` | Output path, must be `.mp4` (default `output.mp4`) |
| `-s, --start` / `-e, --end` | Clip window in seconds; omit if timing is in the route ID |
| `-u, --ui` | `c3` (default) |
| `-f, --file-size` | Target size in MB (default 9, sized for Discord/GitHub) |
| `-q, --quality` | `high` (hevc, default) or `low` (qcam) |
| `-x, --speed` | Record at this speed multiple |
| `-d, --data-dir` | Use local route data instead of downloading |
| `-p, --prefix` | openpilot prefix to isolate the run |

The default 9MB target suits short clips. For anything longer than about a minute, raise it
(`-f 250`) or the bitrate drops low enough to be visibly bad.

## WSL

Recording works on WSL2 under Windows 11, which supplies a display through WSLg.

```bash
python3 tools/clip/run.py -u c3 -f 250 -o ~/clips/foo.mp4 78511c37de32c375/00000958--8cb1d3e165/140/260
```

Running the tool rebuilds native extensions, and this repo tracks those build artifacts in git,
so the working tree ends up dirty afterwards. That does not affect running it again, it only
matters when pulling:

```bash
git checkout -- . && git pull
```

The discarded files are rebuilt on the next run. If you have source edits you want to keep,
commit or stash them instead, since `git checkout -- .` discards all unstaged changes.
