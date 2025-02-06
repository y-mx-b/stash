# --- COMPILER FLAGS ---
CC = clang
CFLAGS = -Wall -Wextra

# --- PROJECT FILES ---
SRC = $(wildcard src/*.c)
EXEC = dotcfg

# --- DEBUG BUILD ---
DDIR = .build/debug
DEXEC = $(DDIR)/$(EXEC)
DOBJS = $(patsubst src/%.c,$(DDIR)/%.o,$(SRC))
DCFLAGS = -g -O0 -DDEBUG

# --- RELEASE BUILD ---
RDIR = .build/release
REXEC = $(RDIR)/$(EXEC)
ROBJS = $(patsubst src/%.c,$(RDIR)/%.o,$(SRC))
RCFLAGS = -O2 -DNDEBUG

# --- COMMANDS ---

.PHONY: help debug debug_run release release_run clean install fmt


# --- DEBUG BUILD ---

debug: $(DDIR) $(DEXEC)

$(DDIR):
	@mkdir -p $(DDIR)

$(DEXEC): $(DOBJS)
	$(CC) $(CFLAGS) $(DFLAGS) -o $@ $^

$(DDIR)/%.o: $(SRC)
	$(CC) -c $(CFLAGS) $(DCFLAGS) -o $@ -c $<

debug_run: debug
	./$(DEXEC) $(ARGS)


# --- RELEASE BUILD ---

release: $(RDIR) $(REXEC)

$(RDIR):
	@mkdir -p $(RDIR)

$(REXEC): $(ROBJS)
	$(CC) $(CFLAGS) $(RCFLAGS) -o $@ $^

$(RDIR)/%.o: $(SRC)
	$(CC) $(CFLAGS) $(RCFLAGS) -o $@ -c $<

release_run: release
	./$(REXEC)


# --- MISC ---

clean:
	rm -rf .build

fmt:
	mdformat --wrap 100 *.md
	clang-format -i src/*

# TODO: make install directories variables
install: release
	mkdir -p ~/.local/share/man
	cp ./doc/dotcfg.man ~/.local/share/man/dotcfg.1
	mkdir -p ~/.local/bin
	cp ./.build/release/dotcfg ~/.local/bin/dotcfg

uninstall:
	-rm ~/.local/share/man/dotcfg.1
	-rm ~/.local/bin/dotcfg

help:
	@echo '# Build'
	@echo '`make debug`                     -- debug build'
	@echo '`make release`                   -- release build'
	@echo
	@echo '# Run'
	@echo '`make debug_run ARGS="{ARGS}"`   -- run debug binary with arguments'
	@echo '`make release_run ARGS="{ARGS}"` -- run release binary with arguments'
	@echo
	@echo '# Misc'
	@echo '`make clean`                     -- clean all build artifacts'
	@echo '`make install`                   -- install `dotcfg`'
