# `stash`

Configure your dotfiles, all from one place!

> [!NOTE]
>
> `stash` currently only supports POSIX compatible operating systems.

## Installation

> [!NOTE]
>
> It is recommended to have `~/.local/share/man` in your `MANPATH` and `~/.local/bin` in your
> `PATH`.

## Usage

### Storage Model

`stash` works by storing all your dotfiles physically in one directory and symlinking them to where
they need to go.

Here is an example `stash` setup:

```
.stash
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

Here is the resulting synced home directory:

```
~
├── .zshrc -> ~/.stash/.zshrc
├── .local
│   └── bin
│       └── my-script -> ~/.stash/bin/my-script
├── .config
│   └── nvim
│       └── init.lua -> ~/.stash/.config/nvim/init.lua
└── Library
    └── Preferences
        └── espanso
            ├── config
            │   └── default.yml -> ~/.stash/Library/Preferences/espanso/config/default.yml
            └── match
                └── base.yml -> ~/.stash/Library/Preferences/espanso/match/base.yml
```
