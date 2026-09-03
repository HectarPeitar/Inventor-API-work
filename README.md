# Inventor API Work

Workspace for Autodesk Inventor automation (iLogic rules and .NET add-ins),
structured to work safely and effectively with an AI coding agent (Cline).

## Directory Structure

```
Inventor-API-work/
├── .clinerules/          Behavior rules for Cline (source hierarchy,
│                         verification requirements, what to store where)
├── .gitignore
├── .clineignore
├── README.md
│
├── knowledge/            Normalized technical knowledge, by topic
│   ├── APInotes.md         General API concepts
│   ├── api-compatibility.md  Version / .NET / Interop compatibility
│   ├── object-model.md     Relationships between API objects
│   ├── ilogic.md           iLogic-specific knowledge
│   ├── addins.md           .NET add-in architecture
│   ├── assemblies.md       Assembly API
│   ├── parameters.md       Parameter automation
│   └── units.md            Units and pitfalls
│
├── reference/            Raw external source material (e.g. Autodesk
│                         DevTech training material). Kept locally, but
│                         excluded from git (see .gitignore).
│
├── examples/              Standalone, illustrative examples (not
│                         necessarily verified) — "how might this work?"
│   └── ilogic/
│
├── tested/               Small patterns actually verified in Inventor —
│                         "this is proven to work"
│   └── ilogic/
│
├── templates/            Starting points for new projects
│   └── addin/
│
├── addins/               Active, complete .NET add-in projects
│                         (built/debugged via Visual Studio)
│
├── scratch/              Temporary experiments, not yet part of a real
│                         project
│
└── cadfiles/             WORKING COPIES of .ipt/.iam/.idw — never the
                          originals. Fully excluded from git.
```

## Core Principles

1. **Never place original CAD files in this project.** Only working copies
   in `cadfiles/`. The entire directory is excluded from git.
2. **Cline does not invent API members.** Unknown properties/methods/enums
   are verified against the source hierarchy in `.clinerules/00-core.md`
   before being used.
3. **The distinction between knowledge levels is intentional**: `examples/`
   is illustrative, `tested/` is proven to work in Inventor itself,
   `reference/` is raw source material. Do not confuse these with each
   other.
4. **One authoritative location per add-in**, in `addins/`. No duplicate
   copies in `tested/` or `scratch/` — only reusable patterns are extracted
   from those.
5. **Open only this directory as the VS Code workspace**, so Cline cannot
   touch files outside this project.
6. **Commit before letting Cline work.** This lets you see exactly what
   changed with `git diff`, and revert with `git checkout -- <file>` if
   needed.

See the `README.md` in each subdirectory for the precise rules of that
directory.

## Setup

```bash
git clone <repo-url>
cd Inventor-API-work
```

Open the directory in VS Code (File > Open Folder) and start Cline. The
rules in `.clinerules/` are automatically included as context.