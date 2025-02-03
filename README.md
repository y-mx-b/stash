# `dotcfg`

Configure your dotfiles, all from one place!

> [!NOTE]
> `dotcfg` currently only supports UNIX compatible operating systems.

## Usage

### Storage Model

`dotcfg` works by storing all your dotfiles physically in one directory and symlinking them to
where they need to go.

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

Each file will be symlinked such that this will be symlinked to a corresponding location in the
home directory. As such, the above setup would result in the following:

```
~
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

By default, all parent directories will be created in order to symlink the files where they need to be.

### Commands

```sh
dotcfg add
dotcfg link
```

## Configuration

### Directories

#### macOS

The situation of configuration directories is rather complicated on macOS.
