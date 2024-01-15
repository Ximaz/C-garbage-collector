# C Garbage Collector

A humble attempt to create a pseudo garbage collector in C.

# Functions

```c
// Memory allocation interface
void *gc_alloc(gc_t *gc, size_t size);

// Memory-specific destruction interface (only the specified address)
bool gc_free(gc_t *gc, void *address);

// Memory destruction interface (any allocated memory)
bool gc_free_all(gc_t *gc);
```

# Setup

Compilation is done using `make` command :

```bash
git clone https://github.com/Ximaz/C-garbage-collector
cd C-garbage-collector
make
```

Once compilatoin is done, you get a `libgc.a` file that you can link to your projects.
