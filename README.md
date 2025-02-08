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

### Actions

`stash` provides several flags to enable certain actions to be taken:

- `-i`: Initialize the working directory.
- `-s`: Sync files in the working directory.
- `-f`: Overwrite any existing files when syncing.
- `-d WORK_PATH`: Provide a custom working directory (default: `"~/.stash/`).

`stash` also allows you to run arbitrary commands within the working directory:

```
stash -i git init
stash echo "hello world" >my_file.txt
stash -i git commit -am "My first file!"
stash -s\fP
```

This snippet initializes a git repository in "~/.stash", creates a file with the contents "hello
world", commits it to the repository, and then creates a symlink "~/my_file.txt" that points to
"~/.stash/my_file.txt".
