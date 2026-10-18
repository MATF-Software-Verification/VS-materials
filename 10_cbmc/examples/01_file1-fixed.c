int puts(const char *s) {}

int main(int argc, char **argv) {
    if (argc > 2)
        puts(argv[2]);
}
