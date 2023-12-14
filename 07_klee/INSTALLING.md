## Simboličko izvršavanje

### KLEE

KLEE se može instalirati prateći uputstva na zvaničnoj [stranici](https://klee.github.io/getting-started/). Preporučeno je koristiti Docker kontejner:
```sh
$ docker pull klee/klee:3.0
$ docker run --rm -ti --ulimit='stack=-1:-1' klee/klee:3.0
```
