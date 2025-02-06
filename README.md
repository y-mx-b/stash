# `dotcfg`

Configure your dotfiles, all from one place!

> [!NOTE] `dotcfg` currently only supports UNIX compatible operating systems.

## Features

- Localization
- Manage all your dotfiles in a single directory.
- Easily move your configuration between machines.
- Easily maintain your configuration across machines.
- Sync
- Intelligent use of symlinks to keep existing dotfiles in sync.
- Easily add new dotfiles and link them.
- Profiles and Backups
- Backed by `git` with atomic commits.
- Create profiles to maintain different configurations for different machines.

## Installation

> [!NOTE] It is recommended to have `~/.local/share/man` in your `MANPATH` and `~/.local/bin` in
> your `PATH`.

## Usage

### Storage Model

`dotcfg` works by storing all your dotfiles physically in one directory and symlinking them to where
they need to go.

Here is an example `dotcfg` setup:

```
.cfg
├── .zshrc
├── .local
│   └── bin
│       └── my-script
├── .config
│   └── nvim
│       └── init.lua
└── Library
    └── Preferences
        └── espanso
            ├── config
            │   └── default.yml
            └── match
                └── base.yml
```

Instead of symlinking each and every file, `dotcfg` will intelligently symlink directories if it
can, so the above example configuration would result in the following symlinks:

```
~
├── .zshrc -> ~/.cfg/.zshrc
├── .local
│   └── bin
│       └── my-script -> ~/.cfg/bin/my-script
├── .config
│   └── nvim -> ~/.cfg/.config/nvim
│       └── init.lua
└── Library
    └── Preferences
        └── espanso -> ~/.cfg/Library/Preferences/espanso
            ├── config
            │   └── default.yml
            └── match
                └── base.yml
```

Any missing parent directories will be add if necessary.

### Commands

```sh
dotcfg add
dotcfg link
```
