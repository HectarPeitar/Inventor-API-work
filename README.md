# InventorProject

Werkomgeving voor iLogic-regels en een Autodesk Inventor add-in, opgezet om veilig
met een AI-coding-agent (bv. Cline) te kunnen werken.

## Mappenstructuur

```
InventorProject/
├── .gitignore
├── .clineignore          Houdt Cline weg bij binaire/gevoelige bestanden
├── README.md
│
├── iLogicRules/          Externe iLogic-regels als platte tekst (.iLogicVb)
│
├── AddIn/                .NET/C# Inventor add-in
│   ├── src/              Broncode (.cs)
│   ├── bin/              Build-output (genegeerd door git)
│   └── obj/              Build-output (genegeerd door git)
│
├── Docs/                 Inventor API-notities, voorbeelden, referenties
│
└── CadFiles/             WERKKOPIEEN van .ipt/.iam/.idw — nooit de originelen
```

## Belangrijke regels

1. **Nooit originele CAD-bestanden hier plaatsen.** Zet in `CadFiles/` alleen
   kopieën waarmee je test. Bewaar productiebestanden buiten deze map.
2. **Interne iLogic-regels?** Kopieer de code eerst naar een bestand in
   `iLogicRules/` voordat je Cline erop loslaat, en plak het resultaat na
   controle terug in Inventor.
3. **Open in VS Code alleen deze map als workspace**, niet je hele schijf of
   Documents-map, zodat Cline geen bestanden buiten dit project aanraakt.
4. **Commit voor je Cline aan het werk zet.** Zo kun je met `git diff` precies
   zien wat er is veranderd en met `git checkout -- <bestand>` alles
   terugdraaien.

## Setup

```bash
cd InventorProject
git init
git add .
git commit -m "Initial project structure"
```

Open daarna deze map in VS Code (File > Open Folder) en start Cline.
