# VS materials

LaTeX source for the course materials PDF.

## Build

Run:

```sh
make MATERIALS.pdf
```

The local build uses `latexmk`, XeLaTeX, and `minted`, so Python/Pygments must be available for syntax highlighting. On Overleaf, compile `MATERIALS.tex` with XeLaTeX.

Legacy Markdown sources from the migration are archived under `_legacy_markdown/` and are not part of the PDF build.
