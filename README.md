# Git-Indicator

An indicator for the Unity panel that show sync percentage of all your git repositories in your home directory. You can use it to show information about the origin/master branch compare to your local master one.

`git-indicator` makes fetch and diff from master to origin/master for each repository in order to check differences.

## Screenshots

Panel showing synchronisation in progress.

![git-indicator screenshot 1](https://github.com/UbikZ/git-indicator/blob/gh-pages/img/git_indicator_3.png "git-indicator screenshot 1")

Panel showing total synchronisation of repositories.

![git-indicator screenshot 2](https://github.com/UbikZ/git-indicator/blob/gh-pages/img/git_indicator_2.png "git-indicator screenshot 2")

Panel showing synchronisation of each repositories.

![git-indicator screenshot 3](https://github.com/UbikZ/git-indicator/blob/gh-pages/img/git_indicator.png "git-indicator screenshot 3")

Panel showing notification for repositories which have new commits.

![git-indicator screenshot notify](https://github.com/UbikZ/git-indicator/blob/gh-pages/img/git_indicator_notify.png "git-indicator screenshot notify")



## Motivation

The goal is to have some quick synchronisation information about your [Git](http://www.git-scm.com/) repositories.

From developper point of view, you always need to know if your (or external) repositories are up to date or not. Thus I decided to develop a Gnome indicator to notice the current user if origin branches have new commits.

There is still room for improvement.

## Installation

### Source
> To prepare the install

```bash
$ sudo apt-get install libgtk-2-dev libappindicator2-dev libssh2-1-dev libgit2-dev libnotify-dev
$ git clone https://github.com/ubikz/git-indicator.git
$ cd git-indicator
```

> You may need to compile the libgit2 dependencie yourself

If you want to get the **last stable version** ([here](https://github.com/libgit2/libgit2/releases)).
You can follow [this](https://github.com/libgit2/libgit2) to compile the lib.
**But the application is developped to be compiled/run with 0.20.0 version of libgit.
Why this version? just because it's the one which is released in the precompiled
package from the official repo.
Thus, functions prototypes may have been changed.**

> To install git-indicator

```bash
$ make configure
$ make
$ sudo make install
```

> To clean and uninstall git-indicator

```bash
$ make clean
$ sudo make uninstall
```

> Last two steps in single one

```bash
$ sudo ./rebuild
```

### Autostart

Ubuntu uses `.desktop` files to manage autostart. You may use the one provided
with the sources.
> The make install will copy the destkop autostart file

### Usage

The install creates a bash script: `/usr/local/bin/git-indicator`. It is a service-like script.
You can manage the indicator with **{start|restart|stop|status}** commands.

### Change configuration

The makefile creates default configuration looking for *.git repositories in your home folder.

That's the goal of these commands:
```bash
[ ! -f ~/.$(NAME)/.conf ] && \
find ~/ -type d -name '*.git' | sed "s/\.git//g" | \
egrep -v '(bundle|tests|vendor|.composer)' > ~/.$(NAME)/.conf
```

You can see with `egrep -v` that we're excluding some folders name (dependency repositories).

You can change the `$HOME/.git-indicator/.conf` file, but you need to restart the service.

### Commands-like for test Git-Indicator
> How to test manually the difference between branches for a repository

You can simulate Git-Indicator feature for a repository:
```bash
$ cd $HOME/path/to/my/gitrepository
$ git fetch
$ git rev-list master..origin/master --count
```

If stdout = 0, then your local master is up to date; otherwise there are commits above your local branch.

### Issues

You might encounter some issues.

> "Too many files opened" or "ulimit: max user processes: cannot modify limit"

It's all about linux file open descriptors. By default there are 2^10 per process which
is pretty low actually. We have to increase it **manually**:
* Change the max hard limit from 2^10 to 2^16 ```sudo echo "* hard nofile 65536" >> /etc/security/limits.conf```

The service script ```/usr/local/bin/git-indicator``` (which is used to launch the indicator) uses ```ulimit```
command to increase the number of open descriptors automatically (to 2^16).

> "This transport isn't implemented"

This error occures (in most of the cases) when you want to access to repositories with SSH network protocol.
Then you need to check if **libssh2** library is correctly installed. If all is fine, you need to compile **libgit2**
sources with the right version (git-indicator source code compiled for 0.20.0) and try again.

### Libraries

* [App-Indicator](https://wiki.ubuntu.com/DesktopExperienceTeam/ApplicationIndicators): API for panel indicator aera support (gnome).
* [Libgit2](https://libgit2.github.com/): portable and pure C implementation of the Git core methods provided as a re-entrant linkable library with a solid API, allowing you to write native speed custom Git applications in any language which supports C bindings.
* [NotifyOSD](https://wiki.ubuntu.com/NotifyOSD): desktop notifications framework providing a standard way of doing passive pop-up notifications on the Linux desktop.
* [Libssh2](http://www.libssh2.org/): C library that implements the SSH2 protocol and provide a support transport for **libgit2**.

### TODO LIST
> You can make pull requests adding the feature name

* Add constant progress percentage for fetching
* Add **no connection** icon and disable percentage then
* Improve design for each repository status (**markup for GTK**)

### Ubuntu Package

Currently, there is no pre-compiled package. I might be able to provide one, if
somebody is interested. Just write a feature request.

## License

This program is distributed under the terms of the MIT license. See
[LICENSE](https://github.com/UbikZ/git-indicator/blob/master/LICENSE) file.
