# VS materials

Quarto book source for the "Verifikacija softvera - Vežbe" course materials.

## Layout

| Path | Description |
|------|-------------|
| `01_debugging/` ... `12_dafny/` | Chapter source directories (`.qmd` + code labs + images) |
| `index.qmd` | Book front page / abstract |
| `_quarto.yml` | Book configuration (HTML + PDF formats) |
| `build` | Full build: validate + render PDF + HTML |
| `check` | Validate environment + residual LaTeX scan + image path checks |

## Build

```sh
./build
```

This runs `./check`, then renders both outputs into `_book/`:

- `_book/index.html` — HTML book (primary)
- `_book/Verifikacija-softvera---Vežbe.pdf` — PDF (via XeLaTeX)

## Deploy to GitHub Pages

Push the `gh-pages` branch with the contents of `_book/`:

```sh
quarto publish gh-pages
```

Or manually: after `./build`, copy `_book/` contents to the `gh-pages` branch.
