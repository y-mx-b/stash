# `dotcfg`

Configure your dotfiles, all from one place!

> [!NOTE]
> `dotcfg` currently only supports UNIX compatible operating systems.

## Usage

### Storage Model

`dotcfg` works by storing all your dotfiles physically in one directory and either symlinking them
or physically copying them to where they need to go.

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

### Commands

```sh
dotcfg add
dotcfg link
```

## Configuration

### Directories

#### macOS

The situation of configuration directories is rather complicated on macOS.
